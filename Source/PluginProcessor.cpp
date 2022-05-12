/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VSTSynth_JClarkAudioProcessor::VSTSynth_JClarkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    //This section manages the creation and clearing of instances of the synth voice
    synth.clearVoices();
    
    //numVoices determines the polyphony
    for(int i = 0; i < numVoices; ++i)
    {
        synth.addVoice(new SynthVoice());
    }
    
    synth.clearSounds();
    synth.addSound(new SynthSound());
}

VSTSynth_JClarkAudioProcessor::~VSTSynth_JClarkAudioProcessor()
{
}

//==============================================================================
const juce::String VSTSynth_JClarkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VSTSynth_JClarkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VSTSynth_JClarkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VSTSynth_JClarkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VSTSynth_JClarkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VSTSynth_JClarkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VSTSynth_JClarkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VSTSynth_JClarkAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String VSTSynth_JClarkAudioProcessor::getProgramName (int index)
{
    return {};
}

void VSTSynth_JClarkAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void VSTSynth_JClarkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //this function ensures that all elements are aware of the sample rate/samples per block
    
    juce::ignoreUnused(samplesPerBlock);
    
    lastSampleRate = sampleRate;
    
    synth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    for(int i = 0; i < synth.getNumVoices(); ++i)
    {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(lastSampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
    filter.prepareToPlay(lastSampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void VSTSynth_JClarkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VSTSynth_JClarkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VSTSynth_JClarkAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            //OSC Controls
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");

            
            //ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            auto& gainIn = *apvts.getRawParameterValue("GAIN");
            
            auto& fmDepth = *apvts.getRawParameterValue("FMDEPTH");
            auto& fmFreq = *apvts.getRawParameterValue("FMFREQ");
           
            //update various parameters for the synth voice
            voice->getOscillator().setWaveType(oscWaveChoice);
            voice->getOscillator().setFmParams(fmDepth, fmFreq);
            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->updateGain(gainIn);
            
            //LFO
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    //Filter Processing
    
    auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
    auto& filterCutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
    auto& filterRes = *apvts.getRawParameterValue("FILTERRES");
    
    filter.updateParameters(filterType, filterCutoff, filterRes);
    
    filter.process(buffer);
}

//==============================================================================
bool VSTSynth_JClarkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VSTSynth_JClarkAudioProcessor::createEditor()
{
    return new VSTSynth_JClarkAudioProcessorEditor (*this);
}

//==============================================================================
void VSTSynth_JClarkAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VSTSynth_JClarkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VSTSynth_JClarkAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout VSTSynth_JClarkAudioProcessor::createParameters()
{
    //This is where all editable parameters are created
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //waveform selection
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    
    //Gain control
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.8f));
    
    //FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMFREQ", "FM Frequency", juce::NormalisableRange<float>{ 0.0f, 1000.0f, 0.01f, 0.3f }, 5.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMDEPTH", "FM Depth", juce::NormalisableRange<float>{ 0.0f, 1000.0f, 0.01f, 0.3f }, 130.0f));
    
    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{ 0.1f, 4.0f, 0.1f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{ 0.1f, 1.0f, 0.1f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.1f}, 0.9f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{ 0.1f, 5.0f, 0.1f}, 0.4f));
    
    //Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray {"Low-Pass", "Band-Pass", "High-Pass"}, 1));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float>{ 20.0f, 20000.0f, 0.6f}, 200.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float>{ 1.0f, 10.0f}, 1.0f));

    
    return { params.begin(), params.end()};
}

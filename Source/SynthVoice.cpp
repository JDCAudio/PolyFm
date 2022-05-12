/*
  ==============================================================================

    SynthVoice.cpp
    Created: 16 Apr 2022 6:41:54pm
    Author:  Jacob Clark

  ==============================================================================
*/

#include "SynthVoice.h"



bool SynthVoice::canPlaySound (juce::SynthesiserSound * sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setWaveFreq(midiNoteNumber);
    adsr.noteOn();
}
void  SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (! allowTailOff || ! adsr.isActive())
        clearCurrentNote();
}
void  SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
void  SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}
void  SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    //initialize values that need to be set before playtime
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    //send values to osc
    osc.prepareToPlay(spec);
    //send values to gain
    gain.prepare(spec);
    

    isPrepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateGain(const float gainIn)
{
    float gainInLin = gainIn / 2;
    
    //set gain
    gain.setGainLinear(gainInLin);
}

void  SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    if (! isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    //create audio block
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    
    //process oscillator information in audioBlock
    osc.getNextAudioBlock(audioBlock);
    
    //process oscillator information through gain process
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    //apply envelope to synth buffer
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    if ( startSample != 0 )
        jassertfalse;
    
    for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (! adsr.isActive())
            clearCurrentNote();
     
    }
}

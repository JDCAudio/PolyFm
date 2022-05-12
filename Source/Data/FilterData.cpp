/*
  ==============================================================================

    FilterData.cpp
    Created: 2 May 2022 1:56:48am
    Author:  Jacob Clark

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    filter.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    filter.prepare(spec);
    
    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert (isPrepared);
    
    juce::dsp::AudioBlock<float> block { buffer };
    
    filter.process(juce::dsp::ProcessContextReplacing<float> { block });
}

void FilterData::updateParameters(const int filterType, const float freq, const float res)
{
    switch(filterType)
    {
        case 0:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
            
        case 1:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
            
        case 2:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
    }
    
    filter.setCutoffFrequency(freq);
    filter.setResonance(res);
    
    
}

void FilterData::reset()
{
    filter.reset();
}

/*
  ==============================================================================

    FilterData.h
    Created: 2 May 2022 1:56:48am
    Author:  Jacob Clark

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int filterType, const float freq, const float res);
    void reset();
    
private:
    bool isPrepared { false };
    juce::dsp::StateVariableTPTFilter<float> filter;
};

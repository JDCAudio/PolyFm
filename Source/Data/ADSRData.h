/*
  ==============================================================================

    ADSRData.h
    Created: 23 Apr 2022 7:56:05pm
    Author:  Jacob Clark

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    
private:
    //adsr parameters
    juce::ADSR::Parameters adsrParams;
    
};


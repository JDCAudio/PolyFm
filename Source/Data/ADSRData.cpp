/*
  ==============================================================================

    ADSRData.cpp
    Created: 23 Apr 2022 7:56:05pm
    Author:  Jacob Clark

  ==============================================================================
*/

#include "ADSRData.h"
#include <JuceHeader.h>

void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    //set ADSR
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters(adsrParams);
}

/*
  ==============================================================================

    SynthSound.h
    Created: 16 Apr 2022 6:44:20pm
    Author:  Jacob Clark

  ==============================================================================
*/

#pragma once

//include juce header (allows to call juce objects)
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};

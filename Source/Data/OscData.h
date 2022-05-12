/*
  ==============================================================================

    OscData.h
    Created: 23 Apr 2022 9:56:44pm
    Author:  Jacob Clark

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFreq(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParams (const float depth, const float freq);
    
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x);} };
    float fmMod { 0.0f };
    float fmDepth { 0.0f };
    int lastMidiNote { 0 };
    
};

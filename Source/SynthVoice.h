/*
  ==============================================================================

    SynthVoice.h
    Created: 16 Apr 2022 6:41:54pm
    Author:  Jacob Clark

  ==============================================================================
*/

#pragma once

//include juce header
#include <JuceHeader.h>
//include SynthSound
#include "SynthSound.h"
#include "Data/ADSRData.h"
#include "Data/OscData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound * sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void  stopNote (float velocity, bool allowTailOff) override;
    void  controllerMoved (int controllerNumber, int newControllerValue) override;
    void  pitchWheelMoved (int newPitchWheelValue) override;
    void  prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void  renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void update(const float attack, const float deca,const float sustain, const float release);
    
    OscData& getOscillator() { return osc; }
    
    void updateGain(const float gainIn);
    
private:
    juce::AudioBuffer<float> synthBuffer;
    
    ADSRData adsr;
    
    //declare an oscillator "osc" recieves x and outputs sin x
    OscData osc;
    //juce::dsp::Oscillator<float> osc { [](float x) {return x / juce::MathConstants<float>::pi;}};
    //juce::dsp::Oscillator<float> osc;
  
    //create a gain
    juce::dsp::Gain<float> gain;
    
    //variable to ensure everything is initialized correctly
    bool isPrepared {false};
    
};

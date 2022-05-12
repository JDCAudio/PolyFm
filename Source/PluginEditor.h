/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"

//==============================================================================
/**
*/
class VSTSynth_JClarkAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    VSTSynth_JClarkAudioProcessorEditor (VSTSynth_JClarkAudioProcessor&);
    ~VSTSynth_JClarkAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VSTSynth_JClarkAudioProcessor& audioProcessor;
    
    //create an instance of the osc, adsr and filter
    OscComponent osc;
    ADSRComponent adsr;
    FilterComponent filter;
    
    //create an instance of the gain slider (these other steps are taken care of within the Osc/Adsr/Filter classes
    juce::Slider gainSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> gainAttachment;
    
    juce::Label gainLabel {"Gain", "Gain"};

    
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VSTSynth_JClarkAudioProcessorEditor)
};

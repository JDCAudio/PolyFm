/*
  ==============================================================================

    ADSRComponent.h
    Created: 23 Apr 2022 7:54:35pm
    Author:  Jacob Clark

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRComponent : public juce::Component
{
public:
    ADSRComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ADSRComponent() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    
private:
    void setADSRSliderParams(juce::Slider& slider);
    
    
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    juce::Label attackLabel { "Attack", "Attack"};
    juce::Label decayLabel { "Decay", "Decay"};
    juce::Label sustainLabel { "Sustain", "Sustain"};
    juce::Label releaseLabel { "Release", "Release"};

     
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    
};


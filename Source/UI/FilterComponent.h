/*
  ==============================================================================

    FilterComponent.h
    Created: 2 May 2022 2:48:11am
    Author:  Jacob Clark

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;
    juce::Label cutoffLabel { "Cutoff", "Cutoff"};
    juce::Label resLabel { "Resonance", "Resonance"};


    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;
    
    juce::ComboBox filterSelector {"Filter Type"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};

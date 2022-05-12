/*
  ==============================================================================

    FilterComponent.cpp
    Created: 2 May 2022 2:48:11am
    Author:  Jacob Clark

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    cutoffAttachment = std::make_unique<SliderAttachment>(apvts, "FILTERCUTOFF", cutoffSlider);
    resonanceAttachment = std::make_unique<SliderAttachment>(apvts, "FILTERRES", resonanceSlider);
    filterSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "FILTERTYPE", filterSelector);
    
    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(cutoffSlider);
    
    resonanceSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    resonanceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(resonanceSlider);
    
    juce::StringArray choices { "Low-Pass", "Band-Pass", "High-Pass" };
    filterSelector.addItemList(choices, 1);
    addAndMakeVisible(filterSelector);
    
    cutoffLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    cutoffLabel.setFont(15.0f);
    cutoffLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(cutoffLabel);
    
    resLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    resLabel.setFont(15.0f);
    resLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(resLabel);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    const auto bounds = getLocalBounds();
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), 5.0f, 3.0f);
    g.setFont(40.0f);
    g.drawFittedText("FIL", bounds.getX() + bounds.getWidth() * 0.1, bounds.getCentreY(), bounds.getWidth() * 0.25, bounds.getHeight() * 0.25, juce::Justification::centred, 1);
}

void FilterComponent::resized()
{
    const auto bounds = getLocalBounds();
    float padding = bounds.getWidth() * 0.06;

    
    filterSelector.setBounds(bounds.getX() + padding, bounds.getCentreY() - bounds.getHeight() * 0.4, bounds.getWidth() / 3, bounds.getHeight() / 4);
    cutoffSlider.setBounds(filterSelector.getRight() + bounds.getWidth() * 0.06, bounds.getCentreY() - bounds.getHeight() * 0.3, bounds.getWidth() * 0.25, bounds.getHeight() * 0.5);
    resonanceSlider.setBounds(cutoffSlider.getX() + bounds.getWidth() * 0.25, bounds.getCentreY() - bounds.getHeight() * 0.3, bounds.getWidth() * 0.25, bounds.getHeight() * 0.5);
    
    cutoffLabel.setBounds(cutoffSlider.getX(), cutoffSlider.getY() - getLocalBounds().getHeight() * 0.05, cutoffSlider.getWidth(), 20);
    
    resLabel.setBounds(resonanceSlider.getX(), resonanceSlider.getY() - getLocalBounds().getHeight() * 0.05, resonanceSlider.getWidth(), 20);

}

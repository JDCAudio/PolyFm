/*
  ==============================================================================

    OscComponent.cpp
    Created: 23 Apr 2022 10:37:42pm
    Author:  Jacob Clark

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId)
{
    juce::StringArray choices { "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(choices, 1);
    
    addAndMakeVisible(oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
    
    fmFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    fmFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(fmFreqSlider);
    
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider);
    
    fmFreqLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    fmFreqLabel.setFont(15.0f);
    fmFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(fmFreqLabel);
    
    fmDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    fmDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(fmDepthSlider);
    
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider);
    
    fmDepthLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    fmDepthLabel.setFont(15.0f);
    fmDepthLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(fmDepthLabel);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    const auto bounds = getLocalBounds();

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), 5.0f, 3.0f);
    g.setFont(40.0f);
    g.drawFittedText("OSC", bounds.getX() + bounds.getWidth() * 0.1, bounds.getCentreY(), bounds.getWidth() * 0.25, bounds.getHeight() * 0.25, juce::Justification::centred, 1);
}

void OscComponent::resized()
{
    const auto bounds = getLocalBounds();
    float padding = bounds.getWidth() * 0.06;

    //oscWaveSelector.setBounds(25, 25, 300, 50);
    oscWaveSelector.setBounds(bounds.getX() + padding, bounds.getCentreY() - bounds.getHeight() * 0.4, bounds.getWidth() / 3, bounds.getHeight() / 4);
    //oscWaveSelector.setBounds(getWidth() * 0.025, getHeight() * 0.05, getWidth() * 0.3, getHeight() * 0.1);
    
    fmFreqSlider.setBounds(oscWaveSelector.getRight() + bounds.getWidth() * 0.06, bounds.getCentreY() - bounds.getHeight() * 0.3, bounds.getWidth() * 0.25, bounds.getHeight() * 0.5);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - bounds.getHeight() * 0.05, fmFreqSlider.getWidth(), 20);
    
    fmDepthSlider.setBounds(fmFreqSlider.getX() + bounds.getWidth() * 0.25, bounds.getCentreY() - bounds.getHeight() * 0.3, bounds.getWidth() * 0.25, bounds.getHeight() * 0.5);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - bounds.getHeight() * 0.05, fmDepthSlider.getWidth(), 20);
}

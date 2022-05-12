/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 23 Apr 2022 7:54:35pm
    Author:  Jacob Clark

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"


ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    
    setADSRSliderParams(attackSlider);
    setADSRSliderParams(decaySlider);
    setADSRSliderParams(sustainSlider);
    setADSRSliderParams(releaseSlider);
    
    attackLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    attackLabel.setFont(15.0f);
    attackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(attackLabel);
    
    decayLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    decayLabel.setFont(15.0f);
    decayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(decayLabel);
    
    sustainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    sustainLabel.setFont(15.0f);
    sustainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sustainLabel);
    
    releaseLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    releaseLabel.setFont(15.0f);
    releaseLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(releaseLabel);
}

ADSRComponent::~ADSRComponent()
{
    
}

void ADSRComponent::paint (juce::Graphics& g)
{
    const auto bounds = getLocalBounds();
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), 5.0f, 3.0f);
    g.setFont(40.0f);
    g.drawFittedText("ENV", bounds.getCentreX() - bounds.getWidth() * 0.125, bounds.getCentreY() + bounds.getHeight() * 0.1, bounds.getWidth() * 0.25, bounds.getHeight() * 0.25, juce::Justification::centred, 1);
}

void ADSRComponent::resized()
{
   /*
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto ADSRsliderWidth = bounds.getWidth() / 4 - padding;
    const auto ADSRsliderHeight = bounds.getWidth() / 2 - padding;
    const auto ADSRstartX = 10;
    const auto ADSRstartY = bounds.getCentreY() + (ADSRsliderHeight / 2);
    
    attackSlider.setBounds(ADSRstartX, ADSRstartY, ADSRsliderWidth, ADSRsliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, ADSRstartY, ADSRsliderWidth, ADSRsliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, ADSRstartY, ADSRsliderWidth, ADSRsliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, ADSRstartY, ADSRsliderWidth, ADSRsliderHeight);
     */
    attackSlider.setBounds(getLocalBounds().getX(), getLocalBounds().getY() + getLocalBounds().getHeight() * 0.09, getLocalBounds().getWidth() * 0.25, getLocalBounds().getHeight() * 0.4);
    decaySlider.setBounds(attackSlider.getRight(), getLocalBounds().getY() + getLocalBounds().getHeight() * 0.09, getLocalBounds().getWidth() * 0.25, getLocalBounds().getHeight() * 0.4);
    sustainSlider.setBounds(decaySlider.getRight(), getLocalBounds().getY() + getLocalBounds().getHeight() * 0.09, getLocalBounds().getWidth() * 0.25, getLocalBounds().getHeight() * 0.4);
    releaseSlider.setBounds(sustainSlider.getRight(), getLocalBounds().getY() + getLocalBounds().getHeight() * 0.09, getLocalBounds().getWidth() * 0.25, getLocalBounds().getHeight() * 0.4);
    
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() - getLocalBounds().getHeight() * 0.05, attackSlider.getWidth(), 20);
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getY() - getLocalBounds().getHeight() * 0.05, decaySlider.getWidth(), 20);
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getY() - getLocalBounds().getHeight() * 0.05, sustainSlider.getWidth(), 20);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() - getLocalBounds().getHeight() * 0.05, releaseSlider.getWidth(), 20);
    
    //attackSlider.setBounds(getLocalBounds());
    //decaySlider.setBounds(getLocalBounds());
   // sustainSlider.setBounds(getLocalBounds());
    //releaseSlider.setBounds(getLocalBounds());
}

void ADSRComponent::setADSRSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(slider);
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VSTSynth_JClarkAudioProcessorEditor::VSTSynth_JClarkAudioProcessorEditor (VSTSynth_JClarkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc (audioProcessor.apvts, "OSC1WAVETYPE", "FMFREQ", "FMDEPTH"), adsr (audioProcessor.apvts), filter (audioProcessor.apvts)
{
    
    //connect gain slider to value tree state
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    gainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "GAIN", gainSlider);
    
    
    //create gain slider gui
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(gainSlider);
    
    //gain label
    gainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    gainLabel.setFont(15.0f);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);
    
    
    //create wave selector gui
    //addAndMakeVisible(waveSelector);
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    
    //make resizeable from bottom right corner
    setResizable(true, true);
    setResizeLimits(500, 250, 2000, 1000);
    //width = height * 2
    getConstrainer()->setFixedAspectRatio(2.0);
    
    
    //Color pallete
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::red.darker(1));
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::red.darker(2));
    getLookAndFeel().setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::lightgrey);
    getLookAndFeel().setColour(juce::Slider::textBoxTextColourId, juce::Colours::lightgrey);
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker(3));
    
    //set initial size
    setSize(1000, 500);
}

VSTSynth_JClarkAudioProcessorEditor::~VSTSynth_JClarkAudioProcessorEditor()
{
}

//==============================================================================
void VSTSynth_JClarkAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void VSTSynth_JClarkAudioProcessorEditor::resized()
{
    //set osc bounds
    osc.setBounds((getWidth() * 0.015) + getWidth() * 0.015, getHeight() * 0.05, getWidth() * 0.4, getHeight() * 0.4);
    
    //set adsr bounds
    adsr.setBounds(osc.getRight() + getWidth() * 0.015, getHeight() * 0.05, getWidth() * 0.4, getHeight() * 0.4);
    
    //set filter bounds
    filter.setBounds(osc.getX() + osc.getWidth() * 0.5, osc.getBottom() + getHeight() * 0.02, getWidth() * 0.4, getHeight() * 0.4);
    
    //set gain bounds
    gainSlider.setBounds(getWidth() * 0.9, getHeight() * 0.2, getWidth() * 0.05, getHeight() * 0.6);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() - 10, gainSlider.getWidth(), 20);
}



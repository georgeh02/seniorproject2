/*
  ==============================================================================

    OscComponent.cpp
    Created: 18 Mar 2024 11:15:53pm
    Author:  George Harrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String gainSelectorId)
{
    componentName = name;
    
    juce::StringArray choices {"Sine", "Saw", "Square"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
    
    oscWaveSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    oscWaveSelectorLabel.setFont (15.0f);
    oscWaveSelectorLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (oscWaveSelectorLabel);
    
    setSliderWithLabel(oscGainSlider, oscGainLabel, apvts, gainSelectorId, oscGainAttachment);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText(componentName, labelSpace.withX(10), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 3.0f);
    
    //g.setColour(juce::Colours::grey);
    //g.fillRoundedRectangle(bounds.toFloat(), 5.0f);
}

void OscComponent::resized()
{
    const auto padding = 25;
    const auto boxHeight = 20;
    const auto bounds = getLocalBounds().reduced(padding);
    
    oscWaveSelector.setBounds (padding, bounds.getHeight() - padding, bounds.getWidth()/4, boxHeight);
    oscWaveSelectorLabel.setBounds (oscWaveSelector.getX(), oscWaveSelector.getY()-padding, oscWaveSelector.getWidth(), boxHeight);
    
    oscGainSlider.setBounds (oscWaveSelector.getRight(), oscWaveSelector.getY()-padding, bounds.getWidth()/4, bounds.getHeight());
    oscGainLabel.setBounds (oscGainSlider.getX(), oscWaveSelector.getY()-padding, oscGainSlider.getWidth(), boxHeight);
}

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

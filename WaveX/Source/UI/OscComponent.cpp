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
    
    helper.setComboBox(oscWaveSelector, oscWaveSelectorLabel, choices, apvts, waveSelectorId, oscWaveSelectorAttachment, *this);
    helper.setSliderWithLabel(oscGainSlider, oscGainLabel, apvts, gainSelectorId, oscGainAttachment, *this);
}


OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.setColour(juce::Colours::black);
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
    
    oscWaveSelector.setBounds (padding, padding * 2, bounds.getWidth()/2, boxHeight);
    //oscWaveSelectorLabel.setBounds (oscWaveSelector.getX(), padding, oscWaveSelector.getWidth(), boxHeight);
    
    oscGainSlider.setBounds (oscWaveSelector.getRight(), padding * 2, bounds.getWidth()/2, bounds.getHeight() - (padding/2));
    oscGainLabel.setBounds (oscGainSlider.getX(), padding * 1.5, bounds.getWidth()/2, boxHeight);
}

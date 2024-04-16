/*
  ==============================================================================

    FilterComponent.cpp
    Created: 2 Apr 2024 1:53:35pm
    Author:  George Harrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId)
{
    juce::StringArray choices {"Low-Pass", "Band-Pass", "High-Pass"};
    
    helper.setComboBox(filterTypeSelector, filterTypeSelectorLabel, choices, apvts, filterTypeSelectorId, filterTypeSelectorAttachment, *this);
    helper.setSliderWithLabel(filterFreq, filterFreqLabel, apvts, filterFreqId, filterFreqAttachment, *this);
    helper.setSliderWithLabel(filterRes, filterResLabel, apvts, filterResId, filterResAttachment, *this);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::black);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(10), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 3.0f);
}

void FilterComponent::resized()
{
    const auto padding = 25;
    const auto boxHeight = 20;
    const auto bounds = getLocalBounds().reduced(padding);
    
    filterTypeSelector.setBounds(padding, padding * 3, bounds.getWidth()/3, boxHeight);
    filterTypeSelectorLabel.setBounds(filterTypeSelector.getX(), filterTypeSelector.getY()-padding, filterTypeSelector.getWidth(), boxHeight);
    
    filterFreq.setBounds(filterTypeSelectorLabel.getRight(), padding * 3, bounds.getWidth()/3, bounds.getHeight()/2);
    filterFreqLabel.setBounds(filterFreq.getX(), filterFreq.getY()-padding, filterFreq.getWidth(), boxHeight);
    
    filterRes.setBounds(filterFreq.getRight(), padding * 3, bounds.getWidth()/3, bounds.getHeight()/2);
    filterResLabel.setBounds(filterRes.getX(), filterRes.getY()-padding, filterRes.getWidth(), boxHeight);
}

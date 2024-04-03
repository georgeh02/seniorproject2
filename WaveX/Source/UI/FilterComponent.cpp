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
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);
    
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeSelectorId, filterTypeSelector);
    
    filterTypeSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterTypeSelectorLabel.setFont(15.0f);
    filterTypeSelectorLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(filterTypeSelectorLabel);
    
    
    setSliderWithLabel(filterFreq, filterFreqLabel, apvts, filterFreqId, filterFreqAttachment);
    setSliderWithLabel(filterRes, filterResLabel, apvts, filterResId, filterResAttachment);


}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::white);
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

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

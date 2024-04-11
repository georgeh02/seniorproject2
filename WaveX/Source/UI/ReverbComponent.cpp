/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 5 Apr 2024 5:58:25pm
    Author:  George Harrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String roomSizeId, juce::String reverbMixId)
{
    setSliderWithLabel(roomSize, roomSizeLabel, apvts, roomSizeId, roomSizeAttachment);
    setSliderWithLabel(reverbMix, reverbMixLabel, apvts, reverbMixId, reverbMixAttachment);
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::black);
    g.setFont(20.0f);
    g.drawText("Reverb", labelSpace.withX(10), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 3.0f);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void ReverbComponent::resized()
{
    const auto padding = 25;
    const auto boxHeight = 20;
    const auto bounds = getLocalBounds().reduced(padding);
    
    roomSize.setBounds(padding, padding * 3, bounds.getWidth()/3, bounds.getHeight()/2);
    roomSizeLabel.setBounds(roomSize.getX(), roomSize.getY()-padding, roomSize.getWidth(), boxHeight);
    
    reverbMix.setBounds(roomSizeLabel.getRight(), padding * 3, bounds.getWidth()/3, bounds.getHeight()/2);
    reverbMixLabel.setBounds(reverbMix.getX(), reverbMix.getY()-padding, reverbMix.getWidth(), boxHeight);
}

void ReverbComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

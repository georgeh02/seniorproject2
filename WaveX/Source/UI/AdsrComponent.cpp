/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 18 Mar 2024 10:15:02pm
    Author:  George Harrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    componentName = name;
    
    setSliderWithLabel (attackSlider, attackLabel, apvts, attackId, attackAttachment);
    setSliderWithLabel (decaySlider, decayLabel, apvts, decayId, decayAttachment);
    setSliderWithLabel (sustainSlider, sustainLabel, apvts, sustainId, sustainAttachment);
    setSliderWithLabel (releaseSlider, releaseLabel, apvts, releaseId, releaseAttachment);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText(componentName, labelSpace.withX (10), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 3.0f);
}

void AdsrComponent::resized()
{
    const auto padding = 25;
    const auto bounds = getLocalBounds().reduced(padding);
    const auto sliderWidth = bounds.getWidth() / 4;
    const auto sliderHeight = bounds.getHeight() - (padding * 2);
    const auto sliderStartX = padding;
    const auto sliderStartY = padding * 3;
    const auto labelHeight = padding;
    const auto labelStart = sliderStartY - padding;
    
    attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds (attackSlider.getX(), labelStart, sliderWidth, labelHeight);

    decaySlider.setBounds (attackSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds (decaySlider.getX(), labelStart, sliderWidth, labelHeight);

    sustainSlider.setBounds (decaySlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds (sustainSlider.getX(), labelStart, sliderWidth, labelHeight);

    releaseSlider.setBounds (sustainSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds (releaseSlider.getX(), labelStart, sliderWidth, labelHeight);
}

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void AdsrComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont (15.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

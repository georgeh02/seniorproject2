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
    oscWaveSelectorLabel.setJustificationType (juce::Justification::left);
    addAndMakeVisible (oscWaveSelectorLabel);
    
    setSliderWithLabel(oscGainSlider, oscGainLabel, apvts, gainSelectorId, oscGainAttachment);
    
    
//    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainSelectorId, oscGainSlider);
//    oscGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
//    oscGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
//    addAndMakeVisible(oscGainSlider);

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
}

void OscComponent::resized()
{
    
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    oscWaveSelector.setBounds (10, startY + 5, 90, 30);
    oscWaveSelectorLabel.setBounds (10, startY - labelYOffset, 90, labelHeight);
    
    oscGainSlider.setBounds (oscWaveSelector.getRight(), startY, sliderWidth, sliderHeight);
    oscGainLabel.setBounds (oscGainSlider.getX(), oscGainSlider.getY() - labelYOffset, oscGainSlider.getWidth(), labelHeight);
}

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
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

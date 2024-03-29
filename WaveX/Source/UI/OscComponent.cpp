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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String gainSelectorId)
{
    juce::StringArray choices {"Sine", "Saw", "Square"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
    
    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainSelectorId, oscGainSlider);
    oscGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    oscGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(oscGainSlider);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    oscWaveSelector.setBounds(0,0,90,20);

    oscGainSlider.setBounds(0, 0, 20, 200);
}

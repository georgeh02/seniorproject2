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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{
    juce::StringArray choices {"Sine", "Saw", "Square"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);
    
    oscWaveSelectorAttachement = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);

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
}

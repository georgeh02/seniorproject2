/*
  ==============================================================================

    GUIHelper.cpp
    Created: 16 Apr 2024 12:53:45pm
    Author:  George Harrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GUIHelper.h"

//==============================================================================

void GUIHelper::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::Component& parentComponent)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    parentComponent.addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    parentComponent.addAndMakeVisible(label);
}

void GUIHelper::setComboBox(juce::ComboBox& comboBox, juce::Label& label, juce::StringArray& choices, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>& attachment,  juce::Component& parentComponent)
{
    comboBox.addItemList(choices, 1);
    parentComponent.addAndMakeVisible(comboBox);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, paramId, comboBox);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::left);
    parentComponent.addAndMakeVisible(label);

    
}


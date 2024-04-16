/*
  ==============================================================================

    GUIHelper.h
    Created: 16 Apr 2024 12:53:45pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GUIHelper
{
public:
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::Component& parentComponent);
    
    void setComboBox(juce::ComboBox& comboBox, juce::Label& label, juce::StringArray& choices, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>& attachment,  juce::Component& parentComponent);
};



/*
  ==============================================================================

    OscComponent.h
    Created: 18 Mar 2024 11:15:53pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GUIHelper.h"

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String gainSelectorId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelector{"Wave Type"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    
    juce::Slider oscGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscGainAttachment;
    
    juce::Label oscWaveSelectorLabel{"Wave Type", "Wave Type"};
    juce::Label oscGainLabel{"Osc Gain", "Osc Gain"};
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    juce::String componentName {""};
    
    GUIHelper helper;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};

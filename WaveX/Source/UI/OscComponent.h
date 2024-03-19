/*
  ==============================================================================

    OscComponent.h
    Created: 18 Mar 2024 11:15:53pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachement;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};

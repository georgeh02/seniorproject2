/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/DelayComponent.h"

//==============================================================================
/**
*/
class WaveXAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WaveXAudioProcessorEditor (WaveXAudioProcessor&);
    ~WaveXAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    WaveXAudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    AdsrComponent adsr;
    FilterComponent filter;
    DelayComponent delay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveXAudioProcessorEditor)
};

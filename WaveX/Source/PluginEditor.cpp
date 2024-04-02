/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveXAudioProcessorEditor::WaveXAudioProcessorEditor (WaveXAudioProcessor& p)
    : AudioProcessorEditor (&p)
, audioProcessor (p)
, osc1(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1GAIN")
, osc2(audioProcessor.apvts, "OSC2WAVETYPE", "OSC2GAIN")
, adsr(audioProcessor.apvts)
, filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
{
    setSize (800, 800);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
}

WaveXAudioProcessorEditor::~WaveXAudioProcessorEditor()
{
}

//==============================================================================
void WaveXAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void WaveXAudioProcessorEditor::resized()
{
    osc1.setBounds(10,10, 100, 200);
    osc2.setBounds(150,10, 100, 200);
    adsr.setBounds(getWidth()/2, 0, getWidth() / 2, getHeight());
    filter.setBounds(10, 270, 300, 200);
}



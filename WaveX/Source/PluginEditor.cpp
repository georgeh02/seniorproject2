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
, osc1("Osc A", audioProcessor.apvts, "OSC1WAVETYPE", "OSC1MIX")
, osc2("Osc B", audioProcessor.apvts, "OSC2WAVETYPE", "OSC2MIX")
, adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
, filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
, delay(audioProcessor.apvts, "DELAYTIME", "FEEDBACK", "DELAYMIX")
, reverb(audioProcessor.apvts, "ROOMSIZE", "REVERBMIX")
//, audioProcessor.visualizer()
{
    setSize (600, 800);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(delay);
    addAndMakeVisible(reverb);
    
    addAndMakeVisible(audioProcessor.visualizer);
    audioProcessor.visualizer.setColours(juce::Colours::darkred, juce::Colours::whitesmoke);

}

WaveXAudioProcessorEditor::~WaveXAudioProcessorEditor()
{
}

//==============================================================================
void WaveXAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
}

void WaveXAudioProcessorEditor::resized()
{
//    osc1.setBounds(0, 100, 500, 150);
//    osc2.setBounds(0, 250, 500, 150);
//    adsr.setBounds(500, 100, 300, 300);
//    filter.setBounds(500, 400, 300, 300);
    
    auto bounds = getLocalBounds();
    
    audioProcessor.visualizer.setBounds(0, 0, bounds.getWidth()/3, 100.0f);
    
    auto labelSpace = bounds.removeFromTop(100.0f);
    
    osc1.setBounds(0, labelSpace.getHeight(), bounds.getWidth()/2, bounds.getHeight()/4);
    osc2.setBounds(0, labelSpace.getHeight()+osc1.getHeight(), bounds.getWidth()/2, bounds.getHeight()/4);
    adsr.setBounds(osc1.getWidth(), labelSpace.getHeight(), bounds.getWidth()/2, bounds.getHeight()/2);
    filter.setBounds(osc1.getWidth(), labelSpace.getHeight()+adsr.getHeight(), bounds.getWidth()/2, bounds.getHeight()/2);
    delay.setBounds(0, labelSpace.getHeight()+adsr.getHeight(), bounds.getWidth()/2, bounds.getHeight()/4);
    reverb.setBounds(0, labelSpace.getHeight()+adsr.getHeight()+delay.getHeight(), bounds.getWidth()/2, bounds.getHeight()/4);

}



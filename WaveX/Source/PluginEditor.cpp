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
, osc1("Osc A", audioProcessor.apvts, "OSC1WAVETYPE", "OSC1GAIN")
, osc2("Osc B", audioProcessor.apvts, "OSC2WAVETYPE", "OSC2GAIN")
, adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
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
    g.fillAll (juce::Colours::black);
    
    //draw osc barrier
//    auto bounds = getLocalBounds().reduced(5);
//    auto labelSpace = bounds.removeFromTop(25.0f);
//    g.fillAll(juce::Colours::black);
//    g.setColour(juce::Colours::white);
//    g.setFont(20.0f);
//    g.drawText("Oscillator", labelSpace.withX(5), juce::Justification::left);
//    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 3.0f);
    
//
//    //DRAW OSC SECTION
//    // Define the bounds for the oscillator section including padding
//    int padding = 10; // Additional padding
//    int width = 400 - 2 * padding; // Subtract padding from width
//    int height = 200 - 2 * padding; // Subtract padding from height
//    juce::Rectangle<int> oscillatorBounds(padding, padding, width, height);
//
//    // Draw the outline for the oscillator section
//    g.setColour(juce::Colours::white);
//    g.drawRoundedRectangle(oscillatorBounds.toFloat(), 5.0f, 3.0f);
//
//    g.setFont(20.0f);
//    g.drawText("Oscillator", oscillatorBounds.getX() + padding, oscillatorBounds.getY() + padding, 200, 25, juce::Justification::left);
}

void WaveXAudioProcessorEditor::resized()
{
    osc1.setBounds(0, 100, 500, 150);
    osc2.setBounds(0, 250, 500, 150);
    adsr.setBounds(500, 100, 300, 300);
    filter.setBounds(500, 400, 300, 300);
}



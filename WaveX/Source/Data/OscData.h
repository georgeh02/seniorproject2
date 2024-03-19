/*
  ==============================================================================

    OscData.h
    Created: 18 Mar 2024 10:54:13pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::ProcessContextReplacing<float>& context);
private:
};

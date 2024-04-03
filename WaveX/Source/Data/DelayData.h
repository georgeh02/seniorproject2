/*
  ==============================================================================

    DelayData.h
    Created: 3 Apr 2024 10:58:34am
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DelayData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const float delayTime);
    void reset();
    
private:
    juce::dsp::DelayLine<float> delay;
    bool isPrepared{false};
};

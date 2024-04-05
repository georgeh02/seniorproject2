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
    void updateParameters(const float delayTime, double sampleRate);
    void reset();
    
private:
    static constexpr auto effectDelaySamples = 192000;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delay {effectDelaySamples};
    std::array<float, 2> lastDelayOutput;
    std::array<float, 2> delayValue{{}};
    
    bool isPrepared{false};
};

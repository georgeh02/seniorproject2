/*
  ==============================================================================

    DelayData.h
    Created: 3 Apr 2024 10:58:34am
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ComponentBase.h"

class DelayData : public ComponentBase
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const juce::NamedValueSet& paramValues) override;
    void reset();
private:
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delay{192000}; //max possible samplerate
    juce::dsp::DryWetMixer<float> mixer;
    std::array<float, 2> lastDelayOutput;
    std::array<juce::LinearSmoothedValue<float>, 2> delayFeedbackVolume;
    double sampleRate;
    bool isPrepared{false};
};

/*
  ==============================================================================

    LimiterData.h
    Created: 23 Apr 2024 3:30:18pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ComponentBase.h"

class LimiterData : public ComponentBase
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const juce::NamedValueSet& paramValues) override;
    void reset();
private:
    juce::dsp::Limiter<float> limiter;
    bool isPrepared{false};
};

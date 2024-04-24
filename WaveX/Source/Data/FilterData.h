/*
  ==============================================================================

    FilterData.h
    Created: 2 Apr 2024 1:14:21pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ComponentBase.h"

class FilterData : public ComponentBase
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const juce::NamedValueSet& paramValues) override;
    void reset();
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{false};
};

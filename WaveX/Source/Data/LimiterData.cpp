/*
  ==============================================================================

    LimiterData.cpp
    Created: 23 Apr 2024 3:30:18pm
    Author:  George Harrison

  ==============================================================================
*/

#include "LimiterData.h"

void LimiterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    limiter.reset();
    limiter.prepare(spec);
    isPrepared = true;
}

void LimiterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float>block{buffer};
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
    limiter.process(context);
}

void LimiterData::updateParameters(const juce::NamedValueSet& paramValues)
{
    limiter.setThreshold(static_cast<float>(paramValues["THRESHOLD"]));
    limiter.setRelease(static_cast<float>(paramValues["RELEASE"]));
}

void LimiterData::reset()
{
    limiter.reset();
}

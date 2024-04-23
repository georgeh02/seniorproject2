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
    limiter.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    limiter.prepare(spec);
    
    isPrepared = true;
}

void LimiterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> block { buffer };
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
    limiter.process(context);
}

void LimiterData::updateParameters(const float threshold, const float release)
{
    limiter.setThreshold(threshold);
    limiter.setRelease(release);
}

void LimiterData::reset()
{
    limiter.reset();
}

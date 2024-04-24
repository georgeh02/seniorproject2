/*
  ==============================================================================

    ReverbData.cpp
    Created: 5 Apr 2024 5:42:39pm
    Author:  George Harrison

  ==============================================================================
*/

#include "ReverbData.h"

void ReverbData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    reverb.reset();
    reverb.prepare(spec);
    isPrepared = true;
}

void ReverbData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float>block{buffer};
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
    reverb.process(context);
}

void ReverbData::updateParameters(const juce::NamedValueSet& paramValues)
{
    reverbParams.roomSize = static_cast<float>(paramValues["ROOMSIZE"]);
    reverbParams.wetLevel = static_cast<float>(paramValues["REVERBMIX"]);
    reverbParams.dryLevel = 1.0f - reverbParams.wetLevel;
    reverb.setParameters(reverbParams);
}

void ReverbData::reset()
{
    reverb.reset();
}

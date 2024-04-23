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
    reverb.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    reverb.prepare(spec);
    
    isPrepared = true;
}

void ReverbData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> block { buffer };
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
    reverb.process(context);
}

void ReverbData::updateParameters(const float roomSize, const float reverbMix)
{
    reverbParams.roomSize = roomSize;
    reverbParams.wetLevel = reverbMix;
    reverbParams.dryLevel = 1.0f - reverbMix;
    reverb.setParameters(reverbParams);
}

void ReverbData::reset()
{
    reverb.reset();
}

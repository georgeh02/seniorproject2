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
    mixer.prepare(spec);
    
    isPrepared = true;
}

void ReverbData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    //auto block = juce::dsp::AudioBlock<float>(buffer);
    juce::dsp::AudioBlock<float> block { buffer };
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    //const auto& input = buffer.getInputBlock();
    //const auto& output = context.getOutputBlock();

    //mixer.pushDrySamples(block);

    reverb.process(context);

    //mixer.mixWetSamples(block);
}

void ReverbData::updateParameters(const float roomSize, const float reverbMix)
{
    reverbParams.roomSize = roomSize;
    reverbParams.wetLevel = reverbMix;
    reverbParams.dryLevel = 1.0f - reverbMix;
    //reverbParams.wetLevel = reverbMix;
    reverb.setParameters(reverbParams);
    //mixer.setWetMixProportion(reverbMix);
}

void ReverbData::reset()
{
    reverb.reset();
}

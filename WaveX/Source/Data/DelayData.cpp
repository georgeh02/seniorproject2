/*
  ==============================================================================

    DelayData.cpp
    Created: 3 Apr 2024 10:58:34am
    Author:  George Harrison

  ==============================================================================
*/

#include "DelayData.h"

void DelayData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    delay.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    delay.prepare(spec);
    
    //std::fill(lastDelayOutput.begin(), lastDelayOutput.end(), 0.0f); i think this is for feedback param
    //std::fill(delayValue.begin(), delayValue.end(), 999);
    isPrepared = true;
}

void DelayData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    const auto numChannels = buffer.getNumChannels();

    auto block = juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(0, (size_t) numChannels);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);

    const auto& input = context.getInputBlock();
    const auto& output = context.getOutputBlock();

    for (size_t channel = 0; channel < numChannels; ++channel)
    {
        auto* samplesIn = input.getChannelPointer(channel);
        auto* samplesOut = output.getChannelPointer(channel);

        for (size_t sample = 0; sample<input.getNumSamples(); ++sample)
        {
            //auto input = samplesIn[sample] - lastDelayOutput[channel];
            auto input = samplesIn[sample];
            delay.pushSample((int)channel, input);
            samplesOut[sample] = delay.popSample((int)channel);

            //lastDelayOutput[channel] = samplesOut[sample] * 0.99;
        }
    }

}

void DelayData::updateParameters(const float delayTime, double sampleRate)
{
    delay.setDelay(delayTime / 1000.0f * sampleRate);
}

void DelayData::reset()
{
    delay.reset();
}

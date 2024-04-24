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
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    this->sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    delay.reset();
    delay.prepare(spec);
    mixer.prepare(spec);
        
    for (auto& volume:delayFeedbackVolume)
        volume.reset(spec.sampleRate, 0.05);
    
    std::fill(lastDelayOutput.begin(), lastDelayOutput.end(), 0.0f); //initialize delay buffer
    
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

    mixer.pushDrySamples (input);
    
    for (size_t channel = 0; channel < numChannels; ++channel)
    {
        auto* samplesIn = input.getChannelPointer(channel);
        auto* samplesOut = output.getChannelPointer(channel);

        for (size_t sample = 0; sample<input.getNumSamples(); ++sample)
        {
            auto input = samplesIn[sample] - lastDelayOutput[channel];
            delay.pushSample((int)channel, input);
            samplesOut[sample] = delay.popSample((int)channel);
            lastDelayOutput[channel] = samplesOut[sample] * delayFeedbackVolume[channel].getNextValue();
        }
    }
    
    mixer.mixWetSamples (output);
}

void DelayData::updateParameters(const juce::NamedValueSet& paramValues)
{
    delay.setDelay(static_cast<float>(paramValues["DELAYTIME"]) / 1000.0f * sampleRate);
    
    const auto feedbackGain = juce::Decibels::decibelsToGain(static_cast<float>(paramValues["FEEDBACK"]), -50.0f);
    
    mixer.setWetMixProportion(static_cast<float>(paramValues["DELAYMIX"]) * 0.5f);
    
    for (auto& volume:delayFeedbackVolume)
        volume.setTargetValue(feedbackGain);
}

void DelayData::reset()
{
    delay.reset();
}

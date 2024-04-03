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
    
    isPrepared = true;
}

void DelayData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> block {buffer};
    //delay.process(juce::dsp::ProcessContextReplacing<float>{block});
    
    for (int ch = 0; ch < block.getNumChannels(); ++ch)
    {
        float* data = block.getChannelPointer(ch);
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            delay.pushSample(ch, data[sample]);
        }
    }
    
}

void DelayData::updateParameters(const float delayTime)
{
    delay.setDelay(delayTime);
}

void DelayData::reset()
{
    delay.reset();
}

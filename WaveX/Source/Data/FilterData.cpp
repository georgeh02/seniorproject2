/*
  ==============================================================================

    FilterData.cpp
    Created: 2 Apr 2024 1:14:21pm
    Author:  George Harrison

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    filter.reset();
    filter.prepare(spec);
    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float>block{buffer};
    filter.process(juce::dsp::ProcessContextReplacing<float>{block});
}

void FilterData::updateParameters(const juce::NamedValueSet& paramValues)
{
    switch (static_cast<int>(paramValues["FILTERTYPE"])) {
        case 0:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
            
        case 1:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
            
        case 2:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
    }
    
    filter.setCutoffFrequency(static_cast<float>(paramValues["FILTERFREQ"]));
    filter.setResonance(static_cast<float>(paramValues["FILTERRES"]));
}

void FilterData::reset()
{
    filter.reset();
}

/*
  ==============================================================================

    ReverbData.h
    Created: 5 Apr 2024 5:42:39pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ComponentBase.h"

class ReverbData : public ComponentBase
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const juce::NamedValueSet& paramValues) override;
    void reset();
    
private:
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParams;
    bool isPrepared{false};
};

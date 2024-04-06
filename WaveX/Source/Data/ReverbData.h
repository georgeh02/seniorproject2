/*
  ==============================================================================

    ReverbData.h
    Created: 5 Apr 2024 5:42:39pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ReverbData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const float roomSize, const float reverbMix);
    void reset();
    
private:
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParams;
    juce::dsp::DryWetMixer<float> mixer;
    
    bool isPrepared{false};
};

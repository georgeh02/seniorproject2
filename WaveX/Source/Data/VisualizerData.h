/*
  ==============================================================================

    VisualizerData.h
    Created: 5 Apr 2024 4:02:43pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class VisualizerData
{
public:
//    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int repaintRate, const int bufferSize);
//    void reset();
    
private:
    juce::AudioVisualiserComponent visualizer{1};
    bool isPrepared{false};
};

/*
  ==============================================================================

    VisualizerData.cpp
    Created: 5 Apr 2024 4:02:43pm
    Author:  George Harrison

  ==============================================================================
*/

#include "VisualizerData.h"

void VisualizerData::updateParameters(const int repaintRate, const int bufferSize)
{
    visualizer.setRepaintRate(repaintRate);
    visualizer.setBufferSize(bufferSize);
    visualizer.setColours(juce::Colours::darkred, juce::Colours::whitesmoke);
}

void VisualizerData::process(juce::AudioBuffer<float>& buffer)
{
    visualizer.pushBuffer(buffer);
}

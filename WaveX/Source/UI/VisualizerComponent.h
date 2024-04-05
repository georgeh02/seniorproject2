/*
  ==============================================================================

    VisualizerComponent.h
    Created: 5 Apr 2024 4:02:11pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VisualizerComponent  : public juce::Component
{
public:
    VisualizerComponent();
    ~VisualizerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualizerComponent)
};

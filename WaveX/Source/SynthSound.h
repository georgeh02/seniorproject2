/*
  ==============================================================================

    SynthSound.h
    Created: 3 Mar 2024 4:21:33pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound: public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override {return true;}
    bool appliesToChannel(int midiChannel) override {return true;}
};

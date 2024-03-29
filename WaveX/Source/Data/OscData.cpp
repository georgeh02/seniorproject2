/*
  ==============================================================================

    OscData.cpp
    Created: 18 Mar 2024 10:54:13pm
    Author:  George Harrison

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
    oscGain.prepare(spec);
}

void OscData::setWaveType(const int choice)
{
    switch (choice) {
        case 0:
            // Sine
            initialise([](float x) {return std::sin(x);});
            break;
            
        case 1:
            // Saw
            initialise([](float x) {return x / juce::MathConstants<float>::pi;});
            break;
        
        case 2:
            // Square
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void OscData::setOscGain(float gain)
{
    oscGain.setGainLinear(gain);
}

void OscData::getNextAudioBlock(juce::dsp::ProcessContextReplacing<float>& context)
{
    process(context);
    oscGain.process(context);
}

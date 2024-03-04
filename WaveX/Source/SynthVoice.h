/*
  ==============================================================================

    SynthVoice.h
    Created: 3 Mar 2024 4:21:06pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice: public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int StartSample, int numSamples) override;
    
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
    juce::dsp::Oscillator<float> osc { [](float x) {return x / juce::MathConstants<float>::pi;}};
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};
    
    // return std::sin(x);
    // return x / juce::MathConstants<float>::pi; // Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f; // Square Wave
};

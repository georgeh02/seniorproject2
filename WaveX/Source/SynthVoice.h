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
#include "Data/AdsrData.h"
#include "Data/OscData.h"

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
    
    void update(const float attack, const float decay, const float sustain, const float release);
    OscData& getOscillator(int index){ return oscillators[index]; };
    
private:
    AdsrData adsr;

    std::array<OscData, 2> oscillators;
    
    //juce::dsp::Gain<float> globalGain;
    bool isPrepared {false};
    

};

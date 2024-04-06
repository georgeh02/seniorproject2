/*
  ==============================================================================

    SynthVoice.cpp
    Created: 3 Mar 2024 4:21:06pm
    Author:  George Harrison

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    oscillators[0].setWaveFrequency(midiNoteNumber);
    oscillators[1].setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    oscillators[0].prepareToPlay(spec);
    oscillators[1].prepareToPlay(spec);
//    globalGain.prepare(spec);
//    globalGain.setGainLinear(0.03f);
    
    isPrepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    if (!isVoiceActive()) return;
    
    // Separate context for each osc ??
    auto audioBlock = juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock(startSample, numSamples);
    juce::dsp::ProcessContextReplacing<float> context1(audioBlock);
    juce::dsp::ProcessContextReplacing<float> context2(audioBlock);
    
    oscillators[0].getNextAudioBlock(context1);
    oscillators[1].getNextAudioBlock(context1);
    
//    globalGain.process(context);
    
    //GPT method
//    for (int sample = 0; sample < numSamples; ++sample)
//    {
//        float osc1Sample = audioBlock.getChannelPointer(0)[sample];
//        float osc2Sample = audioBlock.getChannelPointer(1)[sample];
//
//        // Mix the outputs of both oscillators (you can adjust the scaling factor as needed)
//        float mixedSample = (osc1Sample + osc2Sample) * 0.5f;
//
//        // Write the mixed sample to the output buffer
//        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
//        {
//            outputBuffer.getWritePointer(channel)[startSample + sample] += mixedSample;
//        }
//    }
    
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    
    if (!adsr.isActive())
        clearCurrentNote();
    
}

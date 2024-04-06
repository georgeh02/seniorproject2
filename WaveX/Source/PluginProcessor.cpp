/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveXAudioProcessor::WaveXAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new SynthSound());
    //synth.addVoice(new SynthVoice());
    
    for (int i = 0; i < 5; i++)
    {
        synth.addVoice(new SynthVoice());
    }
    
    visualizer.setRepaintRate(30);
    visualizer.setBufferSize(512);
    //visualizer.updateParameters(30, 512);
}

WaveXAudioProcessor::~WaveXAudioProcessor()
{
}

//==============================================================================
const juce::String WaveXAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveXAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveXAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveXAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveXAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveXAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveXAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveXAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WaveXAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveXAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WaveXAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i=0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
    filter.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    delay.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    reverb.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void WaveXAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveXAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WaveXAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for(int i=0; i<synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // Osc controls
            // ADSR
            // LFO
            
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            
            auto& osc1WaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& osc2WaveChoice = *apvts.getRawParameterValue("OSC2WAVETYPE");
            
            auto& osc1Mix = *apvts.getRawParameterValue("OSC1MIX");
            auto& osc2Mix = *apvts.getRawParameterValue("OSC2MIX");
            
            voice->getOscillator(0).setWaveType(osc1WaveChoice);
            voice->getOscillator(1).setWaveType(osc2WaveChoice);
            voice->getOscillator(0).setOscMix(osc1Mix);
            voice->getOscillator(1).setOscMix(osc2Mix);
            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
    auto& freq = *apvts.getRawParameterValue("FILTERFREQ");
    auto& resonance = *apvts.getRawParameterValue("FILTERRES");

    filter.updateParameters(filterType, freq, resonance);
    filter.process(buffer);

    auto& delayTime = *apvts.getRawParameterValue("DELAYTIME");
    auto& feedback = *apvts.getRawParameterValue("FEEDBACK");
    auto& delayMix = *apvts.getRawParameterValue("DELAYMIX");

    delay.updateParameters(delayTime, feedback, delayMix, getSampleRate());
    delay.process(buffer);
    
    auto& roomSize = *apvts.getRawParameterValue("ROOMSIZE");
    auto& reverbMix = *apvts.getRawParameterValue("DELAYMIX");

    reverb.updateParameters(roomSize, reverbMix);
    reverb.process(buffer);
    
    //visualizer.process(buffer);
    visualizer.pushBuffer(buffer);
}

//==============================================================================
bool WaveXAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WaveXAudioProcessor::createEditor()
{
    return new WaveXAudioProcessorEditor (*this);
}

//==============================================================================
void WaveXAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WaveXAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveXAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout WaveXAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // ADSR
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "ATTACK",  1 }, "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.01f}, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "DECAY",  1 }, "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.01f}, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "SUSTAIN",  1 }, "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.01f}, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "RELEASE",  1 }, "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.01f}, 0.4f));

    
    // OSC CONTROLS
    params.push_back (std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"OSC1WAVETYPE", 1}, "Osc 1 Wave Type", juce::StringArray{"Sine", "Saw", "Square"}, 0));
    
    params.push_back (std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"OSC2WAVETYPE", 1}, "Osc 1 Wave Type", juce::StringArray{"Sine", "Saw", "Square"}, 1));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "OSC1MIX",  1 }, "Osc 1 Mix", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.5f));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "OSC2MIX",  1 }, "Osc 2 Mix", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.5f));
    
    // FILTER
    params.push_back (std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"FILTERTYPE", 1}, "Filter Type", juce::StringArray{"Low Pass", "Band-Pass", "High-Pass"}, 0));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "FILTERFREQ",  1 }, "Filter Frequency", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f}, 20000.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "FILTERRES",  1 }, "Filter Resonance", juce::NormalisableRange<float> { 0.1f, 10.0f, 0.1f}, 1.0f));
    
    // DELAY
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "DELAYTIME",  1 }, "Delay Time", juce::NormalisableRange<float> { 0.0f, 1000.0f, 1.0f}, 500.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "FEEDBACK",  1 }, "Feedback", juce::NormalisableRange<float> { -100.0f, 0.0f, 1.0f}, -100.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "DELAYMIX",  1 }, "Delay Mix", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.0f));
    
    // REVERB
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "ROOMSIZE",  1 }, "Room Size", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f}, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "REVERBMIX",  1 }, "Reverb Mix", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.0f));
    
    return { params.begin(), params.end() };
}

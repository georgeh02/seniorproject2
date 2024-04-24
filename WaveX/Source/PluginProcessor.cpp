/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"

//==============================================================================
WaveXAudioProcessor::WaveXAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : foleys::MagicProcessor (juce::AudioProcessor::BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams())
#endif
{

    magicState.setGuiValueTree(BinaryData::magic_xml, BinaryData::magic_xmlSize); //setting GUI
    oscilloscope = magicState.createAndAddObject<foleys::MagicOscilloscope>("waveform");
    synth.addSound(new SynthSound());

    for (int i = 0; i < numVoices; i++)
    {
        synth.addVoice(new SynthVoice());
    }
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
    limiter.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    oscilloscope->prepareToPlay(sampleRate, samplesPerBlock);
}

void WaveXAudioProcessor::releaseResources()
{

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

    magicState.processMidiBuffer (midiMessages, buffer.getNumSamples(), true);
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for(int i=0; i<synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            updateVoiceParameters(voice, {"ATTACK", "DECAY", "SUSTAIN", "RELEASE", "OSC1WAVETYPE", "OSC2WAVETYPE", "OSC1MIX", "OSC2MIX"});
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    updateParameters(filter, {"FILTERTYPE", "FILTERFREQ", "FILTERRES"});
    filter.process(buffer);

    updateParameters(delay, {"DELAYTIME", "FEEDBACK", "DELAYMIX"});
    delay.process(buffer);
        
    updateParameters(reverb, {"ROOMSIZE", "REVERBMIX"});
    reverb.process(buffer);
    
    limiter.updateParameters({{"THRESHOLD", 0.0f}, {"RELEASE", 0.0f}}); //safety limiter ensures volume isn't too loud
    limiter.process(buffer);
    
    oscilloscope->pushSamples(buffer);
}

//==============================================================================
void WaveXAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void WaveXAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

//==============================================================================
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
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "FEEDBACK",  1 }, "Feedback", juce::NormalisableRange<float> { -50.0, 0.0f, 1.0f}, -50.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "DELAYMIX",  1 }, "Delay Mix", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.0f));
    
    // REVERB
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "ROOMSIZE",  1 }, "Room Size", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f}, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "REVERBMIX",  1 }, "Reverb Mix", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f}, 0.0f));
    
    return { params.begin(), params.end() };
}

void WaveXAudioProcessor::updateParameters(ComponentBase& component, const std::vector<std::string>& params)
{
    juce::NamedValueSet paramValues;
    
    for (const std::string& param : params)
        {
            auto& paramValue = *apvts.getRawParameterValue(param);
            paramValues.set(juce::Identifier(param), juce::var(paramValue));
        }
    
    component.updateParameters(paramValues);
}

void WaveXAudioProcessor::updateVoiceParameters(SynthVoice* voice, const std::vector<std::string>& params)
{
    juce::NamedValueSet paramValues;
    
    for (const std::string& param : params)
        {
            auto& paramValue = *apvts.getRawParameterValue(param);
            paramValues.set(juce::Identifier(param), juce::var(paramValue.load()));
        }
    
    voice->update(paramValues);
}

/*
  ==============================================================================

    ReverbComponent.h
    Created: 5 Apr 2024 5:58:25pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String roomSizeId, juce::String reverbMixId);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider roomSize;
    juce::Slider reverbMix;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> roomSizeAttachment;
    std::unique_ptr<Attachment> reverbMixAttachment;

    juce::Label roomSizeLabel{"Room Size", "Room Size"};
    juce::Label reverbMixLabel{"Reverb Mix", "Reverb Mix"};
    
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};

/*
  ==============================================================================

    DelayComponent.h
    Created: 5 Apr 2024 2:19:16pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DelayComponent  : public juce::Component
{
public:
    DelayComponent(juce::AudioProcessorValueTreeState& apvts, juce::String delayTimeId);
    ~DelayComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider delayTime;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> delayTimeAttachment;
    
    juce::Label delayTimeLabel{"Delay Time", "Delay Time"};
    
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};

/*
  ==============================================================================

    DelayComponent.cpp
    Created: 5 Apr 2024 2:19:16pm
    Author:  George Harrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayComponent.h"

//==============================================================================
DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& apvts, juce::String delayTimeId, juce::String feedbackId, juce::String delayMixId)
{
    GUIHelper helper;
    helper.setSliderWithLabel(delayTime, delayTimeLabel, apvts, delayTimeId, delayTimeAttachment, *this);
    helper.setSliderWithLabel(feedback, feedbackLabel, apvts, feedbackId, feedbackAttachment, *this);
    helper.setSliderWithLabel(delayMix, delayMixLabel, apvts, delayMixId, delayMixAttachment, *this);
}

DelayComponent::~DelayComponent()
{
}

void DelayComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::black);
    g.setFont(20.0f);
    g.drawText("Delay", labelSpace.withX(10), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 3.0f);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void DelayComponent::resized()
{
    const auto padding = 25;
    const auto boxHeight = 20;
    const auto bounds = getLocalBounds().reduced(padding);
    
    delayTime.setBounds(padding, padding * 3, bounds.getWidth()/3, bounds.getHeight()/2);
    delayTimeLabel.setBounds(delayTime.getX(), delayTime.getY()-padding, delayTime.getWidth(), boxHeight);
    
    feedback.setBounds(delayTimeLabel.getRight(), padding * 3, bounds.getWidth()/3, bounds.getHeight()/2);
    feedbackLabel.setBounds(feedback.getX(), feedback.getY()-padding, feedback.getWidth(), boxHeight);
    
    delayMix.setBounds(feedbackLabel.getRight(), padding * 3, bounds.getWidth()/3, bounds.getHeight()/2);
    delayMixLabel.setBounds(delayMix.getX(), delayMix.getY()-padding, delayMix.getWidth(), boxHeight);
}

/*
  ==============================================================================

    ComponentBase.h
    Created: 23 Apr 2024 5:47:24pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ComponentBase
{
public:
    virtual ~ComponentBase() {};
    virtual void updateParameters(const juce::NamedValueSet& paramValues) = 0;
};

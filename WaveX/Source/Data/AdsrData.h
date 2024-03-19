/*
  ==============================================================================

    AdsrData.h
    Created: 18 Mar 2024 10:15:42pm
    Author:  George Harrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrParams;
};

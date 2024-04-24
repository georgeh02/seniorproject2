/*
  ==============================================================================

    AdsrData.cpp
    Created: 18 Mar 2024 10:15:42pm
    Author:  George Harrison

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    setParameters(adsrParams);
};

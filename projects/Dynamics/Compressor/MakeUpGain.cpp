#include "MakeUpGain.h"

namespace DSP {

MakeUpGain::MakeUpGain()
{
}

MakeUpGain::~MakeUpGain()
{
}

void MakeUpGain::process(float *const *output, const float *const *input, float gain, unsigned int numChannels, unsigned int numSamples)
{
    for (unsigned int ch = 0; ch < numChannels; ++ch)
    {
        for (unsigned int n = 0; n < numSamples; ++n)
        {
            output[ch][n] = gain * input[ch][n];
        }
    }
}

}

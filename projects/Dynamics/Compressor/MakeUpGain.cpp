#include "MakeUpGain.h"

namespace DSP {

MakeUpGain::MakeUpGain()
{
    la2aMakeUp[0].load_parameters(la2aMakeUpParameters.params);
    la2aMakeUp[1].load_parameters(la2aMakeUpParameters.params);
}

MakeUpGain::~MakeUpGain()
{
}

void MakeUpGain::prepare(unsigned int numChannels, unsigned int samplesPerBlock)
{
    la2aMakeUp[0].reset_state();
    la2aMakeUp[1].reset_state();
    warmthInBuffer.setSize(samplesPerBlock, INPUT_SIZE);
    warmthInBuffer.clear();
    warmthOutBuffer.setSize(samplesPerBlock, OUTPUT_SIZE);
    warmthOutBuffer.clear();
}

void MakeUpGain::setLA2AWarmth(float newWarmth)
{
    warmth = newWarmth;
}

void MakeUpGain::process(float *const *output, const float *const *input, float gain, unsigned int numChannels, unsigned int numSamples)
{
    const float * const * nn_input_read_ptr = warmthInBuffer.getArrayOfReadPointers();
    float * const * nn_input_write_ptr = warmthInBuffer.getArrayOfWritePointers();
    const float * const * nn_output_read_ptr = warmthOutBuffer.getArrayOfReadPointers();
    float * const * nn_output_write_ptr = warmthOutBuffer.getArrayOfWritePointers();

    for (unsigned int ch = 0; ch < numChannels; ++ch)
    {
        for (unsigned int n = 0; n < numSamples; ++n)
        {
            nn_input_write_ptr[n][0] = input[ch][n];
        }
        la2aMakeUp[ch].process(nn_output_write_ptr, nn_input_read_ptr, numSamples);
        for (unsigned int n = 0; n < numSamples; ++n)
        {
            output[ch][n] = gain * input[ch][n] + warmth * nn_output_read_ptr[n][0];
        }
    }
}

}

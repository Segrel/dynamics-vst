#pragma once

namespace DSP {

class MakeUpGain {
public:
    MakeUpGain();
    ~MakeUpGain();

    MakeUpGain(const MakeUpGain&) = delete;
    MakeUpGain(MakeUpGain&&) = delete;
    const MakeUpGain& operator=(const MakeUpGain&) = delete;
    const MakeUpGain& operator=(MakeUpGain&&) = delete;

    void process(float* const* output, const float* const* input, float gain, unsigned int numChannels, unsigned int numSamples);

private:

};

}

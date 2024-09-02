#pragma once

namespace DSP {

class GainSmoother {
public:
    GainSmoother();
    ~GainSmoother();

    GainSmoother(const GainSmoother&) = delete;
    GainSmoother(GainSmoother&&) = delete;
    const GainSmoother& operator=(const GainSmoother&) = delete;
    const GainSmoother& operator=(GainSmoother&&) = delete;

    void prepare(double sampleRate);
    void setAttackTime(float newAttackTime);
    void setReleaseTime(float newReleaseTime);
    float smooth(float targetGain);

private:
    double sampleRate { 48000.0 };
    float attackTime { 100.f };
    float releaseTime { 100.f };

    float attackCoeff { 0.0f };
    float releaseCoeff { 0.0f };
    float smoothedLevel { 0.f };
};

}

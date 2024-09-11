#pragma once

#include <cstddef>
#include <cmath>

#include "LA2AMakeUpModel.h"


template <unsigned int INPUT_SIZE, unsigned int OUTPUT_SIZE, unsigned int HIDDEN_SIZE>
class LA2AMakeUp
{
public:
    LA2AMakeUp()
    {
        memset(weight_ih_r, 0, sizeof(weight_ih_r));
        memset(weight_ih_z, 0, sizeof(weight_ih_z));
        memset(weight_ih_n, 0, sizeof(weight_ih_n));
        memset(bias_ih_n, 0, sizeof(bias_ih_n));

        memset(weight_hh_r, 0, sizeof(weight_hh_r));
        memset(weight_hh_z, 0, sizeof(weight_hh_z));
        memset(weight_hh_n, 0, sizeof(weight_hh_n));
        memset(bias_hh_n, 0, sizeof(bias_hh_n));
        memset(bias_r, 0, sizeof(bias_r));
        memset(bias_z, 0, sizeof(bias_z));

        memset(weight_output, 0, sizeof(weight_output));
        memset(bias_output, 0, sizeof(bias_output));

        reset_state();
    }

    float sigmoid(float x) const
    {
        return 1.f / (1.f + std::expf(-x));
    }

    void process(float * const * output, const float * const * input, unsigned int numSamples)
    {
        // This is mostly from Valtteri Kallinen's code in the course Slack.
        // No fast math tricks to keep the code simple. Still plenty fast on a modern laptop computer.
        for (size_t n = 0; n < numSamples; ++n) {
            for (size_t i = 0; i < HIDDEN_SIZE; ++i) {
                float r_gate = bias_r[i];
                float z_gate = bias_z[i];
                float n_gate = bias_ih_n[i];

                for (size_t j = 0; j < INPUT_SIZE; ++j) {
                    r_gate = std::fma(weight_ih_r[i][j], input[n][j], r_gate);
                    z_gate = std::fma(weight_ih_z[i][j], input[n][j], z_gate);
                    n_gate = std::fma(weight_ih_n[i][j], input[n][j], n_gate);
                }

                float n_hidden = bias_hh_n[i];
                for (size_t j = 0; j < HIDDEN_SIZE; ++j) {
                    r_gate = std::fma(weight_hh_r[i][j], old_state[j], r_gate);
                    z_gate = std::fma(weight_hh_z[i][j], old_state[j], z_gate);
                    n_hidden = std::fma(weight_hh_n[i][j], old_state[j], n_hidden);
                }

                r_gate = sigmoid(r_gate);
                z_gate = sigmoid(z_gate);

                n_gate = std::fma(n_hidden, r_gate, n_gate);
                n_gate = std::tanhf(n_gate);

                new_state[i] = std::fma(z_gate, (old_state[i] - n_gate), n_gate);
            }

            memcpy(output[n], bias_output, sizeof(bias_output));
            for (size_t i = 0; i < OUTPUT_SIZE; ++i) {
                for (size_t j = 0; j < HIDDEN_SIZE; ++j) {
                    output[n][i] = std::fma(weight_output[i][j], new_state[j], output[n][i]);
                }
            }

            std::swap(new_state, old_state);
        }
    }

    void load_parameters(LA2AMakeUpModel<INPUT_SIZE, OUTPUT_SIZE, HIDDEN_SIZE> params)
    {
        memcpy(weight_ih_r, params.weight_ih_r, sizeof(weight_ih_r));
        memcpy(weight_ih_z, params.weight_ih_z, sizeof(weight_ih_z));
        memcpy(weight_ih_n, params.weight_ih_n, sizeof(weight_ih_n));

        memcpy(bias_ih_n, params.bias_ih_n, sizeof(bias_ih_n));
        memcpy(bias_hh_n, params.bias_hh_n, sizeof(bias_hh_n));
        for (size_t i = 0; i < HIDDEN_SIZE; ++i) {
            bias_r[i] = params.bias_ih_r[i] + params.bias_hh_r[i];
            bias_z[i] = params.bias_ih_z[i] + params.bias_hh_z[i];
        }

        memcpy(weight_hh_r, params.weight_hh_r, sizeof(weight_hh_r));
        memcpy(weight_hh_z, params.weight_hh_z, sizeof(weight_hh_z));
        memcpy(weight_hh_n, params.weight_hh_n, sizeof(weight_hh_n));

        memcpy(weight_output, params.weight_output, sizeof(weight_output));
        memcpy(bias_output, params.bias_output, sizeof(bias_output));
    }

    void reset_state()
    {
        memset(new_state, 0, sizeof(new_state));
        memset(old_state, 0, sizeof(old_state));
    }

private:
    // model parameters
    float weight_ih_r[HIDDEN_SIZE][INPUT_SIZE];
    float weight_ih_z[HIDDEN_SIZE][INPUT_SIZE];
    float weight_ih_n[HIDDEN_SIZE][INPUT_SIZE];
    float bias_ih_n[HIDDEN_SIZE];

    float weight_hh_r[HIDDEN_SIZE][HIDDEN_SIZE];
    float weight_hh_z[HIDDEN_SIZE][HIDDEN_SIZE];
    float weight_hh_n[HIDDEN_SIZE][HIDDEN_SIZE];
    float bias_hh_n[HIDDEN_SIZE];
    float bias_r[HIDDEN_SIZE];
    float bias_z[HIDDEN_SIZE];

    float weight_output[OUTPUT_SIZE][HIDDEN_SIZE];
    float bias_output[OUTPUT_SIZE];

    // gru state
    float new_state[HIDDEN_SIZE];
    float old_state[HIDDEN_SIZE];
};

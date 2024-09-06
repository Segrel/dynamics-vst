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

        memset(bias_ih_r, 0, sizeof(bias_ih_r));
        memset(bias_ih_z, 0, sizeof(bias_ih_z));
        memset(bias_ih_n, 0, sizeof(bias_ih_n));

        memset(weight_hh_r, 0, sizeof(weight_hh_r));
        memset(weight_hh_z, 0, sizeof(weight_hh_z));
        memset(weight_hh_n, 0, sizeof(weight_hh_n));

        memset(bias_hh_r, 0, sizeof(bias_hh_r));
        memset(bias_hh_z, 0, sizeof(bias_hh_z));
        memset(bias_hh_n, 0, sizeof(bias_hh_n));

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
        float r_gate[HIDDEN_SIZE];
        float z_gate[HIDDEN_SIZE];
        float n_gate[HIDDEN_SIZE];
        float n_hidden[HIDDEN_SIZE];

        for (unsigned int n = 0; n < numSamples; ++n)
        {
            // Compute r gate
            for (unsigned int i = 0; i < HIDDEN_SIZE; ++i)
            {
                // Initialise with bias_ih
                r_gate[i] = bias_ih_r[i];
                // Implement matrix-vector multiply with weight_ih and the input signal
                for (unsigned int j = 0; j < INPUT_SIZE; ++j)
                {
                    r_gate[i] += weight_ih_r[i][j] * input[n][j];
                }
                // Add bias_hh
                r_gate[i] += bias_hh_r[i];
                // Implement matrix-vector multiply with weight_hh and the state signal
                for (unsigned int j = 0; j < HIDDEN_SIZE; ++j)
                {
                    r_gate[i] += weight_hh_r[i][j] * state[j];
                }
                // Apply sigmoid activation function
                r_gate[i] = sigmoid(r_gate[i]);
            }

            // Compute z gate
            for (unsigned int i = 0; i < HIDDEN_SIZE; ++i)
            {
                // Initialise with bias_ih
                z_gate[i] = bias_ih_z[i];
                // Implement matrix-vector multiply with weight_ih and the input signal
                for (unsigned int j = 0; j < INPUT_SIZE; ++j)
                {
                    z_gate[i] += weight_ih_z[i][j] * input[n][j];
                }
                // Add bias_hh
                z_gate[i] += bias_hh_z[i];
                // Implement matrix-vector multiply with weight_hh and the state signal
                for (unsigned int j = 0; j < HIDDEN_SIZE; ++j)
                {
                    z_gate[i] += weight_hh_z[i][j] * state[j];
                }
                // Apply sigmoid activation function
                z_gate[i] = sigmoid(z_gate[i]);
            }

            // Compute n gate
            for (unsigned int i = 0; i < HIDDEN_SIZE; ++i)
            {
                // Initialise with bias_n
                n_gate[i] = bias_ih_n[i];
                // Matrix-vector multiply with n weights and input
                for (unsigned int j = 0; j < INPUT_SIZE; ++j) {
                    n_gate[i] += weight_ih_n[i][j] * input[n][j];
                }
                // Initialise with bias_hh
                n_hidden[i] = bias_hh_n[i];
                // Matrix-vector multiply with n weights and state
                for (unsigned int j = 0; j < HIDDEN_SIZE; ++j) {
                    n_hidden[i] += weight_hh_n[i][j] * state[j];
                }
                // Multiply n_hidden by r gate and add it to n gate
                n_hidden[i] *= r_gate[i];
                n_gate[i] += n_hidden[i];
                // Apply tanh activation
                n_gate[i] = std::tanhf(n_gate[i]);
            }

            // Compute hidden state candidate
            for (unsigned int i = 0; i < HIDDEN_SIZE; ++i)
            {
                state[i] = (1.f - z_gate[i]) * n_gate[i] + z_gate[i] * state[i];
            }

            // Affine output
            memcpy(output[n], bias_output, sizeof(bias_output));
            for (unsigned int i = 0; i < OUTPUT_SIZE; ++i)
            {
                for (unsigned int j = 0; j < HIDDEN_SIZE; ++j)
                {
                    output[n][i] += weight_output[i][j] * state[j];
                }
            }
        }
    }

    void load_parameters(LA2AMakeUpModel<INPUT_SIZE, OUTPUT_SIZE, HIDDEN_SIZE> params)
    {
        memcpy(weight_ih_r, params.weight_ih_r, sizeof(weight_ih_r));
        memcpy(weight_ih_z, params.weight_ih_z, sizeof(weight_ih_z));
        memcpy(weight_ih_n, params.weight_ih_n, sizeof(weight_ih_n));

        memcpy(bias_ih_r, params.bias_ih_r, sizeof(bias_ih_r));
        memcpy(bias_ih_z, params.bias_ih_z, sizeof(bias_ih_z));
        memcpy(bias_ih_n, params.bias_ih_n, sizeof(bias_ih_n));

        memcpy(weight_hh_r, params.weight_hh_r, sizeof(weight_hh_r));
        memcpy(weight_hh_z, params.weight_hh_z, sizeof(weight_hh_z));
        memcpy(weight_hh_n, params.weight_hh_n, sizeof(weight_hh_n));

        memcpy(bias_hh_r, params.bias_hh_r, sizeof(bias_hh_r));
        memcpy(bias_hh_z, params.bias_hh_z, sizeof(bias_hh_z));
        memcpy(bias_hh_n, params.bias_hh_n, sizeof(bias_hh_n));

        memcpy(weight_output, params.weight_output, sizeof(weight_output));
        memcpy(bias_output, params.bias_output, sizeof(bias_output));
    }

    void reset_state()
    {
        memset(state, 0, sizeof(state));
    }

private:
    // model parameters
    float weight_ih_r[HIDDEN_SIZE][INPUT_SIZE];
    float weight_ih_z[HIDDEN_SIZE][INPUT_SIZE];
    float weight_ih_n[HIDDEN_SIZE][INPUT_SIZE];

    float bias_ih_r[HIDDEN_SIZE];
    float bias_ih_z[HIDDEN_SIZE];
    float bias_ih_n[HIDDEN_SIZE];

    float weight_hh_r[HIDDEN_SIZE][HIDDEN_SIZE];
    float weight_hh_z[HIDDEN_SIZE][HIDDEN_SIZE];
    float weight_hh_n[HIDDEN_SIZE][HIDDEN_SIZE];

    float bias_hh_r[HIDDEN_SIZE];
    float bias_hh_z[HIDDEN_SIZE];
    float bias_hh_n[HIDDEN_SIZE];

    float weight_output[OUTPUT_SIZE][HIDDEN_SIZE];
    float bias_output[OUTPUT_SIZE];

    // gru state
    float state[HIDDEN_SIZE];
};

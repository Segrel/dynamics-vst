#pragma once

#include <cstddef>
#include <cmath>
#include <cstring>

#include "LA2AParameters.h"

template <size_t INPUT_SIZE, size_t OUTPUT_SIZE, size_t HIDDEN_SIZE, size_t NUM_LAYERS>
class LA2AComputer
{
public:
    static_assert(NUM_LAYERS > 2, "Number of layers must be greater than 2");

    LA2AComputer()
    {
        memset(weight_in, 0, sizeof(weight_in));
        memset(bias_in, 0, sizeof(bias_in));

        memset(weight_hidden, 0, sizeof(weight_hidden));
        memset(bias_hidden, 0, sizeof(bias_hidden));

        memset(weight_out, 0, sizeof(weight_out));
        memset(bias_out, 0, sizeof(bias_out));
    }
    
    float sigmoid(float x) const
    {
        return 1.f / (1.f + std::expf(-x));
    }

    void compute(float *output, const float* input)
    {
        float x[HIDDEN_SIZE];
        float y[HIDDEN_SIZE];

        // input layer
        // initialise input layer output with bias
        memcpy(y, bias_in, sizeof(bias_in));
        // matrix-vector multiply
        for (size_t i = 0; i < HIDDEN_SIZE; ++i)
        {
            for (size_t j = 0; j < INPUT_SIZE; ++j)
            {
                y[i] += weight_in[i][j] * input[j];
            }
        }

        // hidden layers
        for (size_t l = 0; l < NUM_LAYERS - 2; ++l)
        {
            std::swap(x, y);
            // initialise layer output with bias
            memcpy(y, bias_hidden[l], sizeof(bias_hidden[l]));
            // matrix vector multiply
            for (size_t i = 0; i < HIDDEN_SIZE; ++i)
            {
                for (size_t j = 0; j < HIDDEN_SIZE; ++j)
                {
                    y[i] += weight_hidden[l][i][j] * x[j];
                }
            }
            // hidden layer ReLU
            for (size_t i = 0; i < HIDDEN_SIZE; ++i)
            {
                y[i] = std::fmaxf(0.0f, y[i]);
            }
        }

        // output layer
        std::swap(x, y);
        // initialise layer output with bias
        memcpy(output, bias_out, sizeof(bias_out));
        for (size_t i = 0; i < OUTPUT_SIZE; ++i)
        {
            for (size_t j = 0; j < HIDDEN_SIZE; ++j)
            {
                output[i] += weight_out[i][j] * x[j];
            }
        }
        // apply sigmoid to output
        for (size_t i = 0; i < OUTPUT_SIZE; ++i)
        {
            output[i] = sigmoid(output[i]);
        }
    }

    void load_parameters(LA2AParameters<INPUT_SIZE, OUTPUT_SIZE, HIDDEN_SIZE, NUM_LAYERS> params)
    {
        memcpy(weight_in, params.weight_in, sizeof(weight_in));
        memcpy(bias_in, params.bias_in, sizeof(bias_in));

        memcpy(weight_hidden, params.weight_hidden, sizeof(weight_hidden));
        memcpy(bias_hidden, params.bias_hidden, sizeof(bias_hidden));

        memcpy(weight_out, params.weight_out, sizeof(weight_out));
        memcpy(bias_out, params.bias_out, sizeof(bias_out));
    }

private:
    float weight_in[HIDDEN_SIZE][INPUT_SIZE];
    float bias_in[HIDDEN_SIZE];

    float weight_hidden[NUM_LAYERS - 2][HIDDEN_SIZE][HIDDEN_SIZE];
    float bias_hidden[NUM_LAYERS - 2][HIDDEN_SIZE];

    float weight_out[OUTPUT_SIZE][HIDDEN_SIZE];
    float bias_out[OUTPUT_SIZE];
};

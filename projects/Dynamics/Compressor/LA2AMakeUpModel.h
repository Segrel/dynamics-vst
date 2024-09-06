#pragma once
#include <cstddef>


template <unsigned int INPUT_SIZE, unsigned int OUTPUT_SIZE, unsigned int HIDDEN_SIZE>
struct LA2AMakeUpModel
{
    float weight_ih_r[HIDDEN_SIZE * INPUT_SIZE];
    float weight_ih_z[HIDDEN_SIZE * INPUT_SIZE];
    float weight_ih_n[HIDDEN_SIZE * INPUT_SIZE];

    float bias_ih_r[HIDDEN_SIZE];
    float bias_ih_z[HIDDEN_SIZE];
    float bias_ih_n[HIDDEN_SIZE];

    float weight_hh_r[HIDDEN_SIZE * HIDDEN_SIZE];
    float weight_hh_z[HIDDEN_SIZE * HIDDEN_SIZE];
    float weight_hh_n[HIDDEN_SIZE * HIDDEN_SIZE];

    float bias_hh_r[HIDDEN_SIZE];
    float bias_hh_z[HIDDEN_SIZE];
    float bias_hh_n[HIDDEN_SIZE];

    float weight_output[OUTPUT_SIZE * HIDDEN_SIZE];
    float bias_output[OUTPUT_SIZE];
};

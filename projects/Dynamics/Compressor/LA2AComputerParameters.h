#pragma once

#include "LA2AComputerModel.h"

struct LA2AComputerParameters
{
    LA2AComputerParameters();

    static const size_t INPUT_SIZE = 1 ;
    static const size_t OUTPUT_SIZE = 3 ;
    static const size_t HIDDEN_SIZE = 20 ;
    static const size_t NUM_LAYERS = 4 ;

    LA2AComputerModel<INPUT_SIZE, OUTPUT_SIZE, HIDDEN_SIZE, NUM_LAYERS> params;
};

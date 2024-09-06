#pragma once

#include "LA2AMakeUpModel.h"

struct LA2AMakeUpParameters
{
    LA2AMakeUpParameters();

    static const unsigned int INPUT_SIZE = 1 ;
    static const unsigned int OUTPUT_SIZE = 1 ;
    static const unsigned int HIDDEN_SIZE = 8 ;

    LA2AMakeUpModel<INPUT_SIZE, OUTPUT_SIZE, HIDDEN_SIZE> params;
};

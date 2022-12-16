//
// Created by Jonathan Taylor on 4/21/22.
//

#include <math.h>
#include <string.h>
#include "modbus/util.h"
#include <stdlib.h>

uint32_t map(
        uint32_t value, uint32_t inputLow, uint32_t inputHigh,
        uint32_t outputLow, uint32_t outputHigh
)
{

    double slope = 1.0 * (outputHigh - outputLow) /
                   (1.0 * (inputHigh - inputLow));
    return lround(outputLow + round(slope * (value - inputLow)));
}

char * str_combine(const char * start, const char * end)
{
    const uint32_t len = strlen(start) + strlen(end);
    char * ret;
    ret = calloc(len + 1, sizeof(char));
    strncpy(ret, start, len + 1);
    strncat(ret, end, len);
    ret[len] = '\0';
    return ret;
}

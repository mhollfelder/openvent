/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <common/ErrorHandling.hpp>
#include <cstdint>


class IAdc
{
public:
    virtual ~IAdc() = default;

    virtual uint32_t getValue(uint32_t channel) = 0;
    virtual uint32_t getMaxValue(uint32_t channel) = 0;
    virtual uint32_t getMaxVoltage(uint32_t channel) = 0;

    virtual float getVoltage(uint32_t channel) = 0;
};


extern IAdc* defaultIAdc;

/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/access/IAdc.hpp>


class ArduinoAdc :
	public IAdc
{
public:
    ArduinoAdc();
    ~ArduinoAdc();
	
    uint32_t getValue(uint32_t channel);
    uint32_t getMaxValue(uint32_t channel);
    uint32_t getMaxVoltage(uint32_t channel);

    float getVoltage(uint32_t channel);

private:
    uint32_t m_maxValue;
    float m_refVoltage;
};

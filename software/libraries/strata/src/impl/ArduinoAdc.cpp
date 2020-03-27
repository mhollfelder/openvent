/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#include "ArduinoAdc.hpp"

#include "Arduino.h"


ArduinoAdc::ArduinoAdc() :
    m_maxValue {(1u << 9)},
#if defined(ARDUINO_AVR_DUE)
    m_refVoltage {3.3}
#else
    m_refVoltage {5}
#endif
{
}

ArduinoAdc::~ArduinoAdc()
{
}

uint32_t ArduinoAdc::getValue(uint32_t channel)
{
    return analogRead(channel);
}

uint32_t ArduinoAdc::getMaxValue(uint32_t channel)
{
    return m_maxValue;
}

uint32_t ArduinoAdc::getMaxVoltage(uint32_t channel)
{
    return m_refVoltage;
}

float ArduinoAdc::getVoltage(uint32_t channel)
{
    return m_refVoltage * getValue(channel) / m_maxValue;
}

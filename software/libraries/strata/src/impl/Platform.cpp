/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#include "Platform.hpp"


Platform::Platform()
{
}

Platform::~Platform()
{
}

uint16_t Platform::getMaxTransfer()
{
    return UINT16_MAX;
}

IGpio *Platform::getIGpio()
{
    return &m_gpio;
}

II2c *Platform::getII2c()
{
    return &m_i2c;
}

ISpi* Platform::getISpi()
{
    return &m_spi;
}

IAdc *Platform::getIAdc()
{
    return &m_adc;
}

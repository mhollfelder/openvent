/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/BridgeControl.hpp>
#include "ArduinoSpi.hpp"
#include "ArduinoI2c.hpp"
#include "ArduinoGpio.hpp"
#include "ArduinoAdc.hpp"


class Platform :
    public BridgeControl
{
public:
    Platform();
    ~Platform();

    uint16_t getMaxTransfer();

    IGpio *getIGpio();
    II2c *getII2c();
    ISpi *getISpi();
    IAdc *getIAdc();
	
private:
    ArduinoSpi m_spi;
    ArduinoI2c m_i2c;
    ArduinoGpio m_gpio;
    ArduinoAdc m_adc;
};

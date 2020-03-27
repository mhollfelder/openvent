/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#include "ArduinoDac.hpp"

#include "Arduino.h"


ArduinoDac::ArduinoDac()
{
}

ArduinoDac::~ArduinoDac()
{
}

void ArduinoDac::configureOutput(uint32_t channel, uint8_t flags)
{
	pinMode(channel, OUTPUT);
}

void ArduinoDac::setOutput(uint32_t channel, uint32_t value)
{
	analogWrite(channel, value);
}


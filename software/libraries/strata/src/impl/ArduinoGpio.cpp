/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#include "ArduinoGpio.hpp"

#include <Arduino.h>


ArduinoGpio::ArduinoGpio()
{
}

ArduinoGpio::~ArduinoGpio()
{
}

sr_t ArduinoGpio::configureGpio(uint16_t id, uint8_t flags)
{
    if (id == GPIO_NAME_NONE)
    {
        RETURN
    }

    const bool initialHigh = flags & GPIO_FLAG_OUTPUT_INITIAL_HIGH;
    const bool driveLow = flags & GPIO_FLAG_OUTPUT_DRIVE_LOW;
    const bool driveHigh = flags & GPIO_FLAG_OUTPUT_DRIVE_HIGH;
    const bool input = flags & GPIO_FLAG_INPUT_ENABLE;
    const bool pullUp = flags & GPIO_FLAG_PULL_UP;
    const bool pullDown = flags & GPIO_FLAG_PULL_DOWN;
    const bool pull = pullUp || pullDown;

    if (input)
    {
        if (pull)
        {
			pinMode(id, INPUT_PULLUP);
        }
        else
        {
			pinMode(id, INPUT);
        }
    }
    else
    {
        pinMode(id, OUTPUT);
    }
       
	RETURN
}

sr_t ArduinoGpio::setGpio(uint16_t id, bool state)
{
    if (id == GPIO_NAME_NONE)
    {
        return ENone;
    }

    if (state)
    {
        digitalWrite(id, HIGH);
    }
    else
    {
        digitalWrite(id, LOW);
    }

	RETURN
}

bool ArduinoGpio::getGpio(uint16_t id)
{
    if (id == GPIO_NAME_NONE)
    {
        return false;
    }

    return digitalRead(id) == HIGH;
}


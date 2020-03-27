/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/access/IGpio.hpp>


class ArduinoGpio :
	public IGpio
{
public:
    ArduinoGpio();
    ~ArduinoGpio();

    sr_t configureGpio(uint16_t id, uint8_t flags);
    sr_t setGpio(uint16_t id, bool state);
    bool getGpio(uint16_t id);
};

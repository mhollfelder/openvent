/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/access/ISpi.hpp>


class ArduinoSpi :
	public ISpi
{
public:
    ArduinoSpi();
    ~ArduinoSpi();

    uint32_t getSpiMaxTransfer();

    sr_t configureSpi(uint8_t devId, uint8_t flags, uint8_t wordSize, uint32_t speed);

    sr_t readSpi(uint8_t devId, uint32_t count, uint8_t buffer[]);
    sr_t readSpi(uint8_t devId, uint32_t count, uint16_t buffer[]);
    sr_t readSpi(uint8_t devId, uint32_t count, uint32_t buffer[]);

    sr_t writeSpi(uint8_t devId, uint32_t count, const uint8_t buffer[]);
    sr_t writeSpi(uint8_t devId, uint32_t count, const uint16_t buffer[]);
    sr_t writeSpi(uint8_t devId, uint32_t count, const uint32_t buffer[]);

    sr_t transferSpi(uint8_t devId, uint32_t count, const uint8_t write[], uint8_t read[]);
    sr_t transferSpi(uint8_t devId, uint32_t count, const uint16_t write[], uint16_t read[]);
    sr_t transferSpi(uint8_t devId, uint32_t count, const uint32_t write[], uint32_t read[]);
};

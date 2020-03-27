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
#include <universal/spi_definitions.h>


/**
 * This is a generic interface for supporting arbitrary Serial Peripheral Interface
 * access to connected devices. Each instance of this class represents one SPI master.
 */
class ISpi
{
public:
    virtual ~ISpi() = default;

    /**
    * Configure the clock speed for SPI transactions.
    * Optionally, specify a slave for which this setting is intended.
    *
    * @param devId (optional, only if supported) the device ID for which this setting is intended
    * @param flags specifies the configuration flags
    * @param wordSize specifies the word length in bits
    * @param speed specifies the clock speed in Hz
    */
    virtual sr_t configureSpi(uint8_t devId, uint8_t flags, uint8_t wordSize, uint32_t speed) = 0;

    /**
    * Returns the maximum accepted length of a buffer for a transmission,
    * which is specific to the implementation of the interface.
    */
    virtual uint32_t getSpiMaxTransfer() = 0;

    /**
    * Reading data from an SPI device in half-duplex mode.
    *
    * @param devId the device ID that identifies the slave select signal to be used
    * @param count number of words to be read
    * @param buffer a buffer of the specified length
    */
    virtual sr_t readSpi(uint8_t devId, uint32_t count, uint8_t buffer[]) = 0;
    virtual sr_t readSpi(uint8_t devId, uint32_t count, uint16_t buffer[]) = 0;
    virtual sr_t readSpi(uint8_t devId, uint32_t count, uint32_t buffer[]) = 0;

    /**
    * Write data to an SPI device in half-duplex mode.
    * The slave select line can be kept active to follow the write with a read to form a single transmission.
    *
    * @param devId the device ID that identifies the slave select signal to be used
    * @param count number of words to be written
    * @param buffer a buffer of the specified length
    */
    virtual sr_t writeSpi(uint8_t devId, uint32_t count, const uint8_t buffer[]) = 0;
    virtual sr_t writeSpi(uint8_t devId, uint32_t count, const uint16_t buffer[]) = 0;
    virtual sr_t writeSpi(uint8_t devId, uint32_t count, const uint32_t buffer[]) = 0;

    virtual sr_t transferSpi(uint8_t devId, uint32_t count, const uint8_t write[], uint8_t read[]) = 0;
    virtual sr_t transferSpi(uint8_t devId, uint32_t count, const uint16_t write[], uint16_t read[]) = 0;
    virtual sr_t transferSpi(uint8_t devId, uint32_t count, const uint32_t write[], uint32_t read[]) = 0;
};


extern ISpi* defaultISpi;

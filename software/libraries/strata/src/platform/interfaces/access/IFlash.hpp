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


class IFlash
{
public:
    virtual ~IFlash() = default;

    /**
    * Returns the maximum accepted length of a buffer for a transmission,
    * which is specific to the implementation of the interface.
    */
    virtual uint32_t getFlashMaxTransfer() = 0;

    /**
    * Reading from an (SPI) flash device.
    *
    * @param devId the device ID that identifies the slave select signal to be used
    * @param address specifies the memory address to access
    * @param length number of bytes to be read
    * @param buffer a buffer of the specified length
    */
    virtual sr_t readFlash(uint8_t devId, uint32_t address, uint32_t length, uint8_t buffer[]) = 0;

    /**
    * Writing to an (SPI) flash device.
    *
    * @param devId the device ID that identifies the slave select signal to be used
    * @param address specifies the memory address to access
    * @param length number of bytes to be written
    * @param buffer a buffer of the specified length
    */
    virtual sr_t writeFlash(uint8_t devId, uint32_t address, uint32_t length, const uint8_t buffer[]) = 0;

    /**
    * Erasing a sector of an (SPI) flash device
    * This should only happen with the knowledge of the sector size.
    *
    * @param devId the device ID that identifies the slave select signal to be used
    * @param address specifies the memory address to access (sector aligned)
    */
    virtual sr_t eraseFlash(uint8_t devId, uint32_t address) = 0;

    /**
    * Getting the WIP flag of an (SPI) flash device.
    *
    * @param devId the device ID that identifies the slave select signal to be used
    * @param status the variable to receive the return
    */
    virtual uint8_t getFlashStatus(uint8_t devId) = 0;
};

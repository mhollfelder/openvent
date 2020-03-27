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


/**
 * This is a generic interface for supporting arbitrary I2C bus access to connected devices.
 * Each instance of this class represents one I2C master.
 */
class II2c
{
public:
//    static const uint8_t reservedAddress = 0x7F;

    virtual ~II2c() = default;

    /**
    * Returns the maximum accepted length of a buffer for a transmission,
    * which is specific to the implementation of the interface.
    */
    virtual uint16_t getI2cMaxTransfer() = 0;

    /**
     * Read register(s) from an I2C device.
     *
     * @param devAddr the device address that identifies the slave
     * @param length number of bytes to be read
     * @param buffer a buffer of the specified length
     */
    virtual sr_t readI2cNoRegister(uint8_t devAddr, uint16_t length, uint8_t buffer[]) = 0;
    virtual sr_t readI2c8BitRegister(uint8_t devAddr, uint8_t regAddr, uint16_t length, uint8_t buffer[]) = 0;
    virtual sr_t readI2c16BitRegister(uint8_t devAddr, uint16_t regAddr, uint16_t length, uint8_t buffer[]) = 0;

    /**
     * Write register(s) to an I2C device.
     *
     * @param devAddr the device address that identifies the slave
     * @param length number of bytes to be written
     * @param buffer a buffer of the specified length
     */
    virtual sr_t writeI2cNoRegister(uint8_t devAddr, uint16_t length, const uint8_t buffer[]) = 0;
    virtual sr_t writeI2c8BitRegister(uint8_t devAddr, uint8_t regAddr, uint16_t length, const uint8_t buffer[]) = 0;
    virtual sr_t writeI2c16BitRegister(uint8_t devAddr, uint16_t regAddr, uint16_t length, const uint8_t buffer[]) = 0;

    /**
     * Configure the clock speed for I2C transactions.
     * This is always valid for the complete bus, so all connected devices must support it.
     *
     * @param speed specifies the clock speed in Hz
     */
    virtual sr_t setI2cBusSpeed(uint32_t speed) = 0;
};


extern II2c* defaultII2c;

/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/access/II2c.hpp>


class ArduinoI2c :
	public II2c
{
public:
    ArduinoI2c();
    ~ArduinoI2c();

    uint16_t getI2cMaxTransfer();
    sr_t readI2cNoRegister(uint8_t devAddr, uint16_t length, uint8_t buffer[]);
    sr_t readI2c8BitRegister(uint8_t devAddr, uint8_t regAddr, uint16_t length, uint8_t buffer[]);
    sr_t readI2c16BitRegister(uint8_t devAddr, uint16_t regAddr, uint16_t length, uint8_t buffer[]);
    sr_t writeI2cNoRegister(uint8_t devAddr, uint16_t length, const uint8_t buffer[]);
    sr_t writeI2c8BitRegister(uint8_t devAddr, uint8_t regAddr, uint16_t length, const uint8_t buffer[]);
    sr_t writeI2c16BitRegister(uint8_t devAddr, uint16_t regAddr, uint16_t length, const uint8_t buffer[]);
    sr_t setI2cBusSpeed(uint32_t speed);	
};

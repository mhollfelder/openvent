/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#include "ArduinoI2c.hpp"

#include <platform/exception/EPlatform.hpp>

#include <Wire.h>


ArduinoI2c::ArduinoI2c()
{
	Wire.begin();
}

ArduinoI2c::~ArduinoI2c()
{
}

uint16_t ArduinoI2c::getI2cMaxTransfer()
{
    return UINT16_MAX;
}

static sr_t i2cRead(uint8_t devAddr, uint16_t length, uint8_t buffer[])
{
	Wire.requestFrom(static_cast<int>(devAddr), length, true);
	while (Wire.available())
	{
		*buffer++ = Wire.read();
		length--;
	}
	if (length)
	{
		RET_THROW EPlatform("I2C not enough bytes returned");
	}
	RETURN
}

sr_t ArduinoI2c::readI2cNoRegister(uint8_t devAddr, uint16_t length, uint8_t buffer[])
{
	THROWS(i2cRead(devAddr, length, buffer);)
	RETURN
}

sr_t ArduinoI2c::readI2c8BitRegister(uint8_t devAddr, uint8_t regAddr, uint16_t length, uint8_t buffer[])
{
	Wire.beginTransmission(devAddr);
	Wire.write(regAddr);
	Wire.endTransmission();

	THROWS(i2cRead(devAddr, length, buffer);)
	RETURN
}

sr_t ArduinoI2c::readI2c16BitRegister(uint8_t devAddr, uint16_t regAddr, uint16_t length, uint8_t buffer[])
{
	Wire.beginTransmission(devAddr);
	Wire.write(regAddr >> 8);
	Wire.write(regAddr & 0xFF);
	Wire.endTransmission();

	THROWS(i2cRead(devAddr, length, buffer);)
	RETURN
}

sr_t ArduinoI2c::writeI2cNoRegister(uint8_t devAddr, uint16_t length,
        const uint8_t buffer[])
{
	Wire.beginTransmission(devAddr);
	while (length--)
	{
		Wire.write(*buffer++);
	}
	Wire.endTransmission();
	
	RETURN
}

sr_t ArduinoI2c::writeI2c8BitRegister(uint8_t devAddr, uint8_t regAddr,
        uint16_t length, const uint8_t buffer[])
{
	Wire.beginTransmission(devAddr);
	Wire.write(regAddr);
	while (length--)
	{
		Wire.write(*buffer++);
	}
	Wire.endTransmission();
	
	RETURN
}

sr_t ArduinoI2c::writeI2c16BitRegister(uint8_t devAddr, uint16_t regAddr,
        uint16_t length, const uint8_t buffer[])
{
	Wire.beginTransmission(devAddr);
	Wire.write(regAddr >> 8);
	Wire.write(regAddr & 0xFF);
	while (length--)
	{
		Wire.write(*buffer++);
	}
	Wire.endTransmission();
	
	RETURN
}

sr_t ArduinoI2c::setI2cBusSpeed(uint32_t speed)
{	
	RETURN
}

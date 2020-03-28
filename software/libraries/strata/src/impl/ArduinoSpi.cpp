/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#include "ArduinoSpi.hpp"
#include "ArduinoSpiConfig.hpp"
#include <spi_config.h>

#include <platform/exception/EPlatform.hpp>

#include <SPI.h>


#ifndef PLATFORM_SPI_MAX_DEVICES
	#define PLATFORM_SPI_MAX_DEVICES 0
#endif

#if PLATFORM_SPI_MAX_DEVICES
	static SPISettings m_settings[PLATFORM_SPI_MAX_DEVICES];
#endif

//uint8_t ArduinoSpi::setDeviceId(uint8_t devId, int csPin)
//{
//}

static SPISettings* createSettings(unsigned int devId)
{
	for (unsigned int i = 0; i < PLATFORM_SPI_MAX_DEVICES; i++)
	{
		if ((boardSpiConfig[i].csPin == devId) || (boardSpiConfig[i].csPin == 0xEE))
		{
			boardSpiConfig[i].csPin = devId;
			return &m_settings[i];
		}
	}
	
	return nullptr;
}

static SPISettings* findSettings(unsigned int devId)
{
	for (unsigned int i = 0; i < PLATFORM_SPI_MAX_DEVICES; i++)
	{
		if (boardSpiConfig[i].csPin == devId)
		{
			return &m_settings[i];
		}
	}
	
	return nullptr;
}

ArduinoSpi::ArduinoSpi()
{
	SPI.begin();
}

ArduinoSpi::~ArduinoSpi()
{
}

uint32_t ArduinoSpi::getSpiMaxTransfer()
{
    return UINT32_MAX;
}

sr_t ArduinoSpi::configureSpi(uint8_t devId, uint8_t flags, uint8_t wordSize, uint32_t speed)
{
//    if (devId > PLATFORM_SPI_MAX_DEVICES)
//    {
//        return;
//    }
	auto dev = createSettings(devId);
	if (dev == nullptr)
	{
		RET_THROW EPlatform("SPI device not configured");
	}
	
#if PLATFORM_SPI_MAX_DEVICES
    //auto dev = m_settings[devId];
	//const auto csPin = boardSpiConfig[devId].csPin;
	const int csPin = devId;

    const bool threeWire = flags & SPI_3_WIRE;
    if (threeWire)
    {
        //RET_THROW EPlatform("SPI_3_WIRE not supported");
    }

    const bool lsbFirst = flags & SPI_LSB_FIRST;
    const bool csHighActive = flags & SPI_CS_HIGH_ACTIVE;
    const uint8_t spiMode = flags & 0x3;

    if (csHighActive)
    {
        RET_THROW EPlatform("csHighActive not supported");
    }
    if ((wordSize < 8) || (wordSize > 32) || (wordSize % 8))
    {
        RET_THROW EPlatform("wordSize not supported", wordSize);
    }
	
	uint8_t dataMode;

    switch (spiMode)
    {
        case SPI_MODE_0:
            dataMode = SPI_MODE0;
            break;
        case SPI_MODE_1:
            dataMode = SPI_MODE1;
            break;
        case SPI_MODE_2:
            dataMode = SPI_MODE2;
            break;
        case SPI_MODE_3:
            dataMode = SPI_MODE3;
            break;
        default:
            RET_THROW EPlatform("invalid spiMode", spiMode);
    }
	
	*dev = SPISettings(speed, lsbFirst?LSBFIRST:MSBFIRST, dataMode);

	if (csPin < 0xD0)
	{
		pinMode(csPin, OUTPUT);
		digitalWrite(csPin, HIGH);
	}
#endif
}

template <typename L>
static sr_t spiTransaction(uint8_t devId, uint32_t count, L& transfer)
{
//    if (devId > PLATFORM_SPI_MAX_DEVICES)
//    {
//        return;
//    }
	auto dev = findSettings(devId);
	if (dev == nullptr)
	{
		RET_THROW EPlatform("SPI device not configured");
	}
	
#if PLATFORM_SPI_MAX_DEVICES
    //auto &dev = m_settings[devId];
	//const auto csPin = boardSpiConfig[devId].csPin;
	const int csPin = devId;
	
	SPI.beginTransaction(*dev);
	if (csPin < 0xD0)
	{
		digitalWrite(csPin, LOW);
	}
	
	while (count--)
	{
		transfer();
	}

	if (csPin < 0xD0)
	{
		digitalWrite(csPin, HIGH);
	}
	SPI.endTransaction();
#endif
}

sr_t ArduinoSpi::readSpi(uint8_t devId, uint32_t count, uint8_t buffer[])
{
	auto transfer = [&]()
	{
		*buffer++ = SPI.transfer(0);
	};
	
	spiTransaction(devId, count, transfer);
}

sr_t ArduinoSpi::readSpi(uint8_t devId, uint32_t count, uint16_t buffer[])
{
	auto transfer = [&]()
	{
		const auto buf = SPI.transfer(0) << 8;
		*buffer++ = buf | SPI.transfer(0);
	};
	
	spiTransaction(devId, count, transfer);
}

sr_t ArduinoSpi::readSpi(uint8_t devId, uint32_t count, uint32_t buffer[])
{
	auto transfer = [&]()
	{
		auto buf = SPI.transfer(0) << 24;
		buf |= SPI.transfer(0) << 16;
		buf |= SPI.transfer(0) << 8;
		*buffer++ = buf | SPI.transfer(0);
	};
	
	spiTransaction(devId, count, transfer);
}

sr_t ArduinoSpi::writeSpi(uint8_t devId, uint32_t count, const uint8_t buffer[])
{
	auto transfer = [&]()
	{
		SPI.transfer(*buffer++);
	};
	
	spiTransaction(devId, count, transfer);
}

sr_t ArduinoSpi::writeSpi(uint8_t devId, uint32_t count, const uint16_t buffer[])
{
 	auto transfer = [&]()
	{
		const auto buf = *buffer++;
		SPI.transfer(buf >> 8);
		SPI.transfer(buf & 0xFF);
	};
	
	spiTransaction(devId, count, transfer);
}

sr_t ArduinoSpi::writeSpi(uint8_t devId, uint32_t count, const uint32_t buffer[])
{
 	auto transfer = [&]()
	{
		const auto buf = *buffer++;
		SPI.transfer(buf >> 24);
		SPI.transfer((buf >> 16) & 0xFF);
		SPI.transfer((buf >> 8) & 0xFF);
		SPI.transfer(buf & 0xFF);
	};
	
	spiTransaction(devId, count, transfer);
}

sr_t ArduinoSpi::transferSpi(uint8_t devId, uint32_t count, const uint8_t write[], uint8_t read[])
{
	auto transfer = [&]()
	{
		*read++ = SPI.transfer(*write++);
	};
	
	spiTransaction(devId, count, transfer);
}

sr_t ArduinoSpi::transferSpi(uint8_t devId, uint32_t count, const uint16_t write[], uint16_t read[])
{
	auto transfer = [&]()
	{
        const auto bufOut = *write++;
		const auto bufIn = SPI.transfer(bufOut >> 8) << 8;
		*read++ = bufIn | SPI.transfer(bufOut & 0xFF);
	};
	
	spiTransaction(devId, count, transfer);
}

sr_t ArduinoSpi::transferSpi(uint8_t devId, uint32_t count, const uint32_t write[], uint32_t read[])
{
	auto transfer = [&]()
	{
        const auto bufOut = *write++;
		auto bufIn = SPI.transfer(bufOut >> 24) << 24;
		bufIn |= SPI.transfer((bufOut >> 16) & 0xFF) << 16;
		bufIn |= SPI.transfer((bufOut >> 8) & 0xFF) << 8;
		*read++ = bufIn | SPI.transfer(bufOut & 0xFF);
	};
	
	spiTransaction(devId, count, transfer);
}

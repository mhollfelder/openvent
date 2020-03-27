
#define PLATFORM_SPI_MAX_DEVICES 4

#include "impl/ArduinoSpiConfig.hpp"

// use of pin look-up table per board not possible with Arduino
// therefor create the look-up on the go and use csPin as devId

BoardSpiConfig boardSpiConfig[PLATFORM_SPI_MAX_DEVICES] = {
	{0xFF}, //.csPin
	{0xFF}, //.csPin
	{0xFF}, //.csPin
	{0xFF}, //.csPin
};


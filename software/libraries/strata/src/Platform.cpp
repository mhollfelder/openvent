#include "impl/Platform.hpp"


Platform platform;


IGpio* defaultIGpio = platform.getIGpio();
II2c* defaultII2c = platform.getII2c();;
ISpi* defaultISpi = platform.getISpi();;
IAdc* defaultIAdc = platform.getIAdc();


#include "impl/ArduinoDac.hpp"
ArduinoDac Dac;
IDac *defaultIDac = &Dac;

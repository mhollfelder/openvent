/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#include "MemoryAccess.hpp"


uint32_t MemoryAccess::readValue(uint32_t address)
{
    uint32_t value;
    readMem(address, sizeof(value), &value);
    return value;
}

sr_t MemoryAccess::readValue(uint32_t address, uint32_t &value)
{
    readMem(address, sizeof(value), &value);
}

sr_t MemoryAccess::writeValue(uint32_t address, uint32_t value)
{
    writeMem(address, sizeof(value), &value);
}

sr_t MemoryAccess::readMemBatch(uint32_t vals[][2], uint32_t count)
{
    for (uint_fast32_t i = 0; i < count; i++)
    {
        readValue(vals[i][0], vals[i][1]);
    }
}

sr_t MemoryAccess::writeMemBatch(const uint32_t vals[][2], uint32_t count)
{
    for (uint_fast32_t i = 0; i < count; i++)
    {
        writeValue(vals[i][0], vals[i][1]);
    }
}

sr_t MemoryAccess::setMemBits(uint32_t regAddr, uint32_t bitmask)
{
    uint32_t value;
    readValue(regAddr, value);

    value |= bitmask;

    writeValue(regAddr, value);
}

sr_t MemoryAccess::clearMemBits(uint32_t regAddr, uint32_t bitmask)
{
    uint32_t value;
    readValue(regAddr, value);

    value &= ~bitmask;

    writeValue(regAddr, value);
}

sr_t MemoryAccess::modifyMemBits(uint32_t regAddr, uint32_t clearBitmask, uint32_t setBitmask)
{
    uint32_t value;
    readValue(regAddr, value);

    value &= ~clearBitmask;
    value |= setBitmask;

    writeValue(regAddr, value);
}

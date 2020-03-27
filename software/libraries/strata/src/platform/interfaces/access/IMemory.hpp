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


class IMemory
{
public:
    virtual ~IMemory() = default;

    virtual uint32_t readValue(uint32_t address) = 0;
    virtual sr_t readValue(uint32_t address, uint32_t &value) = 0;
    virtual sr_t writeValue(uint32_t address, uint32_t value) = 0;
    virtual sr_t readMem(uint32_t address, uint32_t count, uint32_t data[]) = 0;
    virtual sr_t writeMem(uint32_t address, uint32_t count, const uint32_t data[]) = 0;

    virtual sr_t readMemBatch(uint32_t vals[][2], uint32_t count) = 0;
    virtual sr_t writeMemBatch(const uint32_t vals[][2], uint32_t count) = 0;

    virtual sr_t setMemBits(uint32_t address, uint32_t bitmask) = 0;
    virtual sr_t clearMemBits(uint32_t address, uint32_t bitmask) = 0;
    virtual sr_t modifyMemBits(uint32_t address, uint32_t clearBitmask, uint32_t setBitmask) = 0;

//    virtual sr_t setMem(uint32_t address, uint32_t value, uint32_t length) = 0;

//    virtual sr_t readValue16(uint32_t address, uint16_t &value) = 0;
//    virtual sr_t writeValue16(uint32_t address, uint16_t value) = 0;
};

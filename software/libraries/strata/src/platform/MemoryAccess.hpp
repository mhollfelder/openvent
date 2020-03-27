/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/access/IMemory.hpp>


class MemoryAccess :
    public IMemory
{
public:
    virtual ~MemoryAccess() = default;

    virtual uint32_t readValue(uint32_t address);
    virtual sr_t readValue(uint32_t address, uint32_t &value);
    virtual sr_t writeValue(uint32_t address, uint32_t value);

    virtual sr_t readMemBatch(uint32_t vals[][2], uint32_t count);
    virtual sr_t writeMemBatch(const uint32_t vals[][2], uint32_t count);

    virtual sr_t setMemBits(uint32_t address, uint32_t bitmask);
    virtual sr_t clearMemBits(uint32_t address, uint32_t bitmask);
    virtual sr_t modifyMemBits(uint32_t address, uint32_t clearBitmask, uint32_t setBitmask);
};

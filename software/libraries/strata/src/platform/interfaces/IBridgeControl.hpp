/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/access/IAdc.hpp>
#include <platform/interfaces/access/IGpio.hpp>
#include <platform/interfaces/access/II2c.hpp>
#include <platform/interfaces/access/ISpi.hpp>
#include <platform/interfaces/access/IFlash.hpp>
#include <platform/interfaces/access/IMemory.hpp>


class IBridgeControl
{
public:
    virtual ~IBridgeControl() = default;

    virtual void setDefaultTimeout() = 0;
    virtual uint16_t getMaxTransfer() = 0;

    virtual IAdc *getIAdc() = 0;
    virtual IGpio *getIGpio() = 0;
    virtual II2c *getII2c() = 0;
    virtual ISpi *getISpi() = 0;
    virtual IFlash *getIFlash() = 0;
    virtual IMemory *getIMemory() = 0;
};

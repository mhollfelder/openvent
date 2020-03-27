/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/IBridgeControl.hpp>


class BridgeControl :
    public IBridgeControl
{
public:
    virtual void setDefaultTimeout();
    virtual IAdc *getIAdc();
    virtual IGpio *getIGpio();
    virtual II2c *getII2c();
    virtual ISpi *getISpi();
    virtual IFlash *getIFlash();
    virtual IMemory *getIMemory();
};

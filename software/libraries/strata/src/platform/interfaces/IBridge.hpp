/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/IBridgeData.hpp>
#include <platform/interfaces/IBridgeControl.hpp>



class IBridge
{
public:
    virtual ~IBridge() = default;

    virtual bool isConnected() = 0;
//    virtual sr_t openConnection() = 0;
    virtual sr_t closeConnection() = 0;

    virtual sr_t getBoardInfo(uint8_t buffer[32], uint16_t ids[2]) = 0;

    virtual IBridgeControl *getIBridgeControl() = 0;
    virtual IBridgeData *getIBridgeData() = 0;
};

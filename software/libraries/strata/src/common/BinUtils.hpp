/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once


template <unsigned int bits>
inline int getTwosComplement(int rawValue)
{
    if (rawValue & (1 << (bits - 1)))
    {
        rawValue -= (1 << bits);
    }
    return rawValue;
}


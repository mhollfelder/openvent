/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <common/exception/ENarrowCast.hpp>

/*!
 * Narrow cast proposed by Stroustrup's C++ bible (pg. 299, 11.5)
 */
template<typename Target, typename Source>
inline Target narrow_cast(Source v)
{
    const auto r = static_cast<Target>(v);
    if (static_cast<Source>(r) != v)
    {
        throw ENarrowCast(sizeof(Target));
    }
    return r;
}

template<typename Target, uint8_t bits, typename Source>
inline Target narrow_cast(Source v)
{
    const auto r = static_cast<Target>(v) & ((1 << bits) - 1);
    if (static_cast<Source>(r) != v)
    {
        throw ENarrowCast(bits);
    }
    return r;
}

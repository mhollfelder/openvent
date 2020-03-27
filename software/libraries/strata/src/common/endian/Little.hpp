/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include "General.hpp"
#include <algorithm>



// copy host buffer to little-endian buffer

template <typename InputIt, typename OutputIt, typename It = InputIt>
inline typename std::enable_if<is_little_endian<It>::value>::type
hostToLittle(InputIt first, InputIt last, OutputIt dest)
{
    std::copy(first, last, dest);
}

template <typename InputIt, typename OutputIt, typename It = InputIt>
inline typename std::enable_if<is_big_endian<It>::value>::type
hostToLittle(InputIt first, InputIt last, OutputIt dest)
{
    endian::swap(first, last, dest);
}


// transform host buffer into little-endian buffer

template <typename It>
inline typename std::enable_if<is_little_endian<It>::value>::type
hostToLittle(It, It)
{
}

template <typename It>
inline typename std::enable_if<is_big_endian<It>::value>::type
hostToLittle(It first, It last)
{
    endian::swap(first, last, first);
}


// copy little-endian buffer to host buffer

template <typename InputIt, typename OutputIt, typename It = InputIt>
inline typename std::enable_if <is_little_endian<It>::value>::type
littleToHost(InputIt first, InputIt last, OutputIt dest)
{
    std::copy(first, last, dest);
}

template <typename InputIt, typename OutputIt, typename It = InputIt>
inline typename std::enable_if<is_big_endian<It>::value>::type
littleToHost(InputIt first, InputIt last, OutputIt dest)
{
    endian::swap(first, last, dest);
}


// transform little-endian buffer into host buffer

template <typename It>
inline typename std::enable_if<is_little_endian<It>::value>::type
littleToHost(It, It)
{
}

template <typename It>
inline typename std::enable_if<is_big_endian<It>::value>::type
littleToHost(It first, It last)
{
    endian::swap(first, last, first);
}


// transform little-endian value into host value

template <typename T>
inline typename std::enable_if<is_little_endian<T>::value, T>::type
littleToHost(T first)
{
    return first;
}

template <typename T>
inline typename std::enable_if<is_big_endian<T>::value, T>::type
littleToHost(T first)
{
    return endian::swap(first);
}


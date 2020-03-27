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



// copy host buffer to big-endian buffer

template <typename InputIt, typename OutputIt, typename It = InputIt>
inline typename std::enable_if<is_big_endian<It>::value>::type
hostToBig(InputIt first, InputIt last, OutputIt dest)
{
    std::copy(first, last, dest);
}

template <typename InputIt, typename OutputIt, typename It = InputIt>
inline typename std::enable_if<is_little_endian<It>::value>::type
hostToBig(InputIt first, InputIt last, OutputIt dest)
{
    endian::swap(first, last, dest);
}


// transform host buffer into big-endian buffer

template <typename It>
inline typename std::enable_if<is_big_endian<It>::value>::type
hostToBig(It, It)
{
}

template <typename It>
inline typename std::enable_if<is_little_endian<It>::value>::type
hostToBig(It first, It last)
{
    endian::swap(first, last, first);
}


// copy big-endian buffer to host buffer

template <typename InputIt, typename OutputIt, typename It = InputIt>
inline typename std::enable_if <is_big_endian<It>::value>::type
bigToHost(InputIt first, InputIt last, OutputIt dest)
{
    std::copy(first, last, dest);
}

template <typename InputIt, typename OutputIt, typename It = InputIt>
inline typename std::enable_if<is_little_endian<It>::value>::type
bigToHost(InputIt first, InputIt last, OutputIt dest)
{
    endian::swap(first, last, dest);
}


// transform big-endian buffer into host buffer

template <typename It>
inline typename std::enable_if<is_big_endian<It>::value>::type
bigToHost(It, It)
{
}

template <typename It>
inline typename std::enable_if<is_little_endian<It>::value>::type
bigToHost(It first, It last)
{
    endian::swap(first, last, first);
}


// transform big-endian value into host value

template <typename T>
inline typename std::enable_if<is_big_endian<T>::value, T>::type
bigToHost(T first)
{
    return first;
}

template <typename T>
inline typename std::enable_if<is_little_endian<T>::value, T>::type
bigToHost(T first)
{
    return endian::swap(first);
}


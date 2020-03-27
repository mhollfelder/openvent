/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include "EndianConversion.hpp"


// copy host buffer to serial buffer

template <typename T>
inline uint8_t *hostToSerial(uint8_t *dest, T first)
{
    auto begin_it = reinterpret_cast<const uint8_t *>(&first);
    auto end_it = begin_it + sizeof(T);
    std::copy(begin_it, end_it, dest);
    return dest + sizeof(T);
}

template <>
inline uint8_t *hostToSerial(uint8_t *dest, uint16_t first)
{
    *(dest++) = first & 0xFF;
    *(dest++) = first >> 8;
    return dest;
}

template <>
inline uint8_t *hostToSerial(uint8_t *dest, int16_t first)
{
    return hostToSerial(dest, static_cast<uint16_t>(first));
}

template <>
inline uint8_t *hostToSerial(uint8_t *dest, uint32_t first)
{
    *(dest++) = first & 0xFF;
    *(dest++) = static_cast<uint8_t>(first >> 8);
    *(dest++) = static_cast<uint8_t>(first >> 16);
    *(dest++) = static_cast<uint8_t>(first >> 24);
    return dest;
}

template <>
inline uint8_t *hostToSerial(uint8_t *dest, int32_t first)
{
    return hostToSerial(dest, static_cast<uint32_t>(first));
}

template <typename It>
inline typename std::enable_if < (
    !std::is_integral<typename std::remove_pointer<It>::type>::value ||
    is_little_endian<It>::value ||
    std::is_same<It, uint8_t *>::value ||
    std::is_same<It, int8_t *>::value
), uint8_t * >::type
hostToSerial(uint8_t *dest, const It first, const It last)
{
    auto begin_it = reinterpret_cast<const uint8_t *>(first);
    auto end_it = reinterpret_cast<const uint8_t *>(last);
    std::copy(begin_it, end_it, dest);
    return dest + (last - first) * sizeof(typename std::remove_pointer<It>::type);
}

template <typename It>
inline typename std::enable_if < (
    is_big_endian<It>::value &&(
        std::is_same<It, uint16_t *>::value ||
        std::is_same<It, int16_t *>::value ||
        std::is_same<It, uint32_t *>::value ||
        std::is_same<It, int32_t *>::value
    )), uint8_t * >::type
hostToSerial(uint8_t *dest, const It first, const It last)
{
    while (first < last)
    {
        hostToSerial(dest, *(first++));
    }
}

template <typename T, std::size_t N>
inline uint8_t *hostToSerial(uint8_t *dest, const T(&first)[N])
{
    return hostToSerial(dest, std::begin(first), std::end(first));
}

//template <typename T, std::size_t M, std::size_t N>
//inline uint8_t *hostToSerial(uint8_t *dest, const T(&first)[M][N])
//{
//    return hostToSerial(dest, std::begin(first), std::end(first));
//}


// get serial buffer value

template <typename T, typename std::enable_if <sizeof(T) == 1, T>::type * = nullptr>
inline T serialToHost(const uint8_t *first, const uint8_t *&next)
{
    next = first + sizeof(T);
    return *reinterpret_cast<const T *>(first);
}

template < typename T, typename std::enable_if < sizeof(T) != 1, T >::type * = nullptr >
inline T serialToHost(const uint8_t *first, const uint8_t *&next)
{
    T value;
    next = first + sizeof(T);
    auto dest = reinterpret_cast<uint8_t *>(&value);
    std::copy(first, next, dest);
    return value;
}

template <>
inline uint16_t serialToHost(const uint8_t *first, const uint8_t *&next)
{
    next = first;
    uint16_t tmp = *(next++);
    return tmp | static_cast<uint16_t>(*(next++) << 8);
}

template <>
inline int16_t serialToHost(const uint8_t *first, const uint8_t *&next)
{
    return static_cast<int16_t>(serialToHost<uint16_t>(first, next));
}

template <>
inline uint32_t serialToHost(const uint8_t *first, const uint8_t *&next)
{
    next = first;
    uint32_t tmp = *(next++);
    tmp |= static_cast<uint32_t>(*(next++) << 8);
    tmp |= static_cast<uint32_t>(*(next++) << 16);
    return tmp | static_cast<uint32_t>(*(next++) << 24);
}

template <>
inline int32_t serialToHost(const uint8_t *first, const uint8_t *&next)
{
    return static_cast<int32_t>(serialToHost<uint32_t>(first, next));
}

// this template removing the last argument has to be declared after the ones it calls, otherwise GCC gets confused
template <typename T>
inline T serialToHost(const uint8_t *first)
{
    const uint8_t *next;
    return serialToHost<T>(first, next);
}


// copy serial buffer to host buffer


template <typename T>
inline const uint8_t *serialToHost(const uint8_t *first, T &dest)
{
    dest = serialToHost<T>(first);
    return first + sizeof(T);
}

template < typename It>
inline typename std::enable_if < (
    !std::is_integral<typename std::remove_pointer<It>::type>::value ||
    is_little_endian<It>::value ||
    std::is_same<It, uint8_t *>::value ||
    std::is_same<It, int8_t *>::value
), const uint8_t * >::type
serialToHost(const uint8_t *first, const uint8_t *last, It dest)
{
    std::copy(first, last, reinterpret_cast<uint8_t *>(dest));
    return last;
}

template < typename It>
inline typename std::enable_if < (
    is_big_endian<It>::value &&(
        std::is_same<It, uint16_t *>::value ||
        std::is_same<It, int16_t *>::value ||
        std::is_same<It, uint32_t *>::value ||
        std::is_same<It, int32_t *>::value
    )), const uint8_t * >::type
serialToHost(const uint8_t *first, const uint8_t *last, It dest)
{
    while (first < last)
    {
        *(dest++) = serialToHost<std::remove_pointer<It>>(first);
    }
    return dest;
}

template <typename T, std::size_t N>
inline const uint8_t *serialToHost(const uint8_t *first, T(&dest)[N])
{
    return serialToHost(first, first + N * sizeof(T), dest);
}

//template <typename T, std::size_t M, std::size_t N>
//inline const uint8_t *serialToHost(const uint8_t *&first, T(&dest)[M][N])
//{
//    return serialToHost(first, first + M * N * sizeof(T), dest);
//}


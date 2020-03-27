/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <cstdint>
#include <type_traits>


namespace endian
{
    constexpr static const auto test = 'ABCD'; // multi-character character implementation depends on endianness

	template <typename T>
    inline typename std::enable_if<sizeof(T) == 1, T>::type
	swap(T value)
    {
        return value;
    }

	template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value && sizeof(T) == 2, T>::type
	swap(T value)
    {
        return static_cast<T>(
                   (value << 8) |
                   ((value >> 8) & 0xFF));
    }

	template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value && sizeof(T) == 4, T>::type
	swap(T value)
    {
        return static_cast<T>(
                   (value << 24) |
                   ((value << 8) & 0x00FF0000) |
                   ((value >> 8) & 0x0000FF00) |
                   ((value >> 24) & 0x000000FF)); // right-shift of unsigned inserts undefined bits
    }

    template <typename InputIt, typename OutputIt>
    inline typename std::enable_if<std::is_pointer<InputIt>::value>::type
	swap(InputIt first, InputIt last, OutputIt dest)
    {
        while (first < last)
        {
            *(dest++) = endian::swap<typename std::remove_pointer<InputIt>::type>(*(first++));
        }
    }
}


template <typename T = void>
struct is_little_endian
{
    constexpr static bool value = true;//(endian::test == 0x41424344);
};

template <typename T = void>
struct is_big_endian
{
    constexpr static bool value = false;//(endian::test == 0x44434241);
};

template <typename T = void>
struct is_middle_endian
{
    constexpr static bool value = false;//(endian::test == 0x43434142);
};


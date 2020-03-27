/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once


#if !defined(_MSC_VER) || (_MSC_VER < 1800) // disable if MSVC 2013 or newer
#include <memory>

/*
 * Custom implementation of std::make_unique() to avoid requiring C++14.
 */

namespace std
{
    template <typename T, typename... Args>
    inline std::unique_ptr<T> make_unique(Args &&...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif


#if !defined(_MSC_VER) || (_MSC_VER < 1900) // disable if MSVC 2015 or newer
/*
 * Custom implementation of std::size() to avoid requiring C++17.
 */

namespace std
{
    template <typename T, std::size_t N>
    inline constexpr std::size_t size(const T(&)[N]) noexcept
    {
        return N;
    }
}
#endif

/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once


#include <common/ErrorHandling.hpp>

#if USE_EXCEPTIONS

#include <stdexcept>
//#include <sstream>


/// @brief Parent class for all exceptions.
class EException :
    public std::exception
#else
class EException
#endif
{
public:
//    virtual const char *what() const noexcept
//    {
//        return m_what.c_str();
//    }
//
//    virtual int code() const noexcept
//    {
//        return m_code;
//    }

protected:
    EException() = default;
//
//    mutable std::string m_what;
//    mutable int m_code;
};


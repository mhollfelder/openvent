/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <common/exception/EGenericException.hpp>


class EPlatform :
    public EGenericException
{
public:
    EPlatform(const char desc[] = "Platform Error", int code = 0, const char type[] = "Platform Exception") :
        EGenericException(desc, code, type)
    {}

    EXCEPTION_CODE(1)
};

/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#define USE_EXCEPTIONS 0

#if USE_EXCEPTIONS
using sr_t = void;
#define ENone

#define EXCEPTION_CODE(c)

#define RET_THROW throw
#define THROWS(c) c
#define RETURN return;

#else

using sr_t = int;
#define ENone 0

#define EXCEPTION_CODE(c) inline operator sr_t() const {return c;}

#define RET_THROW return
#define THROWS(c) {const sr_t RET = c if(RET) return RET;}
#define RETURN return ENone;

#endif


/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once


#include <chrono>
#include <impl/clock.h>


template <typename Rep, typename Period>
inline sr_t delay(std::chrono::duration<Rep, Period> rel_time)
{
	if (rel_time > std::chrono::microseconds(16383))
	{
		const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(rel_time).count();
		delay(ms);
	}
	else
	{
		const auto us = std::chrono::duration_cast<std::chrono::microseconds>(rel_time).count();
		delayMicroseconds(us);
	}
}

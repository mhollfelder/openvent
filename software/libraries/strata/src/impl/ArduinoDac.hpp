/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <platform/interfaces/access/IDac.hpp>


class ArduinoDac :
	public IDac
{
public:
	ArduinoDac();
	~ArduinoDac();

	void configureOutput(uint32_t channel, uint8_t flags);
	void setOutput(uint32_t channel, uint32_t value);
};


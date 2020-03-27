/**
 
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

#pragma once

#include <common/ErrorHandling.hpp>
#include <cstdint>


#define DAC_MODE_PWM    (1u << 0)
#define DAC_MODE_ANALOG (1u << 1)

 
class IDac
{
public:
  virtual void configureOutput(uint32_t channel, uint8_t flags) = 0;
  virtual void setOutput(uint32_t channel, uint32_t value) = 0;
};


extern IDac* defaultIDac;

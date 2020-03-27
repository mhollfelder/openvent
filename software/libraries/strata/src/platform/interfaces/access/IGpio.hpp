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
#include <universal/gpio_definitions.h>


/**
 * This is a generic interface for supporting access to GPIOs.
 * They can be identified either by a number, which is hardware-specific,
 * or by a predefined name that is independent of the hardware used,
 * as long as it is defined in the given bridge implementation.
 */
class IGpio
{
public:
    virtual ~IGpio() = default;

    /**
     * Configure a GPIO for pull-up/pull-down, drive-high, drive-low and/or input
     * @param id either a generic number or a predefined name
     * @param flags bit-wise setting of features
     */
    virtual sr_t configureGpio(uint16_t id, uint8_t flags) = 0;

    /**
     * Set a GPIO to logic high or low.
     * @param id either a generic number or a predefined name
     * @param state true for high and false for low
     */
    virtual sr_t setGpio(uint16_t id, bool state) = 0;

    /**
     * Get the current logic level of a GPIO (which should have been configured for input)
     * @param id either a generic number or a predefined name
     * @return true for high and false for low
     */
    virtual bool getGpio(uint16_t id) = 0;
};


extern IGpio* defaultIGpio;

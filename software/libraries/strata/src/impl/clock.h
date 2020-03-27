#ifndef CLOCK_H
#define CLOCK_H 1

#include "Arduino.h"


using clock_ticks_t = uint32_t;

static const clock_ticks_t clock_ticks_per_sec = 1000000;



/**< \brief Converts clock ticks into milli seconds
 *
 * \param ticks amount of clock ticks
 * \return equivalent time in milli seconds
 */
static inline unsigned int clock_ticks_to_milliseconds(clock_ticks_t ticks)
{
    return ticks * 1000 / clock_ticks_per_sec;
}

/**< \brief Converts clock ticks into micro seconds
 *
 * \param ticks amount of clock ticks
 * \return equivalent time in micro seconds
 */
static inline unsigned int clock_ticks_to_microseconds(clock_ticks_t ticks)
{
    return ticks * 1000000 / clock_ticks_per_sec;
}

/**< \brief Converts milli seconds into clock ticks
 *
 * \param duration time in milli seconds
 * \return equivalent time in clock ticks
 */
#define milliseconds_to_clock_ticks(duration) static_cast<clock_ticks_t>((clock_ticks_per_sec * (duration) + 999) / 1000)

/**< \brief Converts micro seconds into clock ticks
 *
 * \param duration time in micro seconds
 * \return equivalent time in clock ticks
 */
#define microseconds_to_clock_ticks(duration) static_cast<clock_ticks_t>((clock_ticks_per_sec * (duration) + 999999) / 1000000)

/** \brief Returns system timer value.
 *
 * \return system timer value, in clock ticks.
 */
static volatile inline clock_ticks_t clock_now(void)
{
    return micros();
}

/** \brief Returns the elapsed time between the current time and the time passed as parameter.
 *
 * \return the elapsed time, in clock ticks.
 */
static inline clock_ticks_t clock_elapsed_since(clock_ticks_t timepoint)
{
    return clock_now() - timepoint;
}

/** \brief Returns whether  elapsed time between the current time and the time passed as parameter.
 *
 * \return the elapsed time, in clock ticks.
 */
static inline bool clock_has_passed(clock_ticks_t timepoint)
{
    const clock_ticks_t diff = clock_now() - timepoint;
    return diff < (1u << (sizeof(clock_ticks_t) * 8 - 1));
}

#endif /* CLOCK_H */

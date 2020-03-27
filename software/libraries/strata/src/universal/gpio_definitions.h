/****************************************************************************\
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/
#ifndef GPIO_DEFINITIONS_H
#define GPIO_DEFINITIONS_H 1

/* Macros for GPIO ID formatting */
#define GPIO_ID(port, pin)              ((port << 8) | pin)
#define GPIO_PORT(id)                   (id >> 8)
#define GPIO_PIN(id)                    (id & 0xFF)


/* Macros for GPIO flag check */
#define STATIC_CHECK_GPIO_FLAGS(flags) \
enum { flags##__INVALID__PULL_UP_AND_PULL_DOWN = ((flags & GPIO_FLAG_PULL_UP) && (flags & GPIO_FLAG_PULL_DOWN)) ? 1/0 : 1,\
       flags##__INVALID__PULL_AND_DRIVE = (((flags & GPIO_FLAG_OUTPUT_DRIVE_HIGH) && (flags & GPIO_FLAG_PULL_UP)) || ((flags & GPIO_FLAG_OUTPUT_DRIVE_LOW) && (flags & GPIO_FLAG_PULL_DOWN))) ? 1/0 : 2,\
       flags##__INVALID__DRIVE_AND_INPUT = ((flags & GPIO_FLAG_INPUT_ENABLE) && ((flags & GPIO_FLAG_OUTPUT_DRIVE_LOW) || (flags & GPIO_FLAG_OUTPUT_DRIVE_HIGH))) ? 1/0 : 3}


/* Values for GPIO name */
#define GPIO_NAME_NONE                  0xFFFFu
#define GPIO_NAME                       0x8000u

#define GPIO_NAME_RESET                 (GPIO_NAME | 0x01u)
#define GPIO_NAME_STANDBY               (GPIO_NAME | 0x02u)
#define GPIO_NAME_TRIGGER               (GPIO_NAME | 0x03u)
#define GPIO_NAME_STATUS                (GPIO_NAME | 0x04u)

#define GPIO_NAME_RESET_0               GPIO_NAME_RESET
#define GPIO_NAME_STATUS_0              GPIO_NAME_STATUS
#define GPIO_NAME_RESET_1               (GPIO_NAME | 0x05u)
#define GPIO_NAME_STATUS_1              (GPIO_NAME | 0x06u)


/* Values for GPIO config flags */
#define GPIO_FLAG_OUTPUT_INITIAL_HIGH   (1u << 0)   // For output, set initial output value to 1 (otherwise it will be 0)
#define GPIO_FLAG_OUTPUT_DRIVE_LOW      (1u << 1)   // For output, drive a low signal
#define GPIO_FLAG_OUTPUT_DRIVE_HIGH     (1u << 2)   // For output, drive a high signal
#define GPIO_FLAG_INPUT_ENABLE          (1u << 3)   // Enable to read in signal
#define GPIO_FLAG_PULL_UP               (1u << 4)   // If the signal is not driven, pull it to high
#define GPIO_FLAG_PULL_DOWN             (1u << 5)   // If the signal is not driven, pull it to low


/* Values for GPIO config modes */
#define GPIO_MODE_INPUT                         (GPIO_FLAG_INPUT_ENABLE)
#define GPIO_MODE_INPUT_PULL_DOWN               (GPIO_FLAG_INPUT_ENABLE | GPIO_FLAG_PULL_DOWN)
#define GPIO_MODE_INPUT_PULL_UP                 (GPIO_FLAG_INPUT_ENABLE | GPIO_FLAG_PULL_UP)
#define GPIO_MODE_OUTPUT_OPEN_DRAIN             (GPIO_FLAG_OUTPUT_DRIVE_LOW)
#define GPIO_MODE_OUTPUT_OPEN_DRAIN_PULL_UP     (GPIO_FLAG_OUTPUT_DRIVE_LOW | GPIO_FLAG_PULL_UP)
#define GPIO_MODE_OUTPUT_OPEN_SOURCE            (GPIO_FLAG_OUTPUT_DRIVE_HIGH)
#define GPIO_MODE_OUTPUT_OPEN_SOURCE_PULL_DOWN  (GPIO_FLAG_OUTPUT_DRIVE_HIGH | GPIO_FLAG_PULL_DOWN)
#define GPIO_MODE_OUTPUT_PUSH_PULL              (GPIO_FLAG_OUTPUT_DRIVE_LOW | GPIO_FLAG_OUTPUT_DRIVE_HIGH)

#endif /* GPIO_DEFINITIONS_H */

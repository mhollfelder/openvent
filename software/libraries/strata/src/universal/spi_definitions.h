/****************************************************************************\
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/
#ifndef SPI_DEFINITIONS_H
#define SPI_DEFINITIONS_H 1

/**
 * SPI device configuration fields
 *
 *  - SPI_CPOL determines the polarity of the cck
 *      - SPI_CPOL = '0' : clock idles at 0. The leading edge is a rising edge,
 *      and the trailing edge is a falling edge
 *      - SPI_CPOL = '1' : clock idles at 1. The leading edge is a falling edge,
 *      and the trailing edge is a rising edge
 *
 *  - SPI_CPHA determines the timing of the data bits relative to the clock pulses
 *      - SPI_CPHA = '0' :
 *          - At MOSI, data changes on the trailing edge of the clock cycle
 *          (i.e. data is hold valid until the trailing edge of the following clock cycle)
 *          - At MISO, data is captured on the leading edge of the clock cycle
 *      - SPI_CPHA = '1' :
 *          - At MOSI, data changes on the leading edge of the clock cycle
 *          (i.e. data is hold valid until the leading edge of the following clock cycle)
 *          - At MISO, data is captured on the trailing edge of the clock cycle
 *
 */
#define SPI_CPOL            (1u << 0)   ///< Clock Polarity CPOL = 1 (otherwise, CPOL = 0)
#define SPI_CPHA            (1u << 1)   ///< Clock Phase CPHA = 1 (otherwise, CPHA = 0)
#define SPI_CS_HIGH_ACTIVE  (1u << 2)   ///< 0: chip select is low active, 1: chip select is high active
#define SPI_LSB_FIRST       (1u << 3)   ///< 0: Data is transmitted MSB first, 1: Data is transmitted LSB first
#define SPI_3_WIRE          (1u << 4)   ///< 0: normal 4-Wire operation, 1: 3 Wire operation (this short both data lanes, so make sure this is supported by the device)


/**
 * Common SPI operational modes
 */
#define SPI_MODE_0          (0 | 0)                 ///< Clock Polarity CPOL = 0, Clock Phase CPHA = 0
#define SPI_MODE_1          (0 | SPI_CPHA)          ///< Clock Polarity CPOL = 0, Clock Phase CPHA = 1
#define SPI_MODE_2          (SPI_CPOL | 0)          ///< Clock Polarity CPOL = 1, Clock Phase CPHA = 0
#define SPI_MODE_3          (SPI_CPOL | SPI_CPHA)   ///< Clock Polarity CPOL = 1, Clock Phase CPHA = 1


#endif /* SPI_DEFINITIONS_H */

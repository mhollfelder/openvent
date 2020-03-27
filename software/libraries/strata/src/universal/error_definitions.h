/****************************************************************************\
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/
#ifndef ERROR_DEFINITIONS_H
#define ERROR_DEFINITIONS_H 1

#define E_SUCCESS                   0x00
#define E_FAILED                    0x01
#define E_INVALID_PARAMETER         0x02
#define E_INVALID_SIZE              0x03
#define E_UNEXPECTED_VALUE          0x04
#define E_OVERFLOW                  0x05
#define E_TIMEOUT                   0x06

#define E_NOT_IMPLEMENTED           0x10
#define E_NOT_AVAILABLE             0x11
#define E_NOT_ALLOWED               0x12
#define E_NOT_INITIALIZED           0x13
#define E_NOT_CONFIGURED            0x14


#define E_FW_LOAD_FAILED            0x70
#define E_FW_TIMEOUT_SETUP          0x71
#define E_FW_FUNCTION_ERROR         0x72
#define E_FW_TIMEOUT_COMPLETION     0x73
#define E_FW_UNEXPECTED_RETURN      0x74
#define E_FW_FUNCTION_NOT_STARTED   0x75
#define E_FW_FUNCTION_FAILED        0x76


#endif /* ERROR_DEFINITIONS_H */

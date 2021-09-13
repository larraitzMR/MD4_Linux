/******************************************************************************
  * @attention
  *
  * COPYRIGHT 2019 STMicroelectronics, all rights reserved
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
******************************************************************************/

/** @file
 *
 *  @author ST Microelectronics
 *
 *  @brief 
 *
 */

/** @addtogroup Application
  * @{
  */
/** @addtogroup PC_Communication
  * @{
  */

#if defined(POSIX)

//
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "../../inc/stuhfl_dl.h"
#include "../../inc/platform/stuhfl_bl_posix.h"
#include "../../inc/stuhfl_err.h"
#include "../../inc/stuhfl_log.h"

static STUHFL_T_ParamTypeConnectionRdTimeout rdComTimeout = 2000;
static STUHFL_T_ParamTypeConnectionWrTimeout wrComTimeout = 1000;

struct termios oldtio = { 0 };

#define TRACE_BL_START()        { STUHFL_F_LogClear(STUHFL_D_LOG_LEVEL_TRACE_BL); }
#define TRACE_BL(...)           { STUHFL_F_LogAppend(STUHFL_D_LOG_LEVEL_TRACE_BL, __VA_ARGS__); STUHFL_F_LogFlush(STUHFL_D_LOG_LEVEL_TRACE_BL); }

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_Connect_Posix(STUHFL_T_DEVICE_CTX *device, char* port, uint32_t br)
{
    HANDLE h;
    struct termios newtio = { 0 };
    STUHFL_T_RET_CODE ret = STUHFL_ERR_GENERIC;

    h = open(port, O_RDWR | O_NOCTTY);

    // Return error if invalid handle
    if (h == INVALID_HANDLE_VALUE) {
        return (ret = STUHFL_ERR_IO);
    }

    // save current settings ..
    tcgetattr((int)h, &oldtio);
    newtio = oldtio;

    // IO Speed
    speed_t ioSpeed = (speed_t)B115200;
    switch (br) {
    case 57600: ioSpeed = B57600; break;
    case 115200: ioSpeed = B115200; break;
    case 230400: ioSpeed = B230400; break;
    case 460800: ioSpeed = B460800; break;
    case 500000: ioSpeed = B500000; break;
    case 576000: ioSpeed = B576000; break;
    case 921600: ioSpeed = B921600; break;
    case 1000000: ioSpeed = B1000000; break;
    case 1152000: ioSpeed = B1152000; break;
    case 1500000: ioSpeed = B1500000; break;
    case 2000000: ioSpeed = B2000000; break;
    case 2500000: ioSpeed = B2500000; break;
    case 3000000: ioSpeed = B3000000; break;
    case 3500000: ioSpeed = B3500000; break;
    case 4000000: ioSpeed = B4000000; break;
    default:
        break;
    }
    cfsetospeed(&newtio, (speed_t)ioSpeed);
    cfsetispeed(&newtio, (speed_t)ioSpeed);

    // setup for raw communication
    cfmakeraw(&newtio);
    // 8N1, No HW flow control, ..
    newtio.c_cflag &= (unsigned int)~CSTOPB;        // Warning removal
    newtio.c_cflag &= (unsigned int)~CRTSCTS;       // Warning removal
    newtio.c_cflag |= (CLOCAL | CREAD);

    // TimeOut
    newtio.c_cc[VMIN] = 0;
    newtio.c_cc[VTIME] = 0;

    // apply settings to terminal
    tcflush(h, TCIOFLUSH);
    if (0 != tcsetattr((int)h, TCSANOW, &newtio)) {
        return (ret = STUHFL_ERR_IO);
    }

    // finally assign handle as device context
    *device = (STUHFL_T_DEVICE_CTX)h;
    return (ret = STUHFL_ERR_NONE);
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_Reset_Posix(STUHFL_T_DEVICE_CTX *device, STUHFL_T_RESET resetType)
{
    if (resetType == STUHFL_D_RESET_TYPE_CLEAR_COMM) {
        // Abort all outstandig r/w operations and clear buffers
        tcflush((int)*device, TCIOFLUSH);
        return STUHFL_ERR_NONE;
    }
    return STUHFL_ERR_PARAM;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_Disconnect_Posix(STUHFL_T_DEVICE_CTX *device)
{
    //
    if ((*device == (void*)INVALID_HANDLE_VALUE) || (*device == NULL)) {
        return STUHFL_ERR_PARAM;
    }
    tcsetattr((int)device, TCSANOW, &oldtio);
    close((int)*device);
    *device = NULL;
    return STUHFL_ERR_NONE;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_SndRaw_Posix(STUHFL_T_DEVICE_CTX *device, uint8_t *data, uint16_t dataLen)
{
    //
    if ((*device == (void*)INVALID_HANDLE_VALUE) || (*device == NULL)) {
        return STUHFL_ERR_PARAM;
    }

    //
    STUHFL_T_RET_CODE ret = STUHFL_F_Reset_Posix(device, STUHFL_D_RESET_TYPE_CLEAR_COMM);
    if (ret != STUHFL_ERR_NONE) {
        return ret;
    }

    //
    ssize_t     dwWritten = 0;
    bool        success = false;

    // write operation completed successfully.
    dwWritten = write((int)*device, data, dataLen);
    if (dataLen == dwWritten) {
        success = true;
    }

    if (!success) {
        ret = STUHFL_ERR_IO;
    }
    return ret;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_RcvRaw_Posix(STUHFL_T_DEVICE_CTX *device, uint8_t *data, uint16_t *dataLen)
{
    //
    if ((*device == (void*)INVALID_HANDLE_VALUE) || (*device == NULL)) {
        return STUHFL_ERR_PARAM;
    }

    bool            success = false;
    ssize_t         dwBytesRead = 0;
    uint32_t        nNumberOfBytesToRead = *dataLen;

    // clear upfront
    *dataLen = 0;

    //
    int nBytesAvailable = 0;
    STUHFL_T_ParamTypeConnectionRdTimeout timeout = rdComTimeout * 10;
    // check if data is available
    while (((--timeout) > 0) && (nBytesAvailable < nNumberOfBytesToRead)) {
        ioctl((int)*device, FIONREAD, &nBytesAvailable);
        usleep(100);
    }
    // last try before return ..
    if (timeout == 0) {
        ioctl((int)*device, FIONREAD, &nBytesAvailable);
        if (nBytesAvailable < nNumberOfBytesToRead) {
            return STUHFL_ERR_IO;
        }
    }
    // finally read available data
    dwBytesRead = read((int)*device, data, nNumberOfBytesToRead);

    //
    *dataLen = (uint16_t)dwBytesRead;
    if (nNumberOfBytesToRead == dwBytesRead) {
        success = true;
    }

    return success ? STUHFL_ERR_NONE : (STUHFL_T_RET_CODE)errno;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_SetDTR_Posix(STUHFL_T_DEVICE_CTX *device, uint8_t dtrValue)
{
    //
    if ((*device == (void*)INVALID_HANDLE_VALUE) || (*device == NULL)) {
        return STUHFL_ERR_PARAM;
    }

    //
    int status;
    if (ioctl((int)*device, TIOCMGET, &status) == -1) {
        return STUHFL_ERR_IO;
    }
    if (dtrValue) {
        status |= TIOCM_DTR;    /* turn on DTR */
    } else {
        status &= ~TIOCM_DTR;    /* turn off DTR */
    }
    if (ioctl((int)*device, TIOCMSET, &status) == -1) {
        return STUHFL_ERR_IO;
    }
    return STUHFL_ERR_NONE;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_GetDTR_Posix(STUHFL_T_DEVICE_CTX *device, uint8_t *dtrValue)
{
    //
    if ((*device == (void*)INVALID_HANDLE_VALUE) || (*device == NULL)) {
        return STUHFL_ERR_PARAM;
    }

    //
    int status;
    if (ioctl((int)*device, TIOCMGET, &status) == -1) {
        return STUHFL_ERR_IO;
    }
    *dtrValue = status & TIOCM_DTR;
    return STUHFL_ERR_NONE;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_SetRTS_Posix(STUHFL_T_DEVICE_CTX *device, uint8_t rtsValue)
{
    //
    if ((*device == (void*)INVALID_HANDLE_VALUE) || (*device == NULL)) {
        return STUHFL_ERR_PARAM;
    }

    //
    int status;
    if (ioctl((int)*device, TIOCMGET, &status) == -1) {
        return STUHFL_ERR_IO;
    }
    if (rtsValue) {
        status |= TIOCM_RTS;    /* turn on RTS */
    } else {
        status &= ~TIOCM_RTS;    /* turn off RTS */
    }
    if (ioctl((int)*device, TIOCMSET, &status) == -1) {
        return STUHFL_ERR_IO;
    }
    return STUHFL_ERR_NONE;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_GetRTS_Posix(STUHFL_T_DEVICE_CTX *device, uint8_t *rtsValue)
{
    //
    if ((*device == (void*)INVALID_HANDLE_VALUE) || (*device == NULL)) {
        return STUHFL_ERR_PARAM;
    }

    //
    int status;
    if (ioctl((int)*device, TIOCMGET, &status) == -1) {
        return STUHFL_ERR_IO;
    }
    *rtsValue = status & TIOCM_RTS;
    return STUHFL_ERR_NONE;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_SetTimeouts_Posix(STUHFL_T_DEVICE_CTX *device, uint32_t rdTimeout, uint32_t wrTimeout)
{
    ////
    //if ((*device == (void*)INVALID_HANDLE_VALUE) || (*device == NULL)) {
    //    return STUHFL_ERR_PARAM;
    //}

    //// convert ms to tenth of seconds
    //rdTimeout = MS_TO_TENTHS_OF_SEC(rdTimeout);
    //wrTimeout = MS_TO_TENTHS_OF_SEC(wrTimeout);

    //struct termios  tio;
    //tcgetattr((int)*device, &tio);

    //// TimeOut
    //tio.c_cc[VMIN] = 0;
    //tio.c_cc[VTIME] = (cc_t)rdTimeout;


    //tcflush((int)*device, TCIFLUSH);
    //if (0 != tcsetattr((int)*device, TCSANOW, &tio)) {
    //    return STUHFL_ERR_IO;
    //}

    rdComTimeout = rdTimeout;
    wrComTimeout = wrTimeout;
    return STUHFL_ERR_NONE;
}

// --------------------------------------------------------------------------
STUHFL_T_RET_CODE STUHFL_F_GetTimeouts_Posix(STUHFL_T_DEVICE_CTX *device, uint32_t *rdTimeout, uint32_t *wrTimeout)
{
    //// convert reply to ms
    //*rdTimeout = TENTHS_OF_SEC_TO_MS(rdComTimeout);
    //*wrTimeout = TENTHS_OF_SEC_TO_MS(wrComTimeout);

    *rdTimeout = rdComTimeout;
    *wrTimeout = wrComTimeout;
    return STUHFL_ERR_NONE;
}

#endif

/**
  * @}
  */
/**
  * @}
  */

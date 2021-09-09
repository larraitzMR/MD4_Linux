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


//
#if !defined __STUHFL_PL_H
#define __STUHFL_PL_H

//
#include "stuhfl.h"

//
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

STUHFL_T_RET_CODE STUHFL_F_Connect_Dispatcher(STUHFL_T_DEVICE_CTX *device, uint8_t *sndBuffer, uint16_t sndBufferLen, uint8_t *rcvBuffer, uint16_t rcvBufferLen);
STUHFL_T_RET_CODE STUHFL_F_Disconnect_Dispatcher(STUHFL_T_DEVICE_CTX device);
STUHFL_T_RET_CODE STUHFL_F_Reset_Dispatcher(STUHFL_T_DEVICE_CTX device, STUHFL_T_RESET resetType);
STUHFL_T_RET_CODE STUHFL_F_Snd_Dispatcher(STUHFL_T_DEVICE_CTX device, uint16_t cmd, uint16_t status, uint8_t *data, uint16_t dataLen);
STUHFL_T_RET_CODE STUHFL_F_Rcv_Dispatcher(STUHFL_T_DEVICE_CTX device, uint8_t *data, uint16_t *dataLen);
STUHFL_T_RET_CODE STUHFL_F_SndRaw_Dispatcher(STUHFL_T_DEVICE_CTX device, uint8_t *data, uint16_t dataLen);
STUHFL_T_RET_CODE STUHFL_F_RcvRaw_Dispatcher(STUHFL_T_DEVICE_CTX device, uint8_t *data, uint16_t *dataLen);

STUHFL_T_RET_CODE STUHFL_F_SetParam_Dispatcher(STUHFL_T_DEVICE_CTX device, STUHFL_T_PARAM param, STUHFL_T_PARAM_VALUE value);
STUHFL_T_RET_CODE STUHFL_F_GetParam_Dispatcher(STUHFL_T_DEVICE_CTX device, STUHFL_T_PARAM param, STUHFL_T_PARAM_VALUE value);

uint8_t *STUHFL_F_Get_SndPayloadPtr(void);

uint16_t STUHFL_F_Get_RcvCmd(void);
STUHFL_T_RET_CODE STUHFL_F_Get_RcvStatus(void);
uint8_t *STUHFL_F_Get_RcvPayloadPtr(void);



//
#define STUHFL_COMM_PREAMBLE_MODE_SIZE                 2
#define STUHFL_COMM_PREAMBLE_ID_SIZE                   2
#define STUHFL_COMM_STATUS_SIZE                        2
#define STUHFL_COMM_CMD_SIZE                           2
#define STUHFL_COMM_PAYLOAD_LENGTH_SIZE                2

#define STUHFL_COMM_PREAMBLE_MODE_POS                  0U
#define STUHFL_COMM_PREAMBLE_ID_POS                    2U//STUHFL_COMM_PREAMBLE_MODE_SIZE
#define STUHFL_COMM_STATUS_POS                         4U//(STUHFL_COMM_PREAMBLE_ID_POS + STUHFL_COMM_PREAMBLE_ID_SIZE)
#define STUHFL_COMM_CMD_POS                            6U//(STUHFL_COMM_STATUS_POS + STUHFL_COMM_STATUS_SIZE)
#define STUHFL_COMM_PAYLOAD_LENGTH_POS                 8U//(STUHFL_COMM_CMD_POS + STUHFL_COMM_CMD_SIZE)
#define STUHFL_COMM_PAYLOAD_POS                        10U//(STUHFL_COMM_PAYLOAD_LENGTH_POS + STUHFL_COMM_PAYLOAD_LENGTH_SIZE)
#define STUHFL_COMM_CHECKSUM_POS(payloadLength)        (STUHFL_COMM_PAYLOAD_POS + (payloadLength))



#define STUHFL_COMM_GET_PREAMBLE_MODE(buf)             (uint16_t)((((buf)[STUHFL_COMM_PREAMBLE_MODE_POS ]) << 8 ) | (((buf)[STUHFL_COMM_PREAMBLE_MODE_POS  + 1]) & 0xFF))
#define STUHFL_COMM_GET_PREAMBLE_ID(buf)               (uint16_t)((((buf)[STUHFL_COMM_PREAMBLE_ID_POS   ]) << 8 ) | (((buf)[STUHFL_COMM_PREAMBLE_ID_POS    + 1]) & 0xFF))
#define STUHFL_COMM_GET_STATUS(buf)                    (uint16_t)((((buf)[STUHFL_COMM_STATUS_POS        ]) << 8 ) | (((buf)[STUHFL_COMM_STATUS_POS         + 1]) & 0xFF))
#define STUHFL_COMM_GET_CMD(buf)                       (uint16_t)((((buf)[STUHFL_COMM_CMD_POS           ]) << 8 ) | (((buf)[STUHFL_COMM_CMD_POS            + 1]) & 0xFF))
#define STUHFL_COMM_GET_PAYLOAD_LENGTH(buf)            (uint16_t)((((buf)[STUHFL_COMM_PAYLOAD_LENGTH_POS]) << 8 ) | (((buf)[STUHFL_COMM_PAYLOAD_LENGTH_POS + 1]) & 0xFF))
#define STUHFL_COMM_GET_PAYLOAD_PTR(buf)               ((buf) + STUHFL_COMM_PAYLOAD_POS)

#define STUHFL_COMM_SET_PREAMBLE_MODE(buf, m)          do { (buf)[STUHFL_COMM_PREAMBLE_MODE_POS   ] = (uint8_t)((m) >> 8); (buf)[STUHFL_COMM_PREAMBLE_MODE_POS  + 1] = (uint8_t)((m) & 0xFF); } while ( 0 )
#define STUHFL_COMM_SET_PREAMBLE_ID(buf, i)            do { (buf)[STUHFL_COMM_PREAMBLE_ID_POS     ] = (uint8_t)((i) >> 8); (buf)[STUHFL_COMM_PREAMBLE_ID_POS    + 1] = (uint8_t)((i) & 0xFF); } while ( 0 )
#define STUHFL_COMM_SET_STATUS(buf, s)                 do { (buf)[STUHFL_COMM_STATUS_POS          ] = (uint8_t)((s) >> 8); (buf)[STUHFL_COMM_STATUS_POS         + 1] = (uint8_t)((s) & 0xFF); } while ( 0 )
#define STUHFL_COMM_SET_CMD(buf, c)                    do { (buf)[STUHFL_COMM_CMD_POS             ] = (uint8_t)((c) >> 8); (buf)[STUHFL_COMM_CMD_POS            + 1] = (uint8_t)((c) & 0xFF); } while ( 0 )
#define STUHFL_COMM_SET_PAYLOAD_LENGTH(buf, l)         do { (buf)[STUHFL_COMM_PAYLOAD_LENGTH_POS  ] = (uint8_t)((l) >> 8); (buf)[STUHFL_COMM_PAYLOAD_LENGTH_POS + 1] = (uint8_t)((l) & 0xFF); } while ( 0 )


#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __STUHFL_PL_H

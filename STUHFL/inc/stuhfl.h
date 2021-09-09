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
#if !defined __STUHFL_H
#define __STUHFL_H

//
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
//
#include "stuhfl_platform.h"

// --------------------------------------------------------------------------
// Prefix explanation
// --------------------------------------------------------------------------
// STUHFL_T_                            .. STUHLF typedef
// STUHFL_D_                            .. STUHLF define
// STUHFL_E_                            .. STUHLF enum
// STUHFL_F_                            .. STUHLF function
// STUHFL_O_                            .. STUHLF object
// STUHFL_P_                            .. STUHLF pointer





//
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

// --------------------------------------------------------------------------



// --------------------------------------------------------------------------
#ifdef WIN64
typedef uint64_t                                STUHFL_T_POINTER2UINT;
#else
typedef uint32_t                                STUHFL_T_POINTER2UINT;
#endif

typedef uint32_t                                STUHFL_T_RET_CODE;
typedef uint32_t                                STUHFL_T_RESET;
typedef uint32_t                                STUHFL_T_VERSION;
typedef void*                                   STUHFL_T_DEVICE_CTX;
typedef void*                                   STUHFL_T_PARAM_VALUE;
typedef void*                                   STUHFL_T_PARAM_INFO;
typedef uint32_t                                STUHFL_T_PARAM;
typedef uint32_t                                STUHFL_T_PARAM_CNT;
typedef uint32_t                                STUHFL_T_TYPE;
typedef uint16_t                                STUHFL_T_CMD;
typedef void*                                   STUHFL_T_CMD_SND_PARAMS;
typedef void*                                   STUHFL_T_CMD_RCV_DATA;
typedef uint8_t                                 STUHFL_T_TAG;
typedef uint8_t                                 STUHFL_T_LEN8;
typedef uint16_t                                STUHFL_T_LEN16;
#define STUHFL_D_T_LEN_LENGTH(l)                  (uint32_t)((l & 0x80) ? sizeof(STUHFL_T_LEN16) : sizeof(STUHFL_T_LEN8))
#define STUHFL_D_T_LEN_MAX_SIZE                   sizeof(STUHFL_T_LEN16)

// - Parameter Types & Keys -----------------------------------------------
#define STUHFL_D_TYPE_MASK                  0xFF000000
#define STUHFL_D_KEY_MASK                   0x00FFFFFF

// TYPES
#define STUHFL_PARAM_TYPE_CONNECTION            0x01000000
#define STUHFL_PARAM_TYPE_ST25RU3993            0x02000000

// KEYS CONNECTION
#define STUHFL_KEY_PORT                   0x00000001
#define STUHFL_KEY_BR                     0x00000002
#define STUHFL_KEY_RD_TIMEOUT_MS          0x00000003
#define STUHFL_KEY_WR_TIMEOUT_MS          0x00000004
#define STUHFL_KEY_DTR                    0x00000005
#define STUHFL_KEY_RTS                    0x00000006


// KEYS ST25RU3993
#define STUHFL_KEY_VERSION_FW             0x00000001
#define STUHFL_KEY_VERSION_HW             0x00000002
// - HW Cfg
#define STUHFL_KEY_RWD_REGISTER           0x00000010
#define STUHFL_KEY_RWD_CONFIG             0x00000011
// - Power
#define STUHFL_KEY_RWD_ANTENNA_POWER      0x00000012
// - Freq
#define STUHFL_KEY_RWD_FREQ_RSSI          0x00000013          /* DEPRECATED */
#define STUHFL_KEY_RWD_FREQ_REFLECTED     0x00000014          /* DEPRECATED */
#define STUHFL_KEY_RWD_FREQ_PROFILE       0x00000015          /* DEPRECATED */
#define STUHFL_KEY_RWD_FREQ_PROFILE_ADDTOCUSTOM    0x00000016  /* DEPRECATED */
#define STUHFL_KEY_RWD_FREQ_PROFILE_INFO  0x00000017          /* DEPRECATED */
#define STUHFL_KEY_RWD_FREQ_HOP           0x00000018
#define STUHFL_KEY_RWD_FREQ_LBT           0x00000019
#define STUHFL_KEY_RWD_FREQ_CONTINUOUS_MODULATION      0x0000001A
#define STUHFL_KEY_RWD_TXRX_CFG           0x0000001B
#define STUHFL_KEY_RWD_POWER_AMPLIFIER_CFG             0x0000001C
#define STUHFL_KEY_RWD_CHANNEL_LIST       0x0000001D
//- Gen2 SW Cfg
#define STUHFL_KEY_RWD_GEN2_PROTOCOL_CFG   0x00000020
#define STUHFL_KEY_RWD_GEN2_INVENTORY_CFG  0x00000021
#define STUHFL_KEY_RWD_GEN2_TIMINGS        0x00000022
//- Gb29768 SW Cfg
#define STUHFL_KEY_RWD_GB29768_PROTOCOL_CFG        0x00000028
#define STUHFL_KEY_RWD_GB29768_INVENTORY_CFG       0x00000029
// - RX Filter / Calibration
#define STUHFL_KEY_GEN2_RX_FILTER         0x0000002A
#define STUHFL_KEY_GB29768_RX_FILTER      0x0000002B
#define STUHFL_KEY_GEN2_FILTER_CALIBRATION     0x0000002C
#define STUHFL_KEY_GB29768_FILTER_CALIBRATION  0x0000002D

// - Tuner
#define STUHFL_KEY_TUNING                 0x00000030          /* DEPRECATED */
#define STUHFL_KEY_TUNING_TABLE_ENTRY     0x00000031          /* DEPRECATED */
#define STUHFL_KEY_TUNING_TABLE_DEFAULT   0x00000032          /* DEPRECATED */
#define STUHFL_KEY_TUNING_TABLE_SAVE      0x00000033          /* DEPRECATED */
#define STUHFL_KEY_TUNING_TABLE_EMPTY     0x00000034          /* DEPRECATED */
#define STUHFL_KEY_TUNING_TABLE_INFO      0x00000035          /* DEPRECATED */
//#define STUHFL_KEY_TUNE                   0x00000036
#define STUHFL_KEY_TUNING_CAPS            0x00000037
#define STUFHL_KEY_TEMPERATURE			  0x00000038
#define STUFHL_KEY_PWR_DETECTED			  0x00000039
#define STUFHL_KEY_ATTENUATOR			  0x00000040
#define STUHFL_KEY_ANTENNA_SEQ			  0x00000041
#define STUFHL_KEY_PWR_DETECTED_DBM		  0x00000042
#define STUFHL_KEY_PWR_DET_CALIBRATION	  0x00000043
#define STUFHL_KEY_ATT_PWR_CALIBRATION	  0x00000044
#define STUFHL_KEY_ATT_PWR_CALIBRATION_STATE	0x00000045
#define STUFHL_KEY_PWR_DET_CALIBRATION_ENABLE	0x00000046

// - Gen2
// - Iso6B
// - GB29768

// Command Group
#define STUHFL_CG_GENERIC                                   0x00
#define STUHFL_CG_DL                                        0x01
#define STUHFL_CG_SL                                        0x02
#define STUHFL_CG_AL                                        0x03
#define STUHFL_CG_TS                                        0x04
// --------------------------------------------------------------------------
// Command Code - Generic
#define STUHFL_CC_GET_VERSION                               0x00
#define STUHFL_CC_GET_INFO                                  0x01
#define STUHFL_CC_UPGRADE                                   0x02
#define STUHFL_CC_ENTER_BOOTLOADER                          0x03
#define STUHFL_CC_REBOOT                                    0x04
#define STUFHL_CC_GET_RD_VERSION                            0x05
// Command Code - Unit Layer
#define STUHFL_CC_GET_PARAM                                 0x00
#define STUHFL_CC_SET_PARAM                                 0x01
#define STUHFL_CC_TUNE                                      0x02
#define STUHFL_CC_TUNE_CHANNEL                              0x03
// Command Code - Session Layer
// Command Code - Activity Layer
#define STUHFL_CC_INVENTORY_START                           0x00
#define STUHFL_CC_INVENTORY_STOP                            0x01
#define STUHFL_CC_INVENTORY_DATA                            0x02
#ifdef USE_INVENTORY_EXT
#define STUHFL_CC_INVENTORY_START_W_SLOT_STATISTICS         0x03
#endif

#define STUHFL_CC_GEN2_INVENTORY                            0x03
#define STUHFL_CC_GEN2_SELECT                               0x04
#define STUHFL_CC_GEN2_READ                                 0x05
#define STUHFL_CC_GEN2_WRITE                                0x06
#define STUHFL_CC_GEN2_LOCK                                 0x07
#define STUHFL_CC_GEN2_KILL                                 0x08
#define STUHFL_CC_GEN2_GENERIC_CMD                          0x09
#define STUHFL_CC_GEN2_QUERY_MEASURE_RSSI                   0x0A
#define STUHFL_CC_GEN2_BLOCKWRITE                           0x0B

#define STUHFL_CC_GB29768_INVENTORY                         0x13
#define STUHFL_CC_GB29768_SORT                              0x14
#define STUHFL_CC_GB29768_READ                              0x15
#define STUHFL_CC_GB29768_WRITE                             0x16
#define STUHFL_CC_GB29768_LOCK                              0x17
#define STUHFL_CC_GB29768_KILL                              0x18
#define STUHFL_CC_GB29768_GENERIC_CMD                       0x19
#define STUHFL_CC_GB29768_ERASE                             0x1A


// TLV TAGs - Generic
#define STUHFL_TAG_VERSION_FW                               0x01
#define STUHFL_TAG_VERSION_HW                               0x02
#define STUHFL_TAG_INFO_FW                                  0x03
#define STUHFL_TAG_INFO_HW                                  0x04
// TLV TAGs - Unit Layer
#define STUHFL_TAG_REGISTER                                 0x01
#define STUHFL_TAG_RWD_CONFIG                               0x02
#define STUHFL_TAG_ANTENNA_POWER                            0x03
#define STUHFL_TAG_FREQ_RSSI                                0x04
#define STUHFL_TAG_FREQ_REFLECTED                           0x05
#define STUHFL_TAG_FREQ_PROFILE                             0x06
#define STUHFL_TAG_FREQ_PROFILE_ADDTOCUSTOM                  0x07
#define STUHFL_TAG_FREQ_PROFILE_INFO                        0x08
#define STUHFL_TAG_FREQ_HOP                                 0x09
#define STUHFL_TAG_FREQ_LBT                                 0x0A
#define STUHFL_TAG_FREQ_CONTINUOUS_MODULATION                            0x0B
#define STUHFL_TAG_GEN2_PROTOCOL_CFG                         0x0C
#define STUHFL_TAG_GB29768_PROTOCOL_CFG                      0x0D
#define STUHFL_TAG_TXRX_CFG                                 0x0E
#define STUHFL_TAG_POWER_AMPLIFIER_CFG                                   0x0F
#define STUHFL_TAG_GEN2_INVENTORY_CFG                        0x10
#define STUHFL_TAG_GB29768_INVENTORY_CFG                     0x11
#define STUHFL_TAG_TUNING                                   0x12
#define STUHFL_TAG_TUNING_TABLE_DEFAULT                     0x13
#define STUHFL_TAG_TUNING_TABLE_ENTRY                       0x14
#define STUHFL_TAG_TUNING_TABLE_INFO                        0x15
#define STUHFL_TAG_TUNING_TABLE_SAVE                        0x16
#define STUHFL_TAG_TUNING_TABLE_EMPTY                       0x17
#define STUHFL_TAG_TUNE                                     0x18
#define STUHFL_TAG_GEN2_TIMINGS                             0x19
#define STUHFL_TAG_TUNE_CHANNEL                             0x20
#define STUHFL_TAG_TUNING_CAPS                              0x21
#define STUHFL_TAG_CHANNEL_LIST                             0x22
#define STUHFL_TAG_GEN2_RX_FILTER                           0x33
#define STUHFL_TAG_GB29768_RX_FILTER                        0x34
#define STUHFL_TAG_GEN2_FILTER_CALIBRATION                  0x35
#define STUHFL_TAG_GB29768_FILTER_CALIBRATION               0x36
#define STUHFL_TAG_TEMPERATURE								0x37
#define STUHFL_TAG_PWR_DETECTED								0x38
#define STUHFL_TAG_ATTENUATOR								0x39
#define STUHFL_TAG_ANTENNA_SEQ								0x40
#define STUHFL_TAG_PWR_DETECTED_DBM							0x41
#define STUFHL_TAG_PWR_DET_CALIBRATION						0x42
#define STUFHL_TAG_ATT_PWR_CALIBRATION						0x43
#define STUFHL_TAG_ATT_PWR_CALIBRATION_STATE				0x44
#define STUFHL_TAG_PWR_DET_CALIBRATION_ENABLE				0x45

// TLV TAGs - Session Layer
#define STUHFL_TAG_GEN2_INVENTORY_OPTION                    0x01
#define STUHFL_TAG_GEN2_INVENTORY                           0x02
#define STUHFL_TAG_GEN2_INVENTORY_TAG                       0x03
#define STUHFL_TAG_GEN2_SELECT                              0x04
#define STUHFL_TAG_GEN2_READ                                0x05
#define STUHFL_TAG_GEN2_WRITE                               0x06
#define STUHFL_TAG_GEN2_LOCK                                0x07
#define STUHFL_TAG_GEN2_KILL                                0x08
#define STUHFL_TAG_GEN2_GENERIC                             0x09
#define STUHFL_TAG_GEN2_QUERY_MEASURE_RSSI                  0x0A
#define STUHFL_TAG_GEN2_BLOCKWRITE                          0x0B

#define STUHFL_TAG_GB29768_INVENTORY_OPTION                 STUHFL_TAG_GEN2_INVENTORY_OPTION
#define STUHFL_TAG_GB29768_SORT                             0x14
#define STUHFL_TAG_GB29768_READ                             0x15
#define STUHFL_TAG_GB29768_WRITE                            0x16
#define STUHFL_TAG_GB29768_LOCK                             0x17
#define STUHFL_TAG_GB29768_KILL                             0x18
#define STUHFL_TAG_GB29768_GENERIC                          0x19
#define STUHFL_TAG_GB29768_ERASE                            0x1A

// TLV TAGs - Activity Layer
#define STUHFL_TAG_INVENTORY_OPTION                         0x01
#define STUHFL_TAG_INVENTORY_STATISTICS                     0x02
#define STUHFL_TAG_INVENTORY_TAG_INFO_HEADER                0x03
#define STUHFL_TAG_INVENTORY_TAG_EPC                        0x04
#define STUHFL_TAG_INVENTORY_TAG_TID                        0x05
#define STUHFL_TAG_INVENTORY_TAG_XPC                        0x06
#define STUHFL_TAG_INVENTORY_TAG_FINISHED                   0xFF

#define STUHFL_TAG_INVENTORY_SLOT_INFO_SYNC                 0x07
#define STUHFL_TAG_INVENTORY_SLOT_INFO                      0x08

//
#define STUHFL_TYPE_UINT8                                   0
#define STUHFL_TYPE_UINT16                                  1
#define STUHFL_TYPE_UINT32                                  2
#define STUHFL_TYPE_INT8                                    3
#define STUHFL_TYPE_INT16                                   4
#define STUHFL_TYPE_INT32                                   5
#define STUHFL_TYPE_BOOL                                    6
#define STUHFL_TYPE_ST25RU3993_ACCESS_REGISTER              7
//..

#pragma pack(push, 1)

typedef struct {
    uint8_t                             major;      /**< O Param: Major version information */
    uint8_t                             minor;      /**< O Param: Minor version information */
    uint8_t                             micro;      /**< O Param: Micro version information */
    uint8_t                             nano;       /**< O Param: Nano version information */
} STUHFL_T_Version;
#define STUHFL_O_VERSION_INIT()         {0, 0, 0, 0}

#define STUHFL_D_MAX_VERSION_INFO_LENGTH                             64U
typedef struct {
    char                                info[STUHFL_D_MAX_VERSION_INFO_LENGTH];  /**< O Param: Readable version information string. Zero terminated */
    uint8_t                             infoLength;                              /**< O Param: Length of version information string */
} STUHFL_T_VersionInfo;
#define STUHFL_O_VERSION_INFO_INIT()    {{0}, 0}

#pragma pack(pop)


// --------------------------------------------------------------------------
typedef uint8_t                         STUHFL_T_ParamTypeUINT8;
typedef uint16_t                        STUHFL_T_ParamTypeUINT16;
typedef uint32_t                        STUHFL_T_ParamTypeUINT32;
typedef char*                           STUHFL_T_ParamTypeConnectionPort;
typedef uint32_t                        STUHFL_T_ParamTypeConnectionBR;
typedef uint32_t                        STUHFL_T_ParamTypeConnectionRdTimeout;
typedef uint32_t                        STUHFL_T_ParamTypeConnectionWrTimeout;

// --------------------------------------------------------------------------
#define STUHFL_HWID_DISCOVERY                 1
#define STUHFL_HWID_EVAL                      2
#define STUHFL_HWID_JIGEN                     3
#define STUHFL_HWID_ELANCE                    4
#define STUHFL_HWID_JIGEN_PHI                 5


// --------------------------------------------------------------------------
/**
 * Reply version information of STUHFL
 *
 * @return version number
*/
STUHFL_DLL_API STUHFL_T_VERSION CALL_CONV STUHFL_F_GetLibVersion(void);



#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __STUHFL_H

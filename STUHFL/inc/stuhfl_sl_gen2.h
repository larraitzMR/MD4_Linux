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
#if !defined __STUHFL_SL_GEN2_H
#define __STUHFL_SL_GEN2_H

#include "stuhfl.h"
#include "stuhfl_sl.h"


#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

// - GEN2 -------------------------------------------------------------------

#pragma pack(push, 1)
#define STUHFL_D_GEN2_SELECT_MODE_CLEAR_LIST             0
#define STUHFL_D_GEN2_SELECT_MODE_ADD2LIST               1
#define STUHFL_D_GEN2_SELECT_MODE_CLEAR_AND_ADD          2

#define STUHFL_D_GEN2_TARGET_S0                  0
#define STUHFL_D_GEN2_TARGET_S1                  1
#define STUHFL_D_GEN2_TARGET_S2                  2
#define STUHFL_D_GEN2_TARGET_S3                  3
#define STUHFL_D_GEN2_TARGET_SL                  4

#define STUHFL_D_GEN2_MEMORY_BANK_RESERVED       0
#define STUHFL_D_GEN2_MEMORY_BANK_EPC            1
#define STUHFL_D_GEN2_MEMORY_BANK_TID            2
#define STUHFL_D_GEN2_MEMORY_BANK_USER           3

#define STUHFL_D_GEN2_MAX_SELECT_MASK_LENGTH          32  /**< Maximum select mask length. Limited to 255 bits by EPCglobal */
typedef struct {
    uint8_t                             mode;           /**< I Param: Select mode to be applied (CLEAR_LIST, ADD2LIST, CLEAR_AND_ADD). */
    uint8_t                             target;         /**< I Param: indicates whether the select modifies a tag's SL flag or its inventoried flag. */
    uint8_t                             action;         /**< I Param: Elicit the tag behavior according to Gen2 Select specification. */
    uint8_t                             memoryBank;     /**< I Param: Bank (File, EPC, TID, USER) on which apply the select. */
    uint8_t                             mask[STUHFL_D_GEN2_MAX_SELECT_MASK_LENGTH];   /**< I Param: Selection mask. */
    uint32_t                            maskBitPointer; /**< I Param: Bit starting address to which mask is applied (bit address). */
    uint8_t                             maskBitLength;  /**< I Param: Mask length in bits. */
    uint8_t                             truncation;     /**< I Param: Truncate enabling. */
} STUHFL_T_Gen2_Select;
#define STUHFL_O_GEN2_SELECT_INIT()      {STUHFL_D_GEN2_SELECT_MODE_CLEAR_LIST, STUHFL_D_GEN2_TARGET_S0, 0, STUHFL_D_GEN2_MEMORY_BANK_EPC, {0}, 0, 0, false}

typedef STUHFL_T_Read           STUHFL_T_Gen2_Read;
typedef STUHFL_T_Write          STUHFL_T_Gen2_Write;
typedef STUHFL_T_BlockWrite     STUHFL_T_Gen2_BlockWrite;

#define STUHFL_D_GEN2_LOCK_MASK_ACTION_LEN            3
typedef struct {
    uint8_t                             mask[STUHFL_D_GEN2_LOCK_MASK_ACTION_LEN]; /**< I Param: Mask and actions field. */
    uint8_t                             pwd[STUHFL_D_PASSWORD_LEN];          /**< I Param: Password. */
    uint8_t                             tagReply;                   /**< O Param: Tag reply. */
} STUHFL_T_Gen2_Lock;
#define STUHFL_O_GEN2_LOCK_INIT()        {{0}, {0}, 0}

typedef STUHFL_T_Kill           STUHFL_T_Gen2_Kill;

#define STUHFL_D_GEN2_GENERIC_CMD_CRC                   0x90
#define STUHFL_D_GEN2_GENERIC_CMD_CRC_EXPECT_HEAD       0x91
#define STUHFL_D_GEN2_GENERIC_CMD_NO_CRC                0x92

#define STUHFL_D_GEN2_GENERIC_CMD_MAX_SND_DATA_BYTES     64U    // 512/8
#define STUHFL_D_GEN2_GENERIC_CMD_MAX_RCV_DATA_BYTES     128U

typedef struct {
    uint8_t                             pwd[STUHFL_D_PASSWORD_LEN];     /**< I Param: Password. */
    uint8_t                             cmd;                            /**< I Param: Generic command. */
    uint8_t                             noResponseTime;                 /**< I Param: Tag response timeout. */
    uint16_t                            expectedRcvDataBitLength;       /**< I Param: Size in bits of expected received data. NOTE: For the direct commands 0x90 and 0x91 (Tranmission with CRC) CRC is handled by HW and need not to be included into the expected bit count. The received CRC will also not replied to the host. When using command 0x92 handling of any data integrity checking must be done manually.*/
    uint16_t                            sndDataBitLength;               /**< I Param: Size in bits of data sent to Tag. */
    bool                                appendRN16;                     /**< I Param: Append tag handle to generic command. */
    uint8_t                             sndData[STUHFL_D_GEN2_GENERIC_CMD_MAX_SND_DATA_BYTES];   /**< I Param: Data being sent to Tag. */
    uint16_t                            rcvDataLength;                  /**< O Param: Size in bytes of received data from Tag. */
    uint8_t                             rcvData[STUHFL_D_GEN2_GENERIC_CMD_MAX_RCV_DATA_BYTES];   /**< O Param: Data received from Tag. */
} STUHFL_T_Gen2_GenericCmd;
#define STUHFL_O_GEN2_GENERICCMD_INIT()      {{0}, 0, 0, 0, 0, true, {0}, 0, {0}}

typedef struct {
    uint32_t                            frequency;                  /**< I Param: Frequency. */
    uint8_t                             measureCnt;                 /**< I Param: Number of measures. */
    uint8_t                             agc[256];                   /**< O Param: AGC. */
    uint8_t                             rssiLogI[256];              /**< O Param: RSSI log. */
    uint8_t                             rssiLogQ[256];              /**< O Param: RSSI log. */
    int8_t                              rssiLinI[256];              /**< O Param: RSSI I Level. */
    int8_t                              rssiLinQ[256];              /**< O Param: RSSI Q Level. */
} STUHFL_T_Gen2_QueryMeasureRssi;
#define STUHFL_O_GEN2_QUERY_MEASURE_RSSI_INIT()      {0, 0, {0}, {0}, {0}, {0}, {0}}

#pragma pack(pop)

// --------------------------------------------------------------------------
/**
 * Perform Gen2 Inventory depending on the current inventory and gen2 configuration
 * @param invOption: See STUHFL_T_InventoryOption struct for further info
 * @param invData: See STUHFL_T_InventoryData struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Inventory(STUHFL_T_InventoryOption *invOption, STUHFL_T_InventoryData *invData);
/**
 * Perform Gen2 Select command to select or filter transponders
 * @param selData: See STUHFL_T_Gen2_Select struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Select(STUHFL_T_Gen2_Select *selData);
/**
 * Perform Gen2 Read command to read from the Gen2 transponders
 * @param readData: See STUHFL_T_Read struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Read(STUHFL_T_Gen2_Read *readData);
/**
 * Perform Gen2 Write command to write data to Gen2 transponders
 * @param writeData: See STUHFL_T_Write struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Write(STUHFL_T_Gen2_Write *writeData);
/**
 * Perform Gen2 Block Write command to write block data to Gen2 transponders
 * @param blockWrite: See STUHFL_T_BlockWrite struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_BlockWrite(STUHFL_T_Gen2_BlockWrite *blockWrite);
/**
 * Perform Gen2 Lock command to lock transponders
 * @param lockData: See STUHFL_T_Gen2_Lock struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Lock(STUHFL_T_Gen2_Lock *lockData);
/**
 * Perform Gen2 Kill command to kill transponders.
 * NOTE: After this command your transponders will not be functional anymore
 * @param killData: See STUHFL_T_Kill struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Kill(STUHFL_T_Gen2_Kill *killData);
/**
 * Perform generic Gen2 bit exchange
 * @param genericCmdDataSnd: See STUHFL_T_Gen2_GenericCmd struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_GenericCmd(STUHFL_T_Gen2_GenericCmd *genericCmd);
/**
 * Perform RSSI measurement during Gen2 Query commmand
 * @param queryMeasureRssi: See STUHFL_T_Gen2_QueryMeasureRssi struct for further info
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_QueryMeasureRssi(STUHFL_T_Gen2_QueryMeasureRssi *queryMeasureRssi);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __STUHFL_SL_GEN2_H

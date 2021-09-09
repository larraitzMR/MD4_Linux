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

// dllmain.cpp

#include "stuhfl.h"
#include "stuhfl_sl.h"
#include "stuhfl_sl_gen2.h"
#include "stuhfl_sl_gb29768.h"
#include "stuhfl_dl.h"
#include "stuhfl_err.h"
#include "stuhfl_log.h"
#include "stuhfl_helpers.h"

#define TRACE_SL_LOG_CLEAR()    { STUHFL_F_LogClear(); }
#define TRACE_SL_LOG_APPEND(...){ STUHFL_F_LogAppend(__VA_ARGS__); }
#define TRACE_SL_LOG_FLUSH()    { STUHFL_F_LogFlush(STUHFL_D_LOG_LEVEL_TRACE_SL); }

#define TRACE_SL_LOG_START(...) { STUHFL_F_LogClear(STUHFL_D_LOG_LEVEL_TRACE_SL); }
#define TRACE_SL_LOG(...)       { STUHFL_F_LogAppend(STUHFL_D_LOG_LEVEL_TRACE_SL, __VA_ARGS__); STUHFL_F_LogFlush(STUHFL_D_LOG_LEVEL_TRACE_SL); }

// --------------------------------------------------------------------------
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Inventory(STUHFL_T_InventoryOption *invOption, STUHFL_T_InventoryData *invData)
{
    invData->tagListSize = 0;
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_INVENTORY, (STUHFL_T_PARAM_VALUE)invOption, (STUHFL_T_PARAM_VALUE)invData);
    TRACE_SL_LOG("Gen2_Inventory(rssiMode: %d, roundCnt: %d, inventoryDelay: %d, options: %d, tagListSizeMax: %d, tagListSize: %d, STATISTICS: tuningStatus: %d, roundCnt: %d, sensitivity: %d, Q: %d, adc: %d, frequency: %d, tagCnt: %d, emptySlotCnt: %d, collisionCnt: %d, skipCnt: %d, preambleErrCnt: %d, crcErrCnt: %d, TAGLIST: ..) = %d",
                 invOption->rssiMode, invOption->roundCnt, invOption->inventoryDelay, invOption->options,
                 invData->tagListSizeMax, invData->tagListSize,
                 invData->statistics.tuningStatus, invData->statistics.roundCnt, invData->statistics.sensitivity, invData->statistics.Q, invData->statistics.adc, invData->statistics.frequency, invData->statistics.tagCnt, invData->statistics.emptySlotCnt, invData->statistics.collisionCnt, invData->statistics.skipCnt, invData->statistics.preambleErrCnt, invData->statistics.crcErrCnt, ret);
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gb29768_Inventory(STUHFL_T_InventoryOption *invOption, STUHFL_T_InventoryData *invData)
{
    invData->tagListSize = 0;
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GB29768_INVENTORY, (STUHFL_T_PARAM_VALUE)invOption, (STUHFL_T_PARAM_VALUE)invData);
    TRACE_SL_LOG("Gb29768_Inventory(rssiMode: %d, roundCnt: %d, inventoryDelay: %d, options: %d, tagListSizeMax: %d, tagListSize: %d, STATISTICS: tuningStatus: %d, roundCnt: %d, sensitivity: %d, adc: %d, frequency: %d, tagCnt: %d, emptySlotCnt: %d, collisionCnt: %d, skipCnt: %d, preambleErrCnt: %d, crcErrCnt: %d, TAGLIST: ..) = %d",
                 invOption->rssiMode, invOption->roundCnt, invOption->inventoryDelay, invOption->options,
                 invData->tagListSizeMax, invData->tagListSize,
                 invData->statistics.tuningStatus, invData->statistics.roundCnt, invData->statistics.sensitivity, invData->statistics.adc, invData->statistics.frequency, invData->statistics.tagCnt, invData->statistics.emptySlotCnt, invData->statistics.collisionCnt, invData->statistics.skipCnt, invData->statistics.preambleErrCnt, invData->statistics.crcErrCnt, ret);
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Select(STUHFL_T_Gen2_Select *selData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_SELECT, (STUHFL_T_PARAM_VALUE)selData, NULL);
    TRACE_SL_LOG("Gen2_Select(mode: %d, target: %d, action: %d, memoryBank: %d, mask[32]: 0x%02x.., maskBitPointer: %d, maskBitLength: %d, truncation: %d) = %d",
                 selData->mode, selData->target, selData->action, selData->memoryBank, selData->mask[0], selData->maskBitPointer, selData->maskBitLength, selData->truncation, ret);
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gb29768_Sort(STUHFL_T_Gb29768_Sort *sortData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GB29768_SORT, (STUHFL_T_PARAM_VALUE)sortData, NULL);
    TRACE_SL_LOG("Gb29768_Sort(mode: %d, target: %d, rule: %d, memoryBank: %d, mask[32]: 0x%02x.., maskBitPointer: %d, maskBitLength: %d) = %d",
                 sortData->mode, sortData->target, sortData->rule, sortData->memoryBank, sortData->mask[0], sortData->maskBitPointer, sortData->maskBitLength, ret);
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Read(STUHFL_T_Read *readData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_READ, (STUHFL_T_PARAM_VALUE)readData, (STUHFL_T_PARAM_VALUE)readData);
#define TB_SIZE    256
    char tb[2][TB_SIZE];
    TRACE_SL_LOG("Gen2_Read(memoryBank: %d, wordPtr: %d, numBytesToRead: %d, numReadBytes: %d, pwd: 0x%s, data: 0x%s) = %d", readData->memoryBank, readData->wordPtr, readData->numBytesToRead, readData->numReadBytes, byteArray2HexString(tb[0], TB_SIZE, readData->pwd, STUHFL_D_PASSWORD_LEN), byteArray2HexString(tb[1], TB_SIZE, readData->data, STUHFL_D_MAX_READ_DATA_LEN), ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gb29768_Read(STUHFL_T_Read *readData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GB29768_READ, (STUHFL_T_PARAM_VALUE)readData, (STUHFL_T_PARAM_VALUE)readData);
#define TB_SIZE    256
    char tb[2][TB_SIZE];
    TRACE_SL_LOG("Gb29768_Read(memoryBank: %d, wordPtr: %d, numBytesToRead: %d, numReadBytes: %d, pwd: 0x%s, data: 0x%s) = %d", readData->memoryBank, readData->wordPtr, readData->numBytesToRead, readData->numReadBytes, byteArray2HexString(tb[0], TB_SIZE, readData->pwd, STUHFL_D_PASSWORD_LEN), byteArray2HexString(tb[1], TB_SIZE, readData->data, STUHFL_D_MAX_READ_DATA_LEN), ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Write(STUHFL_T_Write *writeData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_WRITE, (STUHFL_T_PARAM_VALUE)writeData, (STUHFL_T_PARAM_VALUE)writeData);
#define TB_SIZE    256
    char tb[TB_SIZE];
    TRACE_SL_LOG("Gen2_Write(memoryBank: %d, wordPtr: %d, pwd: 0x%s, data: 0x%02x%02x, tagReply: 0x%02x) = %d", writeData->memoryBank, writeData->wordPtr, byteArray2HexString(tb, TB_SIZE, writeData->pwd, STUHFL_D_PASSWORD_LEN), writeData->data[0], writeData->data[1], writeData->tagReply, ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_BlockWrite(STUHFL_T_BlockWrite *blockWrite)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_BLOCKWRITE, (STUHFL_T_PARAM_VALUE)blockWrite, (STUHFL_T_PARAM_VALUE)blockWrite);
#define TB_SIZE    256
    char tb[2][TB_SIZE];
    TRACE_SL_LOG("Gen2_BlockWrite(memoryBank: %d, wordPtr: %d, pwd: 0x%s, numBytesToWrite: %d, data: 0x%s, tagReply: 0x%02x) = %d", blockWrite->memoryBank, blockWrite->wordPtr, byteArray2HexString(tb[0], TB_SIZE, blockWrite->pwd, STUHFL_D_PASSWORD_LEN), blockWrite->numBytesToWrite, byteArray2HexString(tb[1], TB_SIZE, blockWrite->data, STUHFL_D_MAX_BLOCKWRITE_DATA_LEN), blockWrite->tagReply, ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gb29768_Write(STUHFL_T_Write *writeData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GB29768_WRITE, (STUHFL_T_PARAM_VALUE)writeData, (STUHFL_T_PARAM_VALUE)writeData);
#define TB_SIZE    256
    char tb[TB_SIZE];
    TRACE_SL_LOG("Gb29768_Write(memoryBank: %d, wordPtr: %d, pwd: 0x%s, data: 0x%02x%02x) = %d", writeData->memoryBank, writeData->wordPtr, byteArray2HexString(tb, TB_SIZE, writeData->pwd, STUHFL_D_PASSWORD_LEN), writeData->data[0], writeData->data[1], ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Lock(STUHFL_T_Gen2_Lock *lockData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_LOCK, (STUHFL_T_PARAM_VALUE)lockData, NULL);
#define TB_SIZE    256
    char tb[2][TB_SIZE];
    TRACE_SL_LOG("Gen2_Lock(mask: 0x%s, pwd: 0x%s, tagReply: 0x%02x) = %d", byteArray2HexString(tb[0], TB_SIZE, lockData->mask, 3), byteArray2HexString(tb[1], TB_SIZE, lockData->pwd, STUHFL_D_PASSWORD_LEN), lockData->tagReply, ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gb29768_Lock(STUHFL_T_Gb29768_Lock *lockData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GB29768_LOCK, (STUHFL_T_PARAM_VALUE)lockData, NULL);
#define TB_SIZE    256
    char tb[TB_SIZE];
    TRACE_SL_LOG("Gb29768_Lock(memoryBank: 0x%02x, configuration: 0x%02x, action: 0x%02x, pwd: 0x%s) = %d", lockData->memoryBank, lockData->configuration, lockData->action, byteArray2HexString(tb, TB_SIZE, lockData->pwd, STUHFL_D_PASSWORD_LEN), ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_Kill(STUHFL_T_Kill *killData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_KILL, (STUHFL_T_PARAM_VALUE)killData, NULL);
#define TB_SIZE    256
    char tb[TB_SIZE];
    TRACE_SL_LOG("Gen2_Kill(pwd: 0x%s, recommission: %d, tagReply: 0x%02x) = %d", byteArray2HexString(tb, TB_SIZE, killData->pwd, STUHFL_D_PASSWORD_LEN), killData->recommission, killData->tagReply, ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gb29768_Kill(STUHFL_T_Kill *killData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GB29768_KILL, (STUHFL_T_PARAM_VALUE)killData, NULL);
#define TB_SIZE    256
    char tb[TB_SIZE];
    TRACE_SL_LOG("Gb29768_Kill(pwd: 0x%s) = %d", byteArray2HexString(tb, TB_SIZE, killData->pwd, STUHFL_D_PASSWORD_LEN), ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_GenericCmd(STUHFL_T_Gen2_GenericCmd *genericCmd)
{
    genericCmd->rcvDataLength = 0;
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_GENERIC_CMD, (STUHFL_T_PARAM_VALUE)genericCmd, (STUHFL_T_PARAM_VALUE)genericCmd);
#define TB_SIZE    256
    char tb[3][TB_SIZE];
    TRACE_SL_LOG("Gen2_GenericCmd(pwd: 0x%s, cmd: 0x%02x, noResponseTime: %d, sndDataBitLength: %d, sndData: 0x%s.., expectedRcvDataBitLength: %d, rcvDataLength: %d, rcvData: 0x%s..) = %d",
                 byteArray2HexString(tb[0], TB_SIZE, genericCmd->pwd, STUHFL_D_PASSWORD_LEN), genericCmd->cmd, genericCmd->noResponseTime, genericCmd->sndDataBitLength, byteArray2HexString(tb[1], TB_SIZE, genericCmd->sndData, 4), genericCmd->expectedRcvDataBitLength, genericCmd->rcvDataLength, byteArray2HexString(tb[2], TB_SIZE, genericCmd->rcvData, 4), ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gen2_QueryMeasureRssi(STUHFL_T_Gen2_QueryMeasureRssi *queryMeasureRssi)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GEN2_QUERY_MEASURE_RSSI, (STUHFL_T_PARAM_VALUE)queryMeasureRssi, (STUHFL_T_PARAM_VALUE)queryMeasureRssi);
#define TB_SIZE    256
    char tb[5][TB_SIZE];
    TRACE_SL_LOG("Gen2_QueryMeasureRssi(frequency: %d, measureCnt: %d, agc: 0x%s.., rssiLogI: 0x%s.., rssiLogQ: 0x%s.., rssiLinI: 0x%s.., rssiLinQ: 0x%s..) = %d", queryMeasureRssi->frequency, queryMeasureRssi->measureCnt, byteArray2HexString(tb[0], TB_SIZE, queryMeasureRssi->agc, 4), byteArray2HexString(tb[1], TB_SIZE, queryMeasureRssi->rssiLogI, 4), byteArray2HexString(tb[2], TB_SIZE, queryMeasureRssi->rssiLogQ, 4), byteArray2HexString(tb[3], TB_SIZE, queryMeasureRssi->rssiLinI, 4), byteArray2HexString(tb[4], TB_SIZE, queryMeasureRssi->rssiLinQ, 4), ret);
#undef TB_SIZE
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Gb29768_Erase(STUHFL_T_Gb29768_Erase *eraseData)
{
    TRACE_SL_LOG_START();
    STUHFL_T_RET_CODE ret = STUHFL_F_ExecuteCmd((STUHFL_CG_SL << 8) | STUHFL_CC_GB29768_ERASE, (STUHFL_T_PARAM_VALUE)eraseData, (STUHFL_T_PARAM_VALUE)eraseData);
#define TB_SIZE    256
    char tb[TB_SIZE];
    TRACE_SL_LOG("Gb29768_Erase(memoryBank: %d, bytePtr: %d, numBytesToErase: %d, pwd: 0x%s) = %d", eraseData->memoryBank, eraseData->bytePtr, eraseData->numBytesToErase, byteArray2HexString(tb, TB_SIZE, eraseData->pwd, STUHFL_D_PASSWORD_LEN), ret);
#undef TB_SIZE
    return ret;
}

/**
  * @}
  */
/**
  * @}
  */

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
#include "stuhfl_err.h"
#include "stuhfl_al.h"
#include "stuhfl_sl.h"
#include "stuhfl_sl_gen2.h"
#include "stuhfl_sl_gb29768.h"
#include "stuhfl_dl.h"


#if defined(WIN32) || defined(WIN64)
static HANDLE inventoryThread = INVALID_HANDLE_VALUE;
#elif defined(POSIX)
static pthread_t inventoryThread = INVALID_HANDLE_VALUE;
#else
#endif

void* CALL_CONV_STD threadInventoryFunc(void *ptr);

static STUHFL_T_CallerCtx gCallerCtxPointer = NULL;
static STUHFL_T_ActionCycle gActionCycleCallback = NULL;
static STUHFL_T_ActionCycleOOP gActionCycleCallbackOOP = NULL;
static STUHFL_T_ActionFinished gActionFinishedCallback = NULL;
static STUHFL_T_ActionFinishedOOP gActionFinishedCallbackOOP = NULL;

static STUHFL_T_ActionCycleData *gActionCycleData = NULL;

static uint32_t requestedRoundCnt = 0;

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Start(STUHFL_T_Action action, STUHFL_T_ActionOption actionOptions, STUHFL_T_ActionCycle cycleCallback, STUHFL_T_ActionCycleData cycleData, STUHFL_T_ActionFinished finishedCallback, STUHFL_T_ActionId *id)
{
    gActionCycleCallback = cycleCallback;
    gActionFinishedCallback = finishedCallback;
    return STUHFL_F_StartOOP(action, actionOptions, NULL, NULL, cycleData, NULL, id);
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_StartOOP(STUHFL_T_Action action, STUHFL_T_ActionOption actionOptions, STUHFL_T_CallerCtx callerCtx, STUHFL_T_ActionCycleOOP cycleCallbackOOP, STUHFL_T_ActionCycleData cycleData, STUHFL_T_ActionFinishedOOP finishedCallbackOOP, STUHFL_T_ActionId *id)
{
    STUHFL_T_RET_CODE ret = STUHFL_ERR_GENERIC;

    if ((inventoryThread != INVALID_HANDLE_VALUE) && (inventoryThread != (STUHFL_T_POINTER2UINT)NULL)) {
        return STUHFL_ERR_REQUEST;
    }

    gCallerCtxPointer = callerCtx;
    gActionCycleCallbackOOP = cycleCallbackOOP;
    gActionCycleData = cycleData;
    gActionFinishedCallbackOOP = finishedCallbackOOP;
    *id = (STUHFL_T_ActionId)inventoryThread;

    switch (action) {
    case STUHFL_D_ACTION_INVENTORY: {
        requestedRoundCnt = (uint32_t)((STUHFL_T_InventoryOption *)actionOptions)->roundCnt;
        // reset tagListSize & statistics
        ((STUHFL_T_InventoryData *)cycleData)->tagListSize = 0;
        memset(&((STUHFL_T_InventoryData *)cycleData)->statistics, 0, sizeof(STUHFL_T_InventoryStatistics));

        // send start signal to begin inventory rounds
        ret = STUHFL_F_ExecuteCmd((STUHFL_CG_AL << 8) | STUHFL_CC_INVENTORY_START, actionOptions, NULL);
        break;
    }
#ifdef USE_INVENTORY_EXT
    case STUHFL_D_ACTION_INVENTORY_W_SLOT_STATISTICS: {
        requestedRoundCnt = (uint32_t)((STUHFL_T_InventoryOption *)actionOptions)->roundCnt;
        // reset tagListSize & statistics
        ((STUHFL_T_InventoryDataExt *)cycleData)->invData.tagListSize = 0;
        memset(&((STUHFL_T_InventoryDataExt *)cycleData)->invData.statistics, 0, sizeof(STUHFL_T_InventoryStatistics));
        // reset slotInfo
        ((STUHFL_T_InventoryDataExt *)cycleData)->invSlotInfoData.slotInfoListSize = 0;

        // send start signal to begin extented inventory rounds
        ret = STUHFL_F_ExecuteCmd((STUHFL_CG_AL << 8) | STUHFL_CC_INVENTORY_START_W_SLOT_STATISTICS, actionOptions, NULL);
        break;
    }
#endif  // USE_INVENTORY_EXT
    default:
        return STUHFL_ERR_REQUEST;
    }

#if defined(WIN32) || defined(WIN64)
    inventoryThread = CreateThread(
                          NULL,   //default security
                          0,      //default stack size
                          (LPTHREAD_START_ROUTINE)threadInventoryFunc,
                          (void*)action,   //argument to threadFunc
                          0,      //creation flags
                          0
                      );
#elif defined(POSIX)
    if (pthread_create(&inventoryThread, NULL, threadInventoryFunc, (void*)action)) {
        inventoryThread = INVALID_HANDLE_VALUE;
    }
#else
#endif
    if ((inventoryThread == INVALID_HANDLE_VALUE) || (inventoryThread == (STUHFL_T_POINTER2UINT)NULL)) {
        return STUHFL_ERR_REQUEST;
    }

    *id = (STUHFL_T_ActionId)inventoryThread;
    return ret;
}

STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Stop(STUHFL_T_ActionId id)
{
    STUHFL_T_RET_CODE ret = STUHFL_ERR_PARAM;
    if ((HANDLE)id == inventoryThread) {
        // Force thread to exit
        inventoryThread = INVALID_HANDLE_VALUE;

        // send stop signal to terminate
        int maxRetry = 256;
        while ((ret != STUHFL_ERR_NONE) && (maxRetry--)) {
            // repeat STOP until all outstanding runner packets are received and the STOP is correctly answered
            ret = STUHFL_F_ExecuteCmd((STUHFL_CG_AL << 8) | STUHFL_CC_INVENTORY_STOP, NULL, NULL);
        }

        // notify about thread termination
        if (gActionFinishedCallback) {
            gActionFinishedCallback(gActionCycleData);
        } else {
            gActionFinishedCallbackOOP(gCallerCtxPointer, gActionCycleData);
        }
    }
    return ret;
}

void* CALL_CONV_STD threadInventoryFunc(void *ptr)
{
    STUHFL_T_POINTER2UINT action = (STUHFL_T_POINTER2UINT)ptr;
    STUHFL_T_InventoryData *invData = NULL;
#ifdef USE_INVENTORY_EXT
    STUHFL_T_InventorySlotInfoData *invSlotData = NULL;
#endif
    STUHFL_T_RET_CODE ret = STUHFL_ERR_PARAM;

    bool looping = true;
    do {

        switch (action) {
        case STUHFL_D_ACTION_INVENTORY: {
            invData = (STUHFL_T_InventoryData *)gActionCycleData;
            break;
        }
#ifdef USE_INVENTORY_EXT
        case STUHFL_D_ACTION_INVENTORY_W_SLOT_STATISTICS: {
            invData = &((STUHFL_T_InventoryDataExt *)gActionCycleData)->invData;
            invSlotData = &((STUHFL_T_InventoryDataExt *)gActionCycleData)->invSlotInfoData;
            break;
        }
#endif
        default:
            invData = NULL;
#ifdef USE_INVENTORY_EXT
            invSlotData = NULL;
#endif
            break;
        }

        if (invData == NULL) {
            // terminate thread in case we received an not supported action
            break;
        }

        // check for inventory data..
        ret = STUHFL_F_ReceiveCmdData((STUHFL_CG_AL << 8) | STUHFL_CC_INVENTORY_DATA, gActionCycleData);
        if (ret == STUHFL_ERR_NONE) {
            // notify via callback, when something received
            if (gActionCycleCallback) {
                gActionCycleCallback(gActionCycleData);
            } else {
                gActionCycleCallbackOOP(gCallerCtxPointer, gActionCycleData);
            }
        }

        // clear counters to be prepared for next cycle
        if (invData) { invData->tagListSize = 0; }
#ifdef USE_INVENTORY_EXT
        if (invSlotData) { invSlotData->slotInfoListSize = 0; }
#endif

        // terminate thread when finished
        if (requestedRoundCnt) {
            if (invData->statistics.roundCnt >= requestedRoundCnt) {
                if (gActionFinishedCallback) {
                    gActionFinishedCallback(gActionCycleData);
                } else {
                    gActionFinishedCallbackOOP(gCallerCtxPointer, gActionCycleData);
                }
                looping = false;
            }
        }

        if ((inventoryThread == INVALID_HANDLE_VALUE) || (inventoryThread == (STUHFL_T_POINTER2UINT)NULL)) {
            looping = false;
        }
    } while (looping);

    inventoryThread = (STUHFL_T_POINTER2UINT)NULL;
    return (void *)(inventoryThread);
}

/**
  * @}
  */
/**
  * @}
  */

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
#if !defined __STUHFL_AL_H
#define __STUHFL_AL_H

#include "stuhfl.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

// --------------------------------------------------------------------------
#define STUHFL_D_ACTION_INVENTORY                     0x00
#ifdef USE_INVENTORY_EXT
#define STUHFL_D_ACTION_INVENTORY_W_SLOT_STATISTICS   0x01
#endif

typedef STUHFL_T_POINTER2UINT           STUHFL_T_ActionId;
typedef STUHFL_T_POINTER2UINT           STUHFL_T_Action;
typedef void*                           STUHFL_T_ActionOption;
typedef void*                           STUHFL_T_ActionCycleData;

typedef void* STUHFL_T_CallerCtx;
typedef STUHFL_T_RET_CODE(*STUHFL_T_ActionCycle)(STUHFL_T_ActionCycleData data);
typedef STUHFL_T_RET_CODE(*STUHFL_T_ActionCycleOOP)(STUHFL_T_CallerCtx obj, STUHFL_T_ActionCycleData data);
typedef STUHFL_T_RET_CODE(*STUHFL_T_ActionFinished)(STUHFL_T_ActionCycleData data);
typedef STUHFL_T_RET_CODE(*STUHFL_T_ActionFinishedOOP)(STUHFL_T_CallerCtx obj, STUHFL_T_ActionCycleData data);

/**
 * Perform application layer start command
 * @param action: which action to be started
 * @param actionOptions: IN arguments for action
 * @param cycleCallback: function pointer for callback function that is periodically called
 * @param cycleData: I/O arguments that are updated with every periodically cycleCallback
 * @param finishedCallback: function pointer for callback function that is called when action is finished
 * @param *id: OUT param with ID of started action
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Start(
    STUHFL_T_Action action,
    STUHFL_T_ActionOption actionOptions,
    STUHFL_T_ActionCycle cycleCallback,
    STUHFL_T_ActionCycleData cycleData,
    STUHFL_T_ActionFinished finishedCallback,
    STUHFL_T_ActionId *id);

/**
 * Perform application layer start command
 * @param action: which action to be started
 * @param actionOptions: IN arguments for action
 * @param callerCtx: pointer to be returned back with caller "this" context. Needed when called from functions in OOP. Shall be NULL when used from C code. Shall be the this-pointer when used from OOP.
 * @param cycleCallback: function pointer for callback function that is periodically called
 * @param cycleData: I/O arguments that are updated with every periodically cycleCallback
 * @param finishedCallback: function pointer for callback function that is called when action is finished
 * @param *id: OUT param with ID of started action
 *
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_StartOOP(
    STUHFL_T_Action action,
    STUHFL_T_ActionOption actionOptions,
    STUHFL_T_CallerCtx callerCtx,
    STUHFL_T_ActionCycleOOP cycleCallbackOOP,
    STUHFL_T_ActionCycleData cycleData,
    STUHFL_T_ActionFinishedOOP finishedCallbackOOP,
    STUHFL_T_ActionId *id);

/**
 * Perform application layer stop command to stop running action
 * @param id: action to be stoped
 * @return error code
*/
STUHFL_DLL_API STUHFL_T_RET_CODE CALL_CONV STUHFL_F_Stop(STUHFL_T_ActionId id);



#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __STUHFL_AL_H

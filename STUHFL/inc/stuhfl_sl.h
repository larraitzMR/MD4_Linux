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
#if !defined __STUHFL_SL_H
#define __STUHFL_SL_H

#include "stuhfl.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#pragma pack(push, 1)

//
#define STUHFL_D_MAX_TAG_LIST_SIZE               64U

#define STUHFL_D_MAX_TID_LENGTH                  12U
#define STUHFL_D_MAX_PC_LENGTH                   2U
#define STUHFL_D_MAX_EPC_LENGTH                  64U
#define STUHFL_D_MAX_XPC_LENGTH                  4U            /**< XPC_W1 + XPC_W2.*/

//
#define STUHFL_D_RSSI_MODE_REALTIME              0x00
#define STUHFL_D_RSSI_MODE_PILOT                 0x04
#define STUHFL_D_RSSI_MODE_2NDBYTE               0x06
#define STUHFL_D_RSSI_MODE_PEAK                  0x08

#define STUHFL_D_INVENTORYREPORT_HEARTBEAT_DURATION_MS      400
#define STUHFL_D_INVENTORYREPORT_OPTION_NONE           0x00
#define STUHFL_D_INVENTORYREPORT_OPTION_RESERVED       0x01        /**< Reserved bit. */
#define STUHFL_D_INVENTORYREPORT_OPTION_HEARTBEAT      0x02        /**< Bitfield enabling the sending of inventory heart beat (400ms pace) containing generic statistics only. */

typedef struct {
    uint8_t                             rssiMode;                       /**< I Param: RSSI mode. This defines what RSSI value is sent to the host along with the tag data.*/
    uint32_t                            roundCnt;                       /**< I Param: Inventory scan duration (in rounds). Set to 0 for infinity scanning. */
    uint16_t                            inventoryDelay;                 /**< I Param: additional delay that can be added for the each inventory round. */
    uint8_t                             options;                        /**< I Param: Defines Inventory data report scheme. */
} STUHFL_T_InventoryOption;
#define STUHFL_O_INVENTORY_OPTION_INIT()         {STUHFL_D_RSSI_MODE_2NDBYTE, 0, 0, 0x00}

//
typedef struct {
    uint8_t                             length;                                 /**< O Param: length of EPC data. */
    uint8_t                             data[STUHFL_D_MAX_EPC_LENGTH];          /**< O Param: EPC data. */
} STUHFL_T_InventoryTagEPC;
#define STUHFL_O_INVENTORY_TAG_EPC_INIT()        {0, {0}}

typedef struct {
    uint8_t                             length;                                 /**< O Param: length of XPC data. */
    uint8_t                             data[STUHFL_D_MAX_XPC_LENGTH];          /**< O Param: XPC data. */
} STUHFL_T_InventoryTagXPC;
#define STUHFL_O_INVENTORY_TAG_XPC_INIT()        {0, {0}}

typedef struct {
    uint8_t                             length;                                 /**< O Param: length of TID data. */
    uint8_t                             data[STUHFL_D_MAX_TID_LENGTH];          /**< O Param: TID data. */
} STUHFL_T_InventoryTagTID;
#define STUHFL_O_INVENTORY_TAG_TID_INIT()        {0, {0}}

// --------------------------------------------------------------------------
typedef struct {
    uint32_t                            timestamp;                      /**< O Param: Tag detection time stamp. */
    uint8_t                             antenna;                        /**< O Param: Antenna at which Tag was detected. */
    uint8_t                             agc;                            /**< O Param: AGC measured when TAG found. */
    uint8_t                             rssiLogI;                       /**< O Param: I part of Tag logarithmic RSSI. */
    uint8_t                             rssiLogQ;                       /**< O Param: Q part of Tag logarithmic RSSI. */
    int8_t                              rssiLinI;                       /**< O Param: I part of Tag linear RSSI. */
    int8_t                              rssiLinQ;                       /**< O Param: Q part of Tag linear RSSI. */
    uint8_t                             pc[STUHFL_D_MAX_PC_LENGTH];     /**< O Param: Tag PC. */
    STUHFL_T_InventoryTagXPC            xpc;                            /**< O Param: Tag XPC. */
    STUHFL_T_InventoryTagEPC            epc;                            /**< O Param: Tag EPC. */
    STUHFL_T_InventoryTagTID            tid;                            /**< O Param: Tag TID. */
} STUHFL_T_InventoryTag;
#define STUHFL_O_INVENTORY_TAG_INIT()        {  0, \
                                                STUHFL_D_ANTENNA_1, 0, 0, 0, 0, 0, \
                                                {0}, \
                                                STUHFL_O_INVENTORY_TAG_XPC_INIT(), \
                                                STUHFL_O_INVENTORY_TAG_EPC_INIT(), \
                                                STUHFL_O_INVENTORY_TAG_TID_INIT(), \
                                                }

#define STUHFL_D_TUNING_STATUS_UNTUNED           0
#define STUHFL_D_TUNING_STATUS_TUNING            1
#define STUHFL_D_TUNING_STATUS_TUNED             2

typedef struct {
    uint32_t                            timestamp;                      /**< O Param: timestamp of last statistics update. */
    uint32_t                            roundCnt;                       /**< O Param: Inventory rounds already done. */
    uint8_t                             tuningStatus;                   /**< O Param: Reader tuning status. */
    uint8_t                             rssiLogMean;                    /**< O Param: RSSI log mean value. Measurement is updated with every found TAG */
    int8_t                              sensitivity;                    /**< O Param: Reader sensitivity. */
    uint8_t                             Q;                              /**< O Param: Current Q, may vary if adaptive Q is enabled. */
    uint32_t                            frequency;                      /**< O Param: Current used frequency. */
    uint16_t                            adc;                            /**< O Param: ADC value. Measured after each inventory round. */
    uint32_t                            tagCnt;                         /**< O Param: Number of detected tags. */
    uint32_t                            emptySlotCnt;                   /**< O Param: Number of empty slots. */
    uint32_t                            collisionCnt;                   /**< O Param: Number of collisions. */
    uint32_t                            skipCnt;                        /**< O Param: Number of skipped tags due to failed follow command (eg.: subsequent ReadTID after Query). */
    uint32_t                            preambleErrCnt;                 /**< O Param: Number of Preamble errors. */
    uint32_t                            crcErrCnt;                      /**< O Param: Number of CRC errors. */
    uint32_t                            headerErrCnt;                   /**< O Param: Number of Header errors. */
    uint32_t                            rxCountErrCnt;                  /**< O Param: Number of RX count errors. */
} STUHFL_T_InventoryStatistics;
#define STUHFL_O_INVENTORY_STATISTICS_INIT()        { 0, 0, STUHFL_D_TUNING_STATUS_UNTUNED, 0, 0, 0, 0, \
                                                      0, 0, \
                                                      0, 0, 0, 0, 0, 0, 0 \
                                                      }

typedef struct {
    STUHFL_T_InventoryStatistics       statistics;          /**< O Param: Inventory statistics. */
    STUHFL_T_InventoryTag              *tagList;            /**< O Param: Detected tags list. Tag list memory must be allocated by application */
    uint16_t                            tagListSize;        /**< O Param: Detected tags number. */
    uint16_t                            tagListSizeMax;     /**< I Param: tagList size. Max number of tags to be stored during inventory. If more tags found, exceeding ones will overwrite last list entry. */
} STUHFL_T_InventoryData;
#define STUHFL_O_INVENTORY_DATA_INIT()      {STUHFL_O_INVENTORY_STATISTICS_INIT(), NULL, 0, 0}

// --------------------------------------------------------------------------
// Tags events
#define STUHFL_D_EVENT_TAG_FOUND         0x0001
#define STUHFL_D_EVENT_EMPTY_SLOT        0x0002
#define STUHFL_D_EVENT_COLLISION         0x0004
#define STUHFL_D_EVENT_PREAMBLE_ERR      0x0008
#define STUHFL_D_EVENT_CRC_ERR           0x0010
#define STUHFL_D_EVENT_HEADER_ERR        0x0020
#define STUHFL_D_EVENT_RX_COUNT_ERR      0x0040
#define STUHFL_D_EVENT_STOPBIT_ERR       0x0080
#define STUHFL_D_EVENT_SKIP_FOLLOW_CMD   0x0100
#define STUHFL_D_EVENT_RESEND_ACK        0x0200
#define STUHFL_D_EVENT_QUERY_REP         0x0400

#ifdef USE_INVENTORY_EXT
typedef struct {
    uint32_t                            timeStampBase;                  /**< O Param: base timestamp slotInfoList members. */
    uint32_t                            slotIdBase;                     /**< O Param: base ID for slotInfoList members. Starting slot ID slotInfoList members. */
} STUHFL_T_InventorySlotInfoSync;

//
typedef struct {
    uint8_t                             deltaT;                         /**< O Param: time delta to previous slot. absolute time = timeStampBase + sum(smaller slotInfoList list member index) */
    uint8_t                             Q;                              /**< O Param: used Q in this slot */
    int8_t                              sensitivity;                    /**< O Param: used sensitivity in this slot */
    uint16_t                            eventMask;                      /**< O Param: eventMask of slot. Describes occured events */

    uint8_t                             freqIndex;                      /**< O Param: current used frequency index */
    uint16_t                            sendingTime;                    /**< O Param: sending time of current frequency */
#if 0
    uint32_t                            fairModeUpTime;                 /**< O Param: DBG */
    uint32_t                            cpsPhaseValue;                  /**< O Param: DBG */
#endif
} STUHFL_T_InventorySlotInfo;

#define INVENTORYREPORT_SLOT_INFO_LIST_SIZE         256
typedef struct {
    STUHFL_T_InventorySlotInfoSync   slotSync;                                           /**< O Param: Slot sync information */
    STUHFL_T_InventorySlotInfo        slotInfoList[INVENTORYREPORT_SLOT_INFO_LIST_SIZE];  /**< O Param: Slot information list */
    uint16_t                            slotInfoListSize;                                   /**< O Param: Size of the slot information list */
} STUHFL_T_InventorySlotInfoData;

typedef struct {
    STUHFL_T_InventoryData             invData;            /**< O Param: Inventory data */
    STUHFL_T_InventorySlotInfoData   invSlotInfoData;    /**< O Param:  Extented slot information data */
} STUHFL_T_InventoryDataExt;
#endif  // USE_INVENTORY_EXT

// --------------------------------------------------------------------------
#define STUHFL_D_PASSWORD_LEN                4U
#define STUHFL_D_MAX_READ_DATA_LEN           64U
#define STUHFL_D_MAX_WRITE_DATA_LEN          2U
#define STUHFL_D_MAX_BLOCKWRITE_DATA_LEN     16U
typedef struct {
    uint32_t                            wordPtr;                    /**< I Param: Word address to which read data. */
    uint8_t                             memoryBank;                 /**< I Param: Bank (File, EPC, TID, USER) to which read data. */
    uint8_t                             numBytesToRead;             /**< I Param: Number of bytes to read. */
    uint8_t                             pwd[STUHFL_D_PASSWORD_LEN]; /**< I Param: Password. */
    uint8_t                             numReadBytes;               /**< O Param: Number of effectively read bytes. */
    uint8_t                             data[STUHFL_D_MAX_READ_DATA_LEN];    /**< O Param: Read data. */
} STUHFL_T_Read;
#define STUHFL_O_READ_INIT()        {0, 0, 0, {0}, 0, {0}}

typedef struct {
    uint32_t                            wordPtr;                    /**< I Param: Word address to which write data. */
    uint8_t                             memoryBank;                 /**< I Param: Bank (File, EPC, TID, USER) to which write data. */
    uint8_t                             pwd[STUHFL_D_PASSWORD_LEN]; /**< I Param: Password. */
    uint8_t                             data[STUHFL_D_MAX_WRITE_DATA_LEN];   /**< I Param: Data to be written. */
    uint8_t                             tagReply;                   /**< O Param: Tag reply. */
} STUHFL_T_Write;
#define STUHFL_O_WRITE_INIT()        {0, 0, {0}, {0}, 0}

typedef struct {
    uint32_t                            wordPtr;                    /**< I Param: Word address to which write data. */
    uint8_t                             pwd[STUHFL_D_PASSWORD_LEN]; /**< I Param: Password. */
    uint8_t                             memoryBank;                 /**< I Param: Bank (File, EPC, TID, USER) to which write data. */
    uint8_t                             numBytesToWrite;            /**< I Param: Number of bytes to write. NOTE: Only even number of bytes are allowed */
    uint8_t                             data[STUHFL_D_MAX_BLOCKWRITE_DATA_LEN];   /**< O Param: Data to be written. */
    uint8_t                             tagReply;                   /**< O Param: Tag reply. */
} STUHFL_T_BlockWrite;
#define STUHFL_O_BLOCKWRITE_INIT()      {0, {0}, 0, 0, {0}, 0}

typedef struct {
    uint8_t                             pwd[STUHFL_D_PASSWORD_LEN];         /**< I Param: Password. */
    uint8_t                             recommission;                       /**< I Param: Recommissionning. */
    uint8_t                             tagReply;                           /**< O Param: Tag reply. */
} STUHFL_T_Kill;
#define STUHFL_O_KILL_INIT()             {{0}, 0, 0}

#pragma pack(pop)

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __STUHFL_SL_H

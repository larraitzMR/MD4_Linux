
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include "STUHFL/inc/stuhfl.h"
#include "STUHFL/inc/stuhfl_err.h"
#include "STUHFL/inc/stuhfl_al.h"
#include "STUHFL/inc/stuhfl_sl.h"
#include "STUHFL/inc/stuhfl_sl_gen2.h"
#include "STUHFL/inc/stuhfl_sl_gb29768.h"

#include "STUHFL/inc/stuhfl_dl.h"
#include "STUHFL/inc/stuhfl_pl.h"
#include "STUHFL/inc/stuhfl_evalAPI.h"

#include "STUHFL/inc/platform/stuhfl_platform.h"
#include "STUHFL/inc/stuhfl_log.h"

#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "network.h"
#include "inventory.h"

static uint32_t startTickTime = 0;
static uint32_t totalTAGs = 0;

#define UPDATE_CYCLE_TIME_MS 400
static float maxReadRate = 0.0;
static float readRate = 0.0;

char epcbin[4];
char epc[24];
char mensaje[50];
char tid[24];
char tidbin[4];

STUHFL_T_ST25RU3993_TxRxCfg txRxCfg;

//SOCKET clientRead;


/**
  * @brief      Configuration for Inventory Runner + Gen2 Inventory.
  *
  * @param[in]  singleTag:      true: single tag -> no adaptive Q +  Q = 0<br>
  *                             false: multiple tags -> adaptive Q + Q = 4<br>
  * @param[in]  freqHopping:    true: EU frequency profile with hopping<br>
  *                             false: EU frequency profile without hopping<br>
  * @param[in]  antenna:        ANTENNA_1: Using Antenna 1<br>
  *                             ANTENNA_2: Using Antenna 2<br>
  *
  * @retval     None
  * 
  */

void setupGen2Config(bool singleTag, bool freqHopping, int antenna)
{
    printf("setupGen2Config\n");
    STUHFL_T_RET_CODE ret;

    STUHFL_T_ST25RU3993_Gen2_InventoryCfg invGen2Cfg = STUHFL_O_ST25RU3993_GEN2_INVENTORY_CFG_INIT();     // Set to FW default values
    invGen2Cfg.inventoryOption.fast = true;
    invGen2Cfg.inventoryOption.autoAck = false;
    invGen2Cfg.antiCollision.startQ = singleTag ? 0 : 4;
    invGen2Cfg.antiCollision.adaptiveQ = !singleTag;
    invGen2Cfg.adaptiveSensitivity.enable = true;
    invGen2Cfg.queryParams.toggleTarget = true;
    invGen2Cfg.queryParams.targetDepletionMode = true;
    ret = Set_Gen2_InventoryCfg(&invGen2Cfg);
    printf("Set_Gen2_InventoryCfg %d\n", ret);

    //
    STUHFL_T_ST25RU3993_Gen2_ProtocolCfg gen2ProtocolCfg = STUHFL_O_ST25RU3993_GEN2_PROTOCOL_CFG_INIT();  // Set to FW default values
    gen2ProtocolCfg.tari = STUHFL_D_GEN2_TARI_12_50;
    gen2ProtocolCfg.blf = STUHFL_D_GEN2_BLF_320;
    gen2ProtocolCfg.coding = STUHFL_D_GEN2_CODING_MILLER2;
    gen2ProtocolCfg.trext = STUHFL_D_TREXT_ON;
    ret = Set_Gen2_ProtocolCfg(&gen2ProtocolCfg);
    printf("Set_Gen2_ProtocolCfg %d\n", ret);

    STUHFL_T_ST25RU3993_FreqLBT freqLBT = STUHFL_O_ST25RU3993_FREQ_LBT_INIT();                          // Set to FW default values
    freqLBT.listeningTime = 0;
    ret = Set_FreqLBT(&freqLBT);
    printf("Set_FreqLBT %d\n", ret);

    STUHFL_T_ST25RU3993_FreqHop freqHop = STUHFL_O_ST25RU3993_FREQ_HOP_INIT();              // Set to FW default values
    ret = Set_FreqHop(&freqHop);
    printf("Set_FreqHop %d\n", ret);

    STUHFL_T_Gen2_Select    Gen2Select = STUHFL_O_GEN2_SELECT_INIT();                        // Set to FW default values
    Gen2Select.mode = STUHFL_D_GEN2_SELECT_MODE_CLEAR_LIST;  // Clear all Select filters
    ret = Gen2_Select(&Gen2Select);
    printf("Gen2_Select %d\n", ret);

    STUHFL_T_ST25RU3993_ChannelList channelList = STUHFL_O_ST25RU3993_CHANNEL_LIST_INIT();
    ret = Set_ChannelList(&channelList);       // Nota: Profile is implicitely switched to STUHFL_D_PROFILE_NEWTUNING
    printf("Set_ChannelList %d\n", ret);

    channelList.antenna = STUHFL_D_ANTENNA_1;
    ret = Set_ChannelList(&channelList);
    printf("Set_ChannelList 1 %d\n", ret);

    channelList.antenna = STUHFL_D_ANTENNA_2;
    ret = Set_ChannelList(&channelList);
    printf("Set_ChannelList 2 %d\n", ret);

    channelList.antenna = STUHFL_D_ANTENNA_3;
    ret = Set_ChannelList(&channelList);
    printf("Set_ChannelList 3 %d\n", ret);
    channelList.antenna = STUHFL_D_ANTENNA_4;
    ret = Set_ChannelList(&channelList);
    printf("Set_ChannelList 4 %d\n", ret);

    // printf("Tuning Profile frequencies: algo: TUNING_ALGO_SLOW %d\n", ret);

    // Get freq profile + number of frequencies
    STUHFL_T_ST25RU3993_FreqProfileInfo   freqProfileInfo = STUHFL_O_ST25RU3993_FREQ_PROFILE_INFO_INIT();
    freqProfileInfo.profile = STUHFL_D_PROFILE_EUROPE;
    ret = Set_FreqProfile(&freqProfileInfo);
    printf("Set_FreqProfile %d\n", ret);

    //TUNNING FRECUENCY FOR CURRENT PROFILE AND CURRENT ANTENNA
    ret = Get_FreqProfileInfo(&freqProfileInfo);
    printf("Get_FreqProfileInfo %d\n", ret);
    // Tune for each freq
    for (uint8_t i=0 ; i<freqProfileInfo.numFrequencies ; i++) {
        STUHFL_T_ST25RU3993_TuningTableEntry    tuningTableEntry = STUHFL_O_ST25RU3993_TUNING_TABLE_ENTRY_INIT();
        STUHFL_T_ST25RU3993_AntennaPower       antPwr = STUHFL_O_ST25RU3993_ANTENNA_POWER_INIT();
        STUHFL_T_ST25RU3993_Tune                tune = STUHFL_O_ST25RU3993_TUNE_INIT();

        tuningTableEntry.entry = i;
        ret = Get_TuningTableEntry(&tuningTableEntry);               // Retrieve frequency related to this entry
        printf("Get_TuningTableEntry %d\n", ret);

        tuningTableEntry.entry = i;
        memset(tuningTableEntry.applyCapValues, false, STUHFL_D_MAX_ANTENNA);    // Do not apply caps, only set entry
        ret = Set_TuningTableEntry(&tuningTableEntry);
        printf("Set_TuningTableEntry %d\n", ret);

        antPwr.mode = STUHFL_D_ANTENNA_POWER_MODE_ON;
        antPwr.timeout = 0;
        antPwr.frequency = tuningTableEntry.freq;
        ret = Set_AntennaPower(&antPwr);
        printf("Set_AntennaPower %d\n", ret);

        tune.algo = STUHFL_D_TUNING_ALGO_SLOW;
        ret = Tune(&tune);
        printf("Tune %d\n", ret);

        antPwr.mode = STUHFL_D_ANTENNA_POWER_MODE_OFF;
        antPwr.timeout = 0;
        antPwr.frequency = tuningTableEntry.freq;
        ret = Set_AntennaPower(&antPwr);
        printf("Set_AntennaPower %d\n", ret);
    }
}


/**
  * @brief      Inventory Runner run call back.
  *
  * @param[in]  data: Gen2 Inventory data
  *
  * @retval     STUHFL_ERR_NONE: No error happened
  * @retval     otherwise: An error occurred
  *
  */

STUHFL_T_RET_CODE inventoryRunner(STUHFL_T_InventoryData* data)
{

    static uint32_t localCycleTime = 0;
    uint32_t millis = getMilliCount();

    STUHFL_T_InventoryData* invData = ((STUHFL_T_InventoryData*)data);
    totalTAGs = invData->statistics.tagCnt;
    return STUHFL_ERR_NONE;
}

/**
  * @brief      Inventory Runner end call back.
  *
  * @param[in]  data: Gen2 Inventory data
  *
  * @retval     STUHFL_ERR_NONE: No error happened
  * @retval     otherwise: An error occurred
  *
  */

static STUHFL_T_RET_CODE inventoryRunnerEndCallBack(STUHFL_T_InventoryData* cycleData)
{
    //log2Screen(false, true, "    Inventory stopped after %d cycles\n    Processing Inventory end ...\n", cycleData->statistics.roundCnt);
    return STUHFL_ERR_NONE;
}

/**
  * @brief      Get Rwd registers demo
  *
  * @param      None
  *
  * @retval     None
  */
int readRegister(int regNumb)
{
    STUHFL_T_ST25RU3993_Register reg = STUHFL_O_ST25RU3993_REGISTER_INIT();
    reg.addr = (uint8_t)regNumb;
    reg.data = (uint8_t)0;
    Get_Register(&reg);
    printf("Register address: %u data: %u\n", reg.addr, reg.data);
    return reg.data;
}

/**
  * @brief      Get Rwd registers demo
  *
  * @param      None
  *
  * @retval     None
  */
int readRegister9()
{
    STUHFL_T_ST25RU3993_Register reg = STUHFL_O_ST25RU3993_REGISTER_INIT();
    reg.addr = (uint8_t)9;
    reg.data = (uint8_t)0;
    Get_Register(&reg);
    printf("Register address: %u data: %u\n", reg.addr, reg.data);
    return reg.data;
}

/**
  * @brief      Get Rwd registers demo
  *
  * @param      None
  *
  * @retval     None
  */
int readRegister10()
{
    STUHFL_T_ST25RU3993_Register reg = STUHFL_O_ST25RU3993_REGISTER_INIT();
    reg.addr = (uint8_t)10;
    reg.data = (uint8_t)0;
    Get_Register(&reg);
    printf("Register address: %u data: %u\n", reg.addr, reg.data);
    return reg.data;
}

float calculateRSSI(int rssiLogI, int rssiLogQ)
{
    float rssi = 0.0;

    uint8_t reg09 = 0;
    uint8_t reg0A = 0;

    //reg09 = readRegister(9);
    //reg0A = readRegister(10);
    reg09 = readRegister9;
    reg0A = readRegister10;
    int reg0Adesp = reg0A >> 6;

    char reg09Hex[3];
    char reg0AHex[3];
    sprintf(reg09Hex, "%x", reg09);
    sprintf(reg0AHex, "%x", reg0A);

    int gain = reg0Adesp * 3;

    char* reg0Abyte = decimal_to_binary(reg0A);

    if (reg0Abyte[2] == "0") {
        gain = -gain;
    }
    else if ((reg0Abyte[7] == "0") && (reg0Abyte[8] == "1")) {
        gain = gain - 8;
    }
    else if ((reg0Abyte[7] == "0") && (reg0Abyte[8] == "1")) {
        gain = gain + 10;
    }

    int G = gain + 60;

    if ((strncmp(reg09Hex, "3F", 2) == 0) || (strncmp(reg09Hex, "BF", 2) == 0) || (strncmp(reg09Hex, "90", 2) == 0)) {
        G = G + 1; //BLF 160kHz
    }
    else if ((strncmp(reg09Hex, "24", 2) == 0) || (strncmp(reg09Hex, "27", 2) == 0)) {
        G = G + 2; //BLF 320kHz
    }
    else if ((strncmp(reg09Hex, "34", 2) == 0) || (strncmp(reg09Hex, "37", 2) == 0)) {
        G = G + 3; //BLF 256kHz and BLF 213kHz
    }
    else if ((strncmp(reg09Hex, "20", 2) == 0) || (strncmp(reg09Hex, "07", 2) == 0)) {
        G = G + 4; //BLF 640Khz
    }

    rssi = 2.1 * ((rssiLogI + rssiLogQ) / 2) - G;
    //printf("RSSI: %.2f\n", rssi);

    return rssi;
}



void logInventory(STUHFL_T_ActionCycleData data)
{

   
    STUHFL_T_InventoryData* invData = ((STUHFL_T_InventoryData*)data);
    //uint32_t duration = (invData->tagListSize ? invData->tagList[0].timestamp : invData->statistics.timestamp) - startTickTime;
    //readRate = duration ? ((float)totalTAGs * ((float)1000.0 / (float)duration)) : (float)0.0;
    //if (readRate > maxReadRate) {
    //    maxReadRate = readRate;
    //}
//    SOCKET clientRead = getSocketState();

    int clientRead = getSocketState();

    memset(epc, 0, sizeof(epc));
    memset(mensaje, 0, sizeof(mensaje));
    int rssiLogI = 0;
    int rssiLogQ = 0;
    uint8_t usedAntena = 0;

    //printf("INVDATA-> tagListSize = %dn", invData->tagListSize);
    if (invData->tagListSize != 0) {
        for (int tags = 0; tags < invData->tagListSize; tags++) {
            rssiLogI = invData->tagList[tags].rssiLogI;
            rssiLogQ = invData->tagList[tags].rssiLogQ;
            //printf("RSSI Log I %u Q %u\n", rssiLogI, rssiLogQ);
            //printf("RSSI Log Mean %u\n", rssiLogMean);
            float rssi = calculateRSSI(rssiLogI, rssiLogQ);

            for (int i = 0; i < invData->tagList[tags].epc.length; i++) {
                sprintf(epcbin, "%02x", invData->tagList[tags].epc.data[i]);
                strcat(epc, epcbin);
            }
            usedAntena = invData->tagList[tags].antenna;
            //sprintf(mensaje, "$%s,%u,%u#", epc, usedAntena, rssiLinQ);
            sprintf(mensaje, "$%s,%u,%.2f#", epc, usedAntena, rssi);
            printf("tag para enviar: %s\n", mensaje);
            memset(epc, 0, sizeof(epc));
            send_tcp_message(mensaje, clientRead);
            memset(mensaje, 0, sizeof(mensaje));
        }
    }
}

/**
  * @brief      Gen2 Select demo.<br>
  *             Set and launch Select
  *
  * @param[in]  epc: tag EPC to be selected
  * @param[in]  epcLen: tag EPC length
  *
  * @retval     None
  */

void selectTag(uint8_t* epc, uint8_t epcLen)
{
    STUHFL_T_Gen2_Select selData = STUHFL_O_GEN2_SELECT_INIT();

    selData.mode = STUHFL_D_GEN2_SELECT_MODE_CLEAR_AND_ADD;
    selData.target = STUHFL_D_GEN2_TARGET_SL;
    selData.action = 0;
    selData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
    selData.maskBitPointer = 0x00000020;
    if (epcLen > STUHFL_D_GEN2_MAX_SELECT_MASK_LENGTH) {
        epcLen = STUHFL_D_GEN2_MAX_SELECT_MASK_LENGTH;
    }
    memcpy(selData.mask, epc, epcLen);
    selData.maskBitLength = (epcLen == STUHFL_D_GEN2_MAX_SELECT_MASK_LENGTH) ? 0xFF : (uint8_t)(epcLen * 8);    // max mask length == 255 bits
    selData.truncation = 0;

    Gen2_Select(&selData);
    printf("Selected tag\n");
    for (int i = 0; i < epcLen; i++) {
        printf("%02x ", epc[i]);
    }
    printf("\n");
}

/**
  * @brief      Gen2 Read demo.<br>
  *             Read 16 bytes from user memory bank on a pre-selected tag and outputs data
  *
  * @param[out] data: buffer data
  *
  * @retval     None
  */
void demo_gen2Read(uint8_t* data)
{
    STUHFL_T_Read readData = STUHFL_O_READ_INIT();

    readData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
    readData.wordPtr = 0;
    readData.numBytesToRead = 16;
    memset(readData.pwd, 0, 4);

    if (Gen2_Read(&readData) == STUHFL_ERR_NONE) {
        memcpy(data, readData.data, readData.numReadBytes);   // Read may have eventually modified read length

        for (int i = 0; i < readData.numReadBytes; i++) {
            printf("%02x ", readData.data[i]);
        }
    }
    else {
        printf("NO SE PUEDE LEER\n");
    }
}


char* packInt(uint16_t x) {
    uint16_t myInt;
    char* packed = (char*)&myInt;
    char* ptrToX = (char*)&x;

    // If we want to store big and the architecture is already big or
    // if we want to store little and the architecture is already little
    // then we don't need to do anything special

    packed[0] = ptrToX[1];
    packed[1] = ptrToX[0];


    return myInt;
}


void writeTagData(uint16_t epc[6]) {
    //void writeTagData(char* epc) {
    uint16_t EPCBuf[8];
    uint16_t Buf[6] = { 0,0,0,0,0,0 };

    memcpy(&Buf[0], &epc[0], 4);
    memcpy(&Buf[1], &epc[1], 4);
    memcpy(&Buf[2], &epc[2], 4);
    memcpy(&Buf[3], &epc[3], 4);
    memcpy(&Buf[4], &epc[4], 4);
    memcpy(&Buf[5], &epc[5], 4);


    STUHFL_T_Write writeData = STUHFL_O_WRITE_INIT();

    writeData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
    writeData.wordPtr = 2;
    memset(writeData.pwd, 0, 4);
    memcpy(writeData.data, &Buf[0], 2);
    if (Gen2_Write(&writeData) == STUHFL_ERR_NONE) {
        printf("\nWRITE\n");
    }
    else {
        printf("\nTag cannot be written\n");
    }

    //writeData = STUHFL_O_WRITE_INIT();

    writeData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
    writeData.wordPtr = 3;
    memset(writeData.pwd, 0, 4);
    memcpy(writeData.data, &Buf[1], 2);
    if (Gen2_Write(&writeData) == STUHFL_ERR_NONE) {
        printf("\nWRITE\n");
    }
    else {
        printf("\nTag cannot be written\n");
    }

    //writeData = STUHFL_O_WRITE_INIT();

    writeData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
    writeData.wordPtr = 4;
    memset(writeData.pwd, 0, 4);
    memcpy(writeData.data, &Buf[2], 2);
    if (Gen2_Write(&writeData) == STUHFL_ERR_NONE) {
        printf("\nWRITE\n");
    }
    else {
        printf("\nTag cannot be written\n");
    }

    //writeData = STUHFL_O_WRITE_INIT();
    writeData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
    writeData.wordPtr = 5;
    memset(writeData.pwd, 0, 4);
    //memcpy(writeData.data, "\x12\x34", 2);
    memcpy(writeData.data, &Buf[3], 2);
    if (Gen2_Write(&writeData) == STUHFL_ERR_NONE) {
        printf("\nWRITE\n");
    }
    else {
        printf("\nTag cannot be written\n");
    }

    //writeData = STUHFL_O_WRITE_INIT();
    writeData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
    writeData.wordPtr = 6;
    memset(writeData.pwd, 0, 4);
    memcpy(writeData.data, &Buf[4], 2);
    //memcpy(writeData.data, &Buf[1], 2);
    if (Gen2_Write(&writeData) == STUHFL_ERR_NONE) {
       printf("\nWRITE\n");
    }
    else {
        printf("\nTag cannot be written\n");
    }

    //writeData = STUHFL_O_WRITE_INIT();
    writeData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
    writeData.wordPtr = 7;
    memset(writeData.pwd, 0, 4);
    memcpy(writeData.data, &Buf[5], 2);
    //memcpy(writeData.data, &Buf[1], 2);
    if (Gen2_Write(&writeData) == STUHFL_ERR_NONE) {
        printf("\nWRITE\n");
    }
    else {
        printf("\nTag cannot be written\n");
    }
}



void logInventory(STUHFL_T_ActionCycleData data);

void setupGen2Config(bool singleTag, bool freqHopping, int antenna);

STUHFL_T_RET_CODE inventoryRunner(STUHFL_T_InventoryData* data);

static STUHFL_T_RET_CODE inventoryRunnerEndCallBack(STUHFL_T_InventoryData* cycleData);

void selectTag(uint8_t* epc, uint8_t epcLen);

//extern SOCKET clientRead;

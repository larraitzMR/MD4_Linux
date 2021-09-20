/*
 ============================================================================
 Name        : md4.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
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

#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

#include <stdio.h>
#include <stdlib.h>

#include "inventory.h"
#include "middleware.h"


#define BUFFER_SIZE 92
#define SND_BUFFER_SIZE         (STUHFL_D_UART_RX_BUFFER_SIZE)   /* HOST SND buffer based on FW RCV buffer */
#define RCV_BUFFER_SIZE         (STUHFL_D_UART_TX_BUFFER_SIZE)   /* HOST RCV buffer based on FW SND buffer */


// globals
#define LOG_BUF_SIZE    0xFFFF
static char logBuf[LOG_BUF_SIZE];
static int logBufPos = 0;

static uint32_t startTickTime = 0;
static uint32_t totalTAGs = 0;

#define UPDATE_CYCLE_TIME_MS 400
static float maxReadRate = 0.0;
static float readRate = 0.0;

static bool useNewTuningMechanism = false;


char epcbin[4];
char tidbin[4];
char epc[32];
char mensaje[60];
char tid[24];
int startReading = 0;


//Variables globales
int clientRead;
int clientTagRead;
static pthread_t inventoryT = INVALID_HANDLE_VALUE;


STUHFL_T_ST25RU3993_TxRxCfg txRxCfg;
//STUHFL_T_ST25RU3993_AntennaPower pwr;
STUHFL_T_Version swVer = STUHFL_O_VERSION_INIT();
STUHFL_T_Version hwVer = STUHFL_O_VERSION_INIT();
STUHFL_T_VersionInfo   swInfo = STUHFL_O_VERSION_INFO_INIT();
STUHFL_T_VersionInfo   hwInfo = STUHFL_O_VERSION_INFO_INIT();
STUHFL_T_ST25RU3993_Gen2_ProtocolCfg gen2ProtocolCfg = STUHFL_O_ST25RU3993_GEN2_PROTOCOL_CFG_INIT(); // Set to FW default values
STUHFL_T_ST25RU3993_FreqProfile freqProfile = STUHFL_O_ST25RU3993_FREQ_PROFILE_INIT();
STUHFL_T_ST25RU3993_Gen2_InventoryCfg invGen2Cfg  = STUHFL_O_ST25RU3993_GEN2_INVENTORY_CFG_INIT();


#define COM_PORT "/dev/ttyUSB0"


/**
  * @brief      Search for valid com ports
  *
  * @param[out] szPort: Found COM port.
  *
  * @retval     true: Found
  * @retval     false: otherwise
  */
static bool getComPort(char* szPort)
{
    // NOTE: currently search for valid com ports on posix devices is not implemented
    snprintf(szPort, 32, "%s", COM_PORT);

    return true;
}

int getSocketState()
{
    return clientRead;
}


void initParams() {

    setupGen2Config(false, true, STUHFL_D_ANTENNA_1);
    setupGen2Config(false, true, STUHFL_D_ANTENNA_2);
    setupGen2Config(false, true, STUHFL_D_ANTENNA_3);
    setupGen2Config(false, true, STUHFL_D_ANTENNA_4);
    STUHFL_T_ST25RU3993_AntennaSequence ant = STUHFL_O_ST25RU3993_ANTENNA_SEQUENCE_INIT();
    Set_AntennaSequence(&ant);
    Set_Gen2_InventoryCfg(&invGen2Cfg);
    txRxCfg.usedAntenna = STUHFL_D_ANTENNA_ALT;
    txRxCfg.txOutputLevel = 5;
    //printf("Antenna power: %d, Antenna sensitivity: %d\n",pwr.mode, txRxCfg.rxSensitivity);
    Set_TxRxCfg(&txRxCfg);
    printf("Set_TxRxCfg (txOutputLevel: %d, rxSensitivity: %d, usedAntenna: %d, alternateAntennaInterval: %d)\n", txRxCfg.txOutputLevel, txRxCfg.rxSensitivity, txRxCfg.usedAntenna, txRxCfg.alternateAntennaInterval);
}


void* runInventory() {

    printf("RUNNING INVENTORY\n");
    txRxCfg.usedAntenna = STUHFL_D_ANTENNA_ALT;
    Set_TxRxCfg(&txRxCfg);

    STUHFL_T_InventoryTag tagData[STUHFL_D_MAX_TAG_LIST_SIZE];
    // apply data storage location, where the found TAGs shall be stored
    STUHFL_T_InventoryData cycleData = STUHFL_O_INVENTORY_DATA_INIT();
    cycleData.tagList = tagData;
    cycleData.tagListSizeMax = STUHFL_D_MAX_TAG_LIST_SIZE;

    STUHFL_T_InventoryOption invOption = STUHFL_O_INVENTORY_OPTION_INIT();
    invOption.roundCnt = 0;        // Define expected rounds (0: infinite loop)
    invOption.options = STUHFL_D_INVENTORYREPORT_OPTION_HEARTBEAT;     // Enable HeartBeat for read rate calculation accuracy
     
    // before we start initalize statistic counters
    startTickTime = 0;
    totalTAGs = 0;
    maxReadRate = 0.0;
    readRate = 0.0;


    // blocking call
    Inventory_RunnerStart(&invOption, inventoryRunner, NULL, &cycleData);
}

void* stopInventory() {
    Inventory_RunnerStop();
}


int main(void) {
	//printf("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	   //Servidor socket


	    //SOCKADDR_IN  clientAddr;
	int st_fd = 0;
    int client = 0;
    int reading_fd = 0;
	int retval;
	int conectado = 0;

	char msg[BUFFER_SIZE + 1];

	STUHFL_T_DEVICE_CTX device = 0;
	uint8_t sndData[SND_BUFFER_SIZE];
	uint8_t rcvData[RCV_BUFFER_SIZE];

	char comPort[64];
	bool r = getComPort(comPort);
    printf("COM port: %s\n", comPort);
	if (!r) {
		return 0;
	}

	STUHFL_T_RET_CODE ret = STUHFL_F_SetParam(STUHFL_PARAM_TYPE_CONNECTION | STUHFL_KEY_PORT, (STUHFL_T_PARAM_VALUE)comPort);
	ret |= STUHFL_F_Connect(&device, sndData, SND_BUFFER_SIZE, rcvData, RCV_BUFFER_SIZE);

	// enable data line
	uint8_t on = TRUE;
	ret |= STUHFL_F_SetParam(STUHFL_PARAM_TYPE_CONNECTION | STUHFL_KEY_DTR, (STUHFL_T_PARAM_VALUE)&on);
	// toogle reset line
	on = TRUE;
	ret |= STUHFL_F_SetParam(STUHFL_PARAM_TYPE_CONNECTION | STUHFL_KEY_RTS, (STUHFL_T_PARAM_VALUE)&on);
	on = FALSE;
	ret |= STUHFL_F_SetParam(STUHFL_PARAM_TYPE_CONNECTION | STUHFL_KEY_RTS, (STUHFL_T_PARAM_VALUE)&on);

	initParams();

    st_fd = create_tcp_conection(5557) ;

    /* Esperar la petición del cliente. */
    if((client = accept(st_fd,(struct sockaddr*)NULL, 0))>0)
    {
        printf("Cliente conectado: %d\n", client);
         conectado = 1;
    }


  
    while (conectado == 1) {

        memset(msg, '\0', BUFFER_SIZE + 1);
        fflush(stdout);
        read_tcp_message(msg, client);
        char* mens = strtok(msg, "#");
        sprintf(msg, "%s", mens);
       // printf("%s\n", msg);

        if (strncmp(msg, "DISCONNECT", 10) == 0) {
            printf("msg: %s\n", msg);
            conectado = 0;
            send_tcp_message("OK#", client);
        }
        if (strncmp(msg, "POWER_MINMAX", 12) == 0)
        {
            printf("msg: %s\n", msg);
        }
        else if (strncmp(msg, "GET_POWER", 9) == 0) {
            printf("msg: %s\n", msg);
            char pow[6] = "";
            // Get current antenna
            Get_TxRxCfg(&txRxCfg); 
            
           // printf("outputLevel: %.1f antenna: %d\n", txRxCfg.txOutputLevel, txRxCfg.usedAntenna);
            //sprintf(pow, "%.1f#", txRxCfg.txOutputLevel);
            sprintf(pow, "%d#", txRxCfg.txOutputLevel);
           // sprintf(pow, "%.1f#", txRxCfg.txOutputLevel);

            send_tcp_message(pow, client);
        }
        else if (strncmp(msg, "SET_POWER", 9) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* pow = strtok(NULL, " "); 
            
            float value = atof(pow);

            STUHFL_T_ST25RU3993_AntennaPower pwr = STUHFL_O_ST25RU3993_ANTENNA_POWER_INIT();
            //printf("Antenna power: %d, Antenna sensitivity: %.1f\n", pwr.mode, txRxCfg.txOutputLevel);
            printf("Antenna power: %d, Antenna sensitivity: %d\n", pwr.mode, txRxCfg.txOutputLevel);
            printf("RECIBIDO POWER: %.1f\n", value);

            txRxCfg.txOutputLevel = value;
            Set_TxRxCfg(&txRxCfg);

            send_tcp_message("OK#", client);
        }
        else if (strncmp(msg, "GET_SEL_ANT", 11) == 0) {
            printf("msg: %s\n", msg);
            char sAnt[4];
            char selAntSend[16];

            STUHFL_T_ST25RU3993_AntennaSequence antenasConectadas;
            Get_AntennaSequence(&antenasConectadas);
            sprintf(selAntSend, "%u,%u,%u,%u#", antenasConectadas.antenna1, antenasConectadas.antenna2, antenasConectadas.antenna3, antenasConectadas.antenna4);
            printf("Selected antenas: %s\n", selAntSend);
            send_tcp_message(selAntSend, client);
        }
        else if (strncmp(msg, "SET_SEL_ANT", 11) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* con = strtok(NULL, "");
            printf("CONECTADAS: %s\n", con);

            char* token;
            int antena = 0;
            int conectadas = 0;
            int antenaConectada = 0;
            uint8_t arrayConectadas[4] = { 0 };

            token = strtok(con, ",");
            while (token != NULL) {
                txRxCfg.usedAntenna = antena;
                if (strcmp(token,"0") == 0)
                {
                    printf("ANTENA CONECTADA %d\n", antena);
                    arrayConectadas[antena] = STUHFL_D_ANTENNA_POWER_MODE_ON;
                    conectadas++;
                    antenaConectada = antena;
                }
                else {
                    printf("ANTENA NO CONECTADA %d\n", antena);
                    arrayConectadas[antena] = STUHFL_D_ANTENNA_POWER_MODE_OFF;
                }

                token = strtok(NULL, ",");
                antena++;
            }

            Set_AntennaSequence(&arrayConectadas);
           // printf("Set_AntennaSequence, y conectadas %dn", conectadas);
            STUHFL_T_ST25RU3993_AntennaPower pwr = STUHFL_O_ST25RU3993_ANTENNA_POWER_INIT();
            if (conectadas > 1) {
              //  printf("MAS DE UNA ANTENA CONECTADA");
                txRxCfg.usedAntenna = STUHFL_D_ANTENNA_ALT;
                Set_TxRxCfg(&txRxCfg);
            }
            else if (conectadas == 1) {
              //  printf("SOLO UNA ANTENA");
                txRxCfg.usedAntenna = antenaConectada;
                Set_TxRxCfg(&txRxCfg);
                Get_AntennaPower(&pwr);
                pwr.mode = STUHFL_D_ANTENNA_POWER_MODE_ON;
                Set_AntennaPower(&pwr);
            }
            send_tcp_message("OK#", client);
        }
        else if (strncmp(msg, "GET_INFO", 8) == 0) {
            printf("msg: %s\n", msg);
            char info[70];

            STUHFL_T_RET_CODE ret = Get_BoardVersion(&swVer, &hwVer);
            ret |= Get_BoardInfo(&swInfo, &hwInfo);
            sprintf(info, "%d.%d,%d.%d,%s,%s#", swVer.major, swVer.minor, hwVer.major, hwVer.minor, swInfo.info, hwInfo.info);

            printf("info: %s\n", info);
            send_tcp_message(info, client);
            memset(info, 0, sizeof(info));
        }
        else if (strncmp(msg, "GET_ADV_OPT", 11) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* advopt = strtok(NULL, "");
            char optionSend[16];
            memset(optionSend, 0, sizeof(optionSend));

            Get_Gen2_ProtocolCfg(&gen2ProtocolCfg);
            Get_FreqProfileInfo(&freqProfile);
            Get_Gen2_InventoryCfg(&invGen2Cfg);

            fflush(stdout);
            sprintf(optionSend, "%d,%d,%d,%d,%d,%d,%d#", freqProfile.profile, gen2ProtocolCfg.tari, gen2ProtocolCfg.blf, gen2ProtocolCfg.coding, invGen2Cfg.antiCollision.startQ, invGen2Cfg.queryParams.session, invGen2Cfg.queryParams.target);
            printf("Option: %s\n", optionSend);
            send_tcp_message(optionSend, client);
            memset(optionSend, 0, sizeof(optionSend));
        }
        else if (strncmp(msg, "SET_REGION", 10) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* reg = strtok(NULL, "");
            printf("REGION: %s\n", reg);
            fflush(stdout);
            int region = atoi(reg);

            switch (region)
            {
            case 0:
                printf("REGION CUSTOM");
                freqProfile.profile = STUHFL_D_PROFILE_CUSTOM;
                break;
            case 1:
                printf("REGION EUROPE");
                freqProfile.profile = STUHFL_D_PROFILE_EUROPE;
                break;
            case 2:
                freqProfile.profile = STUHFL_D_PROFILE_USA;
                break;
            case 3:
                freqProfile.profile = STUHFL_D_PROFILE_JAPAN;
                break;
            case 4:
                freqProfile.profile = STUHFL_D_PROFILE_CHINA;
                break;
            case 5:
                freqProfile.profile = STUHFL_D_PROFILE_CHINA2;
                break;
            default:
                break;
            }
            Set_FreqProfile(&freqProfile);
            send_tcp_message("OK#", client);
        }
        else if (strncmp(msg, "SET_TARI", 8) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* tari = strtok(NULL, "");
            printf("SET TARI: %s\n", tari);
            fflush(stdout);

            int tariValue = atoi(tari);

            switch (tariValue)
            {
            case 0:
                printf("TARI: 6_25\n");
                gen2ProtocolCfg.tari = STUHFL_D_GEN2_TARI_6_25;
                break;
            case 1:
                printf("TARI: 12_50\n");
                gen2ProtocolCfg.tari = STUHFL_D_GEN2_TARI_12_50;
                break;
            case 2:
                printf("TARI: 25_00\n");
                gen2ProtocolCfg.tari = STUHFL_D_GEN2_TARI_25_00;
                break;
            default:
                break;
            }

            Set_Gen2_ProtocolCfg(&gen2ProtocolCfg);
            fflush(stdout);
            send_tcp_message("OK#", client);
        }
        else if (strncmp(msg, "SET_BLF", 7) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* blf = strtok(NULL, "");
            printf("SET BLF: %s\n", blf);
            fflush(stdout);

            int blfInt = atoi(blf);

            switch (blfInt)
            {
            case 0:
                printf("BLF: 40\n");
                gen2ProtocolCfg.blf = STUHFL_D_GEN2_BLF_40;
                break;
            case 6:
                printf("BLF: 160\n");
                gen2ProtocolCfg.blf = STUHFL_D_GEN2_BLF_160;
                break;
            case 8:
                printf("BLF: 213\n");
                gen2ProtocolCfg.blf = STUHFL_D_GEN2_BLF_213;
                break;
            case 9:
                printf("BLF: 256\n");
                gen2ProtocolCfg.blf = STUHFL_D_GEN2_BLF_256;
                break;
            case 12:
                printf("BLF: 320\n");
                gen2ProtocolCfg.blf = STUHFL_D_GEN2_BLF_320;
                break;
            case 15:
                printf("BLF: 640\n");
                gen2ProtocolCfg.blf = STUHFL_D_GEN2_BLF_640;
                break;
            default:
                break;
            }

            Set_Gen2_ProtocolCfg(&gen2ProtocolCfg);
            fflush(stdout);
            send_tcp_message("OK#", client);
        }
        else if (strncmp(msg, "SET_M", 5) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* m = strtok(NULL, "");
            printf("SET M: %s\n", m);
            fflush(stdout);

            int mValue = atoi(m);

            switch (mValue)
            {
            case 0:
                printf("M: FM0\n");
                gen2ProtocolCfg.coding = STUHFL_D_GEN2_CODING_FM0;
                break;
            case 1:
                printf("M: M2\n");
                gen2ProtocolCfg.coding = STUHFL_D_GEN2_CODING_MILLER2;
                break;
            case 2:
                printf("M: M4\n");
                gen2ProtocolCfg.coding = STUHFL_D_GEN2_CODING_MILLER4;
                break;
            case 3:
                printf("M: M8\n");
                gen2ProtocolCfg.coding = STUHFL_D_GEN2_CODING_MILLER8;
                break;
            default:
                break;
            }

            Set_Gen2_ProtocolCfg(&gen2ProtocolCfg);
            fflush(stdout);
            send_tcp_message("OK#", client);
        }
        else if (strncmp(msg, "SET_Q", 5) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* m = strtok(NULL, "");
            int q = atoi(m);
            printf("Q: %d\n", q);
            invGen2Cfg.antiCollision.startQ = q;
            Set_Gen2_InventoryCfg(&invGen2Cfg);
            fflush(stdout);
            send_tcp_message("OK#", client);

        }
        else if (strncmp(msg, "SET_SESSION", 11) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* session = strtok(NULL, "");
            printf("SESION: %s\n", session);
            fflush(stdout);

            int ses = atoi(session);

            switch (ses)
            {
            case 0:
                printf("SESSION: 0\n");
                invGen2Cfg.queryParams.session = STUHFL_D_GEN2_SESSION_S0;
                break;
            case 1:
                printf("SESSION: 1\n");
                invGen2Cfg.queryParams.session = STUHFL_D_GEN2_SESSION_S1;
                break;
            case 2:
                printf("SESSION: 2\n");
                invGen2Cfg.queryParams.session = STUHFL_D_GEN2_SESSION_S2;
                break;
            case 3:
                printf("SESSION: 3\n");
                invGen2Cfg.queryParams.session = STUHFL_D_GEN2_SESSION_S3;
                break;
            default:
                break;
            }

            Set_Gen2_InventoryCfg(&invGen2Cfg);
            fflush(stdout);
            send_tcp_message("OK#", client);
        }
        else if (strncmp(msg, "SET_TARGET", 10) == 0) {
            printf("msg: %s\n", msg);
            char* mens = strtok(msg, " ");
            char* target = strtok(NULL, "");
            printf("SET TARGET: %s\n", target);

            int tar = atoi(target);

            switch (tar)
            {
            case 0:
                printf("TARGET: 0\n");
                invGen2Cfg.queryParams.target = STUHFL_D_GEN2_TARGET_A;
                break;
            case 1:
                printf("TARGET: 1\n");
                invGen2Cfg.queryParams.target = STUHFL_D_GEN2_TARGET_B;
                break;
            default:
                break;
            }

            Set_Gen2_InventoryCfg(&invGen2Cfg);
            fflush(stdout);

            send_tcp_message("OK#", client);
        }
        else if (strncmp(msg, "START_READING", 13) == 0) {

            printf("msg: %s\n", msg);
            send_tcp_message("OK#", client);

            st_fd = create_tcp_conection(5556);

            /* Esperar la petición del cliente. */
            if((clientRead = accept(st_fd,(struct sockaddr*)NULL, 0))>0)
            {
                printf("Cliente conectado: %d\n", client);
                //setSocket(clientRead);
            } else{
                 perror(NULL);
            }

            if (pthread_create(&inventoryT, NULL, runInventory, NULL)) {
                inventoryT = INVALID_HANDLE_VALUE;
            }
        }
        else if (strncmp(msg, "STOP_READING", 13) == 0) {
            printf("msg: %s\n", msg);
            send_tcp_message("OK#", client);

            if (pthread_create(&inventoryT, NULL, stopInventory, NULL)) {
                inventoryT = INVALID_HANDLE_VALUE;
            }

            close(st_fd);


            // HANDLE thread = CreateThread(NULL, 0, stopInventory, clientRead, 0, NULL);
            //  send_tcp_message("OK#");

            // closesocket(server);
        }
        else if (strncmp(msg, "READ_INFO", 9) == 0) {
            printf("msg: %s\n", msg);
            send_tcp_message("OK#", client);

            // startReading = 1;

            // server = configure_tcp_socket(5556);
            // if ((clientRead = accept(server, (struct sockaddr*)&clientAddrRead, &clientAddrSizeRead)) != INVALID_SOCKET)
            // {
            //     printf("Conectado para enviar tags!\n");
            //     setSocket(clientRead);
            // }

            // HANDLE thread = CreateThread(NULL, 0, readTagData, clientRead, 0, NULL);

        }
        else if (strncmp(msg, "WRITE_EPC", 9) == 0) {
            printf("msg: %s\n", msg);
           //  char EPCBuf[48];
           //  char EPC1Buf[16];
           //  char EPC2Buf[16];
           //  char EPC3Buf[16];
           //  uint16_t writeEPC[6];
           //  startReading = 0;

           //  char* mens = strtok(msg, " ");
           //  char* ant = strtok(NULL, " ");
           //  char* t = strtok(NULL, " ");
           //  char* TID = strtok(NULL, " ");
           //  char* EPC = strtok(NULL, " ");
           //  //char* EPC1 = strtok(NULL, " ");
           //  //char* EPC2 = strtok(NULL, " ");
           //  //char* EPC3 = strtok(NULL, " ");
           //  ////sprintf(EPCBuf, "%s", EPCHex);
           //  //sprintf(EPC1Buf, "%s", EPC1);
           //  //sprintf(EPC2Buf, "%s", EPC2); 
           //  //sprintf(EPC3Buf, "%s", EPC3);

           //  //string2hexString(EPC, writeEPC);

           //  int* ptr = hexadecimalToDecimal(EPC, writeEPC);

           //  STUHFL_T_Read readData = STUHFL_O_READ_INIT();

           //  readData.memoryBank = STUHFL_D_GEN2_MEMORY_BANK_EPC;
           //  readData.wordPtr = 0;
           //  readData.numBytesToRead = STUHFL_D_MAX_READ_DATA_LEN;
           //  memset(readData.pwd, 0, 4);

           //  readTagData();
           // // writeTagData(EPCBuf);
           //  writeTagData(writeEPC);
           //  //HANDLE thread = CreateThread(NULL, 0, writeTagData, writeEPC, 0, NULL);
            send_tcp_message("OK#", client);

        }
    }


	return EXIT_SUCCESS;
}

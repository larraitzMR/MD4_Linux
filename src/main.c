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

//
#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#define CLEAR_SCREEN()          system("cls");
#else
#endif

#define BUFFER_SIZE 92
#define SND_BUFFER_SIZE         (STUHFL_D_UART_RX_BUFFER_SIZE)   /* HOST SND buffer based on FW RCV buffer */
#define RCV_BUFFER_SIZE         (STUHFL_D_UART_TX_BUFFER_SIZE)   /* HOST RCV buffer based on FW SND buffer */

#define COM_PORT "/dev/ttyUSB0"


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


STUHFL_T_ST25RU3993_TxRxCfg txRxCfg;
//STUHFL_T_ST25RU3993_AntennaPower pwr;
STUHFL_T_Version swVer = STUHFL_O_VERSION_INIT();
STUHFL_T_Version hwVer = STUHFL_O_VERSION_INIT();
STUHFL_T_VersionInfo   swInfo = STUHFL_O_VERSION_INFO_INIT();
STUHFL_T_VersionInfo   hwInfo = STUHFL_O_VERSION_INFO_INIT();
STUHFL_T_ST25RU3993_Gen2_ProtocolCfg gen2ProtocolCfg = STUHFL_O_ST25RU3993_GEN2_PROTOCOL_CFG_INIT(); // Set to FW default values
STUHFL_T_ST25RU3993_FreqProfile freqProfile = STUHFL_O_ST25RU3993_FREQ_PROFILE_INIT();
STUHFL_T_ST25RU3993_Gen2_InventoryCfg invGen2Cfg  = STUHFL_O_ST25RU3993_GEN2_INVENTORY_CFG_INIT();


/*void initParams() {

    setupGen2Config(false, true, STUHFL_D_ANTENNA_1);
    setupGen2Config(false, true, STUHFL_D_ANTENNA_2);
    setupGen2Config(false, true, STUHFL_D_ANTENNA_3);
    setupGen2Config(false, true, STUHFL_D_ANTENNA_4);
    STUHFL_T_ST25RU3993_AntennaSequence ant = STUHFL_O_ST25RU3993_ANTENNA_SEQUENCE_INIT();
    Set_AntennaSequence(&ant);
    Set_Gen2_InventoryCfg(&invGen2Cfg);
    txRxCfg.usedAntenna = STUHFL_D_ANTENNA_ALT;
    //printf("Antenna power: %d, Antenna sensitivity: %d\n",pwr.mode, txRxCfg.rxSensitivity);
    Set_TxRxCfg(&txRxCfg);
}*/

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
#if defined(WIN32) || defined(WIN64)
    int port = 0;

    int ports[256];
    int nPorts = 0;
    char szComPort[32];
    HANDLE hCom = NULL;

    nPorts = 0;
    for (int i = 1; i <= 255; i++) {
        // test possible com boards
        snprintf(szComPort, sizeof(szComPort), "\\\\.\\COM%d", i);
        hCom = CreateFileA(szComPort,
            GENERIC_READ | GENERIC_WRITE,   // desired access should be read&write
            0,                              // COM port must be opened in non-sharing mode
            NULL,                           // don't care about the security
            OPEN_EXISTING,                  // IMPORTANT: must use OPEN_EXISTING for a COM port
            0,                              // usually overlapped but non-overlapped for existance test
            NULL);                          // always NULL for a general purpose COM port

        if (INVALID_HANDLE_VALUE != hCom) {
            // COM port exist
            ports[nPorts] = i;
            nPorts++;
            CloseHandle(hCom);
        }
    }
    if (nPorts == 0) {
        printf("Sorry, no serial port detected. press any key to terminate ..\n");
        while (!_kbhit());
        exit;
        return false;
    }
    else if (nPorts > 1) {
        printf("Found the following com ports: ");
        for (int i = 0; i < nPorts; i++) {
            printf("%d, ", ports[i]);
        }
        printf("\nPlease specify the port to use: ");
        port = _getch();
        port -= '0';
    }
    else {
        // exact one port found.
        port = ports[0];
    }
    snprintf(szPort, 32, "\\\\.\\COM%d", port);

#elif defined(POSIX)
    // NOTE: currently search for valid com ports on posix devices is not implemented
    snprintf(szPort, 32, "%s", COM_PORT);
#else
#endif
    //
    return true;
}




int16_t* hexadecimalToDecimal(char hexVal[], int16_t* data)
{
    int len = 24;

    // Initializing base value to 1, i.e 16^0
    int base = 1;
    int cont = 0;
    int write = 0;

    int dec_val = 0;
    int16_t writeData[6];
    int i = 0;
    // Extracting characters as digits from last character
    while (i < len - 1)
        //for (int i = 0; i < len; i++)
        //for (int i = len - 1; i >= 0; i--)
    {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value.
        if (hexVal[i + 1] >= '0' && hexVal[i + 1] <= '9')
        {
            dec_val += (hexVal[i + 1] - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i + 1] >= 'A' && hexVal[i + 1] <= 'F')
        {
            dec_val += (hexVal[i + 1] - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
        cont++;
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value.
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            dec_val += (hexVal[i] - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
        {
            dec_val += (hexVal[i] - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
        cont++;
        i++;
        i++;
        if (cont == 4) {
            writeData[write] = dec_val;
            data[write] = dec_val;
            write++;
            cont = 0;
            dec_val = 0;
            base = 1;
        }

    }
    //data = writeData;
    return data;
}


int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	   //Servidor socket


	    //SOCKADDR_IN  clientAddr;
	int st_fd = 0;
	int retval;
	int conectado = 0;

	char msg[BUFFER_SIZE + 1];

	STUHFL_T_DEVICE_CTX device = 0;
	uint8_t sndData[SND_BUFFER_SIZE];
	uint8_t rcvData[RCV_BUFFER_SIZE];

	char comPort[64];
	// char* comPort;
	bool r = getComPort(comPort);
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

	//initParams();

	st_fd = create_tcp_conection(5554) ;

	return EXIT_SUCCESS;
}


#include "stuhfl.h"
#include "stuhfl_err.h"
#include "stuhfl_al.h"
#include "stuhfl_sl.h"
#include "stuhfl_sl_gen2.h"
#include "stuhfl_sl_gb29768.h"

#include "stuhfl_dl.h"
#include "stuhfl_pl.h"
#include "stuhfl_evalAPI.h"

#include "platform/stuhfl_platform.h"
#include "stuhfl_log.h"

#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "middleware.h"



 

//
//
//void logInventory(STUHFL_T_ACTION_CYCLE_DATA data)
//{
//    STUHFL_T_Inventory_Data* invData = ((STUHFL_T_Inventory_Data*)data);
//    uint32_t duration = (invData->tagListSize ? invData->tagList[0].timestamp : invData->statistics.timestamp) - startTickTime;
//    readRate = duration ? ((float)totalTAGs * ((float)1000.0 / (float)duration)) : (float)0.0;
//    if (readRate > maxReadRate) {
//        maxReadRate = readRate;
//    }
//
//    memset(epc, 0, sizeof(epc));
//    memset(mensaje, 0, sizeof(mensaje));
//
//    for (int tags = 0; tags < invData->tagListSize; tags++) {
//        for (int i = 0; i < invData->tagList[tags].epc.len; i++) {
//            sprintf(epcbin, "%02x", invData->tagList[tags].epc.data[i]);
//            strcat(epc, epcbin);
//        }
//        sprintf(mensaje, "$%s#", epc);
//        printf("tag para enviar: %s\n", mensaje);
//        memset(epc, 0, sizeof(epc));
//        send(clientRead, mensaje, strlen(mensaje), 0);
//    }
//}
//
// 
 
 //Function to convert hexadecimal to decimal


//function to convert ascii char[] to hex-string (char[])
void string2hexString(char* input, char* output)
{
    int loop;
    int i;

    i = 0;
    loop = 0;

    while (input[loop] != '\0')
    {
        sprintf((char*)(output + i), "%02X", input[loop]);
        loop += 1;
        i += 2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}

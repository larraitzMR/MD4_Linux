
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

char* decimal_to_binary(int n)
{
    int c, d, t;
    char* p;

    t = 0;
    p = (char*)malloc(32 + 1);

    if (p == NULL)
        exit(EXIT_FAILURE);

    for (c = 7; c >= 0; c--)
    {
        d = n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    *(p + t) = '\0';

    return  p;
}
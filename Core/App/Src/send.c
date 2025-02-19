/*
 * @Date: 2025-02-04 10:54:03
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-18 21:00:54
 * @FilePath: \MDK-ARMd:\Mein_Werk\meine code\stm32projekt\scope\Core\App\Src\send.c
 */
#include "send.h"



TxPack tx_pack;

void sendinit()
{
    // Initialization code if needed
}

void sendvolt(float *sendbuffer)
{
    tx_pack.floats[0] = sendbuffer[0];
    tx_pack.floats[1] = sendbuffer[1];
    sendValuePack(&tx_pack);


        // printf("CH1:%fV,CH2:%fV.\r\n", sendbuffer[0], sendbuffer[1]);

}

void sendres(float *sendbuffer)
{
    // tx_pack.floats[2] = sendbuffer[2];
    // tx_pack.floats[3] = sendbuffer[3];
    // sendValuePack(&tx_pack);
    // printf("res1: %f, res2: %f\r\n", sendbuffer[0], sendbuffer[1]);
}


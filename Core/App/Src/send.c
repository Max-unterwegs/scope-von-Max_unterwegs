/*
 * @Date: 2025-02-04 10:54:03
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-12 11:54:00
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\App\Src\send.c
 */
#include "send.h"



void sendinit()
{
    // TxPack tx_pack;
}

void sendvolt(float *sendbuffer)
{
    // tx_pack.floats[0] = sendbuffer[0];
    // tx_pack.floats[1] = sendbuffer[1];
    // sendValuePack(&tx_pack);
    // printf("CH1_voltage: %f, CH2_voltage: %f, verfint_voltage: %f\r\n", sendbuffer[0], sendbuffer[1], sendbuffer[2]);
}

void sendres(float *sendbuffer)
{
    // tx_pack.floats[2] = sendbuffer[2];
    // tx_pack.floats[3] = sendbuffer[3];
    // sendValuePack(&tx_pack);
    // printf("res1: %f, res2: %f\r\n", sendbuffer[0], sendbuffer[1]);
}


/*
 * @Date: 2025-02-04 10:54:03
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:07:05
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\App\Src\send.c
 * @Description: 数据发送相关应用函数集
 */
#include "send.h"



TxPack tx_pack;//发送数据包
/**
 * @brief 数据发送初始化
 * @param void
 * @return void
 * @note 初始化数据发送
 * @author Max_unterwegs
 */
void sendinit()
{
    
}
/**
 * @brief 电压数据发送
 * @param sendbuffer: 发送缓存
 * @return void
 * @note 发送电压数据
 * @author Max_unterwegs
 */
void sendvolt(float *sendbuffer)
{
    tx_pack.floats[0] = sendbuffer[0];
    tx_pack.floats[1] = sendbuffer[1];
    sendValuePack(&tx_pack);


        // printf("CH1:%fV,CH2:%fV.\r\n", sendbuffer[0], sendbuffer[1]);

}
/**
 * @brief 电阻数据发送
 * @param sendbuffer: 发送缓存
 * @return void
 * @note 发送电阻数据
 * @author Max_unterwegs
 */
void sendres(float *sendbuffer)
{
    // tx_pack.floats[2] = sendbuffer[2];
    // tx_pack.floats[3] = sendbuffer[3];
    // sendValuePack(&tx_pack);
    // printf("res1: %f, res2: %f\r\n", sendbuffer[0], sendbuffer[1]);
}


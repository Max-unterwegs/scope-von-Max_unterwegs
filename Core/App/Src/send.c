/*
 * @Date: 2025-02-04 10:54:03
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:07:05
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\App\Src\send.c
 * @Description: ���ݷ������Ӧ�ú�����
 */
#include "send.h"



TxPack tx_pack;//�������ݰ�
/**
 * @brief ���ݷ��ͳ�ʼ��
 * @param void
 * @return void
 * @note ��ʼ�����ݷ���
 * @author Max_unterwegs
 */
void sendinit()
{
    
}
/**
 * @brief ��ѹ���ݷ���
 * @param sendbuffer: ���ͻ���
 * @return void
 * @note ���͵�ѹ����
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
 * @brief �������ݷ���
 * @param sendbuffer: ���ͻ���
 * @return void
 * @note ���͵�������
 * @author Max_unterwegs
 */
void sendres(float *sendbuffer)
{
    // tx_pack.floats[2] = sendbuffer[2];
    // tx_pack.floats[3] = sendbuffer[3];
    // sendValuePack(&tx_pack);
    // printf("res1: %f, res2: %f\r\n", sendbuffer[0], sendbuffer[1]);
}


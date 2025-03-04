/*
 * @Date: 2025-02-06 18:56:18
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-04 23:08:58
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Modeandmain\Src\mode.c
 */
#include "mode.h"
#include "function.h"
#include "status.h"
#include "show.h"
#include "send.h"


float voltages[3];
float res[2];
int functionshow[5] = {1, 1, 10,1,3};//0:DC 1:CH 2:BUZZER 3:OLED 4:SHOW
float paramshow[5] = {100, 10.1, 10.1, 3.3, 1000000};//0:DCarr 1:CH1mv 2:CH2mv 3:DCv 4:CHf


/**
 * @brief ���������ģʽ��ʼ��
 * ���ܰ���ͨ��������ֱ������������ݷ�����״̬ģʽ��ʾ����ز������ڣ�����״̬��ʾ
 */
void scope_init(void)
{
    // ��ʼ��ͨ������
    CH_control(functionshow[1]);
    // ��ʼ��ֱ�������
    DC_control(functionshow[0], paramshow[0]); // ʾ������
    // ��ʼ�����ݷ���
    sendinit();
    // ��ʼ����ز�������
    // ��ʼ������״̬��ʾ
}

/**
 * @brief ���������ģʽ������
 * ���ܰ���ͨ��������ֱ������������ݷ�����״̬ģʽ��ʾ����ز������ڣ�����״̬��ʾ
 */


void scope_main(void)
{
    // ��ʼ��ֱ�������
    DC_control(functionshow[0], paramshow[0]); // ʾ������
    // ִ��ֱ�������
    DC_vcontrol(paramshow[3]); // ʾ����ѹֵ
    // ִ����ز�������
    CH_fcontrol(paramshow[4], functionshow[1]);
    // ��ʼ��ͨ������
    CH_control(functionshow[1]);
    CH_vcontrol(1,(int)paramshow[1]);
    CH_vcontrol(2,(int)paramshow[2]);
    // ִ��ͨ������
    VOLT_ReadVoltages(voltages);
    //ת��ʵ�ʵ�ѹֵ
    voltage_map(voltages);
    // ִ�����ݷ���
    sendvolt(voltages);
    // ִ������״̬��ʾ
    showshow();
}

/**
 * @brief ���ñ�ģʽ��ʼ��
 * ���ܰ�����ѹ���������������ͨ�ϲ��������ݷ�����״̬��ʾ����ز�������
 */
void messer_init(void)
{
    // ��ʼ��ͨ������
    CH_control(functionshow[1]);
    // ��ʼ��ֱ�������
    DC_control(functionshow[0], paramshow[0]); // ʾ������
    // ��ʼ�����ݷ���
    sendinit();
    // ��ʼ��״̬ģʽ��ʾ
    // ��ʼ����ز�������
    // ��ʼ������״̬��ʾ
}

/**
 * @brief ���ñ�ģʽ������
 * ���ܰ�����ѹ���������������ͨ�ϲ��������ݷ�����״̬��ʾ����ز�������
 */
void messer_main(void)
{
     
     // ��ʼ��ֱ�������
     DC_control(functionshow[0], paramshow[0]); // ʾ������
     // ִ��ֱ�������
     DC_vcontrol(paramshow[3]); // ʾ����ѹֵ
     // ִ����ز�������
     CH_fcontrol(paramshow[4], functionshow[1]);
     // ��ʼ��ͨ������
     CH_control(functionshow[1]);
     CH_vcontrol(1,(int)paramshow[1]);
     CH_vcontrol(2,(int)paramshow[2]);
     // ִ��ͨ������
     VOLT_ReadVoltages(voltages);

    // ִ�е������
    Get_Res(paramshow[3],res,voltages);
     //ת��ʵ�ʵ�ѹֵ
     voltage_map(voltages);

     // ִ�����ݷ���
     sendvolt(voltages);
     sendres(res);
     // ִ������״̬��ʾ
     showshow();



}

/**
 * @brief �Զ�������ģʽ��ʼ��
 * Ŀǰû�й���
 */
void mu_init(void)
{
    // Ԥ����ʼ������
}

/**
 * @brief �Զ�������ģʽ������
 * Ŀǰû�й���
 */
void mu_main(void)
{
    // Ԥ������������
}

void allstop()
{
        // ֹͣͨ������
        HAL_ADC_Stop_DMA(&ADC_handle);
        HAL_TIM_Base_Stop(&CH_HAL_TIM);
        HAL_TIM_PWM_Stop(&CH1_HAL_TIM, CH1_CHANNEL);
        HAL_TIM_PWM_Stop(&CH2_HAL_TIM, CH2_CHANNEL);
        HAL_TIM_Base_Stop(&CH1_HAL_TIM);
        HAL_TIM_Base_Stop(&CH2_HAL_TIM);
    
        // ֱֹͣ�������
        HAL_TIM_PWM_Stop(&OUT_HAL_TIM, OUT_CHANNEL);
        HAL_TIM_Base_Stop(&OUT_HAL_TIM);
    
}

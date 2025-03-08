/*
 * @Date: 2025-02-06 18:56:18
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-08 10:32:27
 * @FilePath: \scope_project\Core\Modeandmain\Src\mode.c
 */
#include "mode.h"
#include "function.h"
#include "status.h"
#include "show.h"
#include "send.h"


float voltages[3];//0:CH1 1:CH2 2:Verfint
float res[2];//0:R1 1:R2
int functionshow[5] = {1, 1, 10,0,3};//0:DC 1:CH 2:Hz 3:wave 4:SHOW
float paramshow[7] = {100, 10.1, 10.1, 3.3, 1000000,3.3,0};//0:DCarr 1:CH1mv 2:CH2mv 3:DCv 4:CHf 5:ACA 6:ACV


/**
 * @brief ���������ģʽ��ʼ��
 * @param void
 * @return void
 * @note ���ܰ���ͨ����������������������ݷ�����״̬ģʽ��ʾ����ز������ڣ�����״̬��ʾ
 * @author Max_unterwegs
 */
void scope_init(void)
{
    // ��ʼ��ͨ������
    CH_control(functionshow[1]);
    // ��ʼ��ֱ�������
    DC_control(functionshow[0], paramshow[0]); // ʾ������
    // ��ʼ�����ݷ���
    sendinit();
}

/**
 * @brief ���������ģʽ������
 * @param void
 * @return void
 * @note ���ܰ���ͨ����������������������ݷ�����״̬ģʽ��ʾ����ز������ڣ�����״̬��ʾ
 * @author Max_unterwegs
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
 * @note ���ܰ�����ѹ���������������ͨ�ϲ�����ֱ������������ݷ�����״̬��ʾ����ز�������
 * @param void
 * @return void
 * @author Max_unterwegs
 */
void messer_init(void)
{
    // ��ʼ��ͨ������
    CH_control(functionshow[1]);
    // ��ʼ��ֱ�������
    DC_control(functionshow[0], paramshow[0]); // ʾ������
    // ��ʼ�����ݷ���
    sendinit();
}

/**
 * @brief ���ñ�ģʽ������
 * @note ���ܰ�����ѹ���������������ͨ�ϲ��������ݷ�����״̬��ʾ����ز�������
 * @bug �����������������
 * @param void
 * @return void
 * @author Max_unterwegs
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
 * @param void
 * @return void
 * @note Ŀǰû�й���
 * @author Max_unterwegs
 */
void mu_init(void)
{
    // Ԥ����ʼ������
}

/**
 * @brief �Զ�������ģʽ������
 * @param void
 * @return void
 * @note Ŀǰû�й���
 * @author Max_unterwegs
 */
void mu_main(void)
{
    // Ԥ������������
}
/**
 * @brief ֹͣ���й���
 * @param void
 * @return void
 * @note ֹͣ���й��ܣ�����ͨ����������������������ݷ�����״̬ģʽ��ʾ����ز������ڣ�����״̬��ʾ
 * @author Max_unterwegs
 */
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

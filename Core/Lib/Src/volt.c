/*
 * @Date: 2025-02-04 15:21:50
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:05:53
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Lib\Src\volt.c
 * @Description: ��ѹ������غ���
 */

#include "volt.h"
#include "printf.h"
#include "tim.h"


uint16_t adcValues[ADC_CHANNEL_NUM];//ADC����ֵ

/**
 * @brief ��ѹ������ʼ��
 * @param void
 * @return void
 * @note ��ʼ��ADC����
 * @attention ��
 * @author Max_unterwegs
 */
void VOLT_Init(void)
{
    //�ر�DMA1�ж�
    HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);
    HAL_TIM_Base_Start(&htim2);
    HAL_ADCEx_Calibration_Start( &ADC_handle ); // У׼ADC
    // ����ADCת��
    HAL_ADC_Start_DMA( &ADC_handle , (uint32_t*)adcValues, ADC_CHANNEL_NUM);
}

/**
 * @brief ��ȡ��ѹֵ
 * @param voltages: ��ѹֵ����
 * @return void
 * @note ��ȡADC����ֵ�������ѹֵ
 * @attention ��
 * @author Max_unterwegs
 */
void VOLT_ReadVoltages(float* voltages)
{
    
    // ��ȡ�ڲ��ο���ѹ��ADCֵ
    uint16_t vrefint_adc = adcValues[ADC_CHANNEL_Vrefint_index];
    // ����ʵ�ʵ��ڲ��ο���ѹֵ����λ��������
    float vrefint_actual = (1200.0/(float)vrefint_adc) * 4095.0;
    // ����ÿ��ͨ���ĵ�ѹֵ����λ�����أ�
    for (int i = 0; i < ADC_CHANNEL_NUM; i++)
    {
        voltages[i] = ((float)adcValues[i] / 4095.0) * vrefint_actual / 1000.0;
    }
}




/*
 * @Date: 2025-02-04 15:21:50
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-15 23:09:34
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Src\volt.c
 */

#include "volt.h"
#include "printf.h"
#include "tim.h"
// �洢ADC��ȡֵ������

int tmp;
uint16_t adcValues[ADC_CHANNEL_NUM];

// ��ʼ��ADC��DMA
void VOLT_Init(void)
{
    //�ر�DMA1�ж�
    HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);
    HAL_TIM_Base_Start(&htim2);
    HAL_ADCEx_Calibration_Start( &ADC_handle ); // У׼ADC
    // ����ADCת��
    HAL_ADC_Start_DMA( &ADC_handle , (uint32_t*)adcValues, ADC_CHANNEL_NUM);
}

// ��ȡ��ѹֵ���洢�ڴ����������
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

// // �û��Զ���� ADC ת����ɻص�����
// void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
// {
//     if (hadc == &hadc1) {
//         // ����ADCת�����
//         // ���磺��ӡ����ֵ
//         printf("ADC Value 0: %d\n", adcValues[0]);
//         printf("ADC Value 1: %d\n", adcValues[1]);
//         printf("ADC Value 2: %d\n", adcValues[2]);
//     }
// }


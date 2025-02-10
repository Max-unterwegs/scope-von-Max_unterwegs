/*
 * @Date: 2025-02-04 15:21:50
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 22:01:13
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Src\volt.c
 */

#include "volt.h"
#include "printf.h"
// �洢ADC��ȡֵ������

int tmp;

// ��ʼ��ADC��DMA
void VOLT_Init(void)
{
    int c1 = HAL_ADCEx_Calibration_Start( &ADC_handle ); // У׼ADC
    printf("c1: %d\r\n", c1);
    // ����ADCת��
    int c2 = HAL_ADC_Start_DMA( &ADC_handle , (uint32_t*)adcValues, ADC_CHANNEL_NUM);
    printf("c2: %d\r\n", c2);
}

// ��ȡ��ѹֵ���洢�ڴ����������
void VOLT_ReadVoltages(float* voltages)
{
    
    // ��ȡ�ڲ��ο���ѹ��ADCֵ
    uint16_t vrefint_adc = adcValues[ADC_CHANNEL_Vrefint_index];
    printf("vrefint_adc: %d\r\n", vrefint_adc);
    // ����ʵ�ʵ��ڲ��ο���ѹֵ����λ��������
    float vrefint_actual = (1200.0/(float)vrefint_adc) * 4095.0;
    printf("vrefint_actual: %f\r\n", vrefint_actual);
    // printf("CH1_adc: %f\r\n", voltages[0]);
    // printf("CH2_adc: %f\r\n", voltages[1]);
    // ����ÿ��ͨ���ĵ�ѹֵ����λ�����أ�
    for (int i = 0; i < ADC_CHANNEL_NUM - 1; i++)
    {
        voltages[i] = ((float)adcValues[i] / 4095.0) * vrefint_actual / 1000.0;
    }
}

// �û��Զ���� ADC ת����ɻص�����
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        // ���� ADC ת������¼�
        printf("ADC Conversion Complete\r\n");
        printf("CH1_adc: %d\r\n", adcValues[0]);
        printf("CH2_adc: %d\r\n", adcValues[1]);
        printf("CH3_adc: %d\r\n", adcValues[2]);
    }
}


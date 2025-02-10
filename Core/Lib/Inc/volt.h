/*
 * @Date: 2025-02-04 15:21:24
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-05 20:20:23
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Inc\volt.h
 */

#ifndef __VOLT_H
#define __VOLT_H

#include "main.h"
#include "adc.h"
/**
 * ��ȡ����ÿ��ͨ���ĵ�ѹֵ����λ�����أ�
 * ע�⣺Ĭ���ڲ��ο���ѹΪ 1.2V���ο���ѹΪ3.3V��Ӧ4095ADCֵ�����ǵĻ��Լ���һ��
 */

#define ADC_handle hadc1
#define ADC_CHANNEL_NUM 3
#define ADC_CHANNEL_Vrefint_index 2

static uint16_t adcValues[ADC_CHANNEL_NUM];

// ��ʼ��ADC��DMA
void VOLT_Init(void);

// ��ȡ��ѹֵ���洢�ڴ����������
void VOLT_ReadVoltages(float* voltages);

#endif

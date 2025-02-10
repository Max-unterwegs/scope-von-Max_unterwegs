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
 * 读取计算每个通道的电压值（单位：伏特）
 * 注意：默认内部参考电压为 1.2V，参考电压为3.3V对应4095ADC值，不是的话自己改一下
 */

#define ADC_handle hadc1
#define ADC_CHANNEL_NUM 3
#define ADC_CHANNEL_Vrefint_index 2

static uint16_t adcValues[ADC_CHANNEL_NUM];

// 初始化ADC和DMA
void VOLT_Init(void);

// 读取电压值并存储在传入的数组中
void VOLT_ReadVoltages(float* voltages);

#endif

/*
 * @Date: 2025-02-04 15:21:50
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 22:01:13
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Src\volt.c
 */

#include "volt.h"
#include "printf.h"
// 存储ADC读取值的数组

int tmp;

// 初始化ADC和DMA
void VOLT_Init(void)
{
    int c1 = HAL_ADCEx_Calibration_Start( &ADC_handle ); // 校准ADC
    printf("c1: %d\r\n", c1);
    // 启动ADC转换
    int c2 = HAL_ADC_Start_DMA( &ADC_handle , (uint32_t*)adcValues, ADC_CHANNEL_NUM);
    printf("c2: %d\r\n", c2);
}

// 读取电压值并存储在传入的数组中
void VOLT_ReadVoltages(float* voltages)
{
    
    // 获取内部参考电压的ADC值
    uint16_t vrefint_adc = adcValues[ADC_CHANNEL_Vrefint_index];
    printf("vrefint_adc: %d\r\n", vrefint_adc);
    // 计算实际的内部参考电压值（单位：毫伏）
    float vrefint_actual = (1200.0/(float)vrefint_adc) * 4095.0;
    printf("vrefint_actual: %f\r\n", vrefint_actual);
    // printf("CH1_adc: %f\r\n", voltages[0]);
    // printf("CH2_adc: %f\r\n", voltages[1]);
    // 计算每个通道的电压值（单位：伏特）
    for (int i = 0; i < ADC_CHANNEL_NUM - 1; i++)
    {
        voltages[i] = ((float)adcValues[i] / 4095.0) * vrefint_actual / 1000.0;
    }
}

// 用户自定义的 ADC 转换完成回调函数
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
        // 处理 ADC 转换完成事件
        printf("ADC Conversion Complete\r\n");
        printf("CH1_adc: %d\r\n", adcValues[0]);
        printf("CH2_adc: %d\r\n", adcValues[1]);
        printf("CH3_adc: %d\r\n", adcValues[2]);
    }
}


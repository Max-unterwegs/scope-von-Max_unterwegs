/*
 * @Date: 2025-02-04 15:21:50
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-15 23:09:34
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Src\volt.c
 */

#include "volt.h"
#include "printf.h"
#include "tim.h"
// 存储ADC读取值的数组

int tmp;
uint16_t adcValues[ADC_CHANNEL_NUM];

// 初始化ADC和DMA
void VOLT_Init(void)
{
    //关闭DMA1中断
    HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);
    HAL_TIM_Base_Start(&htim2);
    HAL_ADCEx_Calibration_Start( &ADC_handle ); // 校准ADC
    // 启动ADC转换
    HAL_ADC_Start_DMA( &ADC_handle , (uint32_t*)adcValues, ADC_CHANNEL_NUM);
}

// 读取电压值并存储在传入的数组中
void VOLT_ReadVoltages(float* voltages)
{
    
    // 获取内部参考电压的ADC值
    uint16_t vrefint_adc = adcValues[ADC_CHANNEL_Vrefint_index];
    // 计算实际的内部参考电压值（单位：毫伏）
    float vrefint_actual = (1200.0/(float)vrefint_adc) * 4095.0;
    // 计算每个通道的电压值（单位：伏特）
    for (int i = 0; i < ADC_CHANNEL_NUM; i++)
    {
        voltages[i] = ((float)adcValues[i] / 4095.0) * vrefint_actual / 1000.0;
    }
}

// // 用户自定义的 ADC 转换完成回调函数
// void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
// {
//     if (hadc == &hadc1) {
//         // 处理ADC转换结果
//         // 例如：打印采样值
//         printf("ADC Value 0: %d\n", adcValues[0]);
//         printf("ADC Value 1: %d\n", adcValues[1]);
//         printf("ADC Value 2: %d\n", adcValues[2]);
//     }
// }


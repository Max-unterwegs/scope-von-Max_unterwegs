/*
 * @Date: 2025-02-04 15:21:50
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:05:53
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Lib\Src\volt.c
 * @Description: 电压采样相关函数
 */

#include "volt.h"
#include "printf.h"
#include "tim.h"


uint16_t adcValues[ADC_CHANNEL_NUM];//ADC采样值

/**
 * @brief 电压采样初始化
 * @param void
 * @return void
 * @note 初始化ADC采样
 * @attention 无
 * @author Max_unterwegs
 */
void VOLT_Init(void)
{
    //关闭DMA1中断
    HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);
    HAL_TIM_Base_Start(&htim2);
    HAL_ADCEx_Calibration_Start( &ADC_handle ); // 校准ADC
    // 启动ADC转换
    HAL_ADC_Start_DMA( &ADC_handle , (uint32_t*)adcValues, ADC_CHANNEL_NUM);
}

/**
 * @brief 读取电压值
 * @param voltages: 电压值数组
 * @return void
 * @note 读取ADC采样值并计算电压值
 * @attention 无
 * @author Max_unterwegs
 */
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




/*
 * @Date: 2025-02-04 10:30:55
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:08:54
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Lib\Src\PWM.c
 * @Description: PWM直流电压输出相关函数
 */
#include "PWM.h"
#include "main.h"
#include "printf.h"



/**
 * @brief OUTPWM输出初始化
 * @param void
 * @return void
 * @note 初始化PWM输出
 * @attention 无
 * @author Max_unterwegs
 */
void PWM_OUT_Init( void )
{
  // printf("PWM_OUT_Init\r\n");
  HAL_TIM_PWM_Start( &OUT_HAL_TIM ,OUT_CHANNEL);
}
/**
 * @brief CHPWM输出初始化
 * @param void
 * @return void
 * @note 初始化PWM输出
 * @attention 无
 * @author Max_unterwegs
 */
void PWM_CH_Init( void )
{
  // printf("PWM_CH_Init\r\n");
  HAL_TIM_PWM_Start( &CH1_HAL_TIM ,CH1_CHANNEL);
  HAL_TIM_PWM_Start( &CH2_HAL_TIM ,CH2_CHANNEL);
}
/**
 * @brief PWM占空比设置
 * @param timx: 定时器
 * @param channel: 通道
 * @param duty: 占空比
 * @return void
 * @note 设置PWM占空比
 * @attention 无
 * @author Max_unterwegs
 */
void PWM_DutySet( TIM_TypeDef* timx, uint8_t channel, uint16_t duty )
{
  // printf("tim: channel:%d,duty:%d\r\n",channel,duty);
  switch( channel )
  {
    case TIM_CHANNEL_1:
    {
      timx->CCR1 = duty;
      break;
    }
    case TIM_CHANNEL_2:
    {
      timx->CCR2 = duty;
      break;
    }
    case TIM_CHANNEL_3:
    {
      timx->CCR3 = duty;
      break;
    }
    case TIM_CHANNEL_4:
    {
      timx->CCR4 = duty;
      break;
    }
  }
}
/**
 * @brief 直流电输出
 * @param timx: 定时器
 * @param channel: 通道
 * @param value: 电压值
 * @param arr: 自动重装载值
 * @return void
 * @note 直流电输出
 * @attention 无
 * @author Max_unterwegs
 */
void DC_OUT(TIM_TypeDef* timx, uint8_t channel, float value, uint16_t arr)
{
  PWM_DutySet(timx,channel,(uint16_t)((value/3.3)*arr));
}

/*
 * @Date: 2025-02-04 10:30:55
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-05 20:36:24
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Src\PWM.c
 */
#include "PWM.h"
#include "main.h"




/**
************************************************************************************************
* @brief    PWM初始化函数
* @param    None
* @return   None
* @author   None
************************************************************************************************
**/
void PWM_OUT_Init( void )
{
  HAL_TIM_PWM_Start( &OUT_HAL_TIM ,OUT_CHANNEL);
}
void PWM_CH_Init( void )
{
  HAL_TIM_PWM_Start( &CH1_HAL_TIM ,CH1_CHANNEL);
  HAL_TIM_PWM_Start( &CH2_HAL_TIM ,CH2_CHANNEL);
}
/**
************************************************************************************************
* @brief    PWM占空比设置函数
* @param    timx: 定时器 channel: 通道 duty: 占空比
* @return   None
* @author   None
************************************************************************************************
**/
void PWM_DutySet( TIM_TypeDef* timx, uint8_t channel, uint16_t duty )
{
  switch( channel )
  {
    case 1:
    {
      timx->CCR1 = duty;
      break;
    }
    case 2:
    {
      timx->CCR2 = duty;
      break;
    }
    case 3:
    {
      timx->CCR3 = duty;
      break;
    }
    case 4:
    {
      timx->CCR4 = duty;
      break;
    }
  }
}

void DC_OUT(TIM_TypeDef* timx, uint8_t channel, float value, uint16_t arr)
{
  PWM_DutySet(timx,channel,(uint16_t)((value/3.3)*arr));
}

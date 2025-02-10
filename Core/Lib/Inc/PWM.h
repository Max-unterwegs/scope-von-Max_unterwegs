/*
 * @Date: 2025-02-04 10:30:55
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-05 20:56:33
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Inc\PWM.h
 */

#ifndef __PWM_H
#define __PWM_H

#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_tim.h"
#include "tim.h"

#define CH1_HAL_TIM  htim3
#define CH1_TIM      TIM3
#define CH1_CHANNEL  TIM_CHANNEL_1
#define CH2_HAL_TIM  htim3
#define CH2_TIM      TIM3
#define CH2_CHANNEL  TIM_CHANNEL_4
#define OUT_HAL_TIM  htim1
#define OUT_TIM      TIM1
#define OUT_CHANNEL  TIM_CHANNEL_2
#define CH_HAL_TIM   htim2


void PWM_OUT_Init( void );
void PWM_CH_Init( void );
void PWM_DutySet( TIM_TypeDef* timx, uint8_t channel, uint16_t duty );
void DC_OUT(TIM_TypeDef* timx, uint8_t channel, float value, uint16_t arr);
#endif

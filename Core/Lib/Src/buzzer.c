/*
 * @Date: 2025-02-04 15:21:41
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 19:22:12
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Src\buzzer.c
 */
#include "buzzer.h"


void buzzer_on(void)
{
    HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, GPIO_PIN_SET);
}

void buzzer_off(void)
{
    HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, GPIO_PIN_RESET);
}

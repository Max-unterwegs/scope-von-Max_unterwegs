/*
 * @Date: 2025-02-04 15:21:41
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:06:50
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Lib\Src\buzzer.c
 * @Description: 蜂鸣器驱动相关函数
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

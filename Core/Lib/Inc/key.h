/*
 * @Date: 2025-02-04 10:30:55
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-23 14:43:25
 * @FilePath: \MDK-ARMd:\Mein_Werk\meine code\stm32projekt\scope\Core\Lib\Inc\key.h
 */
#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "status.h"
#include "mode.h"
#include "printf.h"
#include "tim.h"


// 按键状态结构体，存储几个变量
typedef struct
{
	uint8_t KeyLogic;       // 按键逻辑状态
	uint8_t KeyPhysic;      // 按键物理状态
	uint8_t KeyONCounts;    // 按键按下计数
	uint8_t KeyOFFCounts;   // 按键松开计数
	
	// 增加两个信息
	uint8_t MulClickCounts; // 多次点击计数
	uint8_t MulClickFlag;   // 多次点击标志
} KEY_TypeDef;

typedef struct 
{
	uint8_t forp;
	uint8_t index;
}select_Typedef;

#define		KEY_IDLE		8  // 按键空闲状态
#define		KEY_ERROR		10 // 按键错误状态
#define    	KEY_HOLD		7  // 按键保持状态

/* user setup */

/* 按键高低电平设置 */
// 按下时为高电平的设置，若按下为低电平注意对调on和off
// 此时按键低电平按下，高电平松开
#define    	KEY_OFF	   		1  // 按键松开状态
#define    	KEY_ON	   	 	0  // 按键按下状态

/* 按键多次点击设置 */
#define    	KEY_1ClICK				KEY_ON  // 单击
#define    	KEY_2ClICK				2       // 双击
#define    	KEY_3ClICK				3       // 三击
#define    	KEY_4ClICK				4       // 四击
#define    	KEY_5ClICK				5       // 五击
#define     KEY_MAX_MULCLICK		KEY_5ClICK  // 最大多次点击数

/* 按键参数设置 */
#define		HOLD_COUNTS					100  // 按键保持计数
#define 	SHAKES_COUNTS				3    // 按键抖动计数
#define		MULTIPLE_CLICK_COUNTS		10   // 多次点击计数

#define		KEY_NUMS		5  // 按键数量


// 初始化按键状态数组
static KEY_TypeDef Key[KEY_NUMS] =
	{
	 {KEY_OFF, KEY_OFF, 0, 0, 0, KEY_1ClICK},  
	 {KEY_OFF, KEY_OFF, 0, 0, 0, KEY_1ClICK},
	 {KEY_OFF, KEY_OFF, 0, 0, 0, KEY_1ClICK},
	 {KEY_OFF, KEY_OFF, 0, 0, 0, KEY_1ClICK},
	 {KEY_OFF, KEY_OFF, 0, 0, 0, KEY_1ClICK}
	}; 

extern int functionshow[];
extern float paramshow[];
extern int status;
uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
int8_t Encoder_Scan(uint8_t EC11_A_Now, uint8_t EC11_B_Now);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif

/*
 * @Date: 2025-02-05 18:02:39
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-12 22:58:34
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\App\Inc\function.h
 */
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "PWM.h"
#include "volt.h"
#include "show.h"

#define HCLK 64000000


extern float adcValues[ADC_CHANNEL_NUM];


void DC_control(char isopen,int arris);
void DC_vcontrol(float value);
void CH_control(char isCHopen);
void CH_vcontrol(char chnum,char chvmode);
void CH_fcontrol(float freq, char isCHopen);
void voltage_map(float* mapbuffer);
void Get_Res(float vsvalue,float* resbuffer,float* mapbuffer);
#endif 

/*
 * @Date: 2025-02-06 18:56:18
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-04 23:08:58
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Modeandmain\Src\mode.c
 */
#include "mode.h"
#include "function.h"
#include "status.h"
#include "show.h"
#include "send.h"


float voltages[3];
float res[2];
int functionshow[5] = {1, 1, 10,1,3};//0:DC 1:CH 2:BUZZER 3:OLED 4:SHOW
float paramshow[5] = {100, 10.1, 10.1, 3.3, 1000000};//0:DCarr 1:CH1mv 2:CH2mv 3:DCv 4:CHf


/**
 * @brief 采样与输出模式初始化
 * 功能包括通道采样，直流电输出，数据发送与状态模式显示，相关参数调节，其余状态显示
 */
void scope_init(void)
{
    // 初始化通道采样
    CH_control(functionshow[1]);
    // 初始化直流电输出
    DC_control(functionshow[0], paramshow[0]); // 示例参数
    // 初始化数据发送
    sendinit();
    // 初始化相关参数调节
    // 初始化其余状态显示
}

/**
 * @brief 采样与输出模式主函数
 * 功能包括通道采样，直流电输出，数据发送与状态模式显示，相关参数调节，其余状态显示
 */


void scope_main(void)
{
    // 初始化直流电输出
    DC_control(functionshow[0], paramshow[0]); // 示例参数
    // 执行直流电输出
    DC_vcontrol(paramshow[3]); // 示例电压值
    // 执行相关参数调节
    CH_fcontrol(paramshow[4], functionshow[1]);
    // 初始化通道采样
    CH_control(functionshow[1]);
    CH_vcontrol(1,(int)paramshow[1]);
    CH_vcontrol(2,(int)paramshow[2]);
    // 执行通道采样
    VOLT_ReadVoltages(voltages);
    //转换实际电压值
    voltage_map(voltages);
    // 执行数据发送
    sendvolt(voltages);
    // 执行其余状态显示
    showshow();
}

/**
 * @brief 万用表模式初始化
 * 功能包括电压测量，电阻测量，通断测量，数据发送与状态显示，相关参数调节
 */
void messer_init(void)
{
    // 初始化通道采样
    CH_control(functionshow[1]);
    // 初始化直流电输出
    DC_control(functionshow[0], paramshow[0]); // 示例参数
    // 初始化数据发送
    sendinit();
    // 初始化状态模式显示
    // 初始化相关参数调节
    // 初始化其余状态显示
}

/**
 * @brief 万用表模式主函数
 * 功能包括电压测量，电阻测量，通断测量，数据发送与状态显示，相关参数调节
 */
void messer_main(void)
{
     
     // 初始化直流电输出
     DC_control(functionshow[0], paramshow[0]); // 示例参数
     // 执行直流电输出
     DC_vcontrol(paramshow[3]); // 示例电压值
     // 执行相关参数调节
     CH_fcontrol(paramshow[4], functionshow[1]);
     // 初始化通道采样
     CH_control(functionshow[1]);
     CH_vcontrol(1,(int)paramshow[1]);
     CH_vcontrol(2,(int)paramshow[2]);
     // 执行通道采样
     VOLT_ReadVoltages(voltages);

    // 执行电阻测量
    Get_Res(paramshow[3],res,voltages);
     //转换实际电压值
     voltage_map(voltages);

     // 执行数据发送
     sendvolt(voltages);
     sendres(res);
     // 执行其余状态显示
     showshow();



}

/**
 * @brief 自定义整活模式初始化
 * 目前没有功能
 */
void mu_init(void)
{
    // 预留初始化代码
}

/**
 * @brief 自定义整活模式主函数
 * 目前没有功能
 */
void mu_main(void)
{
    // 预留主函数代码
}

void allstop()
{
        // 停止通道采样
        HAL_ADC_Stop_DMA(&ADC_handle);
        HAL_TIM_Base_Stop(&CH_HAL_TIM);
        HAL_TIM_PWM_Stop(&CH1_HAL_TIM, CH1_CHANNEL);
        HAL_TIM_PWM_Stop(&CH2_HAL_TIM, CH2_CHANNEL);
        HAL_TIM_Base_Stop(&CH1_HAL_TIM);
        HAL_TIM_Base_Stop(&CH2_HAL_TIM);
    
        // 停止直流电输出
        HAL_TIM_PWM_Stop(&OUT_HAL_TIM, OUT_CHANNEL);
        HAL_TIM_Base_Stop(&OUT_HAL_TIM);
    
}

/*
 * @Author: Max-unterwegs 14068827+max_unterwegs@user.noreply.gitee.com
 * @Date: 2025-01-18 22:26:44
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:07:21
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Lib\Src\printf.c
 * @Description: 重定向printf函数到串口
 */
#include <stdio.h>
#include <stdint.h>
#include <usart.h>
#include "printf.h"

/**
  * 函数功能: 重定向c库函数printf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit( &UART_HANDLE , (uint8_t *)&ch, 1, 0xffff );
  return ch;
}
 
/**
  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive( &UART_HANDLE , &ch, 1, 0xffff );
  return ch;
}

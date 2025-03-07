/*
 * @Author: Max-unterwegs 14068827+max_unterwegs@user.noreply.gitee.com
 * @Date: 2025-01-18 22:26:44
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:07:21
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Lib\Src\printf.c
 * @Description: �ض���printf����������
 */
#include <stdio.h>
#include <stdint.h>
#include <usart.h>
#include "printf.h"

/**
  * ��������: �ض���c�⺯��printf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit( &UART_HANDLE , (uint8_t *)&ch, 1, 0xffff );
  return ch;
}
 
/**
  * ��������: �ض���c�⺯��getchar,scanf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive( &UART_HANDLE , &ch, 1, 0xffff );
  return ch;
}

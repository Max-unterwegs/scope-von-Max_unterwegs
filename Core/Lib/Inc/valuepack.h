/*
 * @Author: Max-unterwegs 14068827+max_unterwegs@user.noreply.gitee.com
 * @Date: 2025-02-04 10:49:02
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 18:43:29
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Inc\valuepack.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef VALUEPACK_H_
#define VALUEPACK_H_

#include "main.h"
#include "dma.h"
#include "usart.h"

// 本程序通过DMA和USART 进行数据包的接收和发送
// 接收的数据自动写入到buffer中，通过定时调用readValuePack()函数来解析，定时间隔建议在10ms以内。
// 数据发送也采用DMA

/*
	使用说明：
	1.接收时，主程序中需开启DMA接收，示例如下：
		HAL_UART_Receive_DMA(&huart2, vp_rxbuff, VALUEPACK_BUFFER_SIZE);
	2.发送和接收模块需要定义一个TxPack和RxPack结构体，分别用于发送和接收数据包，示例如下：
		RxPack rx_pack;
		TxPack tx_pack;
	3.接收时调用readValuePack()函数，该函数会解析接收到的数据包，如果接收到完整的数据包，则返回1，否则返回0。（蓝牙每秒不低于10次）
		如果接收到完整的数据包，则会将数据包中的数据写入到rx_pack结构体中。示例如下：
		if(readValuePack(&rx_pack))
		{
			//接收到完整的数据包，可以在这里处理接收到的数据
		}
	4.发送时调用sendValuePack()函数，该函数会将tx_pack结构体中的数据发送出去。示例如下：
		sendValuePack(&tx_pack);
	
*/

// 0.指定使用的串口 --------------------------------------------------------------------------------
//串口和DMA的句柄
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

// 1.指定接收缓冲区的大小 --------------------------------------------------------------------------------
// 一般需要512字节以上，需要根据实际接收数据的速度和proc函数的频率考虑。
#define VALUEPACK_BUFFER_SIZE 1024

// 2.指定发送到手机的数据包的结构----------在发送时会自动额外在前后加上包头，包尾和校验和数据，因此会多出3个字节
// 根据实际需要的变量，定义数据包中 bool byte short int float 五种类型的数目

#define TX_BOOL_NUM 0
#define TX_BYTE_NUM 0
#define TX_SHORT_NUM 0
#define TX_INT_NUM 0
#define TX_FLOAT_NUM 2

// 3.指定接收数据包的结构-----------------------------------------------------------------------------------
// 根据实际需要的变量，定义数据包中 bool byte short int float 五种类型的数目

#define RX_BOOL_NUM 0
#define RX_BYTE_NUM 1
#define RX_SHORT_NUM 0
#define RX_INT_NUM 0
#define RX_FLOAT_NUM 0

typedef struct
{
#if TX_BOOL_NUM > 0
	unsigned char bools[TX_BOOL_NUM];
#endif

#if TX_BYTE_NUM > 0
	char bytes[TX_BYTE_NUM];
#endif

#if TX_SHORT_NUM > 0
	short shorts[TX_SHORT_NUM];
#endif

#if TX_INT_NUM > 0
	int integers[TX_INT_NUM];
#endif

#if TX_FLOAT_NUM > 0
	float floats[TX_FLOAT_NUM];
#endif
	char space; // 无意义，只为了不让结构体为空，结构体为空会报错。
} TxPack;
typedef struct
{
#if RX_BOOL_NUM > 0
	unsigned char bools[RX_BOOL_NUM];
#endif

#if RX_BYTE_NUM > 0
	char bytes[RX_BYTE_NUM];
#endif

#if RX_SHORT_NUM > 0
	short shorts[RX_SHORT_NUM];
#endif

#if RX_INT_NUM > 0
	int integers[RX_INT_NUM];
#endif

#if RX_FLOAT_NUM > 0
	float floats[RX_FLOAT_NUM];
#endif
	char space; // 无意义，只为了不让结构体为空，结构体为空会报错。
} RxPack;
// 初始化 valuepack 包括一些必要的硬件外设配置

//void initValuePack(int baudrate);

// 需要保证至少每秒执行10次该函数
// 该函数的主要过程是先解析接收的缓冲区，如果接收到完整的RX数据包，则解析RX数据包中的数据，然后开始串口发送TX数据包 。
// 接收到数据包时 返回 1 ，否则返回 0
unsigned char readValuePack(RxPack *rx_pack_ptr);
// 发送数据包
void sendValuePack(TxPack *tx_pack_ptr);

#define PACK_HEAD 0xa5
#define PACK_TAIL 0x5a

#endif /* VALUEPACK_H_ */


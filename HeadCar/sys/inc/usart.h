/****************************************************/
// MSP432P401R
// 串口配置
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
/****************************************************/

/******************   版本更新说明   *****************
 * 
 * CCS�?持printf
 * Keil�?持标准C库跟�?�?
 * 用Keil开发终于可以不开�?库啦
 * 
 * ? 需要注意：
 * ①使用标准C库时，将无法使用scanf�?
 * 如果需要使用scanf时，请使用微�? MicroLIB
 * ①低频时钟�?�率下，高波特率使得传输时�??�?过大,
 * 比�??35768Hz�?19200波特�?,
 * 会使得传输出错，这时�?以尝试降低波特率�?
 * �?baudrate_calculate的问题�?�去文件内查看�?
 * 
 * **************************************************
 * 
 * ? v3.2  2021/10/28
 * 简化�?�CCS�?持的printf代码
 *
 * ? v3.1  2021/10/18
 * 添加对CCS的printf�?�?
 *
 * ? v3.0  2021/10/15
 * 此版�?�?持使�? 标准C�?
 * 文件正式改名为与正点原子同名�?
 * usart.c �? usart.h，方便移�?
 * 仅支持Keil平台开�?
 *  
 * ? v2.1  2021/8/27
 * 添加�?持固件库v3_21_00_05
 * 仅支�? MicroLIB �?库、Keil平台开�?
 * 
 * ? v2.0  2021/8/25
 * uart_init增添了波特率传入参数，可直接配置波特率�?
 * 计算UART的代码单�?打包为名�?
 * baudrate_calculate的c文件和h文件
 * 仅支�? MicroLIB �?库、Keil平台开�?
 * 
 * ? v1.0 2021/7/17
 * 仅支持固件库v3_40_01_02
 * 配置了SMCLK 48MHz 波特�? 115200的初始化代码�?
 * 对接标准输入输出库，使其能使用printf、scanf函数
 * 仅支�? MicroLIB �?库、Keil平台开�?
 * 
 ****************************************************/

#ifndef __USART_H
#define __USART_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "stdio.h" //1.61328125kb

#ifdef __TI_COMPILER_VERSION__
//CCS平台
#include "stdarg.h"
#include "string.h"
#define USART0_MAX_SEND_LEN     600                 //最大发送缓存字节数
int printf(const char *str, ...);
#endif

void uart_init(uint32_t baudRate);
void uart2_init(uint32_t baudRate);

#endif

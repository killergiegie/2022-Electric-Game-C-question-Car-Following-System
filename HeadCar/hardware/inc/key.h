/****************************************************/
// MSP432P401R
// ���ذ�������
// Bilibili��m-RNA
// E-mail:m-RNA@qq.com
// ��������:2021/8/11
/****************************************************/

#ifndef __KEY_H
#define __KEY_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"

#define KEY1 BITBAND_PERI(P1IN, 1) // ��ȡ����1
#define KEY2 BITBAND_PERI(P1IN, 4) // ��ȡ����2

#define KEY1_PRES 1 // KEY1����
#define KEY2_PRES 2 // KEY2����

void KEY_Init(bool mode);    // IO��ʼ��
uint8_t KEY_Scan(bool mode); // ����ɨ�躯��

#endif

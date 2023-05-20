/****************************************************/
// MSP432P401R
// LED����
// Bilibili��m-RNA
// E-mail:m-RNA@qq.com
// ��������:2021/8/10
/****************************************************/

/**************************
 *
 * V1.2 2021/12/27
 * ֧��λ�����������Ч��
 *
 * V1.1 2021/9/13
 * ���������ɫ
 * ��Ϊ��֧��Multi_timer��չ��
 * ���궨���޸�Ϊ����
 *
 * V1.0 2021/8/10
 * ��ɻ�������
 *
 ************************/

#ifndef __LED_H
#define __LED_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"

// λ������
#define LED_RED BITBAND_PERI(P1OUT, 0)
#define LED_R BITBAND_PERI(P2OUT, 0)
#define LED_G BITBAND_PERI(P2OUT, 1)
#define LED_B BITBAND_PERI(P2OUT, 2)

#define BEEP BITBAND_PERI(P6OUT, 0)

void LED_Init(void);
void BEEP_Init(void);

void LED_RED_On(void);
void LED_RED_Off(void);
void LED_RED_Tog(void);

void LED_Y_On(void);
void LED_C_On(void);
void LED_P_On(void);

void LED_R_On(void);
void LED_G_On(void);
void LED_B_On(void);

void LED_R_Off(void);
void LED_G_Off(void);
void LED_B_Off(void);

void LED_R_Tog(void);
void LED_G_Tog(void);
void LED_B_Tog(void);

void LED_W_On(void);
void LED_W_Off(void);
void LED_W_Tog(void);

void BEEP_On(void);
void BEEP_Off(void);

#endif

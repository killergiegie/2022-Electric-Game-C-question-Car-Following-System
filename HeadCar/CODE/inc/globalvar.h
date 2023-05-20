#ifndef __GLOBALVAR_H
#define __GLOBALVAR_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "PIDcontrol.h"

// ������
extern int encoder_left;
extern int encoder_right;
extern float speed_left;
extern float speed_right;

// ������
extern int ult_distance;

extern float road; // ·��
extern int road_flag; // ·�̱�־λ
extern int lap; // Ȧ��
extern int task; // ����
extern int cross_flag; // ��·�ڱ�����Ȧ��־λ
extern int wait_flag;     // ��ͣ��־λ
extern int wait_time;     // ��ͣ��ʱ
extern int send_flag;     // ���ͱ�־λ
extern int last_send_flag;   // �ϴη��ͱ�־λ

// ���
extern PID pid_left, pid_right;
extern int movement; // movement_left, movement_right;
extern float movement_left, movement_right;
extern int motor_left;
extern int motor_left;
extern int motor_right;
extern int motor_flag;

// �Ҷȴ�����
extern int gray_state;
extern int small_kdiff;
extern int medium_kdiff;
extern int large_kdiff;

// ���ߴ���ͨ��
extern int usart0_rx_data;

// ������
extern int beep_flag;

//�޷�����
int myabs(int dat);

#include "sysinit.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "tim32.h"
#include "timA.h"
#include "oled.h"

#include "encoder.h"
#include "motor.h"
#include "grayscale.h"
#include "FSM.h"


#endif

#ifndef __GLOBALVAR_H
#define __GLOBALVAR_H

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "pid.h"

//������
extern int16_t encoder_left, encoder_right;
extern bool Dis_Calc_Flag;
extern float distance;
extern float per;

//���
extern bool motor_flag;
extern PID pid_left, pid_right;
extern float movement_left, movement_right, movement;
extern float differ;
extern float dis_movement;

//�Ҷȴ�����
extern bool L4,L3,L2,L1,M,MU,LU,RU,R1,R2,R3,R4;

//����Ҫ��
extern int8_t lap;          //Ȧ��
extern int8_t task;         //����
extern bool outer_road;     //����Ȧ��1��Ȧ��0��Ȧ
extern bool wait_stop_flag; //��ͣ��־λ
extern bool pre_stop_flag;  //Ԥֹͣ��־λ
extern bool chase_flag;     //���ٱ�־λ

//������
extern int16_t ult_distance;
extern bool ult_flag;
extern PID pid_dis;

#endif // !__GLOBALVAR_H

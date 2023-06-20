#ifndef __GLOBALVAR_H
#define __GLOBALVAR_H

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "pid.h"

//编码器
extern int16_t encoder_left, encoder_right;
extern bool Dis_Calc_Flag;
extern float distance;
extern float per;

//电机
extern bool motor_flag;
extern PID pid_left, pid_right;
extern float movement_left, movement_right, movement;
extern float differ;
extern float dis_movement;

//灰度传感器
extern bool L4,L3,L2,L1,M,MU,LU,RU,R1,R2,R3,R4;

//任务要求
extern int8_t lap;          //圈数
extern int8_t task;         //任务
extern bool outer_road;     //内外圈；1外圈，0内圈
extern bool wait_stop_flag; //等停标志位
extern bool pre_stop_flag;  //预停止标志位
extern bool chase_flag;     //加速标志位

//超声波
extern int16_t ult_distance;
extern bool ult_flag;
extern PID pid_dis;

#endif // !__GLOBALVAR_H

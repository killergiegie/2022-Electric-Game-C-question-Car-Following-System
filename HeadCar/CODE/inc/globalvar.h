#ifndef __GLOBALVAR_H
#define __GLOBALVAR_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "PIDcontrol.h"

// 编码器
extern int encoder_left;
extern int encoder_right;
extern float speed_left;
extern float speed_right;

// 超声波
extern int ult_distance;

extern float road; // 路程
extern int road_flag; // 路程标志位
extern int lap; // 圈数
extern int task; // 任务
extern int cross_flag; // 岔路口标内外圈标志位
extern int wait_flag;     // 等停标志位
extern int wait_time;     // 等停计时
extern int send_flag;     // 发送标志位
extern int last_send_flag;   // 上次发送标志位

// 电机
extern PID pid_left, pid_right;
extern int movement; // movement_left, movement_right;
extern float movement_left, movement_right;
extern int motor_left;
extern int motor_left;
extern int motor_right;
extern int motor_flag;

// 灰度传感器
extern int gray_state;
extern int small_kdiff;
extern int medium_kdiff;
extern int large_kdiff;

// 无线串口通信
extern int usart0_rx_data;

// 蜂鸣器
extern int beep_flag;

//限幅函数
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

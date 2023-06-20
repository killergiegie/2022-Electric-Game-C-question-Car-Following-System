#include "globalvar.h"

//编码器
int16_t encoder_left, encoder_right;
bool Dis_Calc_Flag = 0;
float distance;
float per = 0.02;

//电机
bool motor_flag = 0;
PID pid_left, pid_right;
float movement_left, movement_right, movement = 50;
float differ = 0;
float dis_movement = 0;

//灰度传感器
bool L4,L3,L2,L1,M,MU,LU,RU,R1,R2,R3,R4;

//任务要求
int8_t lap = 0;         //圈数
int8_t task = 5;        //任务
bool outer_road = 1;    //内外圈；1外圈，0内圈
bool wait_stop_flag = 0;//等停标志位
bool pre_stop_flag = 0; //预停止标志位
bool chase_flag = 0;    //加速标志位

//超声波
int16_t ult_distance = 50;
bool ult_flag = 1;
PID pid_dis;


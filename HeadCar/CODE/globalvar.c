#include "globalvar.h"

// 编码器
int encoder_left = 0;
int encoder_right = 0;
float speed_left = 0;
float speed_right = 0;

// 超声波
int ult_distance = 0;

// 状态
float road = 0;     // 路程
int road_flag = 0;  // 路程标志位
int lap = 0;        // 圈数
int task = 1;       // 任务
int cross_flag = 0; // 岔路口标内外圈标志位, 1为外圈, 0为内圈
int wait_flag = 0;  // 等停标志位
int wait_time = 0;  // 等停计时
int send_flag = 0;  // 发送标志位
int last_send_flag = 0;  // 上一次的发送标志位

// 电机
PID pid_left, pid_right;
int movement = 0; // movement_left = 0, movement_right = 0;
float movement_left = 0, movement_right = 0;
int motor_left = 0;
int motor_right = 0;
int motor_flag = 0;

// 灰度传感器
int gray_state = 0;
int small_kdiff = 0;
int medium_kdiff = 0;
int large_kdiff = 0;

// 无线串口通信
int usart0_rx_data = 0;

// 蜂鸣器
int beep_flag = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      绝对值函数
//  @param      dat				需要求绝对值的数
//  @return     int				返回绝对值
//  Sample usage:				dat = myabs(dat);//将dat变成正数
//-------------------------------------------------------------------------------------------------------------------
int myabs(int dat)
{
    if (dat >= 0)
        return dat;
    else
        return -dat;
}

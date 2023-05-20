#include "motor.h"

void Motor_Init(void)
{
    /*
     * 定时器PWM周期：
     *
     * T_timer_a = CLKDIV * (CCR0 + 1) / f_clk
     *           = 48 * （19999 + 1） / 48000000
     *           = 0.02s = 50Hz
    */
    //1.初始化定时器，设置电机PWM输出的频率，
    TimA0_PWM_Init(4799, 1); // 10000Hz
    // 初始化电机控制引脚
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2); // 设置P5.1|2|3为输出
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN5); // 设置P3.5为输出
}

void Motor_PID(void)
{
    Incremental_PID_Calc(&pid_left, movement_left, speed_left * 100);
    Incremental_PID_Calc(&pid_right, movement_right, speed_right * 100);
    Motor_Set(pid_left.output, pid_right.output);
}

void Motor_Set(int motor_left, int motor_right)
{
    int PWM_left = myabs(motor_left);
    int PWM_right = myabs(motor_right);
    if(motor_left >= 0)
    {
        AIN1_ON;
        AIN2_OFF;
    }
    else if(motor_left < 0)
    {
        AIN1_OFF;
        AIN2_ON;
    }
    // 通过更改传入的CCR1来改变通道1占空比
    // TA0.1
    MAP_Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, PWM_left); 

    if(motor_right >= 0)
    {
        BIN1_ON;
        BIN2_OFF;
    }
    else if(motor_right < 0)
    {
        BIN1_OFF;
        BIN2_ON;
    }
    // 通过更改传入的CCR2来改变通道2占空比
    // TA0.2
    MAP_Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, PWM_right); 
}


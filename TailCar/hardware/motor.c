#include "motor.h"

/*************电机初始化***************
PWMA - 7.6, AIN1 - 10.0, AIN2 - 10.2
PWMB - 7.7, BIN1 - 10.1, BIN2 - 10.3
*************************************/
void motor_Init(void)
{
    //初始化方向引脚
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 );
    //初始化PWM通道
    TimA1_PWM_Init(4800 - 1, 1);
    //初始化编码器
    Encoder_Init();
}

void motor_PID(void)
{
    //计算左右轮期望转速
    movement_left  = movement  + dis_movement - differ;
    movement_right = movement  + dis_movement + differ;
    //PID计算
    Incremental_PID_Calc(&pid_left, movement_left, encoder_left);
    Incremental_PID_Calc(&pid_right, movement_right, encoder_right);
    //清除编码器数值
    encoder_left  = 0;
    encoder_right = 0;
    //控制电机
    motor_set(pid_left.output, pid_right.output);
}

void motor_set(int PWM_left, int PWM_right)
{
    if (PWM_left >= 0)
    {
        //左电机正转
        GPIO_setOutputHighOnPin(GPIO_PORT_P10,GPIO_PIN0);	 	  //高电平    P10.0 --- AIN1     1
        GPIO_setOutputLowOnPin(GPIO_PORT_P10,GPIO_PIN2);  		  //低电平    P10.2 --- AIN2     0
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, PWM_left);
    }
    else if (PWM_left < 0)
    {
        //左电机反转
        GPIO_setOutputLowOnPin(GPIO_PORT_P10,GPIO_PIN0);	 	  //低电平    P10.0 --- AIN1     0   
        GPIO_setOutputHighOnPin(GPIO_PORT_P10,GPIO_PIN2);	 	  //高电平    P10.2 --- AIN2     1
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, -PWM_left);
    }

    if (PWM_right >= 0)
    {
        //右电机正转
        GPIO_setOutputHighOnPin(GPIO_PORT_P10,GPIO_PIN1);	 	  //高电平    P10.1 --- BIN1     1
        GPIO_setOutputLowOnPin(GPIO_PORT_P10,GPIO_PIN3);  		  //低电平    P10.3 --- BIN2     0
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, PWM_right);
    }
    else if (PWM_right < 0)
    {
        //右电机反转
        GPIO_setOutputLowOnPin(GPIO_PORT_P10,GPIO_PIN1);	 	  //低电平    P10.1 --- BIN1     0   
        GPIO_setOutputHighOnPin(GPIO_PORT_P10,GPIO_PIN3);	 	  //高电平    P10.3 --- BIN2     1
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, -PWM_right);
    }

}


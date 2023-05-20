#include "motor.h"

void Motor_Init(void)
{
    /*
     * ��ʱ��PWM���ڣ�
     *
     * T_timer_a = CLKDIV * (CCR0 + 1) / f_clk
     *           = 48 * ��19999 + 1�� / 48000000
     *           = 0.02s = 50Hz
    */
    //1.��ʼ����ʱ�������õ��PWM�����Ƶ�ʣ�
    TimA0_PWM_Init(4799, 1); // 10000Hz
    // ��ʼ�������������
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2); // ����P5.1|2|3Ϊ���
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN5); // ����P3.5Ϊ���
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
    // ͨ�����Ĵ����CCR1���ı�ͨ��1ռ�ձ�
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
    // ͨ�����Ĵ����CCR2���ı�ͨ��2ռ�ձ�
    // TA0.2
    MAP_Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, PWM_right); 
}


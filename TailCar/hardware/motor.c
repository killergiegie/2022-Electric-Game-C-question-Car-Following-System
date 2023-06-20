#include "motor.h"

/*************�����ʼ��***************
PWMA - 7.6, AIN1 - 10.0, AIN2 - 10.2
PWMB - 7.7, BIN1 - 10.1, BIN2 - 10.3
*************************************/
void motor_Init(void)
{
    //��ʼ����������
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 );
    //��ʼ��PWMͨ��
    TimA1_PWM_Init(4800 - 1, 1);
    //��ʼ��������
    Encoder_Init();
}

void motor_PID(void)
{
    //��������������ת��
    movement_left  = movement  + dis_movement - differ;
    movement_right = movement  + dis_movement + differ;
    //PID����
    Incremental_PID_Calc(&pid_left, movement_left, encoder_left);
    Incremental_PID_Calc(&pid_right, movement_right, encoder_right);
    //�����������ֵ
    encoder_left  = 0;
    encoder_right = 0;
    //���Ƶ��
    motor_set(pid_left.output, pid_right.output);
}

void motor_set(int PWM_left, int PWM_right)
{
    if (PWM_left >= 0)
    {
        //������ת
        GPIO_setOutputHighOnPin(GPIO_PORT_P10,GPIO_PIN0);	 	  //�ߵ�ƽ    P10.0 --- AIN1     1
        GPIO_setOutputLowOnPin(GPIO_PORT_P10,GPIO_PIN2);  		  //�͵�ƽ    P10.2 --- AIN2     0
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, PWM_left);
    }
    else if (PWM_left < 0)
    {
        //������ת
        GPIO_setOutputLowOnPin(GPIO_PORT_P10,GPIO_PIN0);	 	  //�͵�ƽ    P10.0 --- AIN1     0   
        GPIO_setOutputHighOnPin(GPIO_PORT_P10,GPIO_PIN2);	 	  //�ߵ�ƽ    P10.2 --- AIN2     1
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, -PWM_left);
    }

    if (PWM_right >= 0)
    {
        //�ҵ����ת
        GPIO_setOutputHighOnPin(GPIO_PORT_P10,GPIO_PIN1);	 	  //�ߵ�ƽ    P10.1 --- BIN1     1
        GPIO_setOutputLowOnPin(GPIO_PORT_P10,GPIO_PIN3);  		  //�͵�ƽ    P10.3 --- BIN2     0
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, PWM_right);
    }
    else if (PWM_right < 0)
    {
        //�ҵ����ת
        GPIO_setOutputLowOnPin(GPIO_PORT_P10,GPIO_PIN1);	 	  //�͵�ƽ    P10.1 --- BIN1     0   
        GPIO_setOutputHighOnPin(GPIO_PORT_P10,GPIO_PIN3);	 	  //�ߵ�ƽ    P10.3 --- BIN2     1
        MAP_Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, -PWM_right);
    }

}


/****************************************************/
// MSP432P401R
// ����Keil�����չ��� (�ѽ�ti�̼�����������)
// Keil���������ÿ���FPU
// Bilibili��m-RNA
// E-mail:m-RNA@qq.com
// ��������:2021/9/28
/****************************************************/

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "globalvar.h"

int key_flag = 0;
void system_init(void)
{
    LED_Init();
    BEEP_Init();
    KEY_Init(0);
    OLED_Init();
    Grayscale_Init();
    SW_Encoder_Init(); // ����������
    Motor_Init();      // �������
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN5);
    TimA3_Cap_Init();  // ��ʱ������Ϊ���벶��ģʽ�����ڳ�����ģ��
    TimA2_Int_Init(29999, 48); // ��ʱ��A3�ж�����,���ڴ������ж� 30ms
    TimA1_Int_Init(19999, 48); // ��ʱ��A1�ж�����,�����ٶȻ��ж�,50Hz, 20ms
    movement = 0.5 * 100; // ʵ���ٶ�0.5m/s
    movement_left  = (float)movement;
    movement_right = (float)movement;
    /* ��Ȧ���� */
    small_kdiff  = (int)(movement * 0.25);
    medium_kdiff = (int)(movement * 0.5);
    large_kdiff  = (int)(movement * 0.85);
    Incremental_PID_Init(&pid_left,  100, 3, 0, 85 * 48); // �ٶȻ�PID��������
    Incremental_PID_Init(&pid_right, 100, 3, 0, 85 * 48); 

    /*�ж����ȼ������мǶ�ʱ���ж����ȼ����ܸ����ⲿ�ж����ȼ�*/
    //�������ɼ��ж����ȼ�������Ϊ�ε�
    Interrupt_setPriority(INT_PORT2, 3 << 5);
    Interrupt_setPriority(INT_PORT4, 3 << 5);
    Interrupt_setPriority(INT_PORT5, 3 << 5);
    Interrupt_setPriority(INT_PORT6, 3 << 5);

    //�ٶȻ��ж����ȼ�������Ϊ���
    Interrupt_setPriority(INT_TA1_0, 2 << 5);

    // ͨ���ж����ȼ�������Ϊ���
    Interrupt_setPriority(INT_EUSCIA0, 4 << 5);

    /*����жϱ�־λ*/
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN6);
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN7);
    GPIO_clearInterrupt(GPIO_PORT_P5, GPIO_PIN6);
    GPIO_clearInterrupt(GPIO_PORT_P5, GPIO_PIN7);
    GPIO_clearInterrupt(GPIO_PORT_P6, GPIO_PIN6);
    GPIO_clearInterrupt(GPIO_PORT_P6, GPIO_PIN7);
}

int main(void)
{
    SysInit();         // ��3�� ʱ������
    uart_init(115200); // ��7�� ��������
    delay_init();      // ��4�� �δ���ʱ

    /*��ʼ����ʼ������*/
    system_init();
    /*ֹͣ����ʼ������*/

    //printf("Hello,MSP432!\r\n");
    delay_ms(200);
    MAP_Interrupt_enableMaster(); // �������ж�
    while (1)
    {
        /*��ʼ����û�����*/
        //printf("%d,", movement);
        //printf("%d\r\n", (int)(speed_left*100));
        //printf("left: %f    right: %f \r\n", movement_left, movement_right);
        //printf("left: %5f    right: %5f \r\n", speed_left, speed_right);
        OLED_ShowNum(1 * 4, 0, beep_flag, 3, 16);
        OLED_ShowNum(9 * 4, 0, lap, 3, 16);
        OLED_ShowNum(16 * 4, 0, task, 3, 16);
        OLED_ShowNum(1 * 4, 5, ult_distance, 5, 16);
        //OLED_ShowNum(1 * 4, 2, myabs(encoder_left), 5, 16);
        //OLED_ShowNum(1 * 4, 4, myabs(encoder_right), 5, 16);
        //printf("��ͣ��%d    ·�̣�%f    Ȧ����%d\r\n", wait_time, road, lap);
        //if(encoder_left < 0)
        //{
        //    OLED_ShowChar(0 * 4, 2, '-', 16);
        //}
        //if(encoder_right < 0)
        //{
        //    OLED_ShowChar(0 * 4, 4, '-', 16);
        //}

        LED_B_Tog();
        if(motor_flag == 1) // ����������̵���˸
        {
            LED_G_Tog();
        }
        key_flag = KEY_Scan(0);
        send_flag = 0x09 + task; // ��������״ָ̬��
        if (key_flag == 1) // �����л�����
        {
            task++;
            if (task > 4)
            {
                task = 1;
            }
        }
        else if (key_flag == 2) // �������Ʒ���
        {
            motor_flag++;
            send_flag = 1; // ��������ָ��
            if (motor_flag > 1)
            {
                motor_flag = 0;
            }
        }
        if(beep_flag == 1) // ����������
            BEEP_On();
        else if(beep_flag == 0)
            BEEP_Off();
        delay_ms(200);
        /*ֹͣ����û�����*/
    }
}


/**
 * @brief ��ʱ��A1�жϷ������������ٶȻ��жϣ�Ƶ��Ϊ50Hz
 * 
 */
void TA1_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    /*��ʼ����û�����*/
    SW_Encoder_Read(); // �����ȡ����������
    speed_left = encoder_to_speed(encoder_left); // ����Ϊʵ���ٶ�
    speed_right = encoder_to_speed(encoder_right);
    if(road_flag == 1) // ·�̼����־λ����1��ʼ����·�̣�ʵ��ֵ��
    {
        road += 2 * (speed_left + speed_right) / (float)2.0;
    }
    else if(road_flag == 0) // ��λ��·������
    {
        road = 0;
    }

    if (motor_flag == 1) // �����־λ������ż���PID
    {
        Motor_PID();
    }
    else if(motor_flag == 0) 
    {
        Motor_Set(0, 0);
        pid_left.output = 0; // �������PID�����
        pid_right.output = 0;
    }
    /*��������û�����*/
}

/**
 * @brief ��ʱ��A3�жϷ����������ڻҶȴ������жϣ�Ƶ��Ϊ30ms
 * 
 */
void TA2_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    if(wait_flag == 1) // ��ʱ���ʱ���㣬����5s��ͣ
    {
        wait_time++;
    }
    else if(wait_flag == 0)
    {
        wait_time = 0;
    }
    Grayscale_scan();
    // Grayscale_Judge();
    FSM(); // ״̬��
    ult_start(); // ���������
    if((task == 3) && (lap == 2)) // ��ײ���
    {
        if (ult_distance < 20)
        {
            movement = 0.5 * 100 - 2 * (20 - ult_distance);
        }
        else if ((ult_distance > 30) && (ult_distance < 50) && (road > 80))
        {
            movement = 0.5 * 100 + 0.5 * (ult_distance - 30);
        }
        else
        {
            movement = 0.5 * 100;
        }
    }
    if(last_send_flag != send_flag) // ͨ�ţ�ֻ������������
    {
        for (int i = 0; i < 3; i++)
        {
            UART_transmitData(EUSCI_A0_BASE, send_flag); // ͨ�ţ�����ʮ����������
        }
        last_send_flag = send_flag;
    }
}

/* �����жϺ��� */
void EUSCIA0_IRQHandler(void)
{
    // ��ȡ
    UART_clearInterruptFlag(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    usart0_rx_data = UART_receiveData(EUSCI_A0_BASE);
}

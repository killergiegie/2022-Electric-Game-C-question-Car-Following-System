/****************************************************/
// MSP432P401R
// 配置Keil独立空工程 (已将ti固件库打包至工程)
// Keil工程已配置开启FPU
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
// 创建日期:2021/9/28
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
    SW_Encoder_Init(); // 编码器配置
    Motor_Init();      // 电机配置
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN5);
    TimA3_Cap_Init();  // 定时器配置为输入捕获模式，用于超声波模块
    TimA2_Int_Init(29999, 48); // 定时器A3中断配置,用于传感器中断 30ms
    TimA1_Int_Init(19999, 48); // 定时器A1中断配置,用于速度环中断,50Hz, 20ms
    movement = 0.5 * 100; // 实际速度0.5m/s
    movement_left  = (float)movement;
    movement_right = (float)movement;
    /* 外圈参数 */
    small_kdiff  = (int)(movement * 0.25);
    medium_kdiff = (int)(movement * 0.5);
    large_kdiff  = (int)(movement * 0.85);
    Incremental_PID_Init(&pid_left,  100, 3, 0, 85 * 48); // 速度环PID参数配置
    Incremental_PID_Init(&pid_right, 100, 3, 0, 85 * 48); 

    /*中断优先级管理，切记定时器中断优先级不能高于外部中断优先级*/
    //编码器采集中断优先级，设置为次低
    Interrupt_setPriority(INT_PORT2, 3 << 5);
    Interrupt_setPriority(INT_PORT4, 3 << 5);
    Interrupt_setPriority(INT_PORT5, 3 << 5);
    Interrupt_setPriority(INT_PORT6, 3 << 5);

    //速度环中断优先级，设置为最高
    Interrupt_setPriority(INT_TA1_0, 2 << 5);

    // 通信中断优先级，设置为最低
    Interrupt_setPriority(INT_EUSCIA0, 4 << 5);

    /*清除中断标志位*/
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
    SysInit();         // 第3讲 时钟配置
    uart_init(115200); // 第7讲 串口配置
    delay_init();      // 第4讲 滴答延时

    /*开始填充初始化代码*/
    system_init();
    /*停止填充初始化代码*/

    //printf("Hello,MSP432!\r\n");
    delay_ms(200);
    MAP_Interrupt_enableMaster(); // 开启总中断
    while (1)
    {
        /*开始填充用户代码*/
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
        //printf("等停：%d    路程：%f    圈数：%d\r\n", wait_time, road, lap);
        //if(encoder_left < 0)
        //{
        //    OLED_ShowChar(0 * 4, 2, '-', 16);
        //}
        //if(encoder_right < 0)
        //{
        //    OLED_ShowChar(0 * 4, 4, '-', 16);
        //}

        LED_B_Tog();
        if(motor_flag == 1) // 电机启动后，绿灯闪烁
        {
            LED_G_Tog();
        }
        key_flag = KEY_Scan(0);
        send_flag = 0x09 + task; // 发送任务状态指令
        if (key_flag == 1) // 按键切换任务
        {
            task++;
            if (task > 4)
            {
                task = 1;
            }
        }
        else if (key_flag == 2) // 按键控制发车
        {
            motor_flag++;
            send_flag = 1; // 发送启动指令
            if (motor_flag > 1)
            {
                motor_flag = 0;
            }
        }
        if(beep_flag == 1) // 蜂鸣器控制
            BEEP_On();
        else if(beep_flag == 0)
            BEEP_Off();
        delay_ms(200);
        /*停止填充用户代码*/
    }
}


/**
 * @brief 定时器A1中断服务函数，用于速度环中断，频率为50Hz
 * 
 */
void TA1_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    /*开始填充用户代码*/
    SW_Encoder_Read(); // 软件获取编码器数据
    speed_left = encoder_to_speed(encoder_left); // 换算为实际速度
    speed_right = encoder_to_speed(encoder_right);
    if(road_flag == 1) // 路程计算标志位被置1后开始计算路程（实际值）
    {
        road += 2 * (speed_left + speed_right) / (float)2.0;
    }
    else if(road_flag == 0) // 复位后路程清零
    {
        road = 0;
    }

    if (motor_flag == 1) // 电机标志位开启后才计算PID
    {
        Motor_PID();
    }
    else if(motor_flag == 0) 
    {
        Motor_Set(0, 0);
        pid_left.output = 0; // 清空增量PID的输出
        pid_right.output = 0;
    }
    /*结束填充用户代码*/
}

/**
 * @brief 定时器A3中断服务函数，用于灰度传感器中断，频率为30ms
 * 
 */
void TA2_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    if(wait_flag == 1) // 计时与计时清零，用于5s等停
    {
        wait_time++;
    }
    else if(wait_flag == 0)
    {
        wait_time = 0;
    }
    Grayscale_scan();
    // Grayscale_Judge();
    FSM(); // 状态机
    ult_start(); // 超声波测距
    if((task == 3) && (lap == 2)) // 防撞设计
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
    if(last_send_flag != send_flag) // 通信，只发送三次数据
    {
        for (int i = 0; i < 3; i++)
        {
            UART_transmitData(EUSCI_A0_BASE, send_flag); // 通信，发送十六进制数据
        }
        last_send_flag = send_flag;
    }
}

/* 串口中断函数 */
void EUSCIA0_IRQHandler(void)
{
    // 读取
    UART_clearInterruptFlag(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    usart0_rx_data = UART_receiveData(EUSCI_A0_BASE);
}

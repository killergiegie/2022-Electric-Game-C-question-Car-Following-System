/****************************************************/
// MSP432P401R
// 配置Keil独立空工程 (已将ti固件库打包至工程)
// Keil工程已配置开启FPU
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
// 创建日期:2021/9/28
/****************************************************/

#include "sysinit.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "tim32.h"
#include "motor.h"
#include "grayscale.h"
#include "key.h"
#include "globalvar.h"

int key_value;

int main(void)
{
    SysInit();         //时钟配置
    uart_init(115200); //串口配置
    delay_init();      //滴答延时
    KEY_Init(0);

    //蜂鸣器
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);

    /*电机初始化*/
    motor_Init();       
    movement = speed_to_encoder(0.5);

    /*灰度传感器*/
    Grayscale_Init();

    /*定时器中断，在中断服务函数里面使用pid来控制电机*/
    TimA0_Int_Init(20000 - 1, 48);

    TimA3_Int_Init(10000 - 1, 48);

    /*输入捕获初始化*/
    TimA2_Cap_Init();

    MAP_Interrupt_enableMaster(); // 开启总中断

    /*设置中断优先级，注意中断优先级必须设置为一样，否则会有bug*/
    Interrupt_setPriority(INT_TA0_0, 1 << 5);
    Interrupt_setPriority(INT_TA2_0, 2 << 5);
    Interrupt_setPriority(INT_TA3_0, 1 << 5);
    Interrupt_setPriority(INT_PORT4, 3 << 5);
    Interrupt_setPriority(INT_PORT5, 3 << 5);

    /*清除中断标志位*/
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_clearInterrupt(GPIO_PORT_P5, GPIO_PIN0);
    GPIO_clearInterrupt(GPIO_PORT_P5, GPIO_PIN1);

    /*PID初始化*/
//    Incremental_PID_Init(&pid_left,  2.23, 12.05, 0, 60 * 100);
//    Incremental_PID_Init(&pid_right, 2.23, 12.05, 0, 60 * 100);
    Incremental_PID_Init(&pid_left,  100, 3, 0, 90 * 48);
    Incremental_PID_Init(&pid_right, 100, 3, 0, 90 * 48);

    Positional_PID_Init(&pid_dis, 0.5, 0, 0, 50.0, 50.0);

    while (1)
    {
        key_value = KEY_Scan(0);
        switch(key_value)
        {
            case 1:
                break;
            case 2:
                motor_flag = 1 - motor_flag;	
                break;
            default:
                break;
        }
        Grayscale_Get();
                
//        printf("%d,",L4);
//        printf("%d,",L3);
//        printf("%d,",L2);
//        printf("%d,",L1);
//        printf("%d,",M);
//        printf("%d,",MU);
//        printf("%d,",LU);
//        printf("%d,",RU);
//        printf("%d,",R1);
//        printf("%d,",R2);
//        printf("%d,",R3);
//        printf("%d\r\n",R4);
    }
}

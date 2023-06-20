/****************************************************/
// MSP432P401R
// 定时器A
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
// 创建日期:2021/8/26
/****************************************************/

#include "timA.h"
#include "stdio.h"

/**************************************         TIMA2          *******************************************/

#define CAP_TIMA_SELECTION TIMER_A2_BASE                         //在这里改定时器
#define CAP_REGISTER_SELECTION TIMER_A_CAPTURECOMPARE_REGISTER_2 //在这里改定时器通道
#define CAP_CCR_NUM 2                                            //在这里改定时器通道
#define CAP_PORT_PIN GPIO_PORT_P5, GPIO_PIN7                     //在这里改复用引脚

uint8_t TIMA2_CAP_STA;
uint16_t TIMA2_CAP_VAL;

void TimA2_Cap_Init(void)
{
    //初始化trig
    GPIO_setAsOutputPin(GPIO_PORT_P5,GPIO_PIN6);

    // 1.复用输出
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(CAP_PORT_PIN, GPIO_PRIMARY_MODULE_FUNCTION);

    /* 定时器配置参数*/
    Timer_A_ContinuousModeConfig continuousModeConfig = {
        TIMER_A_CLOCKSOURCE_SMCLK,      // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_48, // SMCLK/48 = 1MHz
        TIMER_A_TAIE_INTERRUPT_ENABLE,  // 开启定时器溢出中断
        TIMER_A_DO_CLEAR                // Clear Counter
    };
    // 3.将定时器初始化为连续计数模式
    MAP_Timer_A_configureContinuousMode(CAP_TIMA_SELECTION, &continuousModeConfig);

    // 4.配置捕捉模式结构体 */
    const Timer_A_CaptureModeConfig captureModeConfig_TA2 = {
        CAP_REGISTER_SELECTION,                      //在这里改引脚
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE, //上升下降沿捕获
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,           //CCIxA:外部引脚输入  （CCIxB:与内部ACLK连接(手册)
        TIMER_A_CAPTURE_SYNCHRONOUS,                 //同步捕获
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,     //开启CCRN捕获中断
        TIMER_A_OUTPUTMODE_OUTBITVALUE               //输出位值
    };
    // 5.初始化定时器的捕获模式
    MAP_Timer_A_initCapture(CAP_TIMA_SELECTION, &captureModeConfig_TA2);

    // 6.选择连续模式计数开始计数
    MAP_Timer_A_startCounter(CAP_TIMA_SELECTION, TIMER_A_CONTINUOUS_MODE);

    // 7.清除中断标志位
    MAP_Timer_A_clearInterruptFlag(CAP_TIMA_SELECTION);                                   //清除定时器溢出中断标志位
    MAP_Timer_A_clearCaptureCompareInterrupt(CAP_TIMA_SELECTION, CAP_REGISTER_SELECTION); //清除 CCR1 更新中断标志位

    // 8.开启定时器端口中断
    MAP_Interrupt_enableInterrupt(INT_TA2_N); //开启定时器A2端口中断
}
// 10.编写TIMA ISR ↓↓↓↓

// TIMA2_CAP_STA 捕获状态
// [7]:捕获高电平完成状态
// [6]:0表示未捕获到上升沿，1表示捕获过上升沿
// [5:0]:溢出次数
uint8_t TIMA2_CAP_STA = 0;
uint16_t TIMA2_CAP_VAL = 0;
uint32_t time = 0;
int time_cnt = 0;

void TA2_N_IRQHandler(void)
{
    if ((TIMA2_CAP_STA & 0X80) == 0) //还未成功捕获
    {
        if (MAP_Timer_A_getEnabledInterruptStatus(CAP_TIMA_SELECTION)) //溢出中断
        {
            MAP_Timer_A_clearInterruptFlag(CAP_TIMA_SELECTION); //清除定时器溢出中断标志位
            /* ★ 软件复位COV ★ */
            /* 这里UP忘记讲了，如果在未清除中断位值时，来了一次中断，COV会置位，需要软件复位，这里没有官方库函数。具体可以参考技术手册(slau356h.pdf) P790 */
            BITBAND_PERI(TIMER_A_CMSIS(CAP_TIMA_SELECTION)->CCTL[CAP_CCR_NUM], TIMER_A_CCTLN_COV_OFS) = 0;

            if (TIMA2_CAP_STA & 0X40) //已经捕获到高电平了 40H = 0x01000000
            {
                if ((TIMA2_CAP_STA & 0X3F) == 0X3F) //高电平太长了
                {
                    TIMA2_CAP_STA |= 0X80; //强制标记成功捕获完高电平 80H = 0x10000000
                    TIMA2_CAP_VAL = 0XFFFF;
                }
                else
                {
                    TIMA2_CAP_STA++; //溢出次数加1
                }
            }
        }

        if (MAP_Timer_A_getCaptureCompareEnabledInterruptStatus(CAP_TIMA_SELECTION, CAP_REGISTER_SELECTION)) //捕获中断
        {
            MAP_Timer_A_clearCaptureCompareInterrupt(CAP_TIMA_SELECTION, CAP_REGISTER_SELECTION); //清除 CCR1 更新中断标志位
            //判断是否捕获到下降沿
            if (TIMA2_CAP_STA & 0X40 && (MAP_Timer_A_getSynchronizedCaptureCompareInput(CAP_TIMA_SELECTION,
                                        CAP_REGISTER_SELECTION,
                                        TIMER_A_READ_CAPTURE_COMPARE_INPUT) == TIMER_A_CAPTURECOMPARE_INPUT_LOW))
            {
                TIMA2_CAP_STA |= 0X80; //标记成功捕获完高电平
                TIMA2_CAP_VAL = Timer_A_getCaptureCompareCount(CAP_TIMA_SELECTION, CAP_REGISTER_SELECTION);
                TIMA2_CAP_STA = 0X40;
                time = (TIMA2_CAP_VAL ) / 2;
                ult_distance = 34000 * time / 1000000 ;
                // printf("%d\r\n",ult_distance);
                //printf("%d\r\n",(TIMA2_CAP_VAL));
                time_cnt = 0;
            }
            else //还未开始,第一次捕获上升沿
            {
                TIMA2_CAP_STA = 0;
                TIMA2_CAP_VAL = 0;
                MAP_Timer_A_clearTimer(CAP_TIMA_SELECTION); //清空定时器 重新从0计数
                TIMA2_CAP_STA |= 0X40;                      //标记捕获到了上升沿
            }
        }
    }
}

//启动超声波检测
void ult_start(void)
{ 
	GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN6); //高电平
	delay_us(20);
	GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN6); //低电平
}
/*********************************************************************************************************/

/**************************************         TIMA1          *******************************************/

void TimA1_PWM_Init(uint16_t ccr0, uint16_t psc)
{
    /*初始化引脚*/
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P7, GPIO_PIN7 | GPIO_PIN6 , GPIO_PRIMARY_MODULE_FUNCTION);

    Timer_A_PWMConfig TimA1_PWMConfig;
    /*定时器PWM初始化*/
    TimA1_PWMConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;             //时钟源
    TimA1_PWMConfig.clockSourceDivider = psc;                            //时钟分频 范围1-64
    TimA1_PWMConfig.timerPeriod = ccr0;                                  //自动重装载值（ARR）
    TimA1_PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1; //通道一 （引脚定义）
    TimA1_PWMConfig.compareOutputMode = TIMER_A_OUTPUTMODE_TOGGLE_SET;   //输出模式
    TimA1_PWMConfig.dutyCycle = ccr0;                                    //这里是改变占空比的地方 默认100%

    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &TimA1_PWMConfig);            /* 初始化比较寄存器以产生 PWM1 */

    TimA1_PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2; //通道二 （引脚定义）
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &TimA1_PWMConfig);            /* 初始化比较寄存器以产生 PWM2 */
}
/*********************************************************************************************************/

/**************************************         TIMA0          *******************************************/

void TimA0_Int_Init(uint16_t ccr0, uint16_t psc)
{
    // 1.增计数模式初始化
    Timer_A_UpModeConfig upConfig;
    upConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                                      //时钟源
    upConfig.clockSourceDivider = psc;                                                     //时钟分频 范围1-64
    upConfig.timerPeriod = ccr0;                                                           //自动重装载值（ARR）
    upConfig.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;                   //禁用 tim溢出中断
    upConfig.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE; //启用 ccr0更新中断
    upConfig.timerClear = TIMER_A_DO_CLEAR;                                                // Clear value

    // 2.初始化定时器A
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);

    // 3.选择模式开始计数
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    // 4.清除比较中断标志位
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    // 5.开启串口端口中断
    MAP_Interrupt_enableInterrupt(INT_TA0_0);
}

// 6.编写TIMA ISR
void TA0_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    /*开始填充用户代码*/

    //控制距离
    if(task==1||task==2||task==3||task==4)
    {
        if(ult_distance < 50)
        {
            Positional_PID_Calc(&pid_dis, 30, ult_distance);
            dis_movement = -pid_dis.output;
            // printf("mov=%d\r\n",(int)dis_movement);
        }
        else 
        {
            dis_movement = 0;
        }
    }

    //加速追赶
    if(chase_flag)
    {
        if(ult_distance < 30)
        {
            movement = speed_to_encoder(0.5);
            chase_flag = 0;
        }
    }

    /***********************计算距离****************************/
    // Distance_Calc();
    // printf("%d\r\n",(int)distance);
    // //清除编码器数值
    // encoder_left  = 0;
    // encoder_right = 0;
    /**********************************************************/

    if(motor_flag)
    {
        // printf("%d,",encoder_left);
        // printf("%d\r\n",encoder_right);
        //计算距离
        Distance_Calc();
        // printf("%f\r\n",distance);
        //电机PID
        motor_PID();
        FSM();
    }
    else
    {
        motor_set(0,0);
    }
    

    /*结束填充用户代码*/
}
/*********************************************************************************************************/

/**************************************         TIMA3          *******************************************/

void TimA3_Int_Init(uint16_t ccr0, uint16_t psc)
{
    // 1.增计数模式初始化
    Timer_A_UpModeConfig upConfig;
    upConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                                      // 时钟源
    upConfig.clockSourceDivider = psc;                                                     // 时钟分频 范围1-64
    upConfig.timerPeriod = ccr0;                                                           // 自动重装载值（ARR）
    upConfig.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;                   // 禁用 tim溢出中断
    upConfig.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE; // 启用 ccr0更新中断
    upConfig.timerClear = TIMER_A_DO_CLEAR;                                                // Clear value

    // 2.初始化定时器A
    MAP_Timer_A_configureUpMode(TIMER_A3_BASE, &upConfig);

    // 3.选择模式开始计数
    MAP_Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_UP_MODE);

    // 4.清除比较中断标志位
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    // 5.开启串口端口中断
    MAP_Interrupt_enableInterrupt(INT_TA3_0);
}
/*********************************************************************************************************/
/**
 * @brief 定时器A3中断服务函数，用于灰度传感器中断，频率为30ms
 * 
 */
int ult_cnt = 0;
void TA3_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    ult_cnt++;
    if(ult_cnt > 10)
    {
        if(ult_flag)
            ult_start();
        ult_cnt = 0;
    }
    
}

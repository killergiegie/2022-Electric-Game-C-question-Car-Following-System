#include "encoder.h"

int encoder_l = 0;
int encoder_r = 0;

/**
 * @brief 编码器初始化（软件四分频方案）
 * 
 */
void SW_Encoder_Init(void)
{
    /*开启外部中断*/
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN6); // 开启P2.6中断,leftA_up
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN7); // 开启P2.7中断,leftA_down
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN6); // 开启P4.6中断,leftB_up
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN7); // 开启P4.7中断,leftB_down

    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN6); // 开启P5.6中断,rightA_up
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN7); // 开启P5.7中断,rightA_down
    GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN6); // 开启P6.6中断,rightB_up
    GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN7); // 开启P6.7中断,rightB_down

    /*开启端口中断*/
    Interrupt_enableInterrupt(INT_PORT2);
    Interrupt_enableInterrupt(INT_PORT4);
    Interrupt_enableInterrupt(INT_PORT5);
    Interrupt_enableInterrupt(INT_PORT6);
    /*配置触发方式*/
    GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN6, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN6, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN6, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P6, GPIO_PIN6, GPIO_LOW_TO_HIGH_TRANSITION);

    GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P6, GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
    /*由于编码器一般为开漏输出，所以配置为上拉输入引脚*/
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN6);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN6);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN7);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN6);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN7);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6, GPIO_PIN6);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6, GPIO_PIN7);
    //    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4);
    //    MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN6);
    //    MAP_GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN4);
    //    MAP_GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN6);
    //    MAP_GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN4);
    //    MAP_GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN6);
    //    MAP_GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN4);
    //    MAP_GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN6);
}

/**
 * @brief 读取编码器值
 * 
 */
void SW_Encoder_Read(void)
{
    encoder_left  = encoder_l;
    encoder_right = -encoder_r;
    SW_Encoder_Clear();
}

/**
 * @brief 清除编码器值
 * 
 */
void SW_Encoder_Clear(void)
{
    encoder_l = 0;
    encoder_r = 0;
}

/*****************************************************************
 *Function: PORT2_IRQHandler(void) PORT4_IRQHandler(void) PORT5_IRQHandler(void) PORT6_IRQHandler(void)
 *Description:外部中断服务函数
 *Input:无
 *Output:无
 *Return:无
 *Others:中断服务函数，在中断内处理程序
 *Data:2021/09/14
 *****************************************************************/
void PORT2_IRQHandler(void)
{
    uint16_t flag;

    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P2, flag);
    /*左轮A相上升沿*/
    if (flag & GPIO_PIN6)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN6) == 0)
            encoder_l++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN6) == 1)
            encoder_l--;
    }
    /*左轮A相下降沿*/
    if (flag & GPIO_PIN7)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN6) == 0)
            encoder_l--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN6) == 1)
            encoder_l++;
    }
}

void PORT4_IRQHandler(void)
{
    uint16_t flag;

    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P4, flag);

    /*左轮B相上升沿*/
    if (flag & GPIO_PIN6)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN6) == 0)
            encoder_l--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN6) == 1)
            encoder_l++;
    }
    /*左轮B相下降沿*/
    if (flag & GPIO_PIN7)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN6) == 0)
            encoder_l++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN6) == 1)
            encoder_l--;
    }
}

void PORT5_IRQHandler(void)
{
    uint16_t flag;

    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P5, flag);
    /*右轮A相上升沿*/
    if (flag & GPIO_PIN6)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN6) == 0)
            encoder_r++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN6) == 1)
            encoder_r--;
    }
    /*右轮A相下降沿*/
    if (flag & GPIO_PIN7)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN6) == 0)
            encoder_r--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN6) == 1)
            encoder_r++;
    }
}

void PORT6_IRQHandler(void)
{
    uint16_t flag;

    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P6, flag);
    /*右轮B相上升沿*/
    if (flag & GPIO_PIN6)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 0)
            encoder_r--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 1)
            encoder_r++;
    }
    /*右轮B相下降沿*/
    if (flag & GPIO_PIN7)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 0)
            encoder_r++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == 1)
            encoder_r--;
    }
}

/**
 * @brief 编码器值换算为实际速度
 *  车模轮子周长 X0 = 
    车模齿轮的齿数 X1
    编码器齿轮的齿数 X2
    编码器的线数 X3
    ENC 读到数据 X4
    ENC 读取时间间隔 X5
    速度换算公式： V = ( (X4 / X3) * X2 / X1 ) * X0 / X5
    速度 = ( (总脉冲数 / 编码器线数) * 编码器齿数 / 车模齿数 ) * 轮周长 / 脉冲读取时间
 * @param encoder
 * @return float 速度，单位：米/秒 (m/s)
 */
float encoder_to_speed(int encoder)
{
    float speed = 0;
    float X0 = 4.6 * 3.14; //车轮周长
    int X1 = 1, X2 = 1; // 车模齿轮齿数
    float X3 = 260*4.0;  //编码器线数(4倍频)
    float X4 = (float)encoder; //编码器读到的数据
    int X5 = 20;     //编码器读取时间间隔 50HZ = 20ms

    speed = (((X4 / X3) * X2 / X1) * X0 * (float)1000.0) / (X5 * (float)100.0);
    return speed;
}

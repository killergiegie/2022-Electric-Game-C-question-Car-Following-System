#include "encoder.h"

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
    float X3 = 260*2.0;  //编码器线数(4倍频)
    float X4 = (float)encoder; //编码器读到的数据
    int X5 = 20;     //编码器读取时间间隔 50HZ = 20ms

    speed = (((X4 / X3) * X2 / X1) * X0 * (float)1000.0) / (X5 * (float)100.0);
    return speed;
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
int16_t speed_to_encoder(float speed)
{
    float encoder = 0;
    float X0 = 4.6 * 3.14; //车轮周长
    int X1 = 1, X2 = 1; // 车模齿轮齿数
    float X3 = 260*2.0;  //编码器线数(4倍频)
    float X4 = (float)speed; //速度
    int X5 = 20;     //编码器读取时间间隔 50HZ = 20ms

    encoder = (int)(speed*X1*X3*X5)/(10.0*X2*X0);
    return encoder;
}

/*计算距离*/
void Distance_Calc(void)
{
    if(Dis_Calc_Flag)
    {
        distance = distance + 100 * ( encoder_to_speed(encoder_left) + encoder_to_speed(encoder_right)) * (float)0.5 * per;
    }
    else
    {
        distance = 0;
    }

}

void Encoder_Init(void)
{
    /*开启外部中断*/
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN0);
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
    /*开启端口中断*/
    Interrupt_enableInterrupt(INT_PORT4);
    Interrupt_enableInterrupt(INT_PORT5);
    /*配置触发方式*/
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN5, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN0, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
    /*配置为上拉输入引脚*/
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN0);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1);
}

void PORT4_IRQHandler(void)
{
    uint16_t flag;

    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P4, flag);

    /*左轮编码器线A*/
    if (flag & GPIO_PIN4)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN5) == 0)
            encoder_left++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN5) == 1)
            encoder_left--;
    }

    /*左轮编码器线B*/
    if (flag & GPIO_PIN5)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN4) == 0)
            encoder_left--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN4) == 1)
            encoder_left++;
    }
}

void PORT5_IRQHandler(void)
{
    uint16_t flag;

    /*获取中断状态*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    /*清除中断标志位*/
    GPIO_clearInterruptFlag(GPIO_PORT_P5, flag);

    /*右轮编码器线A*/
    if (flag & GPIO_PIN0)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0)
            encoder_right++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 1)
            encoder_right--;
    }

    /*右轮编码器线B*/
    if (flag & GPIO_PIN1)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN0) == 0)
            encoder_right--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN0) == 1)
            encoder_right++;
    }
}


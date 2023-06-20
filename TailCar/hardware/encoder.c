#include "encoder.h"

/**
 * @brief ������ֵ����Ϊʵ���ٶ�
 *  ��ģ�����ܳ� X0 = 
    ��ģ���ֵĳ��� X1
    ���������ֵĳ��� X2
    ������������ X3
    ENC �������� X4
    ENC ��ȡʱ���� X5
    �ٶȻ��㹫ʽ�� V = ( (X4 / X3) * X2 / X1 ) * X0 / X5
    �ٶ� = ( (�������� / ����������) * ���������� / ��ģ���� ) * ���ܳ� / �����ȡʱ��
 * @param encoder
 * @return float �ٶȣ���λ����/�� (m/s)
 */
float encoder_to_speed(int encoder)
{
    float speed = 0;
    float X0 = 4.6 * 3.14; //�����ܳ�
    int X1 = 1, X2 = 1; // ��ģ���ֳ���
    float X3 = 260*2.0;  //����������(4��Ƶ)
    float X4 = (float)encoder; //����������������
    int X5 = 20;     //��������ȡʱ���� 50HZ = 20ms

    speed = (((X4 / X3) * X2 / X1) * X0 * (float)1000.0) / (X5 * (float)100.0);
    return speed;
}

/**
 * @brief ������ֵ����Ϊʵ���ٶ�
 *  ��ģ�����ܳ� X0 = 
    ��ģ���ֵĳ��� X1
    ���������ֵĳ��� X2
    ������������ X3
    ENC �������� X4
    ENC ��ȡʱ���� X5
    �ٶȻ��㹫ʽ�� V = ( (X4 / X3) * X2 / X1 ) * X0 / X5
    �ٶ� = ( (�������� / ����������) * ���������� / ��ģ���� ) * ���ܳ� / �����ȡʱ��
 * @param encoder
 * @return float �ٶȣ���λ����/�� (m/s)
 */
int16_t speed_to_encoder(float speed)
{
    float encoder = 0;
    float X0 = 4.6 * 3.14; //�����ܳ�
    int X1 = 1, X2 = 1; // ��ģ���ֳ���
    float X3 = 260*2.0;  //����������(4��Ƶ)
    float X4 = (float)speed; //�ٶ�
    int X5 = 20;     //��������ȡʱ���� 50HZ = 20ms

    encoder = (int)(speed*X1*X3*X5)/(10.0*X2*X0);
    return encoder;
}

/*�������*/
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
    /*�����ⲿ�ж�*/
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN0);
    GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
    /*�����˿��ж�*/
    Interrupt_enableInterrupt(INT_PORT4);
    Interrupt_enableInterrupt(INT_PORT5);
    /*���ô�����ʽ*/
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN5, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN0, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
    /*����Ϊ������������*/
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN0);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1);
}

void PORT4_IRQHandler(void)
{
    uint16_t flag;

    /*��ȡ�ж�״̬*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    /*����жϱ�־λ*/
    GPIO_clearInterruptFlag(GPIO_PORT_P4, flag);

    /*���ֱ�������A*/
    if (flag & GPIO_PIN4)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN5) == 0)
            encoder_left++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN5) == 1)
            encoder_left--;
    }

    /*���ֱ�������B*/
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

    /*��ȡ�ж�״̬*/
    flag = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    /*����жϱ�־λ*/
    GPIO_clearInterruptFlag(GPIO_PORT_P5, flag);

    /*���ֱ�������A*/
    if (flag & GPIO_PIN0)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 0)
            encoder_right++;
        else if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1) == 1)
            encoder_right--;
    }

    /*���ֱ�������B*/
    if (flag & GPIO_PIN1)
    {
        if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN0) == 0)
            encoder_right--;
        else if (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN0) == 1)
            encoder_right++;
    }
}


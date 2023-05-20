#include "grayscale.h"

#define A (CHA == 1)
#define a (CHA == 0)

#define B (CHB == 1)
#define b (CHB == 0)

#define C (CHC == 1)
#define c (CHC == 0)

#define D (CHD == 1)
#define d (CHD == 0)

#define E (CHE == 1)
#define e (CHE == 0)

#define F (CHF == 1)
#define f (CHF == 0)

#define G (CHG == 1)
#define g (CHG == 0)

#define H (CHH == 1)
#define h (CHH == 0)

void Grayscale_Init(void)
{
    // ��ʼ������������Ϊ����ģʽ
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN0); // A P7.0
    GPIO_setAsInputPin(GPIO_PORT_P9, GPIO_PIN5); // B P9.5
    GPIO_setAsInputPin(GPIO_PORT_P9, GPIO_PIN7); // C P9.7
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN5); // D P7.5
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN7); // E P7.7
    GPIO_setAsInputPin(GPIO_PORT_P10, GPIO_PIN1);// F P10.1
    GPIO_setAsInputPin(GPIO_PORT_P10, GPIO_PIN3);// G P10.3
    GPIO_setAsInputPin(GPIO_PORT_P10, GPIO_PIN5);// H P10.5
}

int CHA = 0, CHB = 0, CHC = 0, CHD = 0, CHE = 0, CHF = 0, CHG = 0, CHH = 0;
void Grayscale_scan(void)
{
    // ��ȡ���������ŵ�ƽ
    CHA = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN0);  // A P7.0
    CHB = GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN5);  // B P9.5
    CHC = GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN7);  // C P9.7
    CHD = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN5);  // D P7.5
    CHE = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN7);  // E P7.7
    CHF = GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN1); // F P10.1
    CHG = GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN3); // G P10.3
    CHH = GPIO_getInputPinValue(GPIO_PORT_P10, GPIO_PIN5); // H P10.5

    gray_state = CHA + CHB + CHC + CHD + CHE + CHF + CHG + CHH;
}

void Grayscale_Judge(void)
{
    // movement_left = movement;
    // movement_right = movement;
    if(a && b && c && D && E && f && g && h) // ��ֱ��״̬
    {
        movement_left  = (float)movement; // ��ʱ�����ٶ�Ϊ��100���ֵ
        movement_right = (float)movement;
    }
    else if (a && b && C && d && e && f && g && h) // ��Сƫ�����ּ�С��
    {
        movement_left  = (float)(movement - small_kdiff); 
        movement_right = (float)(movement + small_kdiff);
    }
    else if (a && B && c && d && e && f && g && h) // ����ƫ�����ּ�����
    {
        movement_left  = (float)(movement - medium_kdiff);
        movement_right = (float)(movement + medium_kdiff);
    }
    else if (A && b && c && d && e && f && g && h) // �Ҵ�ƫ�����ּӴ���
    {
        movement_left =  (float)(movement - large_kdiff);
        movement_right = (float)(movement + large_kdiff);
    }
    else if (a && b && c && d && e && F && g && h) // ��Сƫ�����ּ�С��
    {
        movement_left  = (float)(movement + small_kdiff);
        movement_right = (float)(movement - small_kdiff);
    }
    else if (a && b && c && d && e && G && h) // ����ƫ�����ּ�����
    {
        movement_left =  (float)(movement + medium_kdiff);
        movement_right = (float)(movement - medium_kdiff);
    }
    else if (a && b && c && d && e && f && g && H) // ���ƫ�����ּӴ���
    {
        movement_left =  (float)(movement + large_kdiff);
        movement_right = (float)(movement - large_kdiff);
    }
    else if (a && b && C && d && e) // ��Сƫ�����ּ�С��
    {
        movement_left = (float)(movement - small_kdiff);
        movement_right = (float)(movement + small_kdiff);
    }
    else if (a && B && c && d && e) // ����ƫ�����ּ�����
    {
        movement_left = (float)(movement - medium_kdiff);
        movement_right = (float)(movement + medium_kdiff);
    }
    else if (A && b && c && d && e) // �Ҵ�ƫ�����ּӴ���
    {
        movement_left = (float)(movement - large_kdiff);
        movement_right = (float)(movement + large_kdiff);
    }
}

void Inner_Ring(void)
{
    if (a && b && c && D && E && f && g && h) // ��ֱ��״̬
    {
        movement_left = (float)movement; // ��ʱ�����ٶ�Ϊ��100���ֵ
        movement_right = (float)movement;
    }
    else if (a && b && C) // ��Сƫ�����ּ�С��
    {
        movement_left = (float)(movement - small_kdiff - 5);
        movement_right = (float)(movement + small_kdiff + 5);
    }
    else if (a && B && c) // ����ƫ�����ּ�����
    {
        movement_left = (float)(movement - medium_kdiff - 7);
        movement_right = (float)(movement + medium_kdiff + 7);
    }
    else if (A && b && c) // �Ҵ�ƫ�����ּӴ���
    {
        movement_left = (float)(movement - large_kdiff - 15);
        movement_right = (float)(movement + large_kdiff + 15);
    }
}

void Outer_Ring(void)
{
    if (D && E && f && g && h) // ��ֱ��״̬
    {
        movement_left = (float)movement; // ��ʱ�����ٶ�Ϊ��100���ֵ
        movement_right = (float)movement;
    }
    else if (d && e && f && g && h) // ��Сƫ�����ּ�С��
    {
        movement_left = (float)(movement - small_kdiff);
        movement_right = (float)(movement + small_kdiff);
    }
    else if (d && e && F && g && h) // ��Сƫ�����ּ�С��
    {
        movement_left = (float)(movement + small_kdiff);
        movement_right = (float)(movement - small_kdiff);
    }
    else if (d && e && G && h) // ����ƫ�����ּ�����
    {
        movement_left = (float)(movement + medium_kdiff);
        movement_right = (float)(movement - medium_kdiff);
    }
    else if (d && e && f && g && H) // ���ƫ�����ּӴ���
    {
        movement_left = (float)(movement + large_kdiff);
        movement_right = (float)(movement - large_kdiff);
    }
}

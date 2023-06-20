#ifndef __FSM_H_
#define __FSM_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"
#include "encoder.h"
#include "grayscale.h"

typedef enum{
    NONE,       //��״̬
    CROSS,      //����
    STOP,       //ֹͣ
    WAIT_STOP   //��ͣ
}statedef;

typedef enum{
    PRE_CROSS,          //Ԥ���
    BEFORE_CROSS,       //���ǰ
    TURN_LEFT,          //��ת
    GO_STRIGHT,         //ֱ��
    CROSS_SPEED_UP,     //����
    CROSS_SPEED_DOWN,   //����
    CROSS_BREAK         //�˳����״̬ *��ֹ�ڶ�����·�����õ�
}stateCROSSdef;

typedef enum{
    PRE_STOP,      //Ԥֹͣ
    IN_STOP        //ֹͣ��
}stateSTOPdef;

//״̬��
void FSM(void);

//�ж������
void Judge_Outer_Inside(void);

#endif

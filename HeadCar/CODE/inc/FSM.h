#ifndef _FSM_H
#define _FSM_H

#include "globalvar.h"

typedef enum
{
    NONE,     // ��״̬
    CROSS,    // ��·��״̬
    WAIT      // ��ͣ״̬
} statedef;

typedef enum
{
    PRE_CROSS, // Ԥ���
    IN_CROSS   // ���
} stateCROSSdef;

// typedef enum
// {
//     IN_WAIT,   // �����ͣ״̬
//     OUT_WAIT   // �˳���ͣ״̬
// } stateWAITEdef;

// ״̬��
void FSM(void);

#endif

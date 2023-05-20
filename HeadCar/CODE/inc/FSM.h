#ifndef _FSM_H
#define _FSM_H

#include "globalvar.h"

typedef enum
{
    NONE,     // 无状态
    CROSS,    // 岔路口状态
    WAIT      // 等停状态
} statedef;

typedef enum
{
    PRE_CROSS, // 预入岔
    IN_CROSS   // 入岔
} stateCROSSdef;

// typedef enum
// {
//     IN_WAIT,   // 进入等停状态
//     OUT_WAIT   // 退出等停状态
// } stateWAITEdef;

// 状态机
void FSM(void);

#endif

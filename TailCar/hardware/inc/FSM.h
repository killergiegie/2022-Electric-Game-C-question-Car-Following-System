#ifndef __FSM_H_
#define __FSM_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"
#include "encoder.h"
#include "grayscale.h"

typedef enum{
    NONE,       //无状态
    CROSS,      //三岔
    STOP,       //停止
    WAIT_STOP   //等停
}statedef;

typedef enum{
    PRE_CROSS,          //预入岔
    BEFORE_CROSS,       //入岔前
    TURN_LEFT,          //左转
    GO_STRIGHT,         //直行
    CROSS_SPEED_UP,     //加速
    CROSS_SPEED_DOWN,   //减速
    CROSS_BREAK         //退出弯道状态 *防止第二个岔路误判用的
}stateCROSSdef;

typedef enum{
    PRE_STOP,      //预停止
    IN_STOP        //停止中
}stateSTOPdef;

//状态机
void FSM(void);

//判断内外道
void Judge_Outer_Inside(void);

#endif

#ifndef __MOTOR_H_
#define __MOTOR_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "encoder.h"
#include "timA.h"
#include "globalvar.h"

void motor_Init(void);
void motor_PID(void);
void motor_set(int PWM_left, int PWM_right);

#endif // !__MOTOR_H_

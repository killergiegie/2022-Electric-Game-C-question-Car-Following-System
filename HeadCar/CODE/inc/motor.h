#ifndef __MOTOR_H
#define __MOTOR_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"

#define AIN1_ON  GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN0)
#define AIN1_OFF GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0)

#define AIN2_ON  GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1)
#define AIN2_OFF GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1)

#define BIN1_ON  GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2)
#define BIN1_OFF GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2)

#define BIN2_ON  GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN5)
#define BIN2_OFF GPIO_setOutputLowOnPin(GPIO_PORT_P3,  GPIO_PIN5)

//#define MOTOR_ON GPIO_setOutputHighOnPin(GPIO_PORT_P10, GPIO_PIN4)
//#define MOTOR_OFF GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN4)

void Motor_Init(void);
void Motor_PID(void);
void Motor_Set(int motor_left, int motor_right);

#endif

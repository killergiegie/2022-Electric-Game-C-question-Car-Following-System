#ifndef __ENCODER_H_
#define __ENCODER_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"

float encoder_to_speed(int encoder);
int16_t speed_to_encoder(float speed);
void Distance_Calc(void);
void Encoder_Init(void);

#endif 

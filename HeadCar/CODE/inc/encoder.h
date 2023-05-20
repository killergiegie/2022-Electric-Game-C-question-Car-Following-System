#ifndef __ENCODER_H
#define __ENCODER_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"

void SW_Encoder_Init(void);
void SW_Encoder_Read(void);
void SW_Encoder_Clear(void);
float encoder_to_speed(int encoder);

#endif

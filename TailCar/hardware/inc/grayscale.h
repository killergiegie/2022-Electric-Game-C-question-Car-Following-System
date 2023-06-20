#ifndef __GRAYSCALE_H
#define __GRAYSCALE_H

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"

#define Gray_Get_L4 GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN6)
#define Gray_Get_L3 GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN7)
#define Gray_Get_L2 GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN1)
#define Gray_Get_L1 GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN3)
#define Gray_Get_M  GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN3)
#define Gray_Get_MU GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN3)
#define Gray_Get_LU GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN5)
#define Gray_Get_RU GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN0)
#define Gray_Get_R1 GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN4)
#define Gray_Get_R2 GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN2)
#define Gray_Get_R3 GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN2)
#define Gray_Get_R4 GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN2)

void Grayscale_Init(void);
void Grayscale_Get(void);
void Search_Line(void);

#endif // !__GRAYSCALE_H

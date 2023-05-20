#ifndef __GRAYSCALE_H
#define __GRAYSCALE_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "globalvar.h"

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

void Grayscale_Init(void);
void Grayscale_scan(void);
void Grayscale_Judge(void);
void Inner_Ring(void);
void Outer_Ring(void);

extern int CHA, CHB, CHC, CHD, CHE, CHF, CHG, CHH;

#endif

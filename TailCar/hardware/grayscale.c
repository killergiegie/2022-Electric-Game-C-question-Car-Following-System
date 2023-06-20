#include "grayscale.h"

void Grayscale_Init(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN2);
    GPIO_setAsInputPin(GPIO_PORT_P8, GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    GPIO_setAsInputPin(GPIO_PORT_P9, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3);
}

void Grayscale_Get(void)
{
    L4 = Gray_Get_L4;
    L3 = Gray_Get_L3;
    L2 = Gray_Get_L2;
    L1 = Gray_Get_L1;
    M  = Gray_Get_M ;
    MU = Gray_Get_MU;
    LU = Gray_Get_LU;
    RU = Gray_Get_RU;
    R1 = Gray_Get_R1;
    R2 = Gray_Get_R2;
    R3 = Gray_Get_R3;
    R4 = Gray_Get_R4;
}

void Search_Line(void)
{
    //ֱ��
    if(!L4 && !L3 && !L2 && !L1 && M && !R1 && !R2 && !R3 && !R4)
    {
        differ = 0;
    }
    //��ƫ1
    else if(!L4 && !L3 && !L2 && !L1 && (M || R1) && !R2 && !R3 && !R4)
    {
        differ = movement * (float)-0.15 ; 
    }
    //��ƫ2
    else if(!L4 && !L3 && !L2 && !L1 && !M && (R1 || R2) && !R3 && !R4)
    {
        differ = movement * (float)-0.25 ; 
    }
    //��ƫ3
    else if(!L4 && !L3 && !L2 && !L1 && !M && !R1 && (R2 || R3) && !R4)
    {
        differ = movement * (float)-0.35 ; 
    }
    //��ƫ4
    else if(!L4 && !L3 && !L2 && !L1 && !M && !R1 && !R2 && (R3 || R4))
    {
        differ = movement * (float)-0.65 ; 
    }
    //��ƫ5
    else if(!L4 && !L3 && !L2 && !L1 && !M && !R1 && !R2 && !R3 && R4)
    {
        differ = movement * (float)-0.85 ; 
    }
    //��ƫ1
    else if(!L4 && !L3 && !L2 && (L1 || M) && !R1 && !R2 && !R3 && !R4)
    {
        differ = movement * (float)0.15 ; 
    }
    //��ƫ2
    else if(!L4 && !L3 && (L2 || L1) && !M && !R1 && !R2 && !R3 && !R4)
    {
        differ = movement * (float)0.25 ; 
    }
    //��ƫ3
    else if(!L4 && (L3 || L2) && !L1 && !M && !R1 && !R2 && !R3 && !R4)
    {
        differ = movement * (float)0.35 ; 
    }
    //��ƫ4
    else if((L4 || L3) && !L2 && !L1 && !M && !R1 && !R2 && !R3 && !R4)
    {
        differ = movement * (float)0.65 ; 
    }
    //��ƫ5
    else if(L4 && !L3 && !L2 && !L1 && !M && !R1 && !R2 && !R3 && !R4)
    {
        differ = movement * (float)0.85 ; 
    }

}

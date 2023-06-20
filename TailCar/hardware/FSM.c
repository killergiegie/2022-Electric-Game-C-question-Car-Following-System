#include "FSM.h"
#include "stdio.h"

statedef state = NONE;
stateCROSSdef stateCROSS;
stateSTOPdef stateSTOP;

void FSM(void)
{
    switch(state)
    {
    case NONE:
        Grayscale_Get();
        Search_Line();
        //等停
        if(wait_stop_flag)
        {
            state = WAIT_STOP;
        }
        //预停止
        if(pre_stop_flag)
        {
            state = STOP;
            stateSTOP = PRE_STOP;
        }
        //识别停止位
        if((!LU && MU && !RU && L2 && L1 && M  && R1 && R2 )||
            (!LU && MU && !RU && L2 && L1 && M  && R1 && R2)||
            (LU && !MU && !RU && L3 && L2 && L1 && M  && R1)||       //出岔路误判
            (!LU && !MU && RU && L1 && M  && R1 && R2 && R3)||
            (!LU && !MU && !RU && M && R1 && R2 && R3 && R4)||
            (!LU && !MU && !RU && L4 && L3 && L2 && L1 && M)||
            (MU && L3 && L2 && L1 && M && R1 && R2 && R3 )||
            (L4 && L3 && L2 && L1 && M && R1 && R2 && R3 )||
            (L3 && L2 && L1 && M && R1 && R2 && R3 && R4))
        {
            lap++;//圈数+1
            // printf("%d\r\n",lap);
            state = CROSS;
            stateCROSS = PRE_CROSS;
        }
        break;

    case CROSS:
        // printf("%d",(int)distance);
        switch(stateCROSS)
        {
        case PRE_CROSS:
            Dis_Calc_Flag = 1;
            Grayscale_Get();
            Search_Line();
            if(distance > 25)
            {
                stateCROSS = BEFORE_CROSS;
            }
            break;

        case BEFORE_CROSS:
            Judge_Outer_Inside();
            Grayscale_Get();
            Search_Line();
            if(!outer_road)
            {
                if(distance > 30)
                {
                    stateCROSS = TURN_LEFT;
                }
            }
            else
            {
                stateCROSS = GO_STRIGHT;
            }
            break;

        /***************************************处理外圈***************************************/
        case GO_STRIGHT:
            Grayscale_Get();
            L4=0;
            L3=0;
            L2=0;
            L1=0;
            Search_Line();
            if(distance > 50)
            {
                stateCROSS = CROSS_BREAK;
                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
            }
            break;

        case CROSS_BREAK:
            Grayscale_Get();
            Search_Line();
            if(distance > 250)
            {
                Dis_Calc_Flag = 0;
                state = NONE;
                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
            }
            break;
        /************************************************************************************/

        /***************************************处理内圈***************************************/
        case TURN_LEFT:
            differ = movement * (float)0.5;
            if(distance > 45)
            {
                stateCROSS = CROSS_SPEED_UP;
            }
            break;

        case CROSS_SPEED_UP:
            Grayscale_Get();
            Search_Line();
            movement = speed_to_encoder(0.5)*1.25;
            if(distance > 120)
            {
                movement = speed_to_encoder(0.5);
                stateCROSS = CROSS_SPEED_DOWN;
            }
            break;

        case CROSS_SPEED_DOWN:
            Grayscale_Get();
            Search_Line();
            if(distance > 190)
            {
                Dis_Calc_Flag = 0;
                state = NONE;
                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
            }
            break;
        /************************************************************************************/
        }
        break;

    case STOP:
        switch(stateSTOP)
        {
        case PRE_STOP:
            Grayscale_Get();
            Search_Line();
            pre_stop_flag = 0;
            if(ult_distance < 24 && task == 1)
            {
                motor_flag = 0;
                stateSTOP = IN_STOP;
            }
            else if(ult_distance < 33)
            {
                motor_flag = 0;
                stateSTOP = IN_STOP;
            }
                
            break;
        case IN_STOP:
            if(motor_flag)
            {
                state = NONE;
            }
                
            break;
        }
        break;
    case WAIT_STOP:
        Grayscale_Get();
        Search_Line();
        wait_stop_flag = 0;
        Dis_Calc_Flag = 1;
        if(distance > 100)
        {
            state = NONE;
        }
        break;
    default:
        break;
    }
}

void Judge_Outer_Inside(void)
{
    switch(task)
    {
        case 1:
            if(lap==1)
                outer_road = 1;
            break;
        case 2:
            if(lap==1)
                outer_road = 1;
            if(lap==2)
                outer_road = 1;
            break;
        case 3:
            if(lap==1)
                outer_road = 1;
            if(lap==2)
                outer_road = 0;
            if(lap==3)
                outer_road = 1;
            break;
        case 4:
            if(lap==1)
                outer_road = 1;
            break;
        case 5:
            outer_road = lap%2;
            break;
        default:
            break;
    }
}

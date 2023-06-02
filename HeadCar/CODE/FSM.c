#include "FSM.h"

statedef state;
stateCROSSdef stateCROSS;
//stateWAITEdef stateWAITE;

void FSM(void)
{
    switch(state)
    {
    case NONE: // 初始状态，此时会判断停止线
        Grayscale_Judge();
        if ((a && C && D && F && h) || (a && b && c && F && G && H) || (A && B && C && f && g && h) || (gray_state >= 4)) // 停止线
        {
            lap++;
            switch (task)
            {
            case 1:
                if (lap == 1)
                {
                    movement = 0.3 * 100;
                    cross_flag = 1; // 外圈
                }
                else if (lap == 2)
                {
                    motor_flag = 0;
                    send_flag = 0x00; // 通信，发送停车指令
                    BEEP_On();
                }
                break;
            case 2:
                if(lap < 3)
                {
                    movement = 0.5 * 100;
                    cross_flag = 1; // 外圈
                }
                else if(lap == 3)
                {
                    motor_flag = 0;
                    send_flag = 0x00; // 通信，发送停车指令
                    BEEP_On();
                }
                break;
            case 3:
                if(lap < 3)
                {
                    movement = 0.5 * 100;
                    cross_flag = 1; // 外圈 
                }
                else if(lap == 3)
                {
                    cross_flag = 0; // 内圈
                }
                else if(lap == 4)
                {
                    motor_flag = 0;
                    send_flag = 0x00; // 通信，发送停车指令
                    BEEP_On();
                }
                break;
            case 4:
                if(lap < 2)
                {
                    movement = 0.5 * 100;
                    cross_flag = 1; // 外圈
                }
                else if(lap == 2)
                {
                    motor_flag = 0;
                    send_flag = 0x00; // 通信，发送停车指令
                    BEEP_On();
                }
                break;
            default:
                break;
            }
            state = CROSS; // 进入岔路口状态
            stateCROSS = PRE_CROSS; // 子状态为预入岔
            LED_RED_Tog();
        }
        break;

    case CROSS:
        switch(stateCROSS)
        {
        case PRE_CROSS:
            road_flag = 1; //开始累计路程
            if(road > 20) // 走到岔路口
            {
                stateCROSS = IN_CROSS;
            }
            else 
            {
                Grayscale_Judge(); // 正常循迹
            }
            gray_state = 1;
            break;

        case IN_CROSS:
            if((task == 3) && (cross_flag == 0) && (road < 180))
            {
                movement = 0.5 * 100 + 15; // 内圈加速
                LED_R_Tog();
            }
            else if((task == 3) && (cross_flag == 0) && (road > 180))
            {
                movement = 0.5 * 100; // 内圈速度还原
            }

            if(road < 55)
            {
                if (cross_flag == 1) // 走外圈
                {
                    Outer_Ring(); // 外圈循迹
                }
                else if (cross_flag == 0) // 走内圈
                {
                    Inner_Ring(); // 内圈循迹
                }
            }
            else if(road < 450)
            {
                // if((ult_distance < 20) && (task == 3) && (lap == 2))
                // {
                //     movement = 0.5 * 100 * 0.7; // 降速
                // }
                // else if((ult_distance >= 20) && (task == 3) && (lap == 2))
                // {
                //     movement = 0.5 * 100; // 速度还原
                // }
                Grayscale_Judge(); // 正常循迹
                if(road > 300)
                {
                    if ((task == 4) && C && D && F) // 等停线
                    {
                        state = WAIT; // 进入等停状态
                        BEEP_On();
                    }
                }
            }
            else if(road > 450)
            {
                state = NONE;
                road_flag = 0;
            }
            gray_state = 2;
            break;

        default:
            break;
        }
        break;
    
    case WAIT:
        wait_flag = 1; // 开始累计时间
        motor_flag = 0; // 停止电机
        send_flag = 0x02; // 通信，发送停车指令

        if (wait_time > 166) // 等待5秒
        {
            motor_flag = 1;
            send_flag = 1; // 通信，发送启动指令
            Grayscale_Judge(); // 正常循迹
            if (wait_time > 200)
            {
                wait_flag = 0; // 停止累计时间
                state = NONE;  // 退出等停状态, 进入无状态
            }
        }
        
        break;

    default:
        break;
    }
}

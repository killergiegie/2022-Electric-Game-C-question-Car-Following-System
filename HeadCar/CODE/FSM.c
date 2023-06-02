#include "FSM.h"

statedef state;
stateCROSSdef stateCROSS;
//stateWAITEdef stateWAITE;

void FSM(void)
{
    switch(state)
    {
    case NONE: // ��ʼ״̬����ʱ���ж�ֹͣ��
        Grayscale_Judge();
        if ((a && C && D && F && h) || (a && b && c && F && G && H) || (A && B && C && f && g && h) || (gray_state >= 4)) // ֹͣ��
        {
            lap++;
            switch (task)
            {
            case 1:
                if (lap == 1)
                {
                    movement = 0.3 * 100;
                    cross_flag = 1; // ��Ȧ
                }
                else if (lap == 2)
                {
                    motor_flag = 0;
                    send_flag = 0x00; // ͨ�ţ�����ͣ��ָ��
                    BEEP_On();
                }
                break;
            case 2:
                if(lap < 3)
                {
                    movement = 0.5 * 100;
                    cross_flag = 1; // ��Ȧ
                }
                else if(lap == 3)
                {
                    motor_flag = 0;
                    send_flag = 0x00; // ͨ�ţ�����ͣ��ָ��
                    BEEP_On();
                }
                break;
            case 3:
                if(lap < 3)
                {
                    movement = 0.5 * 100;
                    cross_flag = 1; // ��Ȧ 
                }
                else if(lap == 3)
                {
                    cross_flag = 0; // ��Ȧ
                }
                else if(lap == 4)
                {
                    motor_flag = 0;
                    send_flag = 0x00; // ͨ�ţ�����ͣ��ָ��
                    BEEP_On();
                }
                break;
            case 4:
                if(lap < 2)
                {
                    movement = 0.5 * 100;
                    cross_flag = 1; // ��Ȧ
                }
                else if(lap == 2)
                {
                    motor_flag = 0;
                    send_flag = 0x00; // ͨ�ţ�����ͣ��ָ��
                    BEEP_On();
                }
                break;
            default:
                break;
            }
            state = CROSS; // �����·��״̬
            stateCROSS = PRE_CROSS; // ��״̬ΪԤ���
            LED_RED_Tog();
        }
        break;

    case CROSS:
        switch(stateCROSS)
        {
        case PRE_CROSS:
            road_flag = 1; //��ʼ�ۼ�·��
            if(road > 20) // �ߵ���·��
            {
                stateCROSS = IN_CROSS;
            }
            else 
            {
                Grayscale_Judge(); // ����ѭ��
            }
            gray_state = 1;
            break;

        case IN_CROSS:
            if((task == 3) && (cross_flag == 0) && (road < 180))
            {
                movement = 0.5 * 100 + 15; // ��Ȧ����
                LED_R_Tog();
            }
            else if((task == 3) && (cross_flag == 0) && (road > 180))
            {
                movement = 0.5 * 100; // ��Ȧ�ٶȻ�ԭ
            }

            if(road < 55)
            {
                if (cross_flag == 1) // ����Ȧ
                {
                    Outer_Ring(); // ��Ȧѭ��
                }
                else if (cross_flag == 0) // ����Ȧ
                {
                    Inner_Ring(); // ��Ȧѭ��
                }
            }
            else if(road < 450)
            {
                // if((ult_distance < 20) && (task == 3) && (lap == 2))
                // {
                //     movement = 0.5 * 100 * 0.7; // ����
                // }
                // else if((ult_distance >= 20) && (task == 3) && (lap == 2))
                // {
                //     movement = 0.5 * 100; // �ٶȻ�ԭ
                // }
                Grayscale_Judge(); // ����ѭ��
                if(road > 300)
                {
                    if ((task == 4) && C && D && F) // ��ͣ��
                    {
                        state = WAIT; // �����ͣ״̬
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
        wait_flag = 1; // ��ʼ�ۼ�ʱ��
        motor_flag = 0; // ֹͣ���
        send_flag = 0x02; // ͨ�ţ�����ͣ��ָ��

        if (wait_time > 166) // �ȴ�5��
        {
            motor_flag = 1;
            send_flag = 1; // ͨ�ţ���������ָ��
            Grayscale_Judge(); // ����ѭ��
            if (wait_time > 200)
            {
                wait_flag = 0; // ֹͣ�ۼ�ʱ��
                state = NONE;  // �˳���ͣ״̬, ������״̬
            }
        }
        
        break;

    default:
        break;
    }
}

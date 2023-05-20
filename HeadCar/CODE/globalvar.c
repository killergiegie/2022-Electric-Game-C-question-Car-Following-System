#include "globalvar.h"

// ������
int encoder_left = 0;
int encoder_right = 0;
float speed_left = 0;
float speed_right = 0;

// ������
int ult_distance = 0;

// ״̬
float road = 0;     // ·��
int road_flag = 0;  // ·�̱�־λ
int lap = 0;        // Ȧ��
int task = 1;       // ����
int cross_flag = 0; // ��·�ڱ�����Ȧ��־λ, 1Ϊ��Ȧ, 0Ϊ��Ȧ
int wait_flag = 0;  // ��ͣ��־λ
int wait_time = 0;  // ��ͣ��ʱ
int send_flag = 0;  // ���ͱ�־λ
int last_send_flag = 0;  // ��һ�εķ��ͱ�־λ

// ���
PID pid_left, pid_right;
int movement = 0; // movement_left = 0, movement_right = 0;
float movement_left = 0, movement_right = 0;
int motor_left = 0;
int motor_right = 0;
int motor_flag = 0;

// �Ҷȴ�����
int gray_state = 0;
int small_kdiff = 0;
int medium_kdiff = 0;
int large_kdiff = 0;

// ���ߴ���ͨ��
int usart0_rx_data = 0;

// ������
int beep_flag = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ֵ����
//  @param      dat				��Ҫ�����ֵ����
//  @return     int				���ؾ���ֵ
//  Sample usage:				dat = myabs(dat);//��dat�������
//-------------------------------------------------------------------------------------------------------------------
int myabs(int dat)
{
    if (dat >= 0)
        return dat;
    else
        return -dat;
}

#include "globalvar.h"

//������
int16_t encoder_left, encoder_right;
bool Dis_Calc_Flag = 0;
float distance;
float per = 0.02;

//���
bool motor_flag = 0;
PID pid_left, pid_right;
float movement_left, movement_right, movement = 50;
float differ = 0;
float dis_movement = 0;

//�Ҷȴ�����
bool L4,L3,L2,L1,M,MU,LU,RU,R1,R2,R3,R4;

//����Ҫ��
int8_t lap = 0;         //Ȧ��
int8_t task = 5;        //����
bool outer_road = 1;    //����Ȧ��1��Ȧ��0��Ȧ
bool wait_stop_flag = 0;//��ͣ��־λ
bool pre_stop_flag = 0; //Ԥֹͣ��־λ
bool chase_flag = 0;    //���ٱ�־λ

//������
int16_t ult_distance = 50;
bool ult_flag = 1;
PID pid_dis;


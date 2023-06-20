#ifndef  __PID_H
#define  __PID_H

typedef struct
{
    float kp,ki,kd;                         //����ϵ��
    float error,lastError,lastlastError;    //���ϴ������ϴ����
    float integral,maxIntegral;             //���֡������޷�
    float output,maxOutput;                 //���������޷�
} PID;

void Incremental_PID_Init(PID *pid, float p, float i, float d, float maxOutput);
void Incremental_PID_Calc(PID *pid, float set_value, float get_value);

void Positional_PID_Init(PID *pid, float p, float i, float d, float maxI, float maxOutput);
void Positional_PID_Calc(PID *pid,float set_value, float get_value);

#endif


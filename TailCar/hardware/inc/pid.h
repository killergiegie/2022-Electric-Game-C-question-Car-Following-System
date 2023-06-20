#ifndef  __PID_H
#define  __PID_H

typedef struct
{
    float kp,ki,kd;                         //三个系数
    float error,lastError,lastlastError;    //误差、上次误差、上上次误差
    float integral,maxIntegral;             //积分、积分限幅
    float output,maxOutput;                 //输出、输出限幅
} PID;

void Incremental_PID_Init(PID *pid, float p, float i, float d, float maxOutput);
void Incremental_PID_Calc(PID *pid, float set_value, float get_value);

void Positional_PID_Init(PID *pid, float p, float i, float d, float maxI, float maxOutput);
void Positional_PID_Calc(PID *pid,float set_value, float get_value);

#endif


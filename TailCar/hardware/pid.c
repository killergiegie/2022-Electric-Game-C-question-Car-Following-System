#include "pid.h"

/**************************************************************************
函数功能：增量式PID参数的初始化
入口参数：pid指针、初始化设定的p、i、d值、输出限幅值
返回  值：无
**************************************************************************/
void Incremental_PID_Init(PID *pid, float p, float i, float d, float maxOutput)
{
	pid->kp = p;
	pid->ki = i;
	pid->kd = d;
	pid->maxOutput = maxOutput;
}


/**************************************************************************
函数功能：增量PI控制器
入口参数：pid指针、目标值、反馈值
返回  值：无
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
void Incremental_PID_Calc(PID *pid, float set_value,float get_value)
{
	pid->error = set_value - get_value;      									//计算偏差
	pid->output += pid->kp*(pid->error - pid->lastError) + pid->ki*pid->error + \
				pid->kd*(pid->error - 2*pid->lastError + pid->lastlastError);			//增量式PI控制器
	pid->lastlastError = pid->lastError;    											//保存上上次误差
	pid->lastError = pid->error;	           											//保存上一次偏差

	if (pid->output > pid->maxOutput)
        pid->output = pid->maxOutput;
    else if (pid->output < -pid->maxOutput)
        pid->output = -pid->maxOutput;													//输出限幅
}

/**************************************************************************
函数功能：位置式PID参数的初始化
入口参数：pid指针、初始化设定的p、i、d值、积分限幅值、输出限幅值
返回  值：无
**************************************************************************/
void Positional_PID_Init (PID *pid, float p, float i, float d, float maxI, float maxOutput)
{
    pid->kp = p;
    pid->ki = i;
    pid->kd = d;
    pid->maxIntegral = maxI;
    pid->maxOutput = maxOutput;
}

//进行一次pid计算
//参数为(pid结构体,目标值,反馈值)，计算结果放在pid结构体的output成员中
void Positional_PID_Calc (PID *pid,float set_value, float get_value)
{
	float dout,pout;
    //更新数据
    pid->lastError = pid->error; 							//将旧error存起来
    pid->error = set_value - get_value; 					//计算新error

    //计算微分
    dout = (pid->error - pid->lastError) * pid->kd;
    //计算比例
    pout = pid->error * pid->kp;
    //计算积分
    pid->integral += pid->error * pid->ki;

    //积分限幅
    if (pid->integral > pid->maxIntegral)
        pid->integral = pid->maxIntegral;
    else if (pid->integral < -pid->maxIntegral)
        pid->integral = -pid->maxIntegral;
    //计算输出
    pid->output = pout + dout + pid->integral;
    //输出限幅
    if (pid->output > pid->maxOutput)
        pid->output = pid->maxOutput;
    else if (pid->output < -pid->maxOutput)
        pid->output = -pid->maxOutput;
}


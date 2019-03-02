#include "main.h"

/**
  * @brief  PID反馈算法
  * @param  PID_Struct *P  PID参数结构体
  *         ActualValue    PID计算反馈量（当前真实检测值）
  * @retval PID反馈计算输出值
  */
extern RM820R_Receive ChassisReceive[4];
extern int Pos_Current,Speed_Current;
Pid_Typedef Pid_pos,Pid_speed;
float SetCircleNum=0;
float NowCircleNum=0;
int CirCount=0,num=0,SpeedDef=500;
float NowPos,LastPos=0,NowSpeed;
float RealPos=0,LastRealPos=0;
extern float FirstPos,PosError;
s16 nowpos=0,lastpos=0;
void PIDInit_pos(Pid_Typedef *Pid)
{
	Pid->P=0.5;
	Pid->I=0.002;
	Pid->D=0.003;
	Pid->LastError=0.0;
	Pid->PreError=0.0;
	Pid->SumError=0.0;
	Pid->dError=0.0;
	Pid->POut=0.0;
	Pid->IOut=0.0;
	Pid->DOut=0.0;
	Pid->IMax=49999.0;
}
void PIDInit_speed(Pid_Typedef *Pid)
{
	Pid->P=4.5;
	Pid->I=0.18;
	Pid->D=1;
	Pid->LastError=0.0;
	Pid->PreError=0.0;
	Pid->SumError=0.0;
	Pid->dError=0.0;
	Pid->POut=0.0;
	Pid->IOut=0.0;
	Pid->DOut=0.0;
	Pid->IMax=49999.0;
}
//////////////////////////////////////////////////////下面是位置环PID代码
/*void SetPos(void)
{
	NowPos=PitchReceive.Angle;
	//delay_ms(3);
	if((NowPos<500) && (LastPos>7500.0))
	{
		CirCount++;
	}
	else if((NowPos>7500) && (LastPos<500.0))
	{
		CirCount--;
	}
	NowCircleNum=CirCount+NowPos/8191.0;
	RealPos=NowPos+(((int)NowCircleNum)*8191.0);
	Pid_pos.SetPoint=(SetCircleNum+(FirstPos/8191.0))*8191.0;
	Pos_Current=-PID_Calc(&Pid_pos,RealPos);
	Pos_Current=LIMIT_MAX_MIN(Pos_Current, 4998, -4998);
	LastPos=NowPos;
}*/
///////////////////////////////////////////////////下面是速度环PID代码
void SetSpeed(u16 SpeedSet)
{
	//RealPos
	nowpos=ChassisReceive[0].angle;
	Pid_speed.SetPoint=SpeedSet;
	//NowSpeed=PosError/1000;
	//NowSpeed=NowPos-LastPos;
	//NowSpeed=(nowpos-lastpos)*10;
	NowSpeed=ChassisReceive[0].speed;
	Speed_Current=PID_Calc(&Pid_speed,NowSpeed);
	Speed_Current=LIMIT_MAX_MIN(Speed_Current, 10000, -10000);
	lastpos=nowpos;
}


float PID_Calc(Pid_Typedef *P, float ActualValue)
{
		P->PreError = P->SetPoint - ActualValue;
		P->dError = P->PreError - P->LastError;
	
		P->SumError += P->PreError;
		P->LastError = P->PreError;
		
		if(P->SumError >= P->IMax)
			P->SumError = P->IMax;
		else if(P->SumError <= -P->IMax)
			P->SumError = -P->IMax;
		
		P->POut = P->P * P->PreError;
		P->IOut = P->I * P->SumError;
		P->DOut = P->D * P->dError;
		
		return P->POut+P->IOut+P->DOut;
}


#include "main.h"
int Pos_Current=0,Speed_Current=0;
extern Pid_Typedef Pid_pos,Pid_speed;
float a,b=0,FirstPos=0,Pos1=0,Pos2=0,PosError=0;
float	a=200;
int main(void)

{	
	//CAN_Config();
	//CAN_Filter_Config();
	CAN_Config();
	CAN_Filter_Config();
	TIM6_Configration();
	TIM7_Configration();
	PIDInit_pos(&Pid_pos);
	PIDInit_speed(&Pid_speed);
	//CAN_Tx_6632(Pos_Current,Pitch_ID);
	delay_ms(100);
	SysTick_Init();
  while(1)
	{	
		
	}
}
void SysTick_Handler(void)
{
	//Pos1=PitchReceive.Angle;
	//SetPos();
	
	SetSpeed(a);
	ChassisSend(Speed_Current,0,0,0);
	//CAN_Tx_6632(Speed_Current,Pitch_ID);
	
}


/*********************************************END OF FILE**********************/


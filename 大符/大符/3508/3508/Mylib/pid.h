#ifndef __PID_H__
#define __PID_H__

typedef struct PID{
		float SetPoint;			//�趨Ŀ��ֵ
		
		float P;						//��������
		float I;						//���ֳ���
		float D;						//΢�ֳ���
		
		float LastError;		//ǰ�����
		float PreError;			//��ǰ���
		float SumError;			//�������
		float dError;
	
		float IMax;					//��������
		
		float POut;					//�������
		float IOut;					//�������
		float DOut;					//΢�����
}Pid_Typedef;

float PID_Calc(Pid_Typedef * P, float ActualValue);
void PIDInit_pos(Pid_Typedef *Pid);
void PIDInit_speed(Pid_Typedef *Pid);
void SetPos(void);
void SetSpeed(u16 SpeedSet);
#endif

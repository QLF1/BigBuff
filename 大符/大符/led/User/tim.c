#include "main.h"
 /**
  * @brief  1ms��ȷ��ʱ
  * @param  ��
  * @retval ��
  */

static void Tim_Config(void)
{
	
	TIM_TimeBaseInitTypeDef tim_init;
	
	TIM_DeInit(TIM3);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	tim_init.TIM_Period=7200-1;
	tim_init.TIM_Prescaler=10-1;
	tim_init.TIM_CounterMode=TIM_CounterMode_Up;
	tim_init.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&tim_init);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	TIM_Cmd(TIM3,ENABLE);
	while(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)!=SET);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	TIM_Cmd(TIM3,DISABLE);
}

 /**
  * @brief  ������ʱ,ҶƬ��ȫ������ʱ�˳�
  * @param  ��
  * @retval ��
  */

extern volatile u8 temp[6];				//�����־λ
extern volatile u8 Led_Status[6];	//װ�װ�״̬λ
void Delay_Ms(u32 time,u8 led_num)
{
	u8 num,i;
	while(time--)
	{
		Tim_Config();
		if((temp[led_num]!=HIT_RESET)&&(Led_Status[led_num]!=LED_OFF))
			return;
	}
	
	for(num=1;num<6;num++)
	{
		if((Led_Status[num]!=LED_OFF)&&(temp[num]==HIT_RESET))
		{
			for(i=1;i<6;i++)
			{
				temp[i]=HIT_RESET;
				Led_Status[i]=LED_OFF;
			}
			LED_AllOFF();
			break;
		}
	}
	return;
}

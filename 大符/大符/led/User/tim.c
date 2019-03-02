#include "main.h"
 /**
  * @brief  1ms精确延时
  * @param  无
  * @retval 无
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
  * @brief  亮灯延时,叶片完全点亮或到时退出
  * @param  无
  * @retval 无
  */

extern volatile u8 temp[6];				//激活标志位
extern volatile u8 Led_Status[6];	//装甲板状态位
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

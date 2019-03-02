#include "main.h" 
/**
  * @brief  ad采集函数
  * @param  无  
  * @retval 无
  */


double adata,limit=1.70;
u32 Count;

u32 ReadCount(void)
{

	unsigned char i;
	GPIO_InitTypeDef gpio;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = ADSK  ;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	gpio.GPIO_Pin = ADDO;	
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);	
	//GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
	//GPIO_ResetBits(GPIOA, ADSK);
	
 GPIO_ResetBits(GPIOA, ADSK);
 Count=0;
 while(GPIO_ReadInputDataBit(GPIOA, ADDO)); 
 for (i=0;i<24;i++)
 {
		 GPIO_SetBits(GPIOA, ADSK); 
     SysTick_Delay_Us(5);	 
	   Count=Count<<1; 
		 if(GPIO_ReadInputDataBit(GPIOA, ADDO))
			 Count++;
	  // SysTick_Delay_Us(5);
		 GPIO_ResetBits(GPIOA, ADSK);
	   SysTick_Delay_Us(5);	 
	}
		 GPIO_SetBits(GPIOA, ADSK);
	   SysTick_Delay_Us(5);	 
		 //Count=Count^0x800000;
	   Count=Count^0x800000;
	   //SysTick_Delay_Us(5);
		 GPIO_ResetBits(GPIOA, ADSK);
	   SysTick_Delay_Us(5);	 
		 return(Count);
}
u32 ADReact(void)
{
		//adata=((double)ReadCount() / 0x00ffffff) * 3.3;
	  u32 adata=ReadCount();
	return adata;
}

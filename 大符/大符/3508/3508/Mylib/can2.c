#include "main.h"

/************************************************************************************
CAN2控制底盘，ID号如下：
			头
			|
	0x201	|   0x204
			|
————————————————————————————
			|
	0x202	|   0x203
			|
		尾（爪子）

***************************************************************************************/

RM820R_Receive ChassisReceive[4];

static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

static void NVIC_Configuration(void)
{
	  NVIC_InitTypeDef       nvic;
    nvic.NVIC_IRQChannel = CAN2_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 2;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
		
		nvic.NVIC_IRQChannel = CAN2_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic); 
}

void CAN_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  CAN_InitTypeDef CAN_InitStructure;	
  RCC_AHB1PeriphClockCmd(TEST_CAN_RX_GPIO_CLK,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2, ENABLE);
  GPIO_PinAFConfig(TEST_CAN_RX_GPIO_PORT,TEST_CAN_RX_SOURCE,TEST_CAN_RX_AF);
  GPIO_PinAFConfig(TEST_CAN_TX_GPIO_PORT,TEST_CAN_TX_SOURCE,TEST_CAN_TX_AF);

  GPIO_InitStructure.GPIO_Pin = TEST_CAN_TX_PIN | TEST_CAN_RX_PIN  ; 
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_Init(TEST_CAN_TX_GPIO_PORT, &GPIO_InitStructure);
  
  CAN_DeInit(CAN2);
  CAN_StructInit(&CAN_InitStructure);	
	
	CAN_InitStructure.CAN_ABOM = ENABLE;
	CAN_InitStructure.CAN_AWUM = ENABLE;
	CAN_InitStructure.CAN_NART = ENABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_TXFP = ENABLE;
	
	CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_Prescaler = TEST_CAN_DIV;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

	CAN_Init(TEST_CAN, &CAN_InitStructure); 

	NVIC_Configuration();
  CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
	CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE); 
//	CAN_ITConfig(TEST_CAN, CAN_IT_FMP0, ENABLE);	
}

void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_Filter_Struct;
	
	CAN_Filter_Struct.CAN_FilterNumber = 16;
	CAN_Filter_Struct.CAN_FilterScale = CAN_FilterScale_32bit ;
	CAN_Filter_Struct.CAN_FilterMode = CAN_FilterMode_IdMask ;//掩码模式
	CAN_Filter_Struct.CAN_FilterFIFOAssignment = CAN_FilterFIFO0 ; //报文存储在FIFO 0
	CAN_Filter_Struct.CAN_FilterActivation = ENABLE ;
	
	CAN_Filter_Struct.CAN_FilterIdHigh = 0;
	CAN_Filter_Struct.CAN_FilterIdLow =0;
	CAN_Filter_Struct.CAN_FilterMaskIdHigh =0;
	CAN_Filter_Struct.CAN_FilterMaskIdLow =0;	
	CAN_FilterInit(&CAN_Filter_Struct);
}

/**
  * @brief  CAN2发送中断
  * @param  None
  * @retval None
  */
void CAN2_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN2, CAN_IT_TME) != RESET) 
	{
		CAN_ClearITPendingBit(CAN2, CAN_IT_TME);
	}
}

/**
  * @brief  CAN2接收中断
  * @param  None
  * @retval None
  */
void CAN2_RX0_IRQHandler(void)
{
    CanRxMsg rx_message;
    if (CAN_GetITStatus(CAN2, CAN_IT_FMP0) != RESET)
    {
        CAN_Receive(CAN2, CAN_FIFO0, &rx_message);
        switch(rx_message.StdId)
        {
            case 0x201:                                                          
                ChassisReceive[0].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                ChassisReceive[0].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
            break;
            
            case 0x202:
                ChassisReceive[1].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                ChassisReceive[1].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
            break;
            
            case 0x203:
                ChassisReceive[2].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                ChassisReceive[2].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
            break;
            
            case 0x204:
                ChassisReceive[3].angle = (rx_message.Data[0] << 8) | rx_message.Data[1];
                ChassisReceive[3].speed = (rx_message.Data[2] << 8) | rx_message.Data[3];
            break;            
        }
       // Flag.CAN2Cnt= 0;
       // Flag.CAN2Connect = 1;
        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
    }
	
}

/**
  * @brief  CAN2发送数据
  * @param  a：0x201电流给定
            b：0x202电流给定
            c：0x203电流给定
            d：0x204电流给定
  * @retval None
  */
void ChassisSend(int a, int b, int c, int d)
{
    CanTxMsg tx_message;
    tx_message.IDE = CAN_ID_STD;    
    tx_message.RTR = CAN_RTR_DATA; 
    tx_message.DLC = 0x08;    
    tx_message.StdId = RM820R_0x204_1;
	
    a = LIMIT_MAX_MIN(a, 15000, -15000);
    b = LIMIT_MAX_MIN(b, 15000, -15000);
    c = LIMIT_MAX_MIN(c, 15000, -15000);
    d = LIMIT_MAX_MIN(d, 15000, -15000);
	  
	
    tx_message.Data[0] = (unsigned char)((a >> 8) & 0xff);
    tx_message.Data[1] = (unsigned char)(a & 0xff);  
    tx_message.Data[2] = (unsigned char)((b >> 8) & 0xff);
    tx_message.Data[3] = (unsigned char)(b & 0xff);
    tx_message.Data[4] = (unsigned char)((c >> 8) & 0xff);
    tx_message.Data[5] = (unsigned char)(c & 0xff);
    tx_message.Data[6] = (unsigned char)((d >> 8) & 0xff); 
    tx_message.Data[7] = (unsigned char)(d & 0xff);

    CAN_Transmit(CAN2, &tx_message);
}



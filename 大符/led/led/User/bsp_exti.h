#ifndef __EXTI_H
#define	__EXTI_H

#include "stm32f10x_exti.h"
#include "stm32f10x.h"


//Òý½Å¶¨Òå
#define KEY1_INT_GPIO_PORT         GPIOA
#define KEY1_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN          GPIO_Pin_11
#define KEY1_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource11
#define KEY1_INT_EXTI_LINE         EXTI_Line11
#define KEY1_INT_EXTI_IRQ          EXTI15_10_IRQn

#define KEY1_IRQHandler            EXTI15_10_IRQHandler

#define KEY2_INT_GPIO_PORT         GPIOA
#define KEY2_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEY2_INT_GPIO_PIN          GPIO_Pin_12
#define KEY2_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define KEY2_INT_EXTI_PINSOURCE    GPIO_PinSource12
#define KEY2_INT_EXTI_LINE         EXTI_Line12
#define KEY2_INT_EXTI_IRQ          EXTI15_10_IRQn

#define KEY2_IRQHandler            EXTI15_10_IRQHandler

#define KEY3_INT_GPIO_PORT         GPIOB
#define KEY3_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define KEY3_INT_GPIO_PIN          GPIO_Pin_6
#define KEY3_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEY3_INT_EXTI_PINSOURCE    GPIO_PinSource6
#define KEY3_INT_EXTI_LINE         EXTI_Line6
#define KEY3_INT_EXTI_IRQ          EXTI9_5_IRQn

#define KEY3_IRQHandler            EXTI9_5_IRQHandler

#define KEY4_INT_GPIO_PORT         GPIOB
#define KEY4_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define KEY4_INT_GPIO_PIN          GPIO_Pin_0
#define KEY4_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEY4_INT_EXTI_PINSOURCE    GPIO_PinSource0
#define KEY4_INT_EXTI_LINE         EXTI_Line0
#define KEY4_INT_EXTI_IRQ          EXTI0_IRQn

#define KEY4_IRQHandler            EXTI0_IRQHandler

#define KEY5_INT_GPIO_PORT         GPIOB
#define KEY5_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define KEY5_INT_GPIO_PIN          GPIO_Pin_5
#define KEY5_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEY5_INT_EXTI_PINSOURCE    GPIO_PinSource5
#define KEY5_INT_EXTI_LINE         EXTI_Line5
#define KEY5_INT_EXTI_IRQ          EXTI9_5_IRQn

#define KEY5_IRQHandler            EXTI9_5_IRQHandler

void EXTI_Key_Config(void);


#endif /* __EXTI_H */

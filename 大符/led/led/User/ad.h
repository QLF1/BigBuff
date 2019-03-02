#ifndef __AD_H
#define	__AD_H
#include "stm32f10x.h"

u32 ReadCount(void);
u32 ADReact(void);
#define  ADSK  GPIO_Pin_12
#define  ADDO  GPIO_Pin_15
#endif


#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "bsp_led.h"
#include "stdlib.h"  
#include "bsp_SysTick.h"
#include "core_cm3.h"
#include "misc.h"
#include "ad.h"   
#include "bsp_exti.h"
#include "stm32f10x_exti.h"
#include "tim.h"

#define SOFT_DELAY Delay(0x0FFFFF);
void Delay(__IO uint32_t nCount);
void System_Config(void);

#endif

#ifndef __MAIN_H__
#define __MAIN_H__

#define pos 0     //此处定义云台安装位置，0表示P-P,Y-Y,1表示P-Y,Y-P
//Standard Lib
#include <stm32f4xx.h>	 
//#include <stm32f4xx_conf.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "bsp_systick.h"
//Mylib
#include "can2.h"
#include "pid.h"
#include "delay.h"
//Task lib
typedef struct
{
    s16 angle;					//角度返回值
	s16 last_angle;				//前一次角度返回值
	s16 cycle;					//圈数
    s16 speed;					//实时速度
}RM820R_Receive;

#define ABS(x) ((x)>0? (x):(-(x))) 
#define LIMIT_MAX_MIN(x, max, min)	(((x) <= (min)) ? (min):(((x) >= (max)) ? (max) : (x)))
#endif


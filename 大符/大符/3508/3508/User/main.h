#ifndef __MAIN_H__
#define __MAIN_H__

#define pos 0     //�˴�������̨��װλ�ã�0��ʾP-P,Y-Y,1��ʾP-Y,Y-P
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
    s16 angle;					//�Ƕȷ���ֵ
	s16 last_angle;				//ǰһ�νǶȷ���ֵ
	s16 cycle;					//Ȧ��
    s16 speed;					//ʵʱ�ٶ�
}RM820R_Receive;

#define ABS(x) ((x)>0? (x):(-(x))) 
#define LIMIT_MAX_MIN(x, max, min)	(((x) <= (min)) ? (min):(((x) >= (max)) ? (max) : (x)))
#endif


#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"  	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

typedef struct
{
	int mit_count;
	u8 mit_flag;
}_MIT;


extern _MIT MIT1_S;
extern _MIT MIT2_S;
extern _MIT MIT3_S;
extern _MIT MIT4_S;



void EXTIX_Init(void);	//�ⲿ�жϳ�ʼ��		 		
void EXTI_Free(void);
#endif


























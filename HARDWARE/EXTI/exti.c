#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"
#include "timer.h"
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

_MIT MIT1_S;
_MIT MIT2_S;
_MIT MIT3_S;
_MIT MIT4_S;

void EXTI_Free(void)
{
	EXTI->IMR &= ~(EXTI_Line1);
	EXTI->IMR &= ~(EXTI_Line2);	
	EXTI->IMR &= ~(EXTI_Line3);	
	EXTI->IMR &= ~(EXTI_Line4);	
}


//�ⲿ�ж�0�������
void EXTI1_IRQHandler(void)
{
	 if(MIT1==0)	  
	{	
		MIT1_S.mit_count=T_count;
		EXTI->IMR &= ~(EXTI_Line1);	
		MIT1_S.mit_flag=1;
	}	
	 EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ 
}

//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	if(MIT2==0)	  
	{	
		MIT2_S.mit_count=T_count;
		EXTI->IMR &= ~(EXTI_Line2);	
		MIT2_S.mit_flag=1;
	}	
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	if(MIT3==0)	  
	{	
		MIT3_S.mit_count=T_count;
		EXTI->IMR &= ~(EXTI_Line3);	
		MIT3_S.mit_flag=1;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	if(MIT4==0)	  
	{
		MIT4_S.mit_count=T_count;
		EXTI->IMR &= ~(EXTI_Line4);	
		MIT4_S.mit_flag=1;
	}
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}

//void EXTI9_5_IRQHandler(void)
//{
//    if(MIT1==0)	  
//	{	
//		MIT1_S.mit_count=T_count%50000;
//		EXTI->IMR &= ~(EXTI_Line5);	
//		MIT1_S.mit_flag=1;
//	}	
//	 EXTI_ClearITPendingBit(EXTI_Line5); //���LINE5�ϵ��жϱ�־λ
//}

//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);//PE1 ���ӵ��ж���1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 ���ӵ��ж���4
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);//PE5 ���ӵ��ж���5
	
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	
	/* ����EXTI_Line2,3,4 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
  
//    /* ����EXTI_Line5 */
//  EXTI_InitStructure.EXTI_Line = EXTI_Line5;//LINE5
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE5
//  EXTI_Init(&EXTI_InitStructure);//����
 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
  
//  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
	   
}













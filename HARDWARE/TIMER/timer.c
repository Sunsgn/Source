#include "timer.h"
#include "led.h"
#include "usart.h"
#include "exti.h"
#include "delay.h"
#include "TDOA.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
//��ʼ������
void TIM1_Int_Init(u16 arr,u16 psc)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrecture;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);/*ʹ�ܶ�ʱ��1��ʱ��*/


NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;/*��ʱ��1���ж�ͨ��ʹ��*/
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;/*��ʱ��1���ж�ͨ��ʹ��*/
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;/*��ռ���ȼ�*/
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;/*��Ӧ���ȼ�*/
NVIC_Init(&NVIC_InitStructure);/*�����жϷ��飬��ʹ���ж�*/

TIM_TimeBaseInitStrecture.TIM_Period = arr;/*��װ�ؼĴ���*/
TIM_TimeBaseInitStrecture.TIM_Prescaler = psc;/*Ԥ����*/
TIM_TimeBaseInitStrecture.TIM_ClockDivision = TIM_CKD_DIV1;/*ʱ�ӷ�Ƶ*/
TIM_TimeBaseInitStrecture.TIM_CounterMode = TIM_CounterMode_Up;/*���ϼ���*/
TIM_TimeBaseInitStrecture.TIM_RepetitionCounter = 0;/*�ظ������Ĵ���*/
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStrecture);/*��ʼ��*/

TIM_ClearFlag(TIM1,TIM_FLAG_Update);/*����±�־λ*/
TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);/*ʹ���ж�*/
TIM_Cmd(TIM1,ENABLE);/*ʹ�ܼ���*/

}

u32 T_count;
char buf[50];
//��ʱ��3�жϷ�����
void TIM1_UP_TIM10_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		
		
/***************�ڴ˴�����ж�ִ������******************/
		if(MIT1_S.mit_flag&&MIT2_S.mit_flag&&MIT3_S.mit_flag&&MIT4_S.mit_flag)
		{
			USART2_printf("%d, %d, %d, %d,\r\n",MIT1_S.mit_count,MIT2_S.mit_count,MIT3_S.mit_count,MIT4_S.mit_count);
			
			
			Get_TDOA(&TDOA_S);
			sprintf(buf,"{\"dis\":%f,\"ang\":%f}\r\n",TDOA_S.distance,TDOA_S.angle);
			printf("%s",buf);
			
			delay_ms(700);
			
			T_count=0;
			MIT1_S.mit_flag=0;
			MIT2_S.mit_flag=0;
			MIT3_S.mit_flag=0;
			MIT4_S.mit_flag=0;
			EXTI->IMR |= EXTI_Line1;
			EXTI->IMR |= EXTI_Line2;
			EXTI->IMR |= EXTI_Line3;
			EXTI->IMR |= EXTI_Line4;
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ 
		T_count++;
	}
}

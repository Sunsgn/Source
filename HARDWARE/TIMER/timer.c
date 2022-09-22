#include "timer.h"
#include "led.h"
#include "usart.h"
#include "exti.h"
#include "delay.h"
#include "TDOA.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
//初始化配置
void TIM1_Int_Init(u16 arr,u16 psc)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrecture;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);/*使能定时器1的时钟*/


NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;/*定时器1的中断通道使能*/
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;/*定时器1的中断通道使能*/
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;/*抢占优先级*/
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;/*响应优先级*/
NVIC_Init(&NVIC_InitStructure);/*配置中断分组，并使能中断*/

TIM_TimeBaseInitStrecture.TIM_Period = arr;/*重装载寄存器*/
TIM_TimeBaseInitStrecture.TIM_Prescaler = psc;/*预分配*/
TIM_TimeBaseInitStrecture.TIM_ClockDivision = TIM_CKD_DIV1;/*时钟分频*/
TIM_TimeBaseInitStrecture.TIM_CounterMode = TIM_CounterMode_Up;/*向上计数*/
TIM_TimeBaseInitStrecture.TIM_RepetitionCounter = 0;/*重复计数寄存器*/
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStrecture);/*初始化*/

TIM_ClearFlag(TIM1,TIM_FLAG_Update);/*清更新标志位*/
TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);/*使能中断*/
TIM_Cmd(TIM1,ENABLE);/*使能计数*/

}

u32 T_count;
char buf[50];
//定时器3中断服务函数
void TIM1_UP_TIM10_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否:TIM 中断源 
	{
		
		
/***************在此处添加中断执行内容******************/
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
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//清除TIMx的中断待处理位:TIM 中断源 
		T_count++;
	}
}

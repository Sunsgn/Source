#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
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


//外部中断0服务程序
void EXTI1_IRQHandler(void)
{
	 if(MIT1==0)	  
	{	
		MIT1_S.mit_count=T_count;
		EXTI->IMR &= ~(EXTI_Line1);	
		MIT1_S.mit_flag=1;
	}	
	 EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位 
}

//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	if(MIT2==0)	  
	{	
		MIT2_S.mit_count=T_count;
		EXTI->IMR &= ~(EXTI_Line2);	
		MIT2_S.mit_flag=1;
	}	
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	if(MIT3==0)	  
	{	
		MIT3_S.mit_count=T_count;
		EXTI->IMR &= ~(EXTI_Line3);	
		MIT3_S.mit_flag=1;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	if(MIT4==0)	  
	{
		MIT4_S.mit_count=T_count;
		EXTI->IMR &= ~(EXTI_Line4);	
		MIT4_S.mit_flag=1;
	}
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}

//void EXTI9_5_IRQHandler(void)
//{
//    if(MIT1==0)	  
//	{	
//		MIT1_S.mit_count=T_count%50000;
//		EXTI->IMR &= ~(EXTI_Line5);	
//		MIT1_S.mit_flag=1;
//	}	
//	 EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE5上的中断标志位
//}

//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);//PE1 连接到中断线1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 连接到中断线4
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);//PE5 连接到中断线5
	
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	
	/* 配置EXTI_Line2,3,4 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
  
//    /* 配置EXTI_Line5 */
//  EXTI_InitStructure.EXTI_Line = EXTI_Line5;//LINE5
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE5
//  EXTI_Init(&EXTI_InitStructure);//配置
 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
  
//  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断5
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级1
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
	   
}













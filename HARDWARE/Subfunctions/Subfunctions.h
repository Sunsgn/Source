#ifndef __Subfunctions_H
#define __Subfunctions_H	 
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "SG90.h"

void Show_location(void);   //显示
float location(void) ;      //角度
float X_loca(void);         //x			
float Y_loca(void);         //Y
float Distance_A(void);     //A点坐标
void Show_STOP(void);    //屏幕不需要实时刷新
void cew_location(void);     // 测试固定显示
void doing(void);    //测试动态刷新
void Show_ON(void);     //开机动漫
void Gimbal(void);          //云台转动
#endif


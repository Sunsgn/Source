#ifndef __Subfunctions_H
#define __Subfunctions_H	 
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "SG90.h"

void Show_location(void);   //��ʾ
float location(void) ;      //�Ƕ�
float X_loca(void);         //x			
float Y_loca(void);         //Y
float Distance_A(void);     //A������
void Show_STOP(void);    //��Ļ����Ҫʵʱˢ��
void cew_location(void);     // ���Թ̶���ʾ
void doing(void);    //���Զ�̬ˢ��
void Show_ON(void);     //��������
void Gimbal(void);          //��̨ת��
#endif


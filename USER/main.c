#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "SG90.h"
#include "math.h"
#include "Subfunctions.h"

int main(void)
 {	 
    int key=0,flag1=0,tr=9;
    float oldanglan;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	  //���ڳ�ʼ��Ϊ115200
 	LED_Init();			      //LED�˿ڳ�ʼ��
	LCD_Init();			      //LCD��ʼ�� 	
    Servo_PWM_Init();         //�����ʼ��
    KEY_Init();               //������ʼ��
    Show_ON();
    //�����ʼ��
    Servo1_SetAngle(90);      //����ת��  ��124  ��90  �� 68
    Servo2_SetAngle(9);       //����
     
	while(1)
	{
        key = KEY_Scan(0);
        
        if(key==KEY0)
        {
            flag1=1;
    
         }
       if(key==KEY1)   //����
         {
             tr-=0.5;
            Servo2_SetAngle(tr);
         }  
        if(flag1==1)
        {
           LCD_Clear(BACK_COLOR);
           Show_STOP();
           Show_location();
           delay_ms(1000);
            if(location()!=oldanglan)
                { 
                  oldanglan=location();
                  Gimbal(); 
                }
                 
        }
        
//         if(flag1==2)
//          {
//           LCD_Clear(BACK_COLOR);
//           cew_location(); 
//           doing();
//           delay_ms(1500);
//         }
       
        if(key==WK_UP)   //����
        {
            tr+=0.5;
            Servo2_SetAngle(tr);
        }         
	}
 }

 
 


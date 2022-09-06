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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	  //串口初始化为115200
 	LED_Init();			      //LED端口初始化
	LCD_Init();			      //LCD初始化 	
    Servo_PWM_Init();         //舵机初始化
    KEY_Init();               //按键初始化
    Show_ON();
    //舵机初始化
    Servo1_SetAngle(90);      //下面转动  左124  中90  右 68
    Servo2_SetAngle(9);       //上面
     
	while(1)
	{
        key = KEY_Scan(0);
        
        if(key==KEY0)
        {
            flag1=1;
    
         }
       if(key==KEY1)   //调试
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
       
        if(key==WK_UP)   //调试
        {
            tr+=0.5;
            Servo2_SetAngle(tr);
        }         
	}
 }

 
 


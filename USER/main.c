#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "timer.h"
#include "TDOA.h"

int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200); 	//串口初始化 
    uart2_init(115200);
	LED_Init();				  //初始化LED端口  
	TIM1_Int_Init(1,83);
	EXTIX_Init();       //初始化外部中断输入 
  
	while(1)
	{  
        //USART2_printf("11");
		//LED0=!LED0;	//打印OK提示程序运行
		//delay_ms(1000);	  //每隔1s打印一次
	}

}

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

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200); 	//���ڳ�ʼ�� 
    uart2_init(115200);
	LED_Init();				  //��ʼ��LED�˿�  
	TIM1_Int_Init(1,83);
	EXTIX_Init();       //��ʼ���ⲿ�ж����� 
  
	while(1)
	{  
        //USART2_printf("11");
		//LED0=!LED0;	//��ӡOK��ʾ��������
		//delay_ms(1000);	  //ÿ��1s��ӡһ��
	}

}

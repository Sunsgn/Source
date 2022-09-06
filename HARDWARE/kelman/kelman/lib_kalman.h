/**
 * @file lib_kalman.h
 * @author Marvin
 * @brief 卡尔曼滤波
 * @version 0.1
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __LIB_KALMAN_H__
#define __LIB_KALMAN_H__

typedef struct __KalmanTypeDef {
    float x;
    float A;
    float H;
    float q;
    float r;
    float p;
    float gain;
} KalmanTypeDef;

#ifdef __cplusplus
extern "C" {
#endif

void KalmanFilter_Init(KalmanTypeDef *);
float KalmanFilter_Update(KalmanTypeDef *, float);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_KALMAN_H__ */


/*
int main (void){//主程序
	float Angle_Value;
	static KalmanTypeDef random = {0};
	
	RCC_Configuration(); //时钟设置
	NVIC_Configuration();
	uart_init(115200);
	AS5600_Init();
	KalmanFilter_Init(&random);
	while(1){

		
		Angle_Value=KalmanFilter_Update(&random,Get_Angle());
		printf("%6.2f\r\n",Angle_Value);
		
	
		//delay_ms(1); //延时1秒
		
	}
}
*/
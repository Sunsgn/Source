#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"

void Servo_PWM_Init(void);  //初始化
void PWM1_SetCompare(uint16_t Compare);
void PWM1_SetCompare(uint16_t Compare);

void Servo1_SetAngle(float Angle);   //舵机转动角度  0~180
void Servo2_SetAngle(float Angle);   //舵机转动角度  0~180
#endif

#include "Subfunctions.h"                  
#include "math.h"

float X_loca(void)    //x
{ 
    float x;
    x=dis*(cos(ang/180.0*3.1415929))-25;
    return x;
}

float Y_loca(void)   //y
{ 
    float y;
    y=(dis*sin(ang/180.0*3.1415929));
    return y;
}
float location(void)     //angle
{
    float a=0;
    a=atan(Y_loca()/X_loca())*180/3.1415926;
    return a;
}

float Distance_A(void) 
{
   float A;
   A=Y_loca()/sin(location()/180.0*3.1415929);
    return A;
}

void Show_ON(void)     //开机动漫
{
    POINT_COLOR=RED;//设置字体为红色
    LCD_ShowString(100,120,300,24,24,"Welcome ! ! !");

}


void Show_STOP(void)    //屏幕不需要实时刷新
{
   POINT_COLOR=RED;//设置字体为红色
   LCD_DrawRectangle(10,40,310,90);     //画矩形  300 50
   Show_Chinese(10,120,0,16,POINT_COLOR,0xFFFF,0);  //角度     
   Show_Chinese(30,120,1,16,POINT_COLOR,0xFFFF,0);
   Show_Chinese(10,150,2,16,POINT_COLOR,0xFFFF,0);   //距离  
   Show_Chinese(30,150,3,16,POINT_COLOR,0xFFFF,0);
   Show_Chinese(10,180,4,16,POINT_COLOR,0xFFFF,0);    //坐标 
   Show_Chinese(30,180,5,16,POINT_COLOR,0xFFFF,0);
   LCD_ShowString(50,120,200,16,16,":");
   LCD_ShowString(50,150,200,16,16,":"); 
   LCD_ShowString(50,180,200,16,16,":"); 
   Show_Chinese(60,20,6,16,POINT_COLOR,0xFFFF,0);    // 
   Show_Chinese(90,20,7,16,POINT_COLOR,0xFFFF,0);
   Show_Chinese(120,20,8,16,POINT_COLOR,0xFFFF,0);
   Show_Chinese(150,20,9,16,POINT_COLOR,0xFFFF,0);
   Show_Chinese(180,20,10,16,POINT_COLOR,0xFFFF,0);
   Show_Chinese(210,20,11,16,POINT_COLOR,0xFFFF,0);

}

void Show_location(void)   //实时刷新显示
{
   float x,y,a,d;
  
   y=275;
   a=location();
   d=Distance_A();
    x=tan(a/180.0*3.1415929)*275;
    
    /*   debug   */

    
   POINT_COLOR=BLUE;//设置字体为蓝色
//   if(x>=400){x=389.6;}
//   if(y<=0){y=5.26;}
   LCD_Draw_Circle(160-x*0.8,60,2);   //实时位置 x,y     10<x<310,  40<y<90
   if(a<0){a=-a;LCD_ShowString(60,120,200,16,16,"-");}
   LCD_ShowxNum(70,120,a,2,16,0);    //角度
   LCD_ShowString(90,120,200,16,16,".");
   LCD_ShowxNum(100,120,(int)(a*1000)%1000,sizeof(a),16,0);  //小数部分 wuyumengxie
   
   LCD_ShowxNum(70,150,d,sizeof(d),16,0);    //距离
   LCD_ShowString(105,150,200,16,16,".");
   LCD_ShowxNum(110,150,(int)(d*1000)%1000,sizeof((int)(d*1000)%1000),16,0);
            
   LCD_ShowString(70,180,200,16,16, "(");
   LCD_ShowxNum(80,180,x,sizeof(x),16,0);      //坐标x
   LCD_ShowString(115,180,200,16,16,".");
   LCD_ShowxNum(118,180,(int)(x*100)%100,2,16,0); 
   
   LCD_ShowString(135,180,200,16,16,",");
   LCD_ShowxNum(140,180,y,sizeof(y),16,0);    //坐标y
   LCD_ShowString(175,180,200,16,16,".");
   LCD_ShowxNum(180,180,(int)(y*100)%100,2,16,0); 
   LCD_ShowString(205,180,200,16,16,")");
   
}


void cew_location(void)     // 测试显示固定
{
//   LCD_ShowString(30,10,200,16,16,"dis:");
//   LCD_ShowString(110,10,200,16,16,"ang:");
//   LCD_ShowString(30,40,200,16,16,"x:");
//   LCD_ShowString(110,40,200,16,16,"y:");
//   LCD_ShowString(30,80,200,16,16,"a:");
//   LCD_ShowString(110,80,200,16,16,"d:");
    

}


void doing(void)    //测试动态刷新
{
   POINT_COLOR=BLUE;//设置字体为蓝色
   LCD_ShowxNum(70,40,dis,4,16,0);
   LCD_ShowxNum(150,40,ang,4,16,0);
   LCD_ShowxNum(70,80,X_loca(),4,16,0);
   LCD_ShowxNum(150,80,Y_loca(),4,16,0);
}

void Gimbal(void)    //云台转动  ！！！！！优化
{
     float a=0;
     a=location();
    if(a>0){Servo1_SetAngle(90+a);
       if(a>20){Servo1_SetAngle(90+a*1.1);}
    }
    
      if(a<0){
          if(a<-22){Servo1_SetAngle(90+a*0.7);}
           if(a<-15&&a>-1) { Servo1_SetAngle(90+a*0.9);}}
      LED1=1;delay_ms(1500);LED1=0;

}

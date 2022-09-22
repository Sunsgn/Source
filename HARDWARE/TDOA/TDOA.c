#include "TDOA.h"
#include "exti.h"
#include "usart.h"

_TDOA TDOA_S;


void f1(double a1,double a2,double c)
{
 TDOA_S.y=(1+(a1*a1)/(c*c-a2*a2))/((1/(a2*a2))-((a1*a1)/((c*c-a1*a1)*(c*c-a2*a2))));
 TDOA_S.y=sqrt(TDOA_S.y);
 TDOA_S.x=(1+(TDOA_S.y*TDOA_S.y)/(c*c-a1*a1))*a1*a1;
 TDOA_S.x=sqrt(TDOA_S.x);
 TDOA_S.x-=17.677670;
 TDOA_S.y-=17.677670;
 TDOA_S.distance=sqrt(TDOA_S.x*TDOA_S.x+TDOA_S.y*TDOA_S.y);
 if(a1>a2)
 {
  TDOA_S.angle=(acos(TDOA_S.x/TDOA_S.distance)-3.1415926/4)/3.1415926*180;
 }
 else
 {
  TDOA_S.angle=(3.1415926/4-acos(TDOA_S.x/TDOA_S.distance))/3.1415926*180;
 }
}
void f2(double a1,double a2,double c)
{
 if(a1>a2)
 { 
  TDOA_S.angle=(atan(sqrt(c*c-a2*a2)/a2)-3.1415926/4)/3.1415926*180;
 }
 if(a1<=a2)
 {
  TDOA_S.angle=(3.1415926/4-atan(sqrt(c*c-a1*a1)/a1))/3.1415926*180;
 }
 TDOA_S.distance=275/cos(fabs(TDOA_S.angle)/180*3.1415926);
 /*TDOA_S.x=TDOA_S.distance*cos(fabs(TDOA_S.angle)/180*3.1415926)-17.677670;
 TDOA_S.y=TDOA_S.distance*sin(fabs(TDOA_S.angle)/180*3.1415926)-17.677670;
 TDOA_S.distance=sqrt(TDOA_S.x*TDOA_S.x+TDOA_S.y*TDOA_S.y);
 if(a1>a2)
 {
  TDOA_S.angle=(acos(TDOA_S.x/TDOA_S.distance))/3.1415926*180;
 }
 else
 {
  TDOA_S.angle=(acos(TDOA_S.x/TDOA_S.distance))/3.1415926*180;
 }*/
}


void Get_TDOA(_TDOA *TDOA_S)
{
	TDOA_S->c=35;
	if(MIT2_S.mit_count > MIT1_S.mit_count && MIT4_S.mit_count > MIT3_S.mit_count)
	{
		TDOA_S->a1=(double)(MIT2_S.mit_count-MIT1_S.mit_count)*34800/1000000/2;
		TDOA_S->a2=(double)(MIT4_S.mit_count-MIT3_S.mit_count)*34800/1000000/2;
   
		if(9.918055<TDOA_S->a1&&TDOA_S->a1<33.901301&&9.918055<TDOA_S->a2&&TDOA_S->a2<33.901301)
		{
			if((TDOA_S->a1>TDOA_S->a2&&(TDOA_S->c*TDOA_S->c-TDOA_S->a1*TDOA_S->a1)/TDOA_S->a1>(TDOA_S->c*TDOA_S->c-TDOA_S->a2*TDOA_S->a2)/TDOA_S->a2)||(TDOA_S->a1<TDOA_S->a2&&(TDOA_S->c*TDOA_S->c-TDOA_S->a1*TDOA_S->a1)/TDOA_S->a1<(TDOA_S->c*TDOA_S->c-TDOA_S->a2*TDOA_S->a2)/TDOA_S->a2))
			{
				f1(TDOA_S->a1,TDOA_S->a2,TDOA_S->c);
				USART2_printf("双曲线输出：");
			}
			else if(TDOA_S->a1<33.901301||TDOA_S->a2<33.901301)
			{
				f2(TDOA_S->a1,TDOA_S->a2,TDOA_S->c);
				USART2_printf("渐近线输出："); 
			}   
			else 
			{
				USART2_printf("error\r\n");
				return;
			}
		}
		else 
		{
			USART2_printf("error\r\n");
            USART2_printf("a1= %lf\ta2= %lf\r\n",TDOA_S->a1,TDOA_S->a2);
			return;
		}
	   
		USART2_printf("a1= %lf\ta2= %lf\r\n",TDOA_S->a1,TDOA_S->a2);
		USART2_printf("    l = %lf\ta = %lf\r\n",TDOA_S->distance,TDOA_S->angle);
   
	}
}

















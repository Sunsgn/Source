#ifndef __TDOA_H
#define	__TDOA_H
#include "sys.h"
#include <math.h>

typedef struct
{
	double x;
	double y;
	double distance;
	double angle;
	long x1;
	long x2;
	long x3;
	long x4;
	double a1;
	double a2;
	double c;
}_TDOA;

extern _TDOA TDOA_S;

void f2(double a1,double a2,double c);
void f1(double a1,double a2,double c);

void Get_TDOA(_TDOA *TDOA_S);

#endif

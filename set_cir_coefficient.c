#include "structure.h"
//calculate coefficients for circular path
double W[6];

 
void set_cir_coff(double time)
{
	unsigned char debug = 0;

	double t3, t4, t5;
	double s = 0;
	double f;
	double diff;

	t3 = time * time * time;
	t4 = t3 * time;
	t5 = t4 * time;

	f = 2 * PI;
	diff = f - s;

	W[0] = s;
	W[1] = 0;
	W[2] = 0;
	W[3] = (10.0 * diff)/ t3;
	W[4] = (-15.0 * diff)/t4;
	W[5] = (6.0 * diff)/t5;

	if(debug)		printf("\nW0 = %lf,  W3 = %lf W4 =%lf W5 = %lf",W[0],W[3], W[4],W[5]);
}

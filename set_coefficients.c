#include "structure.h"

double M[6];

 
void set_coff(double time)
{
	unsigned char debug = 0;

	double t3, t4, t5;
	double s = 0;
	double f = 1;
	double diff;

	t3 = time * time * time;
	t4 = t3 * time;
	t5 = t4 * time;

	diff = f - s;

	M[0] = s;
	M[1] = 0;
	M[2] = 0;
	M[3] = (10.0 * diff)/ t3;
	M[4] = (-15.0 * diff)/t4;
	M[5] = (6.0 * diff)/t5;

	if(debug)		printf("\nM0 = %lf,  M3 = %lf M4 =%lf M5 = %lf",M[0],M[3], M[4],M[5]);
}

#include <stdio.h>

extern void set_location(double, double, double, double);

void line(void)
{
	unsigned char debug = 0;
	double x,y,z;
	double destime;
	
	if(debug)	printf("\nreached line function");

	x = 0.0;
	y = 0.0;
	z = -100.0;

	destime = 10.0;

	set_location(x, y, z, destime);
}

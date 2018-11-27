#include <stdio.h>

extern void set_radius(double, double);

void circle(void)
{
	unsigned char debug = 0;
	double radius;
	double destime;
	
	if(debug)	printf("\nreached circle function");

	radius = 50.0;
	destime = 40.0;

	set_radius(radius, destime);
}

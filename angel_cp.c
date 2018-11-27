#include <math.h>
#include "structure.h"

double a;

double tan_inv(double n, double d)
{
	if(d == 0)
	{
		if(n == 0)
		{
			a = 0;
		}
		else
		{
			a = (PI/2);
		}
	}
	else
	{
		a = atan(n/d);
	}
	if(a < 0)
	{
		a = a + PI;
	}
	
	return(a);
}

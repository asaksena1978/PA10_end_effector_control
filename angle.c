#include <math.h>
#include "structure.h"
//calculate tan inverse
double a;

double tan_inv(double n, double d)
{
	if(d == 0)
	{
		if(n == 0)
		{
			a = 0;	//angle is 0 of both numerator and denominator are zero
		}
		else
		{
			if(n < 0)	
			{
				a = 3 * PI/ 2; //numerator -ve denominator zero
			}
			else
			{
				a = PI/2;	//numerator +ve denomianator zero
			}
		}
	}
	else	//denominator not zero
	{
		if(n == 0)	//numerator zero
		{	
			if(d < 0)	//denominator -ve
				a = PI/2;
			else		//denominator +ve
				a = 0;
		}
		else
			a = atan(n/d);	//non zero numerator and denominator
	}	
	
	if(a < 0)
	{
		a = a + PI;
	}
	
	return(a);
}

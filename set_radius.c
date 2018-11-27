#include "include.h"
#include "structure.h"
#include "enum.h"
//input radius to calculate path
extern double MOTOR_DES_TIME;
extern unsigned char MODE;
extern unsigned char TRIG;
extern int JOINT;

double RAD;

void set_radius(double r, double Time)
{
	int debug = 0;
	int i;

	if(debug)	printf("\nREACHED SET RADIUS FUNCTION");


	MOTOR_DES_TIME = Time;
	TRIG = 1;
	MODE    = circular_mode;

	RAD = r;

	if(debug)	printf("\nset location function over");
}

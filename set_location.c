#include "include.h"
#include "structure.h"
#include "enum.h"
//set end point realtive to current position for straingt line trajectory
extern double MOTOR_DES_TIME;
extern unsigned char MODE;
extern unsigned char TRIG;
extern int JOINT;

endpoint RELATIVE_END_POINT;

void set_location(double x, double y, double z, double Time)
{
	int debug = 0;
	int i;

	if(debug)	printf("\nREACHED SET LOCATION FUNCTION");

	RELATIVE_END_POINT.px = x;
	RELATIVE_END_POINT.py = y;
	RELATIVE_END_POINT.pz = z;

	MOTOR_DES_TIME = Time;
	TRIG = 1;
	MODE    = straight_mode;

	if(debug)	printf("\nset location function over");
}

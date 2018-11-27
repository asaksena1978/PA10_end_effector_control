#include "structure.h"
#include <stdio.h>


extern void joint_moveto(double * ,double);

void move(void)
{
	double angle_arr[7];
	double angle;
	double desTime;
	int debug = 0;
	int i;

	if(debug)	printf("\nREACHED ALL move FUNCTION");

	desTime = 10.;

//	angle = 10. * DEG2RAD;
//	angle = 0. * DEG2RAD;


	for(i = 0; i < 7; i++)
	{
		angle = (i + 1) * 10. * DEG2RAD;

		if(i == 2)	angle_arr[i] = 0.0;	
		else	angle_arr[i] = angle;
	}

	joint_moveto(angle_arr, desTime);

 	if(debug) 	printf("\n\t Joint Control --- allmove!!\n\n");
}

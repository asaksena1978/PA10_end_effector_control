#include "include.h"
#include "main.h"
#include "structure.h"
#include <math.h>

extern status des_j[7];
extern path path_j[7];


double TM[7][MAX_LEN];
double POS[7][MAX_LEN];
double VEL[7][MAX_LEN];
double ACC[7][MAX_LEN];



void pathGenerate_j(unsigned long Time, int joint)
{
	int debug = 0;
	static int print_once_flag[7] = {1, 1, 1, 1, 1, 1, 1};
	double t;
	static long i[7] = {0, 0, 0, 0, 0, 0, 0};
	static int loop[7] = {1000, 1000, 1000, 1000, 1000, 1000, 1000};


	
	t = Time * TICKS;

	if(t > path_j[joint].time)
	{
		t = path_j[joint].time;
	}



	TM[joint][(i[joint])] = t;

	des_j[joint].pos = path_j[joint].pos[0] + t * t * t * (path_j[joint].pos[3] + t * (path_j[joint].pos[4] + t * path_j[joint].pos[5]));
	POS[joint][(i[joint])] = (des_j[joint].pos * RAD2DEG);	


	des_j[joint].vel = t * t * (path_j[joint].vel[2] + t * (path_j[joint].vel[3] + t * path_j[joint].vel[4]));
	VEL[joint][(i[joint])] = des_j[joint].vel;

	des_j[joint].acc = t * (path_j[joint].acc[1] + t * (path_j[joint].acc[2] + t * path_j[joint].acc[3]));
	ACC[joint][(i[joint])] = des_j[joint].acc;




	if(loop[joint] >= 1000)
	{
		if(debug)
			printf("\njoint = %d time = %lf pos = %lf vel = %lf acc = %lf",joint, TM[joint][(i[joint])],POS[joint][(i[joint])],VEL[joint][(i[joint])],ACC[joint][(i[joint])]);
		loop[joint] = 0;

	}

	loop[joint]++;


	i[joint]++;
	if(i[joint] >= MAX_LEN)
	{
		if(debug)	printf("\nERROR ARRAY OF JOINT %d OUT OF RANGE",joint);
		i[joint] = 0;
	}

	if(debug)
	{
		if(print_once_flag[joint])
		{
			printf("\npath generate executed");
			print_once_flag[joint] = 0;
		}
	}

}

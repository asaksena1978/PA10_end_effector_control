#include "include.h"
#include "structure.h"

extern path path_j[7];


void pathInit_j(double Start, double Destination, double Time, int joint)
{
	int debug = 0;
	static int print_once_flag[7] = {1, 1, 1, 1, 1, 1, 1};
	double t3, t4, t5;
	double diff;

	t3 = Time * Time * Time;
	t4 = t3 * Time;
	t5 = t4 * Time;
	diff = Destination - Start;


	if(debug)
	{
		if(print_once_flag[joint])
		{
			printf("\nREACHED PATH INIT FUNCTION");
			printf("\nstart angle = %lf\t destination = %lf\tTime = %lf",Start, Destination, Time);
		}
	}

	switch(joint)
	{
		case	2:
			path_j[joint].pos[0] = 0;
			path_j[joint].pos[1] = 0;	//a1
			path_j[joint].pos[2] = 0;	//a2
			path_j[joint].pos[3] = 0;
			path_j[joint].pos[4] = 0;
			path_j[joint].pos[5] = 0;


			path_j[joint].vel[0] = 0;	//a1
			path_j[joint].vel[1] = 0;	//2a2
			path_j[joint].vel[2] = 0;
			path_j[joint].vel[3] = 0;
			path_j[joint].vel[4] = 0;

			path_j[joint].acc[0] = 0;	//2a2
			path_j[joint].acc[1] = 0;
			path_j[joint].acc[2] = 0;
			path_j[joint].acc[3] = 0;

			path_j[joint].time = 0;
		break;

		default:
			//Qf = a0 + a1t + a2t^2 + a3t^3 + a4t^4 + a5t^5		eq1
			//a0 = Q0
			path_j[joint].pos[0] = Start;

			//vf = a1 + 2a2t + 3a3t^2 + 4a4t^3 + 5a^5t^4		eq2
			//a1 = v0 = 0 //initial velocity vf = final velocity = 0
			//accf = 2a2 + 6a3t^2 + 12a4t^2 + 20a5t^3		eq3
			//a2 = acc0 = 0 //initial acceleration af = final acc = 0

			path_j[joint].pos[1] = 0;	//a1
			path_j[joint].pos[2] = 0;	//a2

			//a3 = (20(Qf - Q0) -(80vf - 12v0)tf - (3a0 - af)tf^2)/2tf^3
			//a3 = 10(Qf - Q0)/tf^3

			path_j[joint].pos[3] = (10.0 * diff)/t3;
	
			//a4 = (-30(Qf - Q0) + (14vf + 16v0)tf + (3a0 - 2af)tf^2)/2tf^4
			//a4 = -15(Qf - Q0)/tf^4

			path_j[joint].pos[4] = (-15.0 * diff)/t4;

			//a5 = (12(Qf - Q0) - 6(vf - v0)tf - (a0 - af)tf^2)/2tf^5
			//a5 = 6(Qf - Q0)/tf^5;
	
			path_j[joint].pos[5] = (6.0 * diff)/t5;

			//eq2

			path_j[joint].vel[0] = 0;	//a1
			path_j[joint].vel[1] = 0;	//2a2
			path_j[joint].vel[2] = 3.0 * path_j[joint].pos[3];
			path_j[joint].vel[3] = 4.0 * path_j[joint].pos[4];
			path_j[joint].vel[4] = 5.0 * path_j[joint].pos[5];

			//eq3

			path_j[joint].acc[0] = 0;	//2a2
			path_j[joint].acc[1] = 6.0 * path_j[joint].pos[3];
			path_j[joint].acc[2] = 12.0 * path_j[joint].pos[4];
			path_j[joint].acc[3] = 20.0 * path_j[joint].pos[5];

			path_j[joint].time = Time;
		break;

	}

	if(debug)
	{
		if(print_once_flag[joint])
		{
			printf("\n Path init function cofficients initialized");

			printf("COEFFICIENTS FOR POSITION FOR JOINT %d=>\n",joint);
			printf("pos = %lf + %lf t + %lf t^2 + %lf t^3 + %lf t^4 + %lf t^5\n",path_j[joint].pos[0], path_j[joint].pos[1], path_j[joint].pos[2], path_j[joint].pos[3], path_j[joint].pos[4], path_j[joint].pos[5]);

			printf("\nCOEFFICIENTS FOR VELOCITY FOR JOINT %d =>\n",joint);
			printf("vel = %lf + %lf t + %lf t^2 + %lf t^3 + %lf t^4\n",path_j[joint].vel[0], path_j[joint].vel[1], path_j[joint].vel[2], path_j[joint].vel[3], path_j[joint].vel[4]);

			printf("\nCOEFFICIENTS FOR ACCELERATION FOR JOINT %d =>\n", joint);
			printf("acc = %lf + %lf t + %lf t^2 + %lf t^3\n",path_j[joint].acc[0], path_j[joint].acc[1], path_j[joint].acc[2], path_j[joint].acc[3]);

			print_once_flag[joint] = 0;
		}
	}
}

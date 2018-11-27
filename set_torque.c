#include "main.h"
#include "structure.h"
#include "enum.h"
#include "./Arcnet/arc_pci.h"

extern double ENDPT_TM[MAX_LEN];
extern double THETA[7];
extern status cur_j[7], des_j[7];
extern unsigned char EXECUTION;
extern exe_mode CtrlMode; 
extern double PX[MAX_LEN], PY[MAX_LEN], PZ[MAX_LEN];

double LINEAR_TORQUE[7][MAX_LEN];
double CUR_ANGLE[7][MAX_LEN];
double VELOCITY[7][MAX_LEN];
double ACCELERATION[7][MAX_LEN];
double last_pos[7];
double last_vel[7];

void set_torque(void)
{
	double INERTIA[7] = {0.75, 0.75, 0.2125, 0.2125, 0.0575, 0.0575, 0.0575};
	double MAX_TORQ[7] = {200.0, 200.0, 80.0, 80.0, 15.0, 15.0, 10.0};
	double KD[7] = {123.0, 123.0, 104.0, 104.0, 70.0, 91.0, 91.0};
	double KP[7] = {10500.0, 9000.0, 7000.0, 7000.0, 5000.0, 5000.0, 4900.0};
	unsigned char debug = 1;
	double diff[7], des_vel[7], des_acc[7], net_acc[7];
	double torq[7];
	int i;
	static unsigned long count = 0;
	static unsigned int loop = 1000;


	for(i = 0; i < 7; i++)
	{
		if(count == 0)
		{
			last_pos[i] = THETA[i];
			last_vel[i] = 0;
		}
			
		diff[i] = THETA[i] - last_pos[i];
		des_vel[i] = diff[i] / TICKS;

		des_acc[i] = (des_vel[i] - last_vel[i])/ TICKS;
		last_pos[i] = THETA[i];
		last_vel[i] = des_vel[i];


		net_acc[i] = des_acc[i] + (KD[i] * (des_vel[i] - cur_j[i].vel)) + (KP[i] * (THETA[i] - cur_j[i].pos));

		torq[i] = net_acc[i] * INERTIA[i];	
		if(torq[i] > MAX_TORQ[i])
			torq[i] = MAX_TORQ[i];
		else
		{
			if(torq[i] < (-1 * MAX_TORQ[i]))
				torq[i] = -1 * MAX_TORQ[i];
		}
		LINEAR_TORQUE[i][count] = torq[i];
		CUR_ANGLE[i][count] = cur_j[i].pos * RAD2DEG;
		VELOCITY[i][count] = des_vel[i];
		ACCELERATION[i][count] = des_acc[i];
	}
	switch(CtrlMode)
	{
		case operation:		if(EXECUTION)	SetTorq(torq);
		break;

		case simulation:	if(EXECUTION)	NoTorq();
					for(i = 0; i < 7; i++)
						des_j[i].pos = THETA[i];

		break;

		default:		if(EXECUTION)	NoTorq();
		break;
	}
	if(debug)
	{
		if(loop >= 1000)
		{
			loop = 0;
//			printf("\nTime = %lf PX[7] = %lf PY[7] = %lf PZ[7] = %lf",ENDPT_TM[count], PX[7], PY[7], PZ[7]);
		}
		loop++;
	}
 
	if(count >= MAX_LEN)
	{
		if(debug)	printf("\ncount out of range in torque");
		count = 0;
	}
	count++;
}

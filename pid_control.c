# include "include.h"
#include "structure.h"
#include "main.h"
#include "enum.h"
#include "./Arcnet/arc_pci.h"

extern double TM[7][MAX_LEN];
extern double POS[7][MAX_LEN];
extern double VEL[7][MAX_LEN];
extern double ACC[7][MAX_LEN];
double CUR_POS[7][MAX_LEN];
extern status des_j[7];
extern status cur_j[7];
extern unsigned char EXECUTION;
extern exe_mode CtrlMode;

extern void check_torq(double *);


double TORQ[7][MAX_LEN];


void pdCtrl(void)
{
	double INERTIA[7] = {0.75, 0.75, 0.2125, 0.2125, 0.0575, 0.0575, 0.0575};
	double MAX_TORQ[7] = {200.0, 200.0, 80.0, 80.0, 15.0, 15.0, 10.0};
	double KD[7] = {123.0, 123.0, 104.0, 104.0, 70.0, 91.0, 91.0};
	double KP[7] = {10500.0, 9000.0, 7000.0, 7000.0, 5000.0, 5000.0, 4900.0};
	double torque[7];
	static int print_once_flag = 0;
	static int loop = 1000;
	static long i = 0;
	int debug = 1;
	int j;
	double accel;
	double temp1;
	double temp2;

	for(j = 0; j < 7; j++)
	{
		accel = des_j[j].acc + (KD[j] * (des_j[j].vel - cur_j[j].vel)) + (KP[j] * (des_j[j].pos - cur_j[j].pos));

	
		torque[j] = INERTIA[j] * accel;

	
		if(torque[j] > MAX_TORQ[j])
			torque[j] = MAX_TORQ[j];
		else
		{
			 if(torque[j] < (-1 * MAX_TORQ[j]))
				torque[j] = -1 * MAX_TORQ[j];
		}
		TORQ[j][i] = torque[j];
		CUR_POS[j][i] = cur_j[j].pos * RAD2DEG;
	}


	if(debug)
	{
		if(loop >= 1000)
		{
//			printf("\ntime = %lf cur pos -1 = %lf cur pos -2 = %lf cur pos -3 = %lf cur pos -4 = %lf cur pos -5 = %lf cur pos -6 = %lf cur pos -7 = %lf",TM[0][i], cur_j[0].pos, cur_j[1].pos, cur_j[2].pos, cur_j[3].pos, cur_j[4].pos, cur_j[5].pos, cur_j[6].pos) ;

//			printf("\ntime = %lf cur pos -1 = %lf des pos -1 = %lf des vel-1 = %lf cur vel = %lf des acc = %lf cur acc = %lf torq -1  = %lf",TM[0][i], cur_j[1].pos, des_j[1].pos, des_j[1].vel, cur_j[1].vel, des_j[1].acc, cur_j[1].acc, torque[1]);
			printf("\ntime = %lf",TM[0][i]);
		
			loop = 0;
		}
		loop++;

	}

  
	i++;
	if(i >= MAX_LEN)
	{
		if(debug)	printf("\ni out of range in pid control function");
		i = 0;
	}


	switch(CtrlMode)
	{

			case operation:
				if(EXECUTION)	SetTorq(torque);		
			break;

			case simulation:	//check_torq(torque);
				if(EXECUTION)	NoTorq();   
			break;
 
			default:
				if(EXECUTION)	NoTorq();
			break;
	}

	if(debug)
	{
		if(print_once_flag)
		{
			print_once_flag = 0;
			printf("\npid control implemeted now");
		}
	}
}

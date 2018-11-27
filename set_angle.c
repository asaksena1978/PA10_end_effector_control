#include "main.h"
#include "structure.h"
#include <math.h>

extern double A07[4][4];
extern double ROT[4][4];
extern double MOTOR_DES_TIME;
extern double M[6];
extern endpoint begin;
extern endpoint final;

double PX[MAX_LEN];
double PY[MAX_LEN];
double PZ[MAX_LEN];
double THETA[7];
double ANGLE[7][MAX_LEN];
double ENDPT_TM[MAX_LEN];

extern void inverse_kin(double *, double *);
extern void display(double *);

void set_angle(double time)
{
	double t;
	double arr[4][4]; 
	double cal_angle[6];
	static unsigned long count = 0;
	int i,j;
	static unsigned int loop = 1000;
	unsigned char debug = 0;
	double m;
	static unsigned char print_once_flag = 1;


	t = time * TICKS;

	if(t > MOTOR_DES_TIME)
		t = MOTOR_DES_TIME;

	ENDPT_TM[count] = t;

	m = M[0] + t * t * t * (M[3]  + t * (M[4] + t * M[5]));

	PX[count] = (final.px * m) + ((1 - m) * begin.px);
	PY[count] = (final.py * m) + ((1 - m) * begin.py);
	PZ[count] = (final.pz * m) + ((1 - m) * begin.pz);

	if(debug)
	{
	if(print_once_flag == 1)
	{
//		display(&A07[0][0]);
	}
	}

/*	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			A07[i][j] = ROT[i][j];
		}
	}*/

	A07[0][3] = PX[count];
	A07[1][3] = PY[count];
	A07[2][3] = PZ[count];
	A07[3][0] = 0;
	A07[3][1] = 0;
	A07[3][2] = 0;
	A07[3][3] = 1;

	if(debug)
{	
	if(print_once_flag == 1)
	{
//		display(&A07[0][0]);	
		print_once_flag = 0;
		printf("final x =%lf, y = %lf, z = %lf",final.px, final.py, final.pz);
	}
}

	inverse_kin(cal_angle, &A07[0][0]);

	THETA[0] = cal_angle[0];
	THETA[1] = cal_angle[1];
	THETA[2] = 0;
	THETA[3] = cal_angle[3];
	THETA[4] = cal_angle[4];
	THETA[5] = cal_angle[5];
	THETA[6] = cal_angle[6];
	
	for(i = 0; i < 7; i++)
	{
		ANGLE[i][count] = THETA[i] * RAD2DEG;
	}	
	if(debug)
	{
	
		if(loop == 1000)
		{
			printf("\nTIME = %lf m = %lf O0 => %lf, O1 => %lf, O2 => %lf, O3 => %lf, O4 => %lf O5 => %lf O6 => %lf", ENDPT_TM[count],m, THETA[0], THETA[1], THETA[2], THETA[3], THETA[4], THETA[5], THETA[6]);

			loop = 0;
		}
		loop++;	
	}
	count++;
	if(count >= MAX_LEN)
	{
		if(debug)	printf("\ncount out of range");
		count = 0;
	}
}

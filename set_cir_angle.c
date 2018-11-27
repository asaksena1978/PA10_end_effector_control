#include "main.h"
#include "structure.h"
#include <math.h>
// draw circular path in X-Y plane
extern double A07[4][4];
extern double ROT[4][4];
extern double MOTOR_DES_TIME;
extern double W[6];
extern endpoint begin;
extern double RAD;

extern double PX[MAX_LEN];
extern double PY[MAX_LEN];
extern double PZ[MAX_LEN];
extern double THETA[7];
extern double ANGLE[7][MAX_LEN];
extern double ENDPT_TM[MAX_LEN];

extern void inverse_kin(double *, double *);
extern void display(double *);

void set_cir_angle(double time)
{
	double t;
	double temp_x, temp_y, temp_z;
	double arr[4][4]; 
	double cal_angle[6];
	static unsigned long count = 0;
	int i,j;
	static unsigned int loop = 1000;
	unsigned char debug = 0;
	double w;
	static unsigned char print_once_flag = 1;


	t = time * TICKS;

	if(t > MOTOR_DES_TIME)
		t = MOTOR_DES_TIME;

	ENDPT_TM[count] = t;
	//angle of rotation using quntic polynomial
	w = W[0] + t * t * t * (W[3]  + t * (W[4] + t * W[5]));

	temp_x = -1 * RAD * sin(w);
	temp_y = (-1 * RAD) + (RAD * cos(w));
	if(w <= PI)	temp_z = -1 * 2 * RAD * w/PI;
	else		temp_z = (2 * RAD * w/PI) - (4 * RAD);

	PX[count] = begin.px + temp_x;
	PY[count] = begin.py + temp_y;
//	PZ[count] = begin.pz + temp_z;
	PZ[count] = begin.pz;


	if(debug)
	{
		if(print_once_flag == 1)
		{
			display(&A07[0][0]);
			print("\nstart x = %lf, y = %lf, z = %lf",begin.px, begin.py, begin.pz);			
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

			printf("\nTime = %lf",ENDPT_TM[count]);
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

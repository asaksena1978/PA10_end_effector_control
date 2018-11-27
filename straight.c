#include "include.h"
#include "structure.h"

extern status des_j[7];
extern status cur_j[7];
extern double MOTOR_DES_TIME;
extern endpoint RELATIVE_END_POINT;
extern double last_pos[7];
extern double last_vel[7];

extern void set_coff(double);
extern void set_angle(double);
extern void set_torque(void);
extern void direct_kin(double *, double *);
extern void display(double *);

double ROT[3][3];
double A07[4][4];
double A[4][4];
endpoint begin;
endpoint final;

void straight(unsigned char trig)
{
	double time;
	static double ticks = 0;
	int i, j;
	double angle[7];

	if(trig)
	{
		ticks = 0;
		time = MOTOR_DES_TIME;	
		for(i = 0; i < 7; i++)
		{
			angle[i] = cur_j[i].pos;
		}
		direct_kin(&A07[0][0], angle);
//		display(&A07[0][0]);
//		inverse_kin(angle, &A07[0][0]);
//		printf("\nA1 = %lf, A2 = %lf, A3 = %lf, A4 = %lf A5 = %lf A6 %lf A7 = %lf",angle[0] * RAD2DEG, angle[1] * RAD2DEG, angle[2] * RAD2DEG, angle[3] * RAD2DEG, angle[4] * RAD2DEG, angle[5] * RAD2DEG, angle[6] * RAD2DEG);
		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 4; j++)
			{
				A[i][j] = A07[i][j];
			}
		}
		begin.px = A[0][3];
		begin.py = A[1][3];
		begin.pz = A[2][3];

		final.px = begin.px + RELATIVE_END_POINT.px;
		final.py = begin.py + RELATIVE_END_POINT.py;
		final.pz = begin.pz + RELATIVE_END_POINT.pz;
//		printf("final x =%lf, y = %lf, z = %lf",final.px, final.py, final.pz);
		set_coff(time);
		for(i = 0; i < 3; i++)
		{
//			printf("\n");
			for(j = 0; j < 3; j++)
			{
				ROT[i][j] = A07[i][j];
				//printf("%lf\t",ROT[i][j]);
			}
		}
	}
	else
	{
		set_angle(ticks);
		ticks++;
		set_torque();
	}
}

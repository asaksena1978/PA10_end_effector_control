# include<stdio.h>
# include<math.h>
# include"structure.h"


extern double tan_inv(double, double);
extern void display(double *);

void inverse_kin(double *angl, double *arr)
{
	double nx, ny, nz;
	double bx, by, bz;
	double tx, ty, tz;
	double a, b, c;
	double Px, Py, Pz;
	double P4x, P4y, P4z;
	double a07[4][4];
	double temp[6];
	double den, num, t0, t1, t2, t3, t4, t5;
	double L0 = 315, L1 = 450, L2 = 500, D = 80/* D = 62*/;
	int i,j;
	static unsigned char print_once_flag = 1;

	//calculating roll pitch yaw angle from direct kin array
	
/*	nx = *(arr + (0 * 4) + 0);
	ny = *(arr + (1 * 4) + 0);
	nz = *(arr + (2 * 4) + 0);
	tz = *(arr + (2 * 4) + 1);
	bz = *(arr + (2 * 4) + 2);
	

	num = ny;
	den = nx;
	a = tan_inv(num, den);

	num = -1 * nz * sin(a);
	den = ny;
	b = tan_inv(num, den);

	num = tz;
	den = bz;
	c = tan_inv(num, den);


	//writing direct kin array using roll yaw pich config
	a07[0][0] = cos(a) * cos(b);
	a07[0][1] = (cos(a) * sin(b) * sin(c)) - (sin(a) * cos(c));
	a07[0][2] = (cos(a) * sin(b) * cos(c)) + (sin(a) * sin(c));
	a07[0][3] = *(arr + (0 * 4) + 3);

	a07[1][0] = sin(a) * cos(b);
	a07[1][1] = (sin(a) * sin(b) * sin(c)) + (cos(a) * cos(c));
	a07[1][2] = (sin(a) * sin(b) * cos(c)) - (cos(a) * sin(c));
	a07[1][3] = *(arr + (1 * 4) + 3);

	a07[2][0] = -1 * (sin(b));
	a07[2][1] = cos(b) * sin(c);
	a07[2][2] = cos(b) * cos(c);
	a07[2][3] = *(arr + (2 * 4) + 3);

	a07[3][0] = 0;
	a07[3][1] = 0;
	a07[3][2] = 0;
	a07[3][3] = 1;*/

//////////////////////////////////////////////////////////////////////////
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)	a07[i][j] = *(arr + (i * 4) + j);
	}

	if(print_once_flag == 1)
	{
//		display(&a07[0][0]);
		print_once_flag = 0;
	}


	//inverse kinematic
	nx = a07[0][0];
	ny = a07[1][0];
	nz = a07[2][0];

	tx = a07[0][1];
	ty = a07[1][1];
	tz = a07[2][1];

	bx = a07[0][2];
	by = a07[1][2];
	bz = a07[2][2];

	Px = a07[0][3];
	Py = a07[1][3];
	Pz = a07[2][3];

	P4x = Px - (D * bx);
	P4y = Py - (D * by);
	P4z = Pz - (D * bz);


	num = P4y;
	den = P4x;
	temp[0] = tan_inv(num, den);

	
	t0 = ((P4x * (cos(temp[0])) + (P4y * (sin(temp[0])))));
	t0 = t0 * t0;
	t1 = L0 - P4z;
	t1 = t1 * t1;
	t2 = (L1 * L1) + (L2 * L2);
	t3 = t1 + t0 - t2;
	t4 = (L1 * L2 * 2);
	t3 = t3/t4;
	t4 = 1 - (t3 * t3);
	t4 = sqrt(t4);
	num = t4;
	den = t3;
	temp[2] = tan_inv(num, den);

	t0 = ((P4x * (cos(temp[0])) + (P4y * (sin(temp[0])))));
	t1 = L0 - P4z;
	t2 = L1  + (L2 * (cos((temp[2]))));
	t3 = L2 * sin(temp[2]);
	num = (t0 * t2) + (t1 * t3);
	den = (t0 * t3) - (t2 * t1);
	temp[1] = tan_inv(num, den);

	t0 = (sin(temp[1]) * cos(temp[2])) + (cos(temp[1]) * sin(temp[2]));
	t0 = t0 * bx * cos(temp[0]);
	t1 = (sin(temp[1]) * cos(temp[2])) + (cos(temp[1]) * sin(temp[2]));
	t1 = t1 * by * sin(temp[0]);
	t2 = (cos(temp[1]) * cos(temp[2])) - (sin(temp[1]) * sin(temp[2]));
	t2 = bz * t2;
	den = t0 + t1 + t2;
	t3 = den * den;
	t4 = 1 - t3;
	num = sqrt(t4);
	temp[4] = tan_inv(num, den);



	t0 = (cos(temp[1]) * cos(temp[2])) - (sin(temp[1]) * sin(temp[2]));
	t1 = (sin(temp[1]) * cos(temp[2])) + (cos(temp[1]) * sin(temp[2]));
	t2 = bx * cos(temp[0]) * t0;
	t3 = by * sin(temp[0]) * t0;
	t4 = bz * t1;
	den = t2 + t3 - t4;
	t2 = bx * sin(temp[0]);
	t3 = by * cos(temp[0]);
	num = t3 - t2;
	temp[3] = tan_inv(num, den);


	t0 = (cos(temp[1]) * cos(temp[2])) - (sin(temp[1]) * sin(temp[2]));
	t1 = (sin(temp[1]) * cos(temp[2])) + (cos(temp[1]) * sin(temp[2]));
	t2 = t1 * sin(temp[3]);
	t3 = t0 * sin(temp[4]);
	t4 = t1 * cos(temp[3]) * cos(temp[4]);
	num = (nz * t2) + (tz * t3) + (tz *t4);
	den = (tz * t2) - (nz * t3) - (nz * t4);
	temp[5] = tan_inv(num, den);

	*(angl + 0) = temp[0];
	*(angl + 1) = temp[1];
	*(angl + 2) = 0.0;
	*(angl + 3) = temp[2];
	*(angl + 4) = temp[3];
	*(angl + 5) = temp[4];
	*(angl + 6) = temp[5];
}	

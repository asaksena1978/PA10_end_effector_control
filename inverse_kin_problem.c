#include "structure.h"
# include<stdio.h>
# include<math.h>


extern double tan_inv(double, double);


void inverse_kin( double *angl,double *arr)
{
	double nx, ny, nz;
	double bx, by, bz;
	double tx, ty, tz;
	double a, b, c;
	double Px, Py, Pz;
	double P4x, P4y, P4z;
	double A07[4][4];
	double T03[4][4];
	double den, num, t0, t1, t2, t3, t4, t5;
	int i,j;
	double L0 = 315, L1 = 450, L2 = 500, D = 80/* D = 62*/;


	//calculating roll pitch yaw angle from direct kin array
	
	nx = *(arr + (0 * 4) + 0);
	ny = *(arr + (1 * 4) + 0);
	nz = *(arr + (2 * 4) + 0);
	tz = *(arr + (2 * 4) + 1);
	bz = *(arr + (2 * 4) + 2);
	

	num = ny;
	den = nx;
	a = tan_inv(num, den);

	num = -1 * nz * cos(a);
	den = nx;
	b = tan_inv(num, den);

	num = tz;
	den = bz;
	c = tan_inv(num, den);


	//writing direct kin array using yaw pich roll config
	A07[0][0] = cos(a) * cos(b);
	A07[0][1] = (cos(a) * sin(b) * sin(c)) - (sin(a) * cos(c));
	A07[0][2] = (cos(a) * sin(b) * cos(c)) + (sin(a) * sin(c));
	A07[0][3] = *(arr + (0 * 4) + 3);

	A07[1][0] = sin(a) * cos(b);
	A07[1][1] = (sin(a) * sin(b) * sin(c)) + (cos(a) * cos(c));
	A07[1][2] = (sin(a) * sin(b) * cos(c)) - (cos(a) * sin(c));
	A07[1][3] = *(arr + (1 * 4) + 3);

	A07[2][0] = -1 * (sin(b));
	A07[2][1] = cos(b) * sin(c);
	A07[2][2] = cos(b) * cos(c);
	A07[2][3] = *(arr + (2 * 4) + 3);

	A07[3][0] = 0;
	A07[3][1] = 0;
	A07[3][2] = 0;
	A07[3][3] = 1;



	//inverse kinematic
	nx = A07[0][0];
	ny = A07[1][0];
	nz = A07[2][0];

	tx = A07[0][1];
	ty = A07[1][1];
	tz = A07[2][1];

	bx = A07[0][2];
	by = A07[1][2];
	bz = A07[2][2];

	Px = A07[0][3];
	Py = A07[1][3];
	Pz = A07[2][3];

	P4x = Px - (D * bx);
	P4y = Py - (D * by);
	P4z = Pz - (D * bz);


	num = P4y;
	den = P4x;
	*((angl + 0)) = tan_inv(num, den);

	
	t0 = ((P4x * (cos(*((angl + 0)))) + (P4y * (sin(*((angl + 0)))))));
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
	*((angl + 3)) = tan_inv(num, den);

	t0 = ((P4x * (cos(*((angl + 0)))) + (P4y * (sin(*((angl + 0)))))));
	t1 = L0 - P4z;
	t2 = L1  + (L2 * (cos((*((angl + 3))))));
	t3 = L2 * sin(*((angl + 3)));
	num = (t0 * t2) + (t1 * t3);
	den = (t0 * t3) - (t2 * t1);
	*((angl + 1)) = tan_inv(num, den);

	t0 = (sin(*((angl + 1))) * cos(*((angl + 3)))) + (cos(*((angl + 1))) * sin(*((angl + 3))));
	t0 = t0 * bx * cos(*((angl + 0)));
	t1 = (sin(*((angl + 1))) * cos(*((angl + 3)))) + (cos(*((angl + 1))) * sin(*((angl + 3))));
	t1 = t1 * by * sin(*((angl + 0)));
	t2 = (cos(*((angl + 1))) * cos(*((angl + 3)))) - (sin(*((angl + 1))) * sin(*((angl + 3))));
	t2 = bz * t2;
	den = t0 + t1 + t2;
	t3 = den * den;
	t4 = 1 - t3;
	num = sqrt(t4);
	*((angl + 5)) = tan_inv(num, den);



	t0 = (cos(*((angl + 1))) * cos(*((angl + 3)))) - (sin(*((angl + 1))) * sin(*((angl + 3))));
	t1 = (sin(*((angl + 1))) * cos(*((angl + 3)))) + (cos(*((angl + 1))) * sin(*((angl + 3))));
	t2 = bx * cos(*((angl + 0))) * t0;
	t3 = by * sin(*((angl + 0))) * t0;
	t4 = bz * t1;
	den = t2 + t3 - t4;
	t2 = bx * sin(*((angl + 0)));
	t3 = by * cos(*((angl + 0)));
	num = t3 - t2;
	*((angl + 4)) = tan_inv(num, den);


	t0 = (cos(*((angl + 1))) * cos(*((angl + 3)))) - (sin(*((angl + 1))) * sin(*((angl + 3))));
	t1 = (sin(*((angl + 1))) * cos(*((angl + 3)))) + (cos(*((angl + 1))) * sin(*((angl + 3))));
	t2 = t1 * sin(*((angl + 4)));
	t3 = t0 * sin(*((angl + 5)));
	t4 = t1 * cos(*((angl + 4))) * cos(*((angl + 5)));
	num = (nz * t2) + (tz * t3) + (tz *t4);
	den = (tz * t2) - (nz * t3) - (nz * t4);
	*((angl + 6)) = tan_inv(num, den);
	
	*(angl + 2) = 0.0;
}	

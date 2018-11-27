# include<stdio.h>

extern void input_A01(double *, double, double);
extern void input_A12(double *, double, double);
extern void input_A23(double *, double);
extern void input_A34(double *, double, double);
extern void input_A45(double *, double);
extern void input_A56(double *, double, double);
extern void mul(double *, double *, double *);


void direct_kin(double *kin, double *theta)
{
	double A01[4][4], A12[4][4], A23[4][4], A34[4][4], A45[4][4], A56[4][4];
	double L0 = 315, L1 = 450, L2 = 500, D = 80/* D = 62*/;
	double temp[4][4], A[4][4];


	input_A01(&(A01[0][0]), *(theta), L0);

	input_A12(&(A12[0][0]), *(theta + 1), L1);

	input_A23(&(A23[0][0]), *(theta + 3));

	input_A34(&(A34[0][0]), *(theta + 4), L2);

	input_A45(&(A45[0][0]), *(theta + 5));

	input_A56(&(A56[0][0]), *(theta + 6), D);

	mul((&temp[0][0]), (&A01[0][0]), (&A12[0][0]));
	transfer(&A[0][0],(&(temp[0][0])));

	mul((&temp[0][0]), (&A[0][0]), (&A23[0][0]));
	transfer(&A[0][0],(&(temp[0][0])));


	mul((&temp[0][0]), (&A[0][0]), (&A34[0][0]));
	transfer(&A[0][0],(&(temp[0][0])));

	mul((&temp[0][0]), (&A[0][0]), (&A45[0][0]));
	transfer(&A[0][0],(&(temp[0][0])));

	mul((&temp[0][0]), (&A[0][0]), (&A56[0][0]));
	transfer(&A[0][0],(&(temp[0][0])));

	transfer(kin,(&(temp[0][0])));
}

#include "include.h"
#include "structure.h"
#include "enum.h"
#include "./Arcnet/arc_pci.h"
#include <errno.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

extern exe_mode CtrlMode;
extern double MOTOR_DES_POS[7];
extern double MOTOR_DES_TIME;
extern int JOINT;
extern unsigned char MODE;
extern unsigned char TRIG;
extern unsigned char EXECUTION;

extern void fin(void);
extern void getCurrentPosition(void);
extern void jointCtrl(unsigned char);
extern void straight(unsigned char);
extern void circular(unsigned char);
extern void allbrakeoff(void);
extern void brakeoff(int);
extern void endTask(void);
extern void Nop(void);
extern int iSend_C(void);
extern int RecData(void);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
status cur_j[7], des_j[7];

void control(void)
{
	int debug = 0;
	int stat1;
	int i;
	static double param[7];
	static unsigned char mode = nop;
	static int joint;
	static unsigned char trig;
	static int print_once_flag[7] = {1, 1, 1, 1, 1, 1, 1};

	if(debug)
	{
		printf("\nENTER CONTROL FUNCTION");
	}

	if( pthread_mutex_lock ( &mutex ) != EOK )
	{
		printf(" ERROR : mutex cannnot lock.\n        fin\n");
		printf("\nfinish called in control.c");
		fin();
		return;
	}
	else
	{
		if(debug)	printf("\nMUTEX LOCK");
	}
	if(debug)	printf("\nCtrlMode = %d",CtrlMode);


	switch(CtrlMode)
	{
		case operation:
			if(EXECUTION)	stat1 = iSend_C();
			if(debug)	printf("\nSEND_C FUNCTION CALLED");
			break;
		case simulation:
			if(debug)	printf("\nSIMULATION MODE IN CONTROL");
			break;
 
		default:
			if(debug)	printf("\nDEFAULT MODE NO ACTION TAKEN");
			break;
	}
  
	for(i = 0; i < 7; i++)
	{
		param[i] = MOTOR_DES_POS[i];
	}
	if(debug)
	{
		for(i = 0; i < 7; i++)	
		{
			if(print_once_flag[i])
			{
				printf("\nmotor%d => trig = %d, mode = %d, despos = %lf, destime = %lf", i + 1, TRIG, MODE, MOTOR_DES_POS[i], MOTOR_DES_TIME);


				print_once_flag[i] = 0;
			}
		}
	}


	getCurrentPosition();

 	if(debug)	printf("\nEXECUTED GET CURRENT POSTION FUNCTION"); 

	if(TRIG)
	{
		trig = TRUE;
		TRIG = FALSE;
	}
	else
		trig = FALSE;

  
	mode = MODE;
	joint = JOINT;
  
	switch(mode)
	{
		case joint_mode:
			if(debug)	printf("\nControl function default mode is joint mode");
			jointCtrl(trig);
			break;
	
		case allbrakeoff_mode:
			if(debug)	printf("\nControl function default mode is all brake off  mode");
			allbrakeoff();
			break;

		case brakeoff_mode:
			if(debug)	printf("\nControl function default mode is brakeoff mode");
			brakeoff(joint);
			JOINT = 8;
			MODE = nop;
			break;

		case straight_mode:		if(debug) printf("\nControl Function Straight line mode");
			straight(trig);
			break;

		case circular_mode:		if(debug) printf("\nControl Function Circular mode");
			circular(trig);
			break;

		default:
			if(debug)	printf("\nControl function default mode is NOP mode");
			Nop();

			break;
	}

  
	switch(CtrlMode)
	{
		case operation:
			if(debug)	printf("\n Ctrl mode operation receive data");
			if(EXECUTION)	stat1 = RecData();
			break;

		case simulation:
			if(debug)	printf("\nCtrlMode simulation no job");
			break;
 
		default:
			if(debug)	printf("\ndefault mode no job");
			break;
	}

	endTask();
	return;

	if(debug)	printf("\nEXIT CONTROL FUNCTION");

}

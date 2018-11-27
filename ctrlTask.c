#include "include.h"
#include "timer.h"
#include "structure.h"
#include <sys/neutrino.h>
#include <pthread.h>


typedef union
{
    ClientMessageT msg;
    struct _pulse pulse;
} MessageT;



extern int ctrltrig;
extern int chid;
extern double MOTOR_DES_POS[7];
extern double MOTOR_DES_TIME;
extern int JOINT;
extern unsigned char MODE;
extern unsigned char TRIG;
extern void control(void);


int ctrlEndFlag = 0;

void ctrlTask(void)
{
	int debug = 0;
	int rcvid=1;
	MessageT msg;
	static unsigned long ticks = 0;
	pthread_attr_t attr;
	int print_once_flag[7] = {1, 1, 1, 1, 1, 1, 1};
	int i;

	if(debug)	printf("\nControl Task function");

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED );
      
	while(ctrltrig)
	{
		rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
		if(rcvid == 0)
		{
			if(!ctrlEndFlag)
			{
				printf("ERROR : Control Task is out of time.\n        fin\n");
				fin();
			}
			if(debug)
			{
				printf("\nINSIDE ctrlTask FUNCTION");
				for(i = 0; i < 7; i++)
				{
					if(print_once_flag[i])
					{
						printf("\nmotor %d trig = %d",i+1, TRIG);
						printf("\nmotor %d mode = %d",i+1, MODE);
						printf("\nmotor desired position = %lf", MOTOR_DES_POS[i]);
						printf("\nmotor %d desired time = %lf",i+1, MOTOR_DES_TIME);
						printf("\nSTARTING CONTROL THREAD");
					print_once_flag[i] = 0;
					}
				}
			}
			ctrlEndFlag = 0;
			pthread_create(NULL,&attr,(void *)control,NULL);

			ticks++;
		}
	}
  
}

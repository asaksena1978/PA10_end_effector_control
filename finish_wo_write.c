#include <stdio.h>

extern int WRITE_FILE_FLAG;

extern void fin(void);


void fin_wow(void)
{
	WRITE_FILE_FLAG = 0;

	fin();


	printf("\nEXECUTION OVER WITHOUT FILE WRITE");
}

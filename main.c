#include "include.h"

unsigned char initialization_check_flag = 0;

extern int cp(int, char **);

main()
{
	printf("\nWAITING FOR COMMAND FROM CPC >>");

	cp(0,0);


	return(0);
}

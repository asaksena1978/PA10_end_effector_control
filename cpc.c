# include<stdio.h>
# include<fcntl.h>


# define CPC_MSG_LEN	93

unsigned char CPC_TARGET_IP[4] = {192, 168, 17, 213};	//vwpc10 192.168.17.212

int debug = 0;
int cpc;

main()
{

	int		cpc;
	int		cpc_flag[10];
	int		i, d, c, ii, dd, cc;
	int		flag = 0;
	int		point;				//holds location of last opening brackets <(>
	int		sp;				//sp counts number of spaces
	int		len[8];
	int		str_len;
	int		j;

	long long	cpc_arg_i[8];			//holds integer type cpc arguments

	unsigned char	*cpc_msg;			//hold final msg to be dispatched
	unsigned char	cpc_arg_type[8];		//holds type of cpc arguemnts
	unsigned char	loop = 1;
	char 		cpc_com[16];			//holds command
	char		cpc_arg_c[8][8];		//holds char type arguments
	char		input[512];			//receives data entered at command prompt
	char		buff[127];
	char		cpc_narg;			//holds number of arguments

	double		cpc_arg_d[8];			//holds double type arguments


	if(!debug)
	{
		cpc = open("/dev/cmd", O_WRONLY);
	}

	while(loop)
	{
		cpc_msg = (unsigned char *)malloc(CPC_MSG_LEN);
		
		memset(cpc_com, 0x00, (sizeof(cpc_com)));
		memset(cpc_arg_c, 0x00, (sizeof(cpc_arg_c)));
		memset(input, 0x00, (sizeof(input)));
		memset(cpc_flag, 0, (sizeof(cpc_flag)));
		memset(cpc_arg_i, 0, (sizeof(cpc_arg_i)));
		memset(cpc_arg_d, 0, (sizeof(cpc_arg_d)));
		memset(cpc_arg_type, 0, (sizeof(cpc_arg_type)));

		cpc_flag[0] = 1;
	
		flag = 0;
	        cpc_narg = 0;
      		i=0;
		ii=0;
		d=0;
		dd=0;
		c=0;
		cc=0;
        	printf("\nSELECT COMMAND FROM FOLLOWING => ");
 		printf("\n1)\tSelect Operation Mode 'sim' - simulation/ 'oper' - operation");      
		printf("\nInitialize - 'init'");
		printf("\nStart - 'start'");
		printf("\nALL ZERO - allzero");
		printf("\nALL BRAKE OFF - allboff");
		printf("\nALL BRAKE ON - allbon");
		printf("\nBRAKE OFF JOINT 1 - boff1");
		printf("\nBRAKE OFF JOINT 2 - boff2");
		printf("\nBRAKE OFF JOINT 3 - boff3");
		printf("\nBRAKE OFF JOINT 4 - boff4");
		printf("\nBRAKE OFF JOINT 5 - boff5");
		printf("\nBRAKE OFF JOINT 6 - boff6");
		printf("\nBRAKE OFF JOINT 7 - boff7");
		printf("\n10 Degree MOVEMENT - ten");

        	printf("\nCPC > ");			//command prompt
	        fgets(input,511,stdin);			//enter string
        
       		str_len = strlen(input);
        
       		for(j=1;j<str_len+1;j++)		//get command from string
		{
            		if(cpc_flag[flag])
			{
                		if(input[j] == 32 || input[j] == 40 || input[j] == 0)	//if input is <space> or <(> or <NUL>
				{
					len[0] = j;
					point = j + 1;
					memcpy(cpc_com,input,len[0]);			//cpc_com holds command
					printf("\nCPC COMMAND ARRAY = %s",cpc_com);
					cpc_flag[flag] = 0;
					if(input[j] != 0)
					{
						cpc_flag[1] = 1;
					}
				}
			}
                }

		for(flag = 1; flag < 9; flag++)					//get arguments
		{
			sp = 1;
			if(cpc_flag[flag])
			{
				for(j = point; j < str_len + 1; j++)		//start checking remaning string
				{
					if(cpc_arg_type[flag] == 0)
					{
						if(input[j] == 34)	cpc_arg_type[flag] = 3;			//if input is <"> argument is string
						if(input[j] == 46)	cpc_arg_type[flag] = 2;			//if input is <.> argument is double
					}

					if(input[j] == 40)	point++;					//if input is <(>	

					if(((sp == 1) && (input[j] == 32)) || ((sp == 1) && (input[j] == 44)))	//if sp = 1 and input is <space> or sp = 1 and input is <,>
					{
						point++;
					}
					else	sp = 0;

					if(((sp == 0) && (input[j] == 32)) || ((sp == 0) && (input[j] == 44)) || (input[j] == 0) || (input[j] == 41))    //if sp = 0 and input is <space> or sp = 0 and input is <,>
					{

			                        len[flag] = j - point;
                        
                       				if(cpc_arg_type[flag] == 3)
						{
							memcpy(cpc_arg_c[c],&input[point+1],len[flag]-2);
							printf("\nchar type argument[%d] = %s", c, cpc_arg_c[c]);
							c++;
						} 
						else
						{
							if(cpc_arg_type[flag] == 2)
							{
								memset(buff,0x00,sizeof(buff));
								memcpy(buff,&input[point],len[flag]);
								cpc_arg_d[d] = atof(buff);				//convert string to double
								printf("\ndouble type argument[%d] = %lf", d, cpc_arg_d[d]);
								d++;
							}
							else
							{
								if(len[flag] != 0)
								{
									cpc_arg_type[flag] = 1;
									memset(buff,0x00,sizeof(buff));
									memcpy(buff,&input[point],len[flag]);		//convert string to integer
									cpc_arg_i[i] = atoi(buff);
									printf("\nINTEGER TYPT ARGUMENT[%d] = %d", i, cpc_arg_i[i]);
									i++;
								}
								else
								{
									cpc_flag[flag] = 0;
									break;
								}
							}
						}

						cpc_narg++;
						point += len[flag];
						point++;
                    
						cpc_flag[flag] = 0;
						if(input[j] == 32 || input[j]  == 44) cpc_flag[flag+1] = 1;
                   
						break;

      					}
				}
			}
		}
        
		if(cpc_narg > 8 || cpc_narg < 0)
		{
			printf("\ninproper argumnet loop end = %d",loop);
						loop = 0;			//	break;		//break from endless while loop
		}
		else
		{
			printf("\nloop continue = %d", loop);
		}
        
		if(debug)
//		if(!debug)
		{
			printf("\n command = %s \n number of arguments = %d\n",cpc_com,cpc_narg);
                    
            
			for(j=1;j<9;j++)
			{
				if(cpc_arg_type[j] == 1)
				{
					printf("\n argument type[%d] = int \n integer type argument[%d] = %d\n",j,j,cpc_arg_i[ii]);
                            
					ii++;
				}
				else
				{
					if(cpc_arg_type[j] == 2)
					{
						printf("\n argument type[%d] = double \n double type argument[%d] = %f\n",j,j,cpc_arg_d[dd]);
                            
						dd++;
					}
					else
					{
						if(cpc_arg_type[j] == 3)
						{
							printf("\n argument type[%d] = char * \n char type argument[%d] = %s\n",j,j,cpc_arg_c[cc]);
                            
							cc++;
						}
						else	 break;
					}
				}
			}
        
		}// end debug
        
/*		if(!(strncmp(cpc_com , "exit" ,4)))
		{
			printf("\nexit command received");
			loop = 0;
							//break;	//break endless while loop
       		}*/
 
		// cpc message setting
        
		memset(cpc_msg,0x00,sizeof(CPC_MSG_LEN));

		memcpy(&cpc_msg[ 0], CPC_TARGET_IP,  4);
		memcpy(&cpc_msg[ 4], cpc_com      , 16);
		memcpy(&cpc_msg[20], &cpc_narg    ,  1);
        
		ii=0,dd=0,cc=0;
        
		for(j=0;j<cpc_narg;j++)
		{
        
			memcpy(&cpc_msg[21+(9*j)], &cpc_arg_type[j+1] ,  1);

			if(cpc_arg_type[j+1] == 1)
			{
				memcpy(&cpc_msg[22+(9*j)], &cpc_arg_i[ii],  8);
				ii++;
			}
			else
			{
				if(cpc_arg_type[j+1] == 2)
				{
			                memcpy(&cpc_msg[22+(9*j)], &cpc_arg_d[dd],  8);
					dd++;
            			}
				else
				{
					if(cpc_arg_type[j+1] == 3)
					{
						memcpy(&cpc_msg[22+(9*j)], cpc_arg_c[cc] ,  8);
						cc++;
					}//else memset(&cpc_msg[22+(9*j)], 0x00, 8);
				}
			}
		}
        
		printf("\nmsg ready");        
		if(debug)
//		if(!debug)
		{
			for(j=0;j<CPC_MSG_LEN;j++)
			{
				printf("cpc_msg[%2d] = %d\n",j,cpc_msg[j]);
			}
		}
		else
		{
			printf("\ndebug = %d, can not print msg",debug);
		}
        
		        // end setting
        
		if(!debug)
		{
			if(write(cpc,cpc_msg,CPC_MSG_LEN) != CPC_MSG_LEN)
				 printf("CPC > ... ERROR!\n");
			else
				 printf("CPC > ... OK\n");
		}

		if(!(strncmp(cpc_com , "fin" ,3)))  //break;
			loop = 0;
		if(!(strncmp(cpc_com, "exit", 4)))
			loop = 0;
		if(!(strncmp(cpc_com, "quit", 4)))
			loop = 0;
		if(!(strncmp(cpc_com, "end", 3)))
			loop = 0;	


	}// end while(loop)
    
	close(cpc);

	free(cpc_msg);


	printf("\nCPC OVER = %d",cpc);


	return(0);
}

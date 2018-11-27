/* cp.c     : Command Processing Server                                       */
/*                                                                            */
/* CAUTION  : THIS PROGRAM IS ONLY FOR  " Q N X "                             */
/*                                                                            */
/* comment  : This server can receive, process and decode user commands       */
/*            sended by cpc(command processing client program).               */


#include "include.h"
#include "structure.h"
#include "enum.h"
#include <errno.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
 
static resmgr_connect_funcs_t		connect_func;
static resmgr_io_funcs_t		io_func;
static iofunc_attr_t			attr;

#define CPC_MSG_LEN	93
unsigned char	CPC_MY_IP[4] = {192,168,17,213};
exe_mode CtrlMode = simulation;
extern int cpflag; 

extern void simulation_mode(void);
extern void operation_mode(void);
extern void allzero(void);
extern void allboff(void);
extern void allbon(void);
extern void boff1(void);
extern void boff2(void);
extern void boff3(void);
extern void boff4(void);
extern void boff5(void);
extern void boff6(void);
extern void boff7(void);
extern void ten(void);
extern void five(void);
extern void move(void);
extern void line(void);
extern void circle(void);
extern void init(void);
extern void fin(void);
extern void fin_wow(void);
extern void start(void);
extern void stop(void);


/*void
end_process (void)
{
//    sleep(3);
    
}*/



void process_data (int offset, char *buffer, int nbytes)
{
	int 		j;
	int 		ii,dd,cc;
	int 		debug = 1;

	unsigned char	*cpc_msg;
	unsigned char	cpc_arg_type[8];

	unsigned char	cpc_target_ip[4];
//	unsigned char	cpc_target_ip[5];
	char		cpc_com[16];
	char		cpc_narg;
	char		cpc_arg_c[8][8];

	long long	cpc_arg_i[8];
	double		cpc_arg_d[8];


	if(!debug)printf("\nmsg received"); 
	if(!debug)	printf("\nSERVER IP = %d: %d: %d: %d", CPC_MY_IP[0], CPC_MY_IP[1], CPC_MY_IP[2], CPC_MY_IP[3]);

	if(!debug) for(j=0;j<nbytes;j++)
		printf("buf[%2d] = %d\n",j,(unsigned char)buffer[j]);

	cpc_msg = (unsigned char *)malloc(CPC_MSG_LEN);
	memset (cpc_msg,0x00,sizeof(CPC_MSG_LEN));
	memcpy (cpc_msg, buffer, CPC_MSG_LEN);
 	if(!debug) for(j=0;j<nbytes;j++)
		printf("cpc_msg[%2d] = %d\n",j,(unsigned char)cpc_msg[j]);
       
	memcpy(cpc_target_ip, &cpc_msg[0],  4);
	if(!debug)	printf("\nRECEIVED IP = %d: %d: %d: %d", cpc_target_ip[0], cpc_target_ip[1], cpc_target_ip[2], cpc_target_ip[3]);
	if(!debug)	printf("\nSERVER IP = %d: %d: %d: %d", CPC_MY_IP[0], CPC_MY_IP[1], CPC_MY_IP[2], CPC_MY_IP[3]);

	if(strncmp(cpc_target_ip , CPC_MY_IP ,4) != 0)
	{
		if(!debug)printf("\nIP Mismatch");
	if(!debug)	printf("\nReceived IP = %d: %d: %d: %d",cpc_target_ip[0],cpc_target_ip[1],cpc_target_ip[2],cpc_target_ip[3]);

	if(!debug)	printf("\nSERVER IP = %d: %d: %d: %d", CPC_MY_IP[0], CPC_MY_IP[1], CPC_MY_IP[2], CPC_MY_IP[3]);
		 return;
	}
	else
	{
	if(!debug)	printf("\nReceived IP = %d: %d: %d: %d",cpc_target_ip[0],cpc_target_ip[1],cpc_target_ip[2],cpc_target_ip[3]);

	if(!debug)	printf("\nSERVER IP = %d: %d: %d: %d", CPC_MY_IP[0], CPC_MY_IP[1], CPC_MY_IP[2], CPC_MY_IP[3]);
		if(!debug)printf("\nIP MATCH");
	}

	memcpy(cpc_com, &cpc_msg[ 4], 16);
	if(!debug)printf("\nCP > command : %s",cpc_com);
	if(!debug)
		printf("\nCP > command : %s received\n",cpc_com);

	memcpy(&cpc_narg, &cpc_msg[20],  1);
        
	ii=0,dd=0,cc=0;
        
	for(j=0;j<cpc_narg;j++)
	{
		memcpy(&cpc_arg_type[j+1], &cpc_msg[21+(9*j)],  1);

		if(cpc_arg_type[j+1] == 1)
		{
			memcpy(&cpc_arg_i[ii], &cpc_msg[22+(9*j)],  8);
			ii++;
		}
		else
		{
			if(cpc_arg_type[j+1] == 2)
			{
				memcpy(&cpc_arg_d[dd], &cpc_msg[22+(9*j)], 8);
				dd++;
			}
			else
			{
				if(cpc_arg_type[j+1] == 3)
				{
					memcpy(cpc_arg_c[cc] , &cpc_msg[22+(9*j)],  8);
					cc++;
				}//else memset(&cpc_msg[22+(9*j)], 0x00, 8);
			}
		}
	}
//	if(((strncmp(cpc_com, "s", 1)) == 0) || ((strncmp(cpc_com, "S", 1)) == 0))
	if((strncmp(cpc_com, "sim", 3)) == 0)
	{
		if(!debug)printf("\nSIMULATION MODE SELECTED");
		simulation_mode();
		return;
	}
//	if(((strncmp(cpc_com, "o", 1)) == 0) || ((strncmp(cpc_com, "O", 1)) == 0))
	if((strncmp(cpc_com, "oper", 4)) == 0)

	{
		if(!debug)printf("\nOPERATION MODE SELECTED");
		operation_mode();
		return;
	}
	if(!(strncmp(cpc_com , "allzero" ,7)))
	{
		if(!debug)printf("\nCALL ALL ZERO FUNCTION");
		allzero();
		return;
	}
	if(!(strncmp(cpc_com , "allboff" ,7)))
	{
		if(!debug)printf("\nCALL ALL BRAKE OFF FUNCTION");
		allboff();
		return;
	}
	if(!(strncmp(cpc_com , "allbon" ,6)))
	{
		if(!debug)printf("\nCALL ALL BRAKE ON FUNCTION");
		allbon();
		return;
	}
	if(!(strncmp(cpc_com , "start"  ,5)))
	{
		if(!debug)printf("\nSTART THREAD FOR START");
		pthread_create (NULL, NULL, (void *)start, NULL);
	}
	if(!(strncmp(cpc_com , "boff1"  ,5)))
	{
		if(!debug)printf("\nBRAKE OFF 1");
		boff1();
		return;
	}
	if(!(strncmp(cpc_com , "boff2"  ,5)))
	{
		if(!debug)printf("\nCALL BRAKE OFF 2 FUNCTION");
		boff2();
		return;
	}
	if(!(strncmp(cpc_com , "boff3"  ,5)))
	{
		if(!debug)printf("\nCALL BRAKE OFF 4 Function");
		boff3();
		return;
	}
	if(!(strncmp(cpc_com , "boff4"  ,5)))
	{
		if(!debug)printf("\nCALL BRAKE OFF 4 function");
		boff4();
		return;
	}
	if(!(strncmp(cpc_com , "boff5"  ,5)))
	{
		if(!debug)printf("\nCALL BRAKE OFF 5 Function");
		boff5();
		return;
	}
	if(!(strncmp(cpc_com , "boff6"  ,5)))
	{
		if(!debug)printf("\nCALL BRAKE OFF 6 Function");
		boff6();
		return;
	}
	if(!(strncmp(cpc_com , "boff7"  ,5)))
	{
		if(!debug)printf("\nCALL BRAKE OFF 7 function");
		boff7();
		return;
	}
	if(!(strncmp(cpc_com , "move"  ,4)))
	{
		if(!debug)printf("\nCALL FUNCTION FOR for each joint moving 10 ~ 80 Degree movement");
		move();
		return;
	}
if(!(strncmp(cpc_com , "circle"  ,6)))
	{
		if(!debug)printf("\nCALL FUNCTION FOR for each joint moving in circular motion");

		circle();
		return;
	}
	if(!(strncmp(cpc_com , "line"  ,4)))
	{
		if(!debug)printf("\nCALL FUNCTION FOR for each joint moving in straight line in z direction");

		line();
		return;
	}
	if(!(strncmp(cpc_com , "ten"  ,3)))
	{
		if(!debug)printf("\nCALL FUNCTION FOR 10 Degree movement");
		ten();
		return;
	}
	if(!(strncmp(cpc_com , "init"   ,4)))
	{
		if(!debug)printf("\nCALL INIT FUNCTION");
		init();
		return;
	}
	if(!(strncmp(cpc_com , "five" ,4)))
	{
		if(!debug)printf("\nCALL ALL FIVE FUNCTION");
		five();
		return;
	}
	if(!((strncmp(cpc_com, "fin", 3))))
	{
		if(!debug)printf("\nFINISH FUNCTION");
		printf("\nfinish called in cp function");
		fin();
		return;
	}
	if(!((strncmp(cpc_com, "stop", 4))))
	{
		if(!debug)printf("\nSTOP FUNCTION");
		stop();
		return;
	}
	if(!((strncmp(cpc_com, "exit", 4))))
	{
		if(!debug)printf("\nFINISH FUNCTION WITHOUT WRITING TO FILES");
		printf("\nFINISH FUNCTION WITHOUT WRITING TO FILES");

		fin_wow();
		return;
	}
	if(!((strncmp(cpc_com, "quit", 4))))
	{
		if(!debug)printf("\nFINISH FUNCTION WITHOUT WRITING TO FILES");
		printf("\nFINISH FUNCTION WITHOUT WRITING TO FILES");

		fin_wow();
		return;
	}
	if(!((strncmp(cpc_com, "end", 3))))
	{
		if(!debug)printf("\nFINISH FUNCTION WITHOUT WRITING TO FILES");
		printf("\nFINISH FUNCTION WITHOUT WRITING TO FILES");

		fin_wow();
		return;
	}

}



int io_write (resmgr_context_t *ctp, io_write_t *msg, iofunc_ocb_t *ocb)
{
	int		debug = 0;
	int		sts;
	int		nbytes;
	int		off;
	int		doffset;
	int		xtype;

	char		*buffer;

	struct _xtype_offset *xoffset;


    
	if(debug)printf("\nThis is write function");

	sts = iofunc_write_verify (ctp, msg, ocb, NULL);
	if(debug)printf("\nsts = %d",sts);
	if (sts != EOK )
	{
		return (sts);
	}
    
   
	xtype = msg->i.xtype & _IO_XTYPE_MASK;
	if ( xtype == _IO_XTYPE_MASK )
	{
		xoffset = (struct _xtype_offset *)(&msg->i+1);
		doffset = sizeof(msg->i) + sizeof(*xoffset);
		off = xoffset->offset;
	}
	else
	{
		if ( xtype == _IO_XTYPE_NONE )
		{
			off = ocb->offset;
		        doffset = sizeof(msg->i);
		}
		else return (ENOSYS);
	}
    
    
	nbytes = msg->i.nbytes;
	buffer = ((char *)(malloc(nbytes)));
	if(buffer == NULL) return (ENOSYS);
    
    
	if(resmgr_msgread(ctp, buffer, nbytes, doffset) == -1)
	{
		free(buffer);
		return (errno);
	}
    
	process_data (off, buffer, nbytes);
    
	free (buffer);
    
	_IO_SET_WRITE_NBYTES (ctp, nbytes);
    
	if(nbytes)
	{
		ocb->attr->flags |= IOFUNC_ATTR_MTIME |  IOFUNC_ATTR_DIRTY_TIME;
		if(xtype == _IO_XTYPE_NONE)
		{
			ocb->offset += nbytes;
		}
        }
    
	return (EOK);
}



int io_open (resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra)
{
	int debug = 0;
	if(debug)	printf("\nthis is io open function");
    
       if(debug)	printf ("CP > accessed.\n");
        return (iofunc_open_default (ctp, msg, handle, extra));
}



int io_close (resmgr_context_t *ctp, void *reserved,RESMGR_OCB_T *ocb)
{
	int debug = 0;
	if(debug)	printf("\n this is close function");
	if(debug)	printf ("CP > closed.\n");
	return (iofunc_close_ocb_default (ctp, reserved, ocb));
}



int io_read (resmgr_context_t *ctp, io_read_t *msg,iofunc_ocb_t *ocb)
{
	int debug = 0;
	if(debug)	printf("\nthis is read function");
	if(debug)	printf ("CP > ERROR: CP does not support \"read.\"\n");
	return (iofunc_read_default (ctp, msg, ocb));
}



int cp (int argc, char **argv)
{
	int				debug = 0;
	dispatch_t			*dpp;
	resmgr_attr_t			resmgr_attr;
	resmgr_context_t		*ctp;
	int				id;
    
	if ((dpp = dispatch_create() ) == NULL)
	{
		printf("\nUnable to dispatch create");
       		fprintf (stderr,"%s: Unable to dispatch_create.\n",argv[0]);
		return (-1);
	}
	else
	{
		if(debug)	printf("\ndispatch create success");
	}
	printf("\nWAITING FOR COMMAND FROM CPC >> ");

	iofunc_func_init (_RESMGR_CONNECT_NFUNCS, &connect_func,_RESMGR_IO_NFUNCS, &io_func);
                          
	iofunc_attr_init (&attr, S_IFNAM | 0777, 0, 0);
    
	connect_func.open = io_open;
	io_func.read = io_read;
	io_func.write = io_write;
	io_func.close_ocb = io_close;
    
   
	memset (&resmgr_attr, 0, sizeof(resmgr_attr));
	resmgr_attr.nparts_max = 1;
	resmgr_attr.msg_max_size = 2048;
    
	id = resmgr_attach (dpp, &resmgr_attr, "/dev/cmd", _FTYPE_ANY, _RESMGR_FLAG_BEFORE,&connect_func, &io_func, &attr);

	if(debug)	printf("\nid = %d",id);
                        
    
	if (id == -1)
	{
		fprintf (stderr,"%s: Unable to resmgr_attach.\n",argv[0]);
		return (-1);
	}
	if(debug)	printf("\nConnected to CPC");
	ctp = resmgr_context_alloc (dpp);

	while(cpflag)
	{
		if((ctp = resmgr_block (ctp)) == NULL)
		{
        		fprintf (stderr,"Unable to resmgr_block.\n");
			printf("\nunable to resmgr block");
        		exit (-1);
        	}
        
		resmgr_handler (ctp);
	}

	if(debug)	printf ("\ncpflg = %d\nCP > cya!\n",cpflag);
	return(1);
}

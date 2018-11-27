typedef struct motion_path
{
	double pos[6];
	double vel[5];
	double acc[4];
	double time;
} path;


typedef struct encoder_status
{
	double pos;
	double vel;
	double acc;
}status;



typedef struct end_point_position
{
	double px;
	double py;
	double pz;
}endpoint;




#ifndef MAX_LEN
#define MAX_LEN 50000
#endif


#ifndef PI
#define PI     (3.14159265358979323846)
#endif

#ifndef DEG2RAD
#define DEG2RAD    (PI/180.0)
#endif

#ifndef Deg2Rad
#define Deg2Rad    (PI/180.0)
#endif

#ifndef RAD2DEG
#define RAD2DEG    (180.0/PI)
#endif

#ifndef Rad2Deg
#define Rad2Deg    (180.0/PI)
#endif


#ifndef _WII_CLASSIC_H
#define _WII_CLASSIC_H
 
typedef struct  {
	uint8_t bouton1;
	uint8_t bouton2;
	uint8_t rx,ry,lx,ly,lt,rt;
} CLASSIC;

void classic_init(void);

void classic_maj_data(CLASSIC * classic);


#endif

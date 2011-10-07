
//par souci de simplicité
typedef char s8;
typedef unsigned char u8;
typedef int s16;
typedef unsigned int u16;
typedef long s32;
typedef unsigned long u32;


#include <util/delay.h>
#include "i2cmaster.h"
#include "wii_classic.h"

void classic_init(void) { //à lancer une fois au début
	// http://wiibrew.org/wiki/Wiimote/Extension_Controllers#The_New_Way

	i2c_init();
	//écrit 0x55 to 0xA400F0
	i2c_start(0xa4);//adresse nunchuk en écriture
	i2c_write(0xf0);
	i2c_write(0x55);
	i2c_stop();
	//écrit 0x00 to 0xA400FB
	i2c_start(0xa4);//adresse nunchuk en écriture
	i2c_write(0xfb);
	i2c_write(0);
	i2c_stop();
}


void classic_maj_data(CLASSIC * classic) {
	u8 i;
	u8 data[6];
	//reset le pointeur de lecture
	i2c_start(0xa4);//adresse classic en écriture
	i2c_write(0);
	i2c_stop();

	_delay_us(200);//minimum observé fonctionnel : _delay_us(150);
	i2c_start_wait(0xa5);//adresse en lecture
	for(i=0; i<5; i++) {
		data[i]=i2c_readAck();
	}
	data[5]=i2c_readNak();//le dernier caractère lu ne doit pas avoir d'acknowledge
	i2c_stop();
	/*for(i=0;i<6;i++){
		phex(data[i]);
		print(" ");
	}*/
	classic->bouton1=~data[4];
	classic->bouton2=~data[5];
	classic->rx=(data[2]>>7)+(data[1]>>(6-1))+(data[0]>>(6-3));
	classic->ry=data[2]&0x1f;
	classic->lx=data[0]&0x3f;
	classic->ly=data[1]&0x3f;
	classic->lt=(data[3]>>5)+((data[2]&0x60)>>(5-3));
	classic->rt=data[1]&0x3f;
}

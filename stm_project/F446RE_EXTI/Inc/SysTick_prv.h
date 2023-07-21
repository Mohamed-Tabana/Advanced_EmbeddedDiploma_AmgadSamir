
#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_


/* * * * * * * * * * * * * * * * * * * * * *
 * 				STK_CTRL Pins 		  	   *
 * * * * * * * * * * * * * * * * * * * * * */

enum {
	ENABLE,
	TICKINT,
	CLKSOURCE,
	COUNTFLAG = 16
};

/* * * * * * * * * * * * * * * * * * * * * *
 * 				STK_CALIB Pins 		  	   *
 * * * * * * * * * * * * * * * * * * * * * */

enum {
	TENMS0,
	SKEW = 30,
	NOREF = 31
};


#endif
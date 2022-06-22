#include "Config.h"

#ifdef SERIAL

#include "typedefs.h"
#include "reg.h"
#include "main.h"
#include "measure.h"
#include "adc.h"
#include "i2c.h"
#include "debug.h"
#include "printf.h"
#include "tw88.h"

extern	DATA  WORD  tm01;
extern	DATA  BYTE  tic01;

/*
//_interrupt(5) void timer2_int1 (void) 
INTERRUPT(5, timer2_int)
{
	TR2 = 0;
	TF2 = 0;
}
*/

void Idle(WORD time)
{
	BYTE ie;

	ie   = IE;					// save IE
	IE   = 0x00;

	T2CON  = 0x00;				// Timer2 Clear
	RCAP2H = 0x00;
	RCAP2L = 0x00;
	TH2    = (time>>8) ^ 0xff;	// Timer interval
	TL2    = (BYTE)time ^0x00;	//

	TR2    = 1;					// Timer2 Run
	ET2    = 1;					// Int Enable
	EA     = 1;

	PCON   = PCON | 0x01;		// Enter IDLE mode
	//---------------------------------------------
	IE   = ie;					// After awaken, restore IE

	TR2  = 0;					// LJY040402 Disable Timer2
}


void ExecuteLoader(void)
{
	BYTE ch;

	Puts("\r\nExcute Loader, Continue ? [y/N] ");

	while(1) {
		ch = Getche();
		if( ch=='Y' || ch=='y' ) break;
		if( ch=='N' || ch=='n' ) return;
	}

	Puts("\r\nWait a moment...");
	delay(100);
	Puts("\r\n\n\n\n\n\n\n\n\n\n");

	CHPENR = 0x87;		// Write Enable
	CHPENR = 0x59;		// Write Enable
	CHPCON = 0x03;		// Enter ISP Mode, Destination=4K Loader
	CHPENR = 0x00;		// Write Enable
	Idle(10000);		// Idle 1.5us
	
	CHPENR = 0x87;		// Write Enable
	CHPENR = 0x59;		// Write Enable
	CHPCON = 0x83;		// Enter ISP Mode, Destination=4K Loader
	Idle(10000);		// Idle 1.5us

}
//=============================================================================
//
//=============================================================================
void Loader(BYTE opt)
{
	switch( opt ) {

	case 2:
		LCDPowerOFF();
		ExecuteLoader();
		return;
	
	default:
		Puts("\r\nInvalid command...");
		return;
	}
}

#endif	// SERIAL

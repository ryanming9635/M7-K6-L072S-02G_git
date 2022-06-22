//-------------------------------------------------------------
//	This is changed for sdcc compiler 2.2.0a	LJY000721
//  ver0.11 2/20/2001	Support Z86129 Line 21 decoder.
//-------------------------------------------------------------
/*#include <io51.h>*/
//#include <pk-51.h>	LJY000721

#include "Config.h"

#include "reg.h"
#include "typedefs.h"
#include "cpu.h"
#include "I2C.h"
#include "main.h"
#include "debug.h"
#include "printf.h"
#include "osdbasic.h"
#include "CPU.h"


#define ID_ADDR		0xc5
#define ID_DATA		0xc6

extern	BYTE	DebugLevel;
#ifdef	INTERNAL_MCU
extern	BYTE	xdata * data regTW88;
#endif


/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/

#define I2C_FAST

#ifdef I2C_FAST
 #define I2Cdelay()
#else
 void I2Cdelay(void)
 {
	 BYTE i;
	 for(i=0; i<1; i++){
	 }
 }
#endif

#if (defined  QVGA) || (defined WQVGA)
void I2C_delay(void)
{
	 BYTE i;
	 for(i=0; i<255; i++){
		i=i;
	 }
	 for(i=0; i<128; i++){
		i=i;
	 }
}
#else
 #define I2C_delay() 
#endif
#if 0
BYTE I2CWriteData_Wait(BYTE value);
#endif
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
void WriteADC_TW88(BYTE index, BYTE dat)
{
	BYTE	page;

	page = ReadTW88( 0xff );		// save page
	WriteTW88( 0xff, 0x01 );		// change page1
	WriteTW88(index, dat);	
	WriteTW88( 0xff, page );		// restore page

}

BYTE ReadADC_TW88(BYTE index)
{
	BYTE	page, val;

	page = ReadTW88( 0xff );		// save page
	WriteTW88( 0xff, 0x01 );		// change page1
	val = ReadTW88( index );
	WriteTW88( 0xff, page );		// restore page
	
	return val;
}


#endif	// SUPPORT_PC

void WriteEEP(WORD index, BYTE dat)
{
	BYTE addr;

	addr = (EEPROMI2CAddress | (index>>7)) & 0xfe;

	I2CStart();
	I2CWriteData(addr);
	I2CWriteData((BYTE)index);
	I2CWriteData(dat);
	I2CStop();

	#ifdef DEBUG_EEP
		dPrintf("Write %02xh to [Adrs(%02xh)Index(%02xh)\r\n", (WORD)dat, (WORD)addr, (WORD)index );
	#endif

	delay(2);
}

BYTE ReadEEP(WORD index)
{
	BYTE val;
	BYTE addr;

	addr = (EEPROMI2CAddress | (index>>7)) & 0xfe;

	val = ReadI2C(addr,(BYTE)index);

	#ifdef DEBUG_OSD
		dPrintf("Read [Adrs:%02xh,Index:%02xh] %02xh\r\n", (WORD)addr, (WORD)index, (WORD)val);
	#endif
	delay(2);
	return val;
}

BYTE ReadI2C(BYTE addr, BYTE index)
{
	BYTE val;

	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);
	I2CStart();
	I2CWriteData(addr | 0x01);
	val = I2CReadData();
	I2CStop();

	return val;
}


void WriteI2C(BYTE addr, BYTE index, BYTE val)
{
	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);
	I2CWriteData(val);
	I2CStop();
}

void WriteI2CnD(BYTE addr, BYTE index, BYTE val, BYTE cnt)
{
	BYTE i;

	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);

	for(i=0; i<cnt; i++){
		I2CWriteData(val);		//LJY050101
		I2C_delay();
	}

	I2CStop();
}

void WriteI2Cn(BYTE addr, BYTE index, BYTE *val, BYTE cnt)
{
	BYTE i;


	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);

	for(i=0; i<cnt; i++){
		I2CWriteData(*(val+i));	
		I2C_delay();
	}
	I2CStop();
}

void WriteI2Cn_(BYTE addr, BYTE *val, BYTE cnt)
{
	BYTE i;

	I2CStart();
	I2CWriteData(addr);

	for(i=0; i<cnt; i++){
		I2CWriteData(*(val+i));		//LJY050101
	}
	I2CStop();
}
#if 0
//BYTE I2CWriteData_Wait(BYTE value);

void I2CReadByteMSP(BYTE addr, BYTE index, BYTE *pd, BYTE cnt)
{
	BYTE i;

	I2CStart();
	I2CWriteData_Wait(addr);
	I2CWriteData(index);
	for(i=0; i<cnt; i++) {
		I2CWriteData(*(pd+i));
	}
	I2CStart();
	I2CWriteData_Wait(addr | 0x01);
	*pd = I2CReadDataWithACK();
	*(pd+1) = I2CReadData();

	I2CStop();
}



/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/

BYTE I2CWriteData_Wait(BYTE value)
{
	WORD i;
	BYTE ack;

	for(i=0; i<8; i++, value<<=1) {
		if(value & 0x80) I2C_SDA = 1;
		else			 I2C_SDA = 0;
		I2Cdelay();
		I2C_SCL = 1;	I2Cdelay();
		I2C_SCL = 0;
	}
	I2C_SDA = 1;	I2Cdelay();
	I2C_SCL = 1;	I2Cdelay();
	i=0;
    while(1) {
		if( I2C_SCL ) break;
		i++;
	}

	ack = I2C_SDA;	//I2Cdelay();
	I2C_SCL = 0;
	return (1-ack);
}
#endif

#ifndef QVGA
void dd(void)
{
//BYTE i=0;
//for(i=0; i<1; i++)
//{}
}
#else
#define dd()  I2Cdelay()
#endif

void I2CStart()
{
	I2C_SDA = 1;	dd();
	I2C_SCL = 1;	dd();
	I2C_SDA = 0;	dd();
	I2C_SCL = 0;
}

void I2CStop()
{
	I2C_SDA = 0;	dd();
	I2C_SCL = 1;	dd();
	I2C_SDA = 1;
}

void I2CWriteData(BYTE value)
{
/*
	int i;

	for(i=0; i<8; i++, value<<=1) {
		I2C_SCL = 0;
		I2Cdelay();	// HHY 2.04 in special case, it was unstable
		if(value & 0x80) I2C_SDA = 1;
		else 			 I2C_SDA = 0;
		I2Cdelay();
		I2C_SCL = 1;
	}
*/

	I2C_SCL=0;	I2C_SDA=(value & 0x80)? 1:0;	I2C_SCL=1;	dd();
	I2C_SCL=0;	I2C_SDA=(value & 0x40)? 1:0;	I2C_SCL=1;	dd();
	I2C_SCL=0;	I2C_SDA=(value & 0x20)? 1:0;	I2C_SCL=1;	dd();
	I2C_SCL=0;	I2C_SDA=(value & 0x10)? 1:0;	I2C_SCL=1;	dd();

	I2C_SCL=0;	I2C_SDA=(value & 0x08)? 1:0;	I2C_SCL=1;	dd();
	I2C_SCL=0;	I2C_SDA=(value & 0x04)? 1:0;	I2C_SCL=1;	dd();
	I2C_SCL=0;	I2C_SDA=(value & 0x02)? 1:0;	I2C_SCL=1;	dd();
	I2C_SCL=0;	I2C_SDA=(value & 0x01)? 1:0;	I2C_SCL=1;	dd();


	I2C_SCL = 0;	// HHY 3.00
	I2C_SCL = 0;	// HHY 3.00
	I2C_SCL = 0;	//	I2Cdelay();
	I2C_SDA = 1;	//	I2Cdelay();

	I2C_SCL = 1;	// HHY 3.00
	I2C_SCL = 1;	// HHY 3.00
	I2C_SCL = 1;	//	I2Cdelay();
	I2C_SCL = 0;
}

BYTE I2CReadData()
{
	int i;
	BYTE value=0;

	I2C_SDA = 1;	dd();
	I2C_SCL = 0;
	
	for(i=0; i<8; i++) {
		I2C_SCL = 1;
		value <<= 1;
		if(I2C_SDA) value |= 1;
		I2C_SCL = 0;
	}
	dd();
	
	I2C_SCL = 1;	// HHY 3.00
	I2C_SCL = 1;	// HHY 3.00
	I2C_SCL = 1;
	I2C_SCL = 0;

	return value;

}
//#if 1
#ifdef ALC106  //Pinchi 20140925 add for AWT ML072Q
BYTE I2CReadDataWithACK()
{
	int i;
	BYTE value=0;

	I2C_SDA = 1;	I2Cdelay();
	I2C_SCL = 0;

	for(i=0; i<8; i++) {
		I2C_SCL = 1;
		value <<= 1;
		if(I2C_SDA) value |= 1;
		I2C_SCL = 0;
	}
	I2C_SDA = 0;	I2Cdelay();		//ack
	I2C_SCL = 1;	I2Cdelay();
	I2C_SCL = 0;

	return value;
}

WORD ReadI2CWORD(BYTE addr, BYTE index)
{
	WORD val;

	I2CStart();
	I2CWriteData(addr);
	I2CWriteData(index);
	I2CStart();
	I2CWriteData(addr | 0x01);
	val = I2CReadDataWithACK();
	val = val<<8;
	val |= I2CReadData();
	I2CStop();

	return val;
}

void WriteALC106(WORD index, WORD  dat)
{
	BYTE addr;
	BYTE dat1,dat2;

	dat2=dat&0x00ff;
	dat1=(dat>>8)&0x00ff;
		
	addr = (ALC106I2CAddress | (index>>7)) & 0xfe;

	I2CStart();
	I2CWriteData(addr);
	I2CWriteData((BYTE)index);
	I2CWriteData(dat1);
	dd();
	I2CWriteData(dat2);
	I2CStop();

	#ifdef DEBUG_EEP
		Printf("Write %02xh to [Adrs(%02xh)Index(%02xh)\r\n", (WORD)dat, (WORD)addr, (WORD)index );
	#endif

	delay(2);
}

WORD ReadALC106(WORD index)
{
	WORD val;
	BYTE addr;

	addr = (ALC106I2CAddress | (index>>7)) & 0xfe;

	val = ReadI2CWORD(addr,(BYTE)index);
	#ifdef DEBUG_OSD
		Printf("Read [Adrs:%02xh,Index:%02xh] %xh\r\n", (WORD)addr, (WORD)index, (WORD)val);
	#endif
	delay(2);
	return val;
}

#endif


//-------------------------------------------------------------
//-------------------------------------------------------------

#include "Config.h"

#ifdef SUPPORT_DELTA_RGB

#include "reg.h"
#include "typedefs.h"
#include "spi.h"
//#include "main.h"
#include "debug.h"
#include "printf.h"
#include "main.h"

#define	SPI_SCL		P1_0
#define	SPI_SDA		P1_1
#define SPI_CS_EN		(P4 = P4 | 0x02)  //P4_1=1
#define SPI_CS_DS		(P4 = P4 & 0xfd)  //P4_1=0

extern	BYTE	DebugLevel;

/*****************************************************************************/
/* SPI                                                                       */
/*****************************************************************************/

void DeltaRGBPanelInit(void)
{
	//volatile S3C2413_IOPORT_REG *s2413IOP = (S3C2413_IOPORT_REG *)OALPAtoVA(S3C2413_BASE_REG_PA_IOPORT, FALSE);

	SPI_CS_EN; //SPI_CS	= 1; 		//	EN = High					CS high
	SPI_SCL=1;							//	SCL High
	SPI_SDA = 1;							//	Data High
	
	#ifdef DEBUG
	dPrintf(">> 2.8inch lcd test...ready!\r\n");

	dPrintf(">> 2.8inch lcd test...start!\r\n");		
	#endif
	delay(7);		// DonGo
	
	///////////////////////////////////////////////////////////////////
	// Power on Reset and Display off
	//////////////////////////////////////////////////////////////////
	WriteSPI(0x07, 0x0000);	 //R07 <--0000h	
	SPIdelay(5*10);  //delay about 25us
	WriteSPI(0x12, 0x0000);	 //R07 <--0000h

	// delay about 10ms --18ms
	delay(1);
	
	///////////////////////////////////////////////////////////////////
	// Power Setting Function 1
	///////////////////////////////////////////////////////////////////	
	WriteSPI(0x11, 0x0510);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x12, 0x0020);	 //R07 <--0000h	
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x13, 0x1f2d);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x14, 0x0000);	 //R07 <--0000h	
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x15, 0x03ed);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x16, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x18, 0x7705);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	
	///////////////////////////////////////////////////////////////////
	// Power Setting Function 2
	///////////////////////////////////////////////////////////////////
	WriteSPI(0x10, 0x0004);	 //R07 <--0000h
		
	// delay about 150ms --180ms
	delay(15);
	
	///////////////////////////////////////////////////////////////////
	// Display Setting Function 
	///////////////////////////////////////////////////////////////////
	WriteSPI(0x01, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x02, 0x0300);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x03, 0x0001);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x04, 0x0001);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x05, 0x000a);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x06, 0x0014);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x0b, 0x0200);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x0c, 0x0200);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x0e, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x0f, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x20, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x21, 0x0700);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x2a, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x2b, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x30, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x31, 0x0000);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x32, 0x0907);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x33, 0x0907);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x34, 0x0001);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x35, 0x0001);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x36, 0x0c06);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x37, 0x0c06);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x38, 0x1f00);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us
	WriteSPI(0x39, 0x1f00);	 //R07 <--0000h
	SPIdelay(50);  //delay about 25us

	// delay about 40ms	-- 48ms		
	delay(4);		

	///////////////////////////////////////////////////////////////////
	// Power On Status---Display On Function 1
	///////////////////////////////////////////////////////////////////
	WriteSPI(0x07, 0x0001);	 //R07 <--0000h
	
	// delay about 40ms	-- 48ms		
	delay(4);		
	
	///////////////////////////////////////////////////////////////////
	// Power On Status---Display On Function 1
	///////////////////////////////////////////////////////////////////
	WriteSPI(0x07, 0x0101);	 //R07 <--0000h
		
	// delay about 40ms	-- 48ms		
	delay(4);		
	
	///////////////////////////////////////////////////////////////////
	// Power On Status---Display On Function 2
	///////////////////////////////////////////////////////////////////
	WriteSPI(0x07, 0x0103);	 //R07 <--0000h

}


void SPIdelay(BYTE d)
{
	 BYTE i;
	 for(i=0; i<d; i++){
	 }
}

void WriteSPI(BYTE addr, WORD dat)
{
	//volatile S3C2413_IOPORT_REG *s2413IOP = (S3C2413_IOPORT_REG *)OALPAtoVA(S3C2413_BASE_REG_PA_IOPORT, FALSE);
   	int	 j;
	//unsigned char DELAY=100;
	unsigned char DELAY=1; // delay about 1us
	DWORD xAddress, xData;
	
	xAddress = 	0x00600000L|(0x000000ffL & addr);
	xData = 	0x00620000L|(0x0000ffffL & dat);
	
	///////////////////////address
	SPI_CS_EN; //SPI_CS	= 1; 		//	EN = High					CS high
	SPI_SCL=1;							//	SCL High
	SPI_SDA = 1;							//	Data High

	SPIdelay(DELAY); // delay about 1us

	SPI_CS_DS; //SPI_CS	= 0; 		//	EN = Low				CS Low
	SPIdelay(DELAY);// delay about 1us

	SPI_SCL = 0;							//	SCL Low
	SPIdelay(DELAY);// delay about 1us
	
	for (j = 23; j >= 0; j--)//17
	{

		if ((xAddress >> j) & 0x00000001L)	// DATA HIGH or LOW
			SPI_SDA = 1;// delay about 1us
		else
			SPI_SDA = 0;// delay about 1us
  
		SPIdelay(DELAY);// delay about 1us

		SPI_SCL=1;			// CLOCK = High
		SPIdelay(DELAY);// delay about 1us

		if(j != 0)
		{
			SPI_SCL = 0;
			SPIdelay(DELAY);	// delay about 1us		// CLOCK = Low
		}
	}

	SPI_SCL=1;
	SPIdelay(DELAY);	// delay about 1us		// CLOCK = Low
	
	SPI_SDA = 1;							// Data Low
	SPIdelay(DELAY);// delay about 1us

	SPI_CS_EN; //SPI_CS	= 1; 		//	EN = High
	SPIdelay(DELAY);// delay about 1us

	SPIdelay(50);  // delay about 25us
	
	SPI_CS_DS; //SPI_CS	= 0; 		//	EN = Low				CS Low
	SPIdelay(DELAY);// delay about 1us

	SPI_SCL = 0;							//	SCL Low
	SPIdelay(DELAY);// delay about 1us
	
	for (j = 23; j >= 0; j--)//17
	{

		SPIdelay(DELAY);// delay about 1us			// CLOCK = Low

		if ((xData >> j) & 0x00000001L)	// DATA HIGH or LOW
			SPI_SDA = 1;
		else
			SPI_SDA = 0;

		SPIdelay(DELAY);// delay about 1us

		SPI_SCL=1;			// CLOCK = High
		SPIdelay(DELAY);// delay about 1us

		if(j != 0)
		{
			SPI_SCL = 0;
			SPIdelay(DELAY);// delay about 1us			// CLOCK = Low
		}
	}

	SPI_SCL=1;
	SPIdelay(DELAY);	// delay about 1us		// CLOCK = Low
	
	SPI_SDA = 1;							// Data Low
	SPIdelay(DELAY);// delay about 1us

	SPI_CS_EN; //SPI_CS	= 1; 		//	EN = High
	SPIdelay(DELAY);// delay about 1us
}


WORD ReadSPI(BYTE addr)
{
	//volatile S3C2413_IOPORT_REG *s2413IOP = (S3C2413_IOPORT_REG *)OALPAtoVA(S3C2413_BASE_REG_PA_IOPORT, FALSE);
   	int	 j;
	//unsigned char DELAY=100;
	unsigned char DELAY=10; // delay about 1us
	DWORD xAddress;
	BYTE  xData;
	WORD  rData ;
	
	xAddress = 	0x00600000L|(0x000000ffL & addr);
	xData = 	0x63;
	
	///////////////////////address
	SPI_CS_EN; //SPI_CS	= 1; 		//	EN = High					CS high
	SPI_SCL=1;							//	SCL High
	SPI_SDA = 1;							//	Data High

	SPIdelay(DELAY); // delay about 1us

	SPI_CS_DS; //SPI_CS	= 0; 		//	EN = Low				CS Low
	SPIdelay(DELAY);// delay about 1us

	SPI_SCL = 0;							//	SCL Low
	SPIdelay(DELAY);// delay about 1us
	
	for (j = 23; j >= 0; j--)//17
	{

		if ((xAddress >> j) & 0x00000001L)	// DATA HIGH or LOW
			SPI_SDA = 1;// delay about 1us
		else
			SPI_SDA = 0;// delay about 1us
  
		SPIdelay(DELAY);// delay about 1us

		SPI_SCL=1;			// CLOCK = High
		SPIdelay(DELAY);// delay about 1us

		if(j != 0)
		{
			SPI_SCL = 0;
			SPIdelay(DELAY);	// delay about 1us		// CLOCK = Low
		}
	}

	SPI_SCL=1;
	SPIdelay(DELAY);	// delay about 1us		// CLOCK = Low
	
	SPI_SDA = 1;							// Data Low
	SPIdelay(DELAY);// delay about 1us

	SPI_CS_EN; //SPI_CS	= 1; 		//	EN = High
	SPIdelay(DELAY);// delay about 1us

	SPIdelay(50);  // delay about 25us
	
	SPI_CS_DS; //SPI_CS	= 0; 		//	EN = Low				CS Low
	SPIdelay(DELAY);// delay about 1us

	SPI_SCL = 0;							//	SCL Low
	SPIdelay(DELAY);// delay about 1us

	
	for (j=7; j >= 0; j--)
	{

		if ((xData >> j) & 0x01)	
			SPI_SDA = 1;
		else
			SPI_SDA = 0;

		SPIdelay(DELAY);// delay about 1us

		SPI_SCL=1;			// CLOCK = High
		SPIdelay(DELAY);// delay about 1us

		SPI_SCL = 0;							//	SCL Low
		SPIdelay(DELAY);// delay about 1us
	}

	//SPI_SDA = 1;
	//SPIdelay(DELAY);// delay about 1us

	SPI_SCL = 0;
	SPIdelay(DELAY);// delay about 1us			// CLOCK = Low

	for (j=15; j >=0; j--)
	{

		SPIdelay(DELAY);// delay about 1us			// CLOCK = Low

		SPI_SCL=1;			// CLOCK = High
		SPIdelay(DELAY);// delay about 1us

		rData <<= 1;
		if( SPI_SDA ) rData |= 1;
		SPIdelay(DELAY);// delay about 1us

		if(j != 0)
		{
			SPI_SCL = 0;
			SPIdelay(DELAY);// delay about 1us			// CLOCK = Low
		}
	}

	SPI_SCL=1;
	SPIdelay(DELAY);	// delay about 1us		// CLOCK = Low
	
	SPI_SDA = 1;							// Data Low
	SPIdelay(DELAY);// delay about 1us

	SPI_CS_EN; //SPI_CS	= 1; 		//	EN = High
	SPIdelay(DELAY);// delay about 1us

	return rData;
}
#endif
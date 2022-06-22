#include "Config.h"

#if defined( SUPPORT_PC ) || defined ( SUPPORT_DTV )

#include "reg.h"
#include "typedefs.h"
#include "i2c.h"
#include "adc.h"
#include "printf.h"
#include "main.h"
#include "tw88.h"
#include "pc_eep.h"
#include "measure.h"

// Address
#define PLLDIVM		0xc3
#define PLLDIVL		0xc4
#define PHASE		0xc5
#define RGB_SEL		0xd0
#define ADCMODE		0xc0
#define ADC_POWER	0xcb
#define VCOCURR		0xc2

//=============================================================================
//                             ADC Functions
//=============================================================================
#ifdef  SUPPORT_DTV
CODE BYTE DTV_YPbPr_ADC_init[] = 
{
	TW88I2CAddress, 51,
	
0x02, 0x4A,			// input format
0x06, 0x00,			// Analog Control Register
0x38, 0x00,			// change Anti Aliasing filter path to RGB
0x40, 0xE4,			// scaler input control register
0x41, 0x00,
0x42, 0x80,
0x43, 0x20,
0x44, 0x2B,
0x45, 0x3B,
0x46, 0x20,
0x49, 0x30, //; seq
0x47, 0x83,
0x48, 0x4B,
0x4D, 0x10,		//0x00, //; seq
0x4A, 0x0E,
0x4B, 0x0E,
0x4C, 0xF6,
0x4E, 0x77,
0x4F, 0x10,
//0x50, 0x01,
0x60, 0xE0,			// Zoom Control Register
0x61, 0x80,
0x62, 0x7C,
0x63, 0x00,
0x64, 0x00,
0x65, 0x80,

0xDA, 0x3D,
0xDB, 0xC3,
0xDC, 0xFC,
0xDD, 0x00,
0xDE, 0x00,
0xDF, 0x00,

0xFF, 0x01, //; Page 1
0xC0, 0x10,
0xC1, 0xFA,
0xC2, 0x00,
0xC3, 0x03,
0xC4, 0x5A,
0xC5, 0x14,
0xC6, 0x26,
0xC7, 0x04,
0xC8, 0x00,
0xC9, 0x00,
0xCA, 0x00,
#ifdef REFERENCE
0xCB, 0xD7,
#else
0xCB, 0xDF,
#endif 
0xCC, 0x0F,
0xCD, 0x00,
0xD0, 0x07,
0xD1, 0x70,
0xD2, 0x70,
0xD3, 0x70,
0xD4, 0x00,
0xD5, 0x00,
0xD6, 0x10,
0xD7, 0x40,
0xD8, 0x02,
0xD9, 0x01,
0xDA, 0x80,
0xDB, 0x80,
0xDC, 0x20,
0xE0, 0x00,

	0xff, 0x00,
	0xff, 0xff
};
#endif
CODE BYTE RGB_ADC_init[] = 
{
	TW88I2CAddress, 52,
0xFF, 0x00, //; Page 0
0x02, 0xCD,
0x06, 0x00,
0x38, 0x00,
0x40, 0xC4,
0x41, 0x00,
0x42, 0x04,
0x43, 0x20,
0x44, 0x2F,
0x45, 0x3B,
0x46, 0x20,
0x47, 0x2C,
0x48, 0xC0,
0x49, 0x20,
0x4A, 0x24,
0x4B, 0x24,
0x4C, 0xE7,
0x4D, 0x10,
0x4E, 0x75,
0x4F, 0x1E,
0x50, 0x00,
0x60, 0xCC,
0x61, 0x80,
0x62, 0x00,
0x63, 0x04,
0x64, 0x00,
0x65, 0x80,

0xDA, 0x3D,
0xDB, 0xC3,
0xDC, 0xFC,
0xDD, 0x00,
0xDE, 0x00,
0xDF, 0x00,

0xFF, 0x01, //; Page 1
0xC0, 0x18,		//0x08,
//0xC1, 0x3F,
0xC2, 0x00,
0xC3, 0x03,
0xC4, 0x20,
0xC5, 0x13,
0xC6, 0x20,
0xC7, 0x04,
0xC8, 0x00,
0xC9, 0x00,
0xCA, 0x00,
0xCB, 0xD7,
0xCC, 0x1F,
0xCD, 0x00,
0xD0, 0x07,
0xD1, 0x8C,
0xD2, 0x79,
0xD3, 0x97,
0xD4, 0x80,
0xD5, 0x00,
0xD6, 0x10,
0xD7, 0x00,
0xD8, 0x47,
0xD9, 0x02,
0xDA, 0x02,
0xDB, 0x01,
0xDC, 0x20,
0xE0, 0x00,

0xff, 0x00,
0xff, 0xff
};

void SetADCMode(BYTE mode)
{
	mode = mode;  //Pinchi 20150316 add for compiler warning
	#ifdef DEBUG_PC
	dPrintf("\r\n SetADCMode: %d", mode);
	#endif

#ifdef  SUPPORT_DTV
	if( mode==DTV ) {	// DTV-YPbPr
		I2CDeviceInitialize( DTV_YPbPr_ADC_init );
	}
	else
#endif		
	{			// RGB
		I2CDeviceInitialize( RGB_ADC_init );
	}
}

WORD GetCoarse(void)
{
	WORD buf;

	buf = ReadADC_TW88(PLLDIVM) << 8;
	buf |= ReadADC_TW88(PLLDIVL);

	buf--;
	return buf;
}

void SetCoarse(WORD i)
{
	i++;
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nSet Coarse->%04x(%d) ", i, i);
	#endif
	WriteADC_TW88(PLLDIVM, (BYTE)(i >> 8));
	WriteADC_TW88(PLLDIVL, (BYTE)(i));
}

void SetPhase(BYTE j)
{
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nSet Phase->%04x ", (WORD)j);
	#endif

	WriteADC_TW88(PHASE, j&0x1f);
}

BYTE GetPhaseCurrent(void)
{
	return ReadADC_TW88(PHASE) & 0x1f;
}

BYTE SetVCORange(DWORD _IPF)
{
	BYTE VCO_CURR, oldv, chged=0;
	BYTE val;
	
	val = _IPF / 1000000L;
	
	if     ( val < 15 )		VCO_CURR = 0x00;	// 00 000
	else if( val < 34 )		VCO_CURR = 0x00;	// 00 000
	else if( val < 45 )		VCO_CURR = 0x08;	// 01 000
	else if( val < 63 )		VCO_CURR = 0x08;	// 01 000
	else if( val < 70 )		VCO_CURR = 0x08;	// 10 000
	else if( val < 80 )		VCO_CURR = 0x10;	// 10 000
	else if( val <100 )		VCO_CURR = 0x10;	// 10 000
	else if( val <110 )		VCO_CURR = 0x10;	// 10 000
	else					VCO_CURR = 0x18;	// 11 000
	
	oldv = ReadADC_TW88(VCOCURR) & 0x1f;	// curr VCO_CURR value  
	val = VCO_CURR;
	if( oldv != val ) {
		chged = 1;
		WriteADC_TW88(VCOCURR, val);		//
		delay(1);					// time to stabilize
	}

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nSetVCO=%02x, changed=%d", (WORD)val, (WORD)chged );
	#endif

	return chged;
}

void AutoColorAdjust(void)
{
WORD	GainYG, GainUB, GainVR;
BYTE	MaxR, MaxG, MaxB, temp, i;
bit		Finish = 0;

	WriteTW88( 0x44, (ReadTW88(0x44)&0xf3)|0x08 );		// set mode to YUV - direct path

	WriteTW88( 0xff, 1 );	// set Page 1
	/*
	temp = ReadTW88(0xD0);		// bit 2 for Y, 1 for U, 0 for V
	GainYG = temp & 4;
	GainYG <<= 6;
	GainYG |= ReadTW88(0xD1);	// read gain G
	GainUB = temp & 2;
	GainUB <<= 7;
	GainUB |= ReadTW88(0xD2);	// read gain G
	GainVR = temp & 1;
	GainVR <<= 8;
	GainVR |= ReadTW88(0xD3);	// read gain G
	*/
	GainVR = 200;
	GainYG = 200;
	GainUB = 200;
	WriteTW88( 0xD0, 0 );
	WriteTW88( 0xD1, GainYG );	// write gain G
	WriteTW88( 0xD2, GainUB );	// write gain B
	WriteTW88( 0xD3, GainVR );	// write gain R
	WriteTW88( 0xff, 0 );	// set Page 1
	#ifdef DEBUG_PC_COLOR
	Printf("\r\nGain R:%d, G:%d, B:%d", GainVR, GainYG, GainUB);
	#endif
	i = 0;
	while (i++ < 20) {			// max count 20
		MeasureAndWait(3);		// measure any fields
		WriteTW88( 0x5B, 0x40 );	// readout RGB Max
		MaxR = ReadTW88( 0x59 );
		MaxG = ReadTW88( 0x58 );
		MaxB = ReadTW88( 0x57 );
		#ifdef DEBUG_PC_COLOR
		Printf("\r\nMax R:%d, G:%d, B:%d", (WORD)MaxR, (WORD)MaxG, (WORD)MaxB);
		#endif
		if (( MaxR == 0xFC ) && ( MaxG == 0xFC ) && ( MaxB == 0xFC )) break;
		
		GainVR += (0xFC - MaxR);
		GainYG += (0xFC - MaxG);
		GainUB += (0xFC - MaxB);
		if ( GainVR & 0xE00 ) GainVR = 0x1FF;				// set MAX
		if ( GainYG & 0xE00 ) GainYG = 0x1FF;				// set MAX
		if ( GainUB & 0xE00 ) GainUB = 0x1FF;				// set MAX
		temp = ((GainYG>>6) & 4) + ((GainUB>>7) & 2) + ((GainVR>>8) & 1);
		WriteTW88( 0xff, 1 );	// set Page 1
		WriteTW88( 0xD0, temp );
		WriteTW88( 0xD1, GainYG );	// write gain G
		WriteTW88( 0xD2, GainUB );	// write gain B
		WriteTW88( 0xD3, GainVR );	// write gain R
		WriteTW88( 0xff, 0 );	// set Page 0

		#ifdef DEBUG_PC_COLOR
		Printf("\r\nSet Gain R:%d, G:%d, B:%d", GainVR, GainYG, GainUB);
		#endif

	}
	WriteTW88( 0x44, (ReadTW88(0x44)&0xf3)|0x0c );		// set mode to RGB
	SaveADCGainOffsetEE(1);		// save to new value
}

#endif	// SUPPORT_PC


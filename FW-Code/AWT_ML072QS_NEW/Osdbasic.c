//osd_basic.c
// ver0.11 2/1x/2001 Change display format from hex to decimal
//	1.32	LJY11262001	.Add border features to OSD window
//	1.70	LJY05302003 .Support a menu with external OSD.
//	2.00	BYH05102007 .Support internal MCU, which connect with direct memoty bus
//						 It needs change whole ReadTW88, WriteTW88 to regTW88

#include "Config.h"

#include "typedefs.h"
#include "i2c.h"
#include "main.h"
#include "tw88.h"

#include "osdbasic.h"
#include "dispinfo.h"
#include "measure.h"
#include "debug.h"
#include "printf.h"
#include "udfont.h"
#include "regmap.h"
#include "externs.h"

extern CODE struct RegisterInfo UserRange;

//CODE BYTE ZoomAttr[]={	0,	0,	0x40,	0x80,	0xc0	};

//IDATA struct BarInfo BarInfo;
IDATA struct OSDStrInfo OSDStrInfo;
extern	bit   I2CAutoIncFlagOn ;
extern		DATA  WORD  stopWatch;

data BYTE	code *ptrFont;

//********************************************************************
//
//	Font
//
//********************************************************************

void WaitEndofDisplayArea(void)
{
	BYTE ret,i;
	
	ret =  ReadTW88(OSDWINSTATUS) & 0x40;

	for(i=0;i<10;i++)
	{
		if( ret^ (ReadTW88(OSDWINSTATUS)&0x40)) break; 
	}
}

//=============================================================================
//			Download OSD Color Look up 
//=============================================================================
void Change_OSDColorLookup(void)
{
	BYTE i,j;
	for(j=0; j<2; j++) {   
		for(i=0; i<8; i++) {
			WriteTW88(0x9c, i+j*8);
			WriteTW88(0x9d, OSD_Color_LookUp_Data_Table[j][i]);
		}
	}
}

//=============================================================================
//			Download RAM Font Data
//=============================================================================
//#include "grid_LPL.c"
//#include "grid_GenTex.c"
//#include "gridTW.c"
//#include "grid\LINE_45B-4.c"
/*
struct MultiGridInfo
{
	unsigned char	NFonts;
	unsigned char	NChars;
	unsigned char	*LUT;
	unsigned char	NofWindows;
	unsigned int	*WPos0;
	unsigned char	*WColors0;
	unsigned int	*WPos1;
	unsigned char	*WColors1;
	unsigned int	*WPos2;
	unsigned char	*WColors2;
	unsigned int	*WPos3;
	unsigned char	*WColors3;
	unsigned char	*CharPos;
	unsigned char	*FontData;
	unsigned char	*DisplayData;
};
*/
//extern code struct MultiGridInfo  cone_Info, Japanese_Info;



void DownloadFont(BYTE cod, CODE_P BYTE *fontdata)
{
	WriteTW88(TW88_ENABLERAM, ReadTW88(TW88_ENABLERAM) | 0x01);		// Font RAM access mode
	WriteTW88(TW88_FONTRAMADDR, cod);

//	WriteTW88(0xff, ReadTW88(0xff) | 0x10);	// Disable I2C index auto increment during multi-write
	WriteTW88(0xe0, ReadTW88(0xe0) | 0x10);	// Disable I2C index auto increment during multi-write
	WriteI2Cn( TW88I2CAddress, TW88_FONTRAMDATA, fontdata, 27 );

	WriteTW88(TW88_ENABLERAM, ReadTW88(TW88_ENABLERAM) & 0xfe);		// OSD RAM access mode
}

void DownloadUDFont(void)
{
	BYTE i;

	WriteTW88(TW88_MULTISTART, COLORFONT_START); // Set Color Font Start Address. 

	for(i=0; i< NO_UDFONT && i<= MAX_FONT_RAM_CHARS ; i++) {
		DownloadFont(i, RAMFONTDATA[i]);
	}
}
/*
void DownloadGridFont(void)
{
	BYTE i;

	WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 

	//for(i=0; i< 62 ; i++) {	//LPL case 62 chars
	for(i=0; i< NofFonts ; i++) {		// Techwell case 48 chars
		DownloadFont(i, gridTW[i]);
	}
}
*/
#if 0
void DownloadGridFont(void)
{
register	BYTE i, m;

	WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 

	m = LINE_45B_Info.NFonts;
	for(i=0; i< m ; i++) {		// Techwell case 48 chars
		DownloadFont(i, &LINE_45B_Info.FontData[i*27]);
	}
}

void DownloadConeFont(void)
{
register	BYTE i, m;

	WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 
	m = cone_Info.NFonts;
	for(i=0; i< m ; i++) {		// Techwell case 48 chars
		DownloadFont(i, &cone_Info.FontData[i*27]);
	}
}

void DownloadJapaneseFont(void)
{
register	BYTE i, m;

	WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 
	m = Japanese_Info.NFonts;
	for(i=0; i< m ; i++) {		// Techwell case 48 chars
		DownloadFont(i+190, &Japanese_Info.FontData[i*27]);
	}
}
#endif

//*****************************************************************************
//	OSD Window internal subfunction for TW88xx
//*****************************************************************************
//*****************************************************************************
//	Functions for TW88xx internal OSD
//*****************************************************************************
#ifdef SUPPORT_OSDPOSITIONMOVE

void SetOSDWindowX_TW88(BYTE winno, BYTE x)
{
	WORD tmp;
	BYTE dat;

	if( winno<1 || winno>8 ) return;
	SetOSDWindowNum(winno);

	tmp = x << 3;

	dat = ReadTW88(TW88_WINSTART_HI) & 0xf0;
	dat = dat | (tmp>>8);

	WriteTW88(TW88_WINSTART_HI, dat);
	WriteTW88(TW88_WINXSTART, tmp);
}
#endif
void SetOSDWindowY_TW88(BYTE winno, BYTE y)
{
	WORD tmp;
	BYTE dat;

	if( winno<1 || winno>8 ) return;
	SetOSDWindowNum(winno);

	tmp = y << 2;

	dat = ReadTW88(TW88_WINSTART_HI) & 0x0f;
	dat = dat | ((tmp>>8)<<4);

	WriteTW88(TW88_WINSTART_HI, dat);
	WriteTW88(TW88_WINYSTART, tmp);
}

//=============================================================================
//			ShowOSDWindow_TW88
//=============================================================================
void ShowOSDWindowAll(BYTE on)
{
	BYTE rd;

	WaitEndofDisplayArea();	
	rd = ReadTW88(TW88_OSDLOCKUPSEL);

	if( on )
		WriteTW88(TW88_OSDLOCKUPSEL, rd&0xef);	// 
	else
		WriteTW88(TW88_OSDLOCKUPSEL, rd|0x10);	// OSD All Off (TW8806B)

}
void ShowOSDWindow_TW88(BYTE winno, BYTE onoff)
{
	BYTE rd;

	if( winno<1 || winno>8 ) return;
	SetOSDWindowNum(winno);

	rd = ReadTW88(TW88_WINATTR);
	if( onoff ) rd |= 0x01;
	else 		rd &= 0xfe;

	WaitEndofDisplayArea();	
	WriteTW88(TW88_WINATTR, rd);
}

#ifdef SUPPORT_OSDPOSITIONMOVE
WORD GetOSDWindowX(BYTE winno)
{
	WORD x;

	if( winno<1 || winno>8 ) return 0;
	SetOSDWindowNum(winno);

	x = (ReadTW88(TW88_WINSTART_HI) & 0x0f) << 8;
	x = x  | ReadTW88(TW88_WINXSTART);

	return (BYTE)(x >> 3);
}
#endif

WORD GetOSDWindowY(BYTE winno)
{
	WORD y;

	if( winno<1 || winno>8 ) return 0;
	SetOSDWindowNum(winno);

	y = (ReadTW88(TW88_WINSTART_HI) & 0xf0) << 4;
	y = y  | ReadTW88(TW88_WINYSTART);

	return (BYTE)(y >> 2);
}

#include	"osdTW88.c"
//*****************************************************************************
//
//	Internal Font test
//
//*****************************************************************************
//-----------------------------------------------------------------------------
//	CopyUDCharToOSDWindow(BYTE winno, BYTE xoff, BYTE yoff, BYTE attr, BYTE ch)
//	- For FONT RAM Char.
//-----------------------------------------------------------------------------
code BYTE	FontTestWindow[] = { 0xa1, 10, 0xa2, 10, 0xa0, 0, 0xa3, 16, 0xa4, 16, 0xa5, 0x91, 
									0xa6, 1, 0xa7, 1, 0xa8, 0x22, 0xa9, 0x10, 0xaa, 00, 0xab, 0x62 };

#ifdef Hs_debug	
void DisplayROMFont( BYTE scode )
{
BYTE	i;

	WriteTW88( 0x94, 0x02 );		// clear OSD RAM clear and ROM font select
	WriteTW88( 0x9e, 0 );			// window #0
	for ( i=0; i<(sizeof(FontTestWindow)/2); i++ )
		WriteTW88(FontTestWindow[i*2], FontTestWindow[i*2+1]);
	if ( scode == 0 ) {
		WriteTW88( 0x94, 0x00 );		//0000 1100 ROM Font select with same attribute
		for ( i=0; i<0xfe; i++ ) {
			WriteTW88( 0x96, i );
			WriteTW88( 0x97, i );
			WriteTW88( 0x98, 0x97 );
		}
	}
	else {
	  WriteTW88( 0x94, 0x0C );		//0000 1100 ROM Font select with same attribute
	  Puts("\r\nIf you'd like to exit, press any Key....");
	  while ( !RS_ready() ){
	    WriteTW88( 0x94, 0x0C );		//0000 1100 ROM Font select with same attribute
		WriteTW88( 0x96, 0 );			// set start position of RAM
		WriteTW88( 0x98, 0x47 );		// different color with upper
		i = 0;
		do {
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
		} while ( i != 0 );
	  }
	}
	WriteTW88( 0x9f, 0x17 );			// enable Window #2
	WriteTW88( 0x9c, 0x0f);			// turn ON
}


void DisplayRAMFont(BYTE scode)
{
BYTE	i, j;
WORD	takenTime;

	WriteTW88( 0x94, 0x02 );		// clear OSD RAM clear
	WriteTW88( 0x9e, 1 );			// window #1
	for ( i=0; i<(sizeof(FontTestWindow)/2); i++ )
		WriteTW88(FontTestWindow[i*2], FontTestWindow[i*2+1]);
	if ( scode == 0 ) {
		WriteTW88( 0x94, 0x80 );		//0000 1101 RAM Font select with same attribute
		for ( i=0; i<0xfe; i++ ) {
			WriteTW88( 0x96, i );
			WriteTW88( 0x97, i );
			WriteTW88( 0x98, 0x97 );
		}
	}
	else if ( scode == 1 ) {
	  Puts("\r\nIf you'd like to exit, press any Key....");
	  j = 0;
	  while ( !RS_ready() ){
		WriteTW88( 0x94, 0x8C );		//0000 1101 RAM Font select with same attribute
		WriteTW88( 0x96, 0 );			// set start position of RAM
		WriteTW88( 0x98, 0x47 );		// different color with upper
		i = 0;
		do {
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
			WriteTW88( 0x97, i++ );
		} while ( i != 0 );
	  }
	}
	else {
		stopWatch = 0;
		DownloadUDFont();
		takenTime = stopWatch;
		Printf("\r\nDownload User Font takes : %d [x10ms]", takenTime);
	}
	WriteTW88( 0x9f, 0x17 );			// enable Window #2
	WriteTW88( 0x9c, 0x0f);			// turn ON
}
#endif

#ifdef CHIP_MANUAL_TEST
void TestRAMFont(void)
{
int		i, j;

	WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 
	WriteTW88( 0x94, 0x02 );		// clear OSD RAM clear
	WriteTW88( 0x9e, 1 );			// window #1
	for ( i=0; i<(sizeof(FontTestWindow)/2); i++ )
		WriteTW88(FontTestWindow[i*2], FontTestWindow[i*2+1]);

	WriteTW88( 0x94, 0x80 );		//0000 1101 RAM Font select with same attribute
	for ( i=0; i<0xfe; i++ ) {
		WriteTW88( 0x96, i );
		WriteTW88( 0x97, i );
		WriteTW88( 0x98, 0x97 );
	}
	WriteTW88(TW88_ENABLERAM, ReadTW88(TW88_ENABLERAM) | 0x01);		// Font RAM access mode ON
	for(i=0; i< 256 ; i++) {		// Techwell case 48 chars
		WriteTW88(TW88_FONTRAMADDR, i);
		for ( j = 0; j<27; j++ ) {
			WriteTW88(TW88_FONTRAMDATA, 0x55);
		}
	}
	DelaynCheck();
	for(i=0; i< 256 ; i++) {		// Techwell case 48 chars
		WriteTW88(TW88_FONTRAMADDR, i);
		for ( j = 0; j<27; j++ ) {
			WriteTW88(TW88_FONTRAMDATA, 0xAA);
		}
	}
	WriteTW88(TW88_ENABLERAM, (ReadTW88(TW88_ENABLERAM) & 0xfe));		// OSD RAM access mode OFF
//	WriteTW88( 0x9f, 0x17 );			// enable Window #2
//	WriteTW88( 0x9c, 0x0f);			// turn ON
}
#endif

// below is for LPL
/*
code BYTE	GridWindow[] = { 0xa5, 0, 0xa6, 0, 0xa7, 0, 0xa8, 0, 0xa9, 0x0, 0xab, 0x62 };
code BYTE	Grid0[] = { 0x0d, 0x0e, 0x0f, 
						0x10, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
						0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d  };	// bottom 22
code BYTE	Grid1[] = { 0x05, 0x06, 0x07, 0x0c, 0x0d, 0x0e,
						0x13, 0x14, 0x1a, 0x1b,
						0x21, 0x22, 0x29, 
						0x30, 0x31, 0x38, 0x39, 0x3a,
						0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47 };	// left 26
code BYTE	Grid2[] = { 0x00, 0x01, 0x0b, 0x0c, 0x0d,
						0x16, 0x17, 0x18,
						0x21, 0x22, 0x23, 0x2b, 0x2c  };	// right
void DisplayGrid( void )
{
BYTE	i, j;

	DownloadGridFont();
	WriteTW88( 0x94, 0x02 );		// clear OSD RAM clear

	WriteTW88( 0x94, 0x80 );		//0000 1101 RAM Font select with same attribute
	for ( i=0; i < (72+51+45); i++ ) {		// clear with font '0'
		WriteTW88( 0x96, i );
		WriteTW88( 0x97, 0 );
		WriteTW88( 0x98, 0x07 );
	}
	i = 1;
	for ( j=0; j< sizeof(Grid0); j++ ) {		// display data for bottom
		WriteTW88( 0x96, Grid0[j] );	// set position
		WriteTW88( 0x97, i++ );
		WriteTW88( 0x98, 0x07 );
	}
	for ( j=0; j< sizeof(Grid1); j++ ) {		// display data for left
		WriteTW88( 0x96, Grid1[j]+51 );	// set position
		WriteTW88( 0x97, i++ );
		WriteTW88( 0x98, 0x07 );
	}
	for ( j=0; j< sizeof(Grid2); j++ ) {		// display data for right
		WriteTW88( 0x96, Grid2[j]+51+72 );	// set position
		WriteTW88( 0x97, i++ );
		WriteTW88( 0x98, 0x07 );
	}

	WriteTW88( 0x9e, 0 );			// window #0 for bottom
	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
	WriteTW88( 0xa0, 0 );
	WriteTW88( 0xa1, 115);
	WriteTW88( 0xa2, 163);
	WriteTW88( 0xa3, 17);
	WriteTW88( 0xa4, 3);
	WriteTW88( 0xaa, 0);
	WriteTW88(0x9e, 0x70 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x00 );
	WriteTW88(0xac, 0 );

	WriteTW88( 0x9f, 1 );			// enable Window #0

	WriteTW88( 0x9e, 1 );		
	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
	WriteTW88( 0xa0, 0 );
	WriteTW88( 0xa1, 19);
	WriteTW88( 0xa2, 56);
	WriteTW88( 0xa3, 8);
	WriteTW88( 0xa4, 9);
	WriteTW88( 0xaa, 51 );
	WriteTW88(0x9e, 0x71 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x01 );
	WriteTW88(0xac, 0 );
	WriteTW88( 0x9f, 1 );			// enable Window #1

	WriteTW88( 0x9e, 2 );		
	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
	WriteTW88( 0xa0, 0 );
	WriteTW88( 0xa1, 204);
	WriteTW88( 0xa2, 64);
	WriteTW88( 0xa3, 9);
	WriteTW88( 0xa4, 5);
	WriteTW88( 0xaa, 51+72 );
	WriteTW88(0x9e, 0x72 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x02 );
	WriteTW88(0xac, 0 );

	WriteTW88( 0x9f, 1 );			// enable Window #2

	WriteTW88( 0x9e, 3 );		
	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
	WriteTW88( 0xa0, 0 );
	WriteTW88( 0xa1, 1);
	WriteTW88( 0xa2, 1);
	WriteTW88( 0xa3, 0x1a);
	WriteTW88( 0xa4, 0x0d);
	WriteTW88( 0xa5, 0xa1);
	WriteTW88( 0xa6, 3);
	WriteTW88( 0xa7, 2);

	WriteTW88( 0xaa, 51+72 );
	WriteTW88(0x9e, 0x03 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x33 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x73 );
	WriteTW88(0xac, 8 );

	WriteTW88( 0x9f, 1 );			// enable Window #3
	WriteTW88( 0x9c, 0x0f);			// turn ON
}
*/

// below is for GenTex
/*
code BYTE	GridWindow[] = { 0xa5, 0, 0xa6, 0, 0xa7, 0, 0xa8, 0, 0xa9, 0x0, 0xab, 0x62 };
code BYTE	Grid0[] = { 0x06, 0x07, 0x0d, 0x0e, 0x0f,
						0x14, 0x15, 0x16, 0x1b, 0x1c,
						0x22, 0x23, 0x29, 0x2a, 0x2b, 
						0x30, 0x31, 0x32, 0x33, 0x38, 0x39, 0x3a, 0x3b };	// left 23
code BYTE	Grid1[] = { 0x00, 0x01, 0x08, 0x09, 0x0a,
						0x11, 0x12, 0x13, 0x1b, 0x1c,
						0x24, 0x25, 0x2c, 0x2d, 0x2e,
				     	0x34, 0x35, 0x36, 0x37, 0x3c, 0x3d, 0x3e, 0x3f }; // right 23
code unsigned char GridLUT[8] = { 0x00,0x1c,0x1c,0xfc,0xE0,0xE3,0xFC,0xFF };
void DisplayGrid( void )
{
BYTE	i, j;

	DownloadGridFont();
	WriteTW88( 0x94, 0x02 );		// clear OSD RAM clear
	for ( i=0; i<8; i++ ) {
		WriteTW88( 0x9c, i );	//select LUT
		WriteTW88( 0x9d, GridLUT[i] );
	}

	WriteTW88( 0x94, 0x80 );		//0000 1101 RAM Font select with same attribute
	for ( i=0; i < (72+51+45); i++ ) {		// clear with font '0'
		WriteTW88( 0x96, i );
		WriteTW88( 0x97, 0 );
		WriteTW88( 0x98, 0x70 );
	}
	i = 1;
	for ( j=0; j< sizeof(Grid0); j++ ) {		// display data for bottom
		WriteTW88( 0x96, Grid0[j] );	// set position
		WriteTW88( 0x97, i++ );
		WriteTW88( 0x98, (0x71 + Grid0[j]/16) );
	}
	for ( j=0; j< sizeof(Grid1); j++ ) {		// display data for left
		WriteTW88( 0x96, Grid1[j]+64 );	// set position
		WriteTW88( 0x97, i++ );
		WriteTW88( 0x98, (0x71 + Grid1[j]/16) );
	}

	WriteTW88( 0x9e, 0 );			// window #0 for Left
	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
	WriteTW88( 0xa0, 0 );
	WriteTW88( 0xa1, 19);
	WriteTW88( 0xa2, 56);
	WriteTW88( 0xa3, 8);
	WriteTW88( 0xa4, 8);
	WriteTW88(0x9e, 0x70 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x10 );
	WriteTW88(0xac, 4 );
	WriteTW88(0x9e, 0x20 );
	WriteTW88(0xac, 3 );
	WriteTW88(0x9e, 0x30 );
	WriteTW88(0xac, 2 );
	WriteTW88(0x9e, 0x40 );
	WriteTW88(0xac, 1 );

	WriteTW88( 0x9f, 1 );			// enable Window #0

	WriteTW88( 0x9e, 1 );		
	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
	WriteTW88( 0xa0, 0 );
	WriteTW88( 0xa1, 204);
	WriteTW88( 0xa2, 56);
	WriteTW88( 0xa3, 8);
	WriteTW88( 0xa4, 8);
	WriteTW88( 0xaa, 64 );
	WriteTW88(0x9e, 0x71 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x11 );
	WriteTW88(0xac, 4 );
	WriteTW88(0x9e, 0x21 );
	WriteTW88(0xac, 3 );
	WriteTW88(0x9e, 0x31 );
	WriteTW88(0xac, 2 );
	WriteTW88(0x9e, 0x41 );
	WriteTW88(0xac, 1 );
	WriteTW88( 0x9f, 1 );			// enable Window #1

//	WriteTW88( 0x9e, 3 );		
//	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
//		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
//	WriteTW88( 0xa0, 0 );
//	WriteTW88( 0xa1, 1);
//	WriteTW88( 0xa2, 1);
//	WriteTW88( 0xa3, 0x1a);
//	WriteTW88( 0xa4, 0x0d);
//	WriteTW88( 0xa5, 0xa1);
//	WriteTW88( 0xa6, 3);
//	WriteTW88( 0xa7, 2);

//	WriteTW88( 0xaa, 51+72 );
//	WriteTW88(0x9e, 0x03 );
//	WriteTW88(0xac, 8 );
//	WriteTW88(0x9e, 0x33 );
//	WriteTW88(0xac, 8 );
//	WriteTW88(0x9e, 0x73 );
//	WriteTW88(0xac, 8 );

//	WriteTW88( 0x9f, 1 );			// enable Window #3

	WriteTW88( 0x9c, 0x0f);			// turn ON
}
*/
// below is for Techwell Tool
/*
code BYTE	GridWindow[] = { 0xa5, 0, 0xa6, 0, 0xa7, 0, 0xa8, 0, 0xa9, 0x0, 0xab, 0x62 };

code unsigned char GridLUT[8] = { 0x00,0x1c,0x1c,0xfc,0xE0,0xE3,0xFC,0xFF };
void DisplayGrid( void )
{
BYTE	i, j, k;

	DownloadGridFont();
	WriteTW88( 0x94, 0x02 );		// clear OSD RAM clear
	for ( i=0; i<8; i++ ) {
		WriteTW88( 0x9c, i );	//select LUT
		WriteTW88( 0x9d, GridLUT[i] );
	}

	WriteTW88( 0x94, 0x80 );		//0000 1101 RAM Font select with same attribute
	for ( i=0; i < NofChars; i++ ) {		// clear with font '0'
		WriteTW88( 0x96, i );
		WriteTW88( 0x97, 0 );
		WriteTW88( 0x98, 0x70 );
	}
	i = 1;
	k = gridTWPos0[2]*gridTWPos0[3];
	for ( j=0; j< sizeof(gridTWChar); j++ ) {		// display data for all
		WriteTW88( 0x96, gridTWChar[j] );	// set position
		WriteTW88( 0x97, i++ );
		if ( gridTWChar[j] < k ) 
			WriteTW88( 0x98, (0x71 + gridTWChar[j]/(gridTWPos0[2]*2)) );			// can control how many lines for sam color
		else
			WriteTW88( 0x98, (0x71 + (gridTWChar[j]-k)/(gridTWPos1[2]*2)) );		// can control how many lines for sam color
	}


	
	WriteTW88( 0x9e, 0 );			// window #0 for Left
	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
	WriteTW88( 0xa0, 0 );
	WriteTW88( 0xa1, gridTWPos0[0]);
	WriteTW88( 0xa2, gridTWPos0[1]);
	WriteTW88( 0xa3, gridTWPos0[2]);
	WriteTW88( 0xa4, gridTWPos0[3]);
	WriteTW88(0x9e, 0x70 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x10 );
	WriteTW88(0xac, 4 );
	WriteTW88(0x9e, 0x20 );
	WriteTW88(0xac, 3 );
	WriteTW88(0x9e, 0x30 );
	WriteTW88(0xac, 2 );
	WriteTW88(0x9e, 0x40 );
	WriteTW88(0xac, 1 );

	WriteTW88( 0x9f, 1 );			// enable Window #0

	WriteTW88( 0x9e, 1 );		
	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
	WriteTW88( 0xa0, 0 );
	WriteTW88( 0xa1, gridTWPos1[0]);
	WriteTW88( 0xa2, gridTWPos1[1]);
	WriteTW88( 0xa3, gridTWPos1[2]);
	WriteTW88( 0xa4, gridTWPos1[3]);
	WriteTW88( 0xaa, 64 );
	WriteTW88(0x9e, 0x71 );
	WriteTW88(0xac, 8 );
	WriteTW88(0x9e, 0x11 );
	WriteTW88(0xac, 4 );
	WriteTW88(0x9e, 0x21 );
	WriteTW88(0xac, 3 );
	WriteTW88(0x9e, 0x31 );
	WriteTW88(0xac, 2 );
	WriteTW88(0x9e, 0x41 );
	WriteTW88(0xac, 1 );
	WriteTW88( 0x9f, 1 );			// enable Window #1

//	WriteTW88( 0x9e, 3 );		
//	for ( i=0; i<(sizeof(GridWindow)/2); i++ )
//		WriteTW88(GridWindow[i*2], GridWindow[i*2+1]);
//	WriteTW88( 0xa0, 0 );
//	WriteTW88( 0xa1, 1);
//	WriteTW88( 0xa2, 1);
//	WriteTW88( 0xa3, 0x1a);
//	WriteTW88( 0xa4, 0x0d);
//	WriteTW88( 0xa5, 0xa1);
//	WriteTW88( 0xa6, 3);
//	WriteTW88( 0xa7, 2);

//	WriteTW88( 0xaa, 51+72 );
//	WriteTW88(0x9e, 0x03 );
//	WriteTW88(0xac, 8 );
//	WriteTW88(0x9e, 0x33 );
//	WriteTW88(0xac, 8 );
//	WriteTW88(0x9e, 0x73 );
//	WriteTW88(0xac, 8 );

//	WriteTW88( 0x9f, 1 );			// enable Window #3

	WriteTW88( 0x9c, 0x0f);			// turn ON
}
*/
#if 0
void DisplayGrid( void )
{
BYTE	i, j, k;
WORD	offset;
BYTE 	*ptrFont, *ptrAttr;
WORD	cPos;

	DownloadGridFont();
	WriteTW88( 0x94, 0x02 );		// clear OSD RAM clear
	for ( i=0; i<8; i++ ) {
		WriteTW88( 0x9c, i );	//select LUT
		WriteTW88( 0x9d, LINE_45B_Info.LUT[i] );
	}

	WriteTW88( 0x94, 0x80 );
	//WriteTW88( 0x98, 0x74 );		// attribute B/C=7, F/C=1 with blink
	j = LINE_45B_Info.NChars;
	ptrFont = LINE_45B_Info.DisplayData;
	ptrAttr = LINE_45BAttr;
	if ( LINE_45B_Info.NChars > 0xff ) {
		i = 0;
		do {
			WriteTW88( 0x96, i );
			WriteTW88( 0x97, *ptrFont++ );	// set position
			WriteTW88( 0x98, *ptrAttr++ );
			i++;
		} while ( i != 0);
		WriteTW88( 0x95, ReadTW88(0x95)|1 );	//set start address
	}
	for ( i=0; i < j; i++ ) {		// clear with font '0'
		WriteTW88( 0x96, i );
		WriteTW88( 0x97,*ptrFont++ );	// set position
		WriteTW88( 0x98, *ptrAttr++ );
	}
/*	i = 1;
	ptrFont = LINE_45B_Info.CharPos;
	m = LINE_45B_Info.NFonts-1;
	for ( j=0; j<m; j++ ) {		// display data for all
		k = *ptrFont++;
		WriteTW88( 0x96, k );	// set position
		WriteTW88( 0x97, i++ );
		WriteTW88( 0x98, 0x70|LINE_45B_Info.WColors0[k/LINE_45B_Info.WPos0[2]] );
	}
*/
	cPos = 0;
	WriteTW88( 0x9e, 0 );			// window #0
	WriteTW88( 0xa5, 0 ); WriteTW88( 0xa6, 0 ); WriteTW88( 0xa7, 0 ); 
	WriteTW88( 0xa8, 0 ); WriteTW88( 0xa9, 0 ); WriteTW88( 0xab, 62 );
	offset = LINE_45B_Info.WPos0[0]; offset >>= 8;
	k = offset;
	offset = LINE_45B_Info.WPos0[1];
	offset >>= 8;
	offset <<= 4;
	k += offset;
	WriteTW88( 0xa0, k );
	WriteTW88( 0xa1, LINE_45B_Info.WPos0[0] );
	WriteTW88( 0xa2, LINE_45B_Info.WPos0[1] );
	WriteTW88( 0xa3, LINE_45B_Info.WPos0[2] );
	WriteTW88( 0xa4, LINE_45B_Info.WPos0[3] );
	cPos = LINE_45B_Info.WPos0[2];
	cPos *= LINE_45B_Info.WPos0[3];
	WriteTW88( 0xaa, 0 );
	WriteTW88( 0x9e, 0x00 );
	WriteTW88( 0xac, 8 );
	WriteTW88( 0x9e, 0x70 );
	WriteTW88( 0xac, 0 );
	WriteTW88( 0x9f, 1 );			// enable Window #0

	WriteTW88( 0x9e, 1 );			// window #1
	WriteTW88( 0xa5, 0 ); WriteTW88( 0xa6, 0 ); WriteTW88( 0xa7, 0 ); 
	WriteTW88( 0xa8, 0 ); WriteTW88( 0xa9, 0 ); WriteTW88( 0xab, 62 );
	offset = LINE_45B_Info.WPos1[0]; offset >>= 8;
	k = offset;
	offset = LINE_45B_Info.WPos1[1];
	offset >>= 8;
	offset <<= 4;
	k += offset;
	WriteTW88( 0xa0, k );
	WriteTW88( 0xa1, LINE_45B_Info.WPos1[0] );
	WriteTW88( 0xa2, LINE_45B_Info.WPos1[1] );
	WriteTW88( 0xa3, LINE_45B_Info.WPos1[2] );
	WriteTW88( 0xa4, LINE_45B_Info.WPos1[3] );

	if ( cPos > 0xff ) {
		WriteTW88( 0xa9, ReadTW88(0xa9) | 1 );
	}
	WriteTW88( 0xaa, cPos );
	offset = LINE_45B_Info.WPos1[2];
	offset *= LINE_45B_Info.WPos1[3];
	cPos += offset;
	WriteTW88( 0x9e, 0x01 );
	WriteTW88( 0xac, 8 );
	WriteTW88( 0x9e, 0x11 );
	WriteTW88( 0xac, 0 );
	WriteTW88( 0x9f, 1 );			// enable Window #1

	WriteTW88( 0x9e, 2 );			// window #2
	WriteTW88( 0xa5, 0 ); WriteTW88( 0xa6, 0 ); WriteTW88( 0xa7, 0 ); 
	WriteTW88( 0xa8, 0 ); WriteTW88( 0xa9, 0 ); WriteTW88( 0xab, 62 );
	offset = LINE_45B_Info.WPos2[0]; offset >>= 8;
	k = offset;
	offset = LINE_45B_Info.WPos2[1];
	offset >>= 8;
	offset <<= 4;
	k += offset;
	WriteTW88( 0xa0, k );
	WriteTW88( 0xa1, LINE_45B_Info.WPos2[0] );
	WriteTW88( 0xa2, LINE_45B_Info.WPos2[1] );
	WriteTW88( 0xa3, LINE_45B_Info.WPos2[2] );
	WriteTW88( 0xa4, LINE_45B_Info.WPos2[3] );

	if ( cPos > 0xff ) {
		WriteTW88( 0xa9, ReadTW88(0xa9) | 1 );
	}
	WriteTW88( 0xaa, cPos );
	offset = LINE_45B_Info.WPos2[2];
	offset *= LINE_45B_Info.WPos2[3];
	cPos += offset;
	WriteTW88( 0x9e, 0x02 );
	WriteTW88( 0xac, 8 );
	WriteTW88( 0x9e, 0x12 );
	WriteTW88( 0xac, 0 );
	WriteTW88( 0x9f, 1 );			// enable Window #2

	WriteTW88( 0x9e, 3 );			// window #3
	WriteTW88( 0xa5, 0 ); WriteTW88( 0xa6, 0 ); WriteTW88( 0xa7, 0 ); 
	WriteTW88( 0xa8, 0 ); WriteTW88( 0xa9, 0 ); WriteTW88( 0xab, 62 );
	offset = LINE_45B_Info.WPos3[0]; offset >>= 8;
	k = offset;
	offset = LINE_45B_Info.WPos3[1];
	offset >>= 8;
	offset <<= 4;
	k += offset;
	WriteTW88( 0xa0, k );
	WriteTW88( 0xa1, LINE_45B_Info.WPos3[0] );
	WriteTW88( 0xa2, LINE_45B_Info.WPos3[1] );
	WriteTW88( 0xa3, LINE_45B_Info.WPos3[2] );
	WriteTW88( 0xa4, LINE_45B_Info.WPos3[3] );

	if ( cPos > 0xff ) {
		WriteTW88( 0xa9, ReadTW88(0xa9) | 1 );
	}
	WriteTW88( 0xaa, cPos );
	WriteTW88( 0x9e, 0x03 );
	WriteTW88( 0xac, 8 );
	WriteTW88( 0x9e, 0x13 );
	WriteTW88( 0xac, 0 );
	WriteTW88( 0x9f, 1 );			// enable Window #3

	WriteTW88( 0x9c, 0x0f );			// turn ON
	WriteTW88( 0x95, ReadTW88(0x95)&0xfe );	//set start address

}
#endif


//*****************************************************************************
//
//	Functions for only CC.
//
//*****************************************************************************
//ljy052903: Only In CC 

//*****************************************************************************

     // Move to CC by Harry

//===============================================================================
//  Used OSD Menu 
//===============================================================================
//------------------------------------------------------------
void WriteStringToAddr(WORD addr, BYTE *str, BYTE cnt)
{
	//if( I2CAutoIncFlagOn==0 )
	WriteTW88(TW88_ENABLERAM, 0x04); // OSD RAM Auto Access Enable, ROMFONT Start Enable

	WriteTW88(TW88_OSDRAMADDRLO, addr);
	WriteI2Cn( TW88I2CAddress, TW88_OSDRAMDATAHI, str, cnt );

//	if( I2CAutoIncFlagOn==0 )
	WriteTW88(TW88_ENABLERAM, 0x00); // OSD RAM Auto Access Disable
}
#ifdef PAL_TV
void DrawAttrString(WORD addr, BYTE *Str, BYTE cnt)
{
//	if( I2CAutoIncFlagOn==0 )
	WriteTW88(TW88_ENABLERAM, 0x04); // OSD RAM Auto Access Enable
	WriteTW88(TW88_OSDRAMADDRLO, addr);
	WriteI2Cn( TW88I2CAddress, TW88_OSDRAMDATALO, Str, cnt );	// Attr

//	if( I2CAutoIncFlagOn==0 )
	WriteTW88(TW88_ENABLERAM, 0x00); // OSD RAM Auto Access Disable
}
#endif

void DrawAttrCnt(WORD addr, BYTE color, BYTE cnt)
{
	WriteTW88(TW88_ENABLERAM, 0x04);		// OSD RAM Auto Access Enable
	WriteTW88(TW88_OSDRAMADDRLO, addr);
	WriteI2CnD( TW88I2CAddress, TW88_OSDRAMDATALO, color, cnt );

	WriteTW88(TW88_ENABLERAM, 0x00);		// OSD RAM Auto Access Disable
}

void ClearDataCnt(WORD addr, BYTE cnt)
{
//	if( I2CAutoIncFlagOn==0 )
	WriteTW88(TW88_ENABLERAM, 0x04);		// OSD RAM Auto Access Enable
	WriteTW88(TW88_OSDRAMADDRLO, addr);
	WriteI2CnD( TW88I2CAddress, TW88_OSDRAMDATAHI, ' ', cnt );

//	if( I2CAutoIncFlagOn==0 )
	WriteTW88(TW88_ENABLERAM, 0x00);		// OSD RAM Auto Access Disable
}

//*****************************************************************************
//
//	Conversion Functions.
//
//*****************************************************************************
BYTE utoa(WORD value, BYTE *str, BYTE radix)
{
	BYTE cnt, *str1;
	WORD i, div;

	#ifdef DEBUG_OSD
	dPrintf("\r\n++(utoa):0x%x__", value);
	#endif

	str1 = str;
	cnt=0;
	if( radix==10) {
		for(div = 10000; div>=10; div/=10) {
			i = value/div;
			if( i ) {
				*str++ = i+'0';
				cnt++;
			}
			else if( cnt )		// 100, 200, 20,,,,
				*str++ = '0';

			value%=div;
		}
		*str++ = value+'0';
		*str = 0;
	}
	else if( radix==16) {
		for(div = 0x1000; div>=0x10; div/=0x10) {
			i = value/div;
			if( i ) {
				if( i>=0xa ) 
					*str++ = i-0xa+'A';
				else
					*str++ = i+'0';
				value%=div;
			}
		}
		if( value>=0xa ) 
			*str++ = value-0xa+'A';
		else
			*str++ = value+'0';
		*str = 0;
	}
	return 1;
}
BYTE strlen( BYTE *str )
{
	BYTE i=0;

	while( *str++ ) i++;
	return i;
}
//=============================================================================
//			Init Menu Window Data initialize 
//=============================================================================
#include "OsdInitTable.c"

void InitOSDWindow(BYTE *ptr)
{
	BYTE i, page;

	page = ReadTW88(0xff);
	WriteTW88( 0xff, (page&0xfe));
	//delay(2);		//Weylis 120307 for test
	WriteTW88(0xe0, ReadTW88(0xe0) & 0xef);

    i = 0;
    while(ptr[i]) {
		WriteI2Cn_(TW88I2CAddress, &ptr[i+1], ptr[i]);
		WriteI2Cn_(TW88I2CAddress, &ptr[i+1], 5);		// To set position LSB...
		//Printf("\r\nAddress=%02x,data=%02x",&ptr[i+1],ptr[i]);
        i += ptr[i] + 1;
    };

	WriteTW88(0xe0, ReadTW88(0xe0) | 0x10);
	WriteTW88( 0xff, page );
}



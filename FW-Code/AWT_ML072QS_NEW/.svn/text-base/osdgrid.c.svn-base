//osd_grid.c
// ver0.11 2/1x/2001 Change display format from hex to decimal
//	1.32	LJY11262001	.Add border features to OSD window
//	1.70	LJY05302003 .Support a menu with external OSD.
//	2.00	BYH05102007 .Support internal MCU, which connect with direct memoty bus
//						 It needs change whole ReadTW88, WriteTW88 to regTW88
#ifdef BANKING
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


BYTE GridOffset = 1;

extern data BYTE	code *ptrFont;

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
extern code struct MultiGridInfo  GMULTI_LL8_Info, GMULTI_LL7_Info, GMULTI_LL6_Info, GMULTI_LL5_Info, 
										GMULTI_LL4_Info, GMULTI_LL3_Info, GMULTI_LL2_Info, GMULTI_LL1_Info, GMULTI_LL0_Info, 
										GMULTI_RR1_Info, GMULTI_RR2_Info, GMULTI_RR3_Info, GMULTI_RR4_Info, 
										GMULTI_RR5_Info, GMULTI_RR6_Info, GMULTI_RR7_Info, GMULTI_RR8_Info,
										Message_Info, Chinese_Info, Japanese_Info, Korean_Info;
code struct MultiGridInfo  *MGrids[21] ={ &GMULTI_LL8_Info, &GMULTI_LL7_Info, &GMULTI_LL6_Info, &GMULTI_LL5_Info, 
										&GMULTI_LL4_Info, &GMULTI_LL3_Info, &GMULTI_LL2_Info, &GMULTI_LL1_Info, &GMULTI_LL0_Info, 
										&GMULTI_RR1_Info, &GMULTI_RR2_Info, &GMULTI_RR3_Info, &GMULTI_RR4_Info, 
										&GMULTI_RR5_Info, &GMULTI_RR6_Info, &GMULTI_RR7_Info, &GMULTI_RR8_Info };
void DownloadMessageFont(void)
{
register	BYTE i, j, m;

	//WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 
	REG9b = 0xff; // Set Color Font Start Address. 

	//WriteTW88(TW88_ENABLERAM, ReadTW88(TW88_ENABLERAM) | 0x01);		// Font RAM access mode ON
	REG94 |= 0x01;		// Font RAM access mode ON
	ptrFont = Message_Info.FontData;
	m = Message_Info.NFonts;
	for(i=0; i< m ; i++) {		// Techwell case 48 chars
		REG99 = i+190;
		for ( j = 0; j<27; j++ ) {
			REG9a = *ptrFont++;
		}
	}
	//WriteTW88(TW88_ENABLERAM, (ReadTW88(TW88_ENABLERAM) & 0xfe));		// OSD RAM access mode OFF
	REG94 &= 0xfe;		// Font RAM access mode ON
}
void DownloadChineseFont(void)
{
register	BYTE i, j, m;

	//WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 
	REG9b = 0xff; // Set Color Font Start Address. 

	//WriteTW88(TW88_ENABLERAM, ReadTW88(TW88_ENABLERAM) | 0x01);		// Font RAM access mode ON
	REG94 |= 0x01;		// Font RAM access mode ON
	ptrFont = Chinese_Info.FontData;
	m = Chinese_Info.NFonts;
	for(i=0; i< m ; i++) {		// Techwell case 48 chars
		REG99 = i+190;
		for ( j = 0; j<27; j++ ) {
			REG9a = *ptrFont++;
		}
	}
	//WriteTW88(TW88_ENABLERAM, (ReadTW88(TW88_ENABLERAM) & 0xfe));		// OSD RAM access mode OFF
	REG94 &= 0xfe;		// Font RAM access mode ON
}
void DownloadJapaneseFont(void)
{
register	BYTE i, j, m;

	//WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 
	REG9b = 0xff; // Set Color Font Start Address. 

	//WriteTW88(TW88_ENABLERAM, ReadTW88(TW88_ENABLERAM) | 0x01);		// Font RAM access mode ON
	REG94 |= 0x01;		// Font RAM access mode ON
	ptrFont = Japanese_Info.FontData;
	m = Japanese_Info.NFonts;
	for(i=0; i< m ; i++) {		// Techwell case 48 chars
		REG99 = i+190;
		for ( j = 0; j<27; j++ ) {
			REG9a = *ptrFont++;
		}
	}
	//WriteTW88(TW88_ENABLERAM, (ReadTW88(TW88_ENABLERAM) & 0xfe));		// OSD RAM access mode OFF
	REG94 &= 0xfe;		// Font RAM access mode ON
}
void DownloadKoreanFont(void)
{
register	BYTE i, j, m;

	//WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 
	REG9b = 0xff; // Set Color Font Start Address. 

	//WriteTW88(TW88_ENABLERAM, ReadTW88(TW88_ENABLERAM) | 0x01);		// Font RAM access mode ON
	REG94 |= 0x01;		// Font RAM access mode ON
	ptrFont = Korean_Info.FontData;
	m = Korean_Info.NFonts;
	for(i=0; i< m ; i++) {		// Techwell case 48 chars
		REG99 = i+190;
		for ( j = 0; j<27; j++ ) {
			REG9a = *ptrFont++;
		}
	}
	//WriteTW88(TW88_ENABLERAM, (ReadTW88(TW88_ENABLERAM) & 0xfe));		// OSD RAM access mode OFF
	REG94 &= 0xfe;		// Font RAM access mode ON
}
void DownloadMGridFont(BYTE n)
{
register	BYTE i, j, k, m;

	//WriteTW88(TW88_MULTISTART, 0xff); // Set Color Font Start Address. 
	REG9b = 0xff; // Set Color Font Start Address. 

	GridOffset ^= 1;	// toggle
	if ( GridOffset )
		k = 100;
	else
		k = 0;
	ptrFont = MGrids[n]->FontData;
	m = MGrids[n]->NFonts;
	//WriteTW88(TW88_ENABLERAM, ReadTW88(TW88_ENABLERAM) | 0x01);		// Font RAM access mode ON
	REG94 |= 0x01;		// Font RAM access mode ON
	for(i=0; i< m ; i++) {		// Techwell case 48 chars
		REG99 = i+k;
		for ( j=0; j<27; j++ ) {
			REG9a = *ptrFont++;
		}
	}
	//WriteTW88(TW88_ENABLERAM, (ReadTW88(TW88_ENABLERAM) & 0xfe));		// OSD RAM access mode OFF
	REG94 &= 0xfe;		// Font RAM access mode ON
}
void DisplayMGrid( BYTE n )
{
register BYTE	i, j, k, m;
register WORD	offset;

static bit init = 0;

	DownloadMGridFont(n);
	ptrFont = MGrids[n]->LUT;
	for ( i=0; i<8; i++ ) {
		REG9c = i;	//select LUT
		REG9d = *ptrFont++;
	}

	if (GridOffset)
		m = 100;
	else
		m = 0;

	i = REG95 & 0x40;
	while (( REG95 & 0x40 ) == i);
	REG9e = 0;			// window #0 select
	REG9f = 0;		// disable
	REG9e = 1;			// window #1 select
	REG9f = 0;		// disable
/*
	REG94 = 0x8c;		// font RAM select, auto mode
	REG98 = 0x70;		// attribute B/C=7, F/C=0
	j = MGrids[n]->NChars;
	for ( i=0; i < j; i++ ) {		// clear with font '0'
		REG96 = i ;	// set position
		REG97 = 0;
	}

//	REG94, 0x02 );		// clear OSD RAM clear
	i = 1;
	k = MGrids[n]->WPos0[2]*MGrids[n]->WPos0[3];
	REG94 = 0x8c;		// font RAM select, auto mode
	REG98 = 0x74;		// attribute B/C=7, F/C=4
	ptrFont = MGrids[n]->CharPos;
	i+=m;
	m = MGrids[n]->NFonts-1;
	for ( j=0; j<m; j++ ) {		// display data for all
		REG96 = *ptrFont++;	// set position
		REG97 = i++;
	}
/*/
	k = MGrids[n]->WPos0[2]*MGrids[n]->WPos0[3];
	REG94 = 0x8C;
	REG98 = 0x74;		// attribute B/C=7, F/C=0
	j = MGrids[n]->NChars;
	ptrFont = MGrids[n]->DisplayData;
	for ( i=0; i < j; i++ ) {		// clear with font '0'
		REG96 = i;
		REG97 = m+*ptrFont++ ;	// set position
	}
//*/
	i = PWIDTH / 320;
	offset = PWIDTH % 320;
	offset >>= 1;
	j = (PHEIGHT+20) / 240;
	j--;
	i--;
	REG9e = 0;			// window #0 select
	if ( init==0 ) {
		REGa5 = 0; REGa6 = 0; REGa7 = 0; REGa8 = 0; REGa9 = ((i<<4)|(j<<6)); REGab = 62;
	}
	offset += MGrids[n]->WPos0[0] * (i+1);
	REGa0 = offset >> 8;
	REGa1 = offset;
	REGa2 = MGrids[n]->WPos0[1] * (j+1);
	REGa3 = MGrids[n]->WPos0[2];
	REGa4 = MGrids[n]->WPos0[3];
	REGaa = 0;
	REG9e = 0x70;		// window 0 color 7
	REGac = 8;		// alpha blend maximum
	REG9e = 0x40;		// window 0 color 4
	REGac = 1;		// alpha blend half

//	REG9f = 1;			// enable Window #1

	REG9e = 1;		
	if ( init==0 ) {
		REGa5 = 0; REGa6 = 0; REGa7 = 0; REGa8 = 0; REGa9 = ((i<<4)|(j<<6)); REGab = 62;
	}
	offset = PWIDTH % 320;
	offset >>= 1;
	offset += MGrids[n]->WPos1[0] * (i+1);
	REGa0 = offset >> 8;
	REGa1 = offset;
	REGa0 = 0;
	REGa2 = MGrids[n]->WPos1[1] * (j+1);
	REGa3 = MGrids[n]->WPos1[2];
	REGa4 = MGrids[n]->WPos1[3];
	REGaa = k;
	REG9e = 0x71;		// window 1 color 7
	REGac = 8;		// alpha blend maximum
	REG9e = 0x41;		// window 1 color 4
	REGac = 1;		// alpha blend half
//	REG9f = 1;			// enable Window #1

	i = REG95 & 0x40;
	while (( REG95 & 0x40 ) == i);
	REG9e = 0;			// window #0 select
	REG9f = 1;		// disable
	REG9e = 1;			// window #1 select
	REG9f = 1;		// disable

	REG9c = 0x0f;			// turn ON
	init = 1;
}

void DisplayMessage( void )
{
register BYTE	i, j, k, m, offset;

	DownloadMessageFont();
	for ( i=0; i<8; i++ ) {
		REG9c = i;	//select LUT
		REG9d = Message_Info.LUT[i];
	}

	REG94 = 0x8C;
	REG98 = 0x79;		// attribute B/C=7, F/C=1 with blink
	j = Message_Info.NChars;
	ptrFont = Message_Info.DisplayData;
	m = 190;
	for ( i=0; i < j; i++ ) {		// clear with font '0'
		REG96 = i+m;
		REG97 = m+*ptrFont++ ;	// set position
	}

	i = PWIDTH / 320;
	offset = PWIDTH % 320;
	offset >>= 1;
	j = (PHEIGHT+20) / 240;
	j--;
	i--;
	REG9e = 3;			// window #3 for Message
	REGa5 = 0; REGa6 = 0; REGa7 = 0; REGa8 = 0; REGa9 = ((i<<4)|(j<<6)); REGab = 62;
	k = 0;
	if ( j )	// vertical
		k = (Message_Info.WPos0[1] >> 4) * (j+1);
	k &= 0x30;
	REGa0 = k;
	REGa1 = Message_Info.WPos0[0] * (i+1)+ offset;
	REGa2 = Message_Info.WPos0[1] * (j+1);
	REGa3 = Message_Info.WPos0[2];
	REGa4 = Message_Info.WPos0[3];

	REGaa = m;
	REG9e = 0x73;
	REGac = 8;
	REG9e = 0x13;
	REGac = 0;
	REG9f = 1;			// enable Window #3

	REG9c = 0x0f;			// turn ON
}
void DisplayChinese( void )
{
register BYTE	i, j, k, m, offset;

	DownloadChineseFont();
	for ( i=0; i<8; i++ ) {
		REG9c = i;	//select LUT
		REG9d = Chinese_Info.LUT[i];
	}

	REG94 = 0x8C;
	REG98 = 0x79;		// attribute B/C=7, F/C=1 with blink
	j = Chinese_Info.NChars;
	ptrFont = Chinese_Info.DisplayData;
	m = 190;
	for ( i=0; i < j; i++ ) {		// clear with font '0'
		REG96 = i+m;
		REG97 = m+*ptrFont++ ;	// set position
	}

	i = PWIDTH / 320;
	offset = PWIDTH % 320;
	offset >>= 1;
	j = (PHEIGHT+20) / 240;
	j--;
	i--;
	REG9e = 3;			// window #3 for Message
	REGa5 = 0; REGa6 = 0; REGa7 = 0; REGa8 = 0; REGa9 = ((i<<4)|(j<<6)); REGab = 62;
	k = 0;
	if ( j )	// vertical
		k = (Chinese_Info.WPos0[1] >> 4) * (j+1);
	k &= 0x30;
	REGa0 = k;
	REGa1 = Chinese_Info.WPos0[0] * (i+1)+ offset;
	REGa2 = Chinese_Info.WPos0[1] * (j+1);
	REGa3 = Chinese_Info.WPos0[2];
	REGa4 = Chinese_Info.WPos0[3];

	REGaa = m;
	REG9e = 0x73;
	REGac = 8;
	REG9e = 0x13;
	REGac = 0;
	REG9f = 1;			// enable Window #3

	REG9c = 0x0f;			// turn ON
}
void DisplayJapanese( void )
{
register BYTE	i, j, k, m, offset;

	DownloadJapaneseFont();
	for ( i=0; i<8; i++ ) {
		REG9c = i;	//select LUT
		REG9d = Japanese_Info.LUT[i];
	}

	REG94 = 0x8C;
	REG98 = 0x79;		// attribute B/C=7, F/C=1 with blink
	j = Japanese_Info.NChars;
	ptrFont = Japanese_Info.DisplayData;
	m = 190;
	for ( i=0; i < j; i++ ) {		// clear with font '0'
		REG96 = i+m;
		REG97 = m+*ptrFont++ ;	// set position
	}

	i = PWIDTH / 320;
	offset = PWIDTH % 320;
	offset >>= 1;
	j = (PHEIGHT+20) / 240;
	j--;
	i--;
	REG9e = 3;			// window #3 for Message
	REGa5 = 0; REGa6 = 0; REGa7 = 0; REGa8 = 0; REGa9 = ((i<<4)|(j<<6)); REGab = 62;
	k = 0;
	if ( j )	// vertical
		k = (Japanese_Info.WPos0[1] >> 4) * (j+1);
	k &= 0x30;
	REGa0 = k;
	REGa1 = Japanese_Info.WPos0[0] * (i+1)+ offset;
	REGa2 = Japanese_Info.WPos0[1] * (j+1);
	REGa3 = Japanese_Info.WPos0[2];
	REGa4 = Japanese_Info.WPos0[3];

	REGaa = m;
	REG9e = 0x73;
	REGac = 8;
	REG9e = 0x13;
	REGac = 0;
	REG9f = 1;			// enable Window #3

	REG9c = 0x0f;			// turn ON
}
void DisplayKorean( void )
{
register BYTE	i, j, k, m, offset;

	DownloadKoreanFont();
	for ( i=0; i<8; i++ ) {
		REG9c = i;	//select LUT
		REG9d = Korean_Info.LUT[i];
	}

	REG94 = 0x8C;
	REG98 = 0x79;		// attribute B/C=7, F/C=1 with blink
	j = Korean_Info.NChars;
	ptrFont = Korean_Info.DisplayData;
	m = 190;
	for ( i=0; i < j; i++ ) {		// clear with font '0'
		REG96 = i+m;
		REG97 = m+*ptrFont++ ;	// set position
	}

	i = PWIDTH / 320;
	offset = PWIDTH % 320;
	offset >>= 1;
	j = (PHEIGHT+20) / 240;
	j--;
	i--;
	REG9e = 3;			// window #3 for Message
	REGa5 = 0; REGa6 = 0; REGa7 = 0; REGa8 = 0; REGa9 = ((i<<4)|(j<<6)); REGab = 62;
	k = 0;
	if ( j )	// vertical
		k = (Korean_Info.WPos0[1] >> 4) * (j+1);
	k &= 0x30;
	REGa0 = k;
	REGa1 = Korean_Info.WPos0[0] * (i+1)+ offset;
	REGa2 = Korean_Info.WPos0[1] * (j+1);
	REGa3 = Korean_Info.WPos0[2];
	REGa4 = Korean_Info.WPos0[3];

	REGaa = m;
	REG9e = 0x73;
	REGac = 8;
	REG9e = 0x13;
	REGac = 0;
	REG9f = 1;			// enable Window #3

	REG9c = 0x0f;			// turn ON
}
void DisplayGridBank0( BYTE n )
{
	DisplayMGrid(n);
}

void DisplayGridBank1( BYTE n )
{
	DisplayMGrid(n);
}
#endif

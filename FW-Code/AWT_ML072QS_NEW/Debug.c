
#include "config.h"
#include "typedefs.h"
#include "main.h"

#include "reg.h"
#include "debug.h"
#include "osdbasic.h"
#include "osdmenu.h"
#include "dispinfo.h"
#include "I2C.h"
#include "printf.h"
#include "panel.h"

#include "keyremo.h"
#include "regmap.h"

#ifdef SUPPORT_DEBUG

#define DEBUGWIN			8
#define DEBUGWIN_ADDR		350

static DATA BYTE Slave=TW88I2CAddress, Index=0, Bdata=0;
bit Debug_On=0;

static	BYTE Debug_index=0;
extern	bit   I2CAutoIncFlagOn ;

CODE BYTE	DebugWindowInit[] = {
	//----- Input Selection : Zoom 2
	17,
	OSD_Win_Num				( BACK_COLOR|DEBUGWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
//	OSD_Win_Start			( 20, 15 ),	// 3 bytes
	OSD_Win_Start			( 20, (PVR_-(18*6))),
	OSD_Win_Width			( 25 ),
	OSD_Win_Height			( 2 ),
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(13) ),
	OSD_Win_VBorder			( WIN_V_BD_W(10) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(10) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(DEBUGWIN_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 4 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0	// End of Data
};

CODE BYTE Debug_Str[][25] = {
	" Addr Idx Data Bit       ",
	" 88   00  00   0000 0000 "   
};

CODE BYTE Cursor_Point[] = {
	1, 2, 6, 7, 10, 11, 15, 16, 17, 18, 20, 21, 22, 23 
};

CODE BYTE Digit_Str[] = {
	'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

void DebugWindowControl (void) {


	if( Debug_On ) {
		Debug_On = 0;
		ShowOSDWindow(DEBUGWIN,FALSE);
		return;
	}
	
	Debug_On = 1;
	Change_OSDColorLookup();
	InitOSDWindow(DebugWindowInit);

	DrawAttrCnt(DEBUGWIN_ADDR, DEFAULT_COLOR, 25 );	// Clear color
	WriteTW88(TW88_ENABLERAM, 0x24);		// OSD RAM Auto Access Enable
	I2CAutoIncFlagOn = 1;
	WriteStringToAddr(DEBUGWIN_ADDR, Debug_Str[0], 25 );
	I2CAutoIncFlagOn = 0;
	DrawAttrCnt(DEBUGWIN_ADDR+25, DEFAULT_COLOR, 25 );	// Clear color
	WriteStringToAddr(DEBUGWIN_ADDR+25, Debug_Str[1], 25 ); 

	ShowOSDWindow(DEBUGWIN,TRUE);
	ShowOSDWindowAll(1);

	Debug_index = 2;

	Bdata = ReadI2C(Slave,Index);

	Draw_Debug_Char();

	DrawAttrCnt(DEBUGWIN_ADDR+25+Cursor_Point[Debug_index], BG_COLOR_YELLOW|CH_COLOR_BLUE, 1 );	// Clear color

}

void Draw_Debug_Char(void)
{
	BYTE i,j;
	BYTE mstr[10];

	i = Slave;
	mstr[0] = Digit_Str[i>>4 & 0x0f] ;
	mstr[1] = Digit_Str[i&0x0f];
	mstr[2] = 0;
	WriteStringToAddr(DEBUGWIN_ADDR+25+1, mstr, 2 );

	i = Index;
	mstr[0] = Digit_Str[i>>4 & 0x0f] ;
	mstr[1] = Digit_Str[i&0x0f];
	mstr[2] = 0;
	WriteStringToAddr(DEBUGWIN_ADDR+25+6, mstr, 2 );

	i = Bdata;
	mstr[0] = Digit_Str[i>>4 & 0x0f] ;
	mstr[1] = Digit_Str[i&0x0f];
	mstr[2] = 0;
	WriteStringToAddr(DEBUGWIN_ADDR+25+10, mstr, 2 );

	i = Bdata;
	for (j=0; j<9 ;j++ )
	{
		mstr[j] = i&0x80? '1':'0';  
		i = i<<1;
		if(j==3) mstr[++j] = ' ';
		//Printf("\n\r i:%2x mstr[%d]: %s", (WORD)i, (WORD)j, mstr);

	}
	mstr[9] = 0;
	//Printf("\n\r Bdata:%2x  mstr: %s", (WORD)Bdata, mstr);
	WriteStringToAddr(DEBUGWIN_ADDR+25+15, mstr, 9 );

}

void DebugWindowCursor( BYTE flag ) {
	 
	if( flag == UP ) Debug_index = (Debug_index + 1) % 14;
	else Debug_index = (Debug_index+14-1)%14;

	DrawAttrCnt(DEBUGWIN_ADDR+25, DEFAULT_COLOR, 25 );	// Clear color
	DrawAttrCnt(DEBUGWIN_ADDR+25+Cursor_Point[Debug_index], BG_COLOR_YELLOW|CH_COLOR_BLUE, 1 );	// Clear color

}

void DebugWindowData( BYTE flag ) {
	
	BYTE i;
	int inc;

	switch(Debug_index){
	case 0: i = (flag == UP )? +0x10: -0x10;	
			i = i + (Slave&0xf0  );
			i &= 0xf0;
			Slave = i | (Slave&0x0f);
			break;	

	case 1: i = (flag == UP )? +1: -1;	
			i = i + (Slave&0x0f  );
			i &= 0x0f;
			Slave = i | (Slave&0xf0);
			break;	
	case 2: i = (flag == UP )? +0x10: -0x10;	
			i = i + (Index&0xf0  );
			i &= 0xf0;
			Index = i | (Index&0x0f);
			break;	
	case 3:  i = (flag == UP )? +1: -1;	
			i = i + (Index&0x0f  );
			i &= 0x0f;
			Index = i | (Index&0xf0);
			break;
	case 4:  i = (flag == UP )? +0x10: -0x10;	
			i = i + (Bdata&0xf0  );
			i &= 0xf0;
			Bdata = i | (Bdata&0x0f);
			break;	
	case 5:  i = (flag == UP )? +1: -1;	
			i = i + (Bdata&0x0f  );
			i &= 0x0f;
			Bdata = i | (Bdata&0xf0);
			break;
	case 6: 
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
			inc = Debug_index - 6;
			inc = 0x80>>inc;
			Bdata = Bdata ^ inc;
			//Printf("\n\r inc:%2x  Bdata:%2x ", (WORD)inc, (WORD)Bdata );
			WriteI2C(Slave, Index, Bdata);
			Draw_Debug_Char();
			delay(50);

			Bdata = ReadI2C(Slave, Index);
			break;	
	}
 
	Draw_Debug_Char();

}

void Debug_Write(void)
{
	WriteI2C(Slave, Index, Bdata);
}

void Debug_Read(void)
{
	Bdata = ReadI2C(Slave, Index);
	Draw_Debug_Char();
}
#endif // DEBUG_OSDMODE

#ifdef CHIP_MANUAL_TEST

extern 	bit		RepeatKey;
		BYTE	ManualFrequency;
		bit		OnChipTest=0;


BYTE DelaynCheck(void)
{
	BYTE ret=FALSE;
	WORD i;

	for(i=ManualFrequency*10; i>0; i--){
		delay(10);

		#ifdef SERIAL
			if( RS_ready() ) { ret=TRUE;  break; }
		#endif
	}

	return ret;
}

void ChipManualTest(void)
{

	if(OnChipTest!=1) return;
	OnChipTest = 0;

	Printf("\r\nPush any key if manual test stop.");
/*
	#ifdef INTERNAL_MCU
	ChangeInput(COMPOSITE);			// Input - Input Source Change Key
    while(1) {
		if( DelaynCheck() ) break;
		TestRAMFont();
	}
	#endif
*/	
	ChangeInput(CH_TW2835);			// Input - Input Source Change Key
     while(1) {
		/*
		WriteDecoder( INFORM, ReadDecoder(INFORM) | 0x01 );
		WriteDecoder( ACNTL, ReadDecoder(ACNTL) & 0xfe );
		
		//WriteDecoder( G_GAIN,  0x80 );
		WriteDecoder( SCrGAIN, 0x40 );
		WriteDecoder( SCrGAIN, 0x40 );
		WriteDecoder( RGBCONTROL, 0x03 );
		WriteDecoder( RG BMISC, 0x05 );
		
		delay(10+10);
		*/
 
		if( DelaynCheck() ) break;
		#ifdef SUPPORT_SVIDEO
		ChangeInput(SVIDEO);			// Input - Input Source Change Key
		if( DelaynCheck() ) break;
		#endif
		#ifdef SUPPORT_COMPONENT			// support component analog to decoder
		ChangeInput(COMPONENT);			// Input - Input Source Change Key
		if( DelaynCheck() ) break;
		#endif
		#ifdef SUPPORT_DTV			// support component analog to decoder
		ChangeInput(DTV);			// Input - Input Source Change Key
		if( DelaynCheck() ) break;
		#endif
		#ifdef SUPPORT_PC			// support component analog to decoder
		ChangeInput(PC);			// Input - Input Source Change Key
		if( DelaynCheck() ) break;
		#endif
		#ifdef SUPPORT_DVI
		ChangeInput(DIGITALVGA);			// Input - Input Source Change Key
		if( DelaynCheck() ) break;
		#endif
		ChangeInput(CH_TW2835);			// Input - Input Source Change Key
		ActionRemo( REMO_MENU, RepeatKey );
		if( DelaynCheck() ) break;
		TestRAMFont();
		/*
		WriteDecoder( INFORM, ReadDecoder(INFORM) | 0x01 );
		WriteDecoder( ACNTL, ReadDecoder(ACNTL) & 0xfe );
		
		//WriteDecoder( G_GAIN,  0x80 );
		WriteDecoder( SCrGAIN, 0x40 );
		WriteDecoder( SCrGAIN, 0x40 );
		WriteDecoder( RGBCONTROL, 0x03 );
		WriteDecoder( RGBMISC, 0x05 );
		
		delay(10+10);
		
		delay(20+10);
		*/
	 }

	Puts("\r\nExiting manual test......");
}
#endif

/*#include "config.h"
#include "panel.h"
#include "osdmenu.h"
*/
//*****************************************************************************
//
//           OSD Window Initialization Table
//
//*****************************************************************************
#ifdef SUPPORT_KRS_OSDDEMO

#define OSDRam_Start_Address 0x01
#define Left_Start_Addr		 OSDRam_Start_Address+30//60
#define Right_Start_Addr	 Left_Start_Addr+63
#define Freq_Start_Addr		 Right_Start_Addr+22

#define WIN4	4
#define WIN3	3
#define WIN2	2
#define WIN1	1
//=============================================================================
CODE BYTE Init_KRS_OSD_Demo[]={ 
	//----- Title Window
	17,                           
	OSD_Win_Num				( WIN4 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0), (0) ), // 3 bytes
	OSD_Win_Width			( 15 ),//30 ), 
	OSD_Win_Height			( 14 ), 
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0x1c) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x07) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx2), WIN_SADDR(OSDRam_Start_Address) ),	//25=MENU_WIDTH// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(8) ),
	OSD_Win_Blending		( 0 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
	//----- Left Window
	17,
	OSD_Win_Num				( WIN3 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (5), (0x2b) ), // 3 bytes
	OSD_Win_Width			( 9 ),
	OSD_Win_Height			( 7 ),
	OSD_Win_Border			(0),
	OSD_Win_HBorder			( WIN_H_BD_W(0x19) ),
	OSD_Win_VBorder			( WIN_V_BD_W(10) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(2) | WIN_CH_VSPACE(0x0d) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(Left_Start_Addr) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(4) ),
	OSD_Win_Blending		( 0 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	//----- Right Window
	17,
	OSD_Win_Num				( WIN2 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0xb3), (0x2b) ), // 3 bytes
	OSD_Win_Width			( 0x16 ), //MENU_WIDTH
	OSD_Win_Height			( 7 ),	// MENU_HEIGHT
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(10) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0x0) | WIN_CH_VSPACE(0xd) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(Right_Start_Addr) ),	//25=MENU_WIDTH// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(8) ),
	OSD_Win_Blending		( 0 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	//----- Freq Window
	17,
	OSD_Win_Num				( WIN1 ),	// 2 bytes
	OSD_Win_Attr			( BG_COLOR_CYAN|WIN_EN0 ),
	OSD_Win_Start			( (0xb3), (0x4c) ), // 3 bytes
	OSD_Win_Width			( 15 ),
	OSD_Win_Height			( 2 ),
	OSD_Win_Border			( WIN_BD_EN0 | BG_COLOR_CYAN | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0x2a) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x3e) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(Freq_Start_Addr) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
};
/*===========================================================================*/
// display char. set
CODE BYTE KRSOSD_FM1[]={ RAMFONT,0x19,0x1a,0x1d,0x1e,0x05,0x06,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
// 								0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,	
								 0x1b,0x1c,0x1f,0x20,0x07,0x08,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
 //								0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,	
//						 ROMFONT,
	0
	};
CODE BYTE KRSOSD_Channel[]={ RAMFONT,
										 0x1c,0x2b,0x2c,0x2d,0x2e,0x2e,0x2f,0x30,0x1c,
//						 ROMFONT,' ',
	0
	};
CODE BYTE KRSOSD_Selected[]={ RAMFONT,
								         0x22,0x21,0x25,0x31,0x26,0x27,0x28,0x29,0x2a,
//						 ROMFONT,' ',
	};
CODE BYTE KRSOSD_ChannelList[]={ RAMFONT,
								         0x22,0x21,0x25,0x31,0x26,0x26,0x28,0x29,0x2a,
								         0x22,0x21,0x25,0x31,0x26,0x25,0x28,0x29,0x2a,
								         0x22,0x21,0x25,0x31,0x26,0x24,0x28,0x29,0x2a,
								         0x22,0x21,0x25,0x31,0x26,0x23,0x28,0x29,0x2a,
								         0x22,0x21,0x25,0x31,0x26,0x22,0x28,0x29,0x2a,
//						 ROMFONT,' ',
	0
	};
CODE BYTE KRSOSD_ST_AF_TP[]={ RAMFONT,0x33,0x34,0x1c,0x35,0x36,0x1c,0x34,0x37,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
								         0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
								         0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
								         0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
								         0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
								         0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
								         0x38,0x39,0x30,0x3a,0x3d,0x3d,0x3d,0x3d,0x3d,0x3d,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x43,
//						 ROMFONT,' '
	0
	};

CODE BYTE KRSOSD_SEL_FREQ[]={ RAMFONT,   0x05,0x06,0x01,0x02,0x11,0x12,0x1c,0x15,0x16,0x15,0x16,0x1c,0x1c,0x1c,0x1c,
								         0x07,0x08,0x03,0x04,0x13,0x14,0x32,0x17,0x18,0x17,0x18,0x1c,0x28,0x29,0x2a,
//						 ROMFONT,' ',
	0
	};


void DisplayKRSOSD(void)
{
	CODE_P BYTE *str;
	BYTE i;

	InitOSDWindow(Init_KRS_OSD_Demo);

	ClearDataCnt(OSDRam_Start_Address, 240);
	DrawAttrCnt(OSDRam_Start_Address, CH_COLOR_CYAN, 30);	 
	DrawAttrCnt(Left_Start_Addr, CH_COLOR_GREEN|BG_COLOR_MAGENTA, 9 );
	DrawAttrCnt(Left_Start_Addr+9, CH_COLOR_YELLOW|BG_COLOR_CYAN, 9 );
	DrawAttrCnt(Left_Start_Addr+18, CH_COLOR_WHITE|BG_COLOR_MAGENTA, 9*5 );
	DrawAttrCnt(Right_Start_Addr, CH_COLOR_WHITE|BG_COLOR_MAGENTA, 22*7 );
	DrawAttrCnt(Freq_Start_Addr, CH_COLOR_WHITE|BG_COLOR_CYAN, 30 );

	str = KRSOSD_FM1;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address, str, 30);
	Printf("i=%d  ", (WORD)i);

	str = KRSOSD_Channel;
	i=strlen(str);
	WriteStringToAddr(Left_Start_Addr, str, i);

	str = KRSOSD_Selected;
	i=strlen(str);
	WriteStringToAddr(Left_Start_Addr+9, str, i);

	str = KRSOSD_ChannelList;
	i=strlen(str);
	WriteStringToAddr(Left_Start_Addr+18, str, i);

	str = KRSOSD_ST_AF_TP;
	i=strlen(str);
	WriteStringToAddr(Right_Start_Addr, str, i);

	str = KRSOSD_SEL_FREQ;
	i=strlen(str);
	WriteStringToAddr(Freq_Start_Addr, str, i);

	for(i=OSDCURSORWINDOW; i<=OSDMENU_TITLEWIN; i++) {
		ShowOSDWindow_TW88(i,TRUE);
	}

	ShowOSDWindowAll(1);
	
}


#endif
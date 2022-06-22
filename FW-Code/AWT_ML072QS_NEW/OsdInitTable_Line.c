/*#include "config.h"
#include "panel.h"
#include "osdmenu.h"
*/
//*****************************************************************************
//
//           OSD Window Initialization Table
//
//*****************************************************************************
#ifdef SUPPORT_LINE_OSDDEMO

#define OSDRam_Start_Address 0x01
#define Left_Start_Addr		 OSDRam_Start_Address+30//60
#define Right_Start_Addr	 Left_Start_Addr+63
#define Freq_Start_Addr		 Right_Start_Addr+22

#define WIN4	4
#define WIN3	3
#define WIN2	2
#define WIN1	1
//=============================================================================

#ifdef HITACHI_TX09D73
CODE BYTE Init_Line_OSD_Demo[]={ 
	//----- Top Window
	17,                           
	OSD_Win_Num				( WIN4 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0x2e), (0x37) ), // 3 bytes
	OSD_Win_Width			( 13 ),
	OSD_Win_Height			( 5 ), 
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(OSDRam_Start_Address) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN0 | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	//----- Left Window
	17,                           
	OSD_Win_Num				( WIN3 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0x0a), (0x91) ), // 3 bytes
	OSD_Win_Width			( 5 ),
	OSD_Win_Height			( 5 ), 
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(OSDRam_Start_Address+65) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN0 | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	//----- Right Window
	17,                           
	OSD_Win_Num				( WIN2 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0xb2), (0x91) ), // 3 bytes
	OSD_Win_Width			( 5 ),
	OSD_Win_Height			( 5 ), 
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(OSDRam_Start_Address+90) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN0 | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
	//----- Red Bar Window
	17,
	OSD_Win_Num				( WIN1 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0x46), (0xd9) ), // 3 bytes
	OSD_Win_Width			( 9 ),
	OSD_Win_Height			( 1 ), 
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(OSDRam_Start_Address+115) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN0 | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
};
/*===========================================================================*/// display char. set
CODE BYTE LineTop[]={ RAMFONT,0x71,0x71,0x80,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x81,0x71,0x71,
			                  0x71,0x82,0x84,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x87,0x85,0x71,
			      0x71,0x83,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x86,0x71,
			      0x82,0x84,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x87,0x85,
			      0x80,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x81,
	0
	};

CODE BYTE LineLeft[]={ RAMFONT,0x71,0x71,0x82,0x84,0x71,
						       0x71,0x71,0x83,0x71,0x71,
						       0x71,0x82,0x84,0x71,0x71,
						       0x71,0x83,0x71,0x71,0x71,
						       0x82,0x7f,0x7f,0x7f,0x7f,
	0
	};
CODE BYTE LineRight[]={ RAMFONT,0x71,0x87,0x85,0x71,0x71,
								0x71,0x71,0x86,0x71,0x71,
								0x71,0x71,0x87,0x85,0x71,
								0x71,0x71,0x71,0x86,0x7b,
								0x7f,0x7f,0x7f,0x7f,0x85,
	0
	};

CODE BYTE BarX[]={ RAMFONT,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,
	0,
	};

void DisplayLineOSD(void)
{
	CODE_P BYTE *str;
	BYTE i;

	InitOSDWindow(Init_Line_OSD_Demo);

	ClearDataCnt(OSDRam_Start_Address, 250);

	DrawAttrCnt(OSDRam_Start_Address, CH_COLOR_GREEN, 52);	 
	DrawAttrCnt(OSDRam_Start_Address+52, CH_COLOR_YELLOW, 13);	 
	DrawAttrCnt(OSDRam_Start_Address+65, CH_COLOR_YELLOW, 20);	 
	DrawAttrCnt(OSDRam_Start_Address+85, CH_COLOR_RED, 5);	 
	DrawAttrCnt(OSDRam_Start_Address+90, CH_COLOR_YELLOW, 20);	 
	DrawAttrCnt(OSDRam_Start_Address+110, CH_COLOR_RED, 21);	 

	str = LineTop;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address, str, i);

	str = LineLeft;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address+65, str, i);

	str = LineRight;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address+90, str, i);


	str = BarX;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address+115, str, i);


	for(i=OSDCURSORWINDOW; i<=OSDMENU_TITLEWIN; i++) {
		ShowOSDWindow_TW88(i,TRUE);
	}

	ShowOSDWindowAll(1);
	
}


#else
CODE BYTE Init_Line_OSD_Demo[]={ 
	//----- Top Window
	17,                           
	OSD_Win_Num				( WIN4 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0xbd), (0x27) ), // 3 bytes
	OSD_Win_Width			( 16 ),
	OSD_Win_Height			( 5 ), 
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx3), WIN_SADDR(OSDRam_Start_Address) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN0 | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	//----- Left Window
	17,                           
	OSD_Win_Num				( WIN3 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0x0b), (0x81) ), // 3 bytes
	OSD_Win_Width			( 5 ),
	OSD_Win_Height			( 5 ), 
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx3), WIN_SADDR(OSDRam_Start_Address+80) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN0 | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	//----- Right Window
	17,                           
	OSD_Win_Num				( WIN2 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0x2fb), (0x81) ), // 3 bytes
	OSD_Win_Width			( 5 ),
	OSD_Win_Height			( 5 ), 
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx3), WIN_SADDR(OSDRam_Start_Address+105) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN0 | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
	//----- Red Bar Window
	17,
	OSD_Win_Num				( WIN1 ),	// 2 bytes
	OSD_Win_Attr			( WIN_EN0 ),
	OSD_Win_Start			( (0xbf), (0xc9) ), // 3 bytes
	OSD_Win_Width			( 16 ),
	OSD_Win_Height			( 1 ), 
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx3), WIN_SADDR(OSDRam_Start_Address+130) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN0 | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
};
/*===========================================================================*/// display char. set
CODE BYTE LineTop[]={ RAMFONT,0x71,0x71,0x71,0x76,0x77,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7a,0x7b,0x71,0x71,0x71,
			      0x71,0x71,0x76,0x77,0x79,0x71,0x71,0x71,0x71,0x71,0x71,0x7c,0x7a,0x7b,0x71,0x71,
			      0x71,0x76,0x77,0x79,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x7c,0x7a,0x7b,0x71,
			      0x76,0x77,0x79,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x71,0x7c,0x7a,0x7b,
			      0x77,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7a,
	0
	};

CODE BYTE LineLeft[]={ RAMFONT,0x71,0x71,0x71,0x76,0x77,
						       0x71,0x71,0x76,0x77,0x79,
						       0x71,0x76,0x77,0x79,0x71,
						       0x76,0x77,0x79,0x71,0x71,
						       0x77,0x7e,0x7f,0x7f,0x7f,
	0
	};
CODE BYTE LineRight[]={ RAMFONT,0x7a,0x7b,0x71,0x71,0x71,
								0x7c,0x7a,0x7b,0x71,0x71,
								0x71,0x7c,0x7a,0x7b,0x71,
								0x71,0x71,0x7c,0x7a,0x7b,
								0x7f,0x7f,0x7f,0x7f,0x7a,
	0
	};

CODE BYTE BarX[]={ RAMFONT,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,
	0,
	};

void DisplayLineOSD(void)
{
	CODE_P BYTE *str;
	BYTE i;

	InitOSDWindow(Init_Line_OSD_Demo);

	ClearDataCnt(OSDRam_Start_Address, 250);

	DrawAttrCnt(OSDRam_Start_Address, CH_COLOR_GREEN, 64);	 
	DrawAttrCnt(OSDRam_Start_Address+64, CH_COLOR_YELLOW, 16);	 
	DrawAttrCnt(OSDRam_Start_Address+80, CH_COLOR_YELLOW, 20);	 
	DrawAttrCnt(OSDRam_Start_Address+100, CH_COLOR_RED, 5);	 
	DrawAttrCnt(OSDRam_Start_Address+105, CH_COLOR_YELLOW, 20);	 
	DrawAttrCnt(OSDRam_Start_Address+125, CH_COLOR_RED, 21);	 

	str = LineTop;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address, str, i);

	str = LineLeft;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address+80, str, i);

	str = LineRight;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address+105, str, i);


	str = BarX;
	i=strlen(str);
	WriteStringToAddr(OSDRam_Start_Address+130, str, i);


	for(i=OSDCURSORWINDOW; i<=OSDMENU_TITLEWIN; i++) {
		ShowOSDWindow_TW88(i,TRUE);
	}

	ShowOSDWindowAll(1);
	
}


#endif


#endif
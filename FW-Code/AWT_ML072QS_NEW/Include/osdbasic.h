//osd_basic.h
//LJY11012001
#ifndef __OSD_BASIC__
#define __OSD_BASIC__

// osd_basic.h
// char code
//#include "apilib.h"

//ljy052903
//definition for internal OSD
#define FONT_WIDTH_TW88			12
#define FONT_HEIGHT_TW88		18
#define PIXS_PER_XSTEP_TW88		8
#define LINES_PER_YSTEP_TW88	4
#define MAX_OSDWINDOW_TW88		8

// Using TW88 OSD for Menu
#define FONT_WIDTH			12
#define FONT_HEIGHT			18
#define PIXS_PER_XSTEP		8
#define LINES_PER_YSTEP		4
#define MAX_OSDWINDOW		4

#define	MAX_FONT_BYTES		27
#define RAMFONT		0xFE
#define ROMFONT		0xFF
#define NO_UDFONT			226 

#define FONT_ROM	1
#define FONT_RAM	2


/////////////////////////////////
// Old Registers...
/*
	#define TW88_WIN1ATTR		0x76
	#define TW88_WIN1XSTART		0x77
	#define TW88_WIN1YSTART		0x78
	#define TW88_WIN1WIDTH		0x79
	#define TW88_WIN1HEIGHT		0x7a
	#define TW88_WIN1BRDATTR	0x7b
	#define TW88_WIN1BRDWIDTH	0x7c
	#define TW88_WIN1BRDHEIGHT	0x7d
	#define TW88_WIN1XSPACE		0x7e		// between characters.
	#define TW88_WIN1YSPACE		0x7f
	#define TW88_WIN1SADDR		0x80		// starting address of OSD ram for Windows 1
*/
/////////////////////////////////

// OSD
#define TW88_ENABLERAM		0x94	// TW8804C
#define TW88_FONTRAMADDR	0x99	// TW8804C
#define TW88_FONTRAMDATA	0x9a	// TW8804C
#define TW88_OSDRAMADDRHI	0x95	// TW8804C
#define TW88_OSDRAMADDRLO	0x96	// TW8804C
#define TW88_OSDRAMDATAHI	0x97	// TW8804C
#define TW88_OSDRAMDATALO	0x98	// TW8804C
#define TW88_MULTISTART		0x9b	// TW8804C
#define TW88_OSDLOCKUPSEL	0x9c
#define TW88_WINNUM			0x9e	// TW8804C
#define TW88_WINATTR		0x9f	//
#define TW88_WINXSTART		0xa1	//
#define TW88_WINYSTART		0xa2	//
#define TW88_WINSTART_HI	0xa0	//
#define TW88_WINWIDTH		0xa3	//
#define TW88_WINHEIGHT		0xa4	//
#define TW88_WINBRDATTR		0xa5	//
#define TW88_WINBRDWIDTH	0xa6	//
#define TW88_WINBRDHEIGHT	0xa7	//
#define TW88_WINSPACE		0xa8	// between characters.
#define TW88_WINZOOM		0xa9	//
#define TW88_WINSADDRHI		0xa9	// starting address of OSD ram for Windows 1
#define TW88_WINSADDRLO		0xaa	// starting address of OSD ram for Windows 1

#define TW88_WINSHADOW		0xab	//
#define TW88_WINBLENDING	0xac	//
#define TW88_WINCHEFFECT	0xad	//


//Attributes for OSD
#define WINZOOMx1			0x01
#define WINZOOMx2			0x02
#define WINZOOMx3			0x03
#define WINZOOMx4			0x04
#define SHOW				0x08	

#define EXTENDED_COLOR		0x80
#define BG_COLOR_BLACK 		0x00	//For background color of window, border, and char. 
#define BG_COLOR_RED		0x40	
#define BG_COLOR_GREEN		0x20
#define BG_COLOR_YELLOW 	0x60
#define BG_COLOR_BLUE		0x10
#define BG_COLOR_MAGENTA	0x50
#define BG_COLOR_CYAN		0x30
#define BG_COLOR_WHITE		0x70
#define BG_COLOR_TRANS		0x80	
#define BG_COLOR_MASK		0xf0	

#define CH_COLOR_BLACK 		0x00	//For color of char.
#define CH_COLOR_RED		0x04	
#define CH_COLOR_GREEN		0x02
#define CH_COLOR_YELLOW 	0x06
#define CH_COLOR_BLUE		0x01
#define CH_COLOR_MAGENTA	0x05
#define CH_COLOR_CYAN		0x03
#define CH_COLOR_WHITE		0x07
#define CH_BLINK			0x08	
#define CH_COLOR_MASK		0x0f	

#define CL_BLACK 			0x00	//For color of char.
#define CL_BLUE				0x01
#define CL_GREEN			0x02
#define CL_CYAN				0x03
#define CL_RED				0x04	
#define CL_MAGENTA			0x05
#define CL_YELLOW			0x06
#define CL_WHITE			0x07
#define CL_BLINK			0x08	

// 0x76*(WindowNo*0x0b)
#define WINDOW_DISABLE		0x00
#define WINDOW_ENABLE		0x01
#define WINDOW_3D_ENABLE    0x04
#define WINDOW_3D_BOTTOM    0x08
#define WINDOW_3D_TOP	    0x00
#define WINDOW_TRANS_ENABLE 0x80

#define WINBDCOLOR_ENABLE	0x80
#define WINBDCOLOR_EXTENT	0x80


#define WINBLENDING_DISABLE 0x00
#define WINBLENDING_BACK    0x10
#define WINBLENDING_FORE    0x20
#define WINBLENDING_ALL     0x30

#define WINSHADOW_ENABLE	0x80
// 0xc8*WindowNo
#define WIN_MULTICOLOR_ENABLE 0x20
#define WIN_CH_EFFECT_ENABLE  0x10
#define WIN_CH_EFFECT_SHADOW  0x08



///////// TW8804C /////////////
// Window Number
#define WINNUM1				1
#define WINNUM2				2
#define WINNUM3				3
#define WINNUM4				4

// Index 0x9f Defination
#define WIN_BG_COLOR_EX		0x80
#define WIN_BG_COLOR_EX0	0x00
#define WIN_3D_TYPE			0x08
#define WIN_3D_TYPE0		0x00
#define WIN_3D_EN			0x04
#define WIN_3D_EN0			0x00
#define WIN_3D_LEVEL		0x02
#define WIN_EN				0x01
#define WIN_EN0				0x00

// Index 0xa5 Defination
#define WIN_BD_EN			0x80
#define WIN_BD_EN0			0x00
#define WIN_BD_WIDTH(a)		a

// Index 0xa6 Defination
#define WIN_BD_COLOR_EX		0x80
#define WIN_BD_COLOR_EX0	0x00
#define WIN_H_BD_W(a)		a

// Index 0xa7 Defination
#define WIN_V_BD_W(a)		a

// Index 0xa8
#define WIN_CH_VSPACE(a)	(a<<4)
#define WIN_CH_HSPACE(a)	a

// Index 0xa9 Defination
#define WIN_VZOOM(a)		(a-1)
#define WIN_HZOOM(a)		(a-1)
#define WIN_SADDR(a)		a

// Index 0xab
#define WIN_SHADOW_EN		0x80
#define WIN_SHADOW_EN0		0x00
#define WIN_SHADOW_W(a)		a

// ad
#define WIN_SHADOW_COLOR_EX		0x80
#define WIN_SHADOW_COLOR_EX0	0x00
#define WIN_MULTI_EN			0x40
#define WIN_MULTI_EN0			0x00
#define WIN_V_EXT_EN			0x20
#define WIN_V_EXT_EN0			0x00
#define WIN_CH_BDSH_SEL(a)		a
#define SEL_BORDER				0
#define SEL_SHADOW				1
#define WIN_CH_BDSH_COLOR_EX	0x08
#define WIN_CH_BDSH_COLOR_EX0	0x00

#define OSD_Win_Num(a)			0x9e, a-1
#define OSD_Win_Start_Addr		0xa0
#define OSD_Win_Attr(a)				a
#define OSD_Win_Start(h,v)			 (BYTE)(((WORD)h>>8) | (((WORD)v>>8)<<4)),(BYTE)h, (BYTE)v
#define OSD_Win_Width(a)			a
#define OSD_Win_Height(a)			a
#define OSD_Win_Border(a)			a
#define OSD_Win_HBorder(a)			a
#define OSD_Win_VBorder(a)			a
#define OSD_Win_CH_Space(a)			a
#define OSD_Win_ZM_SAddr(h,v,a)		((h<<6)|(v<<4)|(a>>8)), (BYTE)a
#define	OSD_Win_Shadow(a)			a
#define OSD_Win_Blending(a)			a
#define OSD_Win_CH_BorderShadow(a)	a


#define	SetOSDWindowNum(winno)		WriteTW88(TW88_WINNUM, winno-1)

//#define  OSD_Window_Attr(Trans_en,Color,3D_Type,3D_en,W_en)       (((( Trans_en | Color ) | 3D_Type) | 3D_en) | W_en)
#define  OSD_Window_Attr(a,b,c,d,e)									(((( a | b ) | c) | d) | e)
#define  OSD_WShadow_Attr(W_Shadow_en,Color,Width)					W_Shadow_en | Color | Width
//#define  OSD_Blending(en,level)										en | (level & 0x0f)
//#define  OSD_Ch_Effect(Multi, Effect_En, ShadowBorder, Color)		Multi | Effect_En | ShadowBorder | Color  


struct OSDStrInfo 
{
	BYTE	cnt;
	WORD	addr;
	BYTE	attr;
	DWORD	str;
};
/*
struct BarInfo {
	struct RegisterInfo BarCnt;
	BYTE	winno;
	BYTE	xoff;
	BYTE	yoff;
	BYTE	color;
	int		bar_cnt;
};
*/
struct FontData {
	BYTE	font[27];
} ;

//====================================================================
//  Internal OSD Function
void CopyCharToOSDRAM_TW88(BYTE Addr, BYTE attr, BYTE ch);
void CopyUDCharToOSDRAM_TW88(BYTE Addr, BYTE attr, BYTE ch);
//BYTE GetOSDWindowWidth_TW88(BYTE winno);
WORD GetOSDWindowSA_TW88(BYTE winno);
void SetOSDWindowX_TW88(BYTE winno, BYTE x);
void SetOSDWindowY_TW88(BYTE winno, BYTE y);
void SetOSDWindowWidth_TW88(BYTE winno, BYTE w);
void SetOSDWindowSA_TW88(BYTE winno, WORD sa);

void SetOSDItalicsAndUnderline(BYTE italics, BYTE underline);

void SetOSDHBorderWidth_TW88(BYTE winno, BYTE w);
//BYTE GetOSDWindowColor_TW88(BYTE winno);
void SetOSDWindowColor_TW88(BYTE CCWin, BYTE color);
void EnableOSDRAMAndChangeFont(BYTE type);
void WriteCharToOSDRAM(WORD addr, BYTE ch, BYTE attr);


void ShowOSDWindowAll(BYTE on);
void ShowOSDWindow_TW88(BYTE winno, BYTE onoff);
void ClearOSD_TW88(void);
//void CreateOSDWindow_TW88(BYTE winno, BYTE x, BYTE y, BYTE w, BYTE h, WORD sa, BYTE attr);
/*not yet!!
//ljy012304...CC_ADJUST_POS
void SetOSDWindowXS_TW88(BYTE winno, BYTE xs);
void SetOSDWindowYS_TW88(BYTE winno, BYTE ys);
*/

//====================================================================
//	OSDMenu Functions

//--------------------------------------------------------------------
//	Functions used in only Menu
#define		CONVERT_CODE			0x80

void InitOSDWindow(BYTE *ptr);

WORD GetOSDWindowX(BYTE winno);
WORD GetOSDWindowY(BYTE winno);
BYTE CreateOSDWindowOutline(BYTE winno, BYTE w, BYTE color);
void CreateOSDMenuWindow(BYTE, BYTE, BYTE, BYTE, BYTE, BYTE, BYTE);
void ClearOSDLine(BYTE winno, BYTE sx, BYTE sy, BYTE cnt, BYTE attr);
void WriteStringToAddr(WORD addr, BYTE *str, BYTE cnt);
void DrawAttrString(WORD addr, BYTE *str, BYTE cnt);
void DrawAttrCnt(WORD addr, BYTE color, BYTE cnt);
void ClearDataCnt(WORD, BYTE);
#define 	SetOSDWindowX(A, B)				SetOSDWindowX_TW88(A, B)
#define 	SetOSDWindowY(A, B)				SetOSDWindowY_TW88(A, B)

//--------------------------------------------------------------------
//	Functions used in Menu and others
#define 	ShowOSDWindow(A, B)				ShowOSDWindow_TW88(A, B)
#define 	ClearOSD()    					ClearOSD_TW88()

//================================================================
//	Font
void DownloadUDFont(void);
#ifdef Hs_debug
void DisplayROMFont(BYTE);
void DisplayRAMFont(BYTE);
#endif
void DownloadFont(BYTE cod, CODE_P BYTE *fontdata);
//void DisplayGrid( void );
//void DisplayCone( void );
//void DisplayJapanese( void );
void TestRAMFont( void );
#ifdef BANKING
void DisplayMGrid( BYTE );
void DisplayMessage( void );
void DisplayChinese( void );
void DisplayJapanese( void );
void DisplayKorean( void );
void DisplayGridBank0( BYTE n );
void DisplayGridBank1( BYTE n );
#endif

//================================================================
//	OSD COLOR
void Change_OSDColorLookup(void);
void Reset_OSDColorLookup(void);

//====================================================================
//				Conversion
//====================================================================
BYTE utoa(WORD value, BYTE *str, BYTE radix);
BYTE ltoa_K(long value, BYTE *str, BYTE);
BYTE strlen( BYTE *str );

#define CStrlen(A)				strlen(A)

void WaitEndofDisplayArea(void);

#endif	// __OSD_BASIC__


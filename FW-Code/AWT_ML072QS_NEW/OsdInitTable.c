#include "config.h"
#include "panel.h"
#include "osdmenu.h"
//*****************************************************************************
//
//           OSD Window Initialization Table
//
//*****************************************************************************
//=============================================================================
//			Initialize Window for DisplayLogo "Techwell"
//=============================================================================
CODE BYTE Init_Osd_DisplayLogo[] = {

	17,
	OSD_Win_Num				( TECHWELLOGO_OSDWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	OSD_Win_Start			( ((PHR_-12*12*LOGO_ZOOM)/2), ((PVR_-18*2*WINZOOMx2)/2)),	// 3 bytes
	OSD_Win_Width			( 12 ),
	OSD_Win_Height			( 2 ),
	OSD_Win_Border			( WIN_BD_EN0 | BG_COLOR_WHITE | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx2), WIN_HZOOM(LOGO_ZOOM), WIN_SADDR(LOGO_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
};
//
#ifdef ADD_ANALOGPANEL
CODE BYTE Init_Osd_DisplayLogo_A[] = {

	17,
	OSD_Win_Num				( TECHWELLOGO_OSDWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),//1
	OSD_Win_Start			( ((480*2-12*12*WINZOOMx3)/2), ((234-18*2*WINZOOMx2)/2)),	// 3 bytes
	OSD_Win_Width			( 12 ),
	OSD_Win_Height			( 2 ),
	OSD_Win_Border			( WIN_BD_EN0 | BG_COLOR_WHITE | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx2), WIN_HZOOM(WINZOOMx3), WIN_SADDR(LOGO_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
};
#endif

//=============================================================================
//			Initialize Window for Vchip Rathing
//=============================================================================
CODE BYTE Init_Osd_DisplayVchipWindow[] = {

	17,
	OSD_Win_Num				( BACK_COLOR|RATINGINFO_OSDWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN ),
	OSD_Win_Start			( ((PHR_-12*18*LOGO_ZOOM-18)/2), ((PVR_-18*2*LOGO_ZOOM-8)/2)),	// 3 bytes
	OSD_Win_Width			( 18 ),
	OSD_Win_Height			( 2 ),
	OSD_Win_Border			( WIN_BD_EN | BG_COLOR_WHITE | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0x10) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x08) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(LOGO_ZOOM), WIN_HZOOM(LOGO_ZOOM), WIN_SADDR(RATINGINFO_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BACK_COLOR | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x00 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
};

//=============================================================================
//			Initialize Window for DisplayMuteInfo
//=============================================================================
CODE BYTE Init_Osd_DisplayMuteInfo[] = {

	17,
	OSD_Win_Num				( BACK_COLOR|TVINFO_OSDWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	OSD_Win_Start			( PHR_-12*4*MUTE_ZOOM, 0 ),	// 3 bytes
	OSD_Win_Width			( 4 ),
	OSD_Win_Height			( 1 ),
	OSD_Win_Border			( WIN_BD_EN0 | BG_COLOR_WHITE | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x00) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(MUTE_ZOOM), WIN_HZOOM(MUTE_ZOOM), WIN_SADDR(MUTEINFO_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
};

//=============================================================================
//			Initialize Window for DisplayTvchannel
//=============================================================================
CODE BYTE Init_Osd_DisplayTVChannel[] = {

	17,
	OSD_Win_Num				( BACK_COLOR|TVINFO_OSDWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BG_COLOR_BLACK | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	OSD_Win_Start			( PHR_-12*3*TVCHN_ZOOM, 0 ),	// 3 bytes
	OSD_Win_Width			( 3 ),
	OSD_Win_Height			( 1 ),
	OSD_Win_Border			( WIN_BD_EN0 | BG_COLOR_WHITE | WIN_BD_WIDTH(0) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x00) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(TVCHN_ZOOM), WIN_HZOOM(TVCHN_ZOOM), WIN_SADDR(TVCHINFO_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x0f ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
	0 // End of Data
};

//=============================================================================
//			Initialize Window for DisplayPCInfo
//=============================================================================
CODE BYTE Init_Osd_DisplayPCInfo[] = {

	17,
	OSD_Win_Num				( BACK_COLOR|PCINFO_OSDWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	OSD_Win_Start			( 12, 13 ),	// 3 bytes
	OSD_Win_Width			( 10 ),
	OSD_Win_Height			( 1 ),
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(4) ),
	OSD_Win_VBorder			( WIN_V_BD_W(4) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(PCINFO_ZOOM), WIN_HZOOM(PCINFO_ZOOM), WIN_SADDR(PCMEASUREINFO_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 4 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
};

//=============================================================================
//			Initialize Window for DisplayInput
//=============================================================================
CODE BYTE Init_Osd_DisplayInput[] = {

	//----- Input Selection : Zoom 2
	17,
	OSD_Win_Num 			( BACK_COLOR|INPUTINFO_OSDWIN-1 ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	#ifdef AWT_ML072S
	OSD_Win_Start			( 0/*592*/, 0 ),	// 3 bytes
	#else
	OSD_Win_Start			( 22, 13 ),	// 3 bytes
	#endif
#ifdef QUAD	
	OSD_Win_Width			( 15/*19*/ ),
#else
		//#ifdef AWT_ML072S
		//OSD_Win_Width			( 16 ),
		//#else
		OSD_Win_Width			( 33/*19*/ ),
		//#endif
#endif

#ifdef AWT_ML072Q  //Pinchi 20140922 add for AWT ML072Q
	OSD_Win_Height			( 2),
#else
	OSD_Win_Height			( 1),//ryan@20171206
#endif
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(1) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x00) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
#ifdef AWT_ML072Q  //Pinchi 20140922 add for AWT ML072Q
	OSD_Win_ZM_SAddr		( WIN_VZOOM(INPUTINFO_ZOOM), WIN_HZOOM(WINZOOMx2), WIN_SADDR(INPUTINFO_ADDR) ),	// 2 bytes
#else
	OSD_Win_ZM_SAddr		( WIN_VZOOM(INPUTINFO_ZOOM), WIN_HZOOM(WINZOOMx2), WIN_SADDR(INPUTINFO_ADDR) ),	// 2 bytes
#endif
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 8 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),                   
	#if 0		//wiilaim-981029
	//----- Input Discription : Zoom 1
	17,
	OSD_Win_Num				( BACK_COLOR|INPUTINFO_OSDWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	OSD_Win_Start			( 11, 12 ),	// 3 bytes
	OSD_Win_Width			( 0x11 ),
		#ifdef  WQVGA
	OSD_Win_Height			( 2 ),
		#else
	OSD_Win_Height			( 3 ),
		#endif
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(8) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x00) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(INPUTINFO_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 4 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),                       
	#endif
	
	  17,
    OSD_Win_Num             ( BACK_COLOR|RATINGINFO_OSDWIN ),   // 2 bytes
    OSD_Win_Attr            ( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN ),
#ifdef TW8816
	#ifdef AWT_ML072S
	OSD_Win_Start           ( 45-8,67),  // 120->40   24->        
	#else
	OSD_Win_Start           ( 45,60-5),  // 120->40   24->        
    	#endif
#else
    OSD_Win_Start           ( 45,60),  // 120->40   24->               
#endif
    OSD_Win_Width           ( 30 ),
    OSD_Win_Height          ( 5 ),
    OSD_Win_Border          ( WIN_BD_EN | BG_COLOR_WHITE | WIN_BD_WIDTH(0) ),
    OSD_Win_HBorder         ( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0x00) ),
    OSD_Win_VBorder         ( WIN_V_BD_W(0x00) ),
    OSD_Win_CH_Space        ( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
    OSD_Win_ZM_SAddr        ( WIN_VZOOM(WINZOOMx4), WIN_HZOOM(WINZOOMx2), WIN_SADDR(RATINGINFO_ADDR) ), // 2 bytes
    OSD_Win_Shadow          ( WIN_SHADOW_EN0 | BACK_COLOR | WIN_SHADOW_W(8) ),//
    OSD_Win_Blending        ( 8 ),
    OSD_Win_CH_BorderShadow ( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
                            | WIN_CH_BDSH_SEL(SEL_BORDER) 
                            | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
/*
	//----- Input Selection : Zoom 4
	17,
	#ifdef AWT_ML072S
	OSD_Win_Num				( BACK_COLOR|VLOSSINFO_OSDWIN-1 ),	// 2 bytes
	#else
	OSD_Win_Num				( BACK_COLOR|DVRStatus_OSDWIN ),	// 2 bytes
	#endif
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	#ifdef AWT_ML072S
	OSD_Win_Start			( 320,218 ),	// 3 bytes
	#else
	OSD_Win_Start			( 12, (PVR_-18*2*BAR_ZOOM)),	// 3 bytes
	#endif
	OSD_Win_Width			( 5 ),
	OSD_Win_Height			( 1 ),
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(1) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x00) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	#ifdef AWT_ML072S
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx3), WIN_HZOOM(WINZOOMx3), WIN_SADDR(33) ),	// 2 bytes	
	#else
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(DVRStatus_ADDR) ),	// 2 bytes
	#endif
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 8 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
*/
	0 // End of Data
}; 

//#ifndef QUAD		
#ifdef AWT_ML072Q  //Pinchi 20140925 enable for trigger C display char of AWT ML072Q 
//=============================================================================
//			Initialize Window for DisplayInput
//=============================================================================
CODE BYTE Init_Osd_DisplayInput_M[] = {

	//----- Input Selection : Zoom 2
	17,
	OSD_Win_Num				( BACK_COLOR|INPUTINFO_OSDWIN-1 ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
#ifdef AWT_ML072Q  //Pinchi 20140922 add for AWT ML072Q
	OSD_Win_Start			( 12 , 12 ),	// 3 bytes
#else
	OSD_Win_Start			( 12, 13 ),	// 3 bytes
#endif

	OSD_Win_Width			( 15/*19*/ ),
#ifdef AWT_ML072Q  //Pinchi 20140922 add for AWT ML072Q
	OSD_Win_Height			( 2 ),
#else
	OSD_Win_Height			( 1 ),
#endif
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(1) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x00) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
#ifdef AWT_ML072Q  //Pinchi 20140922 add for AWT ML072Q
	OSD_Win_ZM_SAddr		( WIN_VZOOM(INPUTINFO_ZOOM), WIN_HZOOM(INPUTINFO_ZOOM), WIN_SADDR(INPUTINFO_ADDR) ),	// 2 bytes
#else
	OSD_Win_ZM_SAddr		( WIN_VZOOM(INPUTINFO_ZOOM), WIN_HZOOM(WINZOOMx1), WIN_SADDR(INPUTINFO_MIRROR_ADDR) ),	// 2 bytes
#endif
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 8 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
	0 // End of Data
};          
#endif

#ifdef ADD_ANALOGPANEL
CODE BYTE Init_Osd_DisplayInput_A[] = {
	//----- Input Selection : Zoom 1
	17,
	OSD_Win_Num				( BACK_COLOR|INPUTINFO_OSDWIN-1 ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	OSD_Win_Start			( 12, 13 ),	// 3 bytes
	OSD_Win_Width			( 9 ),
	OSD_Win_Height			( 1 ),
	OSD_Win_Border			( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(1) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x00) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx2), WIN_SADDR(INPUTINFO_ADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 4 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	8,
	OSD_Win_Num				( BACK_COLOR|INPUTINFO_OSDWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),//1
	OSD_Win_Start			( 11, 12 ),	// 3 bytes
	OSD_Win_Width			( 0x11 ),
	OSD_Win_Height			( 2 ),
	0
};
#endif

#ifdef SUPPORT_2835_CLK_TUNE_BACK_DOOR  //Pinchi 20160929 add
CODE BYTE Init_Osd_DisplayInput_B[] = {
    //----- Input Selection : Zoom 1
    17,
    OSD_Win_Num             ( BACK_COLOR|INPUTINFO_OSDWIN-1 ),  // 2 bytes
    OSD_Win_Attr            ( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
    OSD_Win_Start           ( 10, 5 ), // 3 bytes
    OSD_Win_Width           ( 2 ),
    OSD_Win_Height          ( 1 ),
    OSD_Win_Border          ( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
    OSD_Win_HBorder         ( WIN_BD_COLOR_EX0 | WIN_H_BD_W(1) ),
    OSD_Win_VBorder         ( WIN_V_BD_W(0x00) ),
    OSD_Win_CH_Space        ( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
    OSD_Win_ZM_SAddr        ( WIN_VZOOM(WINZOOMx2), WIN_HZOOM(WINZOOMx2), WIN_SADDR(INPUTINFO_ADDR) ),  // 2 bytes
    OSD_Win_Shadow          ( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
    OSD_Win_Blending        ( 8 ),
    OSD_Win_CH_BorderShadow ( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
                            | WIN_CH_BDSH_SEL(SEL_BORDER) 
                            | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
    0
};
#endif

//=============================================================================
//			Initialize Window for MainMenu
//=============================================================================
#if (defined ADD_ANALOGPANEL)
 #define OSDHSTART_MAX_A (480-(12+1)*25 - 56*2 -4)  //PHR - (pixelsize +Hspace)*MenuWidth - Hborder*2 - outlinewidth*2
 #define OSDVSTART_MAX_A (234-(18+11)*9 - 5*2 ) //  PVR - (Linesize+Vspace)*MENU_HEIGHT - Vborder*2  - outlinewidth*2
CODE BYTE Init_Osd_MainMenu_A[] = {
						#include "data\MenuWindow_A.txt" 
};
#endif

#if ((defined WQVGA) && ((defined ANALOG_7INCH)||(defined TMD_ANALOG)))// || (defined QVGA) 
 #define OSDHSTART_MAX_A (480-(12+2)*25 - 56*2 +40) //OSDHSTART_MAX  //PHR - (pixelsize +Hspace)*MenuWidth - Hborder*2 - outlinewidth*2
 #define OSDVSTART_MAX_A OSDVSTART_MAX  //  PVR - (Linesize+Vspace)*MENU_HEIGHT - Vborder*2  - outlinewidth*2

CODE BYTE Init_Osd_MainMenu[] = {
						#include "data\MenuWindow_A.txt" 
};
#elif (defined QVGA) && (defined SHARP_LQ050Q5DR01)
 #define OSDHSTART_MAX_A (480-(12+2)*25 - 56*2 -8-10) //OSDHSTART_MAX  //PHR - (pixelsize +Hspace)*MenuWidth - Hborder*2 - outlinewidth*2
 #define OSDVSTART_MAX_A OSDVSTART_MAX  //  PVR - (Linesize+Vspace)*MENU_HEIGHT - Vborder*2  - outlinewidth*2

CODE BYTE Init_Osd_MainMenu[] = {
						#include "data\MenuWindow_A.txt" 
};
#else
CODE BYTE Init_Osd_MainMenu[] = {
//						#include "data\MenuWindow.txt" 
/*===========================================================================*/
// Normal Panel Menu Window tabel
/*===========================================================================*/
	///////////////////----- Top(Left) Window
	17,
	OSD_Win_Num				( BACK_COLOR|OSDMENU_TOPWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	
//OSD_Win_Attr				( WIN_BG_COLOR_EX0 | TITLE_BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
#ifdef E_Wintek
	OSD_Win_Start			( (OSDHSTART_MAX/2-145), ((OSDVSTART_MAX/2)-80) ), // 3 bytes
#else
  #ifdef HS_NEWOSDMENU
	OSD_Win_Start			( (OSDHSTART_MAX/2-85), ((OSDVSTART_MAX/2)-84) ), // 3 bytes
  #else	
	#ifdef TW8816
  		 #ifdef AWT_ML072S
 		OSD_Win_Start			( (0x7c), (0x09)), // 3 bytes
		 #else
 		OSD_Win_Start			( (0x40/*0x50*/), (0x09)), // 3 bytes
		#endif
	#else
  	OSD_Win_Start			( (OSDHSTART_MAX/2-145), ((OSDVSTART_MAX/2-60))), // 3 bytes
	#endif	  	
 #endif
#endif
#ifdef HS_NEWOSDMENU
	OSD_Win_Width			( 13 ),
	OSD_Win_Height			( 1 ),
#else
	OSD_Win_Width			( 2 ),
	#ifdef TW8816
	OSD_Win_Height			( 4 ),
	#else
	OSD_Win_Height			( 5 ),
	#endif
#endif
#ifdef HS_NEWOSDMENU
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX | WIN_H_BD_W(0x00) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x00) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0x00) ),
	//OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	//OSD_Win_HBorder			(0),
	//OSD_Win_VBorder			(0),
	//OSD_Win_CH_Space			(0),
#else
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0) ),
	#ifdef TW8816
	OSD_Win_VBorder			( WIN_V_BD_W(0x05/*0x08*/) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0x0b/*0x09*/) ),
	#else
	OSD_Win_VBorder			( WIN_V_BD_W(0) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0x02) ),
	#endif
#endif	
#ifdef E_Wintek	
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx4), WIN_HZOOM(WINZOOMx4), WIN_SADDR(OSDMENU_MAINADDR) ),	// 2 bytes
#else
  #ifdef HS_NEWOSDMENU
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx4), WIN_HZOOM(WINZOOMx4), WIN_SADDR(OSDMENU_MAINADDR) ),
  #else
  OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx4), WIN_HZOOM(WINZOOMx3), WIN_SADDR(OSDMENU_MAINADDR) ),	// 2 bytes
  #endif
#endif
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(4) ),
	OSD_Win_Blending		( 0x33/*0x36*/ ),//( 3 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

#ifdef HS_NEWOSDMENU_2  //Pinchi modify condition for compiler warning
  #ifdef HS_NEWOSDMENU
	/////////////////////////////////////----- Title Window
	17,                           
	OSD_Win_Num					( BACK_COLOR|OSDMENU_TITLEWIN ),	// 2 bytes
	#if 1	
	OSD_Win_Attr				( WIN_BG_COLOR_EX0 | TITLE_BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	#else	
	OSD_Win_Attr				( WIN_BG_COLOR_EX0 | DEFAULT_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	#endif	

	OSD_Win_Start				( ((OSDHSTART_MAX/2)+66+14+2), ((OSDVSTART_MAX/2)-60) ), // 3 bytes
	OSD_Win_Width				( 13 ), 
	OSD_Win_Height				( 1 ), 
	OSD_Win_Border				( WIN_BD_EN0 | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(2) ),
	OSD_Win_HBorder				( WIN_BD_COLOR_EX | WIN_H_BD_W(0x30+8) ),
	OSD_Win_VBorder				( WIN_V_BD_W(0x05) ),
	OSD_Win_CH_Space			( WIN_CH_HSPACE(1) | WIN_CH_VSPACE(0x0b) ),

	#ifdef TW8816
	OSD_Win_ZM_SAddr			( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(OSDMENU_SUBADDR) ),	//Weylis
	#else
	OSD_Win_ZM_SAddr			( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx2), WIN_SADDR(OSDMENU_SUBADDR) ),	//25=MENU_WIDTH
	#endif

	OSD_Win_Shadow				( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(8) ),
	//OSD_Win_Blending				( 3 ),
	OSD_Win_Blending			( 0x05 ),
	OSD_Win_CH_BorderShadow		( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 | WIN_CH_BDSH_SEL(SEL_BORDER) | 
									WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
	//----- Sub(Right) Window
  #else
	/*
	//----- Title Window
	17,
	OSD_Win_Num				( BACK_COLOR|OSDMENU_TITLEWIN ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | TITLE_BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
	OSD_Win_Start			( (OSDHSTART_MAX/2), (OSDVSTART_MAX/2) ), // 3 bytes
	OSD_Win_Width			( TITLE_MAX_DESC ), 
	OSD_Win_Height			( 0x09 ), 
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(2) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX | WIN_H_BD_W(0x30+8) ),
	OSD_Win_VBorder			( WIN_V_BD_W(0x05) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(1) | WIN_CH_VSPACE(0x0b) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx1), WIN_HZOOM(WINZOOMx1), WIN_SADDR(OSDMENU_SUBADDR) ),	//25=MENU_WIDTH// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(8) ),
	OSD_Win_Blending		( 3 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
*/	                        
  #endif
#endif

	////////////////////////////////////----- Sub(Right) Window
	17,
	OSD_Win_Num				( BACK_COLOR|OSDMENUWINDOW ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN0 ),
#ifdef E_Wintek
	OSD_Win_Start			( ((OSDHSTART_MAX/2-145)), (OSDVSTART_MAX/2-60) ), // 3 bytes
#else
	#ifdef TW8816
//	OSD_Win_Start			( ((0x76)), (0x09) ), // 3 bytes//( ((OSDHSTART_MAX/2-85)), (OSDVSTART_MAX/2-10) ), // 3 bytes
#ifdef AWT_ML072S
	OSD_Win_Start			( (0xC0), (0x09) ),
#else
	//OSD_Win_Start			( ((OSDHSTART_MAX/2-45)), (OSDVSTART_MAX/2-60) ), // 3 bytes//( ((OSDHSTART_MAX/2-85)), (OSDVSTART_MAX/2-10) ), // 3 bytes
	OSD_Win_Start			( (0x8a/*0x9a*//*(0xb0)*/), (0x09) ), // 3 bytes//( ((OSDHSTART_MAX/2-85)), (OSDVSTART_MAX/2-10) ), // 3 bytes

#endif
	#else
	OSD_Win_Start			( ((OSDHSTART_MAX/2-45)), (OSDVSTART_MAX/2-60) ), // 3 bytes//( ((OSDHSTART_MAX/2-85)), (OSDVSTART_MAX/2-10) ), // 3 bytes
	#endif
	//OSD_Win_Start			( ((OSDHSTART_MAX/2)+66+14+2), (OSDVSTART_MAX/2+28) ), // 3 bytes
#endif
	OSD_Win_Width			( MENU_WIDTH  ), //MENU_WIDTH
	OSD_Win_Height			( MENU_HEIGHT ),	// MENU_HEIGHT
	#ifdef TW8816
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(0) ),
	#else
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	#endif
	//OSD_Win_HBorder			( WIN_BD_COLOR_EX | WIN_H_BD_W(0x0c+8) ),
	#ifdef TW8816
	OSD_Win_HBorder			( WIN_BD_COLOR_EX | WIN_H_BD_W(0x0A) ),
	#else
	OSD_Win_HBorder			( WIN_BD_COLOR_EX | WIN_H_BD_W(0x0A+8) ),
	#endif

	#ifdef TW8816
	OSD_Win_VBorder			( WIN_V_BD_W(0x05) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0x0b) ),
	#else
	OSD_Win_VBorder			( WIN_V_BD_W(0x16+1) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0x04) ),
	#endif
	
#ifdef E_Wintek	
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx2), WIN_HZOOM(WINZOOMx2), WIN_SADDR(OSDMENU_SUBADDR+MENU_WIDTH) ),	//25=MENU_WIDTH// 2 bytes
#else
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx2), WIN_HZOOM(WINZOOMx2), WIN_SADDR(OSDMENU_SUBADDR+MENU_WIDTH) ),	//25=MENU_WIDTH// 2 bytes
#endif
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(8) ),
	OSD_Win_Blending		( 0x33/*0x36*/ ),//( 3 ),


	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	//----- 3D Cursor Window
	17,
	OSD_Win_Num				( BACK_COLOR|OSDCURSORWINDOW ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN | WIN_EN0 ),
#ifdef E_Wintek
	OSD_Win_Start			( ((OSDHSTART_MAX/2)-145+8), ((OSDVSTART_MAX/2)-80)+10 ), // 3 bytes
#else
#ifdef HS_NEWOSDMENU
	OSD_Win_Start			( (OSDHSTART_MAX/2-85), ((OSDVSTART_MAX/2)-84) ), // 3 bytes
#else	
		#ifdef TW8816
			 #ifdef AWT_ML072S
			OSD_Win_Start			( (0x7c), ((0x27-9) )), // 3 bytes	 
			 #else
			OSD_Win_Start			( (0x40/*0x50*/), ((0x27) )), // 3 bytes
			#endif
		#else
		OSD_Win_Start			( (OSDHSTART_MAX/2-145), ((OSDVSTART_MAX/2-60) )), // 3 bytes
		#endif
#endif	
#endif
	OSD_Win_Width			( 2 ),
	OSD_Win_Height			( 1 ),
	OSD_Win_Border			( WIN_BD_EN | BG_COLOR_WHITE | WIN_BD_WIDTH(1) ),
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0) ),

	#ifdef TW8816
       OSD_Win_VBorder			( WIN_V_BD_W(0) ),
       OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0x00) ),
	#else
       OSD_Win_VBorder			( WIN_V_BD_W(0) ),
       OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0x10) ),
	#endif

#ifdef E_Wintek
	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx4), WIN_HZOOM(WINZOOMx4), WIN_SADDR(OSDMENU_MAINADDR) ),	// 2 bytes
#else
 	OSD_Win_ZM_SAddr		( WIN_VZOOM(WINZOOMx4), WIN_HZOOM(WINZOOMx3), WIN_SADDR(OSDMENU_MAINADDR) ),	// 2 bytes
#endif
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
	OSD_Win_Blending		( 0x33/*0x36*/ ),//( 3 ),
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_SHADOW) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),

	0 // End of Data
/*===========================================================================*/
};

#endif

CODE BYTE Init_Osd_BarWindow[] = {

	//----- Bar/Message Window
	17,
	OSD_Win_Num				( BACK_COLOR|OSDBARWINDOW  ),	// 2 bytes
	OSD_Win_Attr			( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE | WIN_3D_EN | WIN_EN0 ),
	#ifdef TW8816
	OSD_Win_Start			( (0x90), (0x160) ),	// 3 bytes
	#else
	OSD_Win_Start			( ((PHR_-12*25*BAR_ZOOM)/2), (PVR_-18*2*BAR_ZOOM-26) ),	// 3 bytes
	#endif
	#ifdef TW8816
	OSD_Win_Width			( 21),
	OSD_Win_Height			( 2 ),
	OSD_Win_Border			( WIN_BD_EN | BG_COLOR_MASK | WIN_BD_WIDTH(1) ),
	#else
	OSD_Win_Width			( 25 ),
	OSD_Win_Height			( 2 ),
	OSD_Win_Border			( WIN_BD_EN | OSDMENU_OUTLINE_COLOR | WIN_BD_WIDTH(1) ),
	#endif
	OSD_Win_HBorder			( WIN_BD_COLOR_EX0 | WIN_H_BD_W(2) ),
	OSD_Win_VBorder			( WIN_V_BD_W(4) ),
	OSD_Win_CH_Space		( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(4) ),
	OSD_Win_ZM_SAddr		( WIN_VZOOM(BAR_ZOOM), WIN_HZOOM(BAR_ZOOM), WIN_SADDR(OSDMENU_BARADDR) ),	// 2 bytes
	OSD_Win_Shadow			( WIN_SHADOW_EN0 | BG_COLOR_BLACK | WIN_SHADOW_W(0) ),
#ifdef TW8816
	OSD_Win_Blending		( 0x33 ),//( 5 ),
#else
	OSD_Win_Blending		( 0x36 ),//( 5 ),
#endif	
	OSD_Win_CH_BorderShadow	( WIN_SHADOW_COLOR_EX | WIN_MULTI_EN | WIN_V_EXT_EN0 
	                        | WIN_CH_BDSH_SEL(SEL_BORDER) 
	                        | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLUE ),

	0 // End of Data
};


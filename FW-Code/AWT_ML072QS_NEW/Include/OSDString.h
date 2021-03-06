// OSDString.h
//==============================================================================
//
// String by Language
//
// Lang1 = English
// Lang2 = Frensh
// Lanf3 = Deutch
// Lang4 = Spanish
// Lang5 = Korean
//==============================================================================
//
//  Display String by language in information
//
#ifndef _OSDString_H_
#define _OSDString_H_


#ifdef AWT_ML073G
#ifdef HS
#define VERSION1            'H'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION2            'S'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION3            ' '    //版本REV  1. xx     //  william-1.45-971106
#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION5            '9'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION6            ' '    //版本REV  1. xx     //  william-1.45-971106
#define VERSION7            ' '  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION8            ' '    //版本REV  1. xx     //  william-1.45-971106
#else
#define VERSION1            'A'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION2            'W'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION3            'T'    //版本REV  1. xx     //  william-1.45-971106
#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION5            '4'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION6            '1'    //版本REV  1. xx     //  william-1.45-971106
#define VERSION7            '0'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#endif
#endif

#ifdef Holtz
#ifdef QUAD
#define VERSION1            'H'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION2            'z'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION3            ' '    //版本REV  1. xx     //  william-1.45-971106
#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION5            '0'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION6            '1'    //版本REV  1. xx     //  william-1.45-971106
#define VERSION7            '2'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#else
#define VERSION1            'H'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION2            'z'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION3            ' '    //版本REV  1. xx     //  william-1.45-971106
#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION5            '0'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION6            '1'    //版本REV  1. xx     //  william-1.45-971106
#define VERSION7            '3'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#endif
#endif

#ifdef AWT_ML072Q
#define VERSION1            'A'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION2            'W'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION3            'T'    //版本REV  1. xx     //  william-1.45-971106
#define VERSION4            '2'  //AWT ML072Q wit TW8816 初版 by ryan@20171020
#define VERSION5            '0'  
#define VERSION6            '0'  
#define VERSION7            '2'
#endif

#ifdef HTRV  //Pinchi 20150825 add
#define VERSION1            'H'    //ac¥?REV  1. xx     2007.6.22  Justin
#define VERSION2            'V'  //Kane @HS 2007 0720 Ver1.3	  //ac¥?REV  1. xx     2007.6.22  Justin
#define VERSION3            ' '
  #if 1  //Pinchi 20150827 add
  #define VERSION4          '2'  //MP
//  #define VERSION5          '0'  //PP
//  #define VERSION5          '1'  //Pinchi 20151209 update version for HTRV request to remove 4:3 screen
//  #define VERSION5          '2'  //Pinchi 20160929 update for modify TW2835 54M clk to slove garbege of screen
 #define VERSION5          '3'  //ryan@20170727
  #ifdef SUPPORT_DISPLAY_TEST_VERSION  //Pinchi 20150929 add
  #define VERSION6          'T'
  #define VERSION7          '5'
  #else
  #define VERSION6          ' '  //TE
  #endif
  #else
  #define VERSION4          '0'  //MP
  #define VERSION5          '1'  //PP
  #define VERSION6          '1'  //TE
  #define VERSION7          '0'  //EE
  #endif
#endif

#ifdef AWT_ML072S
#ifdef HS
#define VERSION1            'H'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION2            'S'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION3            ' '    //版本REV  1. xx     //  william-1.45-971106
//#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
//#define VERSION5            '0'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
//#define VERSION6            '1'    //版本REV  1. xx     //  william-1.45-971106
#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION5            '0'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION6            '0'  

#define VERSION7            '0'  
#define VERSION8            '0'  
#define VERSION9            '0'  
#define VERSION10          '1'  


#else
#define VERSION1            'A'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION2            'W'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION3            'T'    //版本REV  1. xx     //  william-1.45-971106
//#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
//#define VERSION5            '0'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
//#define VERSION6            '1'    //版本REV  1. xx     //  william-1.45-971106
#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION5            '0'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION6            '1'  

#define VERSION7            '0'  
#define VERSION8            '0'  
#define VERSION9            '0'  
#define VERSION10          '1'  
#endif

#endif

#ifdef E_Wintek
#define VERSION1            'E'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION2            ' '  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION3            ' '    //版本REV  1. xx     //  william-1.45-971106
#define VERSION4            '1'    //版本REV  1. xx     2007.6.22  Justin
#define VERSION5            '2'  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION6            ' '    //版本REV  1. xx     //  william-1.45-971106
#define VERSION7            ' '  //Kane @HS 2007 0720 Ver1.3	  //版本REV  1. xx     2007.6.22  Justin
#define VERSION8            ' '    //版本REV  1. xx     //  william-1.45-971106
#endif

//--------------------------------------------------------------------------------
#if 0
CODE BYTE Enter_Password_Str_E[] = {' ',' ',' ',' ','E','n','t','e','r',' ','P','I','N',' ',':',' ','-','-','-','-',0};
CODE BYTE Enter_Password_Str_F[] = {' ',' ',' ','E','n','t','r','e','r',' ','P','I','N',' ',':',' ','-','-','-','-',0};
CODE BYTE Enter_Password_Str_D[] = {' ',' ','E','i','n','g','a','b','e',' ','P','I','N',' ',':',' ','-','-','-','-',0};
CODE BYTE Enter_Password_Str_S[] = {' ',' ',' ','E','n','t','r','e','r',' ','P','I','N',' ',':',' ','-','-','-','-',0};
CODE BYTE Enter_Password_Str_K[] = {' ',' ',RAMFONT,0x41,0x3d,0x3e,0x6e,0x38,0x71,0x4e,0x36,0x71,0x6b,0x49,0x52,ROMFONT,':',' ','-','-','-','-',0};							   
#endif
//--------------------------------------------------------------------------------
#ifdef E_Wintek
CODE BYTE CheckPCCableStr_E[] = {RAMFONT,0x5f,0x5f,0x52,0x53,0x5f,0x54,0x55,0x5f,0x56,0x57,ROMFONT,0};
#else
CODE BYTE CheckPCCableStr_E[] = {'C','h','e','c','k',' ','V','G','A',' ','C','a','b','l','e',0};
#endif
#ifdef fullcode
CODE BYTE CheckPCCableStr_K[] = {RAMFONT,0x4e,0x36,0x43,0x6e,0x38,0x71,0x6c,0x50,0x6b,0x49,0x52,ROMFONT,0};
#endif
//--------------------------------------------------------------------------------
#ifdef fullcode
CODE BYTE CheckDTVCableStr_E[] = {'C','h','e','c','k',' ','D','T','V',' ','C','a','b','l','e',0};
CODE BYTE CheckDTVCableStr_K[] = {RAMFONT,0x4e,0x36,0x43,0x6e,0x38,0x71,0x6c,0x50,0x6b,0x49,0x52,ROMFONT,0};
#endif
//--------------------------------------------------------------------------------
CODE BYTE OutOfRangeStr_E[] = {'O','u','t',' ','O','f',' ','R','a','n','g','e',0};
CODE BYTE OutOfRangeStr_K[] = {RAMFONT,0x62,0x59,0x6b,0x62,0x71,0x4c,0x2f,0x71,0x3a,0x34,ROMFONT,0};

//--------------------------------------------------------------------------------

CODE BYTE StrVolume_E[] = {0x12,0x13,'V','o','l','u','m','e',0};	
#ifdef fullcode
CODE BYTE StrVolume_F[] = {0x12,0x13,'V','o','l','u','m','e',0};								
CODE BYTE StrVolume_D[] = {0x12,0x13,'L', 'a', 'u', 't', 's', 't', 'a', 'r', 'k', 'e',0};								
CODE BYTE StrVolume_S[] = {0x12,0x13,'V','o','l','u','m','e','n',0};								
CODE BYTE StrVolume_K[] = {0x12,0x13,RAMFONT,0x53,0x37,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE MuteOnStr_E[] = {'M','u','t','e',0};
CODE BYTE MuteOnStr_K[] = {RAMFONT,0x71,0x5f,0x51,0x69,ROMFONT,0};

#endif
//--------------------------------------------------------------------------------
#ifdef E_Wintek
CODE BYTE AutoAdjustInfo[]=	{' ',' ',' ',' ',' ',' ',RAMFONT,0x2c,0x2d,0x2e,0x2f,0x14,0x15,0x16,0x17,ROMFONT,'.','.','.','.',' ',' ',' ',' ',' ',};
#else
CODE BYTE AutoAdjustInfo[]=	{"   Auto Adjusting ....   "};
#endif							//012345678901234

/*================================================================================*/
/*
/* Title String in OSD menu                                                         
/*
/*=================================================================================*/
//#define		TITLEMAXDEC			25	
///* Title String Length :
/*================================================================================*/
#ifdef fullcode
CODE BYTE Str_Input_E[] = {'I','n','p','u','t',0};
CODE BYTE Str_Input_F[] = {'S','o','u','r','c','e',' ','d',0x27, 'e', 'n', 't', 'r', 0x62, 'e',0};
CODE BYTE Str_Input_D[] = {'E', 'i', 'n', 'g', 'a', 'n', 'g', 's', 'q', 'u', 'e', 'l', 'l', 'e',0};
CODE BYTE Str_Input_S[] = {'F', 'u', 'e', 'n', 't', 'e', ' ', 'E', 'n', 't', 'r', 'a', 'd', 'e', 0};
CODE BYTE Str_Input_K[] = {RAMFONT,0x4e,0x36,0x71,0x46,0x67,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Picture_E[] = {'P','i','c','t','u','r','e',0};
CODE BYTE Str_Picture_F[] = {'E', 'c', 'r', 'a', 'n', 0};
CODE BYTE Str_Picture_D[] = {'B', 'i', 'l', 'd',0};
CODE BYTE Str_Picture_S[] = {'P', 'a', 'n', 't', 'a', 'l', 'l', 'a',0};
CODE BYTE Str_Picture_K[] = {RAMFONT,0x6d,0x3b,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Sound_E[] = {'A','u','d','i','o',0};
CODE BYTE Str_Sound_S[] = {'S','o','n','i','d','o',0};
CODE BYTE Str_Sound_K[] = {RAMFONT,0x53,0x70,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Utility_E[] = {'U','t','i','l','i','t','y',0};
CODE BYTE Str_Utility_F[] = {'U', 't', 'i', 'l', 'i', 't', 'a', 'i', 'r', 'e',0};
CODE BYTE Str_Utility_D[] = {'F', 'u', 'n', 'k', 't', 'i', 'o', 'n',0};
CODE BYTE Str_Utility_S[] = {'U', 't', 'i', 'l', 'i', 'd', 'a', 'd',0};
CODE BYTE Str_Utility_K[] = {RAMFONT,0x24,0x2e,0x71,0x46,0x67,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_ColorTemp_E[] = {'C','o','l','o','r',' ','T','e','m','p',0};
CODE BYTE Str_ColorTemp_F[] = {'T', 'e', 'm', 'p', '.', ' ', 'C', 'o', 'u', 'l', 'e', 'u', 'r',0};
CODE BYTE Str_ColorTemp_D[] = {'F', 'a', 'r', 'b', 't', 'e', 'm', 'p', 'e', 'r', 'a', 't', 'u', 'r',0};
CODE BYTE Str_ColorTemp_S[] = {'T', 'e', 'm', 'p', '.', ' ',  'd', 'e', ' ', 'C', 'o', 'l', 'o', 'r',0};
CODE BYTE Str_ColorTemp_K[] = {RAMFONT,0x4a,0x55,0x33,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Comments_E[] = {'E','x','i','t',':','M','E','N','U',' ',' ','M','o','v','e',':',0x1d,0x1e,' ',' ','S','e','l',':',0x1c,0};
CODE BYTE Str_Comments_K[] = {RAMFONT,0x2a,0x26,ROMFONT,':','M','E','N','U',' ',' ',' ',' ',RAMFONT,0x4d,0x35,ROMFONT,':',0x1d,0x1e,
											' ',' ',' ',' ',' ',RAMFONT,0x46,0x67,ROMFONT,':',0x1c,0};
#endif								 
//--------------------------------------------------------------------------------
#ifdef PAL_TV
CODE BYTE Str_Comments1[] = {'M','o','v','e',':',0x7f,0x7f,' ','S','k','i','p','/','A','d','d',':',0x7f,' ','E','d','i','t',':',0x7f,0};
CODE BYTE Color_Comments1[] = {CH_COLOR_RED|TITLE_BACK_COLOR,CH_COLOR_GREEN|TITLE_BACK_COLOR,
 							   COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,
							   COMMENT_COLOR,COMMENT_COLOR,
							   CH_COLOR_YELLOW|TITLE_BACK_COLOR,
							   COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,COMMENT_COLOR,
							   CH_COLOR_CYAN|TITLE_BACK_COLOR
								};
			
#endif

/*================================================================================*/
/*                                                                                */
/* Decsription String in OSD menu                                                 */
/*                                                                                */
//==================================================================================
//MenuStr
#define		MAX_DESC			15 //14	//andy
///* Menu String Max Length :
/*================================================================================*/
CODE BYTE Str_Composite_E[] = {'C','o','m','p','o','s','i','t','e',0};

#ifdef SUPPORT_SVIDEO
CODE BYTE Str_Svideo_E[] = {'S','-','V','i','d','e','o',0};
#endif

	#ifdef SUPPORT_COMPONENT
CODE BYTE Str_Component_E[] = {'C','o','m','p','o','n','e','n','t',0};
	#endif

	#ifdef SUPPORT_DTV
CODE BYTE Str_Dtv_E[] = {'D','T','V',0};
	#endif

	#ifdef SUPPORT_PC
CODE BYTE Str_Pc_E[] = {'P','C',0};
	#endif

	#ifdef SUPPORT_DIGITALVGA
CODE BYTE Str_DigitalVGA_E[] = {'D','i','g','i','t','a','l',' ','V','G','A',0};
	#endif
CODE BYTE Str_Version_E[] = {'V','e','r','s','i','o','n',0};
CODE BYTE Str_LCDVersion_E[] = {'L','C','D',' ','V','e','r','s','i','o','n',0};
CODE BYTE Str_DVRVersion_E[] = {'D','V','R',' ','V','e','r','s','i','o','n',0};

CODE BYTE Str_WIFI_IP_E[] = {'W','I','F','I',' ','I','P',0};
CODE BYTE Str_WIFI_MAC_E[] = {'W','I','F','I',' ','M','A','C',0};
CODE BYTE Str_GETWAY_E[] = {'G','A','T','E','W','A','Y',0};
//--------------------------------------------------------------------------------
#ifdef SUPPORT_PC
CODE BYTE Str_VPosition_E[] = {'V',' ','P','o','s','i','t','i','o','n',0};
CODE BYTE Str_VPosition_F[] = {'P','o','s','i','t','i','o','n',' ','V','.',0};
CODE BYTE Str_VPosition_D[] = {'V',' ','P','o','s','i','t','i','o','n',0};
CODE BYTE Str_VPosition_S[] = {'P','o','s','i','c','i',0x5f,'n',' ','V','.',0};
CODE BYTE Str_VPosition_K[] = {RAMFONT,0x6d,0x3b,0x71,0x45,0x63,0x71,0x54,0x65,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_HPosition_E[] = {'H',' ','P','o','s','i','t','i','o','n',0};
CODE BYTE Str_HPosition_F[] = {'P','o','s','i','t','i','o','n',' ','H','.',0};
CODE BYTE Str_HPosition_D[] = {'H',' ','P','o','s','i','t','i','o','n',0};
CODE BYTE Str_HPosition_S[] = {'P','o','s','i','c','i',0x5f,'n',' ','H','.',0};
CODE BYTE Str_HPosition_K[] = {RAMFONT,0x6d,0x3b,0x71,0x45,0x68,0x71,0x54,0x65,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Phase_E[] = {'P','h','a','s','e',0};
CODE BYTE Str_Phase_S[] = {'F','a','s','e',0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Clock_E[] = {'C','l','o','c','k',0};
CODE BYTE Str_Clock_F[] = {'H', 'o', 'r', 'l', 'o', 'g', 'e',0};
CODE BYTE Str_Clock_D[] = {'T', 'a', 'k', 't',0};
CODE BYTE Str_Clock_S[] = {'R', 'e', 'l', 'o', 'j',0};

//--------------------------------------------------------------------------------

CODE BYTE Str_AutoColor_E[] = {'A','u','t','o',' ','C','o','l','o','r',0};
CODE BYTE Str_AutoColor_K[] = {RAMFONT,0x5b,0x35,0x71,0x4a,0x48,0x71,0x5f,0x60,ROMFONT,0};

CODE BYTE Str_AutoAdjust_E[] = {'A','u','t','o',' ','A','d','j','u','s','t',0};
CODE BYTE Str_AutoAdjust_K[] = {RAMFONT,0x5b,0x35,0x71,0x6d,0x3b,0x71,0x5f,0x60,ROMFONT,0};
#endif

#ifdef E_Wintek
CODE BYTE Str_RETURN_C[] = {RAMFONT,0x10,0x11,0x12,0x13,ROMFONT,0};
CODE BYTE Str_Auto_Day_Night_C[]={RAMFONT,0x2c,0x2d,0x2e,0x2f,0x14,0x15,0x30,0x31,ROMFONT,0};
CODE BYTE Str_DIR_IMAGE_C[]={RAMFONT,0x32,0x33,0x34,0x35,0x36,0x37,0x1e,0x1f,0x20,0x21,0x40,0x41,0x42,0x43,ROMFONT,0};
CODE BYTE Str_REAR_SETUP_C[]={RAMFONT,0x38,0x39,0x3a,0x3b,0x1e,0x1f,0x20,0x21,0x40,0x41,0x42,0x43,ROMFONT,0};
CODE BYTE Str_JUMP_C[] = {RAMFONT,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,ROMFONT,0};
CODE BYTE Str_RECALL_C[]={RAMFONT,0x44,0x45,0x46,0x47,ROMFONT,0};
CODE BYTE Str_EXIT_C[]={RAMFONT,0x50,0x51,0x18,0x19,ROMFONT,0};
CODE BYTE Str_AutoAdjust_C[] = {RAMFONT,0x2c,0x2d,0x2e,0x2f,0x14,0x15,0x16,0x17,ROMFONT,0};
CODE BYTE StrVolume_C[] = {RAMFONT,0x48,0x49,0x4a,0x4b,ROMFONT,0};
#endif

//--------------------------------------------------------------------------------
#ifdef SUPPORT_OSDPOSITIONMOVE
CODE BYTE Str_OSDPosition_E[] =	{'O','S','D',' ','P','o','s','i','t','i','o','n',0};
CODE BYTE Str_OSDPosition_S[] =	{'O','S','D',' ','P','o','s','i','c','i',0x5f,'n',0};
CODE BYTE Str_OSDPosition_K[] =	{'O','S','D',' ',RAMFONT,0x54,0x65,0x71,0x46,0x67,ROMFONT,0};

#endif

//--------------------------------------------------------------------------------
CODE BYTE Str_OSDLang_E[] = {'L','a','n','g','u','a','g','e',0};
CODE BYTE Str_OSDLang_F[] = {'L', 'a', 'n', 'g', 'u', 'e',0};
CODE BYTE Str_OSDLang_D[] = {'S', 'p', 'r', 'a', 'c', 'h', 'e',0};
CODE BYTE Str_OSDLang_S[] =	{'I', 'd', 'i', 'o', 'm', 'a',0};
CODE BYTE Str_OSDLang_K[] = {RAMFONT,0x57,0x56,0x71,0x46,0x67,ROMFONT,0};

//--------------------------------------------------------------------------------
//CODE BYTE Str_SleepTimerE[] = {'S','l','e','e','p',' ','T','i','m','e','r',0};
//CODE BYTE Str_SleepTimerK[] = {RAMFONT,0x30,0x27,0x71,0x42,0x22,0x71,0x44,0x60,ROMFONT,0};

#ifdef fullcode
//--------------------------------------------------------------------------------
CODE BYTE Str_VInputStd_E[] = {'I','n','p','u','t',' ','S','t','d','.',0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Information_E[] =	{'I','n','f','o','r','m','a','t','i','o','n',0};

CODE BYTE Str_Treble_E[] = {'T','r','e','b','l','e',0};
CODE BYTE Str_Treble_F[] = {'A','i','g','u','e','s',0};
CODE BYTE Str_Treble_D[] = {'H','o','h','e','n',0};
CODE BYTE Str_Treble_S[] = {'A','g','u','d','o','s',0};
CODE BYTE Str_Treble_K[] = {RAMFONT,0x29,0x53,0x71,0x5f,0x60,ROMFONT,0};
//--------------------------------------------------------------------------------

CODE BYTE Str_Bass_E[] = {'B','a','s','s',0};
CODE BYTE Str_Bass_F[] = {'B','a','s','s','e','s',0};
CODE BYTE Str_Bass_D[] = {'T','i','e','f','e','n',0};
CODE BYTE Str_Bass_S[] = {'G','r','a','v','e','s',0};
CODE BYTE Str_Bass_K[] = {RAMFONT,0x5e,0x53,0x71,0x5f,0x60,ROMFONT,0};
//--------------------------------------------------------------------------------
CODE BYTE Str_Balance_E[] = {'B','a','l','a','n','c','e',0};
CODE BYTE Str_Balance_F[] = {'B','a','l','a','n','c','e',0};
CODE BYTE Str_Balance_D[] =	{'B','a','l','a','n','c','e',0};
CODE BYTE Str_Balance_S[] =	{'B','a','l','a','n','c','e',0};
CODE BYTE Str_Balance_K[] = {RAMFONT,0x53,0x25,0x6f,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Red_E[] = {'R','e','d',0};
CODE BYTE Str_Red_F[] =	{'R','o','u','g','e',0};
CODE BYTE Str_Red_D[] = {'R','o','t',0};
CODE BYTE Str_Red_S[] = {'R','o','j','o',0};
CODE BYTE Str_Red_K[] = {RAMFONT,0x5c,0x4a,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Green_E[] = {'G','r','e','e','n',0};
CODE BYTE Str_Green_F[] = {'V','e','r','t',0};
CODE BYTE Str_Green_D[] = {'G','r',0xae,'n',0};
CODE BYTE Str_Green_S[] = {'V', 'e', 'r', 'd', 'e',0};
CODE BYTE Str_Green_K[] = {RAMFONT,0x2b,0x4a,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Blue_E[] = {'B','l','u','e',0};
CODE BYTE Str_Blue_F[] = {'B','l','e','u',0};
CODE BYTE Str_Blue_D[] = {'B','l','a','u',0};
CODE BYTE Str_Blue_S[] = {'A','z','u','l',0};
CODE BYTE Str_Blue_K[] = {RAMFONT,0x64,0x4a,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Backlight_E[] = {'B','a','c','k','l','i','g','h','t',0};
CODE BYTE Str_Backlight_F[] = {'B','a','c','k','l','i','g','h','t',0};
CODE BYTE Str_Backlight_D[] = {'B','a','c','k','l','i','g','h','t',0};
CODE BYTE Str_Backlight_S[] = {'B','a','c','k','l','i','g','h','t',0};
CODE BYTE Str_Backlight_K[] = {'B','a','c','k','l','i','g','h','t',0};

//--------------------------------------------------------------------------------
#endif

//--------------------------------------------------------------------------------
CODE BYTE Str_Brightness_E[] = {'B','r','i','g','h','t','n','e','s','s',0};
CODE BYTE Str_Brightness_F[] = {'L', 'u', 'm', 'i', 'n', 'o', 's', 'i', 't', 0x5f,0};
CODE BYTE Str_Brightness_D[] = {'H', 'e', 'l', 'l', 'i', 'g', 'k', 'e', 'i', 't',0};
CODE BYTE Str_Brightness_S[] = {'B', 'r', 'i', 'l', 'l', 'o',0};
CODE BYTE Str_Brightness_K[] = {RAMFONT,0x40,0x24,0x71,0x5f,0x60,ROMFONT,0};
#ifdef E_Wintek
CODE BYTE Str_Brightness_C[] = {RAMFONT,0x08,0x09,0x0a,0x0b,0x14,0x15,0x16,0x17,ROMFONT,0};
#endif

//--------------------------------------------------------------------------------

CODE BYTE Str_Contrast_E[] = {'C','o','n','t','r','a','s','t',0};
CODE BYTE Str_Contrast_F[] = {'C','o','n','t','r','a','s','t','e',0};
CODE BYTE Str_Contrast_D[] = {'K','o','n','t','r','a','s','t',0};
CODE BYTE Str_Contrast_S[] = {'C','o','n','t','r','a','s','t','e',0};
CODE BYTE Str_Contrast_K[] = {RAMFONT,0x39,0x4f,0x71,0x5f,0x60,ROMFONT,0};
#ifdef E_Wintek
CODE BYTE Str_Contrast_C[] = {RAMFONT,0x0c,0x0d,0x0e,0x0f,0x14,0x15,0x16,0x17,ROMFONT,0};
#endif

//--------------------------------------------------------------------------------
CODE BYTE Str_Saturation_E[] = {'S','a','t','u','r','a','t','i','o','n',0};
CODE BYTE Str_Saturation_D[] = {'S', 0xaa, 't', 't', 'i', 'g', 'u', 'n', 'g',0};
CODE BYTE Str_Saturation_S[] = {'S', 'a', 't', 'u', 'r', 'a', 'c', 'i', 0x5f, 'n',0};
CODE BYTE Str_Saturation_K[] = {RAMFONT,0x4a,0x2c,0x33,0x71,0x5f,0x60,ROMFONT,0};
#ifdef E_Wintek
CODE BYTE Str_Saturation_C[] = {RAMFONT,0x4c,0x4d,0x4e,0x4f,0x14,0x15,0x16,0x17,ROMFONT,0};
#endif

//--------------------------------------------------------------------------------
CODE BYTE Str_Hue_E[] = {'H','u','e',0};
CODE BYTE Str_Hue_F[] = {'T', 'o', 'n', 'a', 'l', 'i', 't', 0x5c,0};
CODE BYTE Str_Hue_D[] = {'F', 'a', 'r', 'b', 'e',0};
CODE BYTE Str_Hue_S[] = {'T', 'o', 'n', 'a', 'l', 'i', 'd', 'a', 'd',0};
CODE BYTE Str_Hue_K[] =	{RAMFONT,0x4a,0x54,0x48,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Sharpness_E[] = {'S','h','a','r','p','n','e','s','s',0};
CODE BYTE Str_Sharpness_F[] = {'A', 'c', 'u', 'i', 't', 0x5c,0};
CODE BYTE Str_Sharpness_D[] = {'S', 'c', 'h', 0xaa, 'r','f', 'e',0};
CODE BYTE Str_Sharpness_S[] = {'A', 'g', 'u', 'd', 'e', 'z', 'a',0};
CODE BYTE Str_Sharpness_K[] = {RAMFONT,0x46,0x39,0x33,0x71,0x5f,0x60,ROMFONT,0};

//--------------------------------------------------------------------------------
CODE BYTE Str_Reset_E[] = {'R','e','s','e','t',0};
CODE BYTE Str_Reset_F[] = {'D', 0x5c, 'f', 'a', 'u', 't',0};
CODE BYTE Str_Reset_D[] = {'G', 'r', 'u', 'n', 'd', 'e', 'i', 'n', 's', 't', 'e', 'l', 'u', 'g',0};
CODE BYTE Str_Reset_S[] = {'P', 'r', 'e', 'd', 'e', 't', 'e', 'r', 'm', 'i', 'n', 'a', 'c', 'i',0x5f, 'n',0};
CODE BYTE Str_Reset_K[] = {RAMFONT,0x66,0x24,0x6d,ROMFONT,0};

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
#ifdef WIDE_SCREEN
CODE BYTE Str_WideScreen_E[] = {'W','i','d','e',' ','S','c','r','e','e','n',0};
CODE BYTE Str_WideScreen_K[] = {'W','I','D','E',' ',RAMFONT,0x6d,0x3b,0x71,0x46,0x67,ROMFONT,0};
#endif

//---------------------------------------------------------------------------------
CODE BYTE Str_MIRROR_E[] = {'M','i','r','r','o','r',0};
CODE BYTE Str_JUMP_E[] = {'J','u','m','p',0};
#ifdef AWT_ML072S
CODE BYTE Str_SEQ_TIME_STEP_E[] = {'J','u','m','p',' ','D','w','e','l','l',0};
#else
CODE BYTE Str_SEQ_TIME_STEP_E[] = {'S','E','Q',' ','T','i','m','e',' ','S','t','e','p',0};
#endif
CODE BYTE Str_JumpAV_E[]={'J','u','m','p',' ','A','V',0};		//william @20130902	v1.0.1.2
CODE BYTE Str_CAM_OUT_E[] = {'C','a','m',' ','O','u','t',0};
CODE BYTE Str_RETURN_E[] = {'R','e','t','u','r','n',0};

#ifdef AWT_ML072S
CODE BYTE Str_RECALL_E[]={'R','E','C','A','L','L',0}; 
#else
CODE BYTE Str_RECALL_E[]={'R','e','c','a','l','l',0}; 
#endif

CODE BYTE Str_MonitorRECALL_E[]={'M','o','n','i','t','o','r',' ','R','e','c','a','l','l',0}; 
CODE BYTE Str_DVRRECALL_E[]={'D','V','R',' ','R','e','c','a','l','l',0}; 

#ifdef AWT_ML072S
CODE BYTE Str_EXIT_E[]={' ',' ',' ',' ',' ','E','x','i','t',0}; 
#else
CODE BYTE Str_EXIT_E[]={'E','x','i','t',0}; 
#endif

CODE BYTE Str_SPACE_E[]={' ',0};  // V1.1 02/28/07 simonsung
#ifdef AWT_ML072QS_FW_RULE  //Pinchi 20140902 add
//  	CODE BYTE Str_VER_E[]={' ',' ',' ',' ','V','E','R',' ',VERSION1,/*VERSION2,*/' ',VERSION4,'.',VERSION5,VERSION6,0};
  	CODE BYTE Str_VER_E[]={'V','E','R',' ',VERSION1,/*VERSION2,*/' ',VERSION4,'.',VERSION5,VERSION6,'.',VERSION7,VERSION8,VERSION9,VERSION10,0};
//CODE BYTE Str_VER_E[]={'v','e','r',' ',VERSION1,VERSION4,'.',VERSION5,VERSION6,0};
#elif (defined HTRV_ML072Q_FW_RULE)  //Pinchi 20150827 add
  #ifdef SUPPORT_DISPLAY_TEST_VERSION  //Pinchi 20150929 add
  CODE BYTE Str_VER_E[]={'v','e','r',' ',VERSION1,VERSION2,VERSION4,'.',VERSION5,VERSION6,VERSION7,0};
  #else
  	CODE BYTE Str_VER_E[]={'v','e','r',' ',VERSION1,VERSION2,VERSION4,'.',VERSION5,VERSION6,0};
  #endif
#else
CODE BYTE Str_VER_E[]={VERSION1,VERSION2,VERSION3,' ',VERSION4,'.',VERSION5,'.',VERSION6,'.',VERSION7,0}; //  william-1.45-971106
#endif

CODE BYTE Str_TIMEOUT_STEP_E[] = {'T','i','m','e','O','u','t',' ', 'S','e','t','u','p',0};//2007.4.13 Justin
CODE BYTE Str_GAUGE_STEP_E[] = {'G','a','u','g','e',' ', 'S','e','t','u','p',0};//WILLIAM-V1.43-970325
CODE BYTE Str_GAUGE_RECALL_E[] = {'G','a','u','g','e',' ', 'R','e','c','a','l','l',0};//WILLIAM-V1.43-970325
#ifdef TW8816
CODE BYTE Str_PRIORITY_E[] = {'P','R','I','O','R','I','T','Y',0};//ryan@21071011
#else
CODE BYTE Str_PRIORITY_E[] = {'P','r','i','o','r','i', 't','y',0};//WILLIAM-V1.43-970325
#endif
CODE BYTE Str_ReverseMode_E[]={'R','e','v','e','r','s',' ','M','o','d','e',0};

CODE BYTE Str_Resolution_E[] = {'R','e','s','o','l','u', 't','i','o','n',0};
CODE BYTE Str_FPS_E[] = {'F','P','S',0};
CODE BYTE Str_Quality_E[] = {'Q','u','a','l','i', 't','y',0};
CODE BYTE Str_RecordMode_E[] = {'R','e','c','o','r','d',' ', 'M','o','d','e',0};
CODE BYTE Str_RecordLength_E[] = {'R','e','c','o','r','d',' ','L','e','n','g','t','h',0};
CODE BYTE Str_PreAlarmLength_E[] = {'P','r','e','-','a','l','a','r','m',0};
CODE BYTE Str_PostAlarmLength_E[] = {'P','o','s','t','-','r','e','c','o','r','d',0};
CODE BYTE Str_Apply_E[] = {'A','p','p','l','y',0};
CODE BYTE Str_ManualRecordStart_E[] = {'R','e','c','o','r','d','S','t','a','r','t',0};
CODE BYTE Str_ManualRecordStop_E[] = {'R','e','c','o','r','d','S','t','o','p',0};
CODE BYTE Str_Snapshot_E[] = {'S','n','a','p','s','h', 'o','t',0};
CODE BYTE Str_DateTime_E[] = {'D','a','t','e',' ','T','i', 'm','e',0};
CODE BYTE Str_Year_E[] = {'Y','e','a','r',0};
CODE BYTE Str_Month_E[] = {'M','o','n','t','h',0};
CODE BYTE Str_Day_E[] = {'D','a','y',0};
CODE BYTE Str_Hour_E[] = {'H','o','u','r',0};
CODE BYTE Str_Minute_E[] = {'M','i','n',0};
CODE BYTE Str_Secord_E[] = {'S','e','c',0};
CODE BYTE Str_DaylightSaving_E[] = {'D','a','y','l','i','g','h','t','S','a','v','i','n','g',0};
CODE BYTE Str_TimeBegines_E[] = {'B','e','g','i','n','e',0};
CODE BYTE Str_Standard_E[] = {'E','n','d',0};
CODE BYTE Str_Week_E[]={'W','e','e','k',0};
CODE BYTE Str_Time_E[]={'T','i','m','e',0};
CODE BYTE Str_TimeZone_E[]={'T','i','m','e',' ','Z','o','n','e',0};
CODE BYTE Str_RETURNAPPLY_E[] = {'R','e','t','u','r','n','&','A','p','p','l','y',0};
CODE BYTE Str_FormatSD_E[]={'F','o','r','m','a','t',' ','S','D',' ','C','a','r','d',0};
CODE BYTE Str_AudioRecord_E[]={'A','u','d','i','o',' ','R','e','c','o','r','d',0};
CODE BYTE Str_FirmwareUpdate_E[]={'F','i','r','m','w','a','r','e',' ','U','p','d','a','t','e',0};
CODE BYTE Str_YES_E[]={'Y','e','s',0};
CODE BYTE Str_NO_E[]={'N','o',0};
CODE BYTE Str_FirstNumber_E[]={'F','i','r','s','t',' ','N','u','m','b','e','r',0};
CODE BYTE Str_SecondNumber_E[]={'S','e','c','o','n','d',' ','N','u','m','b','e','r',0};
CODE BYTE Str_ThirdNumber_E[]={'T','h','i','r','d',' ','N','u','m','b','e','r',0};
CODE BYTE Str_FourthNumber_E[]={'F','o','u','r','t','h',' ','N','u','m','b','e','r',0};
CODE BYTE Str_ChangePassword_E[]={'C','h','a','n','g','e',' ','P','a','s','s','w','o','r','d',0};
CODE BYTE Str_OverWrite_E[]={'O','v','e','r','W','r','i','t','e',0};
#ifdef AWT_ML072Q
CODE BYTE Str_TriggerSet_E[]={'D','i','r',' ','I','m','a','g','e',0};
#else
CODE BYTE Str_TriggerSet_E[]={'T','r','i','g','g','e','r',' ','S','e','t',0};
#endif
CODE BYTE Str_TriggerVGA_E[]={'T','r','i','g','g','e','r',' ','V','G','A',0};
CODE BYTE Str_TriggerDelay_E[]={'T','r','i','g','g','e','r',' ','D','e','l','a','y',0};
CODE BYTE Str_Informmation_E[]={'I','n','f','o','r','m','a','t','i','o','n',0};
CODE BYTE Str_UpdateConfig_E[]={'U','p','d','a','t','e',' ','C','o','n','f','i','g',0};
CODE BYTE Str_SDCARDCOVERDET_E[]={'S','D',' ','c','o','v','e','r',' ','D','e','t','.',0};


#ifdef AWT_ADD_TRIGGER_DELAY_FUN  //Pinchi 20150209 add
//CODE BYTE Str_TriggerDelay_E[] = {'T','r','i','g','g','e','r',' ','D','e','l','a','y',0};
CODE BYTE Str_CamADelay_E[] = {'C','A','M',' ','A',0};
CODE BYTE Str_CamBDelay_E[] = {'C','A','M',' ','B',0};
#ifdef AWT_ML072S
CODE BYTE Str_CamCDelay_E[] = {'A','V',' ',' ',' ',0};
#else
CODE BYTE Str_CamCDelay_E[] = {'C','A','M',' ','C',0};
#endif
CODE BYTE Str_CamRDelay_E[] = {'C','A','M',' ','R',0};
#endif

#ifdef AWT_ML072S
CODE BYTE Str_AVDelay_E[] = {'A','V',' ',' ','R',0};
#endif

#ifdef AWT_ML072S
CODE BYTE Str_DISPLAY_E[]={'C','A','M',' ','N','a','m','e',0}; 
#else
CODE BYTE Str_DISPLAY_E[]={'D','i','s','p','l','a','y',0}; 
#endif
CODE BYTE Str_DVR_DISPLAY_E[]={'D','V','R',' ','D','i','s','p','l','a','y',0}; 
CODE BYTE Str_DISTANCE_E[]={'D','i','s','t','a','n','c','e',' ','G','a','u','g','e',0}; 
CODE BYTE Str_OSD_LOCK_E[]={'O','S','D',' ','L','o','c','k',0}; 
CODE BYTE Str_PASSWORD_E[]={'P','a','s','s','w','o','r','d',0}; 
CODE BYTE Str_SOURCE_TITLE_E[]={'S','o','u','r','c','e',' ','T','i','t','l','e',0}; 
CODE BYTE Str_CVBSA_E[]={'C','V','B','S',' ','A',0};
CODE BYTE Str_CVBSB_E[]={'C','V','B','S',' ','B',0};
CODE BYTE Str_CVBSC_E[]={'C','V','B','S',' ','C',0};
CODE BYTE Str_CVBSR_E[]={'C','V','B','S',' ','R',0};
CODE BYTE Str_Auto_Day_Night_E[]={'A','u','t','o',' ','D','a','y','&','N','i','g','h','t',0};
CODE BYTE Str_DIR_IMAGE_E[]={'D','i','r',' ','I','m','a','g','e',0};
CODE BYTE Str_DIR_IMAGE_CAMA_E[]={'D','i','r',' ','I','m','a','g','e',' ','A',0};
CODE BYTE Str_DIR_IMAGE_CAMB_E[]={'D','i','r',' ','I','m','a','g','e',' ','B',0};
CODE BYTE Str_DIR_IMAGE_CAMC_E[]={'D','i','r',' ','I','m','a','g','e',' ','C',0};
CODE BYTE Str_REAR_SETUP_E[]={'R','e','a','r',' ','S','e','t','u','p',0};
#ifdef AWT_ML072S		//william @20130902 v1.0.1.2
	#ifdef TW8816
	CODE BYTE Str_CAMA_E[]={'C','A','M',' ','A',' ','M','I','R','R','O','R',0};
	CODE BYTE Str_CAMR_E[]={'C','A','M',' ','R',' ','M','I','R','R','O','R',0};
	#else
	CODE BYTE Str_CAMA_E[]={'C','A','M',' ','A',' ','M','i','r','r','o','r',0};
	CODE BYTE Str_CAMR_E[]={'C','A','M',' ','R',' ','M','i','r','r','o','r',0};
	#endif
#else
CODE BYTE Str_CAMA_E[]={'C','A','M',' ','A',0};
CODE BYTE Str_CAMR_E[]={'C','A','M',' ','R',0};
#endif
#ifdef HS
CODE BYTE Str_CAMB_E[]={'C','A','M',' ','B',' ','M','I','R','R','O','R',0};
#else
CODE BYTE Str_CAMB_E[]={'C','A','M',' ','B',0};
#endif
CODE BYTE Str_CAMC_E[]={'C','A','M',' ','C',0};
CODE BYTE Str_CAMD_E[]={'C','A','M',' ','D',0};

#ifdef RS485	
CODE BYTE Str_RS485_E[] = {'R','S','4','8','5',0};
CODE BYTE Str_CAMNumber_E[] = {'C','a','m','e','r','a',' ','I','D',0};//TM0350-980227

CODE BYTE Str_CAMNumber_F[] = {'C','a','m',0x5c,'r','a',' ','I','D',0};
CODE BYTE Str_CAMNumber_G[] = {'K','a','m','e','r','a',' ','I','D',0};
CODE BYTE Str_CAMNumber_DUT[] = {'C','a','m','e','r','a',' ','I','D',0};
CODE BYTE Str_CAMNumber_DAN[] = {'K','a','m','e','r','a',' ','I','D',0};
CODE BYTE Str_CAMNumber_S[] = {'C','a','m','e','r','a',' ','I','D',0};//TM0350-980227
CODE BYTE Str_CAMNumber_I[] = {'F','o','t','o','c','a','m','e','r','a',' ','I','D',0};
CODE BYTE Str_CAMNumber_C[] = {RAMFONT,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,ROMFONT,0};//TM0350-980227
CODE BYTE Str_CAMNumber_J[] = {RAMFONT,0x1C,0x1D,0x1E,0x1F,0x20,0x21,ROMFONT,'I','D',0};//TM0350-980227

CODE BYTE Str_Pelco_E[] = {'P','E','L','C','O',0};//TM0350-980227

CODE BYTE Str_Baud_rate_E[] = {'B','a','u','d',' ','r','a','t','e',0};//TM0350-980227.
CODE BYTE Str_Baud_rate_F[] = {'B','a','u','d',' ','r','a','t','e',0};//TM0350-980227.
CODE BYTE Str_Baud_rate_G[] = {'B','a','u','d',' ','r','a','t','e',0};//TM0350-980227.
CODE BYTE Str_Baud_rate_DUT[] = {'B','a','u','d',' ','r','a','t','e',0};//TM0350-980227.
CODE BYTE Str_Baud_rate_DAN[] = {'B','a','u','d',' ','r','a','t','e',0};//TM0350-980227.
CODE BYTE Str_Baud_rate_S[] = {'V','e','l','o','c','i','d','a','d',' ','B','a','u','d',0};//TM0350-980227.
CODE BYTE Str_Baud_rate_I[] = {'V','e','l','o','c','i','t',0x9b,' ','B','a','u','d',0};//TM0350-980227.
CODE BYTE Str_Baud_rate_C[] = {RAMFONT,0xB4,0xB5,0xB6,0xB7,ROMFONT,0};//TM0350-980227
CODE BYTE Str_Baud_rate_J[] = {RAMFONT,0x22,0x23,0x0F,0x24,0x25,0x48,0x26,0x27,0x0F,0x28,0x29,ROMFONT,0};//TM0350-980227

CODE BYTE Str_CameraOSD_E[] = {'C','a','m','e','r','a',' ','O','S','D',0};//TM0350-980227

#endif

//--------------------------------------------------------------------------------

//==================================================================================
//
//   Choice Menu String define in osd menu.
//
//==================================================================================
// Form
// 
//struct EnumType {
//	BYTE    Sz;
//	BYTE    ByLang;
//	BYTE	Str[15];			// doesn't matter size of the string !!!
//};


CODE BYTE OSDLangString[] = 
{
		0x02, // Size 
		0, // Independence by language:0, Dependenced by language:1 
//					 Language I			Language II			Language III....
		'E','n','g','l','i','s','h',0,	
        'F', 'r', 'a', 'n', 0x7b, 'a', 'i', 's',0,
        'D', 'e', 'u', 't', 's', 'c', 'h',0,
        'E', 's', 'p', 'a', 0x7e, 'o', 'l',0,
		RAMFONT,0x6a,0x23,0x56,ROMFONT,' ',0
};

CODE BYTE ModeChoice[] =		{
		0x04, // Size 
		1,
		'M','o','d','e','1',0,	'M','o','d','e','2',0, 'M','o','d','e','3',0,	'U','s','e','r',0,
		'M','o','d','e','1',0,	'M','o','d','e','2',0, 'M','o','d','e','3',0,	'U','s','a','g','e','r',0,
		'M','o','d','u','s','1',0, 'M','o','d','u','s','2',0, 'M','o','d','u','s','3',0, 'B','e','n','u','t','z','e','r',0,
		'M','o','d','o','1',0,	'M','o','d','o','2',0,	'M','o','d','o','3',0,	'U','s','u','a','r','i','o',0,
		RAMFONT,0x3a,0x34,ROMFONT,'1',0, RAMFONT,0x3a,0x34,ROMFONT,'2',0,	RAMFONT,0x3a,0x34,ROMFONT,'3',0, RAMFONT,0x47,0x51,0x5b,0x71,ROMFONT,' ',0  // Caution!: Do not end to osd control command "ROMFONT" or "RAMFONT". 
};

CODE BYTE VInputStdChoice[] = {
			0x08,//size of supported system.(Attention!!)
			0,// None by language.
			'A','u','t','o',0,
			'N','T','S','C',0,
#ifdef SUPPORT_PAL
			'P','A','L',0,
#endif
#ifdef SUPPORT_SECAM
			'S','E','C','A','M',0,	
#endif
#ifdef SUPPORT_NTSC4
			'N','T','S','C','4','.','4','3',0,	
#endif
#ifdef SUPPORT_PALM
			'P','A','L','M',0,	
#endif
#ifdef SUPPORT_PALN
			'P','A','L','N',0,	
#endif
#ifdef SUPPORT_PAL60
			'P','A','L','6','0',0,	
#endif
};

#ifdef WIDE_SCREEN
CODE BYTE WideScreenChoice[] = {
			5,//size 
			0,// by language.
			'N','o','r','m','a','l',0, 			'W','i','d','e',0, 			'P','a','n','o','r','a','m','a',0,	'F','u','l','l',0,//			'Z','o','o','m',0,
};
#endif

#ifdef SUPPORT_OSDPOSITIONMOVE
CODE BYTE OsdPositionModeChoice[] = {
			5,//size
			0,// by language.
			RAMFONT,0x1a,0x1b,ROMFONT,' ',0,				RAMFONT,0x1c,0x1d,ROMFONT,' ',0,
			RAMFONT,0x1e,0x1d,ROMFONT,' ',0,				RAMFONT,0x1f,0x20,ROMFONT,' ',0,
			RAMFONT,0x1f,0x21,ROMFONT,' ',0,
};
#endif


CODE BYTE CaptionChoice[] = {
			0x09,//size
			0,// None by lang.
			'O','f','f',0,	'C','C','1',0,	'C','C','2',0,	'C','C','3',0,	'C','C','4',0,
			'T','1',0,		'T','2',0,		'T','3',0,		'T','4',0,

};

CODE BYTE ONOFFChoiceString[] = {
            0x02, //size
            0,      // None by lang.
            'O','N',0, 
            'O','F','F',0};

CODE BYTE NMhoiceString[] = {
            0x02, //size
            0,      // None by lang.
            'M','I','R','R','O','R',0, 
            'N','O','R','M','A','L',0};			

CODE BYTE DayChoiceString[] = {
            0x03, //size
            0,      // None by lang.
            'D','a','y',0, 
            'A','U','T','O',0,
            'N','i','g','h','t',0};

CODE BYTE ReversModeString[]={
         0x02,
		 0,
		 '1','6',':','9',0,
		 '4',':','3',0,
 };
			
CODE BYTE ONOFFChoiceString1[] = {
            0x02, //size
            0,      // None by lang.
            0,      // None by lang.
            'O','N',0, 
            'O','F','F',0};
//-----------------------------------------------------HS Andy AWT 980827

#ifdef HTRV  //Pinchi 20150825 add
CODE BYTE IMAGEString[]={
	         0x03, //size
             0,      // None by lang.
             'S','I','N','G','L','E',0,
             'D','U','A','L',0,
             'T','R','I','P','L','E',0
             };
#else
CODE BYTE IMAGEString[]={
	         0x04, //size
             0,      // None by lang.
             'S','I','N','G','L','E',0,
             'D','U','A','L',0,
             'T','R','I','P','L','E',0,
             'A','+','B',',','B','+','A',0};
#endif

CODE BYTE IMAGE_A_String[]={
	         0x07, //size
             0,      // None by lang.
             'A',0,
             'A','+','B',0,
             'A','+','C',0,
             'A','+','R',0,
             'A','+','B','C',0,
             'A','+','B','R',0,
             'A','+','C','R',0,
             };

CODE BYTE IMAGE_B_String[]={
	         0x07, //size
             0,      // None by lang.
             'B',0,
             'B','+','A',0,
             'B','+','C',0,
             'B','+','R',0,
             'B','+','A','C',0,
             'B','+','A','R',0,
             'B','+','C','R',0,
             };

CODE BYTE IMAGE_C_String[]={
	         0x07, //size
             0,      // None by lang.
             'C',0,
             'C','+','A',0,
             'C','+','B',0,
             'C','+','R',0,
             'C','+','A','B',0,
             'C','+','A','R',0,
             'C','+','B','R',0,
             };

#ifdef HTRV  //Pinchi 20150825 add
CODE BYTE REARString[]={
	         0x06, //size
             0,      // None by lang.
             'R',0,
             'R','+','A',0,
             'R','+','B',0,
             'R','/','A','B',0,
             'R','+','A','B',0,
             'R','/','C',0
     };
#else
CODE BYTE REARString[]={
	         0x0a,  //Pinchi 20150825 change the number  //0x05, //size
             0,      // None by lang.
             'R',0,
             'R','+','A',0,
             'R','+','B',0,
             'R','+','C',0,
             'R','/','A','B',0,
             'R','/','A','C',0,
             'R','/','B','C',0,
             'R','+','A','B',0,
             'R','+','A','C',0,
             'R','+','B','C',0
    };
#endif

#ifdef QUAD
CODE BYTE JUMPString[]={
	#ifdef HTRV  //Pinchi 20150825 add
	      0x0f,
	#else
	      0x0e,
	#endif
	      0,
	      'Q','U','A','D',0,
	      'S','E','Q',0,
	      'A','+','B',0,
	      'C','+','R',0,
// 2007.4.10 Justin                            add for AR,RB,AC,CB MODE	      
	      'A','+','R',0,
	      'R','+','B',0,	     
	      'A','+','C',0,
	      'C','+','B',0,	
// 2007.4.10 Justin                            add for AR,RB,AC,CB MODE	      
	      'R','/','A','B',0,
	      'R','+','A','B',0,
	#ifdef HTRV  //Pinchi 20150825 add
		  'R','/','C',0,
	#endif
	      'A',0,
	      'B',0,
	      'C',0,
	      'R',0,
	   #ifdef USE_CAMD   
	      'D',0
	   #endif   
	      //'V','G','A',0
	};

CODE BYTE CAMOUTString[]={  //Pinchi 20150825 move to QUAD #define
      0x05,
      0,
      'Q','U','A','D',0,
    #if 1  //Pinchi 20150825 add
      'C','A','M','A',0,
      'C','A','M','B',0,
      'C','A','M','C',0,
      'C','A','M','R',0
    #else
      'A',0,
      'B',0,
      'C',0,
      'R',0
    #endif
    };

#else
CODE BYTE JUMPString[]={
	      0x05,
	      0,
	      'A',0,
	      'B',0,
	      'R',0,
	      'S','E','Q',0,
	};
#endif

//---------------DVR ChoiceString-----------------

CODE BYTE ResolutionChoiceString[] = {
            0x02, //size
            0,      // None by lang.
            0,      // None by lang.
            '7','2','0','x','4','8','0',0, 
            '3','5','2','x','2','4','0',0, };

CODE BYTE FPSChoiceString[] = {
            0x05, //size
            0,      // None by lang.
            0,      // None by lang.
            '5',0,
            '1','0',0, 
            '1','5',0, 
            '2','0',0,
            '2','5',0,
            '3','0',0};

CODE BYTE QualityChoiceString[] = {
            0x05, //size
            0,      // None by lang.
            0,      // None by lang
            'L','e','v','e','l','-','1',0,
            'L','e','v','e','l','-','2',0, 
            'L','e','v','e','l','-','3',0, 
            'L','e','v','e','l','-','4',0,
            'L','e','v','e','l','-','5',0,};

CODE BYTE RecordModeChoiceString[] = {
            0x03, //size
            0,      // None by lang.
            0,      // None by lang
            'N','o','n','e',0, 
            'N','o','r','m','a','l',0, 
            'A','l','a','r','m',0};


CODE BYTE RecordLengthChoiceString[] = {
            0x06, //size
            0,      // None by lang.
            0,      // None by lang
            '1',' ',' ','m','i','n',0, 
            '2',' ',' ','m','i','n',0, 
            '3',' ',' ','m','i','n',0,
            '4',' ',' ','m','i','n',0,
            '5',' ',' ','m','i','n',0,
            '1','0',' ','m','i','n',0};


CODE BYTE PreAlarmLengthChoiceString[] = {
            0x05, //size
            0,      // None by lang.
            0,      // None by lang
            '1','5',' ','s','e','c',0, 
            '3','0',' ','s','e','c',0, 
            '6','0',' ','s','e','c',0
            //'2','5',' ','s','e','c',0,
            //'3','0',' ','s','e','c',0
            };

CODE BYTE PostAlarmLengthChoiceString[] = {
            0x08, //size
            0,      // None by lang.
            0,      // None by lang
            '1','5',' ','s','e','c',0, 
            '3','0',' ','s','e','c',0, 
            '6','0',' ','s','e','c',0
            //'6','0',' ','s','e','c',0,
            //'1','2','0','s','e','c',0,
            //'3','0','0','s','e','c',0,
            //'6','0','0','s','e','c',0,
            //'9','0','0','s','e','c',0
            };

CODE BYTE DaylightSavingChoiceString[] = {
            0x02, //size
            0,      // None by lang.
            0,      // None by lang
            'D','i','s','a','b','l','e',0, 
            'E','n','a','b','l','e',0};

CODE BYTE TimeBeginesWeekChoiceString[] = {
            0x04, //size
            0,      // None by lang.
            0,      // None by lang
            'F','i','r','s','t',0,
            'S','e','c','o','n','d',0, 
            'T','h','i','r','d',0, 
            'F','o','u','r','t','h',0,};

CODE BYTE AudioRecordChoiceString[]={
	      0x04,
	      0,
	      'A',0,
	      'B',0,
	      'C',0,
	      'R',0};

CODE BYTE TimeZoneChoiceString[]={
	      0x019,
	      0,
	      0,      // None by lang
	      '-','1','2',0,
	      '-','1','1',0,
	      '-','1','0',0,
	      '-','9',0,
	      '-','8',0,
	      '-','7',0,
	      '-','6',0,
	      '-','5',0,
	      '-','4',0,
	      '-','3',0,
	      '-','2',0,
	      '-','1',0,
	      '0',0,
	      '1',0,
	      '2',0,
	      '3',0,
	      '4',0,
	      '5',0,
	      '6',0,
	      '7',0,
	      '8',0,
	      '9',0,
	      '1','0',0,
	      '1','1',0,
	      '1','2',0};

CODE BYTE PDChoiceString[] = {
            0x02, //size
            0,      // None by lang.
            'P',' ',0, 
            'D',' ',0};

CODE BYTE bpsChoiceString[]={
	      0x03,
	      0,
	      '2','4','0','0',0,
          '4','8','0','0',0,
          '9','6','0','0',0};

CODE BYTE ONOFFChineseChoiceString[] = {
            0x02, //size
            0,      // None by lang.
            RAMFONT,0x18,0x19,ROMFONT,' ',0,
            RAMFONT,0x1a,0x1b,ROMFONT,' ',0,};

CODE BYTE IMAGEChineseString[]={
	      0x04, //size
             0,      // None by lang.
            RAMFONT,0x1c,0x1d,0x1e,0x1f,0x20,0x21,ROMFONT,' ',0,
            RAMFONT,0x22,0x23,0x28,0x29,0x2a,0x2b,ROMFONT,' ',0,
            RAMFONT,0x24,0x25,0x28,0x29,0x2a,0x2b,ROMFONT,' ',0,
             'A','+','B',',','B','+','A',0};

CODE BYTE JUMPChineseString[]={
	      0x0e,
	      0,
	     RAMFONT,0x26,0x27,0x28,0x29,0x2a,0x2b,ROMFONT,' ',0,
	      'S','E','Q',0,
	      'A','+','B',0,
	      'C','+','R',0,
// 2007.4.10 Justin                            add for AR,RB,AC,CB MODE	      
	      'A','+','R',0,
	      'R','+','B',0,	     
	      'A','+','C',0,
	      'C','+','B',0,	
// 2007.4.10 Justin                            add for AR,RB,AC,CB MODE	      
	      'R','/','A','B',0,
	      'R','+','A','B',0,
	      'A',0,
	      'B',0,
	      'C',0,
	      'R',0,
	      'V','G','A',0
	      };		  
		  
CODE BYTE 	*Str_Version[] =	{Str_Version_E,Str_Version_E,Str_Version_E,Str_Version_E,Str_Version_E};
CODE BYTE 	*Str_LCDVersion[] =	{Str_LCDVersion_E,Str_LCDVersion_E,Str_LCDVersion_E,Str_LCDVersion_E,Str_LCDVersion_E};
CODE BYTE 	*Str_DVRVersion[] =	{Str_DVRVersion_E,Str_DVRVersion_E,Str_DVRVersion_E,Str_DVRVersion_E,Str_DVRVersion_E};

CODE BYTE 	*Str_WIFI_IP[] =	{Str_WIFI_IP_E,Str_WIFI_IP_E,Str_WIFI_IP_E,Str_WIFI_IP_E,Str_WIFI_IP_E};
CODE BYTE 	*Str_WIFI_MAC[] =	{Str_WIFI_MAC_E,Str_WIFI_MAC_E,Str_WIFI_MAC_E,Str_WIFI_MAC_E,Str_WIFI_MAC_E};
CODE BYTE 	*Str_GETWAY[] =	{Str_GETWAY_E,Str_GETWAY_E,Str_GETWAY_E,Str_GETWAY_E,Str_GETWAY_E};

//--------------------------------------------------------------------------------
#if 0
CODE BYTE 	*Enter_Password_Str[]={Enter_Password_Str_E,Enter_Password_Str_F,Enter_Password_Str_D,Enter_Password_Str_S,Enter_Password_Str_K};					   
#endif
CODE BYTE 	*CheckPCCableStr[] =	{CheckPCCableStr_E};
CODE BYTE 	*OutOfRangeStr[] =	{OutOfRangeStr_E,OutOfRangeStr_E,OutOfRangeStr_E,OutOfRangeStr_E,OutOfRangeStr_K};
CODE BYTE 	*StrVolume[]=			{StrVolume_E};

#ifdef fullcode
CODE BYTE 	*CheckDTVCableStr[] = {CheckDTVCableStr_E,CheckDTVCableStr_E,CheckDTVCableStr_E,CheckDTVCableStr_E,CheckDTVCableStr_K};
CODE BYTE 	*MuteOnStr[]=			{MuteOnStr_E,MuteOnStr_E,MuteOnStr_E,MuteOnStr_E,MuteOnStr_K};
CODE BYTE 	*Str_Input[]=			{Str_Input_E,	Str_Input_F,	Str_Input_D,	Str_Input_S,	Str_Input_K};
CODE BYTE 	*Str_Picture[]=		{Str_Picture_E,	Str_Picture_F,	Str_Picture_D,	Str_Picture_S,	Str_Picture_K};
CODE BYTE 	*Str_Sound[]=			{Str_Sound_E,Str_Sound_E,Str_Sound_E,Str_Sound_S,Str_Sound_K};
CODE BYTE 	*Str_Utility[]=		{Str_Utility_E,Str_Utility_F,Str_Utility_D,Str_Utility_S,Str_Utility_K};
CODE BYTE 	*Str_ColorTemp[]=		{Str_ColorTemp_E,Str_ColorTemp_F,Str_ColorTemp_D,Str_ColorTemp_S,Str_ColorTemp_K};
CODE BYTE 	*Str_Comments[]=		{Str_Comments_E,Str_Comments_E,Str_Comments_E,Str_Comments_E,Str_Comments_K};
//============================================================================================
//  OSD Menu String Table
CODE BYTE 	*Str_Composite[] =	{Str_Composite_E,Str_Composite_E,Str_Composite_E,Str_Composite_E,Str_Composite_E};
#endif

//--------------------------------------------------------------------------------

#ifdef SUPPORT_SVIDEO
CODE BYTE 	*Str_Svideo[] =		{Str_Svideo_E,Str_Svideo_E,Str_Svideo_E,Str_Svideo_E,Str_Svideo_E};
#endif
#ifdef SUPPORT_COMPONENT
CODE BYTE 	*Str_Component[] =	{Str_Component_E,Str_Component_E,Str_Component_E,Str_Component_E,Str_Component_E};
#endif
#ifdef SUPPORT_DTV
CODE BYTE 	*Str_Dtv[] =			{Str_Dtv_E,Str_Dtv_E,Str_Dtv_E,Str_Dtv_E,Str_Dtv_E};
#endif
#ifdef SUPPORT_PC
CODE BYTE 	*Str_Pc[] = 			{Str_Pc_E,Str_Pc_E,Str_Pc_E,Str_Pc_E,Str_Pc_E};
#endif
#ifdef SUPPORT_DIGITALVGA
CODE BYTE 	*Str_DigitalVGA[] =   {Str_DigitalVGA_E,Str_DigitalVGA_E,Str_DigitalVGA_E,Str_DigitalVGA_E,Str_DigitalVGA_E};
#endif

#ifdef SUPPORT_PC
CODE BYTE 	*Str_VPosition[]=		{Str_VPosition_E,Str_VPosition_F,Str_VPosition_D,Str_VPosition_S,Str_VPosition_K};
CODE BYTE 	*Str_HPosition[]=		{Str_HPosition_E,Str_HPosition_F,Str_HPosition_D,Str_HPosition_S,Str_HPosition_K};
#endif

#ifdef SUPPORT_OSDPOSITIONMOVE
CODE BYTE 	*Str_OSDPosition[]=	{Str_OSDPosition_E,Str_OSDPosition_E,Str_OSDPosition_E,Str_OSDPosition_S,Str_OSDPosition_K};
#endif
CODE BYTE 	*Str_OSDLang[]=		{Str_OSDLang_E,Str_OSDLang_F,Str_OSDLang_D,Str_OSDLang_S,Str_OSDLang_K};
//CODE BYTE 	*Str_SleepTimer[]=	{Str_SleepTimerE,Str_SleepTimerE,Str_SleepTimerE,Str_SleepTimerE,Str_SleepTimerK};

#ifdef E_Wintek
CODE BYTE 	*Str_AutoAdjust2[]=	{Str_AutoAdjust_C};
CODE BYTE 	*Str_Brightness2[]=	{Str_Brightness_C};
CODE BYTE 	*Str_Contrast2[]=	{Str_Contrast_C};
CODE BYTE 	*Str_Saturation2[]=	{Str_Saturation_C};
CODE BYTE 	*Str_RETURN2[]=		{Str_RETURN_C};

CODE BYTE *Str_Auto_Day_Night2[]={Str_Auto_Day_Night_C};
CODE BYTE *Str_DIR_IMAGE2[]={Str_DIR_IMAGE_C};
CODE BYTE *Str_REAR_SETUP2[]={Str_REAR_SETUP_C};
CODE BYTE *Str_JUMP2[]={Str_JUMP_C};
CODE BYTE *Str_RECALL2[]={Str_RECALL_C};
CODE BYTE *Str_EXIT2[]={Str_EXIT_C};

CODE BYTE 	*StrVolume2[]=			{StrVolume_C};
#endif
#ifdef SUPPORT_PC
CODE BYTE 	*Str_Phase[]=			{Str_Phase_E,Str_Phase_E,Str_Phase_E,Str_Phase_S,Str_Phase_E};
CODE BYTE 	*Str_Clock[]=			{Str_Clock_E,Str_Clock_F,Str_Clock_D,Str_Clock_S,Str_Clock_E};
CODE BYTE 	*Str_AutoColor[]=		{Str_AutoColor_E,Str_AutoColor_E,Str_AutoColor_E,Str_AutoColor_E,Str_AutoColor_K};
CODE BYTE 	*Str_AutoAdjust[]=	{Str_AutoAdjust_E,Str_AutoAdjust_E,Str_AutoAdjust_E,Str_AutoAdjust_E,Str_AutoAdjust_K};
#endif

#ifdef fullcode
CODE BYTE 	*Str_VInputStd[]=		{Str_VInputStd_E,Str_VInputStd_E,Str_VInputStd_E,Str_VInputStd_E,Str_VInputStd_E};
CODE BYTE 	*Str_Information[]=	{Str_Information_E,Str_Information_E,Str_Information_E,Str_Information_E,Str_Information_E};
CODE BYTE 	*Str_Treble[]=		{Str_Treble_E,Str_Treble_F,Str_Treble_D,Str_Treble_S,Str_Treble_K};
CODE BYTE 	*Str_Bass[]=			{Str_Bass_E,Str_Bass_F,Str_Bass_D,Str_Bass_S,Str_Bass_K};
CODE BYTE 	*Str_Balance[]=		{Str_Balance_E,Str_Balance_F,Str_Balance_D,Str_Balance_S,Str_Balance_K};
CODE BYTE 	*Str_Red[]=			{Str_Red_E,Str_Red_F,Str_Red_D,Str_Red_S,Str_Red_K};
CODE BYTE 	*Str_Blue[]=			{Str_Blue_E,Str_Blue_F,Str_Blue_D,Str_Blue_S,Str_Blue_K};
CODE BYTE 	*Str_Green[]=			{Str_Green_E,Str_Green_F,Str_Green_D,Str_Green_S,Str_Green_K};
CODE BYTE 	*Str_Backlight[]=		{Str_Backlight_E,Str_Backlight_F,Str_Backlight_D,Str_Backlight_S,Str_Backlight_K};
#endif

CODE BYTE 	*Str_Brightness[]=	{Str_Brightness_E,Str_Brightness_F,Str_Brightness_D,Str_Brightness_S,Str_Brightness_K};
CODE BYTE 	*Str_Contrast[]=		{Str_Contrast_E,Str_Contrast_F,Str_Contrast_D,Str_Contrast_S,Str_Contrast_K};
CODE BYTE 	*Str_Saturation[]=	{Str_Saturation_E,Str_Saturation_E,Str_Saturation_D,Str_Saturation_S,Str_Saturation_K};
CODE BYTE 	*Str_Hue[]=			{Str_Hue_E,Str_Hue_F,Str_Hue_D,Str_Hue_S,Str_Hue_K};
CODE BYTE 	*Str_Sharpness[]=		{Str_Sharpness_E,Str_Sharpness_F,Str_Sharpness_D,Str_Sharpness_S,Str_Sharpness_K};
CODE BYTE 	*Str_Reset[]=			{Str_Reset_E,Str_Reset_F,Str_Reset_D,Str_Reset_S,Str_Reset_K};

//----------------------------------------------------------------------------------------------HS_Andy AWT84 20090811
CODE BYTE *Str_MIRROR[]={Str_MIRROR_E,Str_MIRROR_E,Str_MIRROR_E,Str_MIRROR_E,Str_MIRROR_E};
CODE BYTE *Str_JUMP[]={Str_JUMP_E,Str_JUMP_E,Str_JUMP_E,Str_JUMP_E,Str_JUMP_E};
CODE BYTE *Str_SEQ_TIME_STEP[]={Str_SEQ_TIME_STEP_E,Str_SEQ_TIME_STEP_E,Str_SEQ_TIME_STEP_E,Str_SEQ_TIME_STEP_E,Str_SEQ_TIME_STEP_E}; 
CODE BYTE *Str_CAM_OUT[]={Str_CAM_OUT_E,Str_CAM_OUT_E,Str_CAM_OUT_E,Str_CAM_OUT_E,Str_CAM_OUT_E};
CODE BYTE *Str_JumpAV[]={Str_JumpAV_E};		//william @20130902 v1.0.1.2
CODE BYTE *Str_RETURN[]={Str_RETURN_E,Str_RETURN_E,Str_RETURN_E,Str_RETURN_E,Str_RETURN_E};
CODE BYTE *Str_RECALL[]={Str_RECALL_E,Str_RECALL_E,Str_RECALL_E,Str_RECALL_E,Str_RECALL_E};
CODE BYTE *Str_MonitorRECALL[]={Str_MonitorRECALL_E,Str_MonitorRECALL_E,Str_MonitorRECALL_E,Str_MonitorRECALL_E,Str_MonitorRECALL_E};
CODE BYTE *Str_DVRRECALL[]={Str_DVRRECALL_E,Str_DVRRECALL_E,Str_DVRRECALL_E,Str_DVRRECALL_E,Str_DVRRECALL_E};
CODE BYTE *Str_EXIT[]={Str_EXIT_E,Str_EXIT_E,Str_EXIT_E,Str_EXIT_E,Str_EXIT_E};
CODE BYTE *Str_DISPLAY[]={Str_DISPLAY_E,Str_DISPLAY_E,Str_DISPLAY_E,Str_DISPLAY_E,Str_DISPLAY_E};
CODE BYTE *Str_DVR_DISPLAY[]={Str_DVR_DISPLAY_E,Str_DVR_DISPLAY_E,Str_DVR_DISPLAY_E,Str_DVR_DISPLAY_E,Str_DVR_DISPLAY_E};
CODE BYTE *Str_DISTANCE[]={Str_DISTANCE_E,Str_DISTANCE_E,Str_DISTANCE_E,Str_DISTANCE_E,Str_DISTANCE_E};
CODE BYTE *Str_OSD_LOCK[]={Str_OSD_LOCK_E,Str_OSD_LOCK_E,Str_OSD_LOCK_E,Str_OSD_LOCK_E,Str_OSD_LOCK_E};
CODE BYTE *Str_PASSWORD[]={Str_PASSWORD_E,Str_PASSWORD_E,Str_PASSWORD_E,Str_PASSWORD_E,Str_PASSWORD_E};
CODE BYTE *Str_SOURCE_TITLE[]={Str_SOURCE_TITLE_E,Str_SOURCE_TITLE_E,Str_SOURCE_TITLE_E,Str_SOURCE_TITLE_E,Str_SOURCE_TITLE_E};
CODE BYTE *Str_CVBSA[]={Str_CVBSA_E,Str_CVBSA_E,Str_CVBSA_E,Str_CVBSA_E,Str_CVBSA_E};
CODE BYTE *Str_CVBSB[]={Str_CVBSB_E,Str_CVBSB_E,Str_CVBSB_E,Str_CVBSB_E,Str_CVBSB_E};
CODE BYTE *Str_CVBSC[]={Str_CVBSC_E,Str_CVBSC_E,Str_CVBSC_E,Str_CVBSC_E,Str_CVBSC_E};
CODE BYTE *Str_CVBSR[]={Str_CVBSR_E,Str_CVBSR_E,Str_CVBSR_E,Str_CVBSR_E,Str_CVBSR_E};
CODE BYTE *Str_Auto_Day_Night[]={Str_Auto_Day_Night_E,Str_Auto_Day_Night_E,Str_Auto_Day_Night_E,Str_Auto_Day_Night_E,Str_Auto_Day_Night_E};
CODE BYTE *Str_DIR_IMAGE[]={Str_DIR_IMAGE_E,Str_DIR_IMAGE_E,Str_DIR_IMAGE_E,Str_DIR_IMAGE_E,Str_DIR_IMAGE_E};
CODE BYTE *Str_DIR_IMAGE_CAMA[]={Str_DIR_IMAGE_CAMA_E};//Andy A1.4 990113
CODE BYTE *Str_DIR_IMAGE_CAMB[]={Str_DIR_IMAGE_CAMB_E};//Andy A1.4 990113
CODE BYTE *Str_DIR_IMAGE_CAMC[]={Str_DIR_IMAGE_CAMC_E};//Andy A1.4 990113CODE BYTE *Str_REAR_SETUP[]={Str_REAR_SETUP_E,Str_REAR_SETUP_E,Str_REAR_SETUP_E,Str_REAR_SETUP_E,Str_REAR_SETUP_E};
CODE BYTE *Str_REAR_SETUP[]={Str_REAR_SETUP_E,Str_REAR_SETUP_E,Str_REAR_SETUP_E,Str_REAR_SETUP_E,Str_REAR_SETUP_E};
CODE BYTE *Str_CAMA[]={Str_CAMA_E,Str_CAMA_E,Str_CAMA_E,Str_CAMA_E,Str_CAMA_E};
CODE BYTE *Str_CAMB[]={Str_CAMB_E,Str_CAMB_E,Str_CAMB_E,Str_CAMB_E,Str_CAMB_E};
CODE BYTE *Str_CAMC[]={Str_CAMC_E,Str_CAMC_E,Str_CAMC_E,Str_CAMC_E,Str_CAMC_E};
CODE BYTE *Str_CAMR[]={Str_CAMR_E,Str_CAMR_E,Str_CAMR_E,Str_CAMR_E,Str_CAMR_E};
CODE BYTE *Str_CAMD[]={Str_CAMD_E,Str_CAMD_E,Str_CAMD_E,Str_CAMD_E,Str_CAMD_E};
CODE BYTE *Str_SPACE[]={Str_SPACE_E}; 
CODE BYTE *Str_VER[]={Str_VER_E}; 
CODE BYTE *Str_TIMEOUT_STEP[]={Str_TIMEOUT_STEP_E};
CODE BYTE *Str_GAUGE_STEP[]={Str_GAUGE_STEP_E};
CODE BYTE *Str_GAUGE_RECALL[]={Str_GAUGE_RECALL_E};
CODE BYTE *Str_PRIORITY[]={Str_PRIORITY_E};

CODE BYTE *Str_ReversMode[]={Str_ReverseMode_E};//Andy holtz 981113

#ifdef AWT_ADD_TRIGGER_DELAY_FUN  //Pinchi 20150209 add
CODE BYTE *Str_TriggerDelay[] = {Str_TriggerDelay_E,Str_TriggerDelay_E,Str_TriggerDelay_E,Str_TriggerDelay_E,Str_TriggerDelay_E};
CODE BYTE *Str_CamADelay[] = {Str_CamADelay_E,Str_CamADelay_E,Str_CamADelay_E,Str_CamADelay_E,Str_CamADelay_E};
CODE BYTE *Str_CamBDelay[] = {Str_CamBDelay_E,Str_CamBDelay_E,Str_CamBDelay_E,Str_CamBDelay_E,Str_CamBDelay_E};
CODE BYTE *Str_CamCDelay[] = {Str_CamCDelay_E,Str_CamCDelay_E,Str_CamCDelay_E,Str_CamCDelay_E,Str_CamCDelay_E};
CODE BYTE *Str_CamRDelay[] = {Str_CamRDelay_E,Str_CamRDelay_E,Str_CamRDelay_E,Str_CamRDelay_E,Str_CamRDelay_E};
#endif

CODE BYTE *Str_Resolution[]={Str_Resolution_E};
CODE BYTE *Str_FPS[]={Str_FPS_E};
CODE BYTE *Str_Quality[]={Str_Quality_E};
CODE BYTE *Str_RecordMode[]={Str_RecordMode_E};
CODE BYTE *Str_RecordLength[]={Str_RecordLength_E};
CODE BYTE *Str_PreAlarmLength[]={Str_PreAlarmLength_E};
CODE BYTE *Str_PostAlarmLength[]={Str_PostAlarmLength_E};
CODE BYTE *Str_Apply[]={Str_Apply_E};
CODE BYTE *Str_ManualRecordStart[]={Str_ManualRecordStart_E};
CODE BYTE *Str_ManualRecordStop[]={Str_ManualRecordStop_E};
CODE BYTE *Str_Snapshot[]={Str_Snapshot_E};
CODE BYTE *Str_DateTime[]={Str_DateTime_E};
CODE BYTE *Str_Year[]={Str_Year_E};
CODE BYTE *Str_Month[]={Str_Month_E};
CODE BYTE *Str_Day[]={Str_Day_E};
CODE BYTE *Str_Hour[]={Str_Hour_E};
CODE BYTE *Str_Minute[]={Str_Minute_E};
CODE BYTE *Str_Secord[]={Str_Secord_E};
CODE BYTE *Str_DaylightSaving[]={Str_DaylightSaving_E};
CODE BYTE *Str_TimeBegines[]={Str_TimeBegines_E};
CODE BYTE *Str_Standard[]={Str_Standard_E};
CODE BYTE *Str_Week[]={Str_Week_E};
CODE BYTE *Str_Time[]={Str_Time_E};
CODE BYTE *Str_TimeZone[]={Str_TimeZone_E};
CODE BYTE *Str_RETURNAPPLY[]={Str_RETURNAPPLY_E};
CODE BYTE *Str_FormatSD[]={Str_FormatSD_E};
CODE BYTE *Str_AudioRecord[]={Str_AudioRecord_E};
CODE BYTE *Str_FirmwareUpdate[]={Str_FirmwareUpdate_E};
CODE BYTE *Str_YES[]={Str_YES_E};
CODE BYTE *Str_NO[]={Str_NO_E};
CODE BYTE *Str_FirstNumber[]={Str_FirstNumber_E};
CODE BYTE *Str_SecondNumber[]={Str_SecondNumber_E};
CODE BYTE *Str_ThirdNumber[]={Str_ThirdNumber_E};
CODE BYTE *Str_FourthNumber[]={Str_FourthNumber_E};
CODE BYTE *Str_ChangePassword[]={Str_ChangePassword_E};
CODE BYTE *Str_Str_OverWrite[]={Str_OverWrite_E};
CODE BYTE *Str_TriggerSet[]={Str_TriggerSet_E};
CODE BYTE *Str_TriggerVGA[]={Str_TriggerVGA_E};
//CODE BYTE *Str_TriggerDelay[]={Str_TriggerDelay_E};
CODE BYTE *Str_Informmation[]={Str_Informmation_E};
CODE BYTE *Str_UpdateConfig[]={Str_UpdateConfig_E};
CODE BYTE *Str_SDCARDCOVERDET[]={Str_SDCARDCOVERDET_E};

#ifdef RS485	
CODE BYTE *Str_RS485[]={Str_RS485_E};
CODE BYTE *Str_CAMNumber[]={Str_CAMNumber_E};// WILLIAM-V1.43-970325
CODE BYTE *Str_Pelco[]={Str_Pelco_E};// WILLIAM-V1.43-970325
CODE BYTE *Str_Baud_rate[]={Str_Baud_rate_E};// WILLIAM-V1.43-970325
CODE BYTE *Str_CameraOSD[]={Str_CameraOSD_E};
#endif
//-------------------------------------------------------------------------------------------------------------

#ifdef WIDE_SCREEN
CODE BYTE 	*Str_WideScreen[] =	{Str_WideScreen_E,Str_WideScreen_E,Str_WideScreen_E,Str_WideScreen_E,Str_WideScreen_K};
#endif

#endif


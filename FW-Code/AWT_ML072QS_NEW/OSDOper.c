#include "Config.h"

#include "typedefs.h"
#include "main.h"
#include "i2c.h"
#include "Tw88.h"
#include "measure.h"
#include "dispinfo.h"
#include "osdbasic.h"
#include "osdmenu.h"
#include "adc.h"
#include "debug.h"
#include "etc_eep.h"
#include "pc_eep.h"
#include "audio.h"
#include "printf.h"
#include "udfont.h"
#include "panel.h"

#include "rgbmix.h"		// for TW8801
#include "Externs.h"

CODE struct RegisterInfo UserRange={0,100,50};

CODE struct RegisterInfo OSDMenuYRange= { OSDMENUY_MIN,	OSDMENUY_MAX,	OSDMENUY_50		};				
CODE struct RegisterInfo OSDMenuXRange= { OSDMENUX_MIN, OSDMENUX_MAX,	OSDMENUX_50		};				

CODE struct RegisterInfo PCUserColorTempRange = { 0, 55, 28 };			

CODE struct RegisterInfo PanelContrastRange={	0,199,100};
//#ifdef AWT
CODE struct RegisterInfo PanelBrightnessRange={	45,210,128};
//#else
//CODE struct RegisterInfo PanelBrightnessRange={	45,128,97};		//{	45,210,128};
//#endif
CODE struct RegisterInfo PanelSharpnessRange={	0,7,3};
CODE struct RegisterInfo PanelHueRange={	0,0x3f,0x20};
CODE struct RegisterInfo PanelSaturationRange={	45,210,128};
CODE struct RegisterInfo PanelBacklightRange={	0,31,16};

#if (defined  AWT_ML072Q)
//CODE struct RegisterInfo VideoContrastRange={	35,135,85/*0,255,128*/};		//william-v1.1-20120518
CODE struct RegisterInfo VideoContrastRange={	(35-5-5),(135-5-5),90/*0,255,128*/};		//william-v1.1-20120518
#elif (defined AWT_ML072S)
CODE struct RegisterInfo VideoContrastRange={	(28+5+2+2),(79-1),66+4/*0,255,128*/};		//william-v1.1-20120518
#else
CODE struct RegisterInfo VideoContrastRange={	16,116,66/*0,255,128*/};		//william-v1.1-20120518
#endif

#ifdef TW8816 //ryan@20170928

//CODE struct RegisterInfo TW2835VideoContrastRange={	35,135,118/*0,255,128*/};		//william-v1.1-20120518
CODE struct RegisterInfo TW2835VideoContrastRange={	(35-5),(135-5),105/*0,255,128*/};		//william-v1.1-20120518

#else
CODE struct RegisterInfo TW2835VideoContrastRange={	35,135,85/*0,255,128*/};		//william-v1.1-20120518
#endif

#ifdef TW8816 //ryan@20170928
//CODE struct RegisterInfo VideoBrightnessRange={	-82,69,75};
//CODE struct RegisterInfo VideoBrightnessRange={-115,34,30};
	#ifdef AWT_ML072S
//	CODE struct RegisterInfo VideoBrightnessRange={159,92,45-12};
//	CODE struct RegisterInfo VideoBrightnessRange={159,92,45};
	CODE struct RegisterInfo VideoBrightnessRange={-96+13,92-13,25-6};
	#else
	CODE struct RegisterInfo VideoBrightnessRange={-125,(34-5-5),30};
	#endif

#else
CODE struct RegisterInfo VideoBrightnessRange={-74,34,-24};
#endif

CODE struct RegisterInfo VideoSaturationRange={	0,255,128};
CODE struct RegisterInfo VideoHueRange={	-128,127,0};	//-90~90
CODE struct RegisterInfo VideoSharpnessRange={	0,7,3};
CODE struct RegisterInfo DigitalVideoSaturationRange={0, 0x7f, 0x40};

#define contrast   		0
#define bright 			1
#define staturation_U 	2
#define staturation_V 	3
#define hue    			4
#define sharpness 		5
#define backlight 		6

CODE BYTE Contast_Reg_Addr[]={0x11, // Composite
							  0x11, // Svideo
				     0x11,//AV 		  
	                          //0x3b, // Component
	                          #ifdef HS
  				     0x11,//CAMB 		  
				#else
	                          0x71, // DTV
	                          #endif
	                          0x11, // TV
	                          0x3b  // Scart
	};
#ifdef WIDE_SCREEN
extern BYTE WideScreenMode;
#define MAXWIDESCREEN 4
#endif
#ifdef SUPPORT_COMPONENT
extern  BYTE  ComponentMode;
#endif
extern	 BYTE  InputSelection;
extern BYTE TriggerMode;  //Pinchi 20141028 add
extern BYTE TriggerFlag;  //Pinchi 20141028 add

//==============================================================
//
//  OSD Menu Operation Function
//
//==============================================================
#define MAX_OSDPOSITIONMODE	5
CODE BYTE OSDPOSITIONMODE_TABLE[][2] = { 
	{OSDMENUX_50, OSDMENUY_50},
	{OSDMENUX_MIN,OSDMENUY_MIN},
	{OSDMENUX_MIN,OSDMENUY_MAX},
	{OSDMENUX_MAX,OSDMENUY_MAX},
	{OSDMENUX_MAX,OSDMENUY_MIN},
};

#ifdef SUPPORT_OSDPOSITIONMOVE
BYTE GetOSDPositionMode(void)
{
	BYTE val;
	val = GetOSDPositionModeEE();
//	Printf("OSD Position=%d\r\n",(BYTE)val);
	
	return val;
}

BYTE SetOSDPositionMode( BYTE flag )
{
	int val, addx, addy;
	BYTE i,inc, winno;
	BYTE OSDStart[5][3];
	WORD tmp;

	#ifdef ADD_ANALOGPANEL
		if(IsAnalogOn()) return 0;
	#endif


	// Get OSD Position Mode
	i = GetOSDPositionMode();
	inc = ( flag==UP  ? 1  :  -1  );
	i = i + MAX_OSDPOSITIONMODE + inc;
	i %= MAX_OSDPOSITIONMODE;

	addx = OSDPOSITIONMODE_TABLE[i][0];
	addx -= OSDMenuX;
	OSDMenuX = OSDPOSITIONMODE_TABLE[i][0];

	addy = OSDPOSITIONMODE_TABLE[i][1];
	addy -= OSDMenuY;
	OSDMenuY = OSDPOSITIONMODE_TABLE[i][1];

	for( winno=OSDCURSORWINDOW; winno<=OSDMENU_TITLEWIN; winno++) {
		val = GetOSDWindowX( winno );
		val += addx;
		tmp = (BYTE)val<<3;
		OSDStart[winno-OSDCURSORWINDOW][1] = tmp;
		OSDStart[winno-OSDCURSORWINDOW][0] = tmp>>8;

		val = GetOSDWindowY( winno );
		val += addy;
		tmp = (BYTE)val<<2;
		OSDStart[winno-OSDCURSORWINDOW][2] = tmp;
		OSDStart[winno-OSDCURSORWINDOW][0] = OSDStart[winno-OSDCURSORWINDOW][0] | (tmp>>4 & 0x70);
	}

	WaitEndofDisplayArea();	
	//WriteTW88(0x90, 0x80); //Close OSD by external
/*	for (winno=OSDCURSORWINDOW; winno<=OSDMENU_TITLEWIN ;winno++ )
	{
		SetOSDWindowNum(j);
		WriteTW88(TW88_WINATTR, 0x00);
	}


	delay(1);
*/
	// Move OSD Position of each windows
//	WriteTW88(0xff, ReadTW88(0xff) & 0xef);
	WriteTW88(0xe0, ReadTW88(0xe0) & 0xef);
	for( winno=OSDCURSORWINDOW; winno<=OSDMENU_TITLEWIN; winno++) {
		SetOSDWindowNum(winno);				// set winno
		WriteI2Cn(TW88I2CAddress, 0xa0, &OSDStart[winno-OSDCURSORWINDOW], 3);  
	}
//	WriteTW88(0xff, ReadTW88(0xff) | 0x10);
	WriteTW88(0xe0, ReadTW88(0xe0) | 0x10);
	SaveOSDPositionModeEE(i);

	WaitEndofDisplayArea();	
	WriteTW88(0x90, 0); // Open OSD


	return i;
}

/*
BYTE GetOSDMenuXValue(void)
{
	int ival;

	Mapping1(OSDMenuX, &OSDMenuXRange, &ival, &UserRange);
	OSDItemValue = ival;
	return (BYTE)ival;
}

BYTE GetOSDMenuYValue(void)
{
	int ival;

	Mapping1(OSDMenuY, &OSDMenuYRange, &ival, &UserRange);
	OSDItemValue = ival;
	return (BYTE)ival;
}


BYTE SetOSDMenuYValue(BYTE flag)
{

	int val, add;
	BYTE winno;

    add = ( flag==UP  ? 1  :  -1  );
	val =  OSDItemValue + add;
	if( val< UserRange.Min || val> UserRange.Max ) {
		return GetOSDMenuYValue();
	}

	Mapping1(val, &UserRange, &add, &OSDMenuYRange);
	SaveOSDYPositionEE(add);
	add -= OSDMenuY;
	OSDMenuY += add;
	SaveOSDYPositionEE(OSDMenuY);
	OSDItemValue = val;

	for( winno=OSDCURSORWINDOW; winno<=OSDMENU_TITLEWIN; winno++) {
		val = GetOSDWindowY( winno );
		SetOSDWindowY(winno,val+add);
	}
	return OSDItemValue;
}

BYTE SetOSDMenuXValue(BYTE flag)
{
	int val, add;
	BYTE winno;

	add = ( flag==UP  ? 1  :  -1  );
	val = OSDItemValue + add;
	if( val< UserRange.Min || val> UserRange.Max ) {
		return OSDItemValue;
	}

	Mapping1(val, &UserRange, &add, &OSDMenuXRange);
	add -= OSDMenuX;
	OSDMenuX += add;
	SaveOSDXPositionEE(OSDMenuX);
	OSDItemValue = val;

	for( winno=OSDCURSORWINDOW; winno<=OSDMENU_TITLEWIN; winno++) {
		val = GetOSDWindowX( winno );
		SetOSDWindowX(winno,val+add);
	}
	return OSDItemValue;

}
*/
#endif
/*
BYTE SetOSDDuration(BYTE newd)
{
	OSDDuration = newd;
	return OSDDuration;
}
*/

void ResetOSDValue(void)
{
	OSDMenuX = OSDPOSITIONMODE_TABLE[0][0];  // Default
	OSDMenuY = OSDPOSITIONMODE_TABLE[0][1];
	#ifdef SUPPORT_OSDPOSITIONMOVE
	SaveOSDPositionModeEE(0);
	#endif
       
	   WriteEEP(EEP_SelectMode,CAM_A);       
	#ifdef SUPPORT_ML072Q_AUTO_DAY_NIGHT  //Pinchi 20150825 add  //AWT_ML072Q  //Pinchi 20140903 add for AWT ML072Q
	   WriteEEP(EEP_AutoMode , 0x01);	  // Auto Day&Night...... OFF
	#else
	   WriteEEP(EEP_AutoMode,0x00);	  // AutoMode...... ON
	#endif
	   DayNightLevel=ReadEEP(EEP_AutoMode);
	   WriteEEP(EEP_IMAGEMode,0x00);	 // IMAGEMode..... SINGLE
	   WriteEEP(EEP_RearMode,0x00); 	 // RearMode...... R  
	   WriteEEP(EEP_TriggerVGA,0x00); 	 // trigger vga...... on  
	 #ifdef HS
	 WriteEEP(EEP_GAUGEMode,0x01);	   // ­Ë¨®OSD....... OFF   
	 #else 
	   WriteEEP(EEP_GAUGEMode,0x00);	 // ­Ë¨®OSD....... ON	
	  #endif 
	   WriteEEP(EEP_Powerflag,0x01);	 // POWER FLAG....... ON  
	   WriteEEP(EEP_COSDMode,0x00); 	 // Display OSD... ON 
	   WriteEEP(EEP_DVRDisplay,0x00); 	 //DVR Display OSD... ON
	   WriteEEP(EEP_CAMAMode,0x01); 	 // MirrorA....... OFF
	   WriteEEP(EEP_CAMBMode,0x01); 	 // MirrorB....... OFF
	   WriteEEP(EEP_CAMCMode,0x01); 	 // MirrorC....... OFF
	   WriteEEP(EEP_CAMRMode,0x00); 	 // MirrorR....... ON
	   WriteEEP(EEP_AUDIOPVOL,50);       // AudioVol
	   AudioVol=50;
	   ChangeVol(0);
	   WriteEEP(EEP_PCAUDIOPVOL,50);
	   WriteEEP(EEP_AudioRecord,0x03); 	 // dvr audio channel
	
	   WriteEEP(EEP_IMAGE_A_Mode,0x00);
	   WriteEEP(EEP_IMAGE_B_Mode,0x00);
       WriteEEP(EEP_IMAGE_C_Mode,0x00);

//#ifndef	AWT_ML072Q  //Pinchi 20140918 add for AWT ML072Q
#ifdef  SUPPORT_ML84TQ_TRIGGER_DELAY  //Pinchi 20150825 add for function define
	   WriteEEP(EEP_DELAYCAMA,0x00); 	 // DELAY CAM A....... 0
	   WriteEEP(EEP_DELAYCAMB,0x00); 	 // DELAY CAM B....... 0
	   WriteEEP(EEP_DELAYCAMC,0x00); 	 // DELAY CAM C....... 0.
	   WriteEEP(EEP_DELAYCAMR,0x00); 	 // DELAY CAM R....... 0
	 #ifdef USE_CAMD  
	   WriteEEP(EEP_DELAYCAMD,0x00); 	 // DELAY CAM D....... 0
	 #endif
#endif

		#ifdef AWT_ML072S
WriteEEP(EEP_ONOFFChoice,0x01); ///  OSD	lock....... off
OSD_LOCKF=1;
#else
	   if(Priority==0)
	   {
		WriteEEP(EEP_JUMPMode,0);	  // JUMPMode...... QUAL
		WriteEEP(EEP_ONOFFChoice,0x01); 	// OSD	lock....... off
		OSD_LOCKF=1;
	   }
		else
	   {
		WriteEEP(EEP_JUMPMode,13);		// JUMPMode...... QUAL
		WriteEEP(EEP_ONOFFChoice,0x00); 	// OSD	lock....... ON
		OSD_LOCKF=0;
	   }
		#endif
		
	   SEQFlag=0;
#ifdef AWT_ML072S
	   WriteEEP(EEP_TimeStep,0x03); 	 // TimerStep.....02
#else
	   WriteEEP(EEP_TimeStep,0x02); 	 // TimerStep.....02
#endif	   
	   WriteEEP(EEP_CAMOutMode,0x00);	 // CAMOut........ QUAL 
	   CAMOutDSel( 0x00 );	///V1.1 02/27/07 simonsung 
	   TW2835Cmd("\n\rmode 0\n\r");
	   ClearDataCnt(INPUTINFO_ADDR, 51);   //william-980416

	   WriteEEP(EEP_AudioRecord,0); 
	   WriteEEP(EEP_FirstNumber,1); 
	   WriteEEP(EEP_SecondNumber,1); 
	   WriteEEP(EEP_ThridNumber,1); 
	   WriteEEP(EEP_FourthNumber,1); 
	   LoadEEPROM();
       SaveOSDLangEE(0);	// Save default Language1  
    
       WriteEEP(EEP_SDCardDetect,0x01); 	//SDCardDetect.....off
       SDCardCoverDetect= ReadEEP(EEP_SDCardDetect);
	#ifdef SUPPORT_SDCARD  //Pinchi 20140903 add for AWT ML072Q
       Hs_DvrTxCmdPaser(DoorClose);
	#endif
	
       WriteEEP(EEP_PELCO,0x00);
       PelcoChoiceFLAG = ReadEEP(EEP_PELCO);
       WriteEEP(EEP_CAMNUMBER,0x01);
       CAMNumber = ReadEEP(EEP_CAMNUMBER);
       WriteEEP(EEP_Baud_rate,0x02);
       Baud_rate = ReadEEP(EEP_Baud_rate);
	   WriteEEP(EEP_NowModeState,SelectMode);
	   NowModeState=SelectMode;

	   ReverseModeFlag=1;
	   WriteEEP(EEP_ReverseMode,ReverseModeFlag); //andy Holtz 981123

#ifdef AWT_ADD_TRIGGER_DELAY_FUN  //Pinchi 20150209 add
    WriteEEP(EEP_CamADelay , 0x00);
    WriteEEP(EEP_CamBDelay , 0x00);
    WriteEEP(EEP_CamCDelay , 0x00);
    WriteEEP(EEP_CamRDelay , 0x00);
#endif

#ifdef AWT_ML072S		//william @20130902 
	JUMPAVFlag=1;//andy h10a 980602 
	WriteEEP(EEP_JUMPAV_TIMESET,0x01);//JUMPAV........OFF
#endif
	
#ifdef HS_NEWOSDMENU	  
	InitOSDMenu(0);
#else
	InitOSDMenu();
#endif
#ifndef QUAD
	CheckMirror();
#endif
}

#ifdef E_Wintek
void ResetUESROSDValue(void)
{

          WriteEEP(EEP_SelectMode,CAM_A);
	   WriteEEP(EEP_AutoMode,0x01);	  // AutoMode...... ON	 
	   WriteEEP(EEP_IMAGEMode,0x00);	 // IMAGEMode..... SINGLE
	   WriteEEP(EEP_RearMode,0x00); 	 // RearMode...... R  
	   //WriteEEP(EEP_TriggerVGA,0x00); 	 // trigger vga...... on  
	   //WriteEEP(EEP_GAUGEMode,0x00);	 // ­Ë¨®OSD....... ON	
	   WriteEEP(EEP_Powerflag,0x01);	 // POWER FLAG....... ON  
	   //WriteEEP(EEP_COSDMode,0x00); 	 // Display OSD... ON 
	   //WriteEEP(EEP_DVRDisplay,0x00); 	 //DVR Display OSD... ON 	   
	   //WriteEEP(EEP_CAMAMode,0x01); 	 // MirrorA....... OFF
	   //WriteEEP(EEP_CAMBMode,0x01); 	 // MirrorB....... OFF
	   //WriteEEP(EEP_CAMCMode,0x01); 	 // MirrorC....... OFF
	   //WriteEEP(EEP_CAMRMode,0x00); 	 // MirrorR....... ON
	   WriteEEP(EEP_AUDIOPVOL,50); 	// MirrorR....... ON
	   WriteEEP(EEP_PCAUDIOPVOL,50); 	// MirrorR....... ON
	   //WriteEEP(EEP_AudioRecord,0x03); 	 // dvr audio channel
	   WriteEEP(EEP_JUMPMode,0);	  // JUMPMode...... QUAL
	   WriteEEP(EEP_ONOFFChoice,0x01); 	// OSD	lock....... off 	
	OSD_LOCKF=1;
	   ClearDataCnt(INPUTINFO_ADDR, 51);   //william-980416

	  LoadEEPROM();
	  SaveOSDLangEE(0);	// Save default Language1
	  InitOSDMenu();	
}
#endif
#define HOUR			1
#define MIN				2
#define MAX_LANG	5	// Max Language : 2
BYTE GetOSDLang(void)
{
	OSDLang = GetOSDLangEE();
	OSDLang %= MAX_LANG;
	return OSDLang;
}

BYTE SetLanguage (BYTE flag)
{
	char inc;
	inc = ( flag==UP  ? 1  :  -1  );
	OSDLang = OSDLang + MAX_LANG + inc;
	OSDLang %= MAX_LANG ; 

	SaveOSDLangEE(OSDLang);

	return OSDLang;
}

#if 0
#define INC_SLEEPTIMER		30
#define	MAX_SLEEPTIMER		150

BYTE ChangeSleepTimer( BYTE flag )
{
	int t;

	t = OSDItemValue / INC_SLEEPTIMER * INC_SLEEPTIMER;		//cut edge of remained sleep timer.

	if( flag==UP )	t+= INC_SLEEPTIMER;
	else			t-= INC_SLEEPTIMER;

	if( t<0 )		t = 0;
	if( t> MAX_SLEEPTIMER)	t = MAX_SLEEPTIMER;

	OSDItemValue = t;
	return OSDItemValue;
}
#endif

//======================================================================
/*BYTE GetOSDDurationValue(void)
{
	OSDItemValue = GetOSDDurationEE();
	return OSDItemValue;

}

BYTE GetOSDDuration(void)
{
	return OSDDuration;
}
*/
void SetRGBContrast( BYTE temp, BYTE val )
{
	WORD index;
	BYTE i;
	int newval, toValue;

	index = PC_COLOR_DATA + 1 + temp*3;
	for( i=0; i<3; i++)
	{
		 newval = ReadEEP( index+i );
		 Mapping1( newval, &UserRange , &toValue, &PCUserColorTempRange);
	 	 SetPanelContrastReg(i,   toValue + val );
	}
}

#define MAX_COLORTEMP	4

CODE BYTE PCColorTempRGB[][3]={
	75,		50,		50,				// Mode 1: Warm
	50,		50,		50,				// Mode 2: plain -- COLOR_MODE2
	50,		50,		75,				// Mode 3: Cold
	50,		50,		50				// User mode
};

#define COLOR_MODE2		1
#define COLOR_USER		3

BYTE SetPCColorTemp(BYTE flag)
{
	BYTE val;
	int  regv;
	char inc;

	//OSDItemValue = GetPCColorTempModeEE();

	inc = ( flag==UP  ? 1  :  -1  );
	OSDItemValue = OSDItemValue + MAX_COLORTEMP + inc;
	OSDItemValue %= MAX_COLORTEMP ; 

	SetPCColorTempModeEE ( OSDItemValue );
	val = GetPanelContrastEE();
	Mapping1( val, &UserRange ,&regv, &PanelContrastRange);
	SetRGBContrast( OSDItemValue, (BYTE)regv );

	if( GetPCColorTempModeEE() != 3 )  // User
			DrawAttrCnt(OSDMENU_SUBADDR+MENU_WIDTH*2, BACK_COLOR, (MENU_HEIGHT-1)*MENU_WIDTH );	
	else
			DrawAttrCnt(OSDMENU_SUBADDR+MENU_WIDTH*2, DEFAULT_COLOR, (MENU_HEIGHT-1)*MENU_WIDTH );	

	return OSDItemValue;
}

#ifdef SUPPORT_PC
BYTE GetPCColorTemp(BYTE color) 
{
	OSDItemValue = GetPCUserColorTempEE(color);
	return OSDItemValue;
}
#endif

BYTE SetPCColor(BYTE color, BYTE flag) 
{
	int newval, toValue, regv;

//	GetPCColorTemp(color);
	newval = ( flag==UP  ? OSDItemValue+1  :  OSDItemValue-1  );
	if( newval< UserRange.Min || newval> UserRange.Max )
		return OSDItemValue;

	OSDItemValue = newval;
	Mapping1( newval, &UserRange , &toValue, &PCUserColorTempRange);
	SavePCUserColorTempEE(color, newval);

	newval = GetPanelContrastEE() ;
	Mapping1( newval, &UserRange ,&regv, &PanelContrastRange);

	SetPanelContrastReg(color,(BYTE)(toValue + regv) );

	return  OSDItemValue;
}

#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )

void ResetPanelAttributeValue(void)
{
	BYTE i, j;

	SetPCColorTempModeEE( COLOR_USER );	//default
	for( j=0; j< 4; j++)
		for( i=0; i< 3; i++)
			WriteEEP ( PC_COLOR_DATA + 1 + j*3 + i, PCColorTempRGB[j][i] );

	SavePanelContrastEE( UserRange.Default );
	SavePanelBrightnessEE( UserRange.Default );

	GetInitPanelAttribute1();		// Panel Brightness / Contrast
}

BYTE SetPanelContrast(BYTE flag) 
{

	int newval, regv;

	newval = ( flag==UP  ? OSDItemValue+1  :  OSDItemValue-1  );
	if( newval< UserRange.Min || newval> UserRange.Max )
		return OSDItemValue;

	Mapping1( newval, &UserRange , &regv, &PanelContrastRange);
	SetRGBContrast( GetPCColorTempModeEE(), regv );
	SavePanelContrastEE(newval);

	OSDItemValue = newval;
	return newval;
}

BYTE SetPanelBrightness(BYTE flag) 
{

	int newv, regv;

	newv = ( flag==UP  ? OSDItemValue+1  :  OSDItemValue-1  );
	if( newv< UserRange.Min || newv> UserRange.Max )
		return OSDItemValue;

	Mapping1( newv, &UserRange , &regv, &PanelBrightnessRange);
	SetPanelBrightnessReg(RED,  (BYTE)regv);
	SetPanelBrightnessReg(GREEN,(BYTE)regv);
	SetPanelBrightnessReg(BLUE, (BYTE)regv);
	SavePanelBrightnessEE(newv);
	OSDItemValue = newv;
	return newv;
}
#endif

//william-981111 		changesource load panelimage
void CheckPanelImage(void)
{
    #ifdef SUPPORT_PC	
	int newv, regv,newval;
		
	if(InputSelection==PC)
	{
	//LOAD	PanelBrightness
		newv=GetPanelBrightnessEE();	
		Mapping1( newv, &UserRange , &regv, &PanelBrightnessRange);
		WriteTW88(0x70,ReadTW88(0x70)&0xbf);
		SetPanelBrightnessReg(RED,	(BYTE)regv);
		SetPanelBrightnessReg(GREEN,(BYTE)regv);
		SetPanelBrightnessReg(BLUE, (BYTE)regv);

	//LOAD	PanelContrast
		newval=GetPanelContrastEE();
		Mapping1( newval, &UserRange , &regv, &PanelContrastRange);
		SetRGBContrast( GetPCColorTempModeEE(), regv );
	}
	else
    #endif		
	{
		WriteTW88(0x70,ReadTW88(0x70)&0xbf);
		SetPanelBrightnessReg(RED,	0x80);
		SetPanelBrightnessReg(GREEN,0x80);
		SetPanelBrightnessReg(BLUE, 0x80);
		SetPanelContrastReg(0,0x80);
		SetPanelContrastReg(1,0x80);
		SetPanelContrastReg(2,0x80);
		WriteTW88(0x70,ReadTW88(0x70)|0x40);
	}
}

CODE BYTE VideoModeTable[][16] ={
	{	0x11,   0x10,	0x13,   0x14, 0x15,  0x70, 0x71, 0x74, 0x72, 0x73, 0x70, 0x71, 0x74, 0x72, 0x73, 0x78,	},// TW8804's Video Picture control Reg Address
//    contrast+bright-+-sat_u-+-sat_v+-hue-+-----+-----+------+----+-----+-----+------------ 
	{	0x63,   0x00,	0x80,	0x80, 0x00, 0x60, 0x80,  0x80, 0x80, 0x80, 0x20, 0x80,  0x80, 0x80, 0x80, 0x3b,  },	// Mode 1: 
	{	0x68,	0xf8,	0x90,	0x90, 0x00, 0x60, 0x80,  0x80, 0x80, 0x80, 0x20, 0x80,  0x80, 0x80, 0x80, 0x03,  },	// Mode 2: 
	{	0x58,	0xf8,	0xa0,	0xa0, 0x00, 0x60, 0x80,  0x80, 0x80, 0x80, 0x20, 0x80,  0x80, 0x80, 0x80, 0x03,  },	// Mode 3: 
//	{	0x60,	0x00,	0x80,	0x80, 0x00, 0x80, 0x80,  0x80, 0x80, 0x80, 0x60, 0x80,  0x80, 0x80, 0x80, 0x03,  },	// User Mode 
};

#define USER_VIDEOMODE	3
void SetVideoMode(BYTE mode)
{
	int  i,regv;

	SetVideoModeEE ( mode );
	
	if( mode != USER_VIDEOMODE ){

		for (i=0 ;i<15 ; i++)
			WriteTW88( VideoModeTable[0][i],  VideoModeTable[mode+1][i] );

		regv = VideoModeTable[mode+1][15];	// Sharpness
		SetPanelSharpnessReg( (BYTE)regv );
		SetVideoVPeakingReg( (BYTE)regv );
//		SetVideoHfilterReg( (BYTE)regv );
	}
	else // USERMODE
	{
		#ifndef SUPPORT_USERCOLORFROMTXT
		{
		int  userv;

		// Load from EEPROM
		SetVideoContrast( GetVideoDatawithOffset(contrast) );
	    SetVideoBrightness( GetVideoDatawithOffset(bright) );
		SetVideoSaturation(U_SAT, GetVideoDatawithOffset(staturation_U) );
		SetVideoSaturation(V_SAT, GetVideoDatawithOffset(staturation_V) );
	    SetVideoHue(GetVideoDatawithOffset( hue) );

		userv = GetVideoDatawithOffset(sharpness);
		Mapping1( userv, &UserRange, &regv, &VideoSharpnessRange );
		}
		SetPanelSharpnessReg( (BYTE)regv );
		SetVideoVPeakingReg( (BYTE)regv );
//		SetVideoHfilterReg( (BYTE)regv );

		#endif

	}

}

BYTE IsInputAnalogRGB()
{
	#if defined SUPPORT_COMPONENT
	if( InputSelection==COMPONENT ) return TRUE;
	#elif defined SUPPORT_SCART
	if( InputSelection==SCART ) return TRUE;
	#endif

	return FALSE;
}

BYTE GetVideoDatawithOffset(BYTE offset)
{
	OSDItemValue = GetVideoDatafromEE(offset);
	
	return OSDItemValue;
}

BYTE ChangeVideoData(BYTE offset, BYTE flag)
{
	int newv, inc;

	inc = ( flag==UP  ? 1  :  -1  );

	newv = OSDItemValue + inc;
	if( newv< UserRange.Min || newv> UserRange.Max ) {
		return OSDItemValue;
	}

	switch (offset)
	{
	case contrast: SetVideoContrast(newv);
		 break;
	case bright:  SetVideoBrightness(newv);
		 break;
	case staturation_U: 
	case staturation_V: 
					SetVideoSaturation(offset-staturation_U,newv);
		 break;
	case hue:	  SetVideoHue(newv);
		 break;
	case backlight:	  SetVideoBacklight(newv);
		 break;
	}

	SaveVideoDatatoEE(offset, newv);

	OSDItemValue = newv;
	return newv;
	
}

void SetVideoContrast(BYTE newv)
{
	int regv;

#ifdef QUAD	// william-20130225
if(GetInputSelection()==CH_TW2835)
	Mapping1( newv, &UserRange , &regv, &TW2835VideoContrastRange);
else
#endif	
	Mapping1( newv, &UserRange , &regv, &VideoContrastRange);


	WriteTW88( Contast_Reg_Addr[InputSelection-1], (BYTE)regv );
	//Printf("\r\nInputSelection=%d", (WORD)InputSelection);
}

void SetVideoBrightness(BYTE newv) 
{

	int regv;

#ifdef QUAD	// william-20130225
	if( InputSelection == DTV ){
		Mapping1( newv, &UserRange , &regv, &PanelBrightnessRange);
		SetDTVBrightnessReg( (BYTE)regv);
	}
	else 
#endif		
		{
		Mapping1( newv, &UserRange , &regv, &VideoBrightnessRange);

		if( IsInputAnalogRGB() ) 
			SetDigitalVideoBrightnessReg( regv );
		else 
			SetVideoBrightnessReg( (BYTE)regv);
	}
}
void SetVideoBacklight(BYTE newv) 
{

	int 	regv;
	BYTE	page;

	Mapping1( newv, &UserRange , &regv, &PanelBacklightRange);
#ifdef	BACKLIGHT_CCFL
	page = ReadTW88( 0xff );
	WriteTW88( 0xff, 0x01 );		// set page 1
	regv = ~regv;
	regv &= 0x01f;
	regv >>= 1;
	WriteTW88(0x35, (ReadTW88(0x35 & 0xe0)) + regv);	// only 5 bit using
	WriteTW88( 0xff, page );
#endif
#ifdef BACKLIGHT_PWM				// 
	page = ReadTW88( 0xff );
	WriteTW88( 0xff, 0x00 );		// set page 0
	WriteTW88( 0xbe, ((ReadTW88(0xbe) & 0xcf) | 0x10) );	// set active Low control, if want active high clear 
	WriteTW88( 0xc4, ((ReadTW88(0xc4) & 0x80)|(regv>>1)) );	// set pwm number
	WriteTW88( 0xff, page );
#endif
}

void SetVideoHue(BYTE newv) 
{

	int regv;

	if( InputSelection == DTV ){
		Mapping1( newv, &UserRange , &regv, &PanelHueRange);
		SetPanelHueReg( (BYTE)regv);
	}
	else {
		Mapping1( newv, &UserRange , &regv, &VideoHueRange);
		if( IsInputAnalogRGB() ) 
			SetDigitalVideoHueReg( regv );
		else 
			SetVideoHueReg( (BYTE)regv);
	}

}

void SetVideoSaturation(BYTE svtype, BYTE newv) 
{

	int regv;

	if( IsInputAnalogRGB() ) {
		Mapping1( newv, &UserRange , &regv, &DigitalVideoSaturationRange);
		SetDigitalVideoSaturationReg(svtype, (BYTE)regv);
	}
	else {

		Mapping1( newv, &UserRange , &regv, &VideoSaturationRange);

		if( InputSelection == DTV ){
			SetPanelSaturationReg( svtype, regv );
		}
		else {
			SetVideoSaturationReg( svtype, (BYTE)regv);
		}
	}
}


BYTE SetVideoSharpness(BYTE flag) 
{
	BYTE orgv;
	char inc;
	int newv, regv;

	orgv = ReadTW88( PNLSHARPNESS )&0x07;
	regv = orgv & 0x0f;
	inc = ( flag==UP  ? 1  :  -1  );
	regv += inc;
	if( regv < VideoSharpnessRange.Min ||
		regv > VideoSharpnessRange.Max )
		return OSDItemValue;

	Mapping1( (BYTE)regv, &VideoSharpnessRange, &newv, &UserRange );

	SetPanelSharpnessReg( (BYTE)regv );			//william v1.3.1.1  20120514
	//SetVideoSharpnessReg((BYTE)regv);			//william v1.3.1.1  20120514
	SetVideoVPeakingReg( (BYTE)regv );
//	SetVideoHfilterReg( (BYTE)regv );

	SaveVideoDatatoEE( sharpness, newv );
	OSDItemValue = newv;

	return newv;
}

/*
BYTE SetOSDDurationValue(BYTE flag)
{
	int val;

	val = ( flag==UP  ? OSDItemValue+1  :  OSDItemValue-1  );
	if( val< OSDDurationRange.Min || val > OSDDurationRange.Max )
		return OSDItemValue;

	OSDItemValue = val;
	SaveOSDDurationEE(val);
	SetOSDDuration( val );
	return OSDItemValue;

}
*/

#ifdef WQVGA
CODE BYTE Init_Video_Data[]={
	50, 50/*26, 41*/,50, 50, 50, 16 }; // Contrast,Bright,Staturation_U,Staturation_V,Hue,Sharpness
#else
  #ifdef AWT_ML072Q
  	 CODE BYTE Init_Video_Data[]={
  	 //Pinchi 20140903 change Video default value for AWT ML072Q
  	       50,37,40, 40, 45, 100 };// Contrast,Bright,Staturation_U,Staturation_V,Hue,Sharpness
  #elif (defined HTRV)  //Pinchi 20150825 add
     CODE BYTE Init_Video_Data[]={
           50,50,50, 50, 50, 50 };// Contrast,Bright,Staturation_U,Staturation_V,Hue,Sharpness
  #else  //ML072S
  #ifdef HS
  CODE BYTE Init_Video_Data[]={
		50, 70, 50, 50,/*62, 62,*/ 50, 50 }; // Contrast,Bright,Staturation_U,Staturation_V,Hue,Sharpness
  #else
  	 CODE BYTE Init_Video_Data[]={
           45/*38*/, 65, 50, 50,/*62, 62,*/ 50, 100 }; // Contrast,Bright,Staturation_U,Staturation_V,Hue,Sharpness
           #endif
  #endif
#endif

#ifdef ADD_ANALOGPANEL
CODE BYTE Init_Video_Data_A[]={
	37, 52, 50, 50, 50, 50 }; // Contrast,Bright,Staturation_U,Staturation_V,Hue,Sharpness
#endif

CODE BYTE Init_DTV_Data[]={
	50, 50, 50, 50, 50, 50 }; // Contrast,Bright,Staturation_U,Staturation_V,Hue,Sharpness

void ResetVideoValue(void)
{
	
	BYTE i, CurInput;
	#ifdef DEBUG
	dPrintf("\r\n---- ResetVideoValue -----");
	#endif
	CurInput = InputSelection;
	for (InputSelection=CH_TW2835; InputSelection<PC ; InputSelection++ ) {

		if( InputSelection == DTV )
		{
			for( i=0; i<6; i++){
				SaveVideoDatatoEE(i, Init_DTV_Data[i]);	// All 50%
			}
		}
		else {
			for( i=0; i<6; i++){
				#ifdef ADD_ANALOGPANEL
				if(IsAnalogOn())
				SaveVideoDatatoEE(i, Init_Video_Data_A[i]);
				else
				#endif
				SaveVideoDatatoEE(i, Init_Video_Data[i]);
			}
		}
	}
	InputSelection = CurInput;
	SetVideoMode(USER_VIDEOMODE);

}

#ifdef WIDE_SCREEN

#include "\data\WideModeData.txt"
/*
void SetHDelay( WORD delay)
{
	BYTE high;
	#ifdef WIDE_SCREEN
	Printf("\n SetHDelay: %4x ", delay);
	#endif
	WriteDecoder( HDELAY_LO, (BYTE)delay );
	high =	ReadDecoder( CROP_HI ) & 0xf3;
	high |= (BYTE)( delay >> 6 );
	WriteDecoder( CROP_HI, high );
}

void SetVideoOverScan(BYTE overscan)	//in 1/20
{
	if(GetInputSelection() == PC)   return;

	VideoOverScan = overscan;
	SetHDelay( DEF_HDELAY + 720 * overscan / 20 / 2 );	// Video H Active : 720 pixels
}

*/
#if (defined SUPPORT_PC) || (defined SUPPORT_DTV)
void SetScale4_3Y(void) // 16:9 --> 4:3  // Normal
{
	extern  CODE struct _PCMDATA  PCMDATA[];
	extern	BYTE PcMode;
	DWORD outv, scale;

	// Vertical
	scale = (DWORD)PCMDATA[PcMode].VAN	;
	outv  = (DWORD)PVR_; 
	scale = 0x10000L * scale / outv;

	YScale2( scale );

	// Horizontal
	if (PcMode >= EE_XGA_60 && PcMode >= EE_XGA_75)
		scale = (DWORD)PCMDATA[PcMode].HAN-4; //just 1024	for focus issue(1:1).
	else
		scale = (DWORD)PCMDATA[PcMode].HAN;	

	scale = scale * 0x10000L * 3 / PVR_ /4;

	XScale2( scale );
}

void SetScale(void)
{
	DWORD scale, outv;

	// Vertical
	scale = (DWORD)PCMDATA[PcMode].VAN;
	outv  = (DWORD)PVR_ ; 
	#ifdef REFERENCE
	scale = 0x10000L * scale / outv;
	#else
	if (PcMode >= EE_VGA_60 &&  PcMode <= EE_VGA_85)
	{
		scale = 0x10000L * scale / outv + 0x70;
	}
	else if (PcMode == EE_SVGA_56)
	{
		scale = 0x10000L * scale / outv + 0x96;
	}
	else if (PcMode == EE_SVGA_72)
	{
		scale = 0x10000L * scale / outv + 0x96;
	}
	else
	{
		scale = 0x10000L * scale / outv;
	}
	#endif 
	YScale2( scale );
	#ifdef DEBUG_PC
	Printf("\n PCMode[%d] %ld YScale: %ld", (WORD)PcMode, outv, scale);
	#endif
	// Horizontal
	scale = PCMDATA[PcMode].HAN;
	outv  = PHR_ ; 
//	scale = scale  * 0x100L / outv;
	scale = (scale*0x10000L+outv-1) / outv;
	XScale2( scale );
}

void SetScale4_3X(void)	
{
	DWORD scale, outv;

	// Horizontal
	scale = (DWORD)PCMDATA[PcMode].HAN;
	outv  = (DWORD)PHR_ ; 
	scale = scale  * 0x10000L / outv;
	XScale2( scale );

	// Vertical
#if (defined REFERENCE) && !(defined XGA)
	scale = (DWORD)PCMDATA[PcMode].VAN; 
	outv  = outv * 3 / 4;			// 4:3
	scale = 0x10000L * scale / outv;
#else
	scale = (DWORD)PCMDATA[PcMode].VAN	;
	outv  = (DWORD)PVR_; 
	scale = 0x10000L * scale / outv;
#endif 
	YScale2( scale);				// *********** plus 2
}
void SetLRBlank(BYTE bl)
{
	WriteTW88(0x66, bl);
}
#endif

void Set4WideScreen( BYTE id )
{
//	Printf("\r\n[MSG]Set4WideScreen() => TriggerFlag=%bx , ReadDecoder(0x0a)=%bx , ReadDecoder(0x66)=%bx",TriggerFlag,ReadDecoder(0x0a),ReadDecoder(0x66));  //pinchi test
	if( id > WIDESCREEN_FULL ){
		Set4WideScreen(WIDESCREEN_WIDE);
		id = WIDESCREEN_WIDE;
	}

#ifdef SUPPORT_AC_ON_NORMAL_SCREEN  //Pinchi 20150901 add
  #ifdef AWT_ML072Q   //Pinchi 20141027 add for power on Reverse trigger the screen been 4:3 to 16:9
	if ((TriggerFlag == 0x20) && (ReadEEP(EEP_RearMode) == 0))  //Pinchi 20150801 add the EEP_RearMode condition
  #elif (defined HTRV)
	if (((NowModeState == SelectMode) && (SelectModeType == CAM_RC))
	|| ((NowModeState == JumpMode) && (ReadEEP(EEP_JUMPMode) == 10))
	|| (((TriggerFlag & 0x20) != 0) && ((ReadEEP(EEP_RearMode) == 0) || (ReadEEP(EEP_RearMode) == 5)))
		)
  #endif
  	{

	  #ifdef AWT_ML072S 
		id = WIDESCREEN_WIDE;
		Printf("\r\n[MSG]Set4WideScreen() => WIDESCREEN_WIDE !!");  //ryan@20171204
	  #else
		id = WIDESCREEN_NORMAL;
		Printf("\r\n[MSG]Set4WideScreen() => Screen to 4:3 !!");  //pinchi test
	#endif
		
  	}
#endif

	WideScreenMode = id;

#if (defined SUPPORT_PC) || (defined SUPPOER_DTV) 	
  if(	(GetInputSelection()== PC) || (GetInputSelection()== DTV) )
  {
	switch( id ) {
	case WIDESCREEN_NORMAL:		
								SetScale4_3Y();
								SetLRBlank((PHR_- (PVR_*4/3 ))/2);
								break;
	case WIDESCREEN_WIDE:		
								SetScale();
								SetLRBlank(0);
								break;
								
	case WIDESCREEN_PANO:		
								SetScale();
								SetLRBlank(0);
								break;
								
	case WIDESCREEN_FULL:		
								SetScale4_3X();
								SetLRBlank(0);
								break;
/*	case WIDESCREEN_ZOOM:		
								SetScale4_3X();
								SetLRBlank(0);
								break;
*/	
								}
	}
	else 
#endif
	{
		int i;
		CODE_P BYTE *WideData;
		
		#ifdef SUPPORT_COMPONENT
		if (GetInputSelection()== COMPONENT )
		{
			switch (ComponentMode)
			{
				case YPBPR_576i:	WideData = WIDEDATA_576i[id];	break;
				#ifndef WQVGA
				case YPBPR_480p:	WideData = WIDEDATA_480p[id];	break;
				case YPBPR_576p:	WideData = WIDEDATA_576p[id];	break;
				case YPBPR_720p:	WideData = WIDEDATA_720p[id];	break;
				case YPBPR_1080i:	WideData = WIDEDATA_1080i[id];	break;
				#endif
				default:			WideData = WIDEDATA_480i[id];	break;
			}

		}
		else 
		#endif
		{
				//if( ReadVInputSTD()== NTSC || ReadVInputSTD()== NTSC4 ) 
				if( GetVInputStd() == NTSC || 
					GetVInputStd()== NTSC4 || 
				#ifdef REFERENCE
				#else
					GetVInputStd()== PALM ||
					GetVInputStd()== PAL60 ||
				#endif 
					GetVInputStd() == 0) {

					#ifdef ADD_ANALOGPANEL
					if(IsAnalogOn()) 
					WideData = WIDEDATA_NA[id];
					else
					#endif
					WideData = WIDEDATA_N[id];
				//	Printf("\r\n[MSG]Set4WideScreen() => wide data=WIDEDATA_N[%bx]",id);  //pinchi test
				#ifdef FIRST_RUN_FROM_AC  //Pinchi 20141029 add
					WideScreenMode = WIDESCREEN_WIDE;
				#endif
				}
				else{
					#ifdef ADD_ANALOGPANEL
					if(IsAnalogOn()) 
					WideData = WIDEDATA_PA[id];
					else
					#endif
					WideData = WIDEDATA_P[id];
				//	Printf("\r\n[MSG]Set4WideScreen() => wide data=WIDEDATA_P[%bx]",id);  //pinchi test
				}

			#ifdef SUPPORT_AC_ON_NORMAL_SCREEN  //Pinchi 20150901 add
				WideScreenMode = WIDESCREEN_WIDE;
			#endif
		}

		#if defined(DEBUG)&& defined(SUPPORT_COMPONENT) 
		Printf( "\r\nWrite Wide Mode Type: %d, Data: %d, VInputStd: %d", (WORD)ComponentMode, (WORD)id, (WORD)GetVInputStd());
		#endif
		WaitEndofDisplayArea();

		for(i=0; i<WIDE_DATA_MAX; i++){
			WriteTW88(WIDE_ADDRESS[i], *WideData);
			#ifdef DEBUG
			Printf( "\r\nwideData=%2x",(WORD)*WideData );
			#endif
			WideData++;
		}
	}

	SaveWideModeEE(WideScreenMode);
}
#endif // WIDE_SCREEN


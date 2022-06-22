/*****************************************************************************/
/*                                                                           */
/*                    TW880x Demo Board   Techwell,Inc                       */
/*                                                                           */
/* CPU        : Winbond 78E62BP-40                                           */
/* LANGUAGE   : Tasking C / Keil C                                           */
/* PROGRAMMER : Jooyeon Lee / Harry Han                                      */
/*                                                                           */
/*****************************************************************************/
/* See 'Release.txt' for firmware revision history                           */

#include "Config.h"

#include "reg.h"
#include "typedefs.h"
#include "main.h"
#include "tw88.h"
#include "i2c.h"
#include "adc.h"
#include "osdbasic.h"
#include "dispinfo.h"
#include "debug.h"
#include "etc_eep.h"
#include "measure.h"
#include "Printf.h"
#include "audio.h"
#include "osdmenu.h"
#include "pc_eep.h"
#include "KeyRemo.h"
#include "Monitor.h"
#include "CPU.h"
#include "HS_keyremo.h"
#include "HS_DisplayOSD.h"
#include "rgbmix.h"			
#include "panel.h"
#include "HS_IOdef.h"
#include "HS_DVRProtocol.h"
#include <math.h>

//bit	AccessEnable = 1;
//void Loader(BYTE);

extern	CODE BYTE NTSC_Regs[];
extern	CODE BYTE PAL_Regs[];
extern	CODE BYTE DVI_Regs[];
#ifdef ADD_ANALOGPANEL
extern CODE BYTE NTSC_Regs_Analog[];
extern CODE BYTE PAL_Regs_Analog[];
#endif

#ifdef SUPPORT_COMPONENT
extern CODE BYTE COMP_YPbPr_480I_Reg[];
extern CODE BYTE COMP_YPbPr_576I_Reg[];
 #ifndef WQVGA
extern CODE BYTE COMP_YPbPr_480P_Reg[];
extern CODE BYTE COMP_YPbPr_576P_Reg[];
extern CODE BYTE COMP_YPbPr_1080I_Reg[];
extern CODE BYTE COMP_YPbPr_720P_Reg[];
 #endif
#endif

#ifdef SUPPORT_GAMMA
extern CODE BYTE GammaRed[];
extern CODE BYTE GammaBlue[];
extern CODE BYTE GammaGreen[];
#endif

extern BYTE TR_JUMP_HOLD; //ryan@20170912
extern  BYTE AV_MODE_DELAY;
extern BYTE CAM_QUAD_TO;//ryan@20170928

extern BYTE OSD_LOCKF;

BYTE CAMNumber;
BYTE PelcoChoiceFLAG;
BYTE Baud_rate;

BYTE	SelectModeType;
BYTE	Priority;
BYTE	PowerFlag;
BYTE DVR_AudioRecord;
bit VGAflag=0;
bit		PowerDownStart=0;
bit	AccPowerDown=0;
bit	DVRReSendDisable;
BYTE	Commanderror;
BYTE AutoDayNightDelay=0;
DATA BYTE PWMLevel=0;
BYTE displayhold_flag;
BYTE  ReverseModeFlag;

BYTE InitVideoDataSrc =0;
	
#ifdef AWT_ML072S //william @20130902 v1.0.1.2
bit 	JUMPAVFlag;
#endif

#ifdef AWT_ML720Q_NEW_TRIGGER_FUN  //Pinchi 20141031 add for AWT request each trigger can work by PRIORITY OFF
//===== bTri_arry[4]={Left , Right , Reverse , CAM C} =====//
BYTE bTri_arry[4]={0,0,0,0};
BYTE bTri_backup[4]={0,0,0,0};
BYTE bTriOrder=0 , bTriNumber=0;
bit IsTriggerArrEmpty=1;  //Pinchi 20150210 add
#endif

#if 1  //Pinchi 20160921 add to modify data location
DATA BYTE  CheckBuf;
//DATA BYTE  updn_reg[4]={0,0,0,0};
DATA BYTE  SourceMode=0;
DATA BYTE  ParkTime=0,RightTime=0,LeftTime=0,ReverseTime=0,RtFlag=0,LtFlag=0,ReverseFlag=0/*,ParkFlag=0*/;
#else
BYTE  CheckBuf;
BYTE  CheckInt; 

BYTE  updn_reg[4]={0,0,0,0};

BYTE  SourceMode=0;
BYTE  ParkTime=0,RightTime=0,LeftTime=0,ReverseTime=0,RtFlag=0,LtFlag=0,ReverseFlag=0,ParkFlag=0;
#endif

BYTE  CkPARK=0,CkTMode=0,TGFlag=0,TGFlag1=0,TDisplayFlag=0;

extern BYTE Disp_Input;
extern BYTE Backlight_TO;

extern  DATA  WORD  tic_pc;
extern DATA BYTE	RS2_in;
extern DATA BYTE   	RS_buf2[BUF_MAX];
extern bit DVR_Ready;
extern bit 	GetDVRStatusflag;
extern bit DoorState;
extern bit CAM_PTZ_RUN_flag;
extern bit Init_DisplayInput;
extern BYTE SelectBoxMode;
extern BYTE LockKeyState;
extern BYTE second;
extern BYTE	PowerDownWait;
extern BYTE SelectBoxADC;
extern BYTE Information[14];
extern BYTE DVR_System;
extern BYTE DayNightLevel;
//#ifdef Format_SDCard
extern BYTE FormatSDCard;
//#endif
extern BYTE DVR_SDCardAvailable;
extern WORD CommandBuffer;
extern void CheckPanelImage(void);
//extern CODE BYTE Init_Osd_DisplayDVRstatus[];

#ifdef HTRV  //Pinchi 20150825 add model #define
extern BYTE GaugeVStart;
#endif
extern DWORD dPressSelectTime;  //Pinchi 20141014 add for AWT ML072Q
extern bit IsPressSelectKey;  //Pinchi 20141014 add for AWT ML072Q

		BYTE  InputSelection;
//		IDATA BYTE	InputSelectionInx = 0;
///	    bit	  PcDetectFlag = 1;
//		bit	  PowerMode = ON;
		IDATA WORD  IVF;
		IDATA DWORD	IHF;
		BYTE  VInputStd;

		bit   Range4Coarse=0;
		//bit	  AutoDetect=0;
		BYTE  VInputStdDetectMode;
		//BYTE  CheckBuf;
		BYTE  SEQTime;
		//bit  AutoDayNight=1;
		bit SDCardCoverDetect;

CODE struct struct_IdName	struct_InputSelection[]={
	{ UNKNOWN			,	"" },				//don't remove or change this.
	{ CH_TW2835,	"CVBS" },			//don't remove or change this.
	{ CH_CAMD  ,   "CAM D"},
	{ CH_AV    ,    "AV  "},

												// you can change the order of the followings
	#ifdef SUPPORT_SVIDEO
	{ SVIDEO			,	"S-Video" },
	#endif

	#ifdef SUPPORT_COMPONENT
	{ COMPONENT	,			"Component" },
	#endif

	#ifdef SUPPORT_DTV
	{ DTV	,				"DTV-SOG" },
	#endif

	#ifdef SUPPORT_PC
	{ PC				,	"VGA"},
	#endif

	#ifdef SUPPORT_DVI
	{ DIGITALVGA		,	"DVI" },
	#endif

	{0					,	""},				//don't remove or change this.
};

#ifndef QUAD
CODE struct struct_IdName	struct_InputSelection_S[]={
	{ UNKNOWN			,	"" },				//don't remove or change this.
	{ SOURCE_A,	"CAM A" },			//don't remove or change this.
	{ SOURCE_B  ,   "CAM B"},
	{ SOURCE_R    ,    "CAM R  "},	
	{ SOURCE_AV,    "AV  "},	
};
#endif

CODE struct struct_IdName struct_VInputStd[]={
	{ UNKNOWN			,	"" },				//don't remove or change this.
	{ NTSC,					"NTSC"},			//don't remove or change this.

	#ifdef SUPPORT_PAL
	{ PAL,					"PAL"},
	#endif

	#ifdef SUPPORT_SECAM
	{ SECAM,				"SECAM"},
	#endif

	#ifdef SUPPORT_PALM
	{ PALM,					"PALM"},
	#endif

	#ifdef SUPPORT_PALN
	{ PALN,					"PALN"},
	#endif

	#ifdef SUPPORT_PAL60
	{ PAL60,				"PAL60"},
	#endif

	#ifdef SUPPORT_NTSC4
	{ NTSC4,				"NTSC4.43"},
	#endif

	{0					,	""},				//don't remove or change this.
};


//===================== OSD ===================================================
		WORD OSDLastKeyInTime;		// in ms

//===================== Button Key ============================================

//================= Etc. ======================================================

#ifdef AWT_ADD_TRIGGER_DELAY_FUN  //Pinchi 20150206 add for AWT request each trigger can setup trigger delay
BYTE bLastTrigger=0;  //Left=1 , Right=2 , Reverse=3 , CAM C=4
#endif

#ifdef WIDE_SCREEN
		BYTE WideScreenMode;
#endif
		BYTE DebugLevel;

		bit  Flag4AutoPanelRegs = 0;
		bit  I2CAutoIncFlagOn = 0;
#ifdef SUPPORT_COMPONENT
	    BYTE ComponentMode;
		WORD OLD_hpn;
#endif
//extern  bit	OnChangingValue;
//extern  BYTE	TVInputSel;
#ifdef SUPPORT_DEBUG
extern  bit  Debug_On;
#endif

#ifdef NO_INITIALIZE
		bit	 NoInitAccess=0;
#endif

//#ifdef FIRST_RUN_FROM_AC  //Pinchi 20141029 add
#ifdef SUPPORT_AC_ON_REDUCE_TIME  //Pinchi 20150903 add
		bit  IsFirstRunfromAC=1;
#endif

#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
		bit  IsDrawNoVideoSignal=0;
		bit  DisplayInputHold=0;  //Pinchi 20150319 enable	//william-981029
#endif


#if 0	//william-981105
//////////////////////////////////////////////////////////////////////////////

//=============================================================================
//		Prompt				                                               
//=============================================================================

void CheckDipSwitch(void)
{
	static bit BW_STATUS=0, EDGE_STATUS=0;
			//----- Check DIP Switch ---------------

			if( EDGE_STATUS != DIP_EDGE_ENHANCE ) {
				if( DIP_EDGE_ENHANCE==0 ) {
					EDGE_STATUS = 0;
					WriteTW88(0xdd, ReadTW88(0xdd) | 0x80);
					//Printf("\r\nEnable Color Enhancement");
				}
				else {
					EDGE_STATUS = 1;
					WriteTW88(0xdd, ReadTW88(0xdd) & 0x7f);
					//Printf("\r\nDisable Color Enhancement");
				}
			}
			
			if( BW_STATUS != DIP_BW_STRETCH ) {
				if( DIP_BW_STRETCH==0 ) {
					BW_STATUS = 0;
					#ifdef WQVGA
					WriteTW88(0x86, 0x0c);
					WriteTW88(0x87, 0xff);
					#else
					WriteTW88(0x86, 0x20);
					WriteTW88(0x87, 0xe0);
					#endif
					//Printf("\r\nEnable Black/White Stretch");
				}
				else {
					BW_STATUS = 1;
					WriteTW88(0x86, 0x00);
					WriteTW88(0x87, 0xff);
					//Printf("\r\nDisable Black/White Stretch");
				}
			}
			if( AutoDetect != DIP_AUTO_DETECT ) {
				AutoDetect = DIP_AUTO_DETECT;
				//if ( AutoDetect )
					//Puts("\r\nAutoDetect Mode Enabled" );
				//else
					//Puts("\r\nAutoDetect Mode Disabled" );
			}
}
#endif
#ifdef SUPPORT_GAMMA

#include "Gamma.c"

void DownLoadGamma(void)
{
		// Red
		WriteI2C(TW88I2CAddress, 0xf0, 0xe8|1 ); 
		WriteI2C(TW88I2CAddress, 0xf1, 0x00); //  Start Address
		WriteI2C(TW88I2CAddress, 0xf2, GammaRed[0]); //  
		WriteI2Cn(TW88I2CAddress, 0xf2, &GammaRed[1], 255);
		// Blue
		WriteI2C(TW88I2CAddress, 0xf0, 0xe8|2 ); 
		WriteI2C(TW88I2CAddress, 0xf1, 0x00); //  Start Address
		WriteI2C(TW88I2CAddress, 0xf2, GammaGreen[0]); //  
		WriteI2Cn(TW88I2CAddress, 0xf2, &GammaGreen[1], 255);
		// Red
		WriteI2C(TW88I2CAddress, 0xf0, 0xe8|3 ); 
		WriteI2C(TW88I2CAddress, 0xf1, 0x00); //  Start Address
		WriteI2C(TW88I2CAddress, 0xf2, GammaBlue[0]); //  
		WriteI2Cn(TW88I2CAddress, 0xf2, &GammaBlue[1], 255);

}
#endif

void I2CDeviceInitialize( CODE_P BYTE *RegSet)
{
	int	cnt=0;
	BYTE addr, index, val;

	addr = *RegSet;
	#ifdef DEBUG_TW88
	Printf("\r\nI2C address : %02x ", (WORD)addr);
	#endif
	cnt = *(RegSet+1);
	RegSet+=2;

	while (( RegSet[0] != 0xFF ) || ( RegSet[1]!= 0xFF )) {			// 0xff, 0xff is end of data
		index = *RegSet;
		val = *(RegSet+1);

	#ifdef FIRST_RUN_FROM_AC  //Pinchi 20141029 add
		if ((IsFirstRunfromAC == 1) && (TriggerFlag == 0x20))  //REVERSE_TRIG
		{
			if (index == 0x0a) 
				val = 0x13;
			else if (index == 0x61) 
				val = 0xa6;
			else if (index == 0x66) 
				val = 0x60;
		}
	#endif

		WriteI2C(addr, index, val);

		#ifdef DEBUG_TW88
		dPrintf("\r\n    addr=%02x  index=%02x   val=%02x", (WORD)addr, (WORD)index, (WORD)val );
		#endif

		RegSet+=2;
	}
	WriteTW88(0xff, 0x00);		// set page 0
//	Printf("\r\n[MSG]I2CDeviceInitialize() => end & ReadDecoder(0x0a)=%bx , ReadDecoder(0x61)=%bx , ReadDecoder(0x66)=%bx",ReadDecoder(0x0a), ReadDecoder(0x61), ReadDecoder(0x66));  //pinchi test
}

extern CODE struct RegisterInfo UserRange;
extern CODE struct RegisterInfo VideoContrastRange;
extern CODE struct RegisterInfo VideoBrightnessRange;
extern CODE struct RegisterInfo VideoSaturationRange;
extern CODE struct RegisterInfo VideoHueRange;
extern CODE struct RegisterInfo VideoSharpnessRange;
extern CODE struct RegisterInfo DigitalVideoSaturationRange;

#ifdef ADD_ANALOGPANEL
BYTE IsAnalogOn(void)
{
	if(DIP_PANEL_SWITCH==0) return 1;
	else return 0;
}
#endif

void InitVideoData(BYTE src)
{
	#ifdef DEBUG_DECODER
	Printf("\r\n++(InitVideoData)src:%02x", (WORD)src);
	#endif

	#ifdef ADD_ANALOGPANEL
	if(IsAnalogOn())
		I2CDeviceInitialize(NTSC_Regs_Analog);
	else
	#endif
	I2CDeviceInitialize(NTSC_Regs);
	WriteTW88(0xff, 0);

	InitVideoDataSrc=src;

					
	switch( src ) {

	#ifdef SUPPORT_PAL
	case PAL:			
		#ifdef ADD_ANALOGPANEL
			if(IsAnalogOn())
				I2CDeviceInitialize(PAL_Regs_Analog);
			else
		#endif
		I2CDeviceInitialize(PAL_Regs);	
		break;
	#endif
	#ifdef SUPPORT_SECAM
	case SECAM:		
		#ifdef ADD_ANALOGPANEL
			if(IsAnalogOn())
				I2CDeviceInitialize(PAL_Regs_Analog);
			else
		#endif
		I2CDeviceInitialize(PAL_Regs);	
		break;
	#endif
	#ifdef SUPPORT_PALN
	case PALN:		
		#ifdef ADD_ANALOGPANEL
			if(IsAnalogOn())
				I2CDeviceInitialize(PAL_Regs_Analog);
			else
		#endif
		I2CDeviceInitialize(PAL_Regs);	
		break;
	#endif

	#ifdef SUPPORT_NTSC4
	case NTSC4:
	#endif
	#ifdef SUPPORT_PALM
	case PALM:
	#endif
	#ifdef SUPPORT_PAL60
	case PAL60:
	#endif
	case NTSC:

	case UNKNOWN:
	case NOINPUT:	src = NTSC;						break;
	}

	if( InputSelection == TV ) 
	{
		if( VInputStdDetectMode==AUTO ) SetAutoDetectStd();
		else							ClearAutoDetectStd(src-1);
	}
	else // Always Auto Detect.
		SetAutoDetectStd();
		
	//----- Set Panel Characteristics
///	SetPanelSingleDouble(PIXEL_SINGLE);


	WriteDecoder(V_CONTROL2, 0x15);			// Set CC line number of Even Field
//	WriteDecoder(CC_ODDLINE, 0x15);			// Set CC line number of Odd Field
	WriteTW88(0x5c, 0x06);			// change error tolerance and enable V/HSYNC change/loss detection

//	DefaultPanelAttributeForVideo();

	SetVideoMode( GetVideoModeEE());		// 02212008 change for ??????? by ybae
	#ifdef DEBUG
	Printf("\r\n SetVideoMode: %d", (WORD)GetVideoModeEE() );
	#endif

	#ifdef WIDE_SCREEN
	Set4WideScreen(GetWideModeEE());
	#endif

	#ifdef AWT_ML072S

		if(src==NTSC)
		{
		WriteTW88(0xff, 0x00);	
		WriteTW88(0x62, 0x78);
		}
		else if(src==PAL)
			{
		WriteTW88(0xff, 0x00);	
		//WriteTW88(0x62, 0x96);
		WriteTW88(0x62, 0x94);
			}

/*
		if(src==NTSC)
		{
		WriteTW88(0xff, 0x00);	
		WriteTW88(0x61, 0x87);
		}
		else if(src==PAL)
			{
		WriteTW88(0xff, 0x00);	
		WriteTW88(0xb4, 0x2d);
			}
		*/


		#ifdef Hs_debug
		Printf("\r\n **GetVideoMode=%02x", (WORD)src );
		#endif

	#endif

	
	Init_DisplayInput=0;		//william 20120328
}

/*********************************/
BYTE IsNoInput(void)
{
	if( ReadDecoder(CSTATUS) & 0x80 ) return 1;
	return 0;
}

#ifdef ID_CHECK_BY_FW
BYTE Is50Hz(void)
{
	if( ReadDecoder(CSTATUS) & 0x01 ) return 1;
	return 0;
}

BYTE Slock(void)
{
	if( ReadDecoder(CSTATUS) & 0x20 ) return 1;
	return 0;
}
#endif	// ID_CHECK_BY_FW

#ifdef SUPPORT_COMPONENT
void CheckDecoderComponent(void)
{
	CODE_P BYTE *reg=0;
	BYTE mode;
	WORD	width, height;
	DWORD	scale;

	extern CODE BYTE COMPONENT_STR[][15] ;

	if( InputSelection != COMPONENT ) return;

	mode = ((ReadDecoder(CVFMT) & 0x70) >> 4);
	if( mode == ComponentMode ) return;
	Printf("\n\rCheckDecoderComponent==> Changed component Mode: %2x-> %2x (%s)", (WORD)ComponentMode, (WORD)mode,COMPONENT_STR[mode]);

	ComponentMode = mode;
	switch (mode)
	{
	case YPBPR_576i:	
		#ifdef ADD_ANALOGPANEL
			if(IsAnalogOn())
			reg = COMP_YPbPr_576I_Reg;	
			else
		#endif
			reg = COMP_YPbPr_576I_Reg;	
			width = 700;
			height = 280;
		break;
	#if (defined WQVGA) || (defined QVGA)

	#else
	case YPBPR_480p:	reg = COMP_YPbPr_480P_Reg;		width = 630;	height = 480;	break;
	case YPBPR_576p:	reg = COMP_YPbPr_576P_Reg;		width = 630;	height = 576;	break;
	case YPBPR_720p:	reg = COMP_YPbPr_720P_Reg;		width = 413;	height = 720;	break;
	case YPBPR_1080i:	reg = COMP_YPbPr_1080I_Reg;		width = 624;	height = 540;	break;
	#endif
	default:			reg = COMP_YPbPr_480I_Reg;		width = 700;	height = 235;	break;

	}

	//InitVideoData(NTSC);

	I2CDeviceInitialize(reg);

	scale = width;
	scale *= 0x10000L;
	scale /= PWIDTH;
	XScale2(scale);
	#ifdef DEBUG_COMPONENT
	dPrintf("\r\nH scale: %xh - %xh", (WORD)(scale>>8), (WORD)(scale & 0xff));
	#endif

	scale = height;
	scale *= 0x10000L;
	scale /= PHEIGHT;
	YScale2(scale);
	#ifdef DEBUG_COMPONENT
	dPrintf("\r\nV scale: %xh - %xh", (WORD)(scale>>8), (WORD)(scale & 0xff));
	#endif

	delay(50);
	
	//william-981029>>>>>>>
	//if( IsNoInput() )	DisplayInputHold = 1;		// Hold  Input Information in no signal.
	//else 
	//DisplayInputHold = 0;
	//william-981029>>>>>

	ClearOSDInfo();

	DisplayInput();
}
#endif

void CheckDecoderInput(void)
{
#ifdef ID_CHECK_BY_FW

	BYTE std, changed=0;

	static DATA BYTE no_cnt=0, secam_cnt=0, check_cnt=0;

	//if( InputSelection == TV ) return;
	if( InputSelection == COMPONENT ) return;
	if( ( InputSelection == TV ) && (VInputStdDetectMode != AUTO) ) return;

	if( IsNoInput() ) {
//		if( VInputStd==NOINPUT ) return;
		no_cnt++;
		if( no_cnt>=10 ) {
			no_cnt = 0;
			
			SetVInputStd( NOINPUT );
			InitVideoData(NTSC);	

			#ifdef DEBUG_DECODER
			Printf("\r\nDecoder No Input");
			#endif

		}
		return;
	}
	else {
		no_cnt = 0;
	}

	switch( VInputStd ) {

	//--------------------------------------------------------------------------------------
	case NOINPUT:

		WriteDecoder(SDT, 0x0f);		// 0x1c
		//WriteTW88(0xb6, 0x87);
		//delay(50);

		switch( ReadDecoder(SDT) & 0x70 ) {
		case 0x00:	std = NTSC;	break;
		case 0x10:	std = PAL;	break;
		case 0x20:	std = SECAM;	break;
		}
		changed = 1;
		check_cnt = 0;
		secam_cnt = 0;
		break;
		
	//--------------------------------------------------------------------------------------
	case NTSC:
		if( Is50Hz() ) {
			if( !Slock() ) secam_cnt++;
			if( ++check_cnt>=10 ) {
				if( secam_cnt>=7 ) {
					std = SECAM;
					changed = 1;
				}
				else {
					std = PAL;
					changed = 1;
				}
				check_cnt = 0;
				secam_cnt = 0;
			}
		}
		break;

	//--------------------------------------------------------------------------------------
	case PAL:

		if( !Is50Hz() ) {
			std = NTSC;
			changed = 1;
			check_cnt = 0;
			secam_cnt = 0;
		}

		if( ReadTW88(0x30) & 0x10 ) secam_cnt++;
		if( ++check_cnt>=10*10 ) {
			if( secam_cnt>=7 ) {
				std = SECAM;
				changed = 1;
			}
			check_cnt = 0;
			secam_cnt = 0;
		}
		break;

	//--------------------------------------------------------------------------------------
	case SECAM:

		if( !Is50Hz() ) {
			std = NTSC;
			changed = 1;
			check_cnt = 0;
			secam_cnt = 0;
		}

		if( !(ReadTW88(0x30) & 0x80) ) secam_cnt++;
		if( ++check_cnt>=10*10 ) {

			#ifdef DEBUG_DECODER
			Printf("%4d", secam_cnt);
			#endif

			if( secam_cnt<=7*10 ) {
				std = PAL;
				changed = 1;
			}
			check_cnt = 0;
			secam_cnt = 0;
		}
		break;

	default:
		break;
	}

	if( changed ) {
		SetVInputStd( std );
		InitVideoData(std);
		//DisplayInput();

		switch( std ) {
		case NTSC:	WriteDecoder(SDT, 0x08);	break;
		case PAL:	WriteDecoder(SDT, 0x09);	break;
		case SECAM:	WriteDecoder(SDT, 0x0a);	break;
		}
		
		#ifdef DEBUG_DECODER
		Printf("\r\n-------> Source changed %d", (WORD)VInputStd);
		#endif
		delay(99);
	}
		
#else // not ID_CHECK_BY_FW

	BYTE std1, std, cnt=0, trycnt=0, ChangedNoinput;

		#ifdef DEBUG_DECODER
		Printf("\r\n====>CheckDecoderInput<====");
		#endif
	// LJY101002
	// Algorithm I 
	//if( InputSelection == TV ) return;
	//if( InputSelection == COMPONENT ) return;
	if( ( InputSelection == TV ) && (VInputStdDetectMode != AUTO) ) return;

	//if( VInputStdDetectMode==AUTO ) {
		std1 = NOINPUT;
		while(1) {						// keep checking until it's stable.(check cnt)
			std = DetectDecoderInput();
			
			#ifdef DEBUG_DECODER
			Printf("\r\n%bx :DetectDecoderInput: std=0x%bx, DisplayedOSD=0x%bx , VInputStd=%bx",trycnt,std,GetDisplayedOSD(),VInputStd);
			#endif
			trycnt++;
			if( trycnt>= 10/*50*//*200*/ )			// so many try, but unstable
				break;

			if( std!=UNKNOWN && std!=VInputStd ) 
			{
			//	Printf("\r\n[MSG]CheckDecoderInput() => run &  cnt=%bx",cnt);  //pinchi test
				//changed!!
				if( std == std1 )		// same as previous one.
					cnt++;
				else
				{					// ooh.. different from previous one.
					cnt = 0;
					std1 = std;
				}

				if( cnt >= 2) { //100 ) {
			#ifdef REFERENCE
			#else
					//ClearOSDInfo();
			#endif 
					//LCDPowerOFF();
					if(  std == NOINPUT  ) 		//some input->NOINPUT
					{	
					//	Printf("\r\n[MSG]CheckDecoderInput() => some input->NOINPUT & DisplayedOSD()=%bx, std=%bx",GetDisplayedOSD(), std);  //pinchi test
						SetVInputStd( std );		//WILLIAM-20120502
						ChangedNoinput = 1;		// Diaplay Input Information for no signal.
					}
					else if( VInputStd==NOINPUT ) //NOINPUT->some input
					{
					//	Printf("\r\n[MSG]CheckDecoderInput() => NOINPUT->some input & DisplayedOSD()=%bx , std=%bx",GetDisplayedOSD(),std);  //pinchi test
					#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
					//	AWT_Display_NoVideoSignal(OFF);
						if ((SelectModeType == AVMode) && (IsDrawNoVideoSignal == 1))
		    				ClearGAUGEINFO();
					#endif

						SetVInputStd( std );		//WILLIAM-20120502
						InitVideoData(std);		//WILLIAM-20120502
						ChangedNoinput = 0;		// Diaplay Input Information for no signal.
					}
					else 
					{								//some input1->some input2
//						LCDPowerOFF();
						//PanelMute(1);
					 //   Printf("\r\n[MSG]CheckDecoderInput() => some input1->some input2 & DisplayedOSD()=%bx, std=%bx",GetDisplayedOSD(), std);  //pinchi test
					#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
					//	AWT_Display_NoVideoSignal(OFF);
						if ((SelectModeType == AVMode) && (IsDrawNoVideoSignal == 1))
		    				ClearGAUGEINFO();
					#endif

						SetVInputStd( std );
						InitVideoData(std);	
						delay(50);
//						LCDPowerON(0);
						ChangedNoinput = 0;		// Diaplay Input Information for no signal.
					}					
					//LCDPowerON(0);
				#ifdef REFERENCE
				#else
				//	delay(0xff);  //Pinchi 20141029 disable
				#endif 
					//DisplayInput();		//william-981029
				#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add to enable
					DisplayInputHold = ChangedNoinput;	//william-981029
				#endif
					break;
				}
			}
			#if 0		//william-981029
			else
			{
				if(  std == NOINPUT  )			// NOINPUT->NOINPUT
					DisplayInputHold = 1;		// Hold input information in no signal.
				else
					DisplayInputHold = 0;		// clear 
				break;
			}
			#endif
		}
		//Printf("\r\nDisplayInputHold=%02x",(WORD)DisplayInputHold);
	//}
	
#endif	// ID_CHECK_BY_FW

}

BYTE ReadVInputSTD(void)
{
	BYTE std;
	
	if( IsNoInput() ) return 1; // Noinput!!
	
	std = ReadDecoder(SDT) & 0xf0;
	if( std & 0x80 ) return 1; // Detection in progress..
	else 
		return ((( std & 0x70 ) >> 4 ) + 1 );
}

BYTE GetVInputStdInx(void)
{
	BYTE i, std;

	std = ReadVInputSTD();

	switch( std ) {

	case NTSC4:
	case PALM:
	case PAL60:
	case NTSC:		IVF = 60;		IHF = 15723;	break;	// 15734

	case SECAM:
	case PALN:
	case PAL:		IVF = 50;		IHF = 15723;	break;  // 15625
	default:		IVF = 0;		IHF = 0;		break;
	}

	for(i=0; ; i++) {
		if( struct_VInputStd[i].Id ==std )
			return i;
		if( struct_VInputStd[i].Id ==0 )
			break;
	}
	return 0;
}

#ifdef WIDE_SCREEN
BYTE GetVInputStd(void)
{
	return VInputStd;
}
#endif

void SetVInputStd(BYTE newd)
{
	VInputStd = newd;

	#ifdef DEBUG
	Printf("\r\n(SetVInputStd=%bx) VInputStd:%d(%s)",newd, struct_VInputStd[GetVInputStdInx()].Name);
	#endif

	#if 0
	if(DVR_System!=newd &&  GetInputSelection()==CH_TW2835)
		{
		DVR_System=newd;		//tw2835 system
		if(GetDVRStatusflag==1)
			Hs_DvrTxCmdPaser(SetSystem);
		}
	#endif
	switch( VInputStd ) {

	#ifdef SUPPORT_NTSC4
	case NTSC4:
	#endif
	#ifdef SUPPORT_PALM
	case PALM:
	#endif
	#ifdef SUPPORT_PAL60
	case PAL60:
	#endif
	case NTSC:		IVF = 60;		IHF = 15723;	break;	// 15734

	#ifdef SUPPORT_SECAM
	case SECAM:
	#endif
	#ifdef SUPPORT_PALN
	case PALN:
	#endif
	#ifdef SUPPORT_PAL
	case PAL:		IVF = 50;		IHF = 15723;	break;  // 15625
	#endif

	default:		IVF = 0;		IHF = 0;		break;
	}
}

BYTE GetInputSelection(void)
{
	return InputSelection;
}

BYTE GetNextInputSelection(void)
{
	BYTE i;

#ifdef QUAD
	for (i=1; ;i++)
		if( struct_InputSelection[i].Id==InputSelection )  break;
	i++;
	if( struct_InputSelection[i].Id == 0 ) i=1;

	return struct_InputSelection[i].Id;
#else
	for (i=1; ;i++)
		if( struct_InputSelection_S[i].Id==InputSelection )  break;
	i++;
	if( struct_InputSelection_S[i].Id == 0 ) i=1;

	return struct_InputSelection_S[i].Id;
#endif
}

void PowerDown_XTAL(bit flag)
{
	if( flag ) P3_7 = 1;
	else      P3_7 = 0;
}

#if 0
void Audio_Select(BYTE flag)
{
	switch(flag)
	{
		case 0:
			TW2835Cmd("\n\raudioselect 0\n\r");	
			break;
		case 1:
			TW2835Cmd("\n\raudioselect 1\n\r");	
			break;	
		case 2:
			TW2835Cmd("\n\raudioselect 2\n\r");	
			break;
		case 3:
			TW2835Cmd("\n\raudioselect 3\n\r");	
			break;
	}
}
#endif

void ChangeInput(BYTE newsel)
{
//	extern	CODE struct _PCMDATA PCMDATA[];
	#ifdef DEBUG
	BYTE i;
	#endif
	
	#if (defined SUPPORT_PC) || (defined SUPPORT_DTV)
	BYTE ret;
	#endif
	
#ifdef QUAD
	if( InputSelection==newsel ) return;
#else
	#ifndef AWT_ML072S
	if( InputSelection==newsel ) 
	{
		DisplayInput();		//william-20100420
		return;
	}  
	#endif
#endif
	

	//DisplayInputHold = 0; // Refresh Input info.	//william-981029
//	ClearOSDInfo();  //Pinchi 20140903 disable for compiler warning
#if 0//ryan@20171016
if(AV_MODE_DELAY==1)
	clrBacklight();
else
	LCDPowerOFF(); 
#else
	clrBacklight();

#endif
	//LCDPowerON(0); 

	//PanelMute(1);

		//mute
		WriteI2C( TW88I2CAddress,0xff,0x01);
		WriteI2C( TW88I2CAddress,0xb4,00);
		WriteI2C( TW88I2CAddress,0xff,0x00); 
		Wait_ms(20);
								
	InputSelection = newsel;

		#ifdef DEBUG
		for (i=1; ;i++)
			if( struct_InputSelection[i].Id==InputSelection )  break;
		Printf("\r\n ->->->->->->->->->->-> Changed Input: %s(%02x)", struct_InputSelection[i].Name, (WORD)InputSelection);
		#endif

		InitVideoData(VInputStd);

		switch(InputSelection)
		{
			#ifdef SUPPORT_PC
			case PC:
						AVGAInput();				// load data and input mux selection to PC 							
						AutoPHPCalDisable();
						tic_pc = 0;
						ret = DetectAndSetForVGAInput(1);
						//Audio_Select(2);
					 	VGAAudio=1;
					    ChangeVol(0);			//william-v1.1-991208
						//Audio_Select1=1;                           
             					//Audio_Select2=0;  
						//ret = DetectAndSetForVGAInput(0);
						break;
			#endif
	 
			case CH_TW2835:
						COMPOSITE1Input();
						//ExtAudio();
					    //Audio_Select(0);
					    VGAAudio=0;
	    					Audio_Select1=0;
             			   	 	Audio_Select2=0;
						Wait_ms(20);
						ChangeVol(0);			//william-v1.1-991208
			
					    	Printf("\r\nCH_TW2835(%02x),ReadDecoder(0x66)=%bx",(WORD)InputSelection,ReadDecoder(0x66));
					    break;
            #ifdef AWT_ML072S
				case CH_CAMD:
					COMPOSITE4Input();
				//#endif
					VGAAudio=0;
					Audio_Select1=1;                           
            				Audio_Select2=1; 
					Wait_ms(20);
					ChangeVol(0);			//william-v1.1-991208
					Printf("\r\n **CH_CAMR(%02x)",(WORD)InputSelection);
					break;
		#endif
		
            #ifdef USE_CAMD  //Pinchi 20150827 add
			case CH_CAMD:
				#ifdef QUAD
					COMPOSITE3Input();
				#else
					COMPOSITE2Input();
				#endif				        
					//Audio_Select(1);
					VGAAudio=0;
				#ifdef AWT_ML072S		//william @20130902 v1.0.1.2
					Audio_Select1=1;                           
             				Audio_Select2=0; 

				#else
					Audio_Select1=0;                           
             				Audio_Select2=1;  
				#endif	
					Wait_ms(20);
					ChangeVol(0);			//william-v1.1-991208

			
					Printf("\r\n CH_CAMD(%02x)",(WORD)InputSelection);
					break;
            #endif

			case CH_AV:
				#ifdef AWT_NEW_SLIM_MODEL  //Pinchi 20150414 add for AWT ML077
					COMPOSITE4Input();

					VGAAudio=0;
					Audio_Select1 = 1;
					Audio_Select2 = 1;
					Wait_ms(20);
					ChangeVol(0);

				#else
				  #ifdef QUAD
					COMPOSITE2Input();
				  #else
				COMPOSITE3Input();
				  #endif

					 //Audio_Select(2); 
					VGAAudio=0;
				  
					//#ifdef AWT_ML072S		//william @20130902 v1.0.1.2
				  #if (defined AWT_ML072S) || (defined HTRV)  //Pinchi 20150910 add HTRV model for correct audio select
					Audio_Select1=0;
					Audio_Select2=1;
				  #else

				  	#ifdef TW8816
				   	Audio_Select1=0;
					Audio_Select2=1;
					#else
					Audio_Select1=1;
					Audio_Select2=0;
					#endif		
				  #endif	
					  Wait_ms(20);
				  
					ChangeVol(0);			//william-v1.1-991208
				  			  
 			#endif
					
					Printf("\r\n CH_AV(%02x)", (WORD)InputSelection); 
					break;

			#ifdef SUPPORT_DTV  //Pinchi 20150414 add
			case DTV:
					COMPOSITE4Input();

					//Audio_Select(2);
					VGAAudio=0;
					ChangeVol(0);			//william-v1.1-991208
					Audio_Select1=1;
             		Audio_Select2=1;
					Printf("\r\n CH_AV(%02x)", (WORD)InputSelection);
					break;
			#endif

			#ifdef HS
			case CH_CAMB:
					COMPOSITE2Input();

					//Audio_Select(2);
					VGAAudio=0;
					ChangeVol(0);			//william-v1.1-991208
					Wait_ms(20);
					Audio_Select1=1;
             				Audio_Select2=0;
					Printf("\r\n CH_CAMB(%02x)", (WORD)InputSelection);
					break;
			#endif
			
		}
	CheckPanelImage();		//william-981111 		changesource load panelimage
	SaveInputSelectionEE(InputSelection);		// HHY 1.31
//#ifdef WIDE_SCREEN
//	WideScreenMode = WIDESCREEN_WIDE;
//#endif
	//InitOSDMenu();  // Standby OSD Menu

	#ifdef DEBUG_PAUSE
	Pause("Detect and Set {CR}");
	#endif

	#if (defined SUPPORT_PC) || (defined SUPPORT_DTV)
	if( InputSelection==PC || InputSelection==DTV ) {
		if( ret==TRUE ) {
			ret = ReadDecoder(ACNTL);
			ret |= 0x80;	// Software Reset
			WriteDecoder(ACNTL, ret);
			delay(30);
			WriteTW88( 0xff, 1);
			WriteTW88( 0xCD, 1 );	// init LLPLL
			WriteTW88( 0xff, 0 );
			//DisplayInput();
		}
		else {
		    //CheckDipSwitch();//andy AWT 981015		
			LCDPowerON(0);
			delay(100);
			WriteTW88( 0xd0, 0xff);	// clear status
			WriteTW88( 0xd1, 0xff);	// clear status
			return;
		}
	}
	else 
	#endif
	{
		//DisplayInput();

		#ifdef SUPPORT_COMPONENT
		if( InputSelection == COMPONENT ){
			delay(30);
			ComponentMode = 0xff;
			CheckDecoderComponent();
		}
		else 
		#endif
		{
			delay(30);
			CheckDecoderInput();
		}
//william-981110		
//Printf("\r\nSetPanelBrightnessReg");
//	SetPanelBrightnessReg(RED,  0x80);
//	SetPanelBrightnessReg(GREEN,0x80);
//	SetPanelBrightnessReg(BLUE, 0x80);
//	SetPanelContrastReg(0,0x80);
//	SetPanelContrastReg(1,0x80);
//	SetPanelContrastReg(2,0x80);
//william-981110	
	}
	//----- Check DIP Switch ---------------
	//CheckDipSwitch();                      //andy AWT 981015		
	//Pause("\r\nBeforn LCD ON");
	//delay(250);

#ifndef QUAD
 // if(NowModeState==JumpMode)
  	CheckMirror();
 // else	
//	CheckMirror();
#endif

		DisplayInput();

	
if(AV_MODE_DELAY==1)
{
	SetBacklight();
	#ifdef Hs_debug
	Printf("\r\nAV_MODE_DELAY==1");
	#endif
}
else
	LCDPowerON(0);

	delay(100);

	WriteTW88(0xd0, 0xff);	// clear status
	WriteTW88(0xd1, 0xff);	// clear status
}

void PowerOff(void)
{
//	Printf("\r\n++(PowerOff)__");
//	PowerMode = OFF;
	//AudioOff();
	AudioMute(0);
	//ClearOSDInfo();		//william v0.2 20120223
	#ifdef TW8816
	clrBacklight();
//mask by ryan@20180102 boot panel scree isuue	P3_5=0;
	#else
	LCDPowerOFF();
	#endif
	PowerLED(OFF);
}

void SetOSDLastKeyInTime(void)
{
	OSDLastKeyInTime = GetTime_ms();
}

WORD GetOSDLastKeyInTime(void)
{
	return OSDLastKeyInTime ;
}

//=============================================================================
//
//=============================================================================
#ifdef SUPPORT_PATTERN
CODE BYTE PATTERN[7][] = {
	{TW88I2CAddress,7, 0x61,0x5f, 0x64,0xff, 0x65,0x00, 0x66,0x00, 0x67,0xff, 0x68,0x00, 0x69,0x00, 0xff,0xff},	// Red
	{TW88I2CAddress,7, 0x61,0x5f, 0x64,0x00, 0x65,0xff, 0x66,0x00, 0x67,0x00, 0x68,0xff, 0x69,0x00, 0xff,0xff},	// Green
	{TW88I2CAddress,7, 0x61,0x5f, 0x64,0x00, 0x65,0x00, 0x66,0xff, 0x67,0x00, 0x68,0x00, 0x69,0xff, 0xff,0xff},	// Blue
	{TW88I2CAddress,7, 0x61,0x5f, 0x64,0xff, 0x65,0xff, 0x66,0xff, 0x67,0xff, 0x68,0xff, 0x69,0xff, 0xff,0xff},	// White
	{TW88I2CAddress,7, 0x61,0x5f, 0x64,0x00, 0x65,0x00, 0x66,0x00, 0x67,0xff, 0x68,0xff, 0x69,0xff, 0xff,0xff},	// Gray
	{TW88I2CAddress,7, 0x61,0x5f, 0x64,0x00, 0x65,0x00, 0x66,0x00, 0x67,0x00, 0x68,0x00, 0x69,0x00, 0xff,0xff},	// Black
	{TW88I2CAddress,7, 0x61,0x00, 0x64,0xc0, 0x65,0xc0, 0x66,0xc0, 0x67,0x88, 0x68,0x88, 0x69,0x88, 0xff,0xff}	// Gray scale
};
#endif // SUPPORT_PATTERN

void AdjustAutoDayNight(BYTE val)
{
	BYTE page;
	BYTE PWMLevelTemp;
	val=0xff-val;

	#if 1//ryan@20170928
	if(val>=0&&val<100)
		PWMLevelTemp=0;
	else if(val>=100&&val<140)
		PWMLevelTemp=20;//20;
	else if(val>=140&&val<180)
		PWMLevelTemp=40;//50;
	else if(val>=180&&val<220)
		PWMLevelTemp=60;//65;
	else if(val>=220&&val<=255)//andy 20110414
	{
		//#ifdef AWT
		PWMLevelTemp=75;//80;
		//#else
		//PWMLevelTemp=115;
		//#endif
	}

	#else
	if(val>=0&&val<100)
		PWMLevelTemp=0;
	else if(val>=100&&val<140)
		PWMLevelTemp=30;//20;
	else if(val>=140&&val<180)
		PWMLevelTemp=60;//50;
	else if(val>=180&&val<220)
		PWMLevelTemp=80;//65;
	else if(val>=220&&val<=255)//andy 20110414
	{
		//#ifdef AWT
		PWMLevelTemp=110;//80;
		//#else
		//PWMLevelTemp=115;
		//#endif
	}
	#endif
	//else
	//	PWMLevelTemp=0;

#ifdef SUPPORT_ML072Q_AUTO_DAY_NIGHT  //Pinchi 20150825 add  AWT_ML072Q  //Pinchi 20140918 add for AWT ML072Q
	if (DayNightLevel == 0)  //1=OFF =>Day , 0=ON =>AUTO
#else
	if(DayNightLevel==1)
#endif
	{
		if(AutoDayNightDelay<(5+5+5))
			AutoDayNightDelay++;
		else
		{
			if(PWMLevel > PWMLevelTemp)
				PWMLevel-=1;
			else if(PWMLevel < PWMLevelTemp)
				PWMLevel+=1;

			AutoDayNightDelay=0;
		}
	}
	else
	{
		PWMLevel=PWMLevelTemp;
		//PWMLevel=0x08;
	}	

	//Printf("\r\nLADC0=%02x",(WORD)val);
	page = ReadTW88( 0xff );
	WriteTW88( 0xff, 0x00 );		// set page 0
	WriteTW88( 0xbe, ((ReadTW88(0xbe) & 0xcf) | 0x10) );	// set active Low control, if want active high clear 
	//WriteTW88( 0xc4, ((ReadTW88(0xc4) & 0x80)|(val>>2)) );	// set pwm number
	WriteTW88( 0xc4, ((ReadTW88(0xc4) & 0x80)|(PWMLevel)) );	// set pwm number
	WriteTW88( 0xff, page );
}

void Hs_InitVars(void)
{
#ifdef SUPPORT_SDCARD  //Pinchi 20140925 add for AWT ML072Q 
	BYTE i;
#endif
	SEQFlag=0;
	SEQTime=0;
	TriggerMode=8;		//No_TRIG

#ifdef SUPPORT_SDCARD  //Pinchi 20140925 add for AWT ML072Q 
	AccPowerDown=1;
	SelectBoxMode=0;
//#ifdef Format_SDCard	
	FormatSDCard=1;
//#endif
	DVR_SDCardAvailable=0xFF;
	for(i=0;i>14;i++)
		Information[i]=0;

	DoorState=P1_7;
#endif
}

void LoadEEPROM (void)
{
	BYTE val;
	 PowerFlag = ReadEEP(EEP_Powerflag);
	 //PowerFlag = 1;		//WILLIAM-V1.3.1.2	20120522
	 SelectModeType = ReadEEP(EEP_SelectMode);

	OSD_LOCKF= ReadEEP(EEP_ONOFFChoice);
	    Disp_Input = ReadEEP(EEP_COSDMode); 
		
	 TimeStep = ReadEEP(EEP_TimeStep);
#ifdef AWT_ML072Q		//william @20130905
	 Priority = ReadEEP(EEP_PRIORITY);
#else
	 Priority=0;
#endif
	 DayNightLevel= ReadEEP(EEP_AutoMode);
   	 PelcoChoiceFLAG = ReadEEP(EEP_PELCO);
	 CAMNumber = ReadEEP(EEP_CAMNUMBER);  
	 Baud_rate = ReadEEP(EEP_Baud_rate);
	 SDCardCoverDetect=ReadEEP(EEP_SDCardDetect);
	 ReverseModeFlag=ReadEEP(EEP_ReverseMode);//andy holtz 20091123
	#ifdef AWT_ML072S //william @20130902 v1.0.1.2
	 JUMPAVFlag=ReadEEP(EEP_JUMPAV_TIMESET);	
	 NowModeState=SelectMode;
	#else
	 NowModeState = ReadEEP(EEP_NowModeState);
	#endif

	#if 0  //pinchi test
	 val = ReadEEP(EEP_COSDMode);   //OSD ON & OFF 切換		 //william-980428
	   if(val==0) 					
	   {
		  Attr_A|=0x02;  //*** BIT1: Channel OSD  set 1
		  Attr_B|=0x02;
		  Attr_C|=0x02;
		  Attr_R|=0x02;
		  //displayhold_flag=0;
	   }
	   
	   else 						  
	   {
		  Attr_A&=0x0d;  //*** BIT1: Channel OSD  set 0
		  Attr_B&=0x0d;
		  Attr_C&=0x0d;
		  Attr_R&=0x0d;
	   }
	#endif
	
	   val = ReadEEP(EEP_CAMAMode);   //CAM Mirror開關設定															  
	   if(val==0)					  //ON				
		 Attr_A|=0x01;				  //*** BIT0: Horizontal Mirror  set 1
	   else 						  //OFF 		   
		 Attr_A&=0x0E;				  //*** BIT0: Horizontal Mirror  set 0
	
	   val = ReadEEP(EEP_CAMBMode); 									   
	   if(val==0)					 //ON			   
		 Attr_B|=0x01;				 
	   else 						 //OFF							  
		 Attr_B&=0x0E;		   
	
	   val = ReadEEP(EEP_CAMCMode); 															
	   if(val==0)					 //ON						   
		 Attr_C|=0x01;						  
	   else 						 //OFF							 
		 Attr_C&=0x0E;					 
	
	   val = ReadEEP(EEP_CAMRMode); 															
	   if(val==0)					 //ON						   
		 Attr_R|=0x01;						  
	   else 						 //OFF							 
		 Attr_R&=0x0E; 
		
		AudioVol = GetAudioVolEE();
		PCAudioVol = GetPCAudioVolEE();
		DVR_AudioRecord = ReadEEP(EEP_AudioRecord); 
		
	//if(PowerFlag)
}

#ifdef SUPPORT_SDCARD
void ACCPowerControl(void)
{

if(ACC_B==1 && AccPowerDown==1)
	{	
	Hs_DvrTxCmdPaser(Halt_Start);
	PowerDownStart=1;
	AccPowerDown=0;

	if(DVR_Ready==1)			
		{
		if(PowerDownWait>29)
			{
			if(ACC_B==1)	
				{
			#ifdef BJTSwitch	
				PPWR=0;
			#else
				PPWR=1;
			#endif
				}
			else
				{
				PowerDownStart=0;
				PowerDownWait=0;
				AccPowerDown=1;
				}		
			}
		}
	else
		{
		if(ACC_B==1)
			{
		#ifdef BJTSwitch	
			PPWR=0;
		#else
			PPWR=1;
		#endif
			}
		else
			{
			PowerDownStart=0;
			PowerDownWait=0;
			AccPowerDown=1;
			}
		}
	}

	if(((PowerDownWait%10)==0) && PowerDownWait!=0)
		AccPowerDown=1;
}

//#ifdef SUPPORT_SDCARD
void SDCardHandler(void)
{
	BYTE val;

	if(RS2_in!=0 /*&& !(GetDisplayedOSD() & MENU)*/)		//william-v1410-20120524
		{
		val=DvrReceivePaser();	
		//Printf("\r\nDvrReceivePaser=%02x",(WORD)val);
		//RS2_in=0;
		}
	
	if(GetDVRStatusflag==1)
		{
		//Hs_DvrTxCmdPaser(GetDVRStatus);
		Hs_DvrTxCmdPaser(GetDVRParam);
		Hs_DvrTxCmdPaser(GetDATETIME);

		if(DoorState&&(SDCardCoverDetect==0))
			Hs_DvrTxCmdPaser(DoorOpen);
		else
			Hs_DvrTxCmdPaser(DoorClose);

		#if 0	
		Hs_DvrTxCmdPaser(SetSystem);		
		#endif
		GetDVRStatusflag=0;
		DisplayDVRStatus();
		}
	
	if(second==30 && DVRReSendDisable==0 && !(GetDisplayedOSD() & MENU))		//william-v1410-20120524
		{
		Hs_DvrTxCmdPaser(GetDATETIME);
		DVRReSendDisable=1;						//william-v1410-20120524
		}

	if(DoorState!=P1_7&&(SDCardCoverDetect==0))
		{
		if(P1_7)
			Hs_DvrTxCmdPaser(DoorOpen);
		else
			Hs_DvrTxCmdPaser(DoorClose);	
		}

	if(((GetDisplayedOSD()&(TVVOL|MENU))==0) && DVR_Ready==1)
		DisplayDVRStatus();
//#ifdef Format_SDCard
	if(FormatSDCard>=60)
		{
		DisplayInformation(InfoRECORDERROR);	
		Printf("\r\n FormatSDCard%02x",(WORD)FormatSDCard);
		}
//#endif		
	if((second&0x01)==0 && DVRReSendDisable==0)
		{
		if(CommandBuffer!=0)
			{
			DVRCommandReSend();
			Commanderror++;
			DVRReSendDisable=1;
			}
		else
			Commanderror=0;
		}
	
	if(Commanderror>=40)						//william-v1410-20120524
		DisplayInformation(InfoPLZRESETSYSTEM);	
	
	if(second&0x01 && DVRReSendDisable==1)
		DVRReSendDisable=0;
}
#endif

void main(void)
{
#ifdef QUAD
	//BYTE i;  //Pinchi disable for compiler warning
#endif
//	WORD  TW2835Check=0;  //william-v1.1-991208
	//mask by ryan@20180102 boot panel scree isuue	P3_5=0;
	AudioMute(0);	

#if 0
#ifdef BJTSwitch
	PPWR=1;
#else
	PPWR=0;
#endif
#endif
	//GPS_PWR=1;
	//GM8126_WD1=1;
	//GM8126_WD2=1;
	//RS232Select=0;

	Wait_ms(10);
	TW88HWReset = 0;			//TW88 HW reset by port pin, internal MCU no meaning

	InitCPU();
    	PowerLED(ON);

	InitVars();
	Hs_InitVars();
	InitTechwell();
			
#ifdef Monitor_debug
SetMonAddress(TW88I2CAddress);
#endif
#ifdef SUPPORT_SDCARD	
	Hs_Protocol_Init();
#endif
	
	main_init();
//	PowerUp = 0;  //Pinchi 20140925 disable for duplicate setting
	Wait_ms(10);

///=======================
	WriteDecoder(INFORM, 0xc6);			// 01 00 00 x x		27M, COMPOSITE, Y0, C-, V-
//	WriteDecoder(ACNTL, 0x00);	// CLK-on, Y-on, C-off, V(FB)-off
	//WriteDecoder(MISC3, ReadDecoder(MISC3)|0x06); 
///=======================

	LoadEEPROM();
	TR_JUMP_HOLD=NowModeState;//ryan@20170912
	
//william-v1.1-991208
#if 0
#ifdef QUAD
for(i=0;i<20;i++) 
{
	TW2835Check=TW2835Command(CAM_A,Attr_A,Attr_B,Attr_C,Attr_R);
	if(TW2835Check==TRUE)
		break;
	Wait_ms(100);
}
#endif
#endif

	CAMOutDSel(ReadEEP(EEP_CAMOutMode));  //Pinchi 20150827 add       //設定CAMOut動作 
	
	TriggerFlag=0x00;					// william-1.0-test

#ifdef HTRV  //Pinchi 20140902 add for HTRV ML072Q
	GaugeVStart= ReadEEP(EEP_Gauge_VStart);                 //william-v1.43-970318
#endif

#ifdef FIRST_RUN_FROM_AC  //Pinchi 20141029 add
	IsFirstRunfromAC = 1;
#endif

#ifdef Hs_debug
Printf("\r\n*** Debug Mode is going ***");  //ryan@20170929
#endif

#ifdef FIX_2835_SCREEN_NOISE  //Pinchi 20160929 add
	TW2835Cmd("\n\rbusw 0 1 7E 89");
#endif


LCDPowerON(3);//ryan@20171016

	//#ifdef WIDE_SCREEN
	//Set4WideScreen(WIDESCREEN_WIDE);
	//#endif


		WriteDecoder(0xd5, 0x09);	// Standby	Panel:1  Signal:0  Back:0
		delay(4);
		WriteDecoder(0xd5, 0x0b);	// Suspend	Panel:1  Signal:1  Back:0
		delay(10);
		#ifdef BACKLIGHT_PWM
		WriteDecoder(0xd5, 0x0f);	// On		Panel:1  Signal:1  Back:1	
		#endif



		
#if 1///ryan@20180112
if(PowerFlag==0)
{

		SetNowMode();///ryan@20180111 for live out issue
		#ifdef Hs_debug
		Printf("\r\n(power off reboot)");  //ryan@20170929
		#endif
}
#endif

#ifdef WIDE_SCREEN
	Set4WideScreen(WIDESCREEN_WIDE);
	#endif
	
	while(1) {
	if(PowerFlag)
		main_loop();		//exit when power off
		
	WaitPowerOn();

	////ChangeVol(0);  //Pinchi 20150827 move to main()
	////DVRAodioSel(DVR_AudioRecord);
	////CAMOutDSel(ReadEEP(EEP_CAMOutMode));  //Pinchi 20150827 move to main()       //設定CAMOut動作 
	//Printf("Last Check --0x%02x\r\n", (WORD)ReadDecoder(0));
	}
}

//bit CCFL_status;	
void main_loop(void)
{
	//static bit AUTO_STATUS=0;
	BYTE val;
	
	TW2835Cmd("  \n\r");

	//---------------------------------------------------------------
	//			             Main Loop
	//---------------------------------------------------------------
	while(1) {

	
	#ifdef SUPPORT_SDCARD
		ACCPowerControl();	
	#endif
		//-------------- Check Serial Port -----------------
	#ifdef SERIAL

	
		#ifdef Monitor_debug
			while( RS_ready() ) 
			{
			Monitor();				// for new monitor functions
			}
		#endif	
			//DebugKeyIn( RS_rx() );	// Input - Serial Port
	#endif // SERIAL

		//if ( AccessEnable == 0 ) continue;

		//-------------- Chip Manual Test  ---------------------
	#ifdef CHIP_MANUAL_TEST
		ChipManualTest();
	#endif
		
	#ifdef SUPPORT_SDCARD
		SDCardHandler();	
	#endif


	#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
//		if ((SelectModeType == AVMode) && !(GetDisplayedOSD() & MENU)&&(TriggerFlag==0))
		#ifdef AWT_ML072S
		#else
		if ((SelectModeType == AVMode) && !(GetDisplayedOSD() & MENU))
		{
			if (DisplayInputHold == 1)  //Input=No signal
			{
	
			      if (IsDrawNoVideoSignal == 0)
				{
					IsDrawNoVideoSignal = 1;

				//if(ReadEEP(EEP_COSDMode)==0) 
	
					displayhold_flag = 0;
				
					if (ReadEEP(EEP_COSDMode) == 0)
						DisplayedOSD &= (~(INPUTINFO));
					else
						displayhold_flag =3;//add to setup 2s for Display OFF	//ryan@20170922

					DisplayInformation(InfoNoVideoSignal);
				}

	
			}
			else
			{
				
				if ((IsDrawNoVideoSignal == 1)&& !(GetDisplayedOSD() & GAUGEINFO))//ryan@20170922
				{
					IsDrawNoVideoSignal = 0;
					if (ReadEEP(EEP_COSDMode) == 1);
					DisplayInput();
				}
			}
		}
		#endif
	#endif

		//--------------ADC select box---------------------
		//SelectBoxHandler();

		//--------------Check Trigger ---------------------
	   // if(SelectBoxADC<8)
	   //Printf("\r\nSelectBoxMode=%d",(WORD)SelectBoxMode);
		{
		val=CheckTrigger();
		TriggerHandler(val);
		}


		if(TriggerFlag==0 /*&& (SelectBoxMode==0 || SelectBoxMode==5)*/)	//當非倒車左右轉停車時為真
		{ 
			if(SEQFlag) 						// SEQ Mode
			{ 
				if(SEQTime>=TimeStep) 
				{
					SEQMode();
					SEQTime=0;
				}
			}
		}

		//--------------AUTO DAY & NIGHT-------------
	//	if (AutoDayNight == 0)		
	#ifdef SUPPORT_ML072Q_AUTO_DAY_NIGHT  //Pinchi 20150825 add  //AWT_ML072Q  //Pinchi 20140918 add for AWT ML072Q
		if (DayNightLevel == 0)  //ON=Auto
		{
			val = ReadDecoder(LADC0);
			AdjustAutoDayNight(val);
		}
		else  //OFF=Day
		{
			AdjustAutoDayNight(0xff);
		}
		//Printf("DayNightLevel=%02x",DayNightLevel);
	#else
		switch(DayNightLevel)
		{
			case 0:
				//AutoDayNight=1;
				AdjustAutoDayNight(0xff);
				break;

			case 1:	
				//AutoDayNight=0;
				val=ReadDecoder(LADC0);
				AdjustAutoDayNight(val);
				break;

			case 2:
				//AutoDayNight=1;
				AdjustAutoDayNight(0);
				break;
		}
	#endif

	//-------------- Check Key in --------------------------
		
		if( !CheckKeyIn() ) break;			// POWEROFF
		
#ifdef AWT_ML072S//ryan@20171208 

if(!(GetDisplayedOSD() & (TVVOL|MENU)))
{
	if((!(GetDisplayedOSD() & (INPUTINFO))))
	{					
		SetDisplayedOSD(INPUTINFO);
		DisplayInput();
		displayhold_flag=3;	

	  if( ReadEEP(EEP_GAUGEMode)==0 && ReadEEP(EEP_RearMode)==0&&(TriggerMode==REVERSE_TRIG))
  	  DisplayGaugeOSD();
	}
	else if((displayhold_flag==1)&&(Disp_Input==1))//disable input osd
	{
		ClearInput2s();
		displayhold_flag=0;
	}
	
	VlossHandler();
}

		
	
	
//else if ((!(GetDisplayedOSD()&VLOSSINFO)))  //Input=No signal
//{
//VlossHandler();
//}

#else

	//#ifndef QUAD
	#if 1  //Pinchi 20141017 enable for AWT ML072Q
if(displayhold_flag==1&& !(GetDisplayedOSD() & MENU)&&!(GetDisplayedOSD()&TVVOL))
		{
//		if(ReadEEP(EEP_COSDMode)!=0 && displayhold_flag==1 && !(GetDisplayedOSD() & MENU))
//		if( !(GetDisplayedOSD() & MENU)&&ReadEEP(EEP_COSDMode)!=0 )

//	if( ReadEEP(EEP_COSDMode)!=0 )  
	if( Disp_Input!=0 ) 
		{
			//if(!(GetDisplayedOSD()&TVVOL))		//william-v1.0-971203
			{
				//  ShowOSDWindow(INPUTINFO_OSDWIN-1,FALSE);
				//Printf("\r\n[MSG]main_loop() => [Display] OFF to clear Info & SelectModeType=%bx , TriggerFlag=%bx",SelectModeType,TriggerFlag); //pinchi test		        
			#ifdef FIX_DISPLAY_OFF_TRIGGER_ISSUE  //Pinchi 20150908 add
				if (TriggerFlag == 0)
			#endif
				{
					if (SelectModeType == AVMode)	//Pinchi 20141024 modify to display AV 2s
					{
						//ClearInput();
						//ShowOSDWindowAll(0);
						ShowOSDWindow(INPUTINFO_OSDWIN-1,FALSE);
						//ShowOSDWindow(INPUTINFO_OSDWIN,FALSE);
						DisplayedOSD &= (~(INPUTINFO));
					}
					else
					{	//Printf("\r\n[MSG]main_loop() => 2s timeout call SetNowMode()");  //pinchi test
					//=== Pinchi 20141017 enable for AWT ML072Q ===
						Attr_A&=0x0d;  //*** BIT1: Channel OSD  set 0
						Attr_B&=0x0d;
						Attr_C&=0x0d;
						Attr_R&=0x0d;

						SetNowMode();

						Attr_A|=0x02;  //*** BIT1: Channel OSD  set 1
						Attr_B|=0x02;
						Attr_C|=0x02;
						Attr_R|=0x02;
					//==============================================
					}
				}

				displayhold_flag=0;
			}	
		}

		}
	#else
	//	if (ReadEEP(EEP_COSDMode) !=0 )
	//	dPressSelectTime = SystemClock;  //Pinchi 20141014 add for AWT ML072Q
   	//	SetSourceMode(SelectModeType,Attr_A,Attr_B,Attr_C,Attr_R); 
	#endif	
#endif

#ifdef Monitor_debug
#else
CheckAndClearOSD();
#endif

#if 1//ryan@20170906
		//============== Check each input status ===============
		
		switch ( GetInputSelection() ) {

		case CH_TW2835:
	    	case CH_CAMD:
		case CH_AV:		
			//----- Check Decoder ----------------

			if(!( GetDisplayedOSD() & MENU ) )
			{
			//	Printf("\r\n[MSG]main_loop() => call CheckDecoderInput() & GetInputSelection()=%bx",GetInputSelection());  //pinchi test
			
				CheckDecoderInput();

			#ifdef FIRST_RUN_FROM_AC  //Pinchi 20141029 add
				if (IsFirstRunfromAC == 1)
				{
					Printf("\r\n[MSG]main_loop() => call CheckDecoderInput():IsFirstRunfromAC=1 & TriggerFlag=%bx,ReadDecoder(0x0a)=%bx , ReadDecoder(0x66)=%bx",TriggerFlag,ReadDecoder(0x0a), ReadDecoder(0x66));  //pinchi test
					IsFirstRunfromAC = 0;
				}
			#endif
			}

			break;

#ifdef SUPPORT_PC
		case PC:
			//if ( AutoDetect == 0 ) break;
			//----- Check PC input changed -------
			CheckPCinput();
		break;
#endif

		}

#ifdef AWT_ML072S
if(Backlight_TO==1)
{
	SetBacklight();
	Backlight_TO=0;
}
#endif

#ifdef AWT_ML072Q
if(CAM_QUAD_TO==1)
{
	SetBacklight();
		CAM_QUAD_TO=0;
}

if(CAM_QUAD_TO==2)
{
	Panel_Enable();
}
#endif

#if 1
//Check FPCLK
	if(ReadTW88(0xb2)==0)
		{
		WriteTW88(0xfd,0xb0);
		PowerLED(OFF);
		Wait_ms(500);
		PowerLED(ON);
		WriteTW88(0xfd,0x30);
		}
#endif	
		
#ifdef RS485		
	if(CAM_PTZ_RUN_flag&&(P2_4&&P2_5&&P2_6&&P2_7))
	{
		CAM_TxCommand_toRS485(CAM_PTZ_STOP);
		CAM_PTZ_RUN_flag=0;
	}
#endif	

#endif
	}
}

void WaitPowerOn(void)
{
	BYTE ikey,val;
	BYTE VGATrigger=0;
	//BYTE AutoKey, _RemoDataCode;

	while(1) 
	{	
	#ifdef SUPPORT_SDCARD
		ACCPowerControl();
		if(RS2_in!=0 && !(GetDisplayedOSD() & MENU))
			{
			DvrReceivePaser();	
			RS2_in=0;
			}
		
		if(GetDVRStatusflag==1)
			{
			Hs_DvrTxCmdPaser(GetDVRStatus);
			Hs_DvrTxCmdPaser(GetDVRParam);
			Hs_DvrTxCmdPaser(GetDATETIME);
			//Hs_DvrTxCmdPaser(GetDVRVersion);		
			GetDVRStatusflag=0;
			}
	#endif		
		//--------------Check Trigger ---------------------
	#if 0
			SelectBoxHandler();
		if(SelectBoxMode>0)
			{
				LCDPowerON(0);	
				AudioMute(1);
				//DisplayInput();		//william v0.2 20120223

			}
		else
	#endif	
	

		val=CheckTrigger();

		//#ifdef Hs_debug
		//Printf("(val=%02x TriggerMode=%02x)",(WORD)val,(WORD)TriggerMode);
		//#endif
		
		if(val!=0)
		{	
			TriggerHandler(val);
			//DisplayInput();		//william v0.2 20120223
			#ifdef AWT_ML072Q
			if(!(TriggerMode==0x08))
			{
				//Printf("\r\n(**PowerFlag=%02x)",(WORD)PowerFlag);
				LCDPowerON(1);//修正power on時顯示太慢問題
				AudioMute(1);		
			}
			#else
				LCDPowerON(1);//修正power on時顯示太慢問題
				AudioMute(1);		
			
			#endif
		}
		else
		{
			TriggerHandler(val);  //Pinchi 20140922 add for AWT ML072Q
			
				if(TriggerFlag==0)
				{
				PowerOff();
				AudioMute(0);
				}
		//	TriggerHandler(val);  //Pinchi 20140922 move to above for AWT ML072Q	
		}


	#ifdef SUPPORT_SDCARD  //Pinchi 20140918 add
		if(((GetDisplayedOSD() & INPUTINFO)||(GetDisplayedOSD() & GAUGEINFO))&& DVR_Ready==1)
			DisplayDVRStatus();
	#endif
		if( (ikey = GetKey(0)) ) {
			#ifdef POWERKEY
			if( ikey==POWERKEY && CheckTrigger()==0)
			{
				PowerFlag=1;
				WriteEEP(EEP_Powerflag,PowerFlag);//2007.3.28 Justin
				break;		//poweron
			}
			#endif
		}
		#if 0
		if( IsRemoDataReady(&_RemoDataCode, &AutoKey) )	{
			if( _RemoDataCode==REMO_STANDBY && !AutoKey )		//POWERON
				break;		//poweron	
		}
		#endif

		#if (defined AWT_ML072Q)
		if(CAM_QUAD_TO==2)//ryan@20171016
		{	
		//Printf("\r\n(**Power off_ LCD setting)");
		OFF_LVDS();
		//PanelMute(1);
		
		Panel_Enable();
		Wait_ms(16);
		P3_5=1;
		
		//delay(10);

		WriteDecoder(0xd5, 0x09);	// Standby	Panel:1  Signal:0  Back:0
		delay(4);
	
		WriteDecoder(0xd5, 0x0b);	// Suspend	Panel:1  Signal:1  Back:0

		delay(10);
		ON_LVDS();
		
		#ifdef BACKLIGHT_PWM
		WriteDecoder(0xd5, 0x0f);	// On		Panel:1  Signal:1  Back:1
		#endif

		//AudioMute(1);				//WILLIAM-981103
		
		delay(5);
			
		//Wait_ms(50);
		//CAM_QUAD_TO=3;//ryan@20170928
		//SetBacklight();
			
		TW2835Cmd("\n\rbusw 0 1 A1 11\n\r");
		Wait_ms(100);
		TW2835Cmd("\n\rbusw 0 1 A2 D7\n\r");  
		CAM_QUAD_TO=0;
		}
		#endif

		#ifdef AWT_ML072S
		VlossHandler();
		#endif
	}

	#ifdef DEBUG_MAIN
	dPuts("\r\n++(PowerOn)__");
	#endif

////	PowerLED(ON);
////	AudioMute(1);
////	ChangeVol(0);

#if 1  //Pinchi 20150408 add to fix power on keep last trigger stage
	DisplayInput();  //Pinchi 20150408 add
	SetNowMode();

	if (ReadEEP(EEP_COSDMode) == 1)
		displayhold_flag = 3;

  #ifdef AWT_NO_SIGNAL_MSG
	IsDrawNoVideoSignal = 0;
  #endif
#endif

	LCDPowerON(1);//修正power on時顯示太慢問題
	
#ifdef FIX_EXIT_STANDBY_NO_AUDIO  //Pinchi 20150908 add
	AudioMute(1);
#endif
#ifdef FIX_2835_SCREEN_NOISE  //Pinchi 20160929 add
	TW2835Cmd("\n\rbusw 0 1 7E 89\r\n");
#endif
//if(VGATrigger==0)
//	DisplayInput();
}

#ifdef AWT_ML720Q_NEW_TRIGGER_FUN  //Pinchi 20141031 add for AWT request each trigger can work by PRIORITY OFF
//===== bTri_arry[4]={Left , Right , Reverse , CAM C} =====//
void CheckNewTriggerFunc(void)
{
	BYTE i , j , num , val;

	if ((Priority == 0) || ((Priority == 1) && (bTriNumber == 0))) 
	{	
		if (IsTriggerArrEmpty == 0)  //Pinchi 20150210 add
		{
			IsTriggerArrEmpty = 1;  //Pinchi 20150210 add

			for (i=0 ; i < 4 ; i++)
			{
				bTri_arry[i] = 0;
				bTri_backup[i] = 0;  //Pinchi 20150210 add
			}
			bTriOrder = 0;
			bTriNumber = 0;
		}

		return;
	}

	IsTriggerArrEmpty = 0;  //Pinchi 20150210 add

	if (bTriOrder > bTriNumber)  //multi trigger & release one
	{
		num = bTriOrder - bTriNumber;

		for (i=0 ; i < num ; i++)
		{
			for (j=0 ; j < 4 ; j++)
			{				
				if (bTri_arry[j] != bTri_backup[j])
				{
					val = bTri_backup[j];
					bTri_backup[j] = 0;
					break;
				}
			}

			for (j=0 ; j < 4 ; j++)
			{
				if (bTri_arry[j] > val)
				{
					bTri_arry[j] -= 1;
					bTri_backup[j] = bTri_arry[j];
				}
			}
		}

		bTriOrder = bTriNumber;
	}

	num = bTriOrder;
	val = 5;

	for (i=0 ; i < 4 ; i++)
	{	
		if (bTri_arry[i] == num)
		{
			val = i;
		
		#ifdef AWT_ADD_TRIGGER_DELAY_FUN  //Pinchi 20150206 add for AWT request each trigger can setup trigger delay
		   if (num == 1)
		   {
			   bLastTrigger = i+1;
		   }
		#endif

			break;
		}
	}

	delay(1);  //delay to avoid polling trigger to make error

	switch(val)
	{
		case 0:   //Left last trigger
			RtFlag = 0;
			ReverseFlag = 0;
			ParkFlag = 0;
			break;
	
		case 1:   //Right last trigger
			LtFlag = 0;
			ReverseFlag = 0;
			ParkFlag = 0;
			break;
	
		case 2:   //Reverse last trigger
			LtFlag = 0;
			RtFlag = 0;
			ParkFlag = 0;

		//	ShowOSDWindow(INPUTINFO_OSDWIN-1 , FALSE);  //clear T Char    //Pinchi 20150210 disable
			break;
	
		case 3:   //CAM C last trigger
			LtFlag = 0;
			RtFlag = 0;
			ReverseFlag = 0;

			if (CkTMode != PARK_TRIG)  //Pinchi 20150210 add to slove T char no disapper after CAM C release
				TDisplayFlag = 0;  //display T Char
			break;
	
		default :
			LtFlag = 0;
			RtFlag = 0;
			ReverseFlag = 0;
			ParkFlag = 0;
	}
}
#endif



#ifndef __ETC_EEP__
#define __ETC_EEP__


////eeprom.h

//=========================================================================
//	EEPROM structure
//	0x00	BYTE	4	'TW88'
#define	EEP_FWREV_MAJOR			0x04	//BYTE	1	F/W Rev.-major(Hex)	
#define	EEP_FWREV_MINOR			0x05	//BYTE	1	F/W Rev.-minor(Hex)
#define	EEP_DEBUGLEVEL			0x06	//BYTE	1	DebugLevel
//
#define EEP_AUTODETECT			0x07	//BYTE	1	Flag for Input Auto Detect	-0:Auto, 1:NTSC,....
#define EEP_AUTODETECTTYTE		0x08	//BYTE	1	Type of Auto-detect(will be value of register 0x1d)
//			---------------------------------------------------------------
#define EEP_WIDEMODE			0x09	//BYTE	1   Wide Mode

#define EEP_AUTORECOGNITION		0x0a	//BYTE  1	Auto Recognition
#define EEP_VIDEOMODE			0x0b	//BYTE  1   Video Mode

#define EEP_OSDLANG				0x0c	//BYTE  1   OSDLang						// 0

#define EEP_OSDPOSITIONMODE 	0x0d	//BYTE	1	OSD Position Mode
#define EEP_CCD					0x0e	//BYTE	1	Closed Caption-	0: off, 1:on

#define EEP_INPUTSELECTION		0x0f	//BYTE	1	InputSelection

//
#define EEP_PC_CONTRAST			0x10
#define EEP_PC_BRIGHT			0x11

#define EEP_CONTRAST			0x12	//BYTE	1	Contrast 
#define EEP_BRIGHTNESS			0x13	//BYTE	1	Brightness
#define EEP_SATURATION_U		0x14	//BYTE	1	Saturation :U
#define EEP_SATURATION_V		0x15	//BYTE	1	Saturation :V
#define EEP_SHARPNESS			0x16	//BYTE	1	Sharpness 
#define EEP_HUE					0x17	//BYTE	1	Hue                    

//====================================HS AWT 981001
#define  EEP_AutoMode           0xa0
#define  EEP_IMAGEMode          0xa1
#define  EEP_RearMode           0xa2
#define  EEP_COSDMode           0xa3
#define  EEP_GAUGEMode          0xa4
#define  EEP_CAMAMode           0xa5 
#define  EEP_CAMBMode           0xa6
#define  EEP_CAMCMode           0xa7
#define  EEP_CAMRMode           0xa8
#define  EEP_CAMOutMode         0xa9	
#define  EEP_TimeStep           0xaa
#define  EEP_Powerflag          0xab   
#define  EEP_ONOFFChoice        0xac 

#define  EEP_PRIORITY 	        0xad
#define  EEP_JUMPMode           0xae
#define  EEP_NowModeState       0xaf
#define  EEP_SelectMode         0xb0
#define  EEP_PriorityOffSelectMode	0xb1
#define  EEP_AudioRecord		0xb2

#define  EEP_FirstNumber		0xb3
#define  EEP_SecondNumber		0xb4
#define  EEP_ThridNumber		0xb5
#define  EEP_FourthNumber		0xb6

#define  EEP_CAMNUMBER     0xb7
#define	 EEP_PELCO		   0xb8
#define	 EEP_Baud_rate	   0xb9
#define	 EEP_TriggerVGA	   0xba
#define	 EEP_DVRDisplay	   0xbb
#define  EEP_IMAGE_A_Mode    0xbc//andy A1.4 20100113
#define  EEP_IMAGE_B_Mode    0xbd//andy A1.4 20100113
#define  EEP_IMAGE_C_Mode    0xbe//andy A1.4 20100113

#define  EEP_SDCardDetect    0xbf//andy A1.4 20100113

#ifdef HTRV
#define  EEP_Gauge_VStart  0x211   //WILLIAM-970318
static  BYTE GaugeVStart;
#endif

#define  EEP_DELAYCAMA           0xC0 
#define  EEP_DELAYCAMB           0xC1
#define  EEP_DELAYCAMC           0xC2
#define  EEP_DELAYCAMR           0xC3
#ifdef USE_CAMD
#define  EEP_DELAYCAMD           0xC4
#endif
//#define  EEP_SelectModeBuf         0xb2
#define  EEP_ReverseMode		0xc5
#define  EEP_JUMPAV_TIMESET	0xc6
#if 0
#define  EEP_Resolution			0xc0
#define  EEP_FPS				0xc1
#define  EEP_Quality			0xc2
#define  EEP_RecordMode			0xc3
#define  EEP_RecordLength		0xc4
#define  EEP_PreAlarmLength		0xc5
#define  EEP_PostAlarmLength	0xc6
#endif
//====================================HS AWT 981001

#ifdef AWT_ADD_TRIGGER_DELAY_FUN  
#define  EEP_CamADelay 		0x21b
#define  EEP_CamBDelay 		0x21c
#define  EEP_CamCDelay 		0x21d
#define  EEP_CamRDelay 		0x21e
#endif
//====================================
//
//	    	---------------------------------------------------------------
#define EEP_PCAUDIOPVOL		0x37	//BYTE	1   AudioVol
#define EEP_AUDIOPVOL			0x38	//BYTE	1   AudioVol
#define EEP_AUDIOBALANCE		0x39	//BYTE	1   AudioBalance
//
//	    	---------------------------------------------------------------

#define EEP_BLOCKMOVIE 			0x40	//BYTE	1	BlockedMovie:Blocked rating for Movie	
#define EEP_BLOCKTV				0x41	//BYTE	1	BlockedTV:Blocked rating for TV			
#define EEP_FVSLD				0x42	//BYTE  6
//						                7    6       4    3    2    1    0
//  FVSLD Level                        ALL   FV(V)   S    L    D    
//  0x43    BYTE    1   TV-Y            X  
//  0x44	BYTE    1   TV-Y7           X    X 
//  0x45	BYTE    1   TV-G            X 
//  0x46	BYTE    1   TV-PG           X       X    X    X    X
//  0x47	BYTE    1   TV-14           X       X    X    X    X 
//  0x48	BYTE    1   TV-MA           X       X    X    X
//
#define	EEP_VCHIPPASSWORD		0x49	//BYTE	4   OSDPassword					//Defualt:3366
//			---------------------------------------------------------------
//
//
//	0x61	WORD	2   PanelXRes
//	0x63	WORD	2	PanelYRes
//	0x65	BYTE	1	PanelHsyncMinPulseWidth
//	0x66	BYTE	1	PanelVsyncMinPulseWidth
//	0x67	WORD	2	PanelHminBackPorch
//	0x69	BYTE	1	PanelHsyncPolarity
//	0x6a	BYTE	1	PanelVsyncPolarity
//	0x6b	WORD	2	PanelDotClock
//	0x6d	BYTE	1	PanelPixsPerClock
//	0x6e	BYTE	1	PanelDEonly
//			---------------------------------------------------------------
//
//	0x80	PC Data
//
//			---------------------------------------------------------------
//
//	0x300	TV Data
//
//	--- NTSC_TV -------------------------------------------------------------
//	CNT_SAVEDAIR			BYTE	1   Total count of saved Air TV Channel.
//	IDX_CURAIR				BYTE	1   Index of Current Air TV Channel
//	CHN_CURAIR				BYTE    1   Current Air TV Channel.
//
//	FIRSTSAVED_AIRCHN		BYTE    1	First saved Air TV channel no	(maximum 100)
//	....
//
//	CNT_SAVEDCABLE			BYTE	1   Total count of saved Cable TV Channel.
//	IDX_CURCABLE			BYTE	1   Index of Current Cable TV Channel
//	CHN_CURCABLE			BYTE    1   Current Cable TV Channel.
//
//	FIRSTSAVED_CABLECHN		BYTE	1	First saved Cable TV channel no	(maximum 100)
//
//	--- PAL_TV --------------------------------------------------------------
//	PR_CUR					BYTE	1   Current PR no.
//	FIRST_SAVEDPR			DWORD	4   Freq of PR0.	(TOTAL_PR)
//	FIRST_SAVEDPR+4			DWORD   4   Freq of PR1.
//	.....
//



//
// Offset of EEPROM
//
/*
#define VIDEOCONTRAST		0x18		// for NTSC.(PAL:0x20,SECAM:0x28)
#define VIDEOBRIGHTNESS		0x19
#define VIDEOSATURATION_U	0x1a
#define VIDEOSATURATION_V	0x1b
#define VIDEOHUE			0x1c		// only for NTSC
#define VIDEOSHARPNESS		0x1d
*/
#define CCCOLOR		0x52
#define VOLZOOM		0x53

#define PANELINFO	0x61

// PAL_TV
#define  PR_CUR					0x301	
#define  FIRST_SAVEDPR			0x308	
 #define TVFREQ_HIGH 0 
 #define TVFREQ_LOW  1
#ifdef PAL_TV
 #define TVFINETUNE  2
		// NOT Finetune: 0 , Range: -32 ~ +32
 #define TVPRSYSTEM  3	
		// bit 7: Add:1 Ereased :0
		// 
 #define TVCHNAME    4

 #define BYTEPERCHANNEL 9 
#endif
// NTSC_TV
#define  EEP_TVInputSel			0x302
#define  CHN_CURAIR				0x303	
#define  FIRSTSAVED_AIRCHN		0x308	
#define  CHN_CURCABLE			0x403	
#define  FIRSTSAVED_CABLECHN	0x408	
#ifdef NTSC_TV
 #define TVFINETUNE  0
		// NOT Finetune: 0 , Range: -32 ~ +32
 #define TVPRSYSTEM  1	
		// bit 7: Add:1 Ereased :0
		// 
 #define BYTEPERCHANNEL 2
#endif




WORD GetFWRevEE(void);
void SaveFWRevEE(WORD);

BYTE GetDebugLevelEE(void);
void SaveDebugLevelEE(BYTE);

#ifdef WIDE_SCREEN
BYTE GetWideModeEE(void);
void SaveWideModeEE(BYTE dl);
#endif


//BYTE GetRange4CoarseEE(void);
//void SaveRange4CoarseEE(BYTE);

BYTE GetPossibleAutoDetectStdEE(void);
void SetPossibleAutoDetectStdEE(void);

//BYTE GetOSDXPositionEE(void);
//BYTE GetOSDYPositionEE(void);
BYTE GetClosedCaptionFlagEE(void);

BYTE GetVideoDatafromEE(BYTE);
void SaveVideoDatatoEE(BYTE offset, BYTE ndata);

//BYTE GetVideoBrightnessEE(void);
//BYTE GetVideoSaturationEE(BYTE);
//BYTE GetVideoHueEE(void);
//BYTE GetVideoSharpnessEE(void);

//void SaveVideoContrastEE(BYTE ndata);
//void SaveVideoBrightnessEE(BYTE ndata);
//void SaveVideoSaturationEE(BYTE, BYTE ndata);
//void SaveVideoHueEE(BYTE ndata);
//void SaveVideoSharpnessEE(BYTE ndata);

BYTE GetOSDPositionModeEE(void);
void SaveOSDPositionModeEE(BYTE ndata);
//void SaveOSDXPositionEE(BYTE);
//void SaveOSDYPositionEE(BYTE);

void SaveClosedCaptionFlagEE(BYTE);

BYTE GetBlockedTVEE(void);			
void SaveBlockedTVEE(BYTE vi);		
BYTE GetBlockedTV_FLDSLEE( BYTE level )	;
void SaveBlockedTV_FLDSLEE(BYTE level, BYTE vi)	;

BYTE GetBlockedMovieEE(void);		
void SaveBlockedMovieEE(BYTE vi);	
#if 0
BYTE GetInputSelectionEE(void);
#endif
void SaveInputSelectionEE(BYTE val);

//BYTE GetOSDDurationEE(void);
//void SaveOSDDurationEE(BYTE val);

BYTE GetOSDLangEE(void);
void SaveOSDLangEE(BYTE val);

//ljy100303...BYTE GetOSDZoomEE(void);
//ljy100303...void SaveOSDZoomEE(BYTE val);

BYTE GetAudioVolEE(void);
void SetAudioVolEE( BYTE vol );
BYTE GetPCAudioVolEE(void);
void SetPCAudioVolEE( BYTE vol );
#if 0
BYTE GetAudioBalanceEE(void);
void SetAudioBalanceEE( BYTE vol );
BYTE GetAudioBassEE(void);
void SetAudioBassEE( BYTE vol );
BYTE GetAudioTrebleEE(void);
void SetAudioTrebleEE( BYTE vol );
#endif
//BYTE GetAudioEffectEE(void);
//void SetAudioEffectEE( BYTE vol );

void ClearBasicEE(void);

BYTE ValidPassword(DATA_P BYTE *numstr, BYTE index);
BYTE SetNewPassword(DATA_P BYTE *numstr, BYTE index);

//WORD GetPanelXRes(void);
//WORD GetPanelYRes(void);
BYTE GetPanelHsyncMinPulseWidth(void);
BYTE GetPanelVsyncMinPulseWidth(void);
WORD GetPanelHMinBackPorch(void);
BYTE GetPanelHsyncPolarity(void);
BYTE GetPanelVsyncPolarity(void);
WORD GetPanelDotClock(void);
WORD GetPanelMaxClock(void);
BYTE GetPanelPixsPerClock(void);
// Not used yet *************************  BYTE GetPanelDEonly(void);

void AddTVChannelEE( BYTE tvtype, BYTE chn);
BYTE GetTVChannelEE( BYTE tvtype, BYTE inx);
void ResetTVChannelEE( BYTE tvtype );
BYTE GetTVChannelCntEE(BYTE tvtype);
BYTE GetTVChnIdxEE(BYTE tvtype);
BYTE GetCurTVChannelEE(BYTE tvtype);
void SetTVChnIdxEE(BYTE tvtype, BYTE newd);
void SetCurTVChannelEE(BYTE tvtype, BYTE newd);
BYTE InsertTVChannelEE(BYTE tvtype, BYTE newd);
BYTE RemoveTVChannelEE(BYTE tvtype, BYTE newd);

void SetTVPrEE(void);
BYTE GetTVPrEE(void);
void SetTVFreqEE(BYTE, WORD);
WORD GetTVFreqEE(BYTE);
void SetFineTuneEE(BYTE, BYTE);
BYTE GetFineTuneEE(BYTE);
BYTE GetTVPrSystem(BYTE);
void SetTVPrSystem(BYTE, BYTE);
BYTE GetTVInputSelEE(void);
void SetTVInputSelEE(BYTE);

#define GetVInputStdDetectModeEE()				ReadEEP(EEP_AUTODETECTTYTE)
#define SaveVInputStdDetectModeEE(A)			WriteEEP(EEP_AUTODETECTTYTE, A)

#define GetAutoRecogntionEE()					ReadEEP(EEP_AUTORECOGNITION)
#define SaveAutoRecogntionEE(A)					WriteEEP(EEP_AUTORECOGNITION, A)

#define	SetVideoModeEE( ctid )					WriteEEP( EEP_VIDEOMODE, ctid )
#define	GetVideoModeEE()						ReadEEP( EEP_VIDEOMODE )

#define GetPanelContrastEE()					ReadEEP(0x10)

#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
//#define GetPanelHueEE()							ReadEEP(0x28)
//#define GetPanelSharpnessEE()					ReadEEP(0x29)
#define GetPanelBrightnessEE()					ReadEEP(0x11)
//#define GetPanelSaturationEE()					ReadEEP(0x2a)

//#define SavePanelHueEE(A)						WriteEEP(0x28, A)
//#define SavePanelSharpnessEE(A)					WriteEEP(0x29, A)
#define SavePanelContrastEE(A)					WriteEEP(0x10, A)
#define SavePanelBrightnessEE(A)				WriteEEP(0x11, A)
//#define SavePanelSaturationEE(A)				WriteEEP(0x2a, A)
#endif

/*
#define GetDigitalVideoContrastEE()				ReadEEP(0x2b)
#define GetDigitalVideoBrightnessEE()			ReadEEP(0x2c)
#define GetDigitalVideoHueEE()					ReadEEP(0x2d)
#define GetDigitalVideoSaturationEE(off)		ReadEEP(0x2e+off)

#define SaveDigitalVideoContrastEE(A)			WriteEEP(0x2b, A)
#define SaveDigitalVideoBrightnessEE(A)			WriteEEP(0x2c, A)
#define SaveDigitalVideoHueEE(A)				WriteEEP(0x2d, A)
#define SaveDigitalVideoSaturationEE(off,A)		WriteEEP(0x2e+off, A)
*/

#endif	// __ETC_EEP__

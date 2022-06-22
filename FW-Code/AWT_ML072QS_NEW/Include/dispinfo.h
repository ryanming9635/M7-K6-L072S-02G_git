#ifndef __DISPINFO__
#define __DISPINFO__
//==================================================================
//				Display Information
//==================================================================
#if (defined WQVGA) && (defined ANALOG_7INCH)
#define		INPUTINFO_ZOOM		WINZOOMx1
#define		LOGO_ZOOM			WINZOOMx3

#else // (defined WQVGA) && (defined SHARP_LQ043T3DX02)

	#ifdef AWT_ML072S
	#define		INPUTINFO_ZOOM		WINZOOMx4
	#else
	#define		INPUTINFO_ZOOM		WINZOOMx2
	#endif
#define		LOGO_ZOOM			WINZOOMx2
#endif
//#define		VOL_ZOOM			WINZOOMx4
#define		MUTE_ZOOM			WINZOOMx3
#define		TVCHN_ZOOM			WINZOOMx4
#define		RATINGINFO_ZOOM		WINZOOMx3
#define     SCANTV_ZOOM			WINZOOMx2		//ljy012304
#define		PCINFO_ZOOM			WINZOOMx2
#define     BAR_ZOOM			WINZOOMx2


#define DVRStatus_OSDWIN	4 
#define DVRStatus_ADDR	180

extern  BYTE  DisplayedOSD;


void ClearDisplayedOSD( BYTE newd );
void SetDisplayedOSD( BYTE newd );
BYTE GetDisplayedOSD(void);
void ClearOSDInfo(void);

void DisplayInput(void);
BYTE ClearInput(void);
BYTE ClearInput2s(void);

//void DisplayLogo(void);

void ClearLogo(void);

void DisplayPCInfo(BYTE CODE *ptr);
void ClearPCInfo(void);
void DisplayAutoAdjust(void);
void ClearAutoAdjust(void);


void DisplayVol(void);
#if 0
void DisplayBrightness(void);
#endif
#if 0
void DisplayMuteInfo(void);
#endif
void ClearMuteInfo(void);
BYTE CheckAndClearOSD(void);
BYTE ClearVlossOsd(void);
#ifdef AWT_ML072S
void VlossHandler(void);
void Check_Vloss(void);
#endif
//==================================================================
//						TV Info
//==================================================================

BYTE ClearTVInfo(void);

#endif	// __DISPINFO__

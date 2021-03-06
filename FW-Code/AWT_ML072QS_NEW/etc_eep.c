//eeprom.c
#include "Config.h"

#include "typedefs.h"
#include "main.h"
#include "i2c.h"
#include "debug.h"
#include "printf.h"
#include "TW88.h"
#include "etc_eep.h"
#include "osdbasic.h"
#include "osdmenu.h"
#include "audio.h"
//-----------------------------------------------------------------------------

//extern BYTE GaugeVStart;

extern BYTE  InputSelection;
//extern 			BYTE	TVChannel, DummyChannel;
//extern  		BYTE	TVInputSel;

//=============================================================================
WORD GetFWRevEE()
{
	WORD	rev;

	if( ReadEEP(0) != 'T' ) return 0;
	if( ReadEEP(1) != 'W' ) return 0;
	if( ReadEEP(2) != '8' ) return 0;
	if( ReadEEP(3) != '8' ) return 0;

	rev = ReadEEP(EEP_FWREV_MAJOR) << 8;
	rev |= ReadEEP(EEP_FWREV_MINOR);

	return rev;
}

void SaveFWRevEE(WORD rev)
{
	WriteEEP(0, 'T');
	WriteEEP(1, 'W');
	WriteEEP(2, '8');
	WriteEEP(3, '8');

	WriteEEP(EEP_FWREV_MAJOR, (BYTE)(rev>>8) );
	WriteEEP(EEP_FWREV_MINOR, (BYTE)rev );
}

BYTE GetDebugLevelEE(void)
{
	return ReadEEP(EEP_DEBUGLEVEL);
}

void SaveDebugLevelEE(BYTE dl)
{
	WriteEEP(EEP_DEBUGLEVEL, dl);
	//delay(1);			
}

#ifdef WIDE_SCREEN
BYTE GetWideModeEE(void)
{
	return ReadEEP(EEP_WIDEMODE);
}

void SaveWideModeEE(BYTE dl)
{
	WriteEEP(EEP_WIDEMODE, dl);
	//delay(1);			
}
#endif

BYTE GetPossibleAutoDetectStdEE(void)
{
	BYTE val;

	val = GetAutoRecogntionEE();

	#ifdef DEBUG_EEP
	dPrintf("\r\nGetPossibleAutoDetectStdEE:0x%02x", (WORD)val);
	#endif

	return val;
}

void SetPossibleAutoDetectStdEE()
{
	BYTE	i, val=0;
	extern  CODE struct struct_IdName struct_VInputStd[];

	for(i=0; ; i++) {
		switch(struct_VInputStd[i].Id) {
		case 0:				{	// end of list
							SaveAutoRecogntionEE(val);

							#ifdef DEBUG_EEP
							dPrintf("\r\nSetPossibleAutoDetectStdEE:0x%02x", (WORD)val);
							#endif
							return;		
							}
		case NTSC:			val |= 0x01;	break;
		case PAL:			val |= 0x02;	break;
		case SECAM:			val |= 0x04;	break;
		case NTSC4:			val |= 0x08;	break;
		case PALM:			val |= 0x10;	break;
		case PALN:			val |= 0x20;	break;
		case PAL60:			val |= 0x40;	break;
		default:			break;
		}
	}
}

//=============================================================================
//
//=============================================================================
#ifdef SUPPORT_OSDPOSITIONMOVE
BYTE GetOSDPositionModeEE(void)
{
	BYTE val;

	val = ReadEEP(EEP_OSDPOSITIONMODE);

	return val;
}

void SaveOSDPositionModeEE(BYTE ndata)
{

	WriteEEP(EEP_OSDPOSITIONMODE, ndata);
}

#endif // SUPPORT_OSDPOSITIONMOVE


#define TOT_VIDEO	6
BYTE GetVideoDatafromEE(BYTE offset)
{
	BYTE val;

	#ifdef TW8816
	val = ReadEEP(EEP_CONTRAST+/*(InputSelection-1)*/0*TOT_VIDEO + offset);
	#else
	val = ReadEEP(EEP_CONTRAST+(InputSelection-1)*TOT_VIDEO + offset);
	#endif
	return val;
}

void SaveVideoDatatoEE(BYTE offset, BYTE ndata)
{
	BYTE tot;

	#ifdef TW8816
	tot=EEP_CONTRAST+ /*(InputSelection-1)*/0*TOT_VIDEO+offset;
	#else
	tot=EEP_CONTRAST+ (InputSelection-1)*TOT_VIDEO+offset;
	#endif
	WriteEEP(tot, ndata);

}
void SaveInputSelectionEE(BYTE val)
{
	WriteEEP(EEP_INPUTSELECTION, val);
}

/*
#ifndef TW8803

BYTE GetOSDDurationEE(void)
{
	BYTE val;

	val = ReadEEP(0x30);
	
	#ifdef DEBUG_EEP
	dPrintf("\r\nGetOSDUuration:%02x", (WORD)val);
	#endif

	return val;
}

void SaveOSDDurationEE(BYTE val)
{
	WriteEEP(0x30, val);
}
*/
BYTE GetOSDLangEE(void)
{
	BYTE val;

	val = ReadEEP(EEP_OSDLANG);
	
	#ifdef DEBUG_EEP
	dPrintf("\r\nGetOSDLang:%02x", (WORD)val);
	#endif

	return val;
}

void SaveOSDLangEE(BYTE val)
{
	WriteEEP(EEP_OSDLANG, val);
}

/*ljy100303
BYTE GetOSDZoomEE(void)
{
	BYTE val;

	val = ReadEEP(OSDZOOM);

	#ifdef DEBUG_EEP
	dPrintf("\r\nGetOSDZoom:%02x", (WORD)val);
	#endif

	return val;
}

void SaveOSDZoomEE(BYTE val)
{
	WriteEEP(OSDZOOM, val);
}
*/


//=========  Audio =================================================
BYTE GetAudioVolEE(void)
{
	return ReadEEP( EEP_AUDIOPVOL );
}

void SetAudioVolEE( BYTE vol )
{
	WriteEEP( EEP_AUDIOPVOL, vol );
}

BYTE GetPCAudioVolEE(void)
{
	return ReadEEP( EEP_PCAUDIOPVOL );
}
void SetPCAudioVolEE( BYTE vol )
{
	WriteEEP( EEP_PCAUDIOPVOL, vol );
}
#if 0
BYTE GetAudioBalanceEE(void)
{
	return ReadEEP( 0x39 );
}

void SetAudioBalanceEE( BYTE vol )
{
	WriteEEP( 0x39, vol );
}

BYTE GetAudioBassEE(void)
{
	return ReadEEP( 0x3a );
}

void SetAudioBassEE( BYTE vol )
{
	WriteEEP( 0x3a, vol );
}

BYTE GetAudioTrebleEE(void)
{
	return ReadEEP( 0x3b );
}

void SetAudioTrebleEE( BYTE vol )
{
	WriteEEP( 0x3b, vol );
}
#endif
/*
BYTE GetAudioEffectEE(void)
{
	return ReadEEP( 0x3c );
}

void SetAudioEffectEE( BYTE vol )
{
	WriteEEP( 0x3c, vol );
}
*/


//===================================================================
/*#include "panel.h"
void SavePanelInfoEE(void)
{
	WriteEEP( PANELINFO+0 , (BYTE)PanelConfig.x_res );
	WriteEEP( PANELINFO+1 , (BYTE)(PanelConfig.x_res >> 8) );

	WriteEEP( PANELINFO+2 , (BYTE)PanelConfig.y_res );
	WriteEEP( PANELINFO+3 , (BYTE)(PanelConfig.y_res >> 8) );

	WriteEEP( PANELINFO+4 , PanelConfig.h_sync_min_pulse_width );

	WriteEEP( PANELINFO+5 , PanelConfig.v_sync_min_pulse_width );

	WriteEEP( PANELINFO+6 , (BYTE)PanelConfig.h_min_back_porch );
	WriteEEP( PANELINFO+7 , (BYTE)(PanelConfig.h_min_back_porch >> 8 ) );

	WriteEEP( PANELINFO+8 , PanelConfig.h_sync_polarity );

	WriteEEP( PANELINFO+9 , PanelConfig.v_sync_polarity );

	WriteEEP( PANELINFO+0x0a , (BYTE)PanelConfig.dot_clock );
	WriteEEP( PANELINFO+0x0b , (BYTE)(PanelConfig.dot_clock >> 8 ) );

	WriteEEP( PANELINFO+0x0c , (BYTE)PanelConfig.max_clock );
	WriteEEP( PANELINFO+0x0d , (BYTE)(PanelConfig.max_clock >> 8 ) );

	WriteEEP( PANELINFO+0x0e , PanelConfig.pixs_per_clock );

	WriteEEP( PANELINFO+0x0f , PanelConfig.DE_only );
}


#if (defined SERIAL) || (defined SUPPORT_PATTERN) || (defined WIDE_SCREEN)
WORD GetPanelXRes(void)
{
	WORD res;

	res = ReadEEP( PANELINFO+1 );
	res = (res <<8 ) | ReadEEP( PANELINFO+0 );
	return res;
}

WORD GetPanelYRes(void)
{
	WORD res;

	res = ReadEEP( PANELINFO+3 );
	res = (res <<8 ) | ReadEEP( PANELINFO+2 );
	return res;
}
#endif//  (defined SUPPORT_PATTERN) || (defined WIDE_SCREEN)
*/

/****
#if (defined SERIAL) || (defined WIDE_SCREEN)
BYTE GetPanelHsyncMinPulseWidth(void)
{
	return ReadEEP( PANELINFO+4 );
}

BYTE GetPanelVsyncMinPulseWidth(void)
{
	return ReadEEP( PANELINFO+5 );
}

WORD GetPanelHMinBackPorch(void)
{
	WORD res;

	res = ReadEEP( PANELINFO+7 );
	res = (res <<8 ) | ReadEEP( PANELINFO+6 );
	return res;
}

BYTE GetPanelHsyncPolarity(void)
{
	return ReadEEP( PANELINFO+8 );
}

BYTE GetPanelVsyncPolarity(void)
{
	return ReadEEP( PANELINFO+9 );
}

WORD GetPanelDotClock(void)
{
	WORD res;

	res = ReadEEP( PANELINFO+0x0b );
	res = (res <<8 ) | ReadEEP( PANELINFO+0x0a );
	return res;
}
#endif // WIDE_SCREEN

WORD GetPanelMaxClock(void)
{
	WORD res;

	res = ReadEEP( PANELINFO+0x0d );
	res = (res <<8 ) | ReadEEP( PANELINFO+0x0c );
	return res;
}

BYTE GetPanelPixsPerClock(void)
{
	return ReadEEP( PANELINFO+0x0e );
}
***/

/* Not used yet *************************
BYTE GetPanelDEonly(void)
{
	return ReadEEP( PANELINFO+0x0f );
}
*/

//===================================================================

void ClearBasicEE(void)
{
	WriteEEP(EEP_PRIORITY,0x00);	//PRIORITY.........OFF	Andy-980602
	Priority=0;

	SaveVInputStdDetectModeEE(0);	// AUTO
	WriteEEP(EEP_CCD, 0);	// CC = OFF

#ifdef HTRV  //Pinchi 20140902 add for AWT ML072Q
    WriteEEP(EEP_Gauge_VStart,0x0C); 	                          //WILLIAM-V1.43-970410
    GaugeVStart= ReadEEP(EEP_Gauge_VStart);                 //WILLIAM-V1.43-970410
#endif

	ResetOSDValue();  //Pinchi 20150212 enable
	//SavePanelInfoEE();
	//ResetAudioValue();

	ResetVideoValue();

	#ifdef WIDE_SCREEN
	Set4WideScreen(WIDESCREEN_WIDE);
	#endif
}



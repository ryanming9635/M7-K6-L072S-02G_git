//pc_eep.c
//=========================================================================
//	EEPROM structure

//	0x80	----------- PC Color Temp Data --------------------------------
//			0	PC Color Temp Mode
//			1	R G B for Mode 1
//			4	R G B for Mode 2
//			7   R G B for Mode 3
//			A	R G B for User Mode
//
//	0x90	----------- PC Input ------------------------------------------
//
//			0	ADC Coarse
//			1	ADC Phase
//			2	Vertical Active Start
//			3	Horizontal Active Start
//

#include "Config.h"

#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )

#include "typedefs.h"
#include "main.h"
#include "i2c.h"
#include "debug.h"
#include "pc_eep.h"
#include "printf.h"
#include "TW88.h"
#include "measure.h"
#include "adc.h"
#include "osdmenu.h"
#include "etc_eep.h"
#include "panel.h"

extern  CODE struct _PCMDATA  PCMDATA[];

extern  BYTE  PcMode, PcModeLast;
extern	IDATA WORD  IVF;
extern	IDATA DWORD	IHF;

///extern	IDATA BYTE	CurrentADC;

WORD GetVactiveStartEE(BYTE mode)
{
	WORD index;
	WORD start;

	index = EE_PCDATA + mode*LEN_PCDATA + 2;
	start = PCMDATA[mode].Vstart + (char)ReadEEP(index);

	return start;
}

WORD GetHactiveStartEE(BYTE mode)
{
	WORD index;
	WORD start;

	index = EE_PCDATA + mode*LEN_PCDATA + 4;
	start = PCMDATA[mode].Hstart + (char)ReadEEP(index);

	return start;
}

//-----------------------------------------------------------------------------
//			Get PC Function Data from EEPROM
//-----------------------------------------------------------------------------
void GetPCDataEE(BYTE mode)
{
	char dat=0;			// must be signed char
	WORD index, temp;
	DWORD scale, pres;
	extern bit Flag4Bypass;
	WORD hstart, vstart;

	#ifdef DEBUG_EEP
	dPrintf("\r\nGetPCDataEE(%d)", (WORD)mode);
	#endif

	GetADCGainOffsetEE();		// restore from

	vstart = PCMDATA[mode].Vstart;
	hstart = PCMDATA[mode].Hstart;

	index = EE_PCDATA + mode*LEN_PCDATA;

	//--------------------------------------------

	// PPF
	ChangeInternPLL(PCMDATA[mode].PPF * 100000L);
	delay(5);

	GetHpnVpn(1);	// For correcting sync polarity

	// ADC VCO
	SetVCORange( PCMDATA[mode].IPF * 100000L );

	// ADC PLL-----(0)

	if( !IsDTVInput() ) dat = ReadEEP(index++);

//	if(GetInputSelection()==PC) WriteADC(0xc1, 0x30);

	SetCoarse( dat + PCMDATA[mode].CLOCK );
	Printf("\r\n CLOCK divider adjustment value: %d", (int) dat );

	if(GetInputSelection()==PC) WriteADC(0xc1, 0x20);

	// ADC Phase---(1)
	dat = ReadEEP(index++);
	if( !IsDTVInput() ) 
	SetPhase( dat );

	// Vertical----(2)
	#ifdef DEBUG_PC
	dPrintf("\r\n  vstart(before add ReadEEP): %d", (WORD)vstart);
	#endif
	if( !IsDTVInput() ) 
	vstart += (char)ReadEEP(index++);
	#ifdef DEBUG_PC
	dPrintf("\r\n  vstart(after add ReadEEP): %d", (WORD)vstart);
	#endif
	
	SetVactiveStart( vstart );
	if( IsDTVInput() ) {
		SetVactiveLen( PCMDATA[mode].VAN+20 );
	}
	else
	{
		//SetVactiveLen( PCMDATA[mode].VAN + 6 );
		#ifdef XGA
		if (mode == EE_VGA_72)
			SetVactiveLen(PCMDATA[mode].VAN + 1);
		else
			SetVactiveLen(PCMDATA[mode].VAN);	
		#else
		SetVactiveLen(PCMDATA[mode].VAN);
		#endif
	}
	pres=(DWORD)PVR_;
	#ifdef XGA
	if (PCMDATA[mode].VAN == PVR_)
		scale = (PCMDATA[mode].VAN * 0x10000L) / pres + 0x64;
	else
		scale = (PCMDATA[mode].VAN * 0x10000L) / pres;
	#else
	scale = (PCMDATA[mode].VAN * 0x10000L) / pres;
	#endif 
	
	if( scale==0x10000 && Flag4Bypass ) 		// Bypass
		BypassZoom();
	else {
		Clear_bypass();
		YScale2(scale);						// save V Scale Up Factor
	}

	SetVValueForPanel(vstart);			// Vstart

	dat=0;
	// VBackPorch--(3)
	if( !IsDTVInput() ) 
	dat = (char)ReadEEP(index++);
	dat += PCMDATA[mode].VBack;
	dat -= ReadTW88(0xb8);				// VOsync value compensation
	#ifdef DEBUG_PC
	dPrintf("\r\nSetVBackPorch( %d )", (WORD)dat);
	#endif
	#ifdef XGA
	if (mode ==  EE_SVGA_56)
		dat += 2;
	else if (mode ==  EE_VGA_72)
		dat --;
	#endif
	SetVBackPorch( dat );

	// Horizontal--(4)
	if( !IsDTVInput() ) 
		hstart += (char)ReadEEP(index++);
//	temp = hstart + PCMDATA[mode].HAN + 2;
	temp = hstart + PCMDATA[mode].HAN + 20;
	#ifdef XGA
	if (mode >= EE_SVGA_56 && mode <= EE_SVGA_85)
		hstart += 1;
	SetHactiveStart( hstart );
	#else
	SetHactiveStart( hstart );
	#endif 

	//#ifdef SXGA
	//if( mode>=EE_XGA_60 && mode <=EE_XGA_85 ) temp--;
	//#endif

	if( IsDTVInput() ) temp += 3;

	SetHactiveEnd( temp );
	SetHValueForPanel();

	if( (PCMDATA[mode].VAN != GetPVR()) || !Flag4Bypass) {
		pres = GetPHR();
		scale = (PCMDATA[mode].HAN * 0x10000L + pres/2) / pres;	// 256*han/phr

		#ifdef DEBUG_EEP
		dPrintf("\r\nXscaleFactor:%04x(%d)", scale, scale);
		#endif
		#ifdef XGA
		if( PCMDATA[mode].HAN == 1024 ) {//1100
			scale = (PCMDATA[mode].HAN * 0x80L ) / 1024 + 1;		// (HAN/1024)*256
			XscaleD(scale);
			scale = ((PCMDATA[mode].HAN -4) * 0x10000L ) / 1024;						// (1024/PHR)*256
			XscaleU(scale);
		}
		else if( PCMDATA[mode].HAN > 1024 )
		{
			scale = (PCMDATA[mode].HAN * 0x80L ) / 1024 + 1;		// (HAN/1024)*256
			XscaleD(scale);
			scale = (1024 * 0x10000L ) / 1024;						// (1024/PHR)*256
			XscaleU(scale);
		}
		#else
		//#if (defined SXGA) || (defined WXGA)
		if( PCMDATA[mode].HAN > 1024 ) {
			scale = (PCMDATA[mode].HAN * 0x80L ) / 1024 + 1;		// (HAN/1024)*256
			XscaleD(scale);
	
			#ifdef DEBUG_EEP
			dPrintf("\r\nXscaleFactorD:%04x(%d)", scale, scale);
			#endif

			scale = (1024 * 0x10000L ) / 1280;						// (1024/PHR)*256
			XscaleU(scale);

			#ifdef DEBUG_EEP
			dPrintf("\r\nXscaleFactorU:%04x(%d)", scale, scale);
			#endif
		}
		#endif
		else
		//#endif

		XScale2(scale);

	}

	dPuts("\r\n +++++++++++++++++=>Auto PHP Enable");
		WriteTW88( 0xb6, (ReadTW88(0xb6) & 0x7f) );	// Auto PHP Enable
		WriteTW88( 0xb2, ReadTW88(0xb2) );

	DisplayResultAndSetActiveRange();

	//-------- Clear changed status -------------
	MeasureAndWait(3);

	#ifdef WIDE_SCREEN
	Set4WideScreen(GetWideModeEE());
	#endif

	WriteTW88( 0x06, 0x80 ); // Software Reset

}
//=============================================================================
//			Save PC Function Data to EEPROM
//=============================================================================

void SavePCDataEE(BYTE mode)
{
	WORD index;
	int clockDiff;

	index = EE_PCDATA + mode*LEN_PCDATA ;

	clockDiff = GetCoarse() - PCMDATA[mode].CLOCK;
	#ifdef DEBUG_EEP
	dPrintf("\r\nSave PC DATA mode(%d) index(%04x) IHF(%ld)", (WORD)mode, (WORD)index, IHF );
	dPrintf(" IVF(%d) PPF(%dM)", IVF, (WORD)(GetPPF()/1000000) ); 
	dPrintf("\r\nGestCoarse(): %d, PCMDATA[mode].CLOCK: %d, difference: %d", GetCoarse(), PCMDATA[mode].CLOCK, clockDiff );
	#endif

	WriteEEP( index++, (char) clockDiff );
	WriteEEP( index++,         GetPhaseCurrent() );
	WriteEEP( index++, (char)( GetVactiveStart() - PCMDATA[mode].Vstart) );
	WriteEEP( index++, (char)( ReadTW88(0xb8) + GetVBackPorch()  - PCMDATA[mode].VBack) );	//VOsync compensation
	WriteEEP( index++, (char)( GetHactiveStart() - PCMDATA[mode].Hstart) );
}

//=============================================================================
void SaveDefaultPCDataEE(void)
{
	WORD	index, i;

	index = EE_PCDATA + PcMode*LEN_PCDATA;

	for(i=0; i<LEN_PCDATA; i++) {
		WriteEEP( index++, 0 );
		delay(1);
	}
}

void SaveDefaultPCDataAllEE(void)
{
	for(PcMode=0; PcMode<EE_PC_MAX; PcMode++)
		SaveDefaultPCDataEE();
}

void SaveCoarseEE(BYTE mode)
{
	WORD	index;

	index = EE_PCDATA + mode*LEN_PCDATA + 0;
	WriteEEP( index, (char)(GetCoarse() - PCMDATA[mode].CLOCK) );
}

void SavePhaseEE(BYTE mode)
{
	WORD	index;

	index = EE_PCDATA + mode*LEN_PCDATA + 1;
	WriteEEP( index,        GetPhaseCurrent() );
}

//=============================================================================

void SaveVactiveEE(BYTE mode)
{
	WORD	index;

	index = EE_PCDATA + mode*LEN_PCDATA + 2;
	WriteEEP( index, (char)(GetVactiveStart() - PCMDATA[mode].Vstart) );
}

void SaveVBackPorchEE(BYTE mode)
{
	WORD	index;

	index = EE_PCDATA + mode*LEN_PCDATA + 3;
	WriteEEP( index, (char)(GetVBackPorch() - PCMDATA[mode].VBack) );

}

void SaveHactiveEE(BYTE mode)
{
	WORD	index;

	index = EE_PCDATA + mode*LEN_PCDATA + 4;
	WriteEEP( index, (char)(GetHactiveStart() - PCMDATA[mode].Hstart) );
}

//-----------------------------------------------------------------------------
//		Save ADC Gain & Offset	mod=0 default value, mod=1 current value
//-----------------------------------------------------------------------------
void SaveADCGainOffsetEE(BYTE mod)
{
	BYTE i, dat;
	WORD index;

	index = EE_ADC_GO;

	for(i=0; i<4; i++) {
		if( mod==0 ) dat = 0x80;
		else		 dat = ReadADC(i+0xd0);		// 0x1d0, 0x1d1, 0x1d2, 0x1d3
		WriteEEP(index+i, dat);
	}
}

void GetADCGainOffsetEE(void)
{
	BYTE i, dat;
	WORD index;

	index = EE_ADC_GO;

	for(i=0; i<4; i++) {
		dat = ReadEEP(index+i);
		WriteADC(i+0xd0, dat);
	}
}

#endif // SUPPORT_PC


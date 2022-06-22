#include "Config.h"

#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )

#include "typedefs.h"

#include "main.h"
#include "tw88.h"
#include "measure.h"
#include "adc.h"
#include "i2c.h"
#include "debug.h"
#include "dispinfo.h"
#include "pc_eep.h"
#include "etc_eep.h"
#include "printf.h"
#include "osdmenu.h"
#include "RegMap.h"
#include "panel.h"
#ifdef REFERENCE
#else //REFERENCE
#include "stdlib.h"
#endif //REFERENCE
//================== Input Measurement ====================================
#ifdef REFERENCE
#else // REFERENCE
static WORD  LastHPN=0;
BYTE cLastSyncLoss= 0;
#endif // REFERENCE
static WORD  LastVPN=0;
static DWORD LastIHF=0;
static WORD  LastIVF=0;
BYTE InputDetection;
BYTE	VPosMax, VPosCurr, HPosMax, HPosCurr;

DWORD 	RGBPeak, PhaseRGB, RGBMin;

#ifdef WIDE_SCREEN
extern BYTE WideScreenMode;
#endif //WIDE_SCREEN

CODE BYTE PcModeStr[][15] = {
    "720x400 70Hz",	// 0

    "640x400 80Hz",	// 1
    "640x350 85Hz",	// 2
    "720x400 85Hz",	// 3

    "640x480 60Hz",	// 4
    "640x480 66Hz",	// 5
    "640x480 70Hz",	// 6
    "640x480 72Hz",	// 7
    "640x480 75Hz",	// 8
    "640x480 85Hz",	// 9

    "800x600 56Hz",	// 10
    "800x600 60Hz",	// 11
    "800x600 70Hz",	// 12
    "800x600 72Hz",	// 13
    "800x600 75Hz",	// 14
    "800x600 85Hz",	// 15
    
    "832x624 75Hz",	// 16

    "1024x768 60Hz",	// 17
    "1024x768 70Hz",	// 18
    "1024x768 72Hz",	// 19
    "1024x768 75Hz",	// 20
    "1024x768 85Hz",	// 21

    "1152x864 60Hz",	// 22
    "1152x864 70Hz",	// 23
    "1152x864 75Hz",	// 24
    
	"1280x1024 60Hz",	// 25
    "1280x1024 70Hz",	// 26
    "1280x1024 75Hz",	// 27

    "RGB 480p 60Hz",	// 28
    "RGB 720p 60Hz",	// 29
    "RGB 720p 50Hz",	// 30
    "RGB 1080i 60Hz",	// 31
    "RGB 1080i 50Hz",	// 32
    "RGB 1080i 50Hz",	// 33
    "RGB 480i 60Hz",	// 34
    "RGB 576i 50Hz",	// 35
    "RGB 576p 50Hz",	// 36

    "YPbPr 480p",	// 37
    "YPbPr 720p",	// 38
    "YPbPr 720p50",	// 39
    "YPbPr 1080i",	// 40
    "YPbPr 1080i50A",	// 41
    "YPbPr 1080i50B",	// 42
    "YPbPr 480i",	// 43
    "YPbPr 576i",	// 44
    "YPbPr 576p",	// 45

	""
};

//-------------------------------------------------------------------------
extern CODE struct RegisterInfo UserRange;

extern	IDATA WORD  IVF;
extern	IDATA DWORD	IHF;
extern	 	  BYTE	DebugLevel;
extern	      bit   Range4Coarse;
extern	DATA  WORD  tm01, tm001;
extern	DATA  BYTE  tic01;
extern  DATA  WORD  tic_pc;

		BYTE PcMode;

#if defined WVGA || defined WSVGA || defined WXGA || defined VGA_PRIMEVIEW
		bit   Flag4Bypass=0;	    // 0:non-bypass
#else //defined WVGA || defined WSVGA || defined WXGA || defined VGA_PRIMEVIEW
		bit   Flag4Bypass=0;//1;		// 1:bypass 
#endif //defined WVGA || defined WSVGA || defined WXGA || defined VGA_PRIMEVIEW

//-----------------------------------------------------------------------------
extern	CODE struct _PCMDATA  PCMDATA[];

extern CODE BYTE *CheckPCCableStr[];
extern CODE BYTE *CheckDTVCableStr[];
extern CODE BYTE *OutOfRangeStr[] ;


CODE BYTE DTVMode[] = {	EE_YPbPr_480I, EE_YPbPr_576I, EE_YPbPr_480P, EE_YPbPr_576P,
						EE_YPbPr_1080I,	EE_YPbPr_720P, EE_PC_UNKNOWN, EE_PC_UNKNOWN };
//#define DetectDTVInputSource()	DTVMode[ReadADC(0xC1)& 0x07]

//=============================================================================
BYTE Measure_VPN_IHF( WORD *p_vpn, DWORD *p_ihf)
{
	DWORD ppf;
	WORD  hpn;


	if( !MeasureAndWait(3) ) {
	
		#ifdef DEBUG_PC
		dPuts("\r\n  ** Error at Get_VPN_IHF");
		#endif //DEBUG_PC
		return 0;
	}

	ppf    = GetPPF();			//
	*p_vpn = GetVPN();			//
	hpn    = GetHPN();			// HPN = H Period Num

	*p_ihf = (ppf + hpn/2) / hpn;			// IHF = PPF / HPN 

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n  *** PPF=%ld   HPN=%4d", ppf, hpn);
	dPrintf("  --> VPN=%4d   IHF=%ld ", *p_vpn, *p_ihf);
	dPrintf("  IVF=%d", (WORD)((*p_ihf + *p_vpn/2) / *p_vpn) );

	dPrintf(" [%d, %ld]", LastVPN, LastIHF);

	#endif // DEBUG_PC_MEAS

	return 1;
}
#ifdef SUPPORT_DTV
BYTE	DetectDTVInputSource( void )
{
	WORD	vpn;
	DWORD	ihf;

	if ( Measure_VPN_IHF( &vpn, &ihf) ) {
		if (( ihf > 15634 ) && ( ihf < 15834 ))				//15734
			return EE_YPbPr_480I;
		else if (( ihf > 31369 ) && ( ihf < 31569 ))		// 31469
			return EE_YPbPr_480P;
		else if (( ihf > 15525 ) && ( ihf < 15725 ))			// 15625
			return EE_YPbPr_576I;
		else if (( ihf > 31150 ) && ( ihf < 31350 )) {		// 31250 576P & 1080I50B
			WriteTW88(0x54, 0);
			MeasureAndWait(3);
			vpn = GetVstart();
			if ( vpn < 3 ) return EE_YPbPr_1080I50B;
			else return EE_YPbPr_576P;
			/*
			ChangeInternPLL(PCMDATA[EE_YPbPr_1080I50B].PPF * 100000L);	// Set PPF (Internal PLL) as 0x948	for 1080I50B
			WriteTW88( 0x40, 0xA4 );						// clear invert field
			WriteTW88(0x45, 0xD2);							// Field detection start=128, end=1664
			WriteDecoder(0x06, 0x80);						// software reset
			delay(100);
			WriteDecoder(0x5b, 1);							// ODD field measure
			delay(100);
			vpn = GetVPN();
			#ifdef DEBUG_DTV
			Printf("\r\nODD field VPN: %d", vpn);
			#endif
			if ( !vpn )	return EE_YPbPr_576P;
			WriteDecoder(0x06, 0x80);						// software reset
			delay(100);
			WriteDecoder(0x5b, 1);							// EVEN field measure
			delay(100);
			vpn = GetVPN();
			#ifdef DEBUG_DTV
			Printf("\r\nEVEN field VPN: %d", vpn);
			#endif
			if ( !vpn )	return EE_YPbPr_576P;
			return EE_YPbPr_1080I50B;
			*/
		}
		else if (( ihf > 36500 ) && ( ihf < 38500 ))			// 37500
			return EE_YPbPr_720P50;
		else if (( ihf > 44000 ) && ( ihf < 46000 ))			// 45000
			return EE_YPbPr_720P;
		else if (( ihf > 32750 ) && ( ihf < 34750 ))			// 33750
			return EE_YPbPr_1080I;
		else if (( ihf > 27125 ) && ( ihf < 29125 ))			// 28125
			return EE_YPbPr_1080I50A;
		else
			return EE_PC_UNKNOWN;
	}

	return (EE_PC_UNKNOWN);		// cannot find correct mode
}
#endif
void ResetPCValue(void)
{
	SaveDefaultPCDataEE();
	if( DetectAndSetForVGAInput(3)==FALSE )		// HHY 1.44 change 1 to 3
		CloseOSDMenu();

	LCDPowerON(0);
}

void StartNewDetect(void)
{
	ClearEnDet();
	MeasureAndWait(3);
	SetEnDet();

	WriteTW88(0xd0, 0xff);
	WriteTW88(0xd1, 0xff);
}
/*
WORD gap(WORD a, WORD b)
{
	if( a>b ) return a-b;
	return b-a;
}
*/
WORD GetCoarseValue(void)
{
	return GetCoarse();
}

WORD SetPCCoarseValue(BYTE val)		//1:Up	2:Dn
{
	WORD	coarse;

//	WriteADC(0xc1, 0x30);
	WriteADC(0xc0, 0x38);

	coarse = GetCoarse();
	if( val==UP ) coarse++;
	else coarse--;

	SetCoarse(coarse);
	SaveCoarseEE(PcMode);	// HHY 1.33

	StartNewDetect();

//	WriteADC(0xc1, 0x20);
	WriteADC(0xc0, 0x28);
	return coarse;
}


BYTE SetPhaseValue(BYTE val)
{
	BYTE	phase;

	phase = GetPhaseCurrent();

	if( val==UP ) {
		if( phase>=31 ) return phase;
		else phase++;
	}
	else {
		if( phase==0 ) return phase;
		else phase--;
	}

	SetPhase(phase);
	SavePhaseEE(PcMode);	// HHY 1.33

	return phase;
}

BYTE IsDTVInput(void)
{
	if( GetInputSelection()==DTV || GetInputSelection()==PC ) {
		if( PcMode>=EE_RGB_480P && PcMode<=EE_YPbPr_576P ) return 1;
	}
	return 0;
}

IDATA struct RegisterInfo VPositionRange={0,100, 50};

//=============================================================================
//                    PC Screen Position Move Functions
//=============================================================================
void MoveActiveVpos(BYTE dir)		//=== Up
{
	char add;

	if( dir==UP ) {
		if( VPosCurr>=VPosMax ) return;
		add = 1;
	}
	else {
		if( VPosCurr==0 ) return;
		add = -1;
	}
	VPosCurr += add;

	if( IsBypassmode() ) {
		SetVactiveStart( GetVactiveStart()+add );
		SaveVactiveEE(PcMode);						// HHY 1.33
	}
	else {
		SetVactiveStart( GetVactiveStart()+add );
		SaveVactiveEE(PcMode);						// HHY 1.33
		SetVBackPorch( GetVBackPorch()+add );		// A6
		SaveVBackPorchEE(PcMode);					// HHY 1.33
	}
}

void MoveActiveHpos(BYTE dir)		//=== Right
{
	char add;
	WORD hstart, hend;

	if( dir==UP ) {
		if( HPosCurr>=HPosMax ) return;
		add = 1;
	}
	else {
		if( HPosCurr==0 ) return;
		add = -1;
	}
	HPosCurr += add;

	hstart = GetHactiveStart();
	hend   = GetHactiveEnd();

	hstart += add;
	hend   += add;
	SetHactiveStart(hstart);
	SetHactiveEnd(hend);

	SaveHactiveEE(PcMode);		// HHY 1.33
}

BYTE GetVPosition(void)
{
	int newv;

	VPositionRange.Max = VPosMax;
	VPositionRange.Default = VPosMax/2;
	Mapping2( VPosCurr, &VPositionRange, &newv, &UserRange );

	return newv;
}

BYTE SetVPosition(BYTE val)		//0:UP, 1:DOWN
{
	int newv;

	MoveActiveVpos(val);

	VPositionRange.Max = VPosMax;
	VPositionRange.Default = VPosMax/2;
	Mapping2( VPosCurr, &VPositionRange, &newv, &UserRange );
	
	return newv;
}

BYTE GetHPosition(void)
{
	return HPosCurr;
}

BYTE SetHPosition(BYTE val)
{
	MoveActiveHpos(val);

	return HPosCurr;
}
//=============================================================================
//		Phase Measurement
//			Return : PhaseBlue, PhaseGreen, PhaseRed										   
//=============================================================================
DWORD ReadOut4(void)
{
	BYTE	i;
	DWORD	dat=0;

	for(i=0; i<4; i++) {
		dat <<= 8;
		dat |= (DWORD)ReadTW88(0x5a-i);
	}
	return dat;
}

BYTE GetPhaseRGB(void)		// HHY 1.10 BYTE return 
{
	static bit flag=0;
	DWORD _RGB;

	#ifdef DEBUG_PC_MEAS
	BYTE sign;
	#endif // DEBUG_PC_MEAS

	_RGB = PhaseRGB;

	if( !MeasureAndWait(3) ) {
		return 0;		//LJY001219
	}

	WriteTW88(0x5b, 0x08);			// Read Phase B
	PhaseRGB  = ReadOut4();

	WriteTW88(0x5b, 0x18);			// Read Phase G
	PhaseRGB += ReadOut4();

	WriteTW88(0x5b, 0x28);			// Read Phase R
	PhaseRGB += ReadOut4();

	#ifdef DEBUG_PC_MEAS
	if( PhaseRGB  >= _RGB ) sign = '+'; else sign = '-';
	dPrintf("(%c%lu)", (WORD)sign, PhaseRGB);
	dPrintf("(%c%lu), %d", (WORD)sign, PhaseRGB, GetHstart() );
	#endif //DEBUG_PC_MEAS

	if( PhaseRGB==_RGB ) {			// NO INPUT ???
		dPuts("\r\n??? SYNC loss...");
		if(flag) {
			flag = 0;
			return 0;
		}
		else flag = 1;
	}
	else flag = 0;

	return 1;
}

//============================================================================
//			Detect Input source for PC
//============================================================================
/*
BYTE DetectPCInputSource(void)
{
	BYTE	 mode, PCMode;

	mode = ReadADC(0xC1)& 0x07;	// 8816 0x1c1 for LLPLL input detection register

	#ifdef DEBUG_PC
	dPrintf("\n +++DetectPCInputSource ==> Detect from ADC : 0x%2x", (WORD)mode);
	#endif
	switch(mode) {
		case 1: PCMode = EE_RGB_480I;	break;
		case 2: PCMode = EE_RGB_576I;  break;
		case 3:	PCMode = EE_RGB_480P;	break;
		case 4:	PCMode = EE_RGB_576P;	break;
		case 5:	PCMode = EE_RGB_720P;	break;
		default:PCMode = EE_PC_UNKNOWN;	break;
	}

	return PCMode;
}
*/

//============================================================================
//			Determine InputSource Format based on VPN
//============================================================================
//	Input	VPN
//	Return	PcMode
//			InputSource (PC_XGA, PC_SVGA, PC_VGA)

BYTE DecideVGAInputSource(WORD vpn, WORD ivf)
{
	BYTE _PcMode;

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n-> DecideVGAInputSource: vpn:%4xh, ivf:%4xh", vpn, ivf);
	#endif // DEBUG_PC_MEAS


	_PcMode     = EE_PC_UNKNOWN;
	//InputSource = UNKNOWN;

	/*		comment out for there is no DTV type on PC input mode 10/05/2007
	_PcMode = DetectDTVInputSource();
	#ifdef DEBUG_PC
	dPrintf("\r\n-----> DetectDTVInputSource(): _PcMode:%d", (WORD)_PcMode);
	#endif
	if(_PcMode != EE_PC_UNKNOWN ) return _PcMode;
	*/
	//====================== PC DOS ================================
	if( vpn >= 440  && vpn <= 460 ) { 
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== PC DOS ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		//InputSource = PC_DOS1;  
		switch( ivf ) {
		case 69: case 70: case 71:	_PcMode = EE_DOS;			break;
		
		case 84: case 85: case 86: case 87:
			GetHpnVpn(1);
		#ifdef REFERENCE
			if( ReadTW88(0x40) & 0x02 ) 
				_PcMode = EE_SP1;			
			else
				_PcMode = EE_SP2;
		#else // REFERENCE
			if( ReadTW88(0x40) & 0x02 )
			{
				if(IHF >= 37910 && IHF <= 38000)
					_PcMode = EE_SP3;	
				else if((IHF >= 37850 && IHF <= 37900) && 
						(GetHPN <= 1360 && GetHPN >= 1330))
					_PcMode = EE_SP2;
				else
					_PcMode = EE_SP1;	
			}
			else
				_PcMode = EE_SP2;	
		#endif //REFERENCE
			break;

		default:					_PcMode = EE_PC_UNKNOWN;	break;

		}
	}
	//====================== PC VGA, DTV 480P ======================
	else if( vpn>=490  && vpn<=540 ) { 

		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== PC VGA, DTV 480P ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		switch( ivf ) {
			case 59: case 60: case 61:
				_PcMode = EE_VGA_60;	break;
			case 65: case 66: case 67:	_PcMode = EE_VGA_66;		break;
			case 69: case 70: case 71:	_PcMode = EE_VGA_70;		break;
	        case 72: case 73:			_PcMode = EE_VGA_72;		break;
			case 74: case 75: case 76:	_PcMode = EE_VGA_75;		break;
			case 83:
		 	case 84: case 85: case 86:	_PcMode = EE_VGA_85;		break;
			default:					_PcMode = EE_PC_UNKNOWN;	break;
		}
	}
	//====================== PC SVGA ===============================
	else if( vpn>=610 && vpn<=680+30 ) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== PC SVGA ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		//InputSource = PC_SVGA;	
		switch( ivf ) {
			case 49: case 50: case 51: _PcMode = EE_RGB_576P;		break;
		
			case 55: case 56: case 57:	_PcMode = EE_SVGA_56;		break;
			case 59: case 60: case 61: case 62: case 63: case 64:
										_PcMode = EE_SVGA_60;		break;
			case 69: case 70: case 71:	_PcMode = EE_SVGA_70;		break;
		    case 72: case 73:			_PcMode = EE_SVGA_72;		break;
			case 74: case 75: case 76:	_PcMode = EE_SVGA_75;		break;

			case 83:
			case 84: case 85: case 86:	_PcMode = EE_SVGA_85;		break;
		
			default:					_PcMode = EE_PC_UNKNOWN;	break;
		}
	}

	//====================== DTV 720P ==============================
	else if(vpn>=751-20 && vpn<=751+30) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== DTV 720P ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		#ifdef REFERENCE
		if( ivf>=55) 
		#else //REFERENCE
		if( ivf>=55  && ivf<=65) 
		#endif //REFERENCE
		{
			_PcMode = EE_RGB_720P;
		}
		#ifdef REFERENCE
		else
		#else //REFERENCE
		else if( ivf>=45  && ivf<=55) 
		#endif //REFERENCE
		{
			_PcMode = EE_RGB_720P50;
		}
	}
	//====================== DTV 1080i =============================
	else if(vpn>=563-10 && vpn<=563+10) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== DTV 1080i ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		if( ivf>=55 ) {
			_PcMode = EE_RGB_1080I;
		}
		else {
			_PcMode = EE_RGB_1080I50A;
		}
	}
	//====================== DTV 480i ==============================
	else if(vpn>=264-40 && vpn<=264+35) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== DTV 480i ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		_PcMode = EE_RGB_480I;
	}
	//====================== DTV 576i ==============================
	else if(vpn>=314-14 && vpn<=314+50) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== DTV 576i ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		_PcMode = EE_RGB_576I;
	}

	//====================== PC XGA ================================
	else if( vpn>=790 && vpn<=820 ) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== PC XGA ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		//InputSource = PC_XGA;	
		switch( ivf ) {
		case 59: case 60: case 61:	_PcMode = EE_XGA_60;		break;
		case 69: case 70: case 71:	_PcMode = EE_XGA_70;		break;
		         case 72: case 73:	_PcMode = EE_XGA_72;		break;
		case 74: case 75: case 76:	_PcMode = EE_XGA_75;		break;
		case 84: case 85: case 86:	_PcMode = EE_XGA_85;		break;
		default:					_PcMode = EE_PC_UNKNOWN;	break;
		}
	}
	//====================== PC 1152x864 ===========================
	else if( vpn>=850 && vpn<=1000 ) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== PC 1152x864 ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		//InputSource = PC_SXGA;	
		switch( ivf ) {
		case 59: case 60: case 61:	_PcMode = EE_1152_60;		break;
		case 69: case 70: case 71:	_PcMode = EE_1152_70;		break;
		case 74: case 75: case 76:	_PcMode = EE_1152_75;		break;
		default:					_PcMode = EE_PC_UNKNOWN;	break;
		}
	}

	//====================== PC SXGA ===============================
	else if( vpn>=1024 && vpn<=1600 ) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=== PC SXGA ===: vpn:%4d, ivf:%4d", (WORD)vpn, (WORD)ivf);
		#endif //DEBUG_PC_MEAS
		//InputSource = PC_SXGA;	
		switch( ivf ) {
		case 59: case 60: case 61:	_PcMode = EE_SXGA_60;		break;
		case 69: case 70: case 71:	_PcMode = EE_SXGA_70;		break;
		case 74: case 75: case 76:	_PcMode = EE_SXGA_75;		break;
		default:					_PcMode = EE_PC_UNKNOWN;	break;
		}
	}

	#ifdef DEBUG_PC_MEAS
	if( _PcMode == EE_PC_UNKNOWN )
		dPrintf("\r\nUnknown Input-- VPN:%d IVF:%d", vpn, ivf);
	else
		dPrintf("\r\nInput VPN(%d) IVF(%d) :%d(%s)", vpn, ivf, (WORD)_PcMode, PcModeStr[_PcMode] );
	#endif //DEBUG_PC_MEAS

	if( !PCMDATA[_PcMode].Support ) _PcMode = EE_PC_UNKNOWN;

	return _PcMode;
}

WORD ConvertBasedOnInput(WORD dat)
{				  
	DWORD	dtmp;

	if( IsBypassmode() ) return dat;				// HHY 2.01

	dtmp = PCMDATA[PcMode].PPF*100000L/dat;			// from PPF-based to IPF-based
	dtmp = PCMDATA[PcMode].IPF*100000L/dtmp;		// NewHPN = OldHPN * (IPF/PPF)
	return (WORD)dtmp;
}

//=============================================================================
//				Search ADC Clock with measuring Phase
//=============================================================================
/*
WORD AutoTuneClock(void)
{
	WORD	low, high, lowV, highV;	// Test value range of plldiv
	WORD	i;
//	BYTE	phase, phasepeak, j;
	WORD	num, width, height;

	#ifdef DEBUG_PC
	dPrintf("\r\n---Tune-Coarse Mode=%d", (WORD)PcMode);
	#endif

	//------ Set Test Range, Divide Range more detail

	low  = 10;
	high = ConvertBasedOnInput( GetHPN() );
	SetMeasureWindowH(low, high);			//

	low  = 1;
	high = GetVPN() - 1;
	SetMeasureWindowV(low, high);			//

	low  = PCMDATA[PcMode].low;
	high = PCMDATA[PcMode].high;

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n===>>>>Get Divider Number=0x%4x to 0x%4x", (WORD)low, (WORD)high);
	#endif
	width = PCMDATA[PcMode].HAN;
	height = PCMDATA[PcMode].VAN;
	SetCoarse( low );
	MeasureAndWait(3);
	low = GetHend() - GetHstart() - 1;
	lowV = GetVend() - GetVstart() - 1;
	SetCoarse( high );
	MeasureAndWait(3);
	high = GetHend() - GetHstart() - 1;
	highV = GetVend() - GetVstart() - 1;

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n===>>>>width: 0x%4x, low: 0x%4x, high: 0x%4x", (WORD)width, (WORD)low, (WORD)high);
	dPrintf("\r\n===>>>>height: 0x%4x, lowV: 0x%4x, highV: 0x%4x", (WORD)height, (WORD)lowV, (WORD)highV);
	#endif
	if(( low > width ) || ( width > high ) )	return 0;		// cannot adjustable in setting range...
//	if(( height > (highV+100) ) )	return 0;		// cannot adjustable in setting range...

	for(i=PCMDATA[PcMode].low; i <= PCMDATA[PcMode].high; i+=4 ) {	// increment by 4

		SetCoarse(i);
		MeasureAndWait(3);
		width = GetHend() - GetHstart();
		if ( width >= PCMDATA[PcMode].HAN ) return (i);
	}
	return num;

}
*/

WORD AutoTuneClock(void)
{
	WORD	low, high;	// Test value range of plldiv
	WORD	i;
	BYTE	phase, phasepeak, j, phasemin;
	WORD	num;
	DWORD	RGBdiff, RGBmin;

	#ifdef DEBUG_PC
	dPrintf("\r\n---Tune-Coarse Mode=%d", (WORD)PcMode);
	#endif //DEBUG_PC

	//------ Set Test Range, Divide Range more detail

	low  = 10;
	high = ConvertBasedOnInput( GetHPN() );
	SetMeasureWindowH(low, high);			//

	low  = 1;
	high = GetVPN() - 1;
	SetMeasureWindowV(low, high);			//

	low  = PCMDATA[PcMode].low;
	high = PCMDATA[PcMode].high;

	i = IVF;
	num = GetHpnVpn(1);								// Get vpn, IVF
	if( num==0 ) {
		#ifdef DEBUG_PC
		dPrintf("\r\n  --> Error at GetHpnVpn() line:%d", __LINE__);
		#endif //DEBUG_PC
		return 0;
	}

	#ifdef DEBUG_PC
	if( i != IVF ) dPrintf("\r\nIVF changed %d -> %d ****", i, IVF);
	#endif //DEBUG_PC

	SetVCORange( (DWORD)IVF * num * PCMDATA[PcMode].CLOCK );

	#ifdef DEBUG_PC
	dPrintf("\r\nRange:%04x to %04x\r\n", low, high);
	#endif //DEBUG_PC

	//===== For the PLL div range, seek the Phase Peak =====
	// if PLL div value is correct, phase RGB values are peak.
	
	RGBPeak=0;

	num = low;	// plldiv of new peak
	RGBdiff = 0;
	for(i=low; i <= high; ) {

		SetCoarse(i);
		WriteADC( 0xCD, 1 );	// init LLPLL
		delay(20);

		GetPhaseRGB();
		RGBPeak = 0;
		RGBmin = PhaseRGB;

		for(j=0; j<8; j++) {
			phase = (7-j)*4;					// HHY 1.10
			SetPhase(phase);					// if NO_INPUT stop
			if( !GetPhaseRGB() ) return 0;		//

			if(RGBPeak < PhaseRGB) {
				RGBPeak = PhaseRGB;
				phasepeak = phase;
				// num = i;
				dPuts(" -*"); 
			} 
			else {
				dPuts("   ");
			}
			if (RGBmin > PhaseRGB ) {
				RGBmin = PhaseRGB;
				phasemin = phase;
			}
		}
		if ( RGBdiff < (RGBPeak - RGBmin) ) {
			RGBdiff = (RGBPeak - RGBmin);
			num = i;
		}
#ifdef REFERENCE
		if( Range4Coarse ) i++;
		else if(PcMode>=EE_SXGA_60 || PcMode==EE_VGA_60)
			i += 4;
		else	
			i += 4;
#else //REFERENCE
		i++;
#endif //REFERENCE
	}

	if( high!=low ) SetCoarse(num);		// set value of peak
	Printf("\r\nFind Coarse Number: %x[%d]", num, num );
	WriteADC( 0xCD, 1 );	// init LLPLL
	SetPhase(phasemin + 14);
//	SetPhase(phasepeak);
	return num;

}

//-----------------------------------------------------------------------------
//		Final Set ADC [PLL div], [Phase]
//-----------------------------------------------------------------------------
/*
void AutoTunePhase(void)
{
	BYTE	i, j, peak_j, min_j;
	DWORD	Phase0, Phase1, Phase2, PhaseT;

	dPuts("\r\n-------------Tune-Fine");

	if( IsDTVInput() ) return;
//	WriteTW88(0xff, 1);
//	WriteTW88(0xcd, 1);
//	WriteTW88(0xff, 0);

	SetMeasureWindowH( 0,  PCMDATA[PcMode].HAN + 200);
	SetMeasureWindowV( 0,  PCMDATA[PcMode].VAN + 200);

	j = GetPhaseCurrent();

	GetPhaseRGB();
	Phase0 = PhaseRGB;
	j++;
	j &= 0x1f;
	SetPhase(j);
	GetPhaseRGB();
	Phase1 = PhaseRGB;
	j++;
	j &= 0x1f;
	SetPhase(j);
	GetPhaseRGB();
	Phase2 = PhaseRGB;

	PhaseT = Phase0 + Phase1 + Phase2;
	
	peak_j = j;
	RGBPeak = PhaseT;
	RGBMin = PhaseT;
	for(i=0; i<32; i++) {
		j++;
		j &= 0x1f;
		SetPhase(j);						// if NO_INPUT stop
		if( !GetPhaseRGB() ) return;		//

		Phase0 = Phase1;
		Phase1 = Phase2;
		Phase2 = PhaseRGB;
		PhaseT = Phase0 + Phase1 + Phase2;
		if(RGBPeak < PhaseT) {
			RGBPeak = PhaseT;
			peak_j = j;
			dPuts("--peak");
		} 
		else if(RGBMin > PhaseT) {		// real case is smallest is good diplay
			RGBMin = PhaseT;
			min_j = j;
			dPuts("--min");
		}
		else {
			dPuts("   ");
		}
	}

//	j = (min_j + 16 -1 ) & 0x1f;
	j = (peak_j - 1 ) & 0x1f;
	SetPhase(j);
}
*/
void AutoTunePhase(void)
{
	BYTE	i, j, peak_j, min_j;
#ifdef REFERENCE
	DWORD	RGBmin, RGBavg;
#else //REFERENCE
	DWORD	RGBmin;
#endif //REFERENCE

	#ifdef DEBUG_PC
	dPuts("\r\n-------------Tune-Fine");
	#endif //DEBUG_PC

	#ifdef SUPPORT_DTV
	if( IsDTVInput() ) return;
	#endif //SUPPORT_DTV

	//j = GetPhaseCurrent() - Start_Phase;  

	SetMeasureWindowH( 0,  PCMDATA[PcMode].HAN + 200);
	SetMeasureWindowV( 0,  PCMDATA[PcMode].VAN + 200);

    j =0;
	RGBPeak=0;//9
	GetPhaseRGB();
	RGBmin = PhaseRGB;
	for(i=0; i<32; i++, j++) {		// full scan PHASE

		SetPhase(j);						// if NO_INPUT stop

		if( !GetPhaseRGB() ) return;		//
		

		if(RGBPeak < PhaseRGB) {
			RGBPeak = PhaseRGB;
			peak_j = j;
			#ifdef DEBUG_PC
			dPuts("--peak");
			#endif //DEBUG_PC
		} 
		else {
			#ifdef DEBUG_PC
			dPuts("   ");
			#endif //DEBUG_PC
		}
		if ( PhaseRGB < RGBmin ) {
			RGBmin = PhaseRGB;
			min_j = j;
		}
	}
	SetPhase(min_j + 16);		// opposite phase of min value
	WriteADC( 0xCD, 1 );	// init LLPLL
	return;

/*
	RGBavg = ( RGBmin + RGBPeak );
	RGBavg >>= 1;
	
	for ( j=min_j; j<min_j+32; j++ ) {
		SetPhase(j);						// if NO_INPUT stop
		if( !GetPhaseRGB() ) return;		//
		
		if ( PhaseRGB > RGBavg ) {
			for ( i=j+1; i<min_j+32; i++ ) {
				SetPhase(i);						// if NO_INPUT stop
				if( !GetPhaseRGB() ) return;		//
				if ( PhaseRGB < RGBavg ) {
					peak_j = (j + i - 1) / 2 - 2;		// center of big value, move 2 points left
					SetPhase( peak_j);
					#ifdef DEBUG
					dPrintf("\r\n set phase: %d, min_j: %d", peak_j, min_j);
					#endif
					return;
				}
			}
		}
	}
	//SetPhase(peak_j);
	//SetPhase(min_j + 12);		// opposite phase of min value
	SetPhase(min_j + 16);		// opposite phase of min value
*/
}
//-----------------------------------------------------------------------------
//			Measure    VPN, HPN
//			Calculate  IVF, IHF
//-----------------------------------------------------------------------------
WORD GetHpnVpn(BYTE en)
{
	WORD	vpn, hpn, sync;	//hsync, vsync;
	BYTE	SyncPol;

	en = DebugLevel;
	if( !en && DebugLevel ) 	DebugLevel = 0;

	#ifdef DEBUG_PC
	dPuts("\r\n------ GetHpnVpn()");
	#endif //DEBUG_PC
	//----- Measurement Command -------------

	if( !MeasureAndWait(3) ) {			// field any...
		#ifdef DEBUG_PC
		dPrintf(" Error at GetHpnVpn ");
		#endif //DEBUG_PC
		DebugLevel = en;
		return 0;
	}

	//----- Get VPN -------------------------
	vpn = GetVPN();					// VPN = V Period Num
	sync = GetVSYNCPulse();
// in case of 8816 sync is same to vpn so I cannot use below....
	// Polarity check
	if( sync > (vpn/3) ) {
		InvertVSYNCPolarity();
		MeasureAndWait(3);
		sync = GetVSYNCPulse();
		#ifdef DEBUG_PC_MEAS
		dPrintf(" --->New VSYNC:%04x(%d)", sync, sync);
		#endif //DEBUG_PC_MEAS
	}
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n VPN:%04x(%d)  VSYNC:%04x(%d)", vpn, vpn, sync, sync);
	dPrintf("\r\n IHF:%08lx(%ld)", IHF, IHF);
	#endif //DEBUG_PC_MEAS

	//----- Get HPN ---------------------
	hpn = GetHPN();						// HPN = H Period Num
	sync = GetHSYNCPulse();			// H sync Pulse Width = HSYNC interval

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n HPN:%04x(%d)  HSYNC:%04x(%d)", hpn, hpn, sync, sync);
	dPrintf("\r\n PPF:%08lx(%ld)", GetPPF(), GetPPF() );
	#endif //DEBUG_PC_MEAS

	if( sync >= (hpn/3) ) {
		SyncPol = ReadDecoder(0x40);	// INVERT SYNC POLARITY
		if ( SyncPol & 0x04 ) 			// b'2 is HSYNC POL
			SyncPol &= 0xfb;
		else SyncPol |= 0x04;
		WriteDecoder(0x40, SyncPol);

		MeasureAndWait(3);
		sync = GetHSYNCPulse();			// H sync Pulse Width = HSYNC interval
		hpn = GetHPN();						// HPN = H Period Num
	}

	//----- Get New HPN -------------
	IHF = (GetPPF()+hpn/2) / hpn;		// IHF = PPF / HPN 

	//----- Get New VPN -------------
	vpn = GetVPN();
	IVF = (WORD)((IHF+vpn/2)/vpn);		// IVF = IHF / VPN 

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nIHF(New):%08lx(%ld)", IHF, IHF);
	dPrintf("\r\nHPN(New):%04x(%d)  HSYNC(New):%04x(%d)", hpn, hpn, sync, sync);
	dPrintf("\r\nVPN(New):%04x(%d)", vpn, vpn);
	dPrintf("\r\nIVF(New):%04x(%d)", IVF, IVF);
	dPuts("\r\n-------");
	#endif //DEBUG_PC_MEAS

	DebugLevel = en;
	return vpn;
}

//=============================================================================
//			Return V active Start
//=============================================================================
WORD GetVerticalActiveArea(void)
{

	WORD  vstart, vstart1, vend;

	char  off=0;

	dPuts("\r\n----- Get V Active Area");

	//----- if current mode is DTV, use default value----------------

	//#ifdef SUPPORT_DTV
	if( IsDTVInput() ) {

		#ifdef DEBUG_DTV
		dPrintf("  ---> Use fixed data Vstart=%d  VAN=%d", PCMDATA[PcMode].Vstart, PCMDATA[PcMode].VAN);
		#endif //DEBUG_DTV

		SetVactiveStart( PCMDATA[PcMode].Vstart );
		
		switch (PcMode) {
		case EE_YPbPr_480I:		off = 4;	break;
		case EE_YPbPr_1080I:	off = 2;	break;
		case EE_RGB_1080I:		off = 4;	break;
		default:				off = 0;	break;
		}
		SetVactiveLen( PCMDATA[PcMode].VAN+off+20 );
		
		return PCMDATA[PcMode].Vstart;
	}
	//#endif

	//======================== Get the Bottom End ========================
#ifdef REFERENCE	
	vend   = GetVend();

	if( vend >= GetVPN() ) {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\nToo big vend [%04x]", vend);
		#endif
		vend = GetVPN()-1;
	}
	vstart  = vend - PCMDATA[PcMode].VAN + 1;
	vstart1 = GetVstart();
//	vstart  = GetVstart();
#else //REFERENCE
		vstart  = GetVstart();
		vend   = GetVend();
#endif //REFERENCE
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nFind Vend   --- %04x %04x", vstart, vend);
	#endif //DEBUG_PC_MEAS

	//================================================= HHY 2.00
	if( PcMode >= EE_1152_60 && PcMode <=EE_1152_75 ) {
		if( vstart1 > vstart && vstart1 <= vstart+3 ) {
			vstart = vstart1;
			vend   = vstart + PCMDATA[PcMode].VAN - 1;
			#ifdef DEBUG_PC_MEAS
			dPuts("    -------> Use Vstart");
			#endif //DEBUG_PC_MEAS
		}
	}
	//=================================================

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nAuto Measure Vstart=%04x(%d)  Vend=%04x(%d)", vstart, vstart, vend, vend);
	#endif //DEBUG_PC_MEAS

	if( (vstart > PCMDATA[PcMode].Vstart + 30) || ((int)vstart < ((int)PCMDATA[PcMode].Vstart - 30) ) ) {

		#ifdef DEBUG_PC_MEAS
		dPrintf("    ==> Out Of Range V Active");
		#endif //DEBUG_PC_MEAS

		vstart = GetVactiveStartEE(PcMode);
		vend   = vstart + PCMDATA[PcMode].VAN - 1;
	}

	//----- Compensation mode by mode -------------------------------

	#ifdef VGA
	if( PcMode>=EE_VGA_60 || PcMode<=EE_VGA_85 ) {
		vstart -= 5;
		dPrintf("\r\n      ----------- VGA Bypass !!!");
	}
	#endif //VGA

	if( PcMode==EE_SP2 ) vstart = PCMDATA[EE_SP2].Vstart;	// HHY 1.62	640x350

	//----- set the register values ( Vstart, VAN ) -----------------
#ifdef REFERENCE
	if ( PcMode == EE_VGA_75 ) vstart --;
	if ( PcMode == EE_VGA_85 ) vstart --;
#endif //REFERENCE
#ifdef XGA
	if (PcMode == EE_VGA_72)
		SetVactiveStart(vstart-1);
	else
		SetVactiveStart(vstart);
#else //XGA
	SetVactiveStart(vstart);
#endif //XGA
	//SetVactiveStart(vstart1 - 1);

	//SetVactiveLen(PCMDATA[PcMode].VAN + 6);		// with VAN
#ifdef REFERENCE	
	SetVactiveLen(PCMDATA[PcMode].VAN);		// with VAN
#else //REFERENCE
#ifdef XGA
	if (PcMode == EE_VGA_72)
		SetVactiveLen(vend - vstart +2);
	else
		SetVactiveLen(vend - vstart +1);
#else //XGA
	SetVactiveLen(vend - vstart +1);
#endif //XGA 
#endif  //REFERENCE
	
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n@@@@@ Vstart=%04x[%d]  Vend=%04x[%d]", vstart, vstart, vend, vend);
	#endif //DEBUG_PC_MEAS

	return vstart;
}
//=============================================================================
//
//=============================================================================
BYTE GetHorizontalActiveArea(void)
{
	WORD	hstart, hend;

	dPuts("\r\n----- Get H Active Area ");

	#ifdef SUPPORT_DTV
	if( IsDTVInput() ) {
		hstart = PCMDATA[PcMode].Hstart;
		#ifdef REFERENCE
		hend   = hstart + PCMDATA[PcMode].HAN + 1;
		else
		if ( PcMode >= EE_YPbPr_1080I || PcMode <= EE_YPbPr_1080I50B) 
			hend =  PCMDATA[PcMode].HAN + 1;	
		#endif //REFERENCE
		#ifdef DEBUG_PC
		dPrintf("  ---> Use fixed data Hstart=%d  HAN=%d  Hend=%d", hstart, PCMDATA[PcMode].HAN, hend);
		#endif //DEBUG_PC
		
		SetHactiveStart( hstart );
		SetHactiveEnd( hend+3 );				// with HAN, Hstart
		return TRUE;
	}
	#endif //SUPPORT_DTV

	//======================== Get the Right End ========================

	hstart = GetHstart();
	#ifdef REFERENCE
	//hend   = hstart + PCMDATA[PcMode].HAN + hstart;
	hend   = hstart + PCMDATA[PcMode].HAN + 5;
	#else //REFERENCE
	LastHPN = GetCoarseValue();
	hend   = LastHPN;
	#endif //REFERENCE
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nAuto Measure Hstart=%04x(%d)  Hend=%04x(%d)", hstart, hstart, hend, hend);
	#endif //DEBUG_PC_MEAS
	
	if( (hstart > PCMDATA[PcMode].Hstart + 100) || ((int)hstart < (int)PCMDATA[PcMode].Hstart - 100) ) {

		#ifdef DEBUG_PC
		ePuts("    ==> Out Of Range H Active");
		#endif //DEBUG_PC
		
		hstart = GetHactiveStartEE(PcMode);
		hend   = hstart + PCMDATA[PcMode].HAN + 1;

		SetHactiveStart(hstart);			// with Hstart
		SetHactiveEnd( hend );				// with HAN, Hstart

		return TRUE;
	}

	//----- Compensation mode by mode -------------------------------
	#ifdef REFERENCE
	if( PcMode < EE_XGA_60 ) hend++;
	#endif //REFERENCE

	if( !IsBypassmode() ) {
		#ifdef REFERENCE
		hstart -= 2;
		hend -= 2;
		if ( PcMode == EE_VGA_60 ) {
		}
		else if ( PcMode <= EE_VGA_72 ) {
			hstart++;
			hend++;
		}
		else if ( PcMode <= EE_VGA_85 ) {
			hstart++;
			hend++;
		}
		#else //REFERENCE
		if ( PcMode <= EE_VGA_85)
			hstart -= 1;
		else if ( PcMode <= EE_SVGA_85)
			hstart -= 2;	
		#ifdef XGA
		else if( PcMode ==  EE_XGA_60 ) 
			hstart -= 1;
		#else //XGA
		else if( PcMode ==  EE_XGA_60 ) 
			hstart -= 4;	
		#endif //XGA
		hend -= 2;
		//if(  PcMode == EE_SVGA_72)
		//	hend   = hend -hstart;
		#endif //REFERENCE
		}

	#ifdef XGA
	if( PcMode>=EE_1152_60 ) {
		hstart+=3;
		hend+=3;
	}
	#endif //XGA

	#ifdef SXGA
	if( PcMode>=EE_1152_60 && PcMode<=EE_1152_75 ) {
		hstart+=2;
		hend+=2;
	}
	#endif //SXGA

	//----- set the register values ( Hstart, Hend ) ----------------

	SetHactiveStart(hstart);			// with Hstart
	SetHactiveEnd( hend );				// with HAN, Hstart

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n@@@@@ Hstart=%04x[%d]  Hend=%04x[%d]", hstart, hstart, hend, hend);
	#endif //DEBUG_PC_MEAS
	
	return TRUE;
}

//-----------------------------------------------------------------------------
//			Calcurate and Save VOback(0xb9) & PVP(0xb7,0xbb)
//             - Refer to additional document
//-----------------------------------------------------------------------------
void SetVValueForPanel(WORD VIstart)
{
	WORD	PVR, VAN, VScale, VIsync, dtmp;
	BYTE	VOsync, VOback;

	VIsync  = GetVSYNCPulse();		// active pulse width
	PVR     = GetPVR();
	#ifdef REFERENCE
	VAN     = PCMDATA[PcMode].VAN;
	#else //REFERENCE
	VAN     = GetVend() - GetVactiveStart();
	#endif //REFERENCE
	VOsync  = ReadTW88(0xb8);

	if ( VIsync > VAN ) VIsync = 0;		// if reverse, and cannot measure
	dtmp = VIstart - VIsync + 1;
	VScale = ReadTW88(0x63) & 0x0c;
	VScale <<= 6;
	VScale += ReadTW88(0x62);			// read VScale
	dtmp <<= 8;			// multiply by 256
	dtmp += (VScale >> 1);		// 0.5 calculation....
	dtmp /= VScale;		// divide by scale, calculate 
	if ( ReadTW88(0xbe) & 2 )		// unset AUTO CALC
		VOback = dtmp - VOsync;
	else
		VOback = dtmp - VOsync - 4;
	#ifdef REFERENCE
	if ( PcMode == EE_VGA_75 ) {		// vga 75Hz
		VOback += 3;
	}
	else if ( PcMode == EE_VGA_85 ) {		// vga 85Hz
		VOback += 2;
	}
	else if ( PcMode == EE_SVGA_56 ) {		// svga 56Hz
		VOback++;
	}
	#else //REFERENCE
	#ifdef XGA
	if ( PcMode == EE_VGA_72 ) 
	{
		VOback += 2;
	}
	#endif //XGA
	#endif //REFERENCE
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n************ void SetVValueForPanel(WORD VIstart) ************");
	dPrintf("\r\nVScale=%d VIsync=%d PVR=%d VAN=%d ", (WORD)VScale, (WORD)VIsync, (WORD)PVR, (WORD)VAN);
	dPrintf("\r\nVIstart=%d VIsync=%d PVR=%d VAN=%d ", (WORD)VIstart, (WORD)VIsync, (WORD)PVR, (WORD)VAN);
	dPrintf("VOsync=%d", (WORD)VOsync);
	dPrintf("==> VOback=%02bx(%bd)", VOback, VOback);
	dPrintf("\r\n**************************************************************");
	#endif // DEBUG_PC

/*
	//----- Compensation mode by mode -------------------------------
	#ifdef XGA
	if     ( PcMode==EE_DOS ) VOback -= 2;	// HHY 3.00 
	else if( PcMode==EE_SP1 ) VOback -= 2;	// HHY 3.00 
	#endif

	#if defined VGA || defined WVGA
	if     ( PcMode==EE_DOS ) VOback += 1;
	else if( (PcMode>=EE_SVGA_56) && (PcMode<=EE_SVGA_85) ) VOback += 1;
	#endif
*/
	//-----------------------------------------------------------

	SetVBackPorch( (BYTE)VOback );
	SetPVP(VOsync + VOback + PVR + 10);
}
//-----------------------------------------------------------------------------
//			Calcurate [Panel H. Cycle] = PHP(Panel H Period)
//-----------------------------------------------------------------------------
#ifndef AUTOCALC_PC
BYTE SetHValueForPanel(void)
{
	WORD	sum=0;
	WORD	php;

	sum = ReadTW88(0xb3) + ReadTW88(0xb4) + GetPHR();	// sum = AA+AB+AC,AD = From Hsync to Active region
	
	MeasureAndWait(3);

	php = (DWORD)(GetHPN()) * PCMDATA[PcMode].VAN / GetPVR();		// PHP = HPN * (VAN/PVR)

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nHPN:%04x(%d)", GetHPN(), GetHPN());
	dPrintf("\r\nVAN:%04x(%d)", PCMDATA[PcMode].VAN, PCMDATA[PcMode].VAN);
	dPrintf("\r\nPVR:%04x(%d)", GetPVR(), GetPVR());
	dPrintf("\r\nPanel H. Cycle:%04x(%d),  aa+ab+ac:%04x(%d)", php, php, sum, sum); 
	#endif //DEBUG_PC_MEAS

	if( php <= sum ) {
		ePuts("--not enough");

		#ifdef DEBUG_PC
		return FALSE;
		#endif //DEBUG_PC_MEAS
	}

	//=================================

	#ifdef SXGA
	switch( PcMode ) {
	case EE_RGB_576I:		case EE_YPbPr_576I:		php = 0x70f;	break;
	case EE_RGB_720P:		case EE_YPbPr_720P:		php = 0x623;	break;
	case EE_RGB_1080I:		case EE_YPbPr_1080I:	php = 0x618;	break;
	case EE_RGB_1080I50A:	case EE_YPbPr_1080I50A:	php -= 6;		break;
	}
	#endif //SXGA

	//=================================
	
	//------ Set PHP ----------
	SetPHP(php);

	return TRUE;
}
#else //AUTOCALC_PC
BYTE SetHValueForPanel(void)
{
	return TRUE;
}
#endif //AUTOCALC_PC
//-----------------------------------------------------------------------------
//		VAN = V Active Number
//		HAN = H active Number
//-----------------------------------------------------------------------------
BYTE GetActiveRegion(void)
{
	WORD	vstart;
	#ifdef REFERENCE
	#else //REFERENCE
	#ifndef WIDE_SCREEN
	WORD	vend;
	#endif //WIDE_SCREEN
	BYTE	cDelta =0;
	#endif //REFERENCE
	DWORD   pres, scale;
	DWORD	ppf;

	WORD	period, sync;

	//----- Set Measurement Wondow Size -----


	SetMeasureWindowV(1, 0x400);
	MeasureAndWait(3);

	// Set H window
	if( (PCMDATA[PcMode].VAN != GetPVR()) || !Flag4Bypass ) {	// --- Change hpulse & hpn ---
		period = ConvertBasedOnInput( GetHPN() );
		sync   = ConvertBasedOnInput( GetHSYNCPulse() );
	}
	else {
		period = GetCoarse();
		sync   = GetHSYNCPulse();
	}
	#ifdef REFERENCE
	SetMeasureWindowH(sync, period);
	#else //REFERENCE
	SetMeasureWindowH(sync, period + sync);
	#endif //REFERENCE
	// Set V window
	period = GetVPN();
	sync   = GetVSYNCPulse();
	SetMeasureWindowV(1, period);

	//----- Do Measurement ---------------------------
	MeasureAndWait(3);

	//----- Get VAN = Vertical Active Area -----------

	vstart = GetVerticalActiveArea();  // Measure Input Vstart, Vactive

	#ifndef REFERENCE
	SetMeasureWindowV(1, period);
	#else //REFERENCE
	SetMeasureWindowV(1, period  + sync);
	#endif //REFERENCE
	//----- Calculate Y-scale Factor, and save -------

	#if (defined WIDE_SCREEN)
	Set4WideScreen(GetWideModeEE());
	#else //WIDE_SCREEN
	{ //NORNAL SCREEN
		#ifdef REFERENCE
		pres = (DWORD)PVR_;
		scale = ((PCMDATA[PcMode].VAN * 0x10000L)+pres/2) / pres;
		#else //REFERENCE
		vstart  = GetVstart();
		vend   = GetVend();
		pres = (DWORD)PVR_;
		#ifdef XGA
		if (PcMode >= EE_XGA_60)
			scale = (((vend-vstart +1) * 0x10000L)+pres/2) / pres + 0x64;
		else if (PcMode == EE_SVGA_72)
			scale = ((PCMDATA[PcMode].VAN * 0x10000L)+pres/2) / pres;
		else
			scale = (((vend-vstart +1) * 0x10000L)+pres/2) / pres;	
		#else //XGA
		scale = (((vend-vstart +1) * 0x10000L)+pres/2) / pres;
		#endif //XGA
		#endif //REFERENCE
		Printf("\nVRes = %d\n", PCMDATA[PcMode].VAN );
		Printf("\nOutput VRes = %d\n", PVR_);
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n VAN=%04x  PVR=%04x", PCMDATA[PcMode].VAN, pres);
		dPrintf("\r\nYscaleFactor:%04x(%d)", scale, scale);
		#endif //DEBUG_PC_MEAS
	
		#ifndef WXGA
		if( scale==0x10000 && Flag4Bypass ) {		// Bypass
			BypassZoom();
		}
		else
		#endif //WXGA
		{
			Clear_bypass();
			YScale2(scale);						// save V Scale Up Factor
		}
	} // WIDE
	#endif //WIDE_SCREEN
	vstart = GetVactiveStart();
	//vstart = GetVstart();			// get from input measurement
	SetVValueForPanel(vstart);		// with VAN, Vstart with offset^^

	//----- Calcurate Panel H. Cycle(A9,AD) ----------

	ppf = GetPPF();

/**
	#ifdef DEBUG_PC_MEAS
	while( !SetHValueForPanel() )	{	// we need to use higher PPF

		ppf += 2700000;
		if( ppf > MAX_PPF ) {
			ePuts("\r\n\n--------------Too big IPF\r\n");
			return FALSE;
		}
		ChangeInternPLL(ppf);			// internal PLL
		#ifdef DEBUG_PC
		dPrintf("--> Increased PPF:%8ld", ppf);
		#endif
		delay(10);
	}
	#endif
/****/

	//----- Get HAN = Horizontal Active Area ---------

	GetHorizontalActiveArea();  

	if( (PCMDATA[PcMode].VAN != GetPVR()) || !Flag4Bypass) {	// non-bypass
		pres = (DWORD)GetPHR();
		#ifdef REFERENCE
		scale = ((PCMDATA[PcMode].HAN * 0x10000L )+pres/2) / pres;	// 256*han/phr
		#else //REFERENCE
		if ( PcMode <= EE_SP3)
		{
			LastHPN = GetCoarseValue();
			if  (LastHPN == PCMDATA[PcMode].CLOCK)
				scale = ((PCMDATA[PcMode].HAN * 0x10000L )+pres/2) / pres;	// 256*han/phr
			else 
			{
				if  (LastHPN < PCMDATA[PcMode].CLOCK)
				{
					cDelta = PCMDATA[PcMode].CLOCK - LastHPN;
					//Printf("xxx");
				}
				else if  (LastHPN > PCMDATA[PcMode].CLOCK)
				{
					cDelta = LastHPN - PCMDATA[PcMode].CLOCK;
					//Printf("ooo");
				}
				scale =(((PCMDATA[PcMode].HAN + cDelta) * 0x10000L )+pres/2) / pres;
			}
		}
		if ( PcMode <= EE_VGA_85)
		{
			scale = ((PCMDATA[PcMode].HAN * 0x10000L )+pres/2) / pres;	// 256*han/phr
		}
		else if ( PcMode <= EE_SVGA_85)
		{
			LastHPN = GetCoarseValue();
			if  (LastHPN == PCMDATA[PcMode].CLOCK)
				#ifdef XGA
				scale = ((PCMDATA[PcMode].HAN * 0x10000L )+pres/2) / pres + 64;	// 256*han/phr
				#else //XGA
				scale = ((PCMDATA[PcMode].HAN * 0x10000L )+pres/2) / pres;	// 256*han/phr
				#endif //XGA 
			else 
			{
				if  (LastHPN < PCMDATA[PcMode].CLOCK)
				{
					cDelta = PCMDATA[PcMode].CLOCK - LastHPN;
					//Printf("xxx");
				}
				else if  (LastHPN > PCMDATA[PcMode].CLOCK)
				{
					cDelta = LastHPN - PCMDATA[PcMode].CLOCK;
					//Printf("ooo");
				}
				scale =(((PCMDATA[PcMode].HAN + cDelta) * 0x10000L )+pres/2) / pres;
			}
				
		}
		else
		{
			scale = ((PCMDATA[PcMode].HAN * 0x10000L )+pres/2) / pres;	// 256*han/phr
			//scale = (PCMDATA[PcMode].HAN * 0x10000L ) / pres + pres/96;
		}
		#endif //REFERENCE
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\nPCMDATA[PcMode].HAN = %04x(%d), pres = %04x(%d)", PCMDATA[PcMode].HAN,PCMDATA[PcMode].HAN, pres, pres)  ;	// 256*han/phr
		dPrintf("\r\nXscaleFactor:%04x(%d)", scale, scale);
		#endif //DEBUG_PC_MEAS

		//#if (defined SXGA) || (defined WXGA) || (defined WSGA)
		#ifdef XGA
		if( PCMDATA[PcMode].HAN == 1024 ) {//1100
			scale = (PCMDATA[PcMode].HAN * 0x80L ) / 1024 + 1;		// (HAN/1024)*256
			XscaleD(scale);
			scale = ((PCMDATA[PcMode].HAN -8) * 0x10000L ) / 1024;						// (1024/PHR)*256
			XscaleU(scale);
		}
		else if( PCMDATA[PcMode].HAN > 1024 )
		{
			scale = (PCMDATA[PcMode].HAN * 0x80L ) / 1024 + 1;		// (HAN/1024)*256
			XscaleD(scale);
			scale = (1024 * 0x10000L ) / 1024;						// (1024/PHR)*256
			XscaleU(scale);
		}
		#else //XGA
		if( PCMDATA[PcMode].HAN > 1024 ) {//1100
			scale = (PCMDATA[PcMode].HAN * 0x80L ) / 1024 + 1;		// (HAN/1024)*256
			XscaleD(scale);
			#ifdef DEBUG_PC_MEAS
			dPrintf("\r\nXscaleFactorD:%04x(%d)", scale, scale);
			#endif //DEBUG_PC_MEAS
			scale = (1024 * 0x10000L ) / 1280;						// (1024/PHR)*256
			XscaleU(scale);
			#ifdef DEBUG_PC_MEAS
			dPrintf("\r\nXscaleFactorU:%04x(%d)", scale, scale);
			#endif //DEBUG_PC_MEAS
		}
		#endif //XGA
		else
		//#endif
		{
	#ifdef WIDE_SCREEN
		if(WideScreenMode == WIDESCREEN_WIDE)
	#endif // WIDE_SCREEN
			XScale2(scale);
		}
	}

	return TRUE;
}
/*===========================================================================*/
/*					  Display The Result for Debugging			             */
/*===========================================================================*/
void DisplayResultAndSetActiveRange(void)
{

	WORD	Back, Front;

	//------- Display the Result ---------------------

	#ifdef DEBUG_PC_MEAS
	dPuts  ("\r\n-------------------------------------------");
	dPrintf("\r\n   Resolution    = %d x %d (%s)", PCMDATA[PcMode].HAN, PCMDATA[PcMode].VAN, PcModeStr[PcMode]);
	dPrintf("\r\n   IVF(Refresh)  = (%d)", IVF);
	dPrintf("\r\n   IHF           = %08lx (%ld)", IHF, IHF);
	dPrintf("\r\n   IHPN(PLLdiv)  = %04x(%d) %02x", GetCoarse(), GetCoarse(), (WORD)GetPhaseCurrent() );
	dPrintf("\r\n   VPN           = %04x(%d)", GetVPN(), GetVPN() );
	dPrintf("\r\n   PPF           = %ld / 2 = %ld", GetPPF(), GetPPF()/2 );
	dPrintf("\r\n   IPF           = %ld", IHF * GetCoarse() );
	#endif //DEBUG_PC_MEAS

	//----- calculate H Pos Range
	Back  = GetHactiveStart() - GetHSYNCPulse();
	Front = GetCoarse() - PCMDATA[PcMode].HAN - GetHactiveStart();

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nH  ~~~|_%d_|~%d~", (WORD)GetHSYNCPulse(), (WORD)Back );
	dPrintf(":+++ %d +++:~%d~|_%d_|~~~ ",  (WORD)PCMDATA[PcMode].HAN, (WORD)Front, (WORD)GetHSYNCPulse() );
	#endif //DEBUG_PC_MEAS

	/*
	if( (Back>50) && (Front>50) ) {
		Back = 50;
		Front = 50;
	}
	else if( Back+Front>=100 ) {
		if( Back>Front )
			Back = 100 - Front;
		else if( Front>Back ) 
			Front = 100 - Back;
	}

	HPosCurr = (BYTE)Back;
	HPosMax  = (BYTE)(Back + Front);
	*/
	HPosCurr = (WORD)Back;
	HPosMax = Back + Front;
	//----- calculate V Pos Range
	Back  = GetVactiveStart() - GetVSYNCPulse();
	//Back  = GetVstart() - GetVSYNCPulse();
	Front = GetVPN() - PCMDATA[PcMode].VAN - GetVactiveStart();
	//Front = GetVPN() - PCMDATA[PcMode].VAN - GetVstart();

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nV  ~~~|_%d_|~%d~", (WORD)GetVSYNCPulse(), Back );
	dPrintf(":+++ %d +++:~%d~|_%d_|~~~ ",  PCMDATA[PcMode].VAN, Front, (WORD)GetVSYNCPulse() );
	dPuts  ("\r\n-------------------------------------------");
	#endif //DEBUG_PC_MEAS

	VPosCurr = Back-4;

	if( Front <= 0 )
		VPosMax = VPosCurr+1;
	else
		VPosMax = VPosCurr + Front;

}
/*===========================================================================*/
/*						  Real Measurement routine				             */
/*===========================================================================*/
BYTE DoMeasurement(void)
{
	WORD coarse;

	//------------------------ Clock Tuning -------------------------------
	#ifdef DEBUG_PAUSE
	Printf("coarse = AutoTuneClock()");
	#endif //DEBUG_PAUSE

	coarse = AutoTuneClock();			// plldiv
	if( coarse == 0 ) {
		ePuts("\r\nToo big IPF");
		MeasureAndWait(3);
		return FALSE;
	}


	//-------------------------- Fine Tuning ------------------------------

	AutoTunePhase();
	
	//-------------------------- Get Active Region ------------------------
	if( !GetActiveRegion() ) {

		GetPCDataEE(PcMode);

		MeasureAndWait(3);
		return FALSE;
	}

	//-------------------------- Display Result ---------------------------
	DisplayResultAndSetActiveRange();

	return TRUE;
}

//#ifdef SUPPORT_DTV
void RGBModeFieldDetect(BYTE flag)
{
	BYTE val;

	val = ReadTW88(0x42);
	if( flag ) val = val | 0x80;
	else       val = val & 0x7f;
	WriteTW88( 0x42, val);
}
//#endif

#include "data\DTV_PC.txt"

/*===========================================================================*/
/*                                                                           */
/*===========================================================================*/
BYTE SetADCandInputRegisterByVGAMode(BYTE mode)
{

	CODE_P BYTE *reg=0;
	BYTE fielddetect=0, ret;

	SetCoarse( PCMDATA[mode].CLOCK );
//	ret = SetVCORange(IHF * PCMDATA[mode].CLOCK);	
	ret = SetVCORange(PCMDATA[mode].IPF * 100000L);	

	{
		switch (mode) {
		case EE_RGB_480I:		
		case EE_RGB_576I:		
		case EE_RGB_1080I:		
		case EE_RGB_1080I50A:
								#ifdef ADD_ANALOGPANEL
								if(IsAnalogOn())reg = DTV_RGB_480I_Reg_Analog; 
								else
								#endif	 //ADD_ANALOGPANEL	
								reg = DTV_RGB_480I_Reg;	fielddetect = 1;	break;
		case EE_RGB_576P:
		case EE_RGB_480P:
								#ifdef ADD_ANALOGPANEL
								if(IsAnalogOn())reg = DTV_RGB_480P_Reg_Analog; 
								else
								#endif	//ADD_ANALOGPANEL	
								reg = DTV_RGB_480P_Reg; 
		
								fielddetect = 0;	break;
		case EE_RGB_720P50:		
		case EE_RGB_720P:
								reg = DTV_RGB_720P_Reg; fielddetect = 0;	break;
		default:				reg = PC_RGB_ADC_Reg; fielddetect = 0;	break;
		}
		
	}

	RGBModeFieldDetect(fielddetect);
	if( reg ) I2CDeviceInitialize( reg );

	return ret;

}
#ifdef SUPPORT_DTV
/*===========================================================================*/
/*                                                                           */
/*===========================================================================*/
BYTE SetADCandInputRegisterByDTVMode(BYTE mode)
{

	CODE_P BYTE *reg=0;
	BYTE fielddetect=1, ret;
	WORD	width, height;
	DWORD	scale;

	WriteADC_TW88(0xc6, 0x20);
	ret = SetVCORange(PCMDATA[mode].IPF * 100000L);	
	SetCoarse( PCMDATA[mode].CLOCK );

	switch (mode) {
		case EE_YPbPr_480I:		reg = DTV_YPbPr_480I_Reg;		break;
		case EE_YPbPr_576I:		reg = DTV_YPbPr_576I_Reg;		break;
		case EE_YPbPr_480P:		reg = DTV_YPbPr_480P_Reg;		break;
		case EE_YPbPr_576P:		reg = DTV_YPbPr_576P_Reg;		break;
		case EE_YPbPr_720P:		reg = DTV_YPbPr_720P_Reg;		break;
		case EE_YPbPr_720P50:	reg = DTV_YPbPr_720P50_Reg;		break;
		case EE_YPbPr_1080I:	reg = DTV_YPbPr_1080I_Reg;		break;
		case EE_YPbPr_1080I50A:	reg = DTV_YPbPr_1080I50A_Reg;	break;
		case EE_YPbPr_1080I50B:	reg = DTV_YPbPr_1080I50B_Reg;	break;
		// default: reg = DTV_YPbPr_480I_Reg;	width = 706;	height = 240;	break;				// default no input setting
	}

	RGBModeFieldDetect(1);		// always detect
	Printf("\r\nMODE: %d", (WORD)mode);
	if( reg ) {
		I2CDeviceInitialize( reg );
		WriteTW88(0xB9, PCMDATA[mode].VBack );			// important for panel setting
		height = PCMDATA[mode].VAN;						// using table for calc
		width = PCMDATA[mode].HAN;
		scale = width;
		scale *= 0x10000L;				
		scale /= PWIDTH;
		XScale2(scale);
		//#ifdef DEBUG_DTV
		Printf("\r\nMODE: %d, width: %d, H scale: %xh - %xh", (WORD)mode, width, (WORD)(scale>>8), (WORD)(scale & 0xff));
		//#endif

		scale = height;
		scale *= 0x10000L;
		scale /= PHEIGHT;
		YScale2(scale);
		#ifdef DEBUG_DTV
		Printf("\r\nMODE: %d, height: %d, V scale: %xh - %xh", (WORD)mode, height, (WORD)(scale>>8), (WORD)(scale & 0xff));
		#endif //DEBUG_DTV
	}

	//delay(250);
	//WriteADC_TW88(0xc6, 0x27);
	return ret;
}

/*===========================================================================*/
/*                                                                           */
/*===========================================================================*/
BYTE DetectAndSetForDTVInput(BYTE eflag)		// 0: measure 	 Range4Coarse=0
												// 1: check EEP  Range4Coarse=0
												// 2: measure    Range4Coarse=1
												// 3: restore EEP
{
	bit VCORangeChged;
	/*
	BYTE  i;
	WORD vpn, vpn1, ivf;
	*/
#ifdef REFERENCE
#else //REFERENCE
	cLastSyncLoss = 0;
#endif //REFERENCE
	if (eflag > 3) return FALSE;
	Printf("\r\n 0xd0=%2x", (WORD)ReadTW88(0xd0));
	if (( ReadTW88(0xD0) & 0x01 ) == 0) {
		DisplayPCInfo(CheckDTVCableStr[GetOSDLang()]);
		PcMode = EE_PC_UNKNOWN;		// no signal
		#ifdef DEBUG_DTV
		Puts("\r\nCheck DTV Cable.....");
		#endif //DEBUG_DTV
		PanelFreeRun(1);
		PanelBlack(1);
		return FALSE;
	}
	#ifdef DEBUG_DTV
	Printf("\r\nDetectAndSetForDTVInput_eflag: %2x,", (WORD)eflag);
	#endif //DEBUG_DTV
//	if( DebugLevel<3 && (eflag==1 || eflag==3) ) 	LCDPowerOFF();//PanelMute(1); 

	PcMode = DetectDTVInputSource();
	VCORangeChged = SetADCandInputRegisterByDTVMode(PcMode);
	//ChangeInternPLL(PCMDATA[PcMode].PPF * 100000L);	// Set PPF (Internal PLL)

	return TRUE;

}
#endif //SUPPORT_DTV
/*===========================================================================*/
/*                                                                           */
/*===========================================================================*/
BYTE DetectAndSetForVGAInput(BYTE eflag)		// 0: measure 	 Range4Coarse=0
												// 1: check EEP  Range4Coarse=0
												// 2: measure    Range4Coarse=1
												// 3: restore EEP
{

	bit VCORangeChged;
	BYTE  i;
	WORD vpn, vpn1, ivf;

	cLastSyncLoss = 0;

	if (( ReadTW88(0xD0) & 0x01 ) == 0) {
		DisplayPCInfo(CheckPCCableStr[GetOSDLang()]);
		PcMode = EE_PC_NO_SIGNAL;		// no signal
		#ifdef DEBUG
		Puts("\r\nCheck PC Cable.....");
		#endif //DEBUG	
		PanelFreeRun(1);
		PanelBlack(1);
		return FALSE;
	}
	WriteTW88( 0x44, (ReadTW88(0x44)&0xf3)|0x08 );		// set mode to YUV - direct path

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\nDetectAndSetForVGAInput_eflag: %2x,", (WORD)eflag);
	#endif //DEBUG_PC_MEAS


	//---------- Set Panel constant reg.------------------

	WriteTW88( 0x5c, (ReadTW88(0x5c) & 0x0f) | 0x30 );	// Noise Mask: 3
	WriteTW88( 0x5d, (ReadTW88(0x5d) & 0x0f) | 0x30 );	// active detect threshold: 3

	AutoPHPCalEnable();

	WriteTW88( 0xbd, 8 );				// Vdelay=8
	WriteTW88( 0xb8, 6 );				// Vsync Pulse Width

	//------- Assume the PC_XGA input, 60Hz Refresh -----------------
	WriteTW88( 0xff, 1 );		//set page 1
	if ( ReadTW88( 0xc1 ) & 0x40 )
	{	// HSYNC POL ?
		dPuts("\r\ninvert CSYNC det pol");
		WriteTW88( 0xc0, 0x18 );		//CSYNC det input polarity reverse
	}
	else 
	{
		WriteTW88( 0xc0, 0x38 );		//CSYNC det input polarity reverse
	}
	if ( ReadTW88( 0xc1 ) & 0x80 ){	// VSYNC POL ?
		dPuts("\r\nNo invert VSYNC pol");
		WriteTW88( 0xcc, 0x1F );		//CSYNC det input polarity reverse
	}
	else {
		WriteTW88( 0xcc, 0x1d );		//CSYNC det input polarity reverse
	}
	WriteTW88( 0xff, 0 );

	SetMeasureWindowH(1, 1400);		// default window to 1400
	SetMeasureWindowV(1, 1200);		//1200

	//if ( eflag == 1 ) return 0;

	#ifdef DEBUG_PAUSE
	Pause("GetHpnVpn_before{CR}");
	#endif //DEBUG_PAUSE
	vpn = GetHpnVpn(1);					// VPN, IVF 
	ivf = IVF;

	//------- Estimate IPF and Set VCO Range (ADC) ---------------
	i=0;
	do {
		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n=========================== LOOP:%d", (WORD)i);
		#endif //DEBUG_PC_MEAS
		#ifdef DEBUG_PAUSE
		Pause("DecideVGAInputSource{CR}");
		#endif //DEBUG_PAUSE
		PcMode = DecideVGAInputSource(vpn, IVF);		// check with vertical line and IVF
		#ifdef XGA
		if (PcMode <= EE_SP3)
			WriteTW88( 0xb1, ReadTW88(0xb1) |4);
		else
			WriteTW88( 0xb1, ReadTW88(0xb1) & 0xf8);
		if (PcMode == EE_VGA_72)
			WriteTW88( 0xb8, 5 );				// Vsync Pulse Width
		#endif //XGA

		#ifdef DEBUG_PC_MEAS
		dPrintf("\r\n-----> Detect PCMODE: %d", (WORD)PcMode);
		#endif //DEBUG_PC_MEAS
		if( PcMode==EE_PC_UNKNOWN ) { 
			#ifdef DEBUG_PC
			dPuts("\r\n-----> PC_UNKNOWN");
			#endif //DEBUG_PC
			if( vpn<200 ) vpn = 250;	// HHY 1.62 if coarse value is too small, ADC is malfunctioned.
			VCORangeChged = SetVCORange( IHF * (vpn/3)*4 );	
			SetCoarse(vpn/3*4);						// HHY 1.43
		}
		else if( PcMode==EE_PC_NO_SIGNAL ) {
			#ifdef DEBUG_PC
			dPuts("\r\n-----> Sync Loss");
			#endif //DEBUG_PC
			if( GetInputSelection()==PC ) goto Failure;
		}
		else {
			#ifdef DEBUG_PC_MEAS
			dPuts("\r\n-----> Find PC mode");
			#endif //DEBUG_PC_MEAS
			if( eflag==1 || eflag==3 ) {	// HHY 2.01
				VCORangeChged = SetADCandInputRegisterByVGAMode(PcMode);
			
				#ifdef DEBUG_PC_MEAS
				dPrintf("\r\n   ---->>> Set Initial value by detected mode[%d]", (WORD)PcMode);
				#endif //DEBUG_PC_MEAS
			}
			if ( PcMode < 28 ) {
				#ifdef DEBUG_PC_MEAS
				dPuts("\r\n-----> stop searching...................");
				#endif //DEBUG_PC_MEAS
			   	break;
			}
			#ifdef REFERENCE
			#else
			else
			{
				WriteTW88( 0x40, ReadTW88(0x40) & 0xdf);
			}
			#endif 				
		}

		vpn1 = GetHpnVpn(1);						// VPN, IVF ***

		if( vpn1==0 ) {
			#ifdef DEBUG_PC
			dPrintf("\r\n   ---> Error at GetHpnVpn line:%d", __LINE__);
			#endif //DEBUG_PC
			goto Failure;
		}

		// Check SYNC Loss	// HHY 1.47
		if( PcMode == EE_PC_UNKNOWN ) {
			StartNewDetect();
			if( (ReadTW88(0xd0) & 0x06) )  {
				PcMode = EE_PC_NO_SIGNAL;
				#ifdef DEBUG_PC
				ePuts("\r\n-----> Sync Loss");
				#endif //DEBUG_PC
				if( GetInputSelection()==PC ) goto Failure;
			}
		}

		vpn = vpn1;
		ivf = IVF;

		i++;
	} while( ( (PcMode==EE_PC_UNKNOWN) || VCORangeChged) && i<5 );	// by getting valid VPN

	if( PcMode==EE_PC_UNKNOWN ) goto Failure;
	if( PcMode==EE_PC_NO_SIGNAL) goto Failure;


	//==================================
	#ifdef ADD_ANALOGPANEL
	if(IsAnalogOn()) return TRUE;
	#endif //ADD_ANALOGPANEL

	//---------------------------------------------------------------------

	#ifdef DEBUG_PAUSE
	Pause("ChangeInternPLL(PCMDATA[PcMode].PPF * 100000L){CR}");
	#endif //DEBUG_PAUSE
	ChangeInternPLL(PCMDATA[PcMode].PPF * 100000L);	// Set PPF (Internal PLL)

	//---------------------------------------------------------------------

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n eflag = %d PcMode = %d(%s)", (WORD)eflag, (WORD)PcMode, PcModeStr[PcMode] );
	#endif //DEBUG_PC_MEAS

	//==================================
	#ifdef DEBUG_PAUSE
	Pause("Measure_VPN_IHF(&LastVPN, &LastIHF){CR}");
	#endif //DEBUG_PAUSE
	Measure_VPN_IHF(&LastVPN, &LastIHF);

	ivf = (LastIHF + LastVPN/2) / LastVPN;

	// Check if PcMode same as before
	#ifdef DEBUG_PAUSE
	Pause("i = DecideVGAInputSource(LastVPN, ivf){CR}");
	#endif //DEBUG_PAUSE
	i = DecideVGAInputSource(LastVPN, ivf);
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n  --> Detect PcMode again:%d[%s]", (WORD)i, PcModeStr[i] );
	#endif //DEBUG_PC_MEAS
	if( PcMode != i )  {
		#ifdef DEBUG_PC_MEAS
		dPrintf("  --- New PcMode=%d  i=%d", (WORD)PcMode, (WORD)i);
		#endif //DEBUG_PC_MEAS
		LastVPN = 0;
		LastIHF = 0;
		PcMode = EE_PC_UNKNOWN;
		goto Failure;
#ifdef REFERENCE
		return FALSE;
#endif //REFERENCE
	}

	//==================================

	if( (eflag==3) || (eflag==1) ) {

		//==================
		GetPCDataEE(PcMode);

		goto Success;

	}
	else {
		switch( eflag ) {
		case 0: Range4Coarse = 0; break;
		case 1: Range4Coarse = 0; break;
		case 2: Range4Coarse = 1; break;
		}

//		SetADCGainOffset(0x80, 0xd0);
//Abnormal_Test:

		//--------------------
		#ifdef DEBUG_PAUSE
		Pause("i = DoMeasurement(){CR}");
		#endif //DEBUG_PAUSE
		i = DoMeasurement(); 			// *** Coarse, Fine, Active
		//--------------------
//		i = 1;

		if( i ) goto Success;
		else	goto Failure;
	}

Success:
	//==============================================

	WriteTW88( 0x44, (ReadTW88(0x44)&0xf3)|0x0c );		// set mode to RGB
	if( (ReadTW88(0xd0) & 0x06) )  {
		#ifdef DEBUG_PC
		ePuts("\r\n---> Finish, but Sync Loss");
		#endif //DEBUG_PC
#ifdef REFERENCE

		LastVPN = 0;
		LastIHF = 0;
		PcMode = EE_PC_NO_SIGNAL;
		return FALSE;
#else //REFERENCE
		goto Failure;
#endif //REFERENCE
	}
	else {
		ClearPCInfo();
		if( eflag==0 || eflag==2 ) SavePCDataEE(PcMode);

		WriteTW88( 0xd0, 0xff );
		WriteTW88( 0xd1, 0xff );
		
		return TRUE;
	}

Failure:

	WriteTW88( 0x44, (ReadTW88(0x44)&0xf3)|0x0c );		// set mode to RGB
	WriteDecoder( ACNTL, ReadDecoder(ACNTL) | 0x80 );		// SW reset, because sometimes unstable
#ifdef REFERENCE
	PcMode = EE_PC_UNKNOWN;
	if( (ReadTW88(0xd0) & 0x06) ) {
#else //REFERENCE
	if((ReadTW88(0xd0) & 2) || (ReadTW88(0xd0) & 4)){
#endif //REFERENCE
		PcMode = EE_PC_NO_SIGNAL;

		#ifdef DEBUG_PC
		ePuts("\r\n-----> Out Of Range, but Sync Loss");
		#endif

		LastVPN = 0;
		LastIHF = 0;
#ifdef REFERENCE
#else //REFERENCE
		DisplayPCInfo(CheckPCCableStr[GetOSDLang()]);
		PanelFreeRun(1);
		PanelBlack(1);
		Printf("aaaaa0");
#endif //REFERENCE
		return FALSE;
	}
	else {
#ifdef REFERENCE
#else //REFERENCE
		PcMode = EE_PC_UNKNOWN;
#endif //REFERENCE
		GetHpnVpn(0);

		if( !Measure_VPN_IHF(&LastVPN, &LastIHF) ) {
			LastVPN = 0;
			LastIHF = 0;

			return FALSE;
		}
		IVF = (LastIHF + LastVPN/2) / LastVPN;

		if( PcMode != DecideVGAInputSource(LastVPN, IVF) )  {
			LastVPN = 0;
			LastIHF = 0;
#ifdef REFERENCE
			PcMode = EE_PC_UNKNOWN;
			return FALSE;
#endif //REFERENCE
		}

		DisplayPCInfo(OutOfRangeStr[GetOSDLang()]);
		LastVPN = 0;
		LastIHF = 0;
		PanelFreeRun(1);
		PanelBlack(1);
	}
	return FALSE;
	}
/*****************************************************************************/
/*				  PC Function Main - called by main periodically             */
/*****************************************************************************/
void CheckPCinput(void)
{
	extern  BYTE InputSelection;
	BYTE statusD0, statusD1, i, page;
	


	DWORD	dwIHF;
	WORD	wIVF;
	WORD	vpn;
	BYTE	cCurrentPCMode;
	BYTE	InputDetectiontemp;
	//===================== HSYNC/VSYNC loss ========================

	page = ReadTW88( REG_PAGE);
	WriteTW88( REG_PAGE, 0 );	
	statusD0 = ReadTW88(0xd0);
	statusD1 = ReadTW88(0xd1);
	InputDetectiontemp=ReadADC(0xc1);
#if 0	
#ifdef REFERENCE
	if( statusD0 & 0x06 ) {		// 
		if ( PcMode == EE_PC_NO_SIGNAL )	return;		// before state is "no signal"
		for(i=0; i<3; i++) {
			#ifdef DEBUG_PC
			ePrintf("\r\nSync Loss cnt=%d", (WORD)i);
			#endif //DEBUG_PC
			WriteTW88( 0xd0, 0xff);	// clear status
			WriteTW88( 0xd1, 0xff);	// clear status
			statusD0 = ReadTW88(0xd0);
			if( statusD0 & 0x06 ) 
				delay(1);
			else {
				WriteTW88( REG_PAGE, page );	// save back to page
				return;
			}
		}
		PcMode = EE_PC_NO_SIGNAL;		// no signal
		//PanelBlack(1);
		ClearLogo();
		DisplayPCInfo(CheckPCCableStr[GetOSDLang()]);
		//PanelBlack(1);
		#ifdef DEBUG_PC
		Puts("\r\nLost PC signal, Check Cable.....");
		#endif //DEBUG_PC
		WriteTW88( REG_PAGE, page );	// save back to page
		return;
	}
	else if ( (statusD1 & 0x30) == 0x30) {		// means VSYNC & HSYNC changed

		#ifdef DEBUG_PC
		Puts("\r\nPC mode change detected, waiting for stable");
		#endif //DEBUG_PC
		i = 0;
		do {
			delay(100);				// wait 0.1sec
			WriteTW88( 0xd0, 0xff);	// clear status
			WriteTW88( 0xd1, 0xff);	// clear status
			statusD0 = ReadTW88(0xd0);
			statusD1 = ReadTW88(0xd1);
			i++;
			if ( i > 10 ) {
				WriteTW88( REG_PAGE, page );	// save back to page
				#ifdef DEBUG_PC
				Puts("\r\ncannot find stable value...........");
				#endif //DEBUG_PC
				return;
			}
		} while ( statusD1 & 0x30 );

		#ifdef DEBUG_PC
		Puts("\r\nPC mode change detected........");
		#endif //DEBUG_PC
		i = InputSelection;
		InputSelection--;
		ChangeInput( i );
		delay(100);

		WriteTW88( 0xd0, 0xff);	// clear status
		WriteTW88( 0xd1, 0xff);	// clear status
	}
#else //REFERENCE
#endif
#endif
	//Printf("\r\nPcMode=%x",(WORD)PcMode);

	if ( PcMode == EE_PC_UNKNOWN)
	{
		if(!cLastSyncLoss) 
		{
			DisplayPCInfo(OutOfRangeStr[GetOSDLang()]);
			PanelFreeRun(1);
			PanelBlack(1);
			cLastSyncLoss = 1;
		}
	}
	if((statusD0 & 2) || (statusD0 & 4)) 
	{		
		if ( PcMode == EE_PC_NO_SIGNAL)
		{
			if(!cLastSyncLoss) 
			{
				DisplayPCInfo(CheckPCCableStr[GetOSDLang()]);
				PanelFreeRun(1);
				PanelBlack(1);
				cLastSyncLoss = 1;
			}
			return;
		}	
		for(i=0; i<3; i++) 
		{
			WriteTW88( 0xd0, 0xff);	// clear status
			WriteTW88( 0xd1, 0xff);	// clear status
			statusD0 = ReadTW88(0xd0);
			if((statusD0 & 2) || (statusD0 & 4)) 
				delay(100);
		}
		PcMode = EE_PC_NO_SIGNAL;		// no signal
		WriteTW88( 0xd0, 0xff);	// clear status
		WriteTW88( 0xd1, 0xff);	// clear status
		DisplayPCInfo(CheckPCCableStr[GetOSDLang()]);
		PanelFreeRun(1);
		PanelBlack(1);
		//ClearLogo();
		WriteTW88( REG_PAGE, page );	// save back to page
		return;
	}
	else if ( (statusD1 & 0x10) ||(statusD1 & 0x20) ||(statusD1 & 1)) 
	{		// means VSYNC & HSYNC changed
		i = 0;
		do {
			delay(100);				// wait 0.1sec
			WriteTW88( 0xd0, 0xff);	// clear status
			WriteTW88( 0xd1, 0xff);	// clear status
			statusD0 = ReadTW88(0xd0);
			statusD1 = ReadTW88(0xd1);
			i++;
			if ( i > 10 )
			{
				WriteTW88( REG_PAGE, page );	// save back to page
				return;
			}
		} while ( (statusD1 & 0x10) ||(statusD1 & 0x20) || (statusD1 & 1)) ;
		i = InputSelection;
		InputSelection--;
		ClearPCInfo();
		ChangeInput(i);
		return;
	}
		//>>>>>>>>>>>>>>>>>>>>>>>>william-20110429
	else if(InputDetectiontemp!=InputDetection)
		{
		Printf("\r\n-> InputDetectiontemp:=%02x,InputDetection:=%02x", InputDetectiontemp, InputDetection);
		i = InputSelection;
		InputSelection--;
		ClearPCInfo();
		ChangeInput(i);
		InputDetection=InputDetectiontemp;
		}
	//>>>>>>>>>>>>>>>>>>>>>>>>william-20110429
	// solve to change timing is fast at unstable sync
	// 2009.01.16 start
	MeasureAndWait(3);
	//----- Get New HPN -------------
	dwIHF = (GetPPF()+GetHPN()/2) / GetHPN();		// IHF = PPF / HPN 
	MeasureAndWait(3);
	//----- Get New VPN -------------
	wIVF = (WORD)((IHF+GetVPN()/2)/GetVPN());		// IVF = IHF / VPN 
	if((abs(IHF -dwIHF) > 500) ||(abs(IVF -wIVF) >= 2))
	{
		i = InputSelection;
		InputSelection--;
		delay(100);				// wait 0.1sec
		ClearPCInfo();
		ChangeInput( i );
		WriteTW88( REG_PAGE, page );	// save back to page
		return;
	}
	vpn = GetHpnVpn(1);					// VPN, IVF 
	cCurrentPCMode = DecideVGAInputSource(vpn, IVF);		// check with vertical line and IVF
	if (cCurrentPCMode != PcMode)
	{
		i = InputSelection;
		InputSelection--;
		ClearPCInfo();
		ChangeInput(i);
		page = ReadTW88( REG_PAGE );
		WriteTW88( REG_PAGE, 0 );	
		delay(100);
		WriteTW88( 0xd0, 0xff);	// clear status
		WriteTW88( 0xd1, 0xff);	// clear status
	}
	// 2009.01.16 end
	WriteTW88( REG_PAGE, page );	// save back to page
}
#ifdef SUPPORT_DTV
/*****************************************************************************/
/*				  DTV Function Main - called by main periodically            */
/*****************************************************************************/
void CheckDTVinput(void)
{
	extern IDATA BYTE InputSelection;
	//BYTE statusD0, statusD1, i, page;
	BYTE i;
	
	//===================== HSYNC/VSYNC loss ========================
	if ((ReadTW88(0xD0) & 0x01) == 0) 
	{
		if(!cLastSyncLoss) 
		{
			DisplayPCInfo(CheckDTVCableStr[GetOSDLang()]);
			PcMode = EE_PC_UNKNOWN;		// no signal
			#ifdef DEBUG_DTV
			Puts("\r\nCheck DTV Cable.....");
			#endif //DEBUG_DTV
			PanelFreeRun(1);
			PanelBlack(1);
			cLastSyncLoss = 1;
		}
		return;
	}
	i = DetectDTVInputSource();
	if ( PcMode == i ) return;			// no input change
	cLastSyncLoss = 0;
	i = InputSelection;
	InputSelection--;
	ChangeInput( i );

}
#endif //SUPPORT_DTV
CODE_P BYTE *GetPCInputSourceName(void)
{
	BYTE *ptr;

	if( PcMode<EE_PC_MAX ) ptr = PcModeStr[PcMode];
	else                   ptr = (CODE_P BYTE *)"";

	#ifdef DEBUG
	dPrintf("\r\n++(GetPCInputSourceName)=<%s>", ptr);
	#endif //DEBUG

	return ptr;
}

BYTE AutoAdjust(void)
{
	BYTE ret=0;

	WriteTW88( 0xff, 0 );			// set page 0
	ClearOSDInfo();
	DisplayAutoAdjust();
	ret = DetectAndSetForVGAInput(0);	
	ClearAutoAdjust();
	LCDPowerON(0);	//HHY 1.63
	WriteTW88( 0xd0, 0xff );
	WriteTW88( 0xd1, 0xff );

	return ret;
}						
#endif //defined( SUPPORT_PC ) || defined( SUPPORT_DTV )











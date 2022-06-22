#include "Config.h"

#include "reg.h"
#include "typedefs.h"
#include "i2c.h"
#include "main.h"
#include "tw88.h"
#include "debug.h"
#include "etc_eep.h"
#include "pc_eep.h"
#include "measure.h"
#include "adc.h"
#include "CPU.h"
#include "Printf.h"
#include "rgbmix.h"		// for TW8801
#include "panel.h"
#include "osdmenu.h"
#include "osdbasic.h"
#include "Externs.h"
#include "audio.h"
#include "HS_keyremo.h"

///extern IDATA BYTE adc_i2c_address, CurrentADC;
//extern	BYTE  CheckBuf;
static 	BYTE m_cStandard= 0;
extern BYTE SelectBoxMode;
BYTE CAM_QUAD_TO=3;//ryan@20170928
BYTE Backlight_TO=50;//ryan@20170928

//=============================================================================
//						Auto Detect
//=============================================================================
void SetAutoDetectStd(void)
{
	BYTE val;

//	if( GetInputSelection()==COMPONENT ) return;

	dPuts("\r\nSetAutoDetectStd");
	val = 0x80 | GetPossibleAutoDetectStdEE();		//AutoDetectStd
	WriteDecoder(SDTR, val);		// SDTR
	val = ReadDecoder(SDT);			// SDT
	WriteDecoder(SDT,  val | 0x07);	// SDT
}

void ClearAutoDetectStd(BYTE std)
{
	BYTE val;

//	if( GetInputSelection()==COMPONENT ) return;

	dPuts("\r\nClearAutoDetectStd");

	val = ReadDecoder(SDT);	// SDT
	val = (val & 0xf8) | std;
	WriteDecoder(SDT,  val );
}
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
//=============================================================================
//						Auto Panel H Period Control
//=============================================================================
void AutoPHPCalEnable(void)
{
	#ifdef DEBUG
	dPuts("\r\n +++++++++++++++++=>Auto PHP Enable");
	#endif
	WriteDecoder( 0xb6, (ReadDecoder(0xb6) & 0x7f) );	// Auto PHP Enable
	WriteDecoder( 0xb2, ReadDecoder(0xb2) );

}

void AutoPHPCalDisable(void)
{
	#ifdef DEBUG
	dPuts("\r\n +++++++++++++++++=>Auto PHP Disable");
	#endif
	WriteDecoder( 0xb6, (ReadDecoder(0xb6) | 0x80) );	// Auto PHP Disable
	WriteDecoder( 0xb2, (ReadDecoder(0xb2)));

}
#endif

//=============================================================================
//	                        Video Input Functions   
//=============================================================================
//=============================================================================
//	                        Detect Video System by Decoder
//=============================================================================
#ifndef ID_CHECK_BY_FW
BYTE DetectDecoderInput(void)
{
	BYTE std;
	BYTE val;

	//----- Check No Input
	val = ReadDecoder(CSTATUS);		// Decoder status Register
	if( (val & 0xc0) != 0x40 ) {	// no decoder input
		std = NOINPUT;
		return std;
	}
	//----- Check Color System by decoder
	for ( std=0; std<10; std++ ) {
		val = ReadDecoder(SDT);				// SDT:0x1c
		#ifdef DEBUG_DECODER
		Printf("\r\nReadDecoder(0x1c): 0x%X", (WORD)val);
		#endif
		if ( val & 0x80 ) {
			delay(10);
		}
		else {
			val >>= 4;
			if ( val == 0x07 ) return (UNKNOWN);
			else return (val+1);
		}
	}
//	if( val & 0x80 ) {					// Detection in proress
//		std = UNKNOWN;
//	}
//	else {
//		val >>= 4;
//		if( val==0x07 ) std = UNKNOWN;
//		else            std = val + 1;
//	}

	#ifdef DEBUG_DECODER
	Printf("\r\nStill Detection in Progress, so return UNKNOWN: 0x%X", (WORD)val);
	#endif
	return UNKNOWN;
}
#endif	// ID_CHECK_BY_FW

//=============================================================================
//	                        Change Input 
//=============================================================================

void COMPOSITE1Input(void)
{
	WriteDecoder(INFORM, 0xC0);			// 01 00 00 x x		27M, COMPOSITE, Y0, C-, V-
	WriteDecoder(ACNTL, 0x03);	// CLK-on, Y-on, C-off, V(FB)-off	
	WriteDecoder(MISC3, ReadDecoder(MISC3)|0x06); 
}

#ifdef QUAD  //Pinchi 20150414 add
void COMPOSITE2Input(void)
{
	WriteDecoder(INFORM, 0xC6);			// 01 00 00 x x		27M, COMPOSITE, Y0, C-, V-
	WriteDecoder(ACNTL, 0x03);	// CLK-on, Y-on, C-off, V(FB)-off
	WriteDecoder(MISC3, ReadDecoder(MISC3)|0x06); 
}
#endif

#ifdef AWT_ML072S  //Pinchi 20150827 add
#ifdef HS
void COMPOSITE2Input(void)///add by ryan@20171204
{
	WriteDecoder(INFORM, 0xC6);			// 01 00 00 x x		27M, COMPOSITE, Y0, C-, V-
	WriteDecoder(ACNTL, 0x03);	// CLK-on, Y-on, C-off, V(FB)-off
	WriteDecoder(MISC3, ReadDecoder(MISC3)|0x06); 
}
#endif
void COMPOSITE3Input(void)
{
	WriteDecoder(INFORM, 0xCA); 		// 01 00 00 x x 	27M, COMPOSITE, Y0, C-, V-
	WriteDecoder(ACNTL, 0x03);	// CLK-on, Y-on, C-off, V(FB)-off
	WriteDecoder(MISC3, ReadDecoder(MISC3)|0x06); 
}

void COMPOSITE4Input(void)
{
	WriteDecoder(INFORM, 0xCE); 		// 01 00 00 x x 	27M, COMPOSITE, Y0, C-, V-
	WriteDecoder(ACNTL, 0x03);	// CLK-on, Y-on, C-off, V(FB)-off
	WriteDecoder(MISC3, ReadDecoder(MISC3)|0x06); 
}

#endif


#if (defined AWT_NEW_SLIM_MODEL) || (defined SUPPORT_DTV)
void COMPOSITE4Input(void)
{
	WriteDecoder(INFORM, 0xCE); 		// 01 00 00 x x 	27M, COMPOSITE, Y0, C-, V-
	WriteDecoder(ACNTL, 0x03);	// CLK-on, Y-on, C-off, V(FB)-off
	WriteDecoder(MISC3, ReadDecoder(MISC3)|0x06); 
}
#endif

#ifdef SUPPORT_SVIDEO
void SVIDEOInput(void)
{
	WriteDecoder(INFORM, 0x54);			// 01 01 01 0 x		27M, S-VIDEO,   Y1, C0, --
	WriteDecoder(ACNTL, 0x01);	// CLK-on, Y-on, C-on, V(FB)-off
}
#endif

#ifdef SUPPORT_COMPONENT
void COMPONENTInput(void)
{
	WriteDecoder(INFORM, 0x7a);			// 0 1 11 10 1 0		27M, COMPONENT, Y2, C1, V0
	WriteDecoder(ACNTL, 0x00);	// CLK-on, Y-on, C-on, V(FB)-on

//	WriteDecoder(0x35, 0x00);		//	V clamp Enable
//	WriteDecoder(SDTR, 0x03);		
}
#endif

#ifdef SUPPORT_PC
void AVGAInput(void)
{
	MakeStartInt();

	WriteDecoder(ACNTL, 0x00);	// CLK-on, Y-on, C-on, V(FB)-on
//	WriteDecoder(INFORM, 0xed);	// Y3,C2,V1
	WriteDecoder(INFORM, 0xcd);	// Y3,C2,V1
	
	SetADCMode(PC);				// Load Inital Data

	//GetADCGainOffsetEE();			// ADC gain & offset
	
	//-------------- comment out for debug by yhbae 082307-------------
//	GetInitPanelAttribute1();		// Panel Brightness / Contrast, it should change for selectable
	//-----------------------------------------------------------------

	SelectPanelAttrRegGroup(GROUP_RGB);	// [0x70] = 0x20
	WriteDecoder(0x77, 0x00);			// Peaking register setting
	WriteDecoder(0x78, 0x00);			// Panel sharpness=0

	WriteDecoder(0x86, 0x00);			// Black/White stretsh Disable
	WriteDecoder(0x87, 0xff);			// min=0, max=0xff

	//SelectADCmux(PC);
}
#endif // SUPPORT_PC

#ifdef SUPPORT_DTV
void DTVInput(void)
{
	MakeStartInt();

	WriteDecoder(ACNTL, 0x00);	// CLK-on, Y-on, C-on, V(FB)-on
	WriteDecoder(INFORM, 0x4a);	// Y3,C2,V1
	SetADCMode(DTV);

	//GetADCGainOffsetForDTVEE();		// ADC gain & offset
	//GetInitPanelAttribute1();		// Panel Brightness / Contrast
	//GetInitPanelAttribute2();		// Panel Hue / Sharpness / Saturation

	SelectPanelAttrRegGroup(GROUP_YCbCr);
	SetVideoMode( GetVideoModeEE());
	WriteDecoder(0x77, 0x30);			// Panel Peaking=0
	WriteDecoder(0x78, 0x30);			// Panel sharpness=0

	//SelectADCmux(DTV);
}
#endif	// SUPPORT_DTV

//=============================================================================
//	                             Power Functions   
//=============================================================================
/*
BYTE GetLCDPowerState(void)
{
	BYTE val;

	val = ReadDecoder(0xd5);
	val &= 0x30;
	val >>= 4;
	return val;
}
*/
/*
void SetLCDPowerState(BYTE dat)
{
	WriteDecoder( 0xd4, 0x01 );	// timer prescaler
	WriteDecoder( 0xd6, 0x11 );	// suspend->standby		on->suspend 
	WriteDecoder( 0xd7, 0x11 );	// off->standby(!)		standby->off
	WriteDecoder( 0xd8, 0x11 );	// standby->suspend(*)	suspend->on			
	
	WriteDecoder( 0xd5, dat );		// Auto Power
}
*/
/*
BYTE IsFreeRun(void)
{
	BYTE val;

	val = ReadDecoder(0xbe);
	if( val & 0x04 ) return 1;
	else             return 0;
}
*/
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
void PanelFreeRun(BYTE on)
{
	BYTE val;
	#ifndef QVGA
	if( on ) AutoPHPCalDisable();
	else AutoPHPCalEnable();
	#endif

	val = ReadDecoder(0xbe);
	if( on ) {
		val |= 0x04;
		WriteDecoder(0xb6, ( ReadDecoder(0xb6)& 0x70) | 0x85 );	// Disable Auto calc H period
		//WriteDecoder(0xb6, 0xb5 );	// Disable Auto calc H period
	}
	else {    
		val &= 0xfb;
		WriteDecoder(0xb6, ReadDecoder(0xb6) & 0x7f );	// Enable Auto calc H period
	}
	WriteDecoder(0xbe, val);
}

void PanelBlack(BYTE on)			// what function for????
{
	BYTE val, tmp;

	tmp = ReadDecoder(0xff);
	WriteDecoder(0xff, 0x01);

	val = ReadDecoder(0xf3);	// 0x1f3 bit5 is for all 0 out
	if( on ) {
		val |= 0x20;
    }
	else    {
		val &= 0xdf;
	}

	WaitEndofDisplayArea();	
	WriteDecoder(0xf3, val);

	WriteDecoder(0xff, tmp);
}
#endif
#if 0
void PanelMute(BYTE on)
{
	if( on ){	// Mute
		PanelBlack(on);
		PanelFreeRun(on);
	}
	else
	{	// Recover
		PanelFreeRun(on);
		PanelBlack(on);
	}
}
#endif

void ON_LVDS(void)
{
	#ifdef LVDS
	BYTE val;
	val = ReadDecoder(0x4e) & 0xdd; //1101 1101 
	WriteDecoder(0x4e, val|0x20);	// GPIO1 En & output enable

	val = ReadDecoder(0x4f) & 0x0f;
	WriteDecoder(0x4f, val | 0x1f);		// GPIO1 = 1
	dPuts("\r\n--ON_LVDS");	
	#endif
}

void OFF_LVDS(void)
{
	#ifdef LVDS
	BYTE val;
	val = ReadDecoder(0x4e) & 0xdd; //1101 1101 
//	WriteDecoder(0x4e, val&~(0x20));	// GPIO0 En
	WriteDecoder(0x4e, val|0x20);	// GPIO1 En

	val = ReadDecoder(0x4f) & 0x0f;	//0xf9;
	WriteDecoder(0x4f, val | 0x00);		// GPIO1 = 0
	dPuts("\r\n--OFF_LVDS");	
	#endif
}

void LCDPowerON(BYTE mute)
{

	if(PowerFlag==0 && CheckTrigger()==0 && SelectBoxMode==0)
		return;
	
	PowerLED(ON);
	//Printf("\r\n------> LCD on=%02x",(WORD)GetLCDPowerState());
		#if 0//ryan@20171016
		if(mute==1)//ryan@20171002
		{
		SetBacklight();
		return;
		}
		#endif
	//if( (GetLCDPowerState()==POWER_OFF)) 
	
	if( mute==3) 
	{
		#if 0//ryan@20171016
	    if(mute==1)
		SetBacklight();
		#endif
		//Printf("\r\n------> LCD on");
		OFF_LVDS();
		//PanelMute(1);
		
		//Panel_Enable();
		//Wait_ms(16);
		P3_5=1;
		
		//delay(10);

		WriteDecoder(0xd5, 0x09);	// Standby	Panel:1  Signal:0  Back:0
		delay(4);
		//Wait_ms(40);
		WriteDecoder(0xd5, 0x0b);	// Suspend	Panel:1  Signal:1  Back:0
//		delay(1);
        
//    	ON_LVDS();
//		PanelMute(mute);
		delay(10);
		ON_LVDS();
		
		#ifdef BACKLIGHT_PWM
		WriteDecoder(0xd5, 0x0f);	// On		Panel:1  Signal:1  Back:1
		#endif

		//AudioMute(1);				//WILLIAM-981103
		
		#ifdef BACKLIGHT_CCFL
		//WriteDecoder(0xd5, 0x0f);	// On		Panel:1  Signal:1  Back:1
		WriteDecoder(0xff, 1);
		WriteDecoder(0xb1, 0x30);
		WriteDecoder(0x30, 0xf1);
		WriteDecoder(0x34, 0x6f);		// dimming frequency for WVGA pannel
		WriteDecoder(0xff, 0);
		WriteDecoder(0xd5, 0x0f);	// On		Panel:1  Signal:1  Back:1
		#endif
		#ifdef BACKLIGHT_LED
		//WriteDecoder(0xd5, 0x0f);	// On		Panel:1  Signal:1  Back:1
		WriteDecoder(0xff, 1);
		WriteDecoder(0xb1, 0x20);
		WriteDecoder(0x30, 0xd2);
		WriteDecoder(0x31, 0xa6);
		WriteDecoder(0x33, 0x40);
		WriteDecoder(0x34, 0x80);
		WriteDecoder(0x32, 0x84);
		WriteDecoder(0x35, 0x80);
		WriteDecoder(0x36, 0x00);
		WriteDecoder(0xff, 0);
		WriteDecoder(0xd5, 0x0f);	// On		Panel:1  Signal:1  Back:1
		#endif
		delay(5);

					
		//Wait_ms(50);
		CAM_QUAD_TO=3;//ryan@20170928
		//SetBacklight();

		TW2835Cmd("\n\rbusw 0 1 A1 11\n\r");
		Wait_ms(100);
	    	TW2835Cmd("\n\rbusw 0 1 A2 D7\n\r");  
		
	}
	else	 if(mute==1||mute==0)
		{
		#ifdef AWT_ML072S
	
			if(SEQFlag||(PowerFlag==0))
			{
			P3_5=1;
			Wait_ms(500);	
			Panel_Enable();
			Wait_ms(20);
			SetBacklight();
			}
			else
			{
				if((GetKey(1)))///ryan@20180109
				{
				P3_5=1;
				//Wait_ms(100);	
				Panel_Enable();
				Wait_ms(20);
				SetBacklight();
				Wait_ms(50);	
				}
				else
				{
				P3_5=1;
				//Wait_ms(500);	
				Panel_Enable();
				//Wait_ms(20);
				//SetBacklight();
				Backlight_TO=20;//ryan@20180108
				}
			}

			#ifdef Hs_debug
			Printf("\r\n*LCDPowerON  mute=%02x",(WORD)mute);
			#endif
		#else
		P3_5=1;
		Wait_ms(300);	
		Panel_Enable();
		Wait_ms(20);
		SetBacklight();	
		#endif
		}
		//PanelMute(mute);
}
/*
void LCDPowerOFF(void)
{
	dPuts("\r\n------> LCD off");
	
	PanelMute(1);
//	OFF_LVDS();

	SetLCDPowerState(POWER_OFF);
	OFF_LVDS();

	delay(10);
}
*/
/*
void LCDPowerOFF(void)
{
//	if( GetLCDPowerState()==POWER_OFF ) return;

	Printf("\r\n------> LCD off");
	//PanelMute(1);
	
	WriteDecoder(0xd5, 0x0b);	// Suspend	Panel:1  Signal:1  Back:0
	delay(1);
	WriteDecoder(0xd5, 0x09);	// Standby	Panel:1  Signal:0  Back:0
	delay(1);
	WriteDecoder(0xd5, 0x08);	// Off		Panel:0  Signal:0  Back:0

	OFF_LVDS();

	#ifdef BACKLIGHT_CCFL
	WriteDecoder(0xff, 1);
	WriteDecoder(0x30, 0xf2);
	WriteDecoder(0xff, 0);
	#endif
	#ifdef BACKLIGHT_LED
	WriteDecoder(0xff, 1);
	WriteDecoder(0x32, 0x44);
	WriteDecoder(0xff, 0);
	#endif
	
	clrBacklight();
	Wait_ms(100);
	P3_5=0;
	Wait_ms(16);
	Panel_Disable();
	
		
//	delay(10);
}

*/
#ifdef Hs_debug
#ifdef SERIAL
void LCDPower(void)
{
	extern  BYTE InputSelection;
	static BYTE state=0;

	//state = GetLCDPowerState();
	if( state==POWER_ON ){
		state = POWER_OFF;
		LCDPowerOFF();
		PowerDown_XTAL(1);

		Printf("\nPower Off!!");
	}
	else //if( state==POWER_OFF )
	{
//		reset = 0;
		PowerDown_XTAL(0);
		delay(10);
/*		reset = 1;
		delay(10);
		InputSelection = 0xff;
		ChangeInput( GetInputSelectionEE() );
		LCDPowerON(0);
*/
		state = POWER_ON;
		LCDPowerON(0);

		Printf("\nPower On!!");
	}
}
#endif // SERIAL
#endif
/*
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
void DPMSmodeOFF(void)
{
	//WriteDecoder(ACNTL, ReadDecoder(ACNTL) | 0x0f);	// HHY 1.44 power down 27M clock, ADC
}

void DPMSmodeON(void)
{
	//WriteDecoder(ACNTL, ReadDecoder(ACNTL) & 0xf0);	// HHY 1.44 power on 27M clock, ADC
	//delay(5);
}
#endif	// SUPPORT_PC
*/
/***
void SetPanelBitOrder(BYTE swap)
{
	BYTE val;
	val = ReadDecoder(0xf7);
	if( swap ) val = val | 0x01;
	else       val = val & 0xfe;
	WriteDecoder(0xf7, val);
}
***/
/***
void SetPanelSingleDouble(BYTE single)
{
	BYTE val;
	val = ReadDecoder(0xb0);
	if( single ) val = val & 0x7f;
	else         val = val | 0x80;
	WriteDecoder(0xb0, val);
}
***/
//=============================================================================
//                          Measurement Functions
//=============================================================================
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV ) || defined( DEBUG_SETPANEL)
BYTE MeasureAndWait(BYTE field)
{
	BYTE val;
	BYTE i;

	// StartMeasurement
	val = ReadDecoder( 0x5b ) & 0xF0;
	val |= ( (field & 0x03) << 2 );			// flag : choose field for measurement
	WriteDecoder(0x5b, val);
	val |= 0x01;
	WriteDecoder(0x5b, val);			// measure start

	// WaitMeasurementDataReady
	for(i=0; i<50; i++) {			// make more delay
		delay(1);
		val = ReadDecoder(0x5b);
	 	val &= 0x01;
		if( val == 0 ) return 1;
	}

	// ClearMeasurement
	WriteDecoder(0x5b, 8);
	wPuts(" ? ");
	return 0;
}
#endif

//=================================================================================================
//
//=================================================================================================
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV ) || defined( DEBUG_SETPANEL)
void SetEnDet(void)
{
	BYTE val;

	val = ReadDecoder(0x5c);
	val |= 0x01;		//Enable Input HSYNC/VSYNC period change/loss detection.
	WriteDecoder(0x5c, val);

	val = ReadDecoder(0x5c);
}

void ClearEnDet(void)
{
	BYTE val;

	val = ReadDecoder(0x5c);
	val &= 0xfe;		//Disable Input HSYNC/VSYNC period change/loss detection.
	WriteDecoder(0x5c, val);

	val = ReadDecoder(0x5c);
}
#endif // SUPPORT_PC || SUPPORT_DTV || DEBUG_SETPANEL

//=============================================================================
//	                        Panel Setting
//=============================================================================
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )

BYTE IsBypassmode(void)
{
	BYTE dat;

	dat = ReadDecoder(TW88_XYSCALEHI) & 0x10;	// Zoom by-pass
	return dat;
}
/*
BYTE IsInteraced(void)
{
	if( ReadDecoder(0x42) & 0x80 ) return 1;
	return 0;
}
*/
WORD GetHstart(void)
{
	WORD hstartMax;

	WriteDecoder(0x5b, 0x88);
	hstartMax = (WORD)ReadDecoder(0x5a) << 8;		// change for TW8816B2
	hstartMax += ReadDecoder(0x59);

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n === GetHstart(%d)", hstartMax);
	#endif
	return ( hstartMax );
}

/*
WORD GetHend(void)
{
	WORD hendMin, hendMax;

	WriteDecoder(0x5b, 0x98);
	hendMin = (WORD)ReadDecoder(0x58) << 8;
	hendMin += ReadDecoder(0x57);
	hendMax = (WORD)ReadDecoder(0x5a) << 8;
	hendMax += ReadDecoder(0x59);


	if ( hendMax < hendMin )
		hendMax = hendMin;
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n === GetHend(%d)", hendMax);
	#endif
	return hendMax;
}
*/
WORD GetVstart(void)
{
	WORD vstartMin, vstartMax;

	WriteDecoder(0x5b, 0xa8);
	vstartMin = (WORD)ReadDecoder(0x58) << 8;
	vstartMin += ReadDecoder(0x57);
	vstartMax = (WORD)ReadDecoder(0x5a) << 8;		// change for TW8816B2
	vstartMax += ReadDecoder(0x59);

	if ( vstartMax < vstartMin )
		vstartMax = vstartMin;
	#ifdef DEBUG_PC_MEAS
	dPrintf( "\r\n === GetVstart%x(%d)", vstartMax, vstartMax );
	#endif
	return vstartMax;
}



WORD GetVend(void)
{
	WORD vend, vendMin;

	WriteDecoder(0x5b, 0xb8);
	vendMin = (WORD)ReadDecoder(0x58) << 8;
	vendMin += ReadDecoder(0x57);
	vend = (WORD)ReadDecoder(0x5a) << 8;
	vend += ReadDecoder(0x59);

	if ( vend < vendMin )
		vend = vendMin;
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n === GetVend(%d)", vend);
	#endif
	return vend;
}

/**** Not used
void MaskOnSYNCInt()
{
	BYTE val;

	val = 0xfc;
	WriteDecoder(0xb2, val);	//IRQ mask
	dPrintf("\r\nDisableSYNCint:->%02x", val);
}
****/

void MaskOffSYNCInt()
{
	BYTE val;

	val = 0xfc;
	WriteDecoder(0xd2, val);	//IRQ mask
	
	#ifdef DEBUG_TW88
	dPrintf("\r\nEnableSYNCint:->%02x", (WORD)val);
	#endif

	WriteDecoder(0xd2, 0xcc);

	#ifdef DEBUG_TW88
	dPrintf("\r\nEnableSYNCint:->%02x", (WORD)0xcc);
	#endif
}


void MakeStartInt(void)
{
	MaskOffSYNCInt();

	WriteDecoder(0xd3, 0x02);					// IRQ mask 2
	WriteDecoder(0x4e, ReadDecoder(0x4e) | 0x08);	// IRQ pin, active low
	WriteDecoder(0x5b, 0x09);					// Start measure
	//WriteDecoder(0x5b, 0x08);					// clear measure self cleared bit
	WriteDecoder(0x5c, 0x07);					// change error tolerance and enable V/HSYNC change/loss detection

	SetEnDet();								// Set enable-detection
}

void Clear_bypass()
{
	BYTE dat;

	dat = ReadDecoder(TW88_XYSCALEHI);	
	WriteDecoder(TW88_XYSCALEHI, dat & 0xef);	// xxx0 xxxx
}


WORD GetHactiveStart(void)
{
	WORD buf;
	BYTE val;

	val = ReadDecoder(0x49);	
	buf = (WORD)(val & 0x07) << 8;
	buf += ReadDecoder(0x47);

	return buf;
}

/**** Not used */
WORD GetHactiveEnd(void)
{
	WORD buf;
	BYTE val;

	val = ReadDecoder(0x49);
	buf = (WORD)(val & 0xf0) << 4;
	buf += ReadDecoder(0x48);

	return buf;
}
/****/

//#ifdef DEBUG_TW88
WORD GetVactiveStart(void)
{
	WORD buf;
	BYTE val;

	val = ReadDecoder(0x4d);			// high 2 bits
	buf = (WORD)(val & 0x03) << 8;
	buf |= ReadDecoder(0x4a);			// Vactive Odd field Line start position

	return buf;
}
//#endif

//-------------------------------------------------------------------
//                  Set Active Region Functions
//-------------------------------------------------------------------
void SetHactiveStart(WORD hstart)
{
	BYTE val;

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n === SetHactiveStart(%d)", hstart);
	#endif
	// TW8804 write LSByte first
	val = ReadDecoder(0x49);
	val = val & 0xf8;
	val = val | (hstart>>8);

	WriteDecoder(0x49, val);
	WriteDecoder(0x47, (BYTE)hstart);
}

void SetHactiveEnd(WORD hend)
{
	BYTE	val, buf;

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n === SetHactiveEnd(%d)", hend);
	#endif
	// TW8804 write LSByte first
	buf = (BYTE)(hend>>8)<<4;
	val = ReadDecoder(0x49);
	val = val & 0x0f;
	val = val | buf;
	
	WriteDecoder(0x49, val);
	WriteDecoder(0x48, (BYTE)hend);
}

void SetVactiveStart(WORD vstart)
{
	BYTE val, v_h, v_l;

	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n === SetVactiveStart(%d)", vstart);
	#endif
	// TW8804 write LSByte first
	v_l = (BYTE)vstart;
	v_h = (BYTE)(vstart>>8);

	val = ReadDecoder(0x4d);	// high 2 bits
	val = (val & 0xf0);
	val = val | (v_h<<2);
	val = val | v_h;
	WriteDecoder(0x4d, val);

	WriteDecoder(0x4a, v_l);	// Vactive Odd field Line start position
	WriteDecoder(0x4b, v_l);	// Vactive Even field Line start position
}

void SetVactiveLen(WORD van)
{
//	WORD vstop;
	BYTE val, buf;

	//van += 1;							// HHY add 1, because of bottom line garbage
	#ifdef DEBUG_PC_MEAS
	dPrintf("\r\n === SetVactiveLen(%d)", van);
	#endif

	// TW8804 write LSByte first
	buf = (BYTE)(van>>8) << 4;
	val = ReadDecoder(0x4d);
	val = val & 0x8f;
	val = val | buf;
	WriteDecoder(0x4d, val);
	WriteDecoder(0x4c, (BYTE)van);		
					
}

#include "osdmenu.h"
extern CODE struct RegisterInfo UserRange;
extern CODE struct RegisterInfo PanelContrastRange;
extern CODE struct RegisterInfo PanelBrightnessRange;
extern CODE struct RegisterInfo PanelSharpnessRange;
extern CODE struct RegisterInfo PanelHueRange;
extern CODE struct RegisterInfo PanelSaturationRange;

void GetInitPanelAttribute1(void)
{
	BYTE rdata;
	int	regv;

	rdata = GetPanelContrastEE();
	Mapping1( rdata, &UserRange ,&regv, &PanelContrastRange);
	SetRGBContrast( GetPCColorTempModeEE(), (BYTE)regv );

	rdata = GetPanelBrightnessEE() ;
	Mapping1( rdata, &UserRange , &regv,   &PanelBrightnessRange );
	SetPanelBrightnessReg(RED,   (BYTE)regv);
	SetPanelBrightnessReg(GREEN, (BYTE)regv);
	SetPanelBrightnessReg(BLUE,  (BYTE)regv);
}

#endif // SUPPORT_PC
/*
void DefaultPanelAttributeForVideo(void)
{
	BYTE rdata;

	SelectPanelAttrRegGroup(GROUP_RGB);
	rdata = GetAttributesFromNTSCSettings(0x70);
	SetPanelHueReg( (ReadDecoder(0x70) & 0xc0) | (rdata & 0x3f) );

	rdata = GetAttributesFromNTSCSettings(0x71);
	SetPanelContrastReg(RED,  rdata);

	rdata = GetAttributesFromNTSCSettings(0x72);
	SetPanelContrastReg(GREEN,rdata);

	rdata = GetAttributesFromNTSCSettings(0x73);
	SetPanelContrastReg(BLUE, rdata);

	rdata = GetAttributesFromNTSCSettings(0x74);
	SetPanelBrightnessReg(RED,  rdata);

	rdata = GetAttributesFromNTSCSettings(0x75);
	SetPanelBrightnessReg(GREEN,rdata);

	rdata = GetAttributesFromNTSCSettings(0x76);
	SetPanelBrightnessReg(BLUE, rdata);

	//rdata = GetAttributesFromNTSCSettings(0x77);
	//SetPanelSharpnessReg( rdata );

	SelectPanelAttrRegGroup(GROUP_YCbCr);
	SetPanelSaturationReg(U_SAT, 0x80);
	SetPanelSaturationReg(V_SAT, 0x80);
	//SelectPanelAttrRegGroup(GROUP_RGB);

}
*/
#ifdef SUPPORT_PC

//=============================================================================
//                          Invert Polarity Functions
//=============================================================================
/*
void InvertHSYNCPolarity(void)
{
	BYTE val;

	val = ReadDecoder(0x40);
	if( val & 0x04 ) {
		val &= 0xfb;

		#ifdef DEBUG_PC
		dPuts("\r\nInvert H Pol: N->P ");
		#endif

	}
	else {
		val |= 0x04;
		
		#ifdef DEBUG_PC
		dPuts("\r\nInvert H Pol: P->N ");
		#endif

	}
	WriteDecoder(0x40, val);
}
*/
void InvertVSYNCPolarity(void)
{
	BYTE val;

	val = ReadDecoder(0x40);
	if( val & 0x02 ) {
		val &= 0xfd;

		#ifdef DEBUG_PC
		dPuts("\r\nInvert V Pol: N->P ");
		#endif

	}
	else {
		val |= 0x02;

		#ifdef DEBUG_PC
		dPuts("\r\nInvert V Pol: P->N ");
		#endif

	}
	WriteDecoder(0x40, val);
}

//=============================================================================
//                          get sync pulse Functions
//=============================================================================
WORD GetVSYNCPulse(void)
{
	WORD buf;

	WriteDecoder(0x5b, 0x78);			// VSYNC 
	delay(10);
	buf = (WORD)ReadDecoder(0x58) << 8;
	buf |= ReadDecoder(0x57);

	#ifdef DEBUG_PC
	dPrintf("\r\nGetVSYNCPulse():%d ", buf);
	#endif
	return buf;
}

/* Not used right now!!
WORD GetRelativePosition(void)
{
	WORD buf;

	WriteDecoder(0x5b, 0x70);			// VSYNC 

	buf = (WORD)ReadDecoder(0x5a) << 8;
	buf |= ReadDecoder(0x59);

	return buf;
}
//*/

WORD GetHSYNCPulse(void)
{
	WORD buf;

	WriteDecoder(0x5b, 0x68);			// HSYNC 
	buf = (WORD)ReadDecoder(0x58) << 8;		// from MSB
	buf |= ReadDecoder(0x57);

	return buf;
}

#endif	// SUPPORT_PC

//=============================================================================
//								Internal PLL
//=============================================================================
#if defined SUPPORT_PC || defined SUPPORT_DTV

BYTE GetPOST(void)
{
	BYTE post;

	post = ReadDecoder(TW88_PLL_DIV);
	return ((post>>6) & 0x03);			// change register position
}

DWORD GetPPF(void)
{
	DWORD ppf, Freq;
	BYTE  i;

	Freq = ReadDecoder(TW88_FPLL0);
	Freq &= 0x0f;
	Freq <<= 8;
	Freq |= ReadDecoder(TW88_FPLL1);
	Freq <<= 8;
	Freq |= ReadDecoder(TW88_FPLL2);

	#ifdef DEBUG_PC
	dPrintf("\r\n(GetFBDN) :%ld", Freq);
	#endif
// 27000000 * 4 * FREQ / 2^17  / 2^POST
	ppf = 824L * ( Freq );
//	ppf = 412L * ( GetFBDN() );

	i= GetPOST();
	
	for(; i>0; i-- ) ppf /= 2;

	#ifdef DEBUG_PC
	dPrintf("\r\n(GetPPF) :%ld", ppf);
	#endif
	return ppf;
}
#endif 

#if defined SUPPORT_PC || defined SUPPORT_DTV

// PLL = 108MHz *FPLL / 2^17
// FPLL = PLL * 2^17 / 108MHz
void ChangeInternPLL(DWORD _PPF)
{
	BYTE	ppf, CURR, VCO, POST, i;
	DWORD	FPLL;

	#ifdef DEBUG_PC
	dPrintf("\r\n++ ChangeInternPLL ++_PPF:%08lx(%ld) ", _PPF, _PPF);
	#endif

	ppf = _PPF/1000000;

	//----- Frequency Range --------------------
	if     ( ppf < 27 )  { VCO=0; CURR=0; POST=2; }		// step = 0.5MHz
	else if( ppf < 54 )  { VCO=1; CURR=0; POST=1; }		// step = 1.0MHz
	else if( ppf < 108 ) { VCO=2; CURR=0; POST=0; }		// step = 1.0MHz
	else                 { VCO=3; CURR=0; POST=0; }		// step = 1.0MHz

	//----- Get FBDN
	FPLL = (_PPF/100000L)*2427L;

	i = POST;
	for(; i>0; i-- )
		FPLL *= 2;

	FPLL = FPLL / 20L;

	//----- Setting Registers : below is different with 8806
	WriteDecoder( TW88_FPLL0, (FPLL>>16));
	WriteDecoder( TW88_FPLL1, (BYTE)(FPLL>>8));
	WriteDecoder( TW88_FPLL2, (BYTE)FPLL );

	if(PcMode==EE_XGA_60)		//william-20100128
		WriteDecoder( TW88_FPLL1,0xb5);	


	WriteDecoder( TW88_PLL_DIV, (VCO<<4) | (POST<<6) |CURR );
}
//=============================================================================
//	                   Set Measurement Window Functions   
//=============================================================================
void SetMeasureWindowH(WORD start, WORD stop)
{
	BYTE val;

	#ifdef DEBUG_PC
	dPrintf("\r\nSetWindow H. Range(%04x, %04x)", start, stop);
	#endif

	// TW8804 write LSByte first
	val = (BYTE)((stop >> 4) & 0xf0);
	val |= (BYTE)((start>>8) & 0x07);
	WriteDecoder(0x53, val);				// H-start and H-stop

	WriteDecoder(0x51, (BYTE)start);		// H-start
	WriteDecoder(0x52, (BYTE)stop);			// H-stop
}

void SetMeasureWindowV(WORD start, WORD stop)
{
	BYTE val;

	#ifdef DEBUG_PC
	dPrintf("\r\nSetWindow V. Range(%04x, %04x)", start, stop);
	#endif

	// TW8804 write LSByte first
	val  = (BYTE)((stop>>4) & 0x70);
	val |= (BYTE)((start>>8) & 0x07);
	WriteDecoder(0x56, val);				// V-start & V-stop

	WriteDecoder(0x54, (BYTE)start);		// V-start
	WriteDecoder(0x55, (BYTE)stop);			// V-stop
}
#endif // SUPPORT_PC || defined SUPPORT_DTV

//=============================================================================
//	                              ZoomControl
//=============================================================================
#if defined(SUPPORT_PC) || defined(SUPPORT_DTV)
void BypassZoom()
{
	#ifdef WXGA
	WriteDecoder(TW88_XUSCALELO, 0xcd);
	WriteDecoder(TW88_YUSCALELO, 0x80);
	WriteDecoder(TW88_XDSCALELO, 0x00);
	WriteDecoder(TW88_XYSCALEHI, 0x06);	
	#else
	//SetBypassmode=1;
	WriteDecoder(TW88_XUSCALELO, 0x00);
	WriteDecoder(TW88_XDSCALELO, 0x80);
	WriteDecoder(TW88_YUSCALELO, 0x00);
	WriteDecoder(TW88_XYSCALEHI, 0x15);	//Set bit 4 to 1
	#endif
}
#endif

#if defined(SUPPORT_PC) || defined(SUPPORT_DTV) //  || defined(WIDE_SCREEN)
void XscaleU(DWORD scale)
{
	BYTE val;

	WriteDecoder( TW88_XUSCALEFINE, (BYTE)scale);

	scale >>= 8;
	WriteDecoder( TW88_XUSCALELO, (BYTE)scale);

	scale >>= 8;
	val = ReadDecoder(TW88_XYSCALEHI);
	val &= 0xfe;
	val |= (BYTE)scale;
	WriteDecoder( TW88_XYSCALEHI, val );
}

void XscaleD(DWORD scale)
{
	BYTE val;

	WriteDecoder( TW88_XDSCALELO, (BYTE)scale);

	scale >>= 8;
	scale <<= 1;
	val = ReadDecoder(TW88_XYSCALEHI);
	val &= 0xfd;
	val |= (BYTE)scale;
	WriteDecoder( TW88_XYSCALEHI, val );
}

void XScale2(DWORD scale)
{
extern	BYTE PcMode;
	if( scale==0x10000 ) {		// No Scale
		XscaleU(0x10000);
		XscaleD(0x80);
	}
	else if( scale<0x10000 ) {	// Up Scale
		XscaleU(scale);
		#ifdef REFERENCE
		XscaleD(0x80);
		#else
		#ifdef XGA
		XscaleD(0x80);
		#else
		if (PcMode >= EE_SVGA_56 && PcMode <= EE_SVGA_85 )
			XscaleD(0x82);
		else
			XscaleD(0x80);
		#endif 
		#endif
	}
	else {						// Down Scale
		XscaleU(0x10000);
		#ifdef REFERENCE
		XscaleD(scale/2/256);
		#else
		if (PcMode == EE_XGA_60)
		{
			XscaleD(scale/2/256 +1);
		}
		else
			XscaleD(scale/2/256);
		#endif
	}
}

void YScale2(DWORD scale)
{
	BYTE val;

	WriteDecoder( TW88_YUSCALEFINE, (BYTE)(scale));

	scale >>= 8;
	WriteDecoder( TW88_YUSCALELO, (BYTE)(scale));

	scale >>= 8;
	scale <<= 2;
	val = ReadDecoder(TW88_XYSCALEHI) & 0xf3;
	val |= (BYTE)scale;
	WriteDecoder( TW88_XYSCALEHI, val );
}
#endif // SUPPORT_PC || SUPPORT_DTV || WIDE_SCREEN

/**
#if defined(SUPPORT_PC) || defined(SUPPORT_DTV)
WORD GetYScale(void)
{
	WORD scale;
	BYTE val;

	scale = ReadDecoder(TW88_YUSCALELO);
	val = ReadDecoder(TW88_XYSCALEHI);
	val = (val >> 2) & 0x03;
	scale = scale + val*0x100;

	return scale;
}
#endif // SUPPORT_PC || SUPPORT_DTV
**/

//=============================================================================
//	                             Panel related..
//=============================================================================
/***
#if (defined SERIAL) || (defined WIDE_SCREEN)
void SetPVR(WORD pvr)
{
	BYTE buf;

	// TW8804 write LSByte first
	buf = ReadDecoder(0xbb) & 0x0f;
	buf = buf | ( (pvr>>4) & 0xf0 );
	WriteDecoder( 0xbb, buf );

	WriteDecoder( 0xba, (BYTE)pvr );
}

void SetPHR(WORD phr)
{
	BYTE buf;

	// TW8804 write LSByte first
	buf = ReadDecoder(0xb6) & 0x0f;
	buf = buf | ( (phr>>4) & 0xf0 );
	WriteDecoder( 0xb6, buf );

	WriteDecoder( 0xb5, (BYTE)phr );
}
#endif // SERIAL || WIDE_SCREEN
***/

#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV ) || defined( DEBUG_SETPANEL)
//----- Panel V Resolution
WORD GetPVR(void)
{
/*	WORD	pvr;
	BYTE	val;
	
	val = ReadDecoder(0xbb);
	pvr = (val & 0x70) << 4;		// pppp xxxx -> pppp 0000 0000
	pvr |= ReadDecoder(0xba);

	return pvr;*/
	return PVR_;
}

//----- Panel H Resolution
WORD GetPHR(void)
{
/*	WORD	phr;
	BYTE	val;

	val = ReadDecoder(0xb6);
	phr = (val & 0x70) << 4;		// pppp xxxx -> pppp 0000 0000
	phr |= ReadDecoder(0xb5);

	return phr;*/
	return PHR_;
}

WORD GetHPN(void)
{
	WORD buf;

	ClearEnDet();			// HHY 05.29.03 protect changing during read out

	WriteDecoder(0x5b, 0x58);	// HSYNC period and VSYNC period

	buf = ReadDecoder(0x58);	// from MSB
	buf = buf << 8;
	buf = buf | ReadDecoder(0x57);

	SetEnDet();				// HHY 05.29.03 release protection

	return buf;


}
/*
WORD GetHPN(void)
{
	WORD buf, sum;
	BYTE i;

	//Get HPN 
	WriteDecoder(0x5b, 0x50);	// HSYNC period and VSYNC period

	//HPN

	for(i=0, sum=0; i<5; i++) {		// HHY 1.45 take average 
		buf = (WORD)ReadDecoder(0x58) << 8;// from MSB
		buf |= ReadDecoder(0x57);
		sum += buf;
	}

	buf = (sum+5)/5;

	return buf;
}
*/
WORD GetVPN(void)
{
	WORD buf;

	WriteDecoder(0x5b, 0x58);	// HSYNC period and VSYNC period

	buf = (WORD)ReadDecoder(0x5a);
	buf = buf << 8;
	buf = buf | ReadDecoder(0x59);
	return buf;
}

/*
WORD GetPVP(void)
{
	WORD pvp;

	pvp = ReadDecoder(0xbb);					// pvp = Panel Vsync Period
	pvp = (pvp & 0x0f) << 8;				//
	pvp |= ReadDecoder(0xb7);					//

	return pvp;
}
*/

BYTE GetVBackPorch(void)
{
	return ReadDecoder(0xb9);
}

#endif // SUPPORT_PC

#if defined SUPPORT_PC || defined SUPPORT_DTV
void SetVBackPorch(BYTE val)
{
	#ifdef DEBUG_PC
	dPrintf("\r\n === SetVBackPorch(%d)", (WORD)val);
	#endif
	WriteDecoder(0xb9, val);
}

void SetPVP(WORD period )
{
	BYTE val;

	// TW8804 write LSByte first
	val = ReadDecoder(0xbb);
	val = val & 0xf0;
	val = val | (BYTE)(period>>8);
	WriteDecoder(0xbb, val);
	WriteDecoder(0xb7, (BYTE)period);	// A4, A8 = Panel Vsync Period
}

void SetPHP(WORD php)
{
	BYTE val;

	// TW8804 write LSByte first
	val = ReadDecoder(0xb6);
	val &= 0xf0;				//0xf8; cut D
	val |= (BYTE)(php>>8);
	WriteDecoder(0xb6, val);
	WriteDecoder(0xb2, php);		// A9, AD = Panel Hsync Cycle
}

#endif //#if defined SUPPORT_PC || defined SUPPORT_DTV

/*WORD GetPHP(void)
{
	WORD php;

	php = ((WORD)ReadDecoder(0xb6) & 0x0f) << 8;
	php += ReadDecoder(0xb2);

	return php;
}

*/


//#if (defined SERIAL) || (defined WIDE_SCREEN)
/*#if (defined WIDE_SCREEN)
WORD GetVactive(void)  // Input V active length
{
	WORD actv;

	actv =   ReadDecoder(CROP_HI) & 0x30;
	actv <<= 4;
	actv |=  ReadDecoder(VACTIVE_LO);

	return actv;
}
#endif // WIDE_SCREEN


WORD GetHCounter1(BYTE field )
{
	WORD counter;

	MeasureAndWait(field);

	WriteDecoder(0x5b, 0xc0);
	counter = (WORD)ReadDecoder(0x58) << 8;
	counter += ReadDecoder(0x57);

	return counter;
}

void SetHInitial(BYTE field, WORD counter)
{
	BYTE val;
	
	if( field==0 ) {	// odd
		val = ReadDecoder( 0xc2 );
		val = ( val & 0xf0 ) |  ( ( counter>>8 ) & 0x0f );
		WriteDecoder(0xc2, val);
		WriteDecoder(0xc0, (BYTE)counter);
	}
	
	else {				// even
		val = ReadDecoder( 0xc2 );
		val = ( val & 0x0f ) |  ( ( counter>>4 ) & 0xf0 );
		WriteDecoder(0xc2, val);
		WriteDecoder(0xc1, (BYTE)counter);
	}
}
*/
//=============================================================================
//
//=============================================================================
//
/*
void TuneLineBuffer(BYTE field)
{
	WORD php, hcounter;
	int initial=0;
	BYTE freerun;

	extern IDATA BYTE  PcMode;


	#if defined (DEBUG_PC) || defined (DEBUG_DECODER)
	dPrintf("\r\n----- TuneLineBuffer:%d -----", (WORD)field);
	#endif

	#ifdef SUPPORT_PC
	if( IsBypassmode() ) return;
	#endif

	//#ifdef SUPPORT_DTV
	//if( IsDTVInput() ) return;
	//#endif

	// disable free run
	freerun = IsFreeRun();
	PanelFreeRun(0);

	php = GetPHP();

	initial = 0;
	SetHInitial(field, initial);

	hcounter = GetHCounter1(field);
	#if defined (DEBUG_PC) || defined (DEBUG_DECODER)
	dPrintf("\r\nInitial=%4x  Hcounter=%4x  PHP=%4x (%2d%%)", initial, hcounter, php, (WORD)((DWORD)hcounter*100/php) );
	#endif
	
	if( (hcounter < ((DWORD)php*78/100)) || (hcounter > ((DWORD)php*82/100)) ) {
		
		initial = php*4/5 - hcounter + initial;
		if( initial>=0 ) {
			SetHInitial(field, initial/2);
			dPuts(" + ");
		}
		else {
			SetHInitial(field, 0x1000 + initial/2);
			dPuts(" - ");
		}
		
//		WriteDecoder(0xb1, ReadDecoder(0xb1)&0x08);
//		WriteDecoder(0xb0, 0xff);
//		WriteDecoder(0xb1, 0xff);
		
	}
	

	PanelFreeRun(freerun);
}
*/

//=============================================================================
//
//=============================================================================
/*
WORD GetAveHCVWRS(BYTE field)
{
	WORD hcounter, ave=0;
	BYTE i;


	#ifdef DEBUG_TW88
	dPuts("\r\n------ Get Average of HCVWRS ------");
	#endif

	for(i=0; i<5; i++) {
	
		hcounter = GetHCounter1(field);

		#ifdef DEBUG_TW88
		dPrintf("\r\n[%2d] HCVWRS=%4d", i, hcounter);
		#endif
		if( i==0 )
			ave = hcounter;
		else
			ave = ( ave + hcounter ) / 2;
	}
	#ifdef DEBUG_TW88
	dPrintf("\r\n----------- Average:%d -------------", ave);
	#endif

	return ave;
}
*/


#if 0 //SERIAL
void TestHCVWRS(BYTE field, WORD initial)
{
	WORD /*php,*/ hcounter, min=0, max=0;
	BYTE i;


	#ifdef DEBUG_TW88
	dPuts("\r\n------ Get HCVWRS ------");
	#endif

//	php = GetPHP();
	
	SetHInitial(field, initial);

	for(i=0; i<30; i++) {
	
		hcounter = GetHCounter1(field);
		dPrintf("\r\n[%2d] HInitial:%d  HCVWRS=%4d  PHP=%4d", i, initial, hcounter, GetPHP());
		dPrintf(" : %d%% of PHP ", hcounter*10/(GetPHP()/10));
		if( i==0 )
			min = hcounter;
		if( min > hcounter )
			min = hcounter;
		if( max < hcounter )
			max = hcounter;
	}
	dPrintf("\r\n------ Min:%d     Max:%d  ---(Field:%d)--", min, max, field);
}
#endif // SERIAL

//#endif

/***
WORD GetHPN1(void)
{
	WORD buf;
	BYTE val;

	//Get HPN 
	WriteDecoder(0x5b, 0x50);	// HSYNC period and VSYNC period

	//HPN

	val = ReadDecoder(0x58);	// from MSB
	buf = (WORD)val << 8;
	val = ReadDecoder(0x57);
	buf |= val;

	return buf;
}
***/

/****
#if (defined SERIAL) || (defined WIDE_SCREEN)
WORD CalcVBackPorch4DecoderInput( void )
{
	WORD		back_porch, vsud;
	DWORD		realv;

	vsud = GetVSUD();
	back_porch = ( ReadDecoder(VDELAY_LO) - ReadDecoder( 0xbd ) + 2 ) * 0x100L ;	
											// input vdelay - diff_in_out_vsync + 2 
	back_porch += (vsud-1);					// for getting rounded up result
	back_porch /=  vsud ;					// convert to value based on output
	back_porch -= ReadDecoder( 0xb8 );			// - Pandel Vertical Pulse Width

	realv =  ( GetVactive() * (DWORD)0x100 / vsud - GetPVR() ) / 2 ;
											// because of overscan.
	Printf("\r\n(CalcVBack...) min back proch:0x%x  add:0x%lx", back_porch, realv);
	back_porch +=  realv;

	SetVBackPorch( (BYTE) back_porch );
	return back_porch;
}
#endif // SERIAL || WIDE_SCREEN
****/

/******
WORD GetVSUD(void)
{
	WORD		vsud;
	BYTE        scale;

	scale = ReadDecoder( TW88_XYSCALEHI );
	vsud = (WORD)(scale & 0x0c) << 8;
	vsud |= ReadDecoder( TW88_YUSCALELO );

	#ifdef DEBUG_TW88
	dPrintf("\r\n(GetVSDU) :0x%x", vsud);
	#endif
	return vsud;
}
******/

/////////////////////////////////////////////////////////////////////////////
// Mapping( int fromValue, CRegInfo fromRange,
//                                           int * toValue, CRegInfo toRange )
// Purpose: Map a value in certain range to a value in another range
// Input:   int fromValue - value to be mapped from
//          CRegInfo fromRange - range of value mapping from
//          CRegInfo toRange   - range of value mapping to
// Output:  int * toValue - mapped value
// Return:  Fail if error in parameter, else Success
// Comment: No range checking is performed here. Assume parameters are in
//          valid ranges.
//          The mapping function does not assume default is always the mid
//          point of the whole range. It only assumes default values of the
//          two ranges correspond to each other.
//          
//          The mapping formula is:
//
//            For fromRange.Min() <= fromValue <= fromRange.Default():
//
//				(fromValue -fromRange.Min())* (toRange.Default() - toRange.Min())
//				-------------------------------------------------------------------- + toRange.Min()
//					fromRange.Default() - fromRange.Min()
//
//			  For fromRange.Default() < fromValue <= fromRange.Max():
//
//				(fromValue - fromRange.Default()) * (toRange.Max() - toRange.Default())
//				--------------------------------------------------------------------- + toRange.Default()
//		             fromRange.Max() - fromRange.Default()
////
////////////////////////////////////////////////////////////////////////////
BYTE Mapping1( int fromValue, CODE_P struct RegisterInfo *fromRange,
                                 int * toValue, CODE_P struct RegisterInfo *toRange ){

	// calculate intermediate values
	int a;
	int b;

	// perform mapping
	if ( fromValue <= fromRange->Default ) {
		a = toRange->Default - toRange->Min;
		b = fromRange->Default - fromRange->Min;
		// prevent divide by zero
		if( b==0 )		return (FALSE);
		*toValue = (int) ( (DWORD)fromValue- (DWORD)fromRange->Min ) * a / b 
						+(DWORD)toRange->Min;
	}
	else {
		a = toRange->Max - toRange->Default;
		b = fromRange->Max - fromRange->Default;
		// prevent divide by zero
		if( b==0 )		return (FALSE);
        *toValue = (int) ( (DWORD)fromValue - (DWORD)fromRange->Default ) * a / b
                       + (DWORD)toRange->Default;
	}

	#ifdef DEBUG_OSD
	dPrintf("\r\n++(Mapping1)%d(%d-%d-%d)", (WORD)fromValue, (WORD)fromRange->Min, (WORD)fromRange->Default, (WORD)fromRange->Max );
	dPrintf("->%d(%d-%d)", (WORD)*toValue, (WORD)toRange->Min, (WORD)toRange->Max);
	#endif
	
	return ( TRUE );
   
}

#ifndef KEILC
#ifdef SUPPORT_PC
BYTE Mapping2( int fromValue, IDATA_P struct RegisterInfo *fromRange,
                                 int * toValue, CODE_P struct RegisterInfo *toRange ){

	// calculate intermediate values
	int a;
	int b;


	// perform mapping
	if ( fromValue <= fromRange->Default ) {
		a = toRange->Default - toRange->Min;
		b = fromRange->Default - fromRange->Min;
		// prevent divide by zero
		if( b==0 )		return (FALSE);
		*toValue = (int) ( (DWORD)fromValue- (DWORD)fromRange->Min ) * a / b 
						+(DWORD)toRange->Min;
	}
	else {
		a = toRange->Max - toRange->Default;
		b = fromRange->Max - fromRange->Default;
		// prevent divide by zero
		if( b==0 )		return (FALSE);
      *toValue = (int) ( (DWORD)fromValue - (DWORD)fromRange->Default ) * a / b
                       + (DWORD)toRange->Default;
	}

	#ifdef DEBUG_OSD
	dPrintf("\r\n++(Mapping2)%d(%d-%d-%d)", (WORD)fromValue, (WORD)fromRange->Min, (WORD)fromRange->Default, 
		(WORD)fromRange->Max );
	dPrintf("->%d(%d-%d)", (WORD)*toValue, (WORD)toRange->Min, (WORD)toRange->Max);
	#endif
	
	return ( TRUE );
   
}
#endif

BYTE Mapping3( int fromValue, CODE_P struct RegisterInfo *fromRange,
                                 int * toValue, IDATA_P struct RegisterInfo *toRange ){

	// calculate intermediate values
	int a;
	int b;


	// perform mapping
	if ( fromValue <= fromRange->Default ) {
		a = toRange->Default - toRange->Min;
		b = fromRange->Default - fromRange->Min;
		// prevent divide by zero
		if( b==0 )		return (FALSE);
		*toValue = (int) ( (DWORD)fromValue- (DWORD)fromRange->Min ) * a / b 
						+(DWORD)toRange->Min;
	}
	else {
		a = toRange->Max - toRange->Default;
		b = fromRange->Max - fromRange->Default;
		// prevent divide by zero
		if( b==0 )		return (FALSE);
      *toValue = (int) ( (DWORD)fromValue - (DWORD)fromRange->Default ) * a / b
                       + (DWORD)toRange->Default;
	}

	#ifdef DEBUG_OSD
	dPrintf("\r\n++(Mapping3)%d(%d-%d-%d)", (WORD)fromValue, (WORD)fromRange->Min, (WORD)fromRange->Default, 
		(WORD)fromRange->Max );
	dPrintf("->%d(%d-%d)", (WORD)*toValue, (WORD)toRange->Min, (WORD)toRange->Max);
	#endif
	
	return ( TRUE );
   
}
#endif

//---------------------------------------------------------------------------------
extern	CODE BYTE NTSC_Regs[];
#ifdef ADD_ANALOGPANEL
extern CODE BYTE NTSC_Regs_Analog[];
#endif

/*
BYTE GetDataFromTxtFile(BYTE index)
{
	BYTE cnt;
	CODE_P BYTE *RegSet;

	#ifdef ADD_ANALOGPANEL
	if(IsAnalogOn())
		RegSet = NTSC_Regs_Analog;
	else
	#endif	
	RegSet = NTSC_Regs;

	cnt = 0;
	CheckBuf = 0;
	while ( *RegSet != 0xFF ) {

		if( cnt==0 ) {
			//first 2 bytes are I2C address and count of register
			if( (*RegSet) ==TW88I2CAddress ) {
				cnt = *(RegSet+1);
				RegSet+=2;
				for(; cnt>0; cnt--) {
					if((*RegSet)==index ) {

						#ifdef DEBUG_TW88
						dPrintf("--%02x", (WORD)*(RegSet+1));
						#endif

						CheckBuf = (*(RegSet+1));
						return 1;
					}
					RegSet+=2;
				}
				break;
			}
			else
				RegSet += ( (*(RegSet+1)+1)*2 );	// HHY 2.04
		}
	}

	return 0;
}
*/
/*
BYTE GetAttributesFromNTSCSettings(BYTE index)
{

	#ifdef DEBUG_TW88
	dPuts("\r\n++(GetAttributesFromNTSCSettings)");
	#endif

	#ifdef DEBUG_TW88
	dPrintf("\r\nindex:%02x", (WORD)index);
	#endif

	if(GetDataFromTxtFile(index)) return CheckBuf;

	//in case of failing to find that register value in default setting

	switch( index ) {
	case 0x70:	return 0x20;
	case 0x71:
	case 0x72:
	case 0x73:
	case 0x74:	
	case 0x75:
	case 0x76:		return 0x80;
	case 0x77:		return 0;

	case BRIGHT:	return 0x00;
	case CONTRAST:	return 0x60;
	case SHARPNESS:	return 0x10;
	case PNLSHARPNESS: return 0x03;
	case SAT_U:		return 0x7f;
	case SAT_V:		return 0x5a;
	case HUE:		return 0x00;

	case SHUE:		return 0x0;
	case SCONTRAST:	return 0x60;
	case SBRIGHT:	return 0x0;
	case SCbGAIN:	return 0x40;
	case SCrGAIN:	return 0x40;
	default:	return 0xff;
	}
}

*/

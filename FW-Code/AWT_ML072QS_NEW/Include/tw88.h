#ifndef __TW88__
#define __TW88__

#include "main.h"

//Value for register 0x44
//#define DECODER_YCbCr		0x08		//xxxx bbxx
//#define RGB_RGB				0x0C

#define TW88_FPLL0			0xf9
#define TW88_FPLL1			0xfa
#define TW88_FPLL2			0xfb
#define TW88_FSS			0xfc
#define TW88_FSS_PD			0xfd
#define TW88_PLL_DIV		0xfe

//#define TW88_XSCALE			0x5d
//#define TW88_YSCALE			0x5e

#define TW88_XUSCALELO		0x60
#define TW88_XDSCALELO		0x61
#define TW88_YUSCALELO		0x62
#define TW88_XYSCALEHI		0x63
#define TW88_XUSCALEFINE	0x69
#define TW88_YUSCALEFINE	0x6a

//Power Mgt
#define	POWER_OFF			0
#define	POWER_STANDBY		1
#define	POWER_SUSPEND		2
#define	POWER_ON			3

//void TWChipsDetect(void);
void SetAutoDetectStd(void);
void ClearAutoDetectStd(BYTE);
void I2CDeviceInitialize( CODE_P BYTE *RegSet);


//0x63.. Register Group
#define GROUP_YCbCr			0x40
#define GROUP_RGB			0
#define SelectPanelAttrRegGroup(A)				WriteTW88(0x70, (ReadTW88(0x70) & 0xbf) | A)

//#if defined TW8801 || defined TW8803
#define FB_MAIN		2
#define FB_NORMAL	1
#define FB_RGB		0
//void SetFBmode( BYTE mode );
//#endif // TW8801


//=============================================================================
//	                             LCD Functions   
//=============================================================================
//BYTE GetLCDPowerState(void);
void SetLCDPowerState(BYTE dat);

BYTE IsFreeRun(void);
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
void PanelFreeRun(BYTE on);
void PanelBlack(BYTE on);
#endif
#if 0
void PanelMute(BYTE on);
#endif
void LCDPowerON(BYTE mute); 

#ifdef AWT_ML072S
void LCDPowerOFF(void);
#endif

#ifdef Hs_debug
void LCDPower(void);
#endif
void DPMSmodeOFF(void);
void DPMSmodeON(void);
//=============================================================================
//	                        Get PC Parameter Functions   
//=============================================================================
void GetInitPanelAttribute1(void);
//void GetInitPanelAttribute2(void);
void DefaultPanelAttributeForVideo(void);
void SetPVR(WORD pvr);
void SetPHR(WORD phr);
WORD GetPVR(void);
WORD GetPHR(void);
WORD GetHPN(void);
WORD GetVPN(void);

//WORD GetVactive(void);

WORD GetHstart(void);
WORD GetHend(void);
WORD GetVstart(void);
WORD GetVend(void);
void TuneLineBuffer(BYTE field);
void TuneLineBuffer4Video(BYTE field);

#if defined (SUPPORT_DTV)
void SetCoarstForDTV(BYTE en);
#endif

WORD GetHactiveStart(void);
WORD GetHactiveEnd(void);
WORD GetVactiveStart(void);
//WORD GetVactiveLen(void);
BYTE GetVBackPorch(void);
void SetVBackPorch(BYTE val);
WORD GetPHP(void);
void SetPHP(WORD php);
void SetPVP(WORD period);
WORD GetPVP(void);
//void SetPanelRelatedRegisters(void);
//BYTE ChangedHPN(void);
//WORD GetVSUD(void);

void SetDefaultPLL(void);
//void SetDefaultFPHSperiod(void);
//BYTE CalcPHP(DWORD ppf, BYTE tol);
//void ChangeFPHSperiod4DecoderInput(WORD vsud, BYTE tol);

//-------------------------------------------------------------------
//                  Set Active Region Functions
//-------------------------------------------------------------------
void SetHactiveStart(WORD hstart);
void SetHactiveEnd(WORD hend);
void SetVactiveStart(WORD vstart);
//void SetVactiveLen(WORD van, WORD vstart);
void SetVactiveLen(WORD van);
//=============================================================================
//	                   Set Measurement Window Functions   
//=============================================================================
void SetMeasureWindowH(WORD start, WORD stop);
void SetMeasureWindowV(WORD start, WORD stop);
//=============================================================================
//	                        Video Input Functions   
//=============================================================================
BYTE IsVideoInput(void);
BYTE DetectDecoderInput(void);
//=============================================================================
//
//=============================================================================
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
void AutoPHPCalEnable(void);
void AutoPHPCalDisable(void);
#endif
void MakeStartInt(void);
void AVGAInput(void);
void DVIInput(void);
//void DVGAInput(void);
void DisableDVGA(void);

void COMPOSITE1Input(void);
void COMPOSITE2Input(void);
void COMPOSITE3Input(void);
void COMPOSITE4Input(void);

void SVIDEOInput(void);
void COMPONENTInput(void);
void ANALOGDTVInput(void);
void DTVInput(void);
void TVInput(void);
void SCARTInput(void);

//=============================================================================
//                          Measurement Functions
//=============================================================================
///void SetPanelBitOrder(BYTE swap);
//void SetPanelSingleDouble(BYTE single);

BYTE MeasureAndWait(BYTE flag);

//WORD GetHCounter1(BYTE field);
//void SetHInitial(BYTE field, WORD counter);
//=============================================================================
//                          Invert Polarity Functions
//=============================================================================
void InvertHSYNCPolarity(void);
void InvertVSYNCPolarity(void);
//=============================================================================
//            Interrupt / SW Reset Control Functions
//=============================================================================
void SetInt(void);
//void ClearInt(void);
void SetEnDet(void);
void ClearEnDet(void);
void SWReset(void);
//void ClearSYNCLossStatus(void);
//void ClearSYNCChangeStatus(void);
//=============================================================================
//
//=============================================================================
BYTE IsBypassmode(void);
//BYTE IsInteraced(void);
void Clear_bypass(void);
void MaskOnSYNCInt(void);
void MaskOffSYNCInt(void);
//=============================================================================
//	                              ZoomControl
//=============================================================================
void BypassZoom(void);

void XscaleU(DWORD scale);
void XscaleD(DWORD scale);
void XScale2(DWORD scale);
void YScale2(DWORD scale);
WORD GetYScale(void);
//=============================================================================
//
//=============================================================================
WORD GetHSYNCPulse(void);
WORD GetVSYNCPulse(void);
//#if defined TW8801 || defined TW8803
WORD GetRelativePosition(void);
//#endif
//=============================================================================
//								MISC2 for decoder
//=============================================================================
#define	BLUE_DECODER		2
#define BLACK_DECODER		0

BYTE ForceDecoderOutput(BYTE color);
BYTE ClearForcedDecoderOutput(void);
//=============================================================================
//								CC and EDS
//=============================================================================
BYTE GetCCStatus(void);
void DisableCC(void);
void EnableCC(void);
BYTE GetCCData(void);
BYTE IsCCEnabled(void);
void EnableEDS(void);
void DisableEDS(void);
void RecoverCCOverflow(void);

#define CCFIFOHalfFull()			(ReadDecoder(CSTATUS) & 0x04)
//=============================================================================
//								Internal PLL
//=============================================================================
BYTE GetPOST(void);
void SetPLLS(BYTE plls);
BYTE GetREFDM(void);
void SetREFDM(BYTE refdm);
DWORD GetFBDN(void);
void SetFBDN(WORD fbdn, BYTE vcsel);
DWORD GetPPF(void);
void ChangeInternPLL(DWORD _PPF);

//=============================================================================
//								Macros for attribute
//=============================================================================
//#define	GetOSDTransReg()						ReadTW88(0xAE)
//#define SetOSDTransReg(AlphaV)					WriteTW88(0xAE, (BYTE)AlphaV )

#define	GetPanelContrastReg(gccolor)			ReadTW88(0x71+gccolor)
#define	SetPanelContrastReg(sccolor, cval)		WriteTW88(0x71+sccolor,cval)

#define GetPanelBrightnessReg(gbcolor)			ReadTW88(0x74+gbcolor);
#define SetPanelBrightnessReg(sbcolor, bval)	WriteTW88(0x74+sbcolor,bval);

#define SetDTVBrightnessReg(bval)				WriteTW88(0x74,bval);

#define GetPanelSaturationReg(gbcolor)			ReadTW88(0x72+gbcolor);
#define SetPanelSaturationReg(sbcolor, bval)	WriteTW88(0x72+sbcolor,bval);

#define SetPanelSharpnessReg(bval)				WriteTW88(0x78,((bval&0x07)|0x38) );

#define SetPanelHueReg(bval)					WriteTW88(0x70, (ReadTW88(0x70) & 0xc0 | (bval)) );

#define	GetVideoContrastReg()					ReadDecoder(CONTRAST)
#define	SetVideoContrastReg(vcval)				WriteDecoder(CONTRAST, vcval)

#define	GetVideoBrightnessReg()					ReadDecoder(BRIGHT)
#define	SetVideoBrightnessReg(vbval)			WriteDecoder(BRIGHT, vbval )

#define	GetVideoSaturationReg(gvstype)			ReadDecoder(SAT_U+gvstype)
#define	SetVideoSaturationReg(svstype, vsval)	WriteDecoder(SAT_U+svstype,	vsval)

#define	GetVideoHueReg()						ReadDecoder(HUE)
#define	SetVideoHueReg(vhval)					WriteDecoder(HUE,	vhval )

#define	GetVideoSharpnessRegDef					(ReadDecoder(SHARPNESS) & 0x0f) 

#define	GetVideoSharpnessReg()					GetVideoSharpnessRegDef
//#define	SetVideoSharpnessReg(vshval)			WriteDecoder(SHARPNESS, vshval )
#define	SetVideoSharpnessReg(vshval)			WriteDecoder(SHARPNESS, ((ReadDecoder(SHARPNESS) & 0xf0) | (vshval & 0x0f) ) );

#ifdef TW9908
#define	SetVideoVPeakingReg(vshval)
#else
#define	SetVideoVPeakingReg(vshval)				WriteDecoder(V_PEAKING, ((ReadDecoder(V_PEAKING) & 0xf8) | (vshval & 0x07) ) );
#endif

#define SetVideoHfilterReg(val)					WriteDecoder(HFILTER, ((ReadDecoder(HFILTER) & 0xf8) | (val & 0x07) )|0x08 );
//----------------------------------------------------------------------------------
//color type
#define	RED		0
#define	GREEN	1
#define	BLUE	2
#define WHITE	3
//saturation type
#define	U_SAT	0
#define	V_SAT	1

//Alpha Blending Level
#define _0		0
#define _25		0x12
#define _37_5	0x13
#define _50		0x14
#define _100	0x18

BYTE GetKey(BYTE repeat);

/*
BYTE Mapping( int fromValue, struct RegisterInfo fromRange,
                                 int * toValue, struct RegisterInfo toRange );
*/
BYTE Mapping1( int fromValue, CODE_P struct RegisterInfo *fromRange,
                                 int * toValue, CODE_P struct RegisterInfo *toRange );
#ifdef KEILC
#define Mapping2( A, B, C, D )			Mapping1( A, B, C, D )
#define Mapping3( A, B, C, D )			Mapping1( A, B, C, D )
#else
BYTE Mapping2( int fromValue, IDATA_P struct RegisterInfo *fromRange,
                                 int * toValue, CODE_P struct RegisterInfo *toRange );
BYTE Mapping3( int fromValue, CODE_P struct RegisterInfo *fromRange,
                                 int * toValue, IDATA_P struct RegisterInfo *toRange );
#endif

BYTE GetAttributesFromNTSCSettings(BYTE index);

#endif	// __TW88__


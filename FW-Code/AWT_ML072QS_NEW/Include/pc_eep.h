#ifndef __PC_EEP__
#define __PC_EEP__


// -----------------------------------------------------------------------------
#define PC_COLOR_DATA	0x80	// StartAddress of EEPROM for PC Color Temperature
#define PC_USERCOLOR	0x8A
#define	SetPCColorTempModeEE( ctid )			WriteEEP( PC_COLOR_DATA, ctid )
#define	GetPCColorTempModeEE()					ReadEEP( PC_COLOR_DATA )

#define	GetPCUserColorTempEE( ucolorr)			ReadEEP( PC_USERCOLOR+ucolorr )
#define	SavePCUserColorTempEE( ucolorw, uval)	WriteEEP( PC_USERCOLOR+ucolorw, uval )
#define GetPCColorEE(index)						ReadEEP(index)

// -----------------------------------------------------------------------------
#define EE_ADC_GO		0x90	// ADC Gain Offset for PC
#define EE_ADC_GO_DTV	0x98	// ADC Gain Offset for DTV

#define	EE_PCDATA		0xC0	// StartAddress of EEPROM for PCDATA
#define	LEN_PCDATA		5		// Length of PCDATA

WORD GetHPNfromEE(BYTE mode);

BYTE CheckPcDataEEValid(BYTE, WORD);

WORD GetVactiveStartEE(BYTE mode);
WORD GetHactiveStartEE(BYTE mode);

void GetPCDataEE(BYTE mode);
void SavePCDataEE(BYTE mode);
void SaveDefaultPCDataEE(void);
void SaveDefaultPCDataAllEE(void);

void SaveHactiveEE(BYTE mode);
void SaveVactiveEE(BYTE mode);
void SaveVBackPorchEE(BYTE mode);
void SaveCoarseEE(BYTE mode);
void SavePhaseEE(BYTE mode);
/*
WORD GetHactiveStartEE(BYTE mode);
WORD GetVactiveStartEE(BYTE mode);
*/
void DumpPCData(void);

void SaveActiveVEE(WORD);
void SaveBackPorchEE(BYTE);
void SaveActiveHEE(WORD);

void SaveADCGainOffsetEE(BYTE mod);
void GetADCGainOffsetEE(void);

void SaveADCGainOffsetForDTVEE(BYTE mod);
void GetADCGainOffsetForDTVEE(void);

#endif	// __PC_EEP__

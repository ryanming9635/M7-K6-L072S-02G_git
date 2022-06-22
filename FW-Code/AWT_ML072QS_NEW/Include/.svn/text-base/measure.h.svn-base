#ifndef __MEASURE__
#define __MEASURE__

#define EE_DOS				0

#define EE_SP1				1
#define EE_SP2				2
#define EE_SP3				3

#define EE_VGA_60			4
#define EE_VGA_66			5
#define EE_VGA_70			6
#define EE_VGA_72			7
#define EE_VGA_75			8
#define EE_VGA_85			9

#define EE_SVGA_56			10
#define EE_SVGA_60			11
#define EE_SVGA_70			12
#define EE_SVGA_72			13
#define EE_SVGA_75			14
#define EE_SVGA_85			15

#define EE_832_75			16

#define EE_XGA_60			17
#define EE_XGA_70			18
#define EE_XGA_72			19
#define EE_XGA_75			20
#define EE_XGA_85			21

#define EE_1152_60 			22
#define EE_1152_70 			23
#define EE_1152_75 			24

#define EE_SXGA_60 			25
#define EE_SXGA_70 			26
#define EE_SXGA_75 			27

#define EE_RGB_480P			28
#define EE_RGB_720P			29
#define EE_RGB_720P50		30
#define EE_RGB_1080I		31
#define EE_RGB_1080I50A		32
#define EE_RGB_1080I50B		33
#define EE_RGB_480I			34
#define EE_RGB_576I			35
#define EE_RGB_576P			36

#define EE_YPbPr_480P		37
#define EE_YPbPr_720P		38
#define EE_YPbPr_720P50		39
#define EE_YPbPr_1080I		40
#define EE_YPbPr_1080I50A	41
#define EE_YPbPr_1080I50B	42
#define EE_YPbPr_480I		43
#define EE_YPbPr_576I		44
#define EE_YPbPr_576P		45

#define EE_PC_MAX			46

#define EE_PC_NO_SIGNAL		0xfe
#define EE_PC_UNKNOWN		0xff

struct _PCMDATA {
	CODE_P BYTE  Support;
	CODE_P WORD  HAN;
	CODE_P WORD  VAN;
	CODE_P WORD  IVF;
	CODE_P WORD  CLOCK;
	CODE_P WORD  low;
	CODE_P WORD  high;
	CODE_P WORD  Hstart;
	CODE_P WORD  Vstart;
	CODE_P WORD  IPF;		// 0.1MHz
	CODE_P WORD  PPF;		// 0.1MHz
	CODE_P BYTE  VBack;
};
#ifndef AUTOCALC_PC

#ifdef SUPPORT_DTV
struct _DTVMDATA {
	CODE_P BYTE Reg62;
	CODE_P BYTE RegBC;
	CODE_P BYTE RegBD;
	CODE_P BYTE RegBE;
	CODE_P WORD PHP;
};
#endif
#endif
#if defined	XGA
	#define	MAX_PPF		 90000000
#elif defined SXGA
	#define	MAX_PPF		135000000
#elif defined WXGA
	#define MAX_PPF		 90000000
#elif defined WVGA
	#define MAX_PPF		 90000000
#elif defined VGA
	#define MAX_PPF		 50000000
#elif defined SVGA
	#define MAX_PPF		 80000000
#elif defined QVGA
	#define MAX_PPF		 30000000
#elif defined WQVGA
	#define MAX_PPF		 30000000
#endif

extern BYTE cLastSyncLoss;
extern BYTE PcMode;

void CompLT170E2(void);

WORD gap(WORD a, WORD b);

//===================================================================
WORD GetHpnVpn(BYTE);

WORD ConvertBasedOnInput(WORD dat);

BYTE IsDTVInput(void);

void SetVValueForPanel(WORD vstart);
BYTE SetHValueForPanel(void);
BYTE GetActiveRegion(void);

BYTE DetectAndSetForVGAInput(BYTE);
#ifdef SUPPORT_DTV
BYTE DetectAndSetForDTVInput(BYTE);
#endif
void CheckPCinput(void);
void CheckDTVinput(void);

WORD GetCoarseValue(void);
BYTE GetPhaseValue(void);
WORD SetPCCoarseValue(BYTE val);
BYTE SetPhaseValue(BYTE val);

void DisplayResultAndSetActiveRange(void);

//=============================================================================
//                    PC Screen Position Move Functions
//=============================================================================
void MoveActiveVpos(BYTE val);		// Up/Down
void MoveActiveHpos(BYTE val);		// Left/Right

BYTE GetVPosition(void);
BYTE SetVPosition(BYTE val);
BYTE GetHPosition(void);
BYTE SetHPosition(BYTE val);

void ResetPCValue(void);

CODE_P BYTE *GetPCInputSourceName(void);
BYTE AutoAdjust(void);

#endif // __MEASURE__

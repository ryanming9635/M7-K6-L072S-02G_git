#ifndef	__TYPEDEFS__
#define	__TYPEDEFS__


#define DATA		data
#define PDATA		pdata
#define IDATA		data
#define CODE		code
#define CODE_P
#define PDATA_P
#define IDATA_P
#define DATA_P

#define INTERRUPT( num, name ) name() interrupt num

#define _between(x, a, b)	(a<=x && x<=b)
#define _swap(a, b)			{ a^=b; b^=a; a^=b; }

typedef	unsigned char	Register;
typedef	unsigned char	BYTE;
typedef	unsigned short	WORD;
typedef	unsigned long	DWORD;

#define	TRUE	1
#define	FALSE	0

//VInputStdDetectMode
#define AUTO 	0

//VInputStd
#define NTSC 	1			
#define PAL		2
#define SECAM	3
#define NTSC4	4
#define PALM 	5
#define PALN 	6
#define PAL60	7

#define MAXINPUTSTD	PAL60+1	// 

#define UNKNOWN	0xfe
#define NOINPUT	0	//0xff

#define NIL			0xff

enum SourceModeTypeEnum
{	
	AVMode, 	   // 0		0X00
	//VGAMode,       // 1
#ifdef USE_CAMD	
	CAM_D,         // 2
#endif
	CAM_A,         // 3		0x01
	CAM_B,         // 4		0x02
	CAM_C,         // 5		0x03
	CAM_R,         // 6		0x04
	CAM_AB,        // 7		0x05
	CAM_CR,        // 8		0x06
	CAM_AR,        // 9		0x07
	CAM_RB,        // 10		0x08
	CAM_AC,        // 11		0x09
 	CAM_CB,        // 12		0x0a
	CAM_RAB_T,     // 13		0x0b
	CAM_RAB_H,     // 14		0x0c

	#ifdef HTRV
	CAM_RC,
	#endif
	
	CAM_QUAD,      // 15		0x0d
	CAM_ABR_T3,    // 16		0x0e
	CAM_ABR_T4,    // 17		0x0f
	CAM_RAC_T,			//  0x10
	CAM_RBC_T,			//  0x11
	CAM_RAC_T2,			//  0x12
	CAM_RBC_T2,			//  0x13
	CAM_BA,				//  0x14
	CAM_BC,				//  0x15
	CAM_BR,				//  0x16
	CAM_CA,				//  0x17
	CAM_ABC,			//  0x18
	CAM_ABR,			//  0x19
	CAM_ACR,			//  0x1a
	CAM_BAC,			//  0x1b
	CAM_BAR,			//  0x1c
	CAM_BCR,			//  0x1d
	CAM_CAB,			//  0x1e
	CAM_CAR,			//  0x1f
	CAM_CBR,			//  0x20
	SEQ,           // 18			0x10
	CAM_NUM
};

typedef unsigned char SourceModeType;

#endif	/* __TYPEDEFS__ */


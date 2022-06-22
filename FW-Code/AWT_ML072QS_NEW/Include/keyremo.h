//
// KeyRemo.h
// Default function for Key Input and Remocon Input
//
//=============================================================================
//		                    Operation Key Mapping
//=============================================================================




#define ResetKey()		{ P2 = 0xff;}
//#define ReadKey()		(~P1 & 0xfc);

#ifdef QUAD
#define EVENTKEY		0x02
#endif
#define POWERKEY		0x04 //andy AWT 980907
#define MENUKEY			0x08

#ifdef AWT_NEW_SLIM_MODEL  //Pinchi 20150203 add for AWT new slim model
#define UPKEY 			0x10
#define DOWNKEY 		0x20
#define SELECTKEY 		0x40
#define INPUTSOURCEKEY	0x80
#define VersionKEY 		0xC0
#define UnLockKEY 		0xC0
#else
#define INPUTSOURCEKEY	0x10
#define UPKEY		    0x20
#define DOWNKEY		    0x40
#define SELECTKEY	    0x80
  #if 1//Pinchi 20160929 add
  #define Tune2835ClkKEY 0x90
  #define Enter2835TuneKEY 0x0C
  #else
  #define VersionKEY	    0x90
  #endif
#endif

#define REMO_CUSTOM		0

#define REMO_NUM0		0
#define REMO_NUM1		1
#define REMO_NUM2		2
#define REMO_NUM3		3
#define REMO_NUM4		4
#define REMO_NUM5		5
#define REMO_NUM6		6
#define REMO_NUM7		7
#define REMO_NUM8		8
#define REMO_NUM9		9

#define REMO_STANDBY	12
#define REMO_CHNUP		32
#define REMO_CHNDN		33
#define REMO_VOLUP		16
#define REMO_VOLDN		17
#define REMO_SELECT		21
#define REMO_MENU		63
#define REMO_MUTE		13
#define REMO_INPUT		56

#define REMO_AUTO		10
#define REMO_INFO		58
#define REMO_AUDIO		38
#define REMO_ASPECT		62
#define REMO_CC			15
#define REMO_EXIT		0x16

#define REMO_TTXRED			0x37
#define REMO_TTXGREEN		0x36
#define REMO_TTXYELLOW		0x32
#define REMO_TTXCYAN		0x34



//=============================================================================
//                                 RC5 type
//=============================================================================
#ifdef REMO_RC5

#ifdef TECHWELL_REMOCON
#define REMO_CUSTOM		0

#define REMO_NUM0		0
#define REMO_NUM1		1
#define REMO_NUM2		2
#define REMO_NUM3		3
#define REMO_NUM4		4
#define REMO_NUM5		5
#define REMO_NUM6		6
#define REMO_NUM7		7
#define REMO_NUM8		8
#define REMO_NUM9		9

#define REMO_STANDBY	12
#define REMO_CHNUP		32
#define REMO_CHNDN		33
#define REMO_VOLUP		16
#define REMO_VOLDN		17
#define REMO_SELECT		21
#define REMO_MENU		63
//#define REMO_TV			63
//#define REMO_VCR		60
//#define REMO_SVIDEO		56
#define REMO_MUTE		13
#define REMO_INPUT		56

#define REMO_AUTO		10
#define REMO_INFO		58
#define REMO_AUDIO		38
#define REMO_ASPECT		62
#define REMO_CC			15
#define REMO_EXIT		0x16

#define REMO_TTXRED			0x37
#define REMO_TTXGREEN		0x36
#define REMO_TTXYELLOW		0x32
#define REMO_TTXCYAN		0x34

#ifdef SUPPORT_DEBUG
#define REMO_DEBUG		0x2b
#define REMO_READ		0x29
#define REMO_WRITE		0x2a
#define REMO_RESERVED	0x30
#endif

#else 
#define REMO_CUSTOM		0

#define REMO_NUM0		0
#define REMO_NUM1		1
#define REMO_NUM2		2
#define REMO_NUM3		3
#define REMO_NUM4		4
#define REMO_NUM5		5
#define REMO_NUM6		6
#define REMO_NUM7		7
#define REMO_NUM8		8
#define REMO_NUM9		9

#define REMO_STANDBY	12
#define REMO_CHNUP		32
#define REMO_CHNDN		33
#define REMO_VOLUP		16
#define REMO_VOLDN		17
#define REMO_SELECT		18
#define REMO_MENU		48
#define REMO_TV			63
#define REMO_VCR		60
#define REMO_SVIDEO		56
#define REMO_MUTE		13
#define REMO_INPUT		0xff

#define REMO_INFO		0x0a //??
#endif

//=============================================================================
//                                 NEC type
//=============================================================================
#elif defined REMO_NEC
/*
// Techwell Origin
#define REMO_CUSTOM1	0x20
#define REMO_CUSTOM2	0xdf


#define REMO_NUM0		0x08
#define REMO_NUM1		0x88
#define REMO_NUM2		0x48
#define REMO_NUM3		0xc8
#define REMO_NUM4		0x28
#define REMO_NUM5		0xa8
#define REMO_NUM6		0x68
#define REMO_NUM7		0xe8
#define REMO_NUM8		0x18
#define REMO_NUM9		0x98

#define REMO_STANDBY	0x10
#define REMO_CHNUP		0x00
#define REMO_CHNDN		0x80
#define REMO_VOLUP		0x40
#define REMO_VOLDN		0xc0
#define REMO_SELECT		0x70
#define REMO_MENU		0x9c
#define REMO_MUTE		0x90
#define REMO_INPUT		0xd0
*/

// Techwell New Remocon after 4/7/2005
#ifdef PHILIPS_REMOCON
#define REMO_CUSTOM1	0x02
#define REMO_CUSTOM2	0xfd

#define REMO_NUM0		0x00
#define REMO_NUM1		0x80
#define REMO_NUM2		0x40
#define REMO_NUM3		0xc0
#define REMO_NUM4		0x20
#define REMO_NUM5		0xa0
#define REMO_NUM6		0x60
#define REMO_NUM7		0xe0
#define REMO_NUM8		0x10
#define REMO_NUM9		0x90

#define REMO_STANDBY	0x48
#define REMO_CHNUP		0xd8
#define REMO_CHNDN		0xf8
#define REMO_VOLUP		0x58
#define REMO_VOLDN		0x78
#define REMO_SELECT		0xe8
#define REMO_MENU		0x01
#define REMO_MUTE		0x08
#define REMO_INPUT		0xf0

#define REMO_INFO		0x38



#define REMO_TTXRED			0x4E
#define REMO_TTXGREEN		0x8E
#define REMO_TTXYELLOW		0xC6
#define REMO_TTXCYAN		0x86

#else
// RYU For Test
#define REMO_CUSTOM1		0x04
#define REMO_CUSTOM2		0xfb

#define REMO_NUM0		0xf8
#define REMO_NUM1		0x48
#define REMO_NUM2		0xc8
#define REMO_NUM3		0x28
#define REMO_NUM4		0xa8
#define REMO_NUM5		0x18
#define REMO_NUM6		0x98
#define REMO_NUM7		0x58
#define REMO_NUM8		0xd8
#define REMO_NUM9		0x78

#define REMO_STANDBY	0x00
#define REMO_CHNUP		0x40	//
#define REMO_CHNDN		0x70	//
#define REMO_VOLUP		0x90	//
#define REMO_VOLDN		0xe0	//
#define REMO_SELECT		0x11//??
#define REMO_MENU		0x10

#define REMO_MUTE		0x60
#define REMO_INPUT		0xc0
#define REMO_AUTO		0x30
#define REMO_AUTOSCAN	0x80
#define REMO_TV			0x20
#define REMO_EXIT		0xa0
#define REMO_INFO		0x08
#define REMO_ASPECT		0x62

#define REMO_TTXRED		0xb8
#define REMO_TTXGREEN	0x02
#define REMO_TTXYELLOW	0x82
#define REMO_TTXCYAN	0x42

#ifdef SUPPORT_DEBUG
#define REMO_DEBUG		0xb8
#define REMO_READ		0x02
#define REMO_WRITE		0x82
#endif

#endif //PHILIPS_REMOCON

#endif // REMO_NEC



BYTE ActionRemo(BYTE, BYTE);
BYTE CheckKeyIn(void);
BYTE GetKey(BYTE repeat);
BYTE IsRemoDataReady(BYTE *, BYTE *);



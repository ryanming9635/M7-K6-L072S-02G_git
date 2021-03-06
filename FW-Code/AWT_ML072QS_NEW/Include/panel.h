//PanelConfig

	#if   defined SXGA
						#define PHR_ 1280
						#define PVR_ 1024
	#elif defined XGA	
						#define PHR_ 1024
						#define PVR_ 768
	#elif defined SVGA
						#define PHR_ 800
						#define PVR_ 600
	#elif defined VGA
						#define PHR_ 640
						#define PVR_ 480
	#elif defined QVGA
						#define PHR_ 320
						#define PVR_ 240
	#elif defined WXGA
						#define PHR_ 1280 //1366
						#define PVR_ 768
	#elif defined WSVGA
						#define PHR_ 1024
						#define PVR_ 600
	#elif defined WVGA
						#define PHR_ 800
						#define PVR_ 480//600
	#elif defined WQVGA
				//		#define PHR_ 960 //480
				//		#define PVR_ 237
						#define PHR_ 480 //480
						#define PVR_ 240
	#endif

 

/*
#define ACTIVE_LOW			0
#define ACTIVE_HIGH			1

CODE struct PanelConfig {
	unsigned		x_res,					y_res;
	unsigned char	h_sync_min_pulse_width, v_sync_min_pulse_width;
	unsigned		h_min_back_porch;
	unsigned char	h_sync_polarity,		v_sync_polarity;
	unsigned		dot_clock,				max_clock;			// in unit Mhz*10
	unsigned char	pixs_per_clock;
	unsigned char	DE_only;
} PanelConfig=
	{
	//----------------------------------------------------
	#ifdef WXGA
	//LG  LM171W01 WXGA
	1280,			768,
	8,				1,
	8,
	ACTIVE_LOW,		ACTIVE_LOW,
	#ifdef DOUBLE_PIXEL
	320,			470,
	2,
	#else
	650,			950,					//65Mhz
	1,
	#endif
	0
	//----------------------------------------------------
	#elif defined XGA
	//Samsung  LT150x1-151 XGA
	1024,			768,
	68,				1,
	80,
	ACTIVE_LOW,		ACTIVE_LOW,
	#ifdef DOUBLE_PIXEL
	325,			400,					//32.5Mhz
	2,
	#else
	650,			800,
	1,
	#endif
	0
	//----------------------------------------------------
	#elif defined SXGA
	//Samsung  LT170E2-131  SXGA
	1280,			1024,
	1,				1,
	1,
	ACTIVE_LOW,		ACTIVE_LOW,
	#ifdef DOUBLE_PIXEL
	540,			540,					//54.5Mhz
	2,
	#else
	1080,			1080,
	1,
	#endif
	0
	//----------------------------------------------------
	#elif defined WSVGA						// Thosiba
	1024,			600,
	8,				3,
	1,//80,				
	ACTIVE_LOW,		ACTIVE_LOW,
	#ifdef DOUBLE_PIXEL
	325,			450,
	2,
	#else
	500,			550,					//50Mhz
	1,
	#endif
	0
	//----------------------------------------------------

	#elif defined SVGA
	//NEC NL8060AC26-11 SVGA
	800,			600,
	2,				1,
	13,
	ACTIVE_LOW,		ACTIVE_LOW,
	#ifdef DOUBLE_PIXEL
	384,			500,					//38.4MHz
	2,
	#else
	670,			1000,
	1,
	#endif
	0
	//----------------------------------------------------
	#elif defined VGA
	//NEC NL6448AC33	VGA					// OK with SetPanelRegisters
	640,			480,
	10,				1,
	4,
	ACTIVE_LOW,		ACTIVE_LOW,
	#ifdef DOUBLE_PIXEL
	130,			150,					//25.2MHz
	2,
	#else
	250,			300,
	1,
	#endif
	0
	//----------------------------------------------------

	#elif defined WVGA
	// Panasonic  EDTCB27QBF WVGA
	800,			480,
	4,				1,
	7,
	ACTIVE_LOW,		ACTIVE_LOW,
	#ifdef DOUBLE_PIXEL
	166,			200,					//33.2MHz
	2,
	#else
	332,			360,					//33.2MHz
	1,
	#endif
	0

	//----------------------------------------------------
	#else
	// Default : XGA panel
	// Samsung  LT150x1-151 XGA
	1024,			768,
	68,				1,
	80,
	ACTIVE_LOW,		ACTIVE_LOW,
	#ifdef DOUBLE_PIXEL
	325,			400,					//32.5Mhz
	2,
	#else
	650,			800,					//32.5Mhz
	1,
	#endif
	0
	#endif
	};

*/
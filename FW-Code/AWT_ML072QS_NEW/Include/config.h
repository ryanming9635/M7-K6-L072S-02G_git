/*****************************************************************************/
/*                           System Configurations                           */
/*							rev 0.10 include auto test						 */
// 0.11 change DTV, PC input initial download data correct for Charge Pump
// 0.12 correct phase measurement routine '>>3'
// 0.13 enable function for SPI control... only EXT MCU case
// 0.14 corrected PC measurement......
// 0.0a test function only for CVBS, SVIDEO
// 0.15 corrected DTV scaler setting for panel resolutions
// 0.0b panel for AND 640x480 TICON panel
// 0.16 corrected COMPONENT scaler setting for panel resolutions	11/21/2007
// 0.0c automatic chip test
// 0.17 add monitor function, osd grid for writing grid
// 0.18 add component, dtv pc for analogpanel, 12/06/2007
// 0.19 correct pal input for CES, 12/20/2007
// 0.1a CCFL control, 12/28/2007
// 0.19 Multi Grid for Banking on Internal MCU	01/17/2008
// 0.20 CCFL contol for backlight brightness	01/21/2008
// 0.21 CCFL contol for backlight brightness	01/25/2008
// 0.22 phase setting 02/07/2008
// 0.221 display input correction 04/03/2008
// 0.23 PC, DTV mode, no signal display
// 0.24 PC Auto Color adjustment
// 0.25 revised PC Auto Clock adjustment - find divide number and phase
// 0.26 Digital RGB for TW8826
// 0.27 Correct LVDS control					08/22/2008
// 0.28 Add WSVGA resolution					10/23/2008
// 0.29 Add NEW GRID							11/14/2008
// 0.30 Fix DTV input							12/10/2008
// 0.31 Add 1080i23, 24, 25A, 25B				01/20/2009
// 0.32 TCON setting FIX all mode				01/22/2009
// 0.33 autodetect is auto on/off by dip sw1 	02/02/2009
// 0.34 Fix autocolor function and clamp position 02/08/2009
/*****************************************************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__

//#define INTERNAL_MCU -- defined by Project Compiler session
#define 	HS 				
//#define 	E_Wintek 	
//#define 	AWT	
//#define Holtz

//#define QUAD

#ifdef QUAD
	#define AWT_ML072Q  //Pinchi 20150827 disable for HTRV
//	#define HTRV  //Pinchi 20140902 disable for AWT ML072Q
#else
	#define AWT_ML072S
#endif

//--------------------------------------------------
//              Common Feature Define
//--------------------------------------------------
//#define FIRST_RUN_FROM_AC  //Pinchi 20150831 disable for Screen re-setting by Set4WideScreen()  //Pinchi 20141029 add
#define SUPPORT_ML072Q_AUTO_DAY_NIGHT  //Pinchi 20150825 add for function define
#define SUPPORT_TRIGGER_EXIT_MENU  //Pinchi 20150827 add for exit OSD Menu by CAM trigger
#define SUPPORT_AC_ON_NORMAL_SCREEN  //Pinchi 20150901 add to set 4:3 screen when AC on

#define FIX_DISPLAY_OFF_TRIGGER_ISSUE  //Pinchi 20150908 add to fix [Display] set OFF and trigger release then trigger again during display info the CAM will change from trigger CH to original CH
#define FIX_EXIT_STANDBY_NO_AUDIO  //Pinchi 20150908 add to fix no audio output when exit Standby mode
#ifdef AWT_ML072Q
#define FIX_2835_SCREEN_NOISE  //Pinchi 20160929 add to fix the screen noise of TW2835 by change DDR to make clock shift
#endif

#define SUPPORT_NEW_TRIGGER_FUNCTION  /////修改新的Trigger方式減少trigger polling 時間 add by ryan@20180124

//#define AWT_ML072QS_MSG  //Pinchi 20140925 add
//#define REDUCE_DELAY_TIME  //Pinchi 20141029 add
//#define DISPLAY_TECHWELL_LOGO  //Pinchi 2050903 add to disable the Techwell logo

//#define SUPPORT_SVIDEO                     //andy Awt 20090914
//#define SUPPORT_COMPONENT			// support component analog to decoder//andy Awt 20090914
//#define SUPPORT_DTV     			// support DTV input through component( to ADC ).//andy Awt 20090914
//#define SUPPORT_PC  			// support PC function
//#define SUPPORT_DVI				// support DVI input
//#define SUPPORT_SDCARD

#define SUPPORT_2835_CLK_TUNE_BACK_DOOR  //Pinchi 20160913 add to fine tune TW2835 clock by hot key
//#define SUPPORT_DISPLAY_TEST_VERSION  //Pinchi 20150929 add to display test software version on OSD

//--------------------------------------------------
//              Model Feature Define
//--------------------------------------------------
#if (defined AWT_ML072Q) || (defined AWT_ML072S)
#define AWT_ML072QS_FW_RULE  //Pinchi 20140902 add
//#define AWT_NEW_SLIM_MODEL  //Pinchi 20150203 add for AWT new slim model
#define AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for display "NO VIDEO SIGNAL" by AWT request of 20150302
#define AWT_TW2835_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon by TW2835 when CAM C trigger
#define SUPPORT_AC_ON_REDUCE_TIME  //Pinchi 20150903 add to reduce Power time when AC on

//#define SUPPORT_TRIGGER_RELEASE_DELAY  //Pinchi 20150908 add to support delay time when CAM trigger release

typedef enum  //Pinchi 20150326 add
{
     LAST_TRIG_NON = 	0x00,
     LAST_TRIG_LEFT = 	0x01,
     LAST_TRIG_RIGHT = 	0x02,
     LAST_TRIG_REVERSE =0x03,
     LAST_TRIG_CAMC = 	0x04,

} AWT_LAST_TRIGGER;

#endif


#ifdef HTRV  //Pinchi 20150825 add
#define HTRV_ML072Q_FW_RULE  //Pinchi 20150827 add
#define HTRV_REDUCE_SCREEN_CHANGE  //Pinchi 20150828 add to reduce screen double change

#if 0  //Pinchi 20151209 add to remove 4:3 screen by HTRV request of 20151209
#define HTRV_SUPPORT_4_3_SCREEN
#else
#undef SUPPORT_AC_ON_NORMAL_SCREEN  //Pinchi 20151210 add
#endif

#endif

//#define SUPPORT_RS485
//-----------------------------------------------------------------------------
//		Firmware Version
//-----------------------------------------------------------------------------
#ifdef HTRV  //Pinchi 20150907 add
//#define	FWVER			0x200	// Rev 2.00
//#define	FWVER			0x210		// Rev 2.1  //Pinchi 20151209 update version for HTRV request to remove 4:3 screen
//#define	FWVER			0x220		// Rev 2.2  //Pinchi 20160929 change for V2.2
#define	FWVER			0x230			//Rev 2.3 	 ryan@20170727 update version by Encoder switches零件 EOL更換
#else
#define	FWVER			0x210		// Rev 0.14
#endif

//-----------------------------------------------------------------------------
//		Compiler
//-----------------------------------------------------------------------------
#define KEILC						// Keil C 5.0
//-----------------------------------------------------------------------------
//		MPU Clock
//-----------------------------------------------------------------------------
#ifndef INTERNAL_MCU
//#define CLOCK_11M					// 11.0592MHz
#define CLOCK_22M					// 22.1184MHz
#else 								// INTERNAL_MCU
#define	CLOCK_27M					// 27MHz
#define	REG_START_ADDRESS	0xc000		// register start 0xc000, for page0, 0xc100-page1 
#endif
//-----------------------------------------------------------------------------
//		TW88 Version
//-----------------------------------------------------------------------------
#define TW8816   ///AWT TW8806 change to TW8816 platform //ryan@20170921
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//		Options for Backlight control
//-----------------------------------------------------------------------------
//#define	BACKLIGHT_CCFL
//#define	BACKLIGHT_LED
#define	BACKLIGHT_PWM

//-----------------------------------------------------------------------------
//		Panel Resolution
//-----------------------------------------------------------------------------
// ---- Select Default Panel
//
//#define UXGA						// 1600 x 1200
//#define SXGA    					// 1280 x 1024
//#define XGA  // 1024 x 768
#ifdef XGA
	#define LVDS					
	#define	PWIDTH	1024
	#define PHEIGHT	768
#endif
//#define SVGA						//  800 x 600
//#define VGA  						//  640 x 480
#ifdef VGA
	#define	PWIDTH	640
	#define PHEIGHT	480
	//#define	HITACHI_640_B_160		//--> 640 x 160
	#define AND_640_480
#endif
//#define WXGA						// 1280 x 768 (15:9) // 1366 x 768 (16:9)
#ifdef WXGA
    //#define WX_SHARP_LQ106K1LA
	#define	PWIDTH	1280
	#define PHEIGHT	768
#endif
//#define WSVGA						// 1024 x 600	*** only video mode
#ifdef WSVGA
	#define	PWIDTH	1024
	#define PHEIGHT	600
	#define UNIDEN_1024_600
#endif
#define WVGA						//  800 x 480
#ifdef WVGA
	#define	PWIDTH	800
	#define PHEIGHT	480//600
	// If WVGA, you have to select panel.
	//#define AU_10INCH
	//#define WVGA_TPO
	//#define SAMSUNG_10INCH
	//#define SAMSUNG_TICONLESS_10INCH
	//#define SHARP_TICONLESS_7INCH
	//#define AU_TICONLESS_7INCH
	//#define AU_G084SN05V8_8_4INCH	
	#define HSD070IDW1_7INCH
	//#define INNOLUX_AT080TN03
	//#define AU_TICONLESS_7INCH_CCFL
	//#define CMO			// CHIMEI panel
	//#define AU_TICONLESS_10INCH
	//#define HITACHI_T01
	//#define HITACHI_TX23D12
	//#define HITACHI_TX18D24
	//#define HITACHI_TX18D16
	//#define TMD_LTA070A320F
	//#define TMD_LTA080B
#endif	//WVGA
//#define HVGA						//  480 x 320
//#define QVGA						//  320 x 240	*** only video mode
#ifdef QVGA
	#define	PWIDTH	320
	#define PHEIGHT	240
	//#define HITACHI_TX09D73
	//#define AU_DELTARGB
	//#define SHARP_LQ050Q5DR01
	//#define SHARP_LQ035
	//#define	TMD
#endif

//#define WQVGA						//  480 x 234	*** only video mode
#ifdef WQVGA
	#define	PWIDTH	480
	#define PHEIGHT	240
	// If WQVGA, you have to select panel	
    #define ANALOG_7INCH
	//#define	PWIDTH	400
	//#define PHEIGHT	240
	//#define SHARP_LQ043T3DX02		//  400 x 237
	//#define LG_ANALOG
	//#define TMD_ANALOG				//TMD_LTA05B352A
	//#define	T_51945GD				// Optorex Panel
#endif 	// WQVGA

//if LVDS pannel disable TICONLESS

//-----------------------------------------------------------------------------
//---- Add Support One more panel with DIPSW#1
//---- Ex. Add Analog AU 7" Panel with Default Panel for evalution
//#define ADD_ANALOGPANEL		// Added Analog panel(AU7") from default set panel(expect WQVGA) with DIP #1 switch.(DIP#1=L:ANALOG, H:DEFAULT)
							// It can't support WQVGA and ADD_ANALOGPANEL same time!!
	//#define ADD_ANALOG_7INCH
	//#define ADD_TMD_LTA05B352A
									
//---- Support Wide panel function
#if (defined WXGA) || (defined WSVGA) || (defined WVGA) || (defined WQVGA)
#if 0///ryan@20180115//mask for NTSC sharpness issue
#define WIDE_SCREEN  				// Can support 4 display mode, i.e. Normal, Wide, Full, Zoom
#endif
#endif								// Tested panasonic WVGA panel.

//-----------------------------------------------------------------------------
//		Panel Vendor Specific
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//		TV Tuner
//-----------------------------------------------------------------------------
#define	PHILIPS				0
#define	ALPS				1		// ALPS, LG
#define	TEMIC				2
#define TVAVA				3
#define LGTUNER				4
#define SAMSUNGMUTITUNER	5

#define TVTunerDevice		4
//-----------------------------------------------------------------------------
//		IR Remote Controller Type
//-----------------------------------------------------------------------------
//#define REMO_RC5					// RC5 style
#define TECHWELL_REMOCON
//#define REMO_NEC					// NEC style
//#define PHILIPS_REMOCON // New remocon 

//-----------------------------------------------------------------------------
//		I2C Device Access Address Mapping
//-----------------------------------------------------------------------------

#define EEPROMI2CAddress	0xa0	// EEPROM (24C16)
#define TW88I2CAddress		0x8a	// TW880x

#define MSPI2CAddress		0x80	// MSP
#define ALC106I2CAddress	0x4A	// MSP
//-----------------------------------------------------------------------------
//		Options for Possible Inputs
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//		Options for Possible Standards
//		Default:NTSC
//-----------------------------------------------------------------------------
#define SUPPORT_PAL			
#define SUPPORT_SECAM
#define SUPPORT_NTSC4		
#define SUPPORT_PALM	
#define SUPPORT_PALN		
#define SUPPORT_PAL60		

//#define ID_CHECK_BY_FW  			// in Video mode, check input system ID by firmware

//-----------------------------------------------------------------------------
//		Options for Debugging/Release
//-----------------------------------------------------------------------------
//#define SUPPORT_PATTERN  			// support LCD test pattern

#ifndef WQVGA
	#ifndef QVGA
#define SUPPORT_OSDPOSITIONMOVE
	#endif
#endif

#define SERIAL      				// include serial communication routines

//#define SUPPORT_DEBUG				// Support to use Read & Write in debug OSD Window by remocon.

//#define DEBUG						// include debug information
#ifdef DEBUG
	//#define DEBUG_MAIN
	//#define DEBUG_TIME
	//#define DEBUG_KEYREMO
	//#define DEBUG_TW88
	//#define DEBUG_DECODER
	//#define DEBUG_I2C
	//#define DEBUG_EEP
	//#define DEBUG_OSD
	//#define DEBUG_AUDIO
	//#define DEBUG_SETPANEL
	//#define DEBUG_DTV
//	#define DEBUG_PC
	//#define DEBUG_PC_MEAS
	//#define DEBUG_PC_COLOR
	//#define DEBUG_COMPONENT
	//#define DEBUG_BANK
	//#define DEBUG_PAUSE
	//#define DEBUG_MCU
#endif

#define AUTOCALC_PC					// in PC mode, Enable Auto Calcuration
//#define SUPPORT_USERCOLORFROMTXT	// Use color setting of text file in Color mode=USER MODE which is as Brightness(Reg10), Contast(Reg11),
									//    Sat_U(Reg13),Sat_V(Reg14),Sharpness(Reg12,Reg78)									
//#define SUPPORT_GAMMA

//#define CHIP_MANUAL_TEST			// DIPSW#1

#ifndef INTERNAL_MCU
//#define NO_INITIALIZE				// After Power switch turn on with DIP SW4 Enable(Low), or pressed MENU button for internal MCU
                                    //     micom works to access only I2C bus by serial command.
#endif

//#define SUPPORT_KRS_OSDDEMO		// For KRS Company Demo 
//#define SUPPORT_LINE_OSDDEMO

//-----------------------------------------------------------------------------
//		Special Features
//-----------------------------------------------------------------------------

#ifndef INTERNAL_MCU
//#define	SUPPORT_DELTA_RGB
#endif
#define SUPPORT_SELECTKEY			// choose the keymap of using select key or left,right key.
//-----------------------------------------------------------------------------

//#define HS_NEWOSDMENU			//Weylis -@121008 for Hor. Style OSD
//#define HS_NEWOSDMENU_2			//Weylis -@121008 for Hor. Style OSD(2 line)

#endif	//__CONFIG_H__


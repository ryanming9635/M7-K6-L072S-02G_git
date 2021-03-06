/* CPU.c */

#include "config.h"

#include "typedefs.h"
#include "reg.h"
#include "regmap.h"
#include "cpu.h"
#include "main.h"
#include "I2C.h"
#include "TW88.h"
#include "Printf.h"
#include "KeyRemo.h"
#include "etc_eep.h"
#include "pc_eep.h"
#include "Audio.h"
#include "Measure.h"
#include "OSDBasic.h"
#include "OSDMenu.h"
#include "DispInfo.h"
//#include "Monitor.h"
#include "variables.h"
#include <math.h>
#include "main.h"

#include "HS_DisplayOSD.h"

#define ClearRemoTimer()	TR2 = 0

extern BYTE CAM_QUAD_TO;//ryan@20170928

extern  BYTE AV_MODE_DELAY;
extern BYTE Backlight_TO;

extern		  BYTE	DebugLevel;
#ifdef REMO_RC5
extern  BYTE RemoDataReady;
#endif
extern  BYTE RemoSystemCode, RemoDataCode;
extern 	BYTE InputSelection;
extern		  BYTE  VInputStdDetectMode;
extern	BYTE  VInputStd;

extern	BYTE	PcMode;
//extern		  bit	AutoDetect;
extern 		  bit	NoInitAccess;
extern	BYTE  DVR_RecordStatus;
//===================== Timer =================================================
		DATA BYTE keytic=0;
		DATA BYTE Key=0;
		bit KeyReady=0, RepeatKey = 0;

		DATA BYTE tm001;
		DATA  WORD  stopWatch;
		DATA  WORD  tm01=0;
		DATA  BYTE  tic01=0;	//, tic_pc;
		DATA  WORD  tic_pc=0;

		DATA DWORD	SystemClock;			//00:00
	//#ifdef Format_SDCard	
		BYTE FormatSDCard=1;
	//#endif
//		xdata DWORD	LastBlockedTime;		//00:00
//static  DATA WORD	WakeupTime;
//static  DATA BYTE	WakeupPR;

//		 WORD	OffTime;	 
//		 BYTE	SleepTimer;
//		 WORD	SleepTime;
#ifdef CHIP_MANUAL_TEST //==============================================================
extern	BYTE ManualFrequency;
extern  bit		OnChipTest;
#endif			//==============================================================

#ifdef SERIAL //=======================================================================

static	DATA BYTE	RS_buf[BUF_MAX];
		DATA BYTE	RS_buf2[BUF_MAX];
		DATA BYTE	DVR_buf[DVR_BUF_MAX];
		
		DATA BYTE	RS_in, RS_out;
		DATA BYTE	RS2_in;
		bit			RS_Xbusy=0;			// bit RS_Xbusy=0;
		bit			RS2_Xbusy=0; 		// bit RS_Xbusy=0;
		
#endif	// SERIAL ======================================================================

//================== Remocon ==================================================
#ifdef REMO_RC5

static	bit 	RemoPhase1, RemoPhase2;
		IDATA	BYTE	RemoDataReady=0;
		IDATA	BYTE	RemoSystemCode, RemoDataCode;

#elif defined REMO_NEC

static  bit     RemoPhase=0;
static  IDATA	BYTE	RemoStep=0;
static  IDATA	BYTE	RemoHcnt, RemoLcnt;
		IDATA	BYTE	RemoData[4];
	    IDATA	BYTE	RemoDataReady=0;
static  IDATA	BYTE	RemoNum, RemoBit;

	    IDATA	BYTE	RemoDataCode=0xff;
#endif	//================== Remocon ======================

BYTE 	keyticSec=0;
BYTE	FormatWait=0;
BYTE	PowerDownWait=0;
BYTE  updn_reg[4]={0,0,0,0};
bit ChangeKey;
BYTE Time5ms;

extern BYTE SEQFlag;

 extern bit 	FormatStart;
extern bit	 PowerDownStart;
extern BYTE 	KeyBuffer;
extern BYTE	year1,year2,month,day,hour,minute,second;
extern BYTE	lock_keycnt;
extern BYTE	DVR_SDCardAvailable;
//#ifndef QUAD
extern BYTE	displayhold_flag;  //Pinchi 20150319 enable
//#endif
extern BYTE TriggerFlag;//ryan@20170914

//====================HS 2835Command================ Andy AWT 980928
code unsigned char *CommTable[] = { 
    {"hscom 1 1 ch0:1%1bx ch1:0%1bx ch2:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x00 CAM A
    {"hscom 1 1 ch1:1%1bx ch0:0%1bx ch2:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x01 CAM B
#ifdef AWT_TW2835_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon by TW2835 when CAM C trigger
    {"hscom 1 1 ch2:%bx ch0:0%1bx ch1:0%1bx ch3:0%1bx\n\r"},          // INDEX_ID=0x02 CAM C
#else
    {"hscom 1 1 ch2:1%1bx ch0:0%1bx ch1:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x02 CAM C
#endif
    {"hscom 1 1 ch3:1%1bx ch0:0%1bx ch1:0%1bx ch2:0%1bx\n\r"},        // INDEX_ID=0x03 CAM R
    {"hscom 2 2 ch0:1%1bx ch1:0%1bx ch2:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x04 CAM A+B
#ifdef AWT_TW2835_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon by TW2835 when CAM C trigger
    {"hscom 2 2 ch2:%bx ch3:1%1bx ch0:0%1bx ch1:0%1bx\n\r"},        // INDEX_ID=0x05 CAM C+R
#else
    {"hscom 2 2 ch2:0%1bx ch3:1%1bx ch0:0%1bx ch1:0%1bx\n\r"},        // INDEX_ID=0x05 CAM C+R
#endif
    {"hscom 2 2 ch0:0%1bx ch3:1%1bx ch1:0%1bx ch2:0%1bx\n\r"},        // INDEX_ID=0x06 CAM A+R
    {"hscom 2 2 ch3:1%1bx ch1:0%1bx ch0:0%1bx ch2:0%1bx\n\r"},        // INDEX_ID=0x07 CAM R+B
    {"hscom 3 1 ch3:1%1bx ch0:0%1bx ch1:0%1bx ch2:0%1bx\n\r"},        // INDEX_ID=0x08 CAM R+A+B T1
    {"hscom 3 3 ch0:0%1bx ch1:0%1bx ch3:1%1bx ch2:0%1bx\n\r"},        // INDEX_ID=0x09 CAM A+B+R T3
    {"hscom 3 4 ch0:0%1bx ch1:0%1bx ch3:1%1bx ch2:0%1bx\n\r"},        // INDEX_ID=0x0A CAM A+B+R T4
    {"hscom 4 1 ch0:0%1bx ch1:0%1bx ch2:0%1bx ch3:1%1bx\n\r"},        // INDEX_ID=0x0B CAM A+B+C+R
    {"hscom 2 2 ch0:1%1bx ch2:0%1bx ch1:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x0C CAM A+C
#ifdef AWT_TW2835_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon by TW2835 when CAM C trigger
    {"hscom 2 2 ch2:%bx ch1:0%1bx ch0:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x0D CAM C+B
#else
    {"hscom 2 2 ch2:1%1bx ch1:0%1bx ch0:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x0D CAM C+B
#endif
    {"hscom 3 3 ch3:1%1bx ch0:0%1bx ch1:0%1bx ch2:0%1bx\n\r"},         // INDEX_ID=0x0E CAM R+AB //Ryan

  //Andy A1.4 2009 1 12 
    {"hscom 2 2 ch3:1%1bx ch2:0%1bx ch1:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x0F CAM R+C
    {"hscom 3 1 ch3:1%1bx ch0:0%1bx ch2:0%1bx ch1:0%1bx\n\r"},        // INDEX_ID=0x10 CAM R+A+C T1
    {"hscom 3 1 ch3:1%1bx ch1:0%1bx ch2:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x11 CAM R+B+C T1
    {"hscom 3 3 ch3:1%1bx ch0:0%1bx ch2:0%1bx ch1:0%1bx\n\r"},        // INDEX_ID=0x12 CAM R+AC T3
    {"hscom 3 3 ch3:1%1bx ch1:0%1bx ch2:0%1bx ch0:0%1bx\n\r"},         // INDEX_ID=0x13 CAM R+BC T3
  //Andy A1.4 2009 1 13 
    {"hscom 3 3 ch0:1%1bx ch1:0%1bx ch2:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x14 CAM A+B+C T3
    {"hscom 3 3 ch0:0%1bx ch2:0%1bx ch3:1%1bx ch1:0%1bx\n\r"},        // INDEX_ID=0x15 CAM A+C+R T3
  //Andy A1.4 2009 1 13 
    {"hscom 2 2 ch1:1%1bx ch0:0%1bx ch2:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x16 CAM B+A
    {"hscom 2 2 ch1:1%1bx ch2:0%1bx ch3:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x17 CAM B+C
    {"hscom 2 2 ch1:0%1bx ch3:1%1bx ch2:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x18 CAM B+R
    {"hscom 3 3 ch1:1%1bx ch0:0%1bx ch2:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x19 CAM B+A+C T3
    {"hscom 3 3 ch1:0%1bx ch0:0%1bx ch3:1%1bx ch2:0%1bx\n\r"},        // INDEX_ID=0x1A CAM B+A+R T3
    {"hscom 3 3 ch1:0%1bx ch2:0%1bx ch3:1%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x1B CAM B+C+R T3
#ifdef AWT_TW2835_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon by TW2835 when CAM C trigger
    {"hscom 2 2 ch2:%bx ch0:0%1bx ch1:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x1C CAM C+A
    {"hscom 2 2 ch2:%bx ch1:0%1bx ch3:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x1D CAM C+B
    {"hscom 2 2 ch2:%bx ch3:1%1bx ch1:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x1E CAM C+R
    {"hscom 3 3 ch2:%bx ch0:0%1bx ch1:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x1F CAM C+A+B T3
    {"hscom 3 3 ch2:%bx ch0:0%1bx ch3:1%1bx ch1:0%1bx\n\r"},        // INDEX_ID=0x20 CAM C+A+R T3
    {"hscom 3 3 ch2:%bx ch1:0%1bx ch3:1%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x21 CAM C+B+R T3
#else
  //Andy A1.4 2009 1 13 //C trigger
    {"hscom 2 2 ch2:1%1bx ch0:0%1bx ch1:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x1C CAM C+A
    {"hscom 2 2 ch2:1%1bx ch1:0%1bx ch3:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x1D CAM C+B
    {"hscom 2 2 ch2:0%1bx ch3:1%1bx ch1:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x1E CAM C+R
    {"hscom 3 3 ch2:1%1bx ch0:0%1bx ch1:0%1bx ch3:0%1bx\n\r"},        // INDEX_ID=0x1F CAM C+A+B T3
    {"hscom 3 3 ch2:0%1bx ch0:0%1bx ch3:1%1bx ch1:0%1bx\n\r"},        // INDEX_ID=0x20 CAM C+A+R T3
    {"hscom 3 3 ch2:0%1bx ch1:0%1bx ch3:1%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x21 CAM C+B+R T3
#endif

#ifdef HTRV
  #if 1  //Pinchi 20150908 add to fix R/C no audio output
    {"hscom 2 1 ch3:1%1bx ch2:0%1bx ch1:0%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x22 CAM R+c 
  #else
    {"hscom 2 1 ch3:1%1bx ch2:0%1bx ch1:1%1bx ch0:0%1bx\n\r"},        // INDEX_ID=0x22 CAM R+c 
  #endif
#endif
};
//=========================End===================


CODE BYTE PanelInfoStr[]={
#if (defined UXGA)						// 1600 x 1200
	"---> Panel: UXGA-1600*1200"
#elif (defined SXGA)    					// 1280 x 1024
	"---> Panel: SXGA-1280*1024"
#elif (defined  XGA)  						// 1024 x 768
	"---> Panel: XGA-1024*768"
#elif (defined SVGA)						//  800 x 600
	"---> Panel: SVGA-800*600"
#elif (defined VGA)  						//  640 x 480
	"---> Panel: VGA-640*480"
#elif (defined WXGA)						// 1280 x 768 (15:9) // 1366 x 768 (16:9)
	"---> Panel: WXGA-1280*768(15:9) or 1366*768(16:9)"
#elif (defined WSVGA)						// 1024 x 600	*** only video mode
	"---> Panel: WSVGA-1024*600"
#elif (defined WVGA)						//  800 x 480
	#ifdef AU_10INCH
	"---> Panel: WVGA-800*480 -- TTL AU 10inch"
	#elif (defined SAMSUNG_10INCH)
	"---> Panel: WVGA-800*480 -- TTL SAMSUNG 10inch"
	#elif (defined SAMSUNG_TICONLESS_10INCH)
	"---> Panel: WVGA-800*480 -- TICONLESS SAMSUNG 10inch"
	#elif (defined SHARP_TICONLESS_7INCH)
	"---> Panel: WVGA-800*480 -- TICONLESS SHARP 7inch"
	#elif (defined AU_TICONLESS_7INCH)
	"---> Panel: WVGA-800*480 -- TICONLESS AU 7inch"
	#elif (defined HSD070IDW1_7INCH)
	"---> Panel: WVGA-800*480 -- TICONLESS HS 7inch"
	#elif (defined AU_TICONLESS_10INCH)
	"---> Panel: WVGA-800*480 -- TICONLESS AU 10inch"
	#elif defined HITACHI_T01
	"---> Panel: WVGA-800*480 -- TICONLESS Hitachi TX18D24VM2BAA"
	#elif defined HITACHI_TX23D12
	"---> Panel: WVGA-800*480 -- TICONLESS Hitachi TX23D12"
	#elif defined HITACHI_TX18D24
	"---> Panel: WVGA-800*480 -- TICONLESS Hitachi TX18D24"
	#else
	"---> Panel: WVGA-800*480"
	#endif
#elif (defined HVGA)						//  480 x 320
	"---> Panel: HVGA-480*320"
#elif (defined QVGA)						//  320 x 240	*** only video mode
	"---> Panel: QVGA-320*240"
#elif (defined WQVGA)						//  480 x 234	*** only video mode
    #ifdef ANALOG_7INCH
	"---> Panel: WQVGA-480*234 -- ANALOG TICONLESS AU 7inch"
	#elif (defined SHARP_LQ043T3DX02)
	"---> Panel: WQVGA-480*234 -- TTL SHARP LED 4.3inch panel"
	#else
	"---> Panel: WQVGA-480*234 "
	#endif
#endif
};

#ifdef ADD_ANALOGPANEL		// Added Analog panel(AU7") from default set panel(expect WQVGA) with DIP #1 switch.(DIP#1=L:ANALOG, H:DEFAULT)
CODE BYTE AddedAnalogPanelStr[]={
		#ifdef ADD_ANALOG_7INCH
	"---> Added Analog Panel(AU 7inch) with DIP SW1=Enabled"
		#elif defined ADD_TMD_LTA05B352A
	"---> Added Analog Panel(TMD 4inch) with DIP SW1=Enabled"
		#endif
};
#endif

#if 0		//william-981029
//=============================================================================
//                            CheckSpecialMode                                                   
//=============================================================================
void CheckSpecialMode(void)
{
	BYTE i;

	i = GetKey(0);

	switch( i ) {
	case MENUKEY:
		Puts("\r\n---- Menu Key is pressed -> Enter Special Mode( To Composite )");
		SaveInputSelectionEE(CH_TW2835);
		DebugLevel = 0;
///		PcDetectFlag = 0;
		break;
	}
}
#endif

//=============================================================================
//    Main Initialize Routine
//=============================================================================
void main_init (void)
{
	extern CODE BYTE *OutOfRangeStr[] ;

	//BYTE	ikey;
	WORD	rev;

	WriteTW88(0xe0, 0x10);	// Disable I2C auto increase mode
	//PowerLED(ON);
	//EnableRemoconInt();
#if 0		//981103
	ikey = ResetMSP();
	if( ikey ) 
	{
		#ifdef DEBUG
		dPrintf("\r\nError on resetting MSP:0x%02x", (WORD)ikey);
		#endif
	}
#endif
	rev = GetFWRevEE();
	Printf("\r\nPrev.FW:%04x", rev);

	if( GetFWRevEE()!=FWVER ) 	// exist EEPROM
	{					
		Printf("\r\nCurr.FW:%04x", (WORD)FWVER);
		SaveFWRevEE(FWVER);
		Printf("\r\nCurr.FW:%04x", (WORD)GetFWRevEE());
	}

	//---------- if FW version is not matched, initialize EEPROM data -----------

	if( GetFWRevEE()==FWVER )
	{					// exist EEPROM
		if( rev != FWVER ) 
		{					//
			SaveDebugLevelEE(DebugLevel);
			//Printf("\r\nNew DebugLevel:%02x", (WORD)DebugLevel);//andy awt084 980928

			SaveInputSelectionEE(CH_TW2835);
			ClearBasicEE();
			Printf("\r\n[MSG]main_init()=> rev != FWVER & call ClearBasicEE()\r\n");  //pinchi test
			#ifdef SUPPORT_PC
			ResetPanelAttributeValue();
			SaveDefaultPCDataAllEE();
			#endif
		}
		else 
		{
		////ClearBasicEE();
			DebugLevel = GetDebugLevelEE();
			//Printf("\r\nSaved DebugLevel:%02x", (WORD)DebugLevel);//andy awt084 980928
		}
	}
	else 
	{
		Printf("\r\nCannot access EEPROM!!!!");
		Printf("\r\nNo initialize");
		DebugLevel = 0xff;
		SetVInputStd( NTSC );
	////	InitVideoData(VInputStd);
	#ifdef DISPLAY_TECHWELL_LOGO  //Pinchi 2050903 add
		DisplayLogo();
	#endif
		LCDPowerON(0);
		return;
	}

	#ifdef SUPPORT_GAMMA
	DownLoadGamma();
	#endif

#if 1		//awt ml073q william-20120308
	VInputStdDetectMode = GetVInputStdDetectModeEE();
	if( VInputStdDetectMode != AUTO )
		SetVInputStd( VInputStdDetectMode );
	else
		SetVInputStd( NTSC );

	SetPossibleAutoDetectStdEE();

	//InputSelectionInx  = 0;
	InputSelection  = UNKNOWN;		//GetInputSelectionEE();
////	InitVideoData(VInputStd);
#endif
	//ChangeInput( GetInputSelectionEE() );

	Change_OSDColorLookup();
	DownloadUDFont();

#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
	DisplayInformation(InfoNoVideoSignal);
	delay(10);
	ClearGAUGEINFO();
#endif

	//AutoDetect = 0;
#ifdef ALC106  //Pinchi 20140925 add for AWT ML072Q
	WriteALC106(0x04,0xC000);
	ReadALC106(0x04);
	WriteALC106(0x02,0x9E9E);
#endif
	
#ifdef Monitor_debug
	Prompt();
#endif

	//panel mirror  //william-20120921
	WriteTW88( 0xff, 0x01);
	WriteTW88( 0x82, 0x01);
	//WriteTW88( 0x82, 0x0c);
	WriteTW88( 0xff, 0x00);
	
	//////////////////////////////////////////////////////////////////////////////////

	WriteTW88( 0xd0, 0xff);	// clear status
	WriteTW88( 0xd1, 0xff);	// clear status
}

//=============================================================================
//                            Initialize WINBOND CPU                                                   
//=============================================================================
void InitCPU(void)
{
	CHPENR = 0x87;		// Enable AUX RAM in Winbond(W78E516B)
	CHPENR = 0x59;		//
	CHPCON = 0x10;		//
	CHPENR = 0x00;		// Write Disable

	/*----- Initialize interrupt -------------*/

	TH1 = 0xf4; 		//    SMOD = 0      SMOD =1	//andy AWT 980924					
						// 0ffh :57600 bps				
						// 0fdh : 9600 bps	0fdh :19200 bps				
						// 0fah : 4800 bps								
						// 0f4h : 2400 bps								
						// 0e8h : 1200 bps								

	SCON = 0x50;		// 0100 0000 mode 1 - 8 bit UART				
						// Enable serial reception						
    TMOD = 0x22;		// 0010 0010 timer 0 - 8 bit auto reload		
						// timer 1 - baud rate generator				
    TCON = 0x55;		// 0101 0001 timer 0,1 run						
						// int 0,  edge triggered						
						// int 1,  edge triggered						
						// TF1 TR1 TF0 TR0	EI1 IT1 EI0 IT0				
	TH0 = TL0 = 64;		// 64=4608 Hz at 11.0592MHz

	PCON = 0x80;		// 0000 0000 SMOD(double baud rate bit) = 1		
	IP	 = 0x02;		// 0000 0000 interrupt priority					
						// -  - PT2 PS PT1 PX1 PT0 PX0	 		         

	#ifdef SERIAL
	IE	 = 0x92;		// 1001 0010 interrupt enable:Serial,TM0		
  						// EA - ET2 ES ET1 EX1 ET0 EX0					

	TI	 = 1;			// LJY000724 // For Starting Serial TX 
	ES   = 1;			// LJY000724
	#else
	IE   = 0x82;
	#endif // SERIAL

	//------------ Timer 2 for Remocon --------------------------------
	T2CON  = 0x00;				// Timer2 Clear
	TR2	   = 0;
	ET2    = 1;
	//-----------------------------------------------------------------

	//Uart2
	//P0M0=0x7F;
	//P1M0=0x04;
       S2CON=0x50;                                 //Set UART Mode 1
       S2BRT=0xf4;                                 //Set 2UART overflow rate
    //AUXR2=0x08;                                 //SMOD = 1,TX12 = 0 (/12)
    //AUXR2|=0x10;                                //S2TR = 1
	AUXR2 |= 0x18;

	// Enable serial interrupt
	AUXIE |= 0x10;

	RS2_Xbusy=0;

//set pwm port 1.6
	CCAPM4=0x42;
	CCON	|=	0x40;				//Start PCA Counter

	//ADC P1.6
	//P1M0=0x80;					//set input p1.6 
	
 	//P2M0=0x01;
	//P2M1=0x01;
	P3M0=0x00;
	P3M1=0x20;


    #ifdef SERIAL//ryan@20170824
    RS_in = RS_out = 0;
    #endif  // SERIAL
}

//#define _ReadKey()		( ((~P4>>2)& 0x01) | (~P1 & 0xfc) )
#ifndef INTERNAL_MCU
  #ifdef AWT_NEW_SLIM_MODEL  //Pinchi 20150203 add for AWT new slim model
  #define _ReadKey() 		((~P2 & 0xFC))
  #else
  #define _ReadKey() 		((~P2 & 0x9c)) //ANDY awt 980907
  #endif
#else
#define _ReadKey()  		( ((~P4>>2)& 0x01) | (~P1 & 0xfe) )
#endif



////////////////////////////////

//INTERRUPT(1, timer0_int)
void timer0_int(void) interrupt 1 using 1			// interrupt number1, bank register 2
{
	BYTE TempKey;

	tm001++;

	//Kane @HS 2007 0814 Ver1.31>>>>
	if(Time5ms)
		Time5ms--;
	if(Time5ms==0)
	{
	#ifdef AWT_NEW_SLIM_MODEL  //Pinchi 20150203 add for AWT new slim model
		TempKey = (((P2 & 0x30) >> 4) & 0x03);
	#else
		TempKey=(( (P2&0x60) >> 5) & 0x03);
	#endif
		if(updn_reg[3] != TempKey )  // (( (P2&0x60) >> 5) & 0x03))    //Abel for HS SW key ......951102                                       
		{                                                                                          
			updn_reg[0] = updn_reg[1];                                                              
			updn_reg[1] = updn_reg[2];                                                              
			updn_reg[2] = updn_reg[3];                                                              
			updn_reg[3] = TempKey;// ( (P2&0x60) >> 5) & 0x03; 
			ChangeKey = 1;		
			//else			//william-v1.42-961130
			//ChangeKey=0;  //william-v1.42-961130
			//Time5ms = (48);
			Time5ms = (40);
		
			
		}
	}
   	//Kane @HS 2007 0814 Ver1.31<<<<
	
	//---------- 0.01 sec timer ------------
	
	#ifdef CLOCK_11M
	if( tm001 > 48 ) {			// LJY001220 0.01sec
	#elif defined CLOCK_22M
	if( tm001 > 48*2 ) {		// LJY001220 0.01sec
	#endif

		stopWatch++;
		tm001 = 0;
		tic01++;
if(Backlight_TO>1)	Backlight_TO--;
		
		if( tic01==100 ) 
		{				// 1 sec
		 	if(SEQTime<255) SEQTime++;
			SystemClock++;
			tic01 = 0;
		//date	
	//#ifndef QUAD
	#if 1  //Pinchi 20141017 enable for AWT ML072Q
		if(displayhold_flag>1)
			displayhold_flag--;

             if(CAM_QUAD_TO>1)
			 	CAM_QUAD_TO--;//ryan@20170928	
	#endif

		second++;

		if(lock_keycnt>0)
			lock_keycnt--;

		if(FormatStart==1)
			FormatWait++;
		if(PowerDownStart==1)
			PowerDownWait++;
		if(second==60)
		{
			second=0;
			minute++;
		}

		if(minute==60)
		{
			minute=0;
			hour++;
		}

		if(hour==24)
		{
			hour=0;
			day++;
		}			

		if(Key)
			keyticSec++;
		else
			keyticSec=0;
	//#ifdef Format_SDCard
	#ifdef SUPPORT_SDCARD  //Pinchi 20141014 add for AWT ML072Q
		 if(((DVR_RecordStatus&NORMAL_Record)!=NORMAL_Record) && DVR_SDCardAvailable!=0xff && FormatSDCard!=0)
		 	FormatSDCard++;
	#endif	

		}
	
		
		if( tic_pc!=0xffff ) 
			tic_pc++;

		///////////////////////////////////////////	
		if( _ReadKey() ) {
			if( keytic==3 ) {
				Key = _ReadKey();
				RepeatKey = 0;
				KeyReady = 1;
			}
			else if( keytic==100 ) {
				Key = _ReadKey();
				RepeatKey = 1;
				KeyReady = 1;
				keytic = 80;
			}
			keytic++;
		}
		else 
		{
			keytic = 0;
			Key=0;
		}
		///////////////////////////////////////////	
	}
}

//------------------------------------------------------------------
// void	InitVars(void) - variable initialize
//------------------------------------------------------------------
void	InitVars(void)
{
	SystemClock=0;			//00:00
	//LastBlockedTime=0xffffffff;		//00:00	//ljy010904...CC_FIX_CLEAR_ON_TIME..oops! previous vchip clear error 
	//OffTime=0xffff;
	//SleepTimer=0;
	//SleepTime=0xffff;

	//SEL_DVI=  1;		// disable Digital VGA
	// ResetKey();

	DebugLevel		= 0;
#ifdef REMO_RC5
	RemoDataReady	= 0;
#endif
	//P0_7 = 1;
	delay(100);
	PowerDown_XTAL(0);
	
	TW88HWReset = 1;
	delay(1);
}

//------------------------------------------------------------------
// void	InitTechwell(void) - Techwell Decoder initialize
//------------------------------------------------------------------
void	InitTechwell( void )
{
	#ifdef NO_INITIALIZE
	if( P0_3==0 ) {// No Initialize
		NoInitAccess =1;
		Printf("\r\n No-initialize Test going on with DIP SW4 ..: %d\n", (WORD)P0_3);
		return;
	}
	#endif
	#ifdef CHIP_MANUAL_TEST
	if( P0_0==0 ) OnChipTest =1;
	ManualFrequency = 2; //1;
	#endif

#ifdef AWT_ML072QS_MSG  //Pinchi 20140925 add
	Puts("\r\n\nDetect ");
#endif

	switch( ReadTW88(0) ) {
		case 0x21:	Puts("TW8816");		break;
		case 0x22:	Puts("TW8816B");	break;
		case 0x49:	Puts("TW8817");		break;
		default:	Printf("Nothing --0x%02x\r\n", (WORD)ReadDecoder(0)); 
			while(1) {
				#ifdef SERIAL
				if( RS_ready() ) break;
				#endif

				Printf("Check again --0x%02x\r\n", (WORD)ReadDecoder(0));
				delay(99);
				if( ReadTW88(0)==0 ) continue;
				if( ReadTW88(0)==0xff ) continue;
				break;
			}

			delay(99);
			delay(99);
			Printf("Last Check --0x%02x\r\n", (WORD)ReadDecoder(0));
		break;
	}

#ifdef AWT_ML072QS_MSG  //Pinchi 20140925 add
	Printf("%s \n", PanelInfoStr);
#endif
	//CheckSpecialMode();		//william-981029
}	


//=============================================================================
//                            Power LED ON / OFF                                                   
//=============================================================================
void PowerLED(BYTE flag)
{
//#define	GREEN_LED	P3_5
//#define RED_LED		P3_3		P4^1

	if( flag==ON ) {
		//GREEN_LED = 0;		// ON GREEN
		P4=P4&0xFE;		//GREEN_LED = 0;		// ON GREEN
		P4=P4|0x02;		//RED_LED = 1;		// OFF RED
		dPuts("\r\n(PowerLED)-ON");
		}
	else if(flag==OFF)
		{
		//GREEN_LED = 1;		// OFF FREEN
		P4=P4|0x01;		//GREEN_LED = 1;		// OFF GREEN
		P4=P4&0xFD;		//RED_LED = 0;		// ON RED
		dPuts("\r\n(PowerLED)-OFF");
		}
	else if(flag==2)
		{
		//GREEN_LED = 1;		// OFF FREEN
		P4=P4|0x01;		//GREEN_LED = 1;		// ON GREEN
		P4=P4|0x02;		//RED_LED = 1;		// OFF RED
		dPuts("\r\n(PowerLED)-OFF");
		}
}


//------------------------ common routines with interrupts --------------------

/*****************************************************************************/
/*      Ext Int 1 Interrupt                                                  */
/*****************************************************************************/
//INTERRUPT(2, ext1_int)
void	ext1_int(void) interrupt 2 using 1
{
	EX1 = 0;
}

//****************************************************************************/
//      Timer 0 Interrupt                                                  
//			If TL0 overflow,
//			 .Invoke this interrupt
//			 .TL0 <- TH0
//			TL0 is incremented every machine cycle
//			Every machine cycle is 12*Tosc(11.0592MHz)
//
//			Every machine cycle = 1.085us
//			Interrupt interval = 208us ( 1.085*(256-64(TH0)) )
//			When tm001==48, it's 0.01sec.  48*208us
//							
//****************************************************************************/


//=============================================================================
//			Remocon
//=============================================================================

#ifdef REMO_RC5

void InitForRemo(void)
{
	WORD temp;

	#if defined CLOCK_11M

	#ifdef TECHWELL_REMOCON // DONGYANG
	temp = 0x10000 - 193;	// 209.62us = 1.085*193
	#else
	temp = 0x10000 - 204;	// 221.34us = 1.085*204
	#endif
	
	#elif defined CLOCK_22M

	#ifdef TECHWELL_REMOCON // DONGYANG
	temp = 0x10000 - 193*2;	// 209.62us = 1.085/2*193*2
	#else
	temp = 0x10000 - 204*2;	// 221.34us = 1.085/2*204*2
	#endif

	#elif defined CLOCK_27M		// intenal_mcu

	#ifdef TECHWELL_REMOCON // DONGYANG
	temp = 0x10000 - 20;	// 209.62us = 1/27 * 283 * 20 = 209.63uS
	T2HIGH = 1;			// 283 = 256 + 27
	T2LOW = 27;			// 
	#else
	temp = 0x10000 - 36;	// 221.34us = 1/27 * 166 * 36 = 221.33uS
	T2HIGH = 0;			// 
	T2LOW = 166;			// 
	#endif

	#endif

	RCAP2H = TH2 = temp>>8;
	RCAP2L = TL2 = (BYTE)(temp & 0xff);
	TR2    = 1;

	tm01 = 4;
	RemoPhase1 = 1;
	RemoSystemCode= RemoDataCode=0;
}

#elif defined REMO_NEC

void InitForRemo(void)
{
	WORD temp;

	#if defined CLOCK_11M
	temp = 0x10000 - 173;	// 187.71us = 1.085*173
	#elif defined CLOCK_22M
	temp = 0x10000 - 173*2;
	#elif defined CLOCK_27M	
	T2HIGH = 0;			// 
	T2LOW = 252;			// 
	temp = 0x10000 - 20;	// 186.667uS = 1 /27 * 252 * 20
	#endif

	RCAP2H = TH2 = temp>>8;
	RCAP2L = TL2 = (BYTE)(temp & 0xff);

	TR2 = 1;

	tm01 = 0;
	RemoStep  = 0;
	RemoPhase = 0;
	RemoHcnt  = 0;
	RemoLcnt  = 0;
}

#endif

#ifdef REMO_RC5

///****************************************************************************
///*      Ext Int 0 Interrupt                                                
///****************************************************************************
//_interrupt(0) void remocon_int (void)
//INTERRUPT(0, remocon_int)
void	remocon_int(void) interrupt 0 using 1
{
	EX0 = 0;	// Enable Remocon (Enable Ext int0)
	InitForRemo();
}
#endif
//*****************************************************************************
//      Serial Interrupt                                                   
//*****************************************************************************
#ifdef SERIAL

//INTERRUPT(4, serial_int)
void serial_int(void) interrupt 4 using 1		// register bank 1
{
	
	//day++;
	//year2=RI;
	//year1=TI;
	if( RI ) {					//--- Receive interrupt ----
		RI = 0;
		RS_buf2[RS_in]=RS_buf[RS_in]=/*DVR_buf[RS_in]=*/ SBUF;//andy awt 980928
		//month++;
	    RS_in++;
		if( RS_in>=BUF_MAX/*DVR_BUF_MAX*/) RS_in = 0;
	}

	if( TI ) {					//--- Transmit interrupt ----
		TI = 0;
		RS_Xbusy=0;
	}
}

#if 1
//INTERRUPT(12, serial2_int)
void serial2_int(void) interrupt 12 using 1		
{
	//--- Receive interrupt ----
	//day++;
	//year2=S2CON&0x0f;
	if ((S2CON & 0x01) == 0x01)
		{					
		// Clear reception flag
		S2CON = S2CON&0xfe;
		DVR_buf[RS2_in] = S2BUF;
		//month++;
	    RS2_in++;
		if( RS2_in>=/*BUF_MAX*/DVR_BUF_MAX) RS2_in = 0;
	}
	
	if ((S2CON & 0x02) == 0x02)
	{
		S2CON = S2CON&0xfd;
		RS2_Xbusy = 0;
	}
}

#endif

//=============================================================================
//		Serial RX Check 												   
//=============================================================================
BYTE RS_ready(void)
{
	if( RS_in == RS_out ) return 0;
	else return 1;
}


#ifdef Monitor_debug

//=============================================================================
//		Serial RX														   
//=============================================================================
BYTE RS_rx(void)
{
	BYTE	ret;
		
	ES = 0;
	ret = RS_buf[RS_out];
	RS_out++;
	if(RS_out >= BUF_MAX) 
		RS_out = 0;
	ES = 1;

	return ret;
}
#endif

//=============================================================================
//		Serial TX														   
//=============================================================================
void RS_tx(BYTE tx_buf)
{
	while(RS_Xbusy);
	SBUF = tx_buf;
	RS_Xbusy=1;
}

//=============================================================================
//		Serial2 TX														   
//=============================================================================
void RS2_tx(BYTE tx_buf)
{
#if 0
	BYTE temp;	

	temp = S2CON;
	S2BUF = tx_buf;
	while(S2CON==temp);
	S2CON = temp;
#endif
	while(RS2_Xbusy);	
		S2BUF=tx_buf;
		RS2_Xbusy=1;
}

#endif	// SERIAL

//****************************************************************************/
//      Timer 2 Interrupt                                                  
//			If TH2 and TL2 are overflowed,
//			 .Invoke this interrupt
//			 .TH2 <- RCAP2H
//			 .TL2 <- RCAP2L
//			TL2 is incremented every machine cycle
//			Every machine cycle is 12*Tosc(11.0592MHz)
//
//			Every machine cycle = 1.085us
//			Interrupt interval  
//				1) REMO_RC5 
//					221.34us  ( 1.085*204 )		// (256-52) (0x10000-0xff34)
//
//					data length: 14bit (2sync bits, 1 control bit, 11 data bits) 24,889ms
//
//								+----+
//					1 is coded:      |    |
//									 +----+   
//								  T    T
//
//									 +----+
//					0 is coded: |    |
//					            +----+	  
//								  T    T					T = 889us
//
//					*) DongYang
//						209.62	( 1.085*193 )	// (256-63) (0x10000-0xff3f)
//-----------------------------------------------------------------------------
//				2) REMO_NEC
//					187.714us ( 1.085*173 )     // (256-83) (0x10000-0xff53)
//							
//****************************************************************************/
//INTERRUPT(5, timer2_int)
void timer2_int(void) interrupt 5 using 1			// using register block 3
{
	TF2 = 0;					// clear overflow

	tm01++;

	#ifdef REMO_RC5
	{
		BYTE	i;

		i = tm01 & 0x07;
		if( i>=1 && i<=2 )
			RemoPhase1 = P3_2;
		else if( i>=5 && i<=6 )
			RemoPhase2 = P3_2;
		else
			;
		if( i==0 ) {	//every 8 tm01
			if( RemoPhase1==RemoPhase2 ) {	// error
				ClearRemoTimer();			
				EnableRemoconInt();
				return;
			}
			if( tm01<=(8*8) ) {				// start control system
				RemoSystemCode <<=1;
				if( RemoPhase1==1 && RemoPhase2==0 )
					RemoSystemCode |=1;
			}
			else {							// data
				RemoDataCode <<=1;
				if( RemoPhase1==1 && RemoPhase2==0 )
					RemoDataCode |=1;
			}
		}
		if( tm01 > (8*14) ) {
			RemoDataReady++;	//LJY051502 RemoDataReady = 1;				// new key
			ClearRemoTimer();				
			//RemoOver = 0;
		}
	}

	#elif defined REMO_NEC
	
	{
		if( RemoDataReady ) return;

		switch( RemoStep ) {

		case 0:
			if( P3_2==0 ) {
				RemoLcnt++;
				if( RemoLcnt==0xff ) goto RemoError;
			}
			else {
				RemoHcnt = 0;
				RemoStep++;
			}
			break;

		case 1:
			if( P3_2==1 ) {
				RemoHcnt++;
				if( RemoHcnt==0xff ) goto RemoError;
			}
			else {
				if( RemoLcnt>=15*3 && RemoLcnt<=17*3 ) {
					
					if( RemoHcnt>=3*3 && RemoHcnt<=5*3 ) {
						RemoStep = 3;
						RemoDataReady = 2;
						break;
					}
					else if( RemoHcnt>=7*3 && RemoHcnt<=9*3 ) {
						RemoStep++;
						RemoPhase = 0;
						RemoLcnt = 0;
						RemoNum  = 0;
						RemoBit  = 0;
						break;
					}
				}
				else goto RemoError;
			}
			break;

		case 2:
			if( RemoPhase==0 ) {
				if( P3_2==0 )					// Phase=0  Input=0
					RemoLcnt++;
				else {							// Phase=0  Input=1
					RemoPhase = 1;
					RemoHcnt = 0;
				}
			}
			else {								
				if( P3_2==1 )					// Phase=1  Input=1
					RemoHcnt++;
				else {							// Phase=1  Input=0
					RemoPhase = 0;
					if( RemoLcnt>=1 && RemoLcnt<=5 ) {
						if( RemoHcnt<=2*3 ) 			// bit 0
							RemoData[RemoNum] <<= 1;
						else if( RemoHcnt<=4*3 ) {		// bit 1
							RemoData[RemoNum] <<= 1;
							RemoData[RemoNum]++;
						}
						else goto RemoError;

						if( ++RemoBit>=8 ) {
							RemoBit = 0;
							if( ++RemoNum>=4 ) {
								RemoDataReady = 1;
								RemoStep++;
							}
						}
						RemoLcnt = 0;

					}
					else goto RemoError;
				}
			}
			break;

		case 3:
			break;
		
		}
		return;

RemoError:
		ClearRemoTimer();				//TimerFor208us();
		EnableRemoconInt();
	}

	#endif	// REMO_NEC
}


void delay(BYTE cnt)
{
	WORD ttic01;

	ttic01 =  ( tic01 + cnt ) % 100;
	do {
		;
	} while( tic01 != ttic01 );
}


//=============================================================================
//		Time
//=============================================================================
#define _24H_SECS			86400L			// 24*60*60
WORD GetTime_ms(void)
{
	WORD tms;

	tms = tic01;
	tms += ( SystemClock % 60 ) * 100;
	return tms;	// in ms
}
//BYTE GetTime_H(void)
//{
//	return ( SystemClock / 60 / 60 ) % 24 ;
//}

//BYTE GetTime_M(void)
//{
//	return ( SystemClock / 60  ) % 60 ;
//}
#if 0
BYTE GetSleepTimer(void)
{
	WORD val;

	val = SleepTimer;
	if( val )	{	// already set, display rest of time
		val = ( SleepTime >> 8 ) * 60 + ( SleepTime & 0xff );
		val -= ( GetTime_H() * 60 + GetTime_M() );
	}
	return (BYTE)val;
}

void SetSleepTimer(BYTE stime)
{
	SleepTimer = stime;
	if( SleepTimer==0 )
		SleepTime = 0xffff;
	else {
		SleepTime = GetTime_H() + ( GetTime_M() + SleepTimer ) / 60;
		SleepTime = ( SleepTime << 8 ) | ( ( GetTime_M() + SleepTimer ) % 60 );
	}

	#ifdef DEBUG_TIME
	dPrintf("\r\n++(SetSleepTimer) SleepTime:0x%x__", (WORD)SleepTime);
	#endif
}

BYTE OKSleepTime(void)
{
	if( GetTime_H() == ( SleepTime >>8 ) && 
		GetTime_M() == ( SleepTime & 0xff ) )	{
		SleepTimer=0;
		SleepTime = 0xffff;
		return 1;
	}
	return 0;
}
#endif
WORD DiffTime_ms( WORD stime, WORD etime )
{
	//#ifdef DEBUG
	//dPrintf("\r\n(DiffTime) stime:%d, etime:%d", (WORD)stime, (WORD)etime );
	//#endif
	if( etime < stime ) {			// resetted
		return etime + (6000 - stime);
	}
	else {
		return etime - stime;
	}
}

void Wait_ms(WORD Tms)
{
	#define CPU_CLK_KHZ 	22118
	#define CPU_SPEED 		1
	#define CountStick	   (1000000U/((CPU_CLK_KHZ*CPU_SPEED)/12))/20	 		//winbond
	#define MegawinCountStick	   ((1000000U/((CPU_CLK_KHZ*CPU_SPEED)/12))/20)*8	//Megawin
    WORD count;
    while(Tms)
     {
     for(count=0; count</*CountStick*/MegawinCountStick; count++);//total 20 clock for this loop
        Tms--;
     }
}

#ifdef AWT_ML072S
#else
BYTE TW2835Command(char _commid, char _attr0, char _attr1, char _attr2, char _attr3)
{        
   BYTE AttrBuf[4];
   BYTE i,j;
   WORD WaitCnt;
   
   //Kane @HS 2007 0807 Ver1.3 for camera always on
   _attr0|=0x10;
   _attr1|=0x10;
#ifdef AWT_TW2835_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon by TW2835 when CAM C trigger
   if ((_commid != 0x05) && (_commid != 0x20) && (_commid != 0x21))
#endif
      _attr2|=0x10;
   _attr3|=0x10;
   //Kane @HS 2007 0807 Ver1.3 for camera always on
 //  Printf("TW2835Command\r\n",0);		//william-v1.44a-970923
    
	switch(_commid)
	{
        //A B C R
		case 0:
        case 11:
            AttrBuf[0]=_attr0;
            AttrBuf[1]=_attr1;
            AttrBuf[2]=_attr2;
            AttrBuf[3]=_attr3;
            break;

        //B A C R     
        case 22:
		case 25:	
		case 1:
            AttrBuf[0]=_attr1;
            AttrBuf[1]=_attr0;
            AttrBuf[2]=_attr2;
            AttrBuf[3]=_attr3;
            break;

        //C A B R     
        case 28:
		case 31:	
		case 2:
            AttrBuf[0]=_attr2;
            AttrBuf[1]=_attr0;
            AttrBuf[2]=_attr1;
            AttrBuf[3]=_attr3;
            break;

        //R A B C     
        case 3:
        case 8:
	    case 14:		
            AttrBuf[0]=_attr3;
            AttrBuf[1]=_attr0;
            AttrBuf[2]=_attr1;
            AttrBuf[3]=_attr2;
            break;

        //A B C R     
        case 20:
		case 4:
            AttrBuf[0]=_attr0;
            AttrBuf[1]=_attr1;
            AttrBuf[2]=_attr2;
            AttrBuf[3]=_attr3;
            break;

        //C R A B      
        case 5:
            AttrBuf[0]=_attr2;
            AttrBuf[1]=_attr3;
            AttrBuf[2]=_attr0;
            AttrBuf[3]=_attr1;
            break;

        //A R B C     
        case 6:
            AttrBuf[0]=_attr0;
            AttrBuf[1]=_attr3;
            AttrBuf[2]=_attr1;
            AttrBuf[3]=_attr2;
            break;

       //R B A C      
        case 7:
            AttrBuf[0]=_attr3;
            AttrBuf[1]=_attr1;
            AttrBuf[2]=_attr0;
            AttrBuf[3]=_attr2;
            break;     

// 2007.4.10 Justin add for A+C &  C+B Mode
        //A C B R 
        case 12:
            AttrBuf[0]=_attr0;
            AttrBuf[1]=_attr2;
            AttrBuf[2]=_attr1;
            AttrBuf[3]=_attr3;
            break;        

        //C B A R
        case 13:
            AttrBuf[0]=_attr2;
            AttrBuf[1]=_attr1;
            AttrBuf[2]=_attr0;
            AttrBuf[3]=_attr3;
            break;        			

	// 2007.4.10 Justin add for A+C &  C+B Mode

	// 2007.4.16  Justin
        //A B R C
		case 9:
	    case 10:
            AttrBuf[0]=_attr0;
            AttrBuf[1]=_attr1;
            AttrBuf[2]=_attr3;
            AttrBuf[3]=_attr2;
            break;

	// 2007.4.16  Justin
        //Andy A1.4 20090113
        //-----------------------------
        //R C A B
		case 15:
		#ifdef HTRV
		case 34:  //  +R/C
		#endif
	        AttrBuf[0]=_attr3;
            AttrBuf[1]=_attr2;
            AttrBuf[2]=_attr1;
            AttrBuf[3]=_attr0;
			break;

        //R A C B
		case 16:
		case 18:           
			AttrBuf[0]=_attr3;
            AttrBuf[1]=_attr0;
            AttrBuf[2]=_attr2;
            AttrBuf[3]=_attr1;
			break;

        //R B C A
		case 17:
		case 19:
			AttrBuf[0]=_attr3;
            AttrBuf[1]=_attr1;
            AttrBuf[2]=_attr2;
            AttrBuf[3]=_attr0;
			break;

        //A C R B
		case 21:
		    AttrBuf[0]=_attr0;
            AttrBuf[1]=_attr2;
            AttrBuf[2]=_attr3;
            AttrBuf[3]=_attr1;
			break;

		//B C R A
		case 23:
	    case 27:
            AttrBuf[0]=_attr1;
            AttrBuf[1]=_attr2;
            AttrBuf[2]=_attr3;
            AttrBuf[3]=_attr0;
			break;

        //B R A C
		case 24:
			AttrBuf[0]=_attr1;
            AttrBuf[1]=_attr3;
            AttrBuf[2]=_attr0;
            AttrBuf[3]=_attr2;
			break;

        //B A R C
		case 26:
			AttrBuf[0]=_attr1;
            AttrBuf[1]=_attr0;
            AttrBuf[2]=_attr3;
            AttrBuf[3]=_attr2;
			break;

        //C B R A
		case 29:
		case 33:
			AttrBuf[0]=_attr2;
            AttrBuf[1]=_attr1;
            AttrBuf[2]=_attr3;
            AttrBuf[3]=_attr0;
			break;

		//C R A B
		case 30:
			AttrBuf[0]=_attr2;
            AttrBuf[1]=_attr3;
            AttrBuf[2]=_attr0;
            AttrBuf[3]=_attr1;
			break;

        //C A R B
		case 32:			
			AttrBuf[0]=_attr2;
            AttrBuf[1]=_attr0;
            AttrBuf[2]=_attr3;
            AttrBuf[3]=_attr1;
			break;
   }

    for(i=0;i<BUF_MAX;i++) {RS_buf2[i]='\0';RS_buf[i]='\0';} // cls RX buffer

#if 1//ryan@20170906


if((InputSelection==CH_AV)&&(TriggerFlag==0))///????AV to CAM ????????2S  //ryan@20170915
{
   Printf(CommTable[_commid], AttrBuf[0], AttrBuf[1], AttrBuf[2], AttrBuf[3]); 
}
else
{
		
    for(j=0;j<3;j++)
    {       

		Printf(CommTable[_commid], AttrBuf[0], AttrBuf[1], AttrBuf[2], AttrBuf[3]); 		
       	WaitCnt=GetTime_ms();
		while(abs(WaitCnt-GetTime_ms())<40);
		{
				
		  for(i=0;i<BUF_MAX;i++) 
	        {  
	         	if(RS_buf2[i]=='A' )
	         	{
	      		
					//if( RS_buf2[(i+1)%8]=='C' &&  RS_buf2[(i+2)%8]=='K'  ) ///mask by ryan@20170906
					if( RS_buf2[(i+1)%(BUF_MAX)]=='C' &&  RS_buf2[(i+2)%(BUF_MAX)]=='K'  ) /// ryan@20170906
					return TRUE;
				
	         	}
			
            }
		
	}	
	Wait_ms(200);			  	
		
	}
}

#else



    for(j=0;j<3;j++)
    {       
        Printf(CommTable[_commid], AttrBuf[0], AttrBuf[1], AttrBuf[2], AttrBuf[3]); 
       	WaitCnt=GetTime_ms();
  		while(abs(WaitCnt-GetTime_ms())<40);
  		{
			for(i=0;i<BUF_MAX;i++) 
	        {  
	         	if(RS_buf2[i]=='A' )
	         	{
					if( RS_buf2[(i+1)%8]=='C' &&  RS_buf2[(i+2)%8]=='K'  ) 
						return TRUE;
	         	}		
            }
		}
	    Wait_ms(200);			  	
	}
	
#endif

	return FALSE;
   
}
#endif


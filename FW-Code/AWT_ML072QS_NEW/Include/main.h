#ifndef __MAIN__
#define __MAIN__

#define ON					1
#define OFF					0
#if 1//ryan@20171214
#define Hs_debug
#define Monitor_debug  
//#define Trigger_debug 
#endif


//#define	DVR
#define Format_SDCard
#define BJTSwitch

#define Panel_Enable() 		P4=P4|0x08 //andy 980908
#define Panel_Disable()		P4=P4&0xf7

#if 0
#define SetBacklight()      P4=P4|0x04
#define clrBacklight()      P4=P4&0xfb
#else
#define SetBacklight() 		P4=P4&0xfb
#define clrBacklight() 		P4=P4|0x04
#endif

//InputSelection
struct struct_IdName {
	BYTE	Id;
	BYTE	Name[16];
};

#define CH_TW2835 			1
#define CH_CAMD 			2
#define CH_AV 				3
#define PC 					7
#define ChineseDefaultMenu	8

#define SVIDEO				2
#define COMPONENT			3
//#define ANALOGDTV			4
#define DTV					4
#define TV					5
#define SCART				6

#ifdef HS
#define CH_CAMB 				4
#endif

#define DIGITALVGA			8

#define AIRTV				0 //9
#define CABLETV				1 //0xa

#define TVTUNER				0xd		//10
#define MUTE 				1	
#define MENU				2	
#define TVVOL				4	
#ifdef AWT_ML072S
#define VLOSSINFO			8	
#else
#define CC					8	
#endif
#define INPUTINFO			0x10
#define PCINFO				0x20
#define GAUGEINFO 			0x40
//#define RATINGINFO			0x40
#define TVCHN				0x80
//#define MUTE				0x40

#define YPBPR_480i			0
#define YPBPR_576i			1
#define YPBPR_480p			2
#define YPBPR_576p			3
#define YPBPR_1080i			4
#define YPBPR_720p			5
#define YPBPR_720p50		6

//---------------------- Feature Define ----------------------------
#ifdef AWT_ML072Q

//mask by ryan@20171018		#define AWT_ML720Q_NEW_TRIGGER_FUN  	//Pinchi 20141031 add for AWT request each trigger can work by PRIORITY OFF
#define AWT_ADD_TRIGGER_DELAY_FUN 
#define AWT_SUPPORT_4_3_SCREEN  	//ryan@20170907 
#endif

#ifdef AWT_ML072S
#define AWT_ADD_TRIGGER_DELAY_FUN 
#endif

//--------------------------- P0 Define -----------------------------
//#define SEL_MIX			P0_6	// 
//--------------------------- P1 Define -----------------------------
//#define SEL_DVI			P3_5	//LJY062001		

#define TW88HWReset 		P3_4	//LJY001010 //LJY000721
#define PowerUp  			P3_7
//======================= CDS Control ================================= 
//#define CDS_CTRL           P1_5
extern BYTE	SelectModeType;
extern BYTE InputSelection;
extern BYTE SEQTime;
extern BYTE	Priority;
extern BYTE PowerFlag;
//extern bit AutoDayNight;
extern bit SDCardCoverDetect;

BYTE keyIn(void);
void TimerForRemocon(void);
void TimerForTick(void);
void DisableRemoconInt(void);
BYTE SetSupport_remocon(BYTE newd);

void delay(BYTE cnt);

BYTE RS_ready(void);
#ifdef Monitor_debug
BYTE RS_rx(void);
#endif
void RS_tx(BYTE tx_buf);

BYTE RS2_rx(void);
void RS2_tx(BYTE tx_buf);

void NewLine(void);
void PutsP(PDATA_P BYTE *ptr);
#ifdef Hs_debug
//void MonWriteI2C(BYTE addr, BYTE index, BYTE val);
//BYTE MonReadI2C(BYTE addr, BYTE index);
#endif
BYTE Asc1Bin(BYTE asc);
BYTE Asc2Bin(PDATA_P BYTE *s);

void I2CDeviceInitialize( CODE_P BYTE *RegSet);

//void RestartSystemClock(WORD clock_hm);
WORD GetTime_ms(void);
#if 0
BYTE GetTime_H(void);
BYTE GetTime_M(void);
#endif
void ChangeTime_H( char add );
void ChangeTime_M( char add );
//WORD GetWakeupTime(void);
//void SetWakeupTime(WORD wtime);


//WORD GetOffTime(void);
//void SetOffTime(WORD wtime);
//BYTE GetSleepTimer(void);
//void SetSleepTimer(BYTE stime);
WORD DiffTime_ms( WORD stime, WORD etime );
//void SetLastBlockedTime(void);
void SetLastCCTime(void);				//ljy010904...CC_FIX_CLEAR_ON_TIME

void SetOSDLastKeyInTime(void);
WORD GetOSDLastKeyInTime(void);
WORD GetIVF(void);
DWORD GetIHF(void);
BYTE ReadVInputSTD(void);
void SetVInputStd(BYTE newd);
BYTE GetVInputStd(void);
BYTE GetInputSelection(void);
#ifdef ADD_ANALOGPANEL
BYTE IsAnalogOn(void);
#endif
void InitVideoData(BYTE src);
void ChangeVInputStdDetectMode(BYTE val);
BYTE GetVInputStdInx(void);

void MonWriteI2Cn_(BYTE addr, BYTE *val, BYTE cnt) ;

void CheckNewTriggerFunc(void);
///void Usage(void);
#ifdef Monitor_debug
	void Prompt(void);
#endif
void DebugKeyIn(BYTE ikey);
void DVIPowerDown(bit flag);
void PowerDown_XTAL(bit flag);

void ChangeInput(BYTE newsel);


void WaitPowerOn(void);
void PowerOff(void);
BYTE GetNextInputSelection(void);

BYTE WantToStopTVScan(void);

//BYTE IsTW8801(void);
//BYTE IsTW8803(void);
//BYTE ConvertVideoVSAT(BYTE reg);

BYTE IsNoInput(void);
void LoadEEPROM (void);
void Hs_InitVars(void);
void AdjustAutoDayNight(BYTE val);
void ACCPowerControl(void);
void ON_LVDS(void);
void OFF_LVDS(void);
void main_loop(void);
struct RegisterInfo
{
   int	Min;
   int	Max;
   int	Default;
};
struct LongRegisterInfo
{
   WORD	Min;
   WORD	Max;
   WORD	Default;
};


typedef enum   ///add enum  by ryan@20170907
{
	NORMALL_MODE,
	REVERSE_TRIG,
	LEFT_TRIG,
	RIGHT_TRIG,
#ifdef USE_CAMD	
	CAMD_TRIG,
#endif	
	CAMC_TRIG,
	VGA_TRIG,
	PARK_TRIG,
	No_TRIG,
	TRIGGER_NUM
}TriggerModeType;


#endif	// __MAIN__


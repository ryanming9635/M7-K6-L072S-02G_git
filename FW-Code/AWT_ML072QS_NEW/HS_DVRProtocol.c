//=====================================================================
//	Work file: Hs_Protocol.c
//
//	This file is generating the HS protocol for DVR .
//
//																
//=====================================================================
//******************************************************************************
//  I N C L U D E    F I L E S
//******************************************************************************
#include "Config.h"
#include "typedefs.h"
#include "i2c.h"
#include "main.h"
#include "tw88.h"
#include "osdbasic.h"
#include "dispinfo.h"
#include "measure.h"
#include "debug.h"
#include "printf.h"
#include "udfont.h"
#include "regmap.h"
#include "externs.h"
#include "CPU.h"

#include "panel.h"
#include "osdmenu.h"
#include "HS_DVRProtocol.h"
#include "HS_IOdef.h"
#include "HS_DisplayOSD.h"


//********************************************************************
//	LOCAL DEFINE
//********************************************************************

//#define DEBUG_HS_PROTOCOL
#define	ProtocolDebug
#define LCDMode 4

//********************************************************************
//	GLOBAL VARIABLES
//********************************************************************
//#ifdef SUPPORT_SDCARD
BYTE	year1,year2,month,day,hour,minute,second;
BYTE	DVR_daylightsaving;
BYTE	DVR_timebeginesmonth;
BYTE	DVR_timebeginesweek;
BYTE	DVR_timebeginesTime;
BYTE	DVR_sandardtimebeginesMonth;
BYTE	DVR_standardtimebeginesWeek;
BYTE	DVR_standardtimebeginesTime;
BYTE	DVR_Resolution			;
BYTE	DVR_FPS					;
BYTE	DVR_Quality				;
BYTE	DVR_RecordMode			;
BYTE	DVR_RecordLength		;
BYTE	DVR_PreAlarmLength		;
BYTE	DVR_PostAlarmLength		;
BYTE	DVR_TimeZone;
BYTE	DVR_SDCardAvailable=255		;
BYTE	DVR_RecordStatus		;
BYTE	DVR_Busy				;
BYTE	DVR_OverWrite;
BYTE	FormatStatus			;
bit	FormatStart				;
BYTE	TriggerStatus			;
BYTE	DVR_System=0;

bit		DVR_Ready				;
bit 	GetDVRStatusflag		;
bit    DoorState;
BYTE GPSState;
//bit 	GetDVRVersionOK=0		;
BYTE DVRVersion[17]=0;
BYTE DVRVersionLen=17;
//#endif		//#ifdef SUPPORT_SDCARD

extern  bit PowerDownStart		;
extern  BYTE PowerDownWait		;
extern  bit AccPowerDown		;
extern  bit PowerDownStart		;
extern  BYTE PowerDownWait		;
extern  bit AccPowerDown		;
extern DATA BYTE RS2_in;
extern DATA  BYTE DVR_buf[DVR_BUF_MAX];
//extern DATA BYTE RS_in;
//extern DATA BYTE RS_buf2[BUF_MAX];

BYTE gb_P_Com[2];	//Pelco P Command Buffer
//BYTE gb_P_Com[7];	//Pelco D Command Buffer
//BYTE GE_Com[9];	//GE Command Buffer
BYTE gb_PTZ_Speed;
bit SpeedDomeMode=0;
BYTE PresetMode=0;
BYTE PresetNumber=1;
extern BYTE  CAMNumber;
extern BYTE  PelcoChoiceFLAG;
extern BYTE  Baud_rate;
BYTE 	UpdateOK=0;
BYTE Information[14];
//BYTE WIFI_IP[4];
//BYTE WIFI_MAC[6]; 
//BYTE GET_WAY[4]; 
BYTE InformationLen=14;
WORD CommandBuffer;
//********************************************************************
//	LOCAL VARIABLES
//********************************************************************
BYTE	SerialNumber; 


//********************************************************************
//	LOCAL FUNCTIONS
//********************************************************************

void Hs_Send_DVR_Command(BYTE * DVR_Com, BYTE len );
BYTE DvrReceivePaser();


#ifdef SUPPORT_SDCARD  //Pinchi 20140902 enable for AWT ML072Q
void Hs_Protocol_Init(void)
{
	SerialNumber=0;
	year1=0;
	year2=0;
	month=0;
	day=0;
	hour=0;
	minute=0;
	second=0;

	DVR_Resolution=0x01;
	DVR_FPS=0x01;
	DVR_Quality=0x01;
	DVR_RecordMode=0x01;
	DVR_RecordLength=0x01;
	DVR_PreAlarmLength=0x01;
	DVR_PostAlarmLength=0x01;
	DVR_TimeZone=0x01;
	DVR_daylightsaving=0x01;
	DVR_timebeginesmonth=0x01;
	DVR_timebeginesweek=0x01;
	DVR_timebeginesTime=0x01;
	DVR_sandardtimebeginesMonth=0x01;
	DVR_standardtimebeginesWeek=0x01;
	DVR_standardtimebeginesTime=0x01;
	DVR_SDCardAvailable=0;
	DVR_RecordStatus=0x01;
	DVR_Busy=0;
	DVR_Ready=0;
	FormatStatus=0;
	FormatStart=0;
	DVR_OverWrite=1;
	GPSState=0;
}

void Hs_DvrTxCmdPaser(BYTE Cmd_Id )
{
	//bit check;
	BYTE j;
	//BYTE	Check_GM8126;
	BYTE DVR_Com[25];	//DVR Protocol Command Buffer
	for(j=0;j<30;j++)
		DVR_Com[j] = 0 ;

	DVR_Com[0] ='H';	//
	DVR_Com[1] ='S';	//	
	DVR_Com[2] = 0x01;		
	DVR_Com[3] = SerialNumber;

	switch(Cmd_Id)
	{
	case SetDVRParam:
		DVR_Com[4] = SetDVRParam;			//Command Data
		DVR_Com[5] = 8;					//Data len		
		DVR_Com[6] = DVR_Resolution;		//Data 1
		DVR_Com[7] = DVR_FPS;				//Data 2
		DVR_Com[8] = DVR_Quality;			//Data 3
		DVR_Com[9] = DVR_RecordMode;		//Data 4
		DVR_Com[10] = DVR_RecordLength;		//Data 5
		DVR_Com[11] = DVR_PreAlarmLength;	//Data 6
		DVR_Com[12] = DVR_PostAlarmLength;	//Data 7
		DVR_Com[13] = DVR_OverWrite;	//Data 7

		CommandBuffer|=bSetDVRParam;
		#ifdef ProtocolDebug
		Printf("\r\n SetDVRParam",0);
		#endif
		break;

	case SetDVRDefault:
		DVR_Com[4] = SetDVRDefault;			//Command Data
		DVR_Com[5] = 0;					//Data len		
		CommandBuffer|=bSetDVRDefault;
		#ifdef ProtocolDebug
		Printf("\r\n SetDVRDefault",0);
		#endif
		break;	
		
	case SetDATETIME:
		DVR_Com[4] = SetDATETIME;			//Command Data
		DVR_Com[5] = 15;					//Data len		
		DVR_Com[6] = year1;		//Data 1
		DVR_Com[7] = year2;				//Data 2
		DVR_Com[8] = month;			//Data 3
		DVR_Com[9] = day;		//Data 4
		DVR_Com[10] = hour;		//Data 5
		DVR_Com[11] = minute;	//Data 6
		DVR_Com[12] = second;	//Data 7
		DVR_Com[13] = DVR_TimeZone;		//Data 8
		DVR_Com[14] = DVR_daylightsaving;				//Data 9
		DVR_Com[15] = DVR_timebeginesmonth;			//Data 10
		DVR_Com[16] = DVR_timebeginesweek;		//Data 11
		DVR_Com[17] = DVR_timebeginesTime;		//Data 12
		DVR_Com[18] = DVR_sandardtimebeginesMonth;	//Data 13
		DVR_Com[19] = DVR_standardtimebeginesWeek;	//Data 14
		DVR_Com[20] = DVR_standardtimebeginesTime;		//Data 15
		CommandBuffer|=bSetDATETIME;
		#ifdef ProtocolDebug
		Printf("\r\n SetDATETIME",0);
		#endif
		break;		
	
	case GetDVRParam:
		DVR_Com[4] = GetDVRParam;			//Command Data
		DVR_Com[5] = 0;					//Data len		
		CommandBuffer|=bGetDVRParam;
		#ifdef ProtocolDebug
		Printf("\r\n GetDVRParam",0);
		#endif
		break;	

	case GetDVRStatus:
		DVR_Com[4] = GetDVRStatus;		//Command Data
		DVR_Com[5] = 1;					//Data len	
		DVR_Com[6] = 0;					//Param1
		CommandBuffer|=bGetDVRStatus;
		#ifdef ProtocolDebug
		Printf("\r\n GetDVRStatus",0);
		#endif
		break;	

	case GetDATETIME:
		DVR_Com[4] = GetDATETIME;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		CommandBuffer|=bGetDATETIME;
		#ifdef ProtocolDebug
		Printf("\r\n GetDATETIME",0);
		#endif
		break;	

	case MANUALRECSTART:
		DVR_Com[4] = MANUALRECSTART;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		#ifdef ProtocolDebug
		Printf("\r\n MANUALRECSTART",0);
		#endif
		break;	

	case MANUALRECSTOP:
		DVR_Com[4] = MANUALRECSTOP;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		#ifdef ProtocolDebug
		Printf("\r\n MANUALRECSTOP",0);
		#endif
		break;	

	case SNAPSHOT:
		DVR_Com[4] = SNAPSHOT;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		#ifdef ProtocolDebug
		Printf("\r\n SNAPSHOT",0);
		#endif
		break;

	case BOOKMARK:
		DVR_Com[4] = BOOKMARK;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		CommandBuffer|=bBOOKMARK;
		#ifdef ProtocolDebug
		Printf("\r\n BOOKMARK",0);
		#endif
		break;

	case SetSystem:
		DVR_Com[4] = SetSystem;		//Command Data
		DVR_Com[5] = 1;					//Data len	
		DVR_Com[6] = DVR_System;		
		CommandBuffer|=bSetSystem;
		#ifdef ProtocolDebug
		Printf("\r\n SetSystem",0);
		#endif
		break;
		
	case Halt_Start:
		DVR_Com[4] = Halt_Start;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		CommandBuffer|=bHalt_Start;
		#ifdef ProtocolDebug
		Printf("\r\n Halt_Start",0);
		#endif
		break;	

	case SetFormatSD :
		DVR_Com[4] = SetFormatSD ;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		//FormatStart=1;
		CommandBuffer|=bSetFormatSD;
		#ifdef ProtocolDebug
		Printf("\r\n SetFormatSD",0);
		#endif
		break;

	case SendAlarm :
		DVR_Com[4] = SendAlarm;		//Command Data
		DVR_Com[5] = 1;					//Data len	
		DVR_Com[6] = 0;					//Param1
		#ifdef ProtocolDebug
		Printf("\r\n SendAlarm",0);
		#endif
		break;	
		
	case GetDVRVersion :
		DVR_Com[4] = GetDVRVersion;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		CommandBuffer|=bGetDVRVersion;
		#ifdef ProtocolDebug
		Printf("\r\n GetDVRVersionLCD",0);
		#endif

		break;	
		
	case FW_Update_Start:
		DVR_Com[4] = FW_Update_Start ;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		CommandBuffer|=bFW_Update_Start;
		//FormatStart=1;
		#ifdef ProtocolDebug
		Printf("\r\n FW_Update_Start",0);
		#endif
		break;

	case Update_CONFIG:
		DVR_Com[4] = Update_CONFIG ;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		CommandBuffer|=bUpdate_CONFIG;
		//FormatStart=1;
		#ifdef ProtocolDebug
		Printf("\r\n Update_CONFIG",0);
		#endif
		break;	

	case DoorClose:
		DVR_Com[4] = DoorClose;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		CommandBuffer&=(!bDoorOpen);
		CommandBuffer|=bDoorClose;
		
		DoorState=0;
		#ifdef ProtocolDebug
		Printf("\r\n DoorClose",0);
		#endif
		break;		

	case DoorOpen:
		DVR_Com[4] = DoorOpen;		//Command Data
		DVR_Com[5] = 0;					//Data len	
		CommandBuffer&=(!bDoorClose);
		CommandBuffer|=bDoorOpen;
		DoorState=1;
		#ifdef ProtocolDebug
		Printf("\r\n DoorOpen",0);
		#endif
		break;	
		

	}
#if 1
//for(j=0;j<2;j++)
//{
	RS2_in=0;
	Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
	//Wait_ms(200);

//	Check_GM8126=DvrReceivePaser();
//	if(Check_GM8126==TRUE)
//		break;
//}
#endif
#if 0
	if(Check_GM8126==FALSE)
		DisplayInformation(InfoSDCARDNotReady);
	else
		{
		ClearOSDInfo();
   		ClearDataCnt(0,30*5);    
		}
#endif
}

void Hs_Send_DVR_Command(BYTE * DVR_Com, BYTE len )
{
	BYTE ii,j;

	//Generate DVR Mode  Check Sum
	DVR_Com[len+6] = DVR_Com[0];
	
	for(j=1;j<(len+6);j++)
		DVR_Com[len+6] = DVR_Com[len+6]^DVR_Com[j];
	//CheckSum = Byte1 XOR Byte2 XOR Byte3 XOR......
	
	//Change_RS485_TxRx(1,RS485_TX);
	//Start Send DVR Command
	for(ii=0;ii<(len+7);ii++)
	{
		RS2_tx(DVR_Com[ii]);	
	}

#ifdef DEBUG_HS_PROTOCOL
	for(ii=0;ii<len+7;ii++)
	{
		Printf("\r\nSend DVR Command[%d] = 0x%02x",(WORD)ii,(WORD)DVR_Com[ii]); 
	}
#endif

}

BYTE DvrReceivePaser(void)
{
	BYTE i,j,CheckSum;
	BYTE DVR_Com[30];	//DVR Protocol Command Buffer
	//BYTE Information[14];

	//Wait_ms(200);		//william-v1410-20120524
#if 0
	for(i=0;i<RS2_in;i++) 
	{  
		Printf("\r\nDVR_buf[%d]=0x%02x",(WORD)i,(WORD)DVR_buf[i]);
	}
#endif
	//DisplayNumber(DVRStatus_ADDR,year1,4);
	for(i=0;i<DVR_BUF_MAX;i++) 
	{  
		if(DVR_buf[i]=='H' /*&& DVR_buf[(i+1)]=='S'*/)
		{
		 if( DVR_buf[i+1]=='S'  ) 
		  break;
		}
	}

#if 0	
if(DVR_buf[(i+2)]==0x02)
	{
		if(!(DVR_buf[(i+3)]==SerialNumber))
			return FALSE;
	}
#endif
	
	//Generate DVR Mode  Check Sum

	CheckSum=DVR_buf[i];

	for(j=1;j<(DVR_buf[i+5]+6);j++)
		CheckSum = CheckSum^DVR_buf[i+j];

	if(!(CheckSum==(DVR_buf[i+DVR_buf[i+5]+6])))
		return FALSE;	

	switch(DVR_buf[i+4])
	{
	case SetDVRParam:
		CommandBuffer&=(!bSetDVRParam);
		#ifdef ProtocolDebug
		Printf("\r\nR SetDVRParam",0);
		#endif
		break;

	case SetDVRDefault:
		CommandBuffer&=(!bSetDVRDefault);
		#ifdef ProtocolDebug
		Printf("\r\nR SetDVRDefault",0);
		#endif
		break;	
		
	case SetDATETIME:
		CommandBuffer&=(!bSetDATETIME);
		#ifdef ProtocolDebug
		Printf("\r\nR SetDATETIME",0);	
		#endif
		break;		

	case Halt_Start:
		CommandBuffer&=(!bHalt_Start);
		#ifdef ProtocolDebug
		Printf("\r\nR Halt_Start",0);	
		#endif
		break;		

	case FW_Update_Start:
		CommandBuffer&=(!bFW_Update_Start);
		#ifdef ProtocolDebug
		Printf("\r\nR FW_Update_Start",0);	
		#endif
		break;		

	case SetFormatSD:
		CommandBuffer&=(!bSetFormatSD);
		#ifdef ProtocolDebug
		Printf("\r\nR SetDATETIME",0);	
		#endif
		break;	

	case SetSystem:
		CommandBuffer&=(!bSetSystem);
		#ifdef ProtocolDebug
		Printf("\r\nR SetSystem",0);	
		#endif
		break;	
	
	case GetDVRParam:
		DVR_Resolution=DVR_buf[i+6];								//Data 1
		DVR_FPS=DVR_buf[i+7];										//Data 2
		DVR_Quality=DVR_buf[i+8];									//Data 3
		DVR_RecordMode=DVR_buf[i+9];								//Data 4
		DVR_RecordLength=DVR_buf[i+10];								//Data 5
		DVR_PreAlarmLength=DVR_buf[i+11];							//Data 6
		DVR_PostAlarmLength=DVR_buf[i+12];							//Data 7
		DVR_OverWrite=DVR_buf[i+13];							//Data 7
		
		CommandBuffer&=(!bGetDVRParam);
		#ifdef ProtocolDebug
		Printf("\r\nR GetDVRParam",0);	
		#endif
		break;	

	case GetDVRStatus:
		year1=DVR_buf[i+6];								//Data 1
		year2=DVR_buf[i+7];								//Data 2
		month=DVR_buf[i+8];								//Data 3
		day=DVR_buf[i+9];								//Data 4
		hour=DVR_buf[i+10];								//Data 5
		minute=DVR_buf[i+11];							//Data 6
		second=DVR_buf[i+12];							//Data 7
		DVR_RecordStatus=DVR_buf[i+13];					//Data 8
		DVR_SDCardAvailable=DVR_buf[i+14];				//Data 9
		DVR_Busy=DVR_buf[i+15];							//Data 10
		CommandBuffer&=(!bGetDVRStatus);
		#ifdef ProtocolDebug
		Printf("\r\nR GetDVRStatus",0);	
		#endif
		break;	

	case GetDATETIME:
		year1=DVR_buf[i+6];								//Data 1
		year2=DVR_buf[i+7];								//Data 2
		month=DVR_buf[i+8];								//Data 3
		day=DVR_buf[i+9];								//Data 4
		hour=DVR_buf[i+10];								//Data 5
		minute=DVR_buf[i+11];							//Data 6
		second=DVR_buf[i+12];							//Data 7
		DVR_TimeZone=DVR_buf[i+13];						//Data 8
		DVR_daylightsaving=DVR_buf[i+14];				//Data 9
		DVR_timebeginesmonth=DVR_buf[i+15];				//Data 10
		DVR_timebeginesweek=DVR_buf[i+16];				//Data 11
		DVR_timebeginesTime=DVR_buf[i+17];				//Data 12
		DVR_sandardtimebeginesMonth=DVR_buf[i+18];		//Data 13
		DVR_standardtimebeginesWeek=DVR_buf[i+19];		//Data 14
		DVR_standardtimebeginesTime=DVR_buf[i+20];		//Data 15					//Data len	
		CommandBuffer&=(!bGetDATETIME);
		#ifdef ProtocolDebug
		Printf("\r\nR GetDATETIME",0);	
		#endif
		break;	
		
	case SendDVRStatus:
		year1=DVR_buf[i+6];								//Data 1
		year2=DVR_buf[i+7];								//Data 2
		month=DVR_buf[i+8];								//Data 3
		day=DVR_buf[i+9];								//Data 4
		hour=DVR_buf[i+10];								//Data 5
		minute=DVR_buf[i+11];							//Data 6
		second=DVR_buf[i+12];							//Data 7
		DVR_RecordStatus=DVR_buf[i+13];						//Data 8
		DVR_SDCardAvailable=DVR_buf[i+14];				//Data 9
		DVR_Busy=DVR_buf[i+15]; 						//Data 10

		for(j=0;j<30;j++)
			DVR_Com[j] = 0 ;
	
		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = SendDVRStatus;		//Command Data
		DVR_Com[5] = 0;					//Data len		
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
		#ifdef ProtocolDebug
		Printf("\r\nR SendDVRStatus",0);
		Printf("\r\nR DVR_RecordStatus=%02x",(WORD)DVR_RecordStatus);	
		#endif
		break;	

	case SendDVRParam:
		DVR_Resolution=DVR_buf[i+6];								//Data 1
		DVR_FPS=DVR_buf[i+7];										//Data 2
		DVR_Quality=DVR_buf[i+8];									//Data 3
		DVR_RecordMode=DVR_buf[i+9];								//Data 4
		DVR_RecordLength=DVR_buf[i+10];								//Data 5
		DVR_PreAlarmLength=DVR_buf[i+11];							//Data 6
		DVR_PostAlarmLength=DVR_buf[i+12];							//Data 7
		DVR_OverWrite=DVR_buf[i+13];							//Data 7

		for(j=0;j<30;j++)
			DVR_Com[j] = 0 ;
	
		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = SendDVRParam;		//Command Data
		DVR_Com[5] = 0;					//Data len		
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
		#ifdef ProtocolDebug
		Printf("\r\nR SendDVRParam",0);	
		#endif
		break;	

	case SendDVRParamDT:

		year1=DVR_buf[i+6];								//Data 1
		year2=DVR_buf[i+7];								//Data 2
		month=DVR_buf[i+8];								//Data 3
		day=DVR_buf[i+9];								//Data 4
		hour=DVR_buf[i+10];								//Data 5
		minute=DVR_buf[i+11];							//Data 6
		second=DVR_buf[i+12];							//Data 7
		DVR_TimeZone=DVR_buf[i+13];						//Data 8
		DVR_daylightsaving=DVR_buf[i+14];				//Data 9
		DVR_timebeginesmonth=DVR_buf[i+15];				//Data 10
		DVR_timebeginesweek=DVR_buf[i+16];				//Data 11
		DVR_timebeginesTime=DVR_buf[i+17];				//Data 12
		DVR_sandardtimebeginesMonth=DVR_buf[i+18];		//Data 13
		DVR_standardtimebeginesWeek=DVR_buf[i+19];		//Data 14
		DVR_standardtimebeginesTime=DVR_buf[i+20];		//Data 15					//Data len		

		for(j=0;j<30;j++)
			DVR_Com[j] = 0 ;
	
		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = SendDVRParamDT;		//Command Data
		DVR_Com[5] = 0;					//Data len		
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
		#ifdef ProtocolDebug
		Printf("\r\nR SendDVRParamDT",0);		
		#endif
		break;	
		
	case GetLCDMode:	
		for(j=0;j<30;j++)
			DVR_Com[j] = 0 ;
	
		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = GetLCDMode;		//Command Data
		DVR_Com[5] = 0x01;					//Data len		
		DVR_Com[6] = LCDMode;					//Data 1
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
		#ifdef ProtocolDebug
		Printf("\r\nR GetLCDMode",0);
		#endif
		break;	

	case MANUALRECSTART:			
		break;	

	case MANUALRECSTOP:			
		break;	

	case SNAPSHOT:				
		break;

	case Halt_OK:
		for(j=0;j<30;j++)
		DVR_Com[j] = 0 ;
		
		if(ACC_B==1)
		{	
		#ifdef BJTSwitch	
			PPWR=0;
		#else
			PPWR=1;
		#endif
		}
		else
		{
			DVR_Com[0] ='H';	//
			DVR_Com[1] ='S';	//	
			DVR_Com[2] = 0x02;		
			DVR_Com[3] = DVR_buf[i+3];
			DVR_Com[4] = Halt_OK;		//Command Data
			DVR_Com[5] = 1; 				//Data len		
			DVR_Com[6] = 0;					//Data 1
			Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
			PowerDownStart=0;
			PowerDownWait=0;
			AccPowerDown=1;
		}
		#ifdef ProtocolDebug
		Printf("\r\nR Halt_OK",0);
		#endif
		
		break;	
		
	case SetFormatSDDone:

		for(j=0;j<30;j++)
		DVR_Com[j] = 0 ;
		
		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = SetFormatSDDone;		//Command Data
		DVR_Com[5] = 0;					//Data len		
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
		FormatStatus=1;
		UpdateOK=1;
		CommandBuffer&=(!bSetFormatSD);
		#ifdef ProtocolDebug
		Printf("\r\nR SetFormatSDDone",0);
		#endif
		break;

	case FW_Update_OK:

		//FormatStatus=DVR_buf[i+6]; 							//Data 1

		UpdateOK=DVR_buf[i+6];

		for(j=0;j<30;j++)
		DVR_Com[j] = 0 ;
		
		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = FW_Update_OK;		//Command Data
		DVR_Com[5] = 0;					//Data len		
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
		FormatStatus=1;
		CommandBuffer&=(!bFW_Update_Start);
		#ifdef ProtocolDebug
		Printf("\r\nR FW_Update_OK",0);	
		#endif
		break;

	case GetDVRVersion:
		
		DVRVersionLen = DVR_buf[i+5];
		for(j=0;j<=DVRVersionLen;j++)
		{
			DVRVersion[j]=DVR_buf[i+6+j];								//Data 1	
		}	
		//GetDVRVersionOK=1;
		DisplayFWVersion();
		CommandBuffer&=(!bGetDVRVersion);
		#ifdef ProtocolDebug
		Printf("\r\nR GetDVRVersionDVR",0);	
		#endif
		break;		

	case GetInformation:
			
		InformationLen= DVR_buf[i+5];
		for(j=0;j<InformationLen;j++)
		{
			Information[j]=DVR_buf[i+6+j];								//Data 1	
		}	

		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = GetInformation;		//Command Data
		DVR_Com[5] = 0;					//Data len		
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);

		//for(i=0;i<InformationLen;i++) 
		//{  
		//Printf("\r\nInformation[%d]=0x%02x",(WORD)i,(WORD)Information[i]);
		//}
		#ifdef ProtocolDebug
		Printf("\r\nR GetInformation",0);
		#endif
		break;
   
	case Update_CONFIG_OK:

		for(j=0;j<30;j++)
		DVR_Com[j] = 0 ;
		
		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = Update_CONFIG_OK;		//Command Data
		DVR_Com[5] = 0;					//Data len		
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);
		FormatStatus= 1;
		UpdateOK=DVR_buf[i+6];

		CommandBuffer&=(!bUpdate_CONFIG);
		#ifdef ProtocolDebug
		Printf("\r\nR Update_CONFIG_OK",0);
		#endif
		break;

#if 0
	case GPSReset:

		GPSState=DVR_buf[i+6];								//Data 1

		for(j=0;j<30;j++)
		DVR_Com[j] = 0 ;
		
		DVR_Com[0] ='H';	//
		DVR_Com[1] ='S';	//	
		DVR_Com[2] = 0x02;		
		DVR_Com[3] = DVR_buf[i+3];
		DVR_Com[4] = GPSReset;		//Command Data
		DVR_Com[5] = 0;					//Data len		
		Hs_Send_DVR_Command((BYTE *)DVR_Com,DVR_Com[5]);

	if(GPSState==1)
		{
		GPS_PWR=0;
		Wait_ms(1000);
		GPS_PWR=1;
		}
		#ifdef ProtocolDebug
		Printf("\r\nR GPSReset",0);
		#endif
		break;
#endif

	case BOOKMARK:
		CommandBuffer&=(!bBOOKMARK);
		#ifdef ProtocolDebug
		Printf("\r\n RBOOKMARK",0);
		#endif
		break;

	case DoorClose:							
		DoorState=0;
		CommandBuffer&=(!bDoorClose);
		#ifdef ProtocolDebug
		Printf("\r\nR DoorClose",0);
		#endif
		break;		

	case DoorOpen:			
		DoorState=1;
		CommandBuffer&=(!bDoorOpen);
		#ifdef ProtocolDebug
		Printf("\r\nR DoorOpen",0);
		#endif
		break;	
		
	}

	for(j=0;j<29;j++)
			DVR_buf[j] = 0 ;
	
	SerialNumber++;
	RS2_in=0;
	
#if 1
	if(DVR_Ready==0)
	{
		DVR_Ready=1;
		GetDVRStatusflag=1;
	}
#endif

	return TRUE;
}

void DVRCommandReSend(void)
{
	if(CommandBuffer&bSetDVRParam)
		Hs_DvrTxCmdPaser(SetDVRParam);

	if(CommandBuffer&bSetDVRDefault)
		Hs_DvrTxCmdPaser(SetDVRDefault);

	if(CommandBuffer&bGetDVRParam)
		Hs_DvrTxCmdPaser(GetDVRParam);

	if(CommandBuffer&bGetDATETIME)
		Hs_DvrTxCmdPaser(GetDATETIME);

	if(CommandBuffer&bGetDATETIME)
		Hs_DvrTxCmdPaser(GetDATETIME);

	if(CommandBuffer&bHalt_Start)
		Hs_DvrTxCmdPaser(Halt_Start);

	if(CommandBuffer&bSetFormatSD)
		Hs_DvrTxCmdPaser(SetFormatSD);

	if(CommandBuffer&bGetDVRVersion)
		Hs_DvrTxCmdPaser(GetDVRVersion);

	if(CommandBuffer&bFW_Update_Start)
		Hs_DvrTxCmdPaser(FW_Update_Start);

	if(CommandBuffer&bDoorClose)
		Hs_DvrTxCmdPaser(DoorClose);

	if(CommandBuffer&bDoorOpen)
		Hs_DvrTxCmdPaser(DoorOpen);

	if(CommandBuffer&bUpdate_CONFIG)
		Hs_DvrTxCmdPaser(Update_CONFIG);
}
#endif

#if 0
BYTE TW2835ReceivePaser(void)
{

BYTE i,j;

	Wait_ms(100);
#if 1
	for(i=0;i<RS_in;i++) 
	{  
		Printf("\r\nRS_buf2[%d]=0x%02x",(WORD)i,(WORD)RS_buf2[i]);
	}
#endif

	for(i=0;i<BUF_MAX;i++) 
		{  
			if(RS_buf2[i]=='N' /*&& DVR_buf[(i+1)]=='S'*/)
			{
			 if( RS_buf2[i+1]=='T'  ) 
			 	{
			 	 if( RS_buf2[i+2]=='S'  )
			 	 	{
			 	 	 if( RS_buf2[i+3]=='C'  ) 
			 	 	 	{
			 	 	 	return NTSC;
					 	break;
			 	 	 	}
			 	 	}
			 	}
			}

		if(RS_buf2[i]=='P' /*&& DVR_buf[(i+1)]=='S'*/)
			{
			 if( RS_buf2[i+1]=='A'  ) 
			 	{
			 	 if( RS_buf2[i+2]=='L'  )
			 	 	{
			 	 	 return PAL;
					 break;
			 	 	}
			 	}
			}
		}

	return 0;


}
#endif
//#endif	//#ifdef SUPPORT_SDCARD


/////////////////////////////////////////////////////////////////////////
//
//	Camera Mode Send Command to RS485 Poart A 
//	Note: Com_ID: Camera Command ID Number 
//		  Dev_ID: Camera Device ID Number 1~256 
//		  *Device ID Show with Input 1~256 Send Command then 0~255
//		  Protocol : 0:Pelco-P   1:Pelco-D
/////////////////////////////////////////////////////////////////////////
void CAM_TxCommand_toRS485(BYTE Com_ID)
{
	BYTE j;
	//Printf("\r\nPelcoChoiceFLAG=%02x",(WORD)PelcoChoiceFLAG);
	//Printf("\r\nCAMNumber=%02x",(WORD)CAMNumber);
	//Printf("\r\nCom_ID=%02x",(WORD)Com_ID);
	//Select Speed Dome Protocol
	switch(PelcoChoiceFLAG)
	{
		case 0:	//Pelco P
			//Clear Pelco P Command Buffer
			for(j=0;j<8;j++)
				gb_P_Com[j] = 0 ;
			gb_P_Com[0] = 0xA0;		//STX-Start Transmission
			//Check Input Source with Camera Address
				gb_P_Com[1] = CAMNumber-1;  // 0~255
			gb_P_Com[6] = 0xAF;		//ETX End Transmission
			//Select Command ID
			switch(Com_ID)
			{
			#if 0
				case CAM_CLEAR:
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x05;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					if(gb_Show_Number_Nor_HL_Status == 0)
						gb_P_Com[5] = UserPrefNumberID;	//Data 4
					else
						gb_P_Com[5] = 0xFF;
					Send_PelcoP_Command();
					break;
			#endif			
				case CAM_ZOOM_OUT_START:
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x40;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;
					
			//	case CAM_ZOOM_OUT_END:
			//	case CAM_ZOOM_IN_END:
			//	case CAM_IRIS_CLOSE_END:
			//	case CAM_IRIS_OPEN_END:
			//	case CAM_FOCUS_FAR_END:
			//	case CAM_FOCUS_NEAR_END:
				case CAM_PTZ_STOP:
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;
				
				case CAM_ZOOM_IN_START:
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x20;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;
			#if 0			
				case CAM_IRIS_CLOSE_START:
					gb_P_Com[2] = 0x08;	//Data 1
					gb_P_Com[3] = 0;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_IRIS_OPEN_START:
					gb_P_Com[2] = 0x04;	//Data 1
					gb_P_Com[3] = 0;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_FOCUS_FAR_START:
					gb_P_Com[2] = 0x01;	//Data 1
					gb_P_Com[3] = 0;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_FOCUS_NEAR_START:
					gb_P_Com[2] = 0x02;	//Data 1
					gb_P_Com[3] = 0;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;

				case CAM_FOCUS_SPEED:
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x27;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					if(gb_Show_Number_Nor_HL_Status == 0)
						gb_P_Com[5] = UserPrefNumberID - 1;	//Data 4
					else
						gb_P_Com[5] = 0xFF;
					//Check Max Value
					if(gb_P_Com[5] >= 0x03)
						gb_P_Com[5] = 0x03;
					Send_PelcoP_Command();
					break;
				case CAM_ZOOM_SPEED:
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x25;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					if(gb_Show_Number_Nor_HL_Status == 0)
						gb_P_Com[5] = UserPrefNumberID - 1;	//Data 4
					else
						gb_P_Com[5] = 0xFF;
					//Check Max Value
					if(gb_P_Com[5] >= 0x03)
						gb_P_Com[5] = 0x03;
					Send_PelcoP_Command();
					break;
				#endif	
				case CAM_SET:
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x03;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					//if(gb_Show_Number_Nor_HL_Status == 0)
					//	gb_P_Com[5] = UserPrefNumberID;	//Data 4
					//else
						gb_P_Com[5] = PresetNumber;
					Send_PelcoP_Command();
					break;
				case CAM_CALL:
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x07;	//Data 2
					gb_P_Com[4] = 0;	//Data 3
					//if(gb_Show_Number_Nor_HL_Status == 0)
					//	gb_P_Com[5] = UserPrefNumberID;	//Data 4
					//else
						gb_P_Com[5] = PresetNumber;
					Send_PelcoP_Command();
					break;
				case CAM_PTZ_RIGHT:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x02;	//Data 2
					if(SpeedDomeMode==1)
						gb_P_Com[4] = 0xff;	//Data 3	
					else
						gb_P_Com[4] = gb_PTZ_Speed;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_PTZ_LEFT:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x04;	//Data 2
					if(SpeedDomeMode==1)
						gb_P_Com[4] = 0xff; //Data 3	
					else
						gb_P_Com[4] = gb_PTZ_Speed;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_PTZ_UP:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x08;	//Data 2		
					gb_P_Com[4] = 0;	//Data 3
					if(SpeedDomeMode==1)
						gb_P_Com[5] = 0xff; //Data 3	
					else	
						gb_P_Com[5] = gb_PTZ_Speed;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_PTZ_DOWN:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x10;	//Data 2					
					gb_P_Com[4] = 0;	//Data 3
					if(SpeedDomeMode==1)
						gb_P_Com[5] = 0xff; //Data 3	
					else	
						gb_P_Com[5] = gb_PTZ_Speed;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_MENU_ENTER:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x03; //Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0x5F;	//Data 4
					Send_PelcoP_Command();
					break;	
				case CAM_Iris_Open:	
					gb_P_Com[2] = 0x04;	//Data 1
					gb_P_Com[3] = 0; //Data 2
					gb_P_Com[4] = 0;	//Data 3
					gb_P_Com[5] = 0;	//Data 4
					Send_PelcoP_Command();
					break;	
				#if 0	
				case CAM_PTZ_RIGHT_UP:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x0A;	//Data 2
					gb_P_Com[4] = gb_PTZ_Right_Speed;	//Data 3
					gb_P_Com[5] = gb_PTZ_Up_Speed;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_PTZ_RIGHT_DOWN:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x12;	//Data 2
					gb_P_Com[4] = gb_PTZ_Right_Speed;	//Data 3
					gb_P_Com[5] = gb_PTZ_Down_Speed;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_PTZ_LEFT_UP:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x0C;	//Data 2
					gb_P_Com[4] = gb_PTZ_Left_Speed;	//Data 3
					gb_P_Com[5] = gb_PTZ_Up_Speed;	//Data 4
					Send_PelcoP_Command();
					break;
				case CAM_PTZ_LEFT_DOWN:	
					gb_P_Com[2] = 0;	//Data 1
					gb_P_Com[3] = 0x14;	//Data 2
					gb_P_Com[4] = gb_PTZ_Left_Speed;	//Data 3
					gb_P_Com[5] = gb_PTZ_Down_Speed;	//Data 4
					Send_PelcoP_Command();
					break;
				#endif	
			}
			break;
		case 1:	//Pelco D
			//Clear Pelco D Command Buffer
			for(j=0;j<7;j++)
				gb_P_Com[j] = 0 ;
			gb_P_Com[0] = 0xFF;		//Synchronization Byte
			//Check Input Source with Camera Address
				gb_P_Com[1] = CAMNumber; // 1~256
			//Select Command ID
			switch(Com_ID)
			{
			#if 0
				case CAM_CLEAR:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x05;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					if(gb_Show_Number_Nor_HL_Status == 0)
						gb_P_Com[5] = UserPrefNumberID;	//Data 2
					else
						gb_P_Com[5] = 0xFF;
					Send_PelcoD_Command();
					break;
			#endif			
				case CAM_ZOOM_OUT_START:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x40;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;
				
			//	case CAM_ZOOM_OUT_END:
			//	case CAM_ZOOM_IN_END:
			//	case CAM_IRIS_CLOSE_END:
			//	case CAM_IRIS_OPEN_END:
			//	case CAM_FOCUS_FAR_END:
			//	case CAM_FOCUS_NEAR_END:
				case CAM_PTZ_STOP:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;
				
				case CAM_ZOOM_IN_START:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x20;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;
			#if 0		
				case CAM_IRIS_CLOSE_START:
					gb_P_Com[2] = 0x04;	//Command 1
					gb_P_Com[3] = 0;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;

				case CAM_FOCUS_FAR_START:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x80;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_FOCUS_NEAR_START:
					gb_P_Com[2] = 0x01;	//Command 1
					gb_P_Com[3] = 0;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;

				case CAM_FOCUS_SPEED:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x27;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					if(gb_Show_Number_Nor_HL_Status == 0)
						gb_P_Com[5] = UserPrefNumberID - 1;	//Data 2
					else
						gb_P_Com[5] = 0xFF;
					//Check Max Value
					if(gb_P_Com[5] >= 0x03)
						gb_P_Com[5] = 0x03;
					Send_PelcoD_Command();
					break;
				case CAM_ZOOM_SPEED:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x25;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					if(gb_Show_Number_Nor_HL_Status == 0)
						gb_P_Com[5] = UserPrefNumberID - 1;	//Data 2
					else
						gb_P_Com[5] = 0xFF;
					//Check Max Value
					if(gb_P_Com[5] >= 0x03)
						gb_P_Com[5] = 0x03;
					Send_PelcoD_Command();
					break;
			#endif		
				case CAM_PTZ_RIGHT:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x02;	//Command 2
					if(SpeedDomeMode==1)
						gb_P_Com[4] = 0xff; //Data 3	
					else
						gb_P_Com[4] = gb_PTZ_Speed;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_PTZ_LEFT:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x04;	//Command 2
					if(SpeedDomeMode==1)
						gb_P_Com[4] = 0xff; //Data 3	
					else
						gb_P_Com[4] = gb_PTZ_Speed;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_PTZ_UP:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x08;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					if(SpeedDomeMode==1)
						gb_P_Com[5] = 0xff; //Data 3	
					else
						gb_P_Com[5] = gb_PTZ_Speed;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_PTZ_DOWN:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x10;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					if(SpeedDomeMode==1)
						gb_P_Com[5] = 0xff; //Data 3	
					else
						gb_P_Com[5] = gb_PTZ_Speed;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_SET:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x03;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					//if(gb_Show_Number_Nor_HL_Status == 0)
					//	gb_P_Com[5] = UserPrefNumberID;	//Data 2
					//else
						gb_P_Com[5] = PresetNumber;
					Send_PelcoD_Command();
					break;
				case CAM_CALL:
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x07;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					//if(gb_Show_Number_Nor_HL_Status == 0)
					//	gb_P_Com[5] = UserPrefNumberID;	//Data 2
					//else
						gb_P_Com[5] = PresetNumber;
					Send_PelcoD_Command();
					break;
				case CAM_MENU_ENTER:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x03;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					gb_P_Com[5] = 0x5F;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_Iris_Open:	
					gb_P_Com[2] = 0x02;	//Command 1
					gb_P_Com[3] = 0;	//Command 2
					gb_P_Com[4] = 0;	//Data 1
					gb_P_Com[5] = 0;	//Data 2
					Send_PelcoD_Command();
					break;	
			#if 0		
				case CAM_PTZ_RIGHT_UP:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x0A;	//Command 2
					gb_P_Com[4] = gb_PTZ_Right_Speed;	//Data 1
					gb_P_Com[5] = gb_PTZ_Up_Speed;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_PTZ_RIGHT_DOWN:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x12;	//Command 2
					gb_P_Com[4] = gb_PTZ_Right_Speed;	//Data 1
					gb_P_Com[5] = gb_PTZ_Down_Speed;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_PTZ_LEFT_UP:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x0C;	//Command 2
					gb_P_Com[4] = gb_PTZ_Left_Speed;	//Data 1
					gb_P_Com[5] = gb_PTZ_Up_Speed;	//Data 2
					Send_PelcoD_Command();
					break;
				case CAM_PTZ_LEFT_DOWN:	
					gb_P_Com[2] = 0;	//Command 1
					gb_P_Com[3] = 0x14;	//Command 2
					gb_P_Com[4] = gb_PTZ_Left_Speed;	//Data 1
					gb_P_Com[5] = gb_PTZ_Down_Speed;	//Data 2
					Send_PelcoD_Command();
					break;
			#endif		
			}
			break;
#ifdef GE_PROTOCOL
		case 2:
			//Clear GE Command Buffer
			for(j=0;j<9;j++)
				GE_Com[j] = 0 ;
			
			GE_Com[0] = 0xFF;		//STX-Start Transmission
			//Check Input Source with Camera Address
				GE_Com[6] = CAMNumber;  // 0~255
			//Select Command ID
			switch(Com_ID)
			{
				case CAM_PTZ_RIGHT: 
					GE_Com[1] = 0x07;	//Length 
					GE_Com[2] = 0x09;	//Message type 1 
					GE_Com[3] = 0x05; //Message type 2
					GE_Com[4] = 0;	//Destination
					GE_Com[5] = 0;	//Source
					GE_Com[7] = 0xc0;	//Motor command 
					Send_GE_Command();
					break;
				case CAM_PTZ_LEFT:	
					GE_Com[1] = 0x07;	//Length 
					GE_Com[2] = 0x09;	//Message type 1 
					GE_Com[3] = 0x05; //Message type 2
					GE_Com[4] = 0;	//Destination
					GE_Com[5] = 0;	//Source
					GE_Com[7] = 0x80;	//Motor command 
					Send_GE_Command();
					break;
				case CAM_PTZ_UP:	
					GE_Com[1] = 0x07;	//Length 
					GE_Com[2] = 0x09;	//Message type 1 
					GE_Com[3] = 0x05; //Message type 2
					GE_Com[4] = 0;	//Destination
					GE_Com[5] = 0;	//Source
					GE_Com[7] = 0x81;	//Motor command 
					Send_GE_Command();
					break;
				case CAM_PTZ_DOWN:	
					GE_Com[1] = 0x07;	//Length 
					GE_Com[2] = 0x09;	//Message type 1 
					GE_Com[3] = 0x05; //Message type 2
					GE_Com[4] = 0;	//Destination
					GE_Com[5] = 0;	//Source
					GE_Com[7] = 0xc1;	//Motor command 
					Send_GE_Command();
					break;
				case CAM_ZOOM_IN_START:	
					GE_Com[1] = 0x07; //Length 
					GE_Com[2] = 0x09; //Message type 1 
					GE_Com[3] = 0x05; //Message type 2
					GE_Com[4] = 0;	//Destination
					GE_Com[5] = 0;	//Source
					GE_Com[7] = 0xc1; //Motor command 
					Send_GE_Command();	
					break;
				case CAM_ZOOM_OUT_START:	
					GE_Com[1] = 0x07;	//Length 
					GE_Com[2] = 0x09;	//Message type 1 
					GE_Com[3] = 0x05; //Message type 2
					GE_Com[4] = 0;	//Destination
					GE_Com[5] = 0;	//Source
					GE_Com[7] = 0xc1;	//Motor command 
					Send_GE_Command();
					break;


			}
			
		break;
#endif		
	}
	
}


////////////////////////////////////////////////////////////////
//
//	Send Pelco P Command Using RS485 Port A Function
//
////////////////////////////////////////////////////////////////
void Send_PelcoP_Command(void)
{
	BYTE ii,j;

	//Generate Camera Mode Pelco P Check Sum
	gb_P_Com[7] = gb_P_Com[0];	
	for(j=1;j<7;j++)
		gb_P_Com[7] = gb_P_Com[7]^gb_P_Com[j];

	//Change_RS485_TxRx(0,RS485_TX);
	//Start Send Pelco P Command
	//Printf("\r\nTH1=%02x",(WORD)TH1);
	//Printf("\r\nBaud_rate=%d",(WORD)Baud_rate);
	switch(Baud_rate)
	{
	case Baud_rate2400:
		S2BRT=0xd0;//0xd0;
		break;
	case Baud_rate4800:
		S2BRT=0xe8;//0xe8;
		break;
	case Baud_rate9600:
		S2BRT=0xf4;//0xf4;
		break;
	}
	
	Printf("\r\nTH111111111111111=%02x",(WORD)TH1);
	Wait_ms(100);
	for(ii=0;ii<8;ii++)
	{
		RS2_tx(gb_P_Com[ii]);	
	}
	Wait_ms(100);
	S2BRT=0xf4;	//Baud_rate960
	//TH1=0xf4;	//Baud_rate9600
	//while(!(READ_PCB_REG(SP0STS) & TEMT));
	//Change_RS485_TxRx(0,RS485_RX);

}


////////////////////////////////////////////////////////////////
//
//	Send Pelco D Command Using RS485 Port A Function
//
////////////////////////////////////////////////////////////////
void Send_PelcoD_Command(void)
{
	BYTE ii,j;

	//Generate Camera Mode Pelco D Check Sum
	gb_P_Com[6] = gb_P_Com[1];	
	for(j=2;j<6;j++)
		gb_P_Com[6] = gb_P_Com[6]+gb_P_Com[j];

	switch(Baud_rate)
	{
	case Baud_rate2400:
		S2BRT=0xd0;//0xd0;
		break;
	case Baud_rate4800:
		S2BRT=0xe8;//0xe8;
		break;
	case Baud_rate9600:
		S2BRT=0xf4;//0xf4;
		break;
	}

	Printf("\r\ngb_p_Com[0]=%02x",(WORD)gb_P_Com[0]);
	Wait_ms(100);
	//Change_RS485_TxRx(0,RS485_TX);
	//Start Send Pelco D Command
	for(ii=0;ii<7;ii++)
	{
		RS2_tx(gb_P_Com[ii]);	
	}

	Wait_ms(100);
	S2BRT=0xf4;	//Baud_rate960
	//while(!(READ_PCB_REG(SP0STS) & TEMT));
	//Change_RS485_TxRx(0,RS485_RX);
}

#ifdef GE_PROTOCOL
////////////////////////////////////////////////////////////////
//
//	Send GE Command Using RS485 Port A Function
//
////////////////////////////////////////////////////////////////
void Send_GE_Command(void)
{
	BYTE ii,j;

	//Generate Camera Mode Pelco D Check Sum
	GE_Com[8] = 0;	
	for(j=1;j<=GE_Com[1];j++)
		{GE_Com[8] = GE_Com[8]+GE_Com[j];}

	GE_Com[8]=~GE_Com[8]+1;

	switch(Baud_rate)
	{
	case Baud_rate2400:
		S2BRT=0xd0;//0xd0;
		break;
	case Baud_rate4800:
		S2BRT=0xe8;//0xe8;
		break;
	case Baud_rate9600:
		S2BRT=0xf4;//0xf4;
		break;
	}

	Printf("\r\n",0);
	
	Wait_ms(1000);
	//Change_RS485_TxRx(0,RS485_TX);
	//Start Send Pelco D Command
	for(ii=0;ii<=GE_Com[1];ii++)
	{
		RS2_tx(GE_Com[ii]);	
	}

	Wait_ms(400);
	S2BRT=0xf4;	//Baud_rate960
	//while(!(READ_PCB_REG(SP0STS) & TEMT));
	//Change_RS485_TxRx(0,RS485_RX);
}
#endif


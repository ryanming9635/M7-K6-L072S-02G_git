//
// HS_KeyRemo.h
// Default function for Key Input and Remocon Input For HiSharp Function
//
//=============================================================================
//		                    Operation Key Mapping
//=============================================================================

#include <math.h>
#include "Config.h"
#include "reg.h"
#include "typedefs.h"
#include "main.h"
#include "tw88.h"
#include "i2c.h"
#include "adc.h"
#include "osdbasic.h"
#include "dispinfo.h"
#include "debug.h"
#include "etc_eep.h"
#include "measure.h"
#include "Printf.h"
#include "audio.h"
#include "osdmenu.h"
#include "pc_eep.h"
#include "KeyRemo.h"
#include "CPU.h"
#include "rgbmix.h"			
#include "panel.h"
//#include "HS_IOdef"
#include "HS_DisplayOSD.h"
#include "HS_keyremo.h"
#include "HS_DVRProtocol.h"

#include "HS_IOdef.h"

#if 0//mask by ryan@20170907
typedef enum
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
#endif

typedef enum
{
	No_SELECT,
	REVERSE_SELECT,
	LEFT_SELECT,
	RIGHT_SELECT,
	CAMC_SELECT,
	JUMP_SELECT,
	EVENT_SELECT,
	//PARK_SELECT,
	//NORMALL_SELECT,
	SELECT_NUM
}SELECTModeType;

#if 0
code unsigned char SEQTable[]={0x00,0x01,0x02,0x03,0xFF};						  // 0xFF:return (FD SEQ Mode)
code unsigned char ParkTable[]={0xFE,0x04,0x05,0x06,0x07,0x0C,0x0D,0x08,0x0e,0x00,0x01,0x02,0x03,0xFF};    //2007.4.10 Justin
code unsigned char LeftTable[]={0x00,0x06,0x09};  
code unsigned char RightTable[]={0x01,0x07,0x0A};
code unsigned char ReverseTable[]={0x13,0x06,0x07,0x08,0x0e};				
code unsigned char JumpTable[]={0x0B,0xFD,0x04,0x05,0x06,0x07,0x0c,0x0d,0x08,0x0e,0x00,0x01,0x02,0x03};   //2007.4.10 Justi

			  BYTE  SourceMode=0;            
              BYTE  CkPARK=0,CkTMode=0,AVFlag=0,TGFlag=0,TGFlag1=0,TDisplayFlag=0;
              BYTE  Attr_A=0x02,Attr_B=0x02,Attr_C=0x02,Attr_R=0x03; 
              BYTE  ParkIndex=0,ParkIndex1=0,JumpIndex=0,ReverseIndex=0,RightIndex=0,LeftIndex=0,SEQIndex=0;
              BYTE  SEQFlag=0,TimeStep,SEQTime=0;
              BYTE  ParkTime=0,RightTime=0,LeftTime=0,ReverseTime=0,RtFlag=0,LtFlag=0,ReverseFlag=0,ParkFlag=0;
extern CODE   BYTE  Init_Osd_MainMenu[];//WILLIAM-V1.43-970403
		      BYTE	PRIORITY;
#endif

#if 0  //Pinchi 20140905 disable for pin define in HS_IOdef.h
#define LEFT_T     P0_0
#define Right_T    P0_1
#define REVERSE_T  P0_2
#ifdef AWT_ML072S
#define PARK_T     P0_3
#else
#define PARK_T     P0_4
#endif
//#define VGA_T      P0_4
#define CAMC_T     P0_3
#define CAMD_T     P0_5
#endif

BYTE  Attr_A=0x02,Attr_B=0x02,Attr_C=0x02,Attr_R=0x03;

BYTE Gauge_Flag=0;//add by yran@20171211

#ifdef USE_CAMD	
CODE unsigned char ParkTable[]={0x00,0x00,0x00,/*0x00,*/0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x0c,0x0d,0x08,0x0e,0x0b,0x09,0x0a,0x10,0x11,0x12,0x13,0x16,0x17,0x18,0x1c,0x14,0x09,0x15,0x19,0x1a,0x1b,0x1f,0x20,0x21};
#else
  #ifdef HTRV
	CODE unsigned char ParkTable[]={0x00,0x00,/*0x00,0x00,*/0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x0c,0x0d,0x08,0x0e,0x22,0x0b,0x09,0x0a,0x10,0x11,0x12,0x13,0x16,0x17,0x18,0x1c,0x14,0x09,0x15,0x19,0x1a,0x1b,0x1f,0x20,0x21};
  #else
	CODE unsigned char ParkTable[]={0x00,0x00,/*0x00,0x00,*/0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x0c,0x0d,0x08,0x0e,0x0b,0x09,0x0a,0x10,0x11,0x12,0x13,0x16,0x17,0x18,0x1c,0x14,0x09,0x15,0x19,0x1a,0x1b,0x1f,0x20,0x21};
  #endif
#endif						     //	0	  1				     2	  3	   4	     5	  6	   7	    8	9	  10	   11   12	13	 14	  15	   16	17	 18	  19	    20   21    22    23   24    25    26   27    28   29    30    31    32

#ifdef USE_CAMD	
CODE unsigned char JumpTable[]={CAM_QUAD,SEQ,CAM_AB,CAM_CR,CAM_AR,CAM_RB,CAM_AC,CAM_CB,CAM_RAB_T,CAM_RAB_H,CAM_RC,CAM_A,CAM_B,CAM_C,CAM_R,CAM_D};
#else
  #ifdef HTRV
	CODE unsigned char JumpTable[]={CAM_QUAD,SEQ,CAM_AB,CAM_CR,CAM_AR,CAM_RB,CAM_AC,CAM_CB,CAM_RAB_T,CAM_RAB_H,CAM_RC,CAM_A,CAM_B,CAM_C,CAM_R};
  #else
	CODE unsigned char JumpTable[]={CAM_QUAD,SEQ,CAM_AB,CAM_CR,CAM_AR,CAM_RB,CAM_AC,CAM_CB,CAM_RAB_T,CAM_RAB_H,CAM_A,CAM_B,CAM_C,CAM_R};
  #endif
#endif

#ifdef HTRV
  #if 1  //Pinchi 20150825 add for HTRV
	CODE unsigned char RearTable[]={CAM_R,CAM_AR,CAM_RB,CAM_RAB_T,CAM_RAB_H,CAM_RC};
  #else
	CODE unsigned char RearTable[]={CAM_R,CAM_AR,CAM_RB,CAM_CR,CAM_RAB_T,CAM_RAC_T,CAM_RBC_T,CAM_RAB_H,CAM_RC,CAM_RAC_T2,CAM_RBC_T2};
  #endif
#else
CODE unsigned char RearTable[]={CAM_R,CAM_AR,CAM_RB,CAM_CR,CAM_RAB_T,CAM_RAC_T,CAM_RBC_T,CAM_RAB_H,CAM_RAC_T2,CAM_RBC_T2};
#endif
	
#ifdef AWT_ML072Q
CODE unsigned char LeftTable[]={CAM_A,CAM_AB,CAM_AC,CAM_AR,CAM_ABC,CAM_ABR,CAM_ACR};  
CODE unsigned char RightTable[]={CAM_B,CAM_BA,CAM_BC,CAM_BR,CAM_BAC,CAM_BAR,CAM_BCR};
CODE unsigned char TriggerC_Table[]={CAM_C,CAM_CA,CAM_CB,CAM_CR,CAM_CAB,CAM_CAR,CAM_CBR};
#else
CODE unsigned char RightTable[]={CAM_B,CAM_RB,CAM_ABR_T4,CAM_BA};
CODE unsigned char LeftTable[]={CAM_A,CAM_AR,CAM_ABR_T3,CAM_AB};
#endif

#ifdef USE_CAMD	
CODE unsigned char SEQTable[]={CAM_A,CAM_B,CAM_C,CAM_R,CAM_D};	//SEQ  	
#else
CODE unsigned char SEQTable[]={CAM_A,CAM_B,CAM_C,CAM_R};	//SEQ  	
#endif

CODE unsigned char JumpTable_S[]={CAM_A,CAM_B,CAM_C,/*CAM_R,*/SEQ};

//CODE unsigned char PriorityOffSelTable[]={CAM_A,CAM_B,CAM_C,CAM_R,CAM_D,VGAMode};	//Priority Off table
//CODE unsigned char PriorityOffParkTable[]={CAM_A,CAM_B,CAM_C,CAM_R,CAM_D,VGAMode,AVMode};	//Priority Off table

BYTE TriggerFlag;
BYTE NowModeState;
BYTE TimeStep;
BYTE SEQFlag;
BYTE SEQIndex;
//extern SourceModeType SelectModeType;
BYTE TriggerMode;
BYTE SelectBoxMode=0;
BYTE SelectBoxADC;
bit ParkFlag;
bit AVFlag=0;
bit VGAAudio=0;

extern bit ChangeKey;

extern BYTE CAM_QUAD_TO;

extern BYTE TR_JUMP_HOLD;//ryan@20170912
extern BYTE TR_JUMP_Flag;//ryan@20170912
extern BYTE RELEASE_TR_JUMP_Flag;//ryan@20170912
BYTE AV_MODE_DELAY=0xff;

extern bit  JUMPAVFlag;
extern BYTE	TriggerStatus;
extern BYTE	BookMarkState;
extern BYTE ReverseModeFlag;//william-v1.43-970402

#ifdef HTRV  //Pinchi 20150825 add model #define
extern BYTE GaugeVStart;
extern BYTE GaugeSetup;  //Pinchi 20150827 add
extern BYTE GaugeInfoOSD;  //Pinchi 20151209 add
#endif
extern CODE BYTE Init_Osd_DisplayInput[];  //Pinchi 20140924 add
extern CODE BYTE Init_Osd_DisplayGAUGEWindow[];  //Pinchi 20140924 add
extern CODE BYTE Init_Osd_DisplayInput_M[];  //Pinchi 20140925 add

extern BYTE	displayhold_flag;  //Pinchi 20150319 add
extern BYTE VInputStd;  //Pinchi 20141028 add

#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
extern bit IsDrawNoVideoSignal;
#endif

#ifdef SUPPORT_AC_ON_REDUCE_TIME  //Pinchi 20150903 add
extern bit IsFirstRunfromAC;
#endif

extern bit  DisplayInputHold; //ryan@20170921

extern BYTE bLastTrigger;  

extern BYTE InitVideoDataSrc;

/*------------------------------*/
/*    選擇SourceMode顯示畫面    */
/*------------------------------*/
#ifdef AWT_ML072S
#else
void SetSourceMode(BYTE Index,char attr0,char attr1,char attr2,char attr3)
{   
	switch(Index)
	{
		case CAM_A:
		case CAM_B:	
		case CAM_C:
		case CAM_R:
		case CAM_AB:
		case CAM_CR:
		case CAM_AR:
		case CAM_RB:
		case CAM_AC:
		case CAM_CB:
		case CAM_RAB_T:
		case CAM_RAB_H:

		#ifdef HTRV
		case CAM_RC:
		#endif

		case CAM_QUAD:
		case CAM_ABR_T3:
		case CAM_ABR_T4:
		case CAM_RAC_T:
		case CAM_RBC_T:
		case CAM_RAC_T2:
		case CAM_RBC_T2:
		case CAM_BA:
		case CAM_BC:
		case CAM_BR:
		case CAM_CA:
		case CAM_ABC:
		case CAM_ABR:
		case CAM_ACR:
		case CAM_BAC:
		case CAM_BAR:
		case CAM_BCR:
		case CAM_CAB:
		case CAM_CAR:
		case CAM_CBR:

		#ifdef AWT_SUPPORT_4_3_SCREEN//ryan@20170907
		//Printf("\r\n[MSG]SetSourceMode() => CAM to 16:9");  //pinchi test
		WriteDecoder(0x0a,0x16); ///_FULLPANEL_20140313_xx
		WriteDecoder(0x61,0x80);
		WriteDecoder(0x66,0x00);
		 #endif	
		 
		TW2835Command(ParkTable[Index],attr0,attr1,attr2,attr3);
		ChangeInput(CH_TW2835);
		AV_MODE_DELAY=0;
		//TW2835Cmd("\n\rtouch 1\n\r");
		//TW2835Cmd("\n\ravout 0\n\r");
		//AVOutPutSelect=0;

#ifdef HTRV_SUPPORT_4_3_SCREEN  //Pinchi 20151209 add
	#ifdef HTRV
	  #if 1  //Pinchi 20150901 add GaugeSetup condition
		if ((Index == CAM_RC) || (GaugeSetup == 1))
	  #else
		if(Index==CAM_RC)
	  #endif
		{
		#ifdef HTRV_REDUCE_SCREEN_CHANGE  //Pinchi 20150828 add
			if (ReadDecoder(0x66) == 0x00)
		#endif
		#if 1  //Pinchi 20150826 change the setting for 4:3
			{
				Printf("\r\n[MSG]SetSourceMode() => CAM_RC to 4:3");  //pinchi test
				WriteDecoder(0x0a,0x13); 
				WriteDecoder(0x61,0xa6);
				WriteDecoder(0x66,0x60);
			}
		#else
			WriteDecoder(0x0a,0x21); 
			WriteDecoder(0x60,0xdf);
			WriteDecoder(0x66,0x60);
		#endif
		}
		else
		{
		#ifdef HTRV_REDUCE_SCREEN_CHANGE  //Pinchi 20150828 add
			if (((Index != CAM_R) || ((Index == CAM_R) && ((TriggerFlag & 0x20) == 0)))
			&& (ReadDecoder(0x66) == 0x60))
		#endif
			{
				 Printf("\r\n[MSG]SetSourceMode() => CAM to 16:9");  //pinchi test
				 WriteDecoder(0x0a,0x16); ///_FULLPANEL_20140313_xx
				 WriteDecoder(0x61,0x80);
				 WriteDecoder(0x66,0x00);
			}
		}
	#endif
#endif

	#if 0
		if(Index==CAM_RC)
			{
			WriteDecoder(0x66,0x45);
		////	if(VInputStd==PAL)
			////	WriteDecoder(0x61,0xf7);
			////else
				WriteDecoder(0x61,0xfa);
		////	CAM_RCFlag=1;
			}
		else
			{		
		////	CAM_RCFlag=0;
			WriteDecoder(0x66,0x00);
			WriteDecoder(0x61,0xb1);
			}
	#endif	
		break;

	#ifdef SUPPORT_PC  //Pinchi 20150319 add
		 case VGAMode:	
		 	//TW2835Cmd("\n\rtouch 0\n\r");
			//TW2835Cmd("\n\ravout 1\n\r");	
			ChangeInput(PC);
			//AVOutPutSelect=1;
			break;
	#endif

	#ifdef USE_CAMD	
	 	case CAM_D:
			ChangeInput(CH_CAMD);
			//TW2835Cmd("\n\rtouch 1\n\r");
			//TW2835Cmd("\n\ravout 0\n\r");
			//AVOutPutSelect=0;
			break;
	#endif

		case AVMode:

				if(AV_MODE_DELAY==0xff)
				{
				AV_MODE_DELAY=0;
				ChangeInput(CH_AV);
				AV_MODE_DELAY=1;		
				}
				else
				{
				AV_MODE_DELAY=1;	
				 ChangeInput(CH_AV);
				
				}
			//TW2835Cmd("\n\rtouch 1\n\r");
			//TW2835Cmd("\n\ravout 0\n\r");
			//AVOutPutSelect=0;
			break;

		case SEQ:
		 	SEQIndex=0;
		 	SEQFlag=1;
			SEQTime=TimeStep;
		 	break;
	}
}
#endif
#ifdef QUAD
void SetSelectMode(void)
{
	BYTE Maxsource;

#if 1  //Pinchi 20150826 modify for HTRV no Priority
  #ifdef HTRV
	Maxsource=CAM_RAB_H+1;
  #else	
	if(Priority)
		Maxsource=CAM_R;
	else
		Maxsource=CAM_RAB_H;
  #endif
#else
	if(Priority)
		Maxsource=CAM_R;
	else
	{
	#ifdef HTRV
		Maxsource=CAM_RAB_H+1;
	#else
		Maxsource=CAM_RAB_H;
	#endif
	}
#endif

    NowModeState=SelectMode;
    SEQFlag=0;
    TW2835Cmd("\n\rmode 0\n\r");

	#if 0
	// trigger AV & VGA
    if(ParkFlag==1 && TriggerMode == VGA_TRIG)
	    {
	    	if(AVFlag==0)
	 	   	{	   	
		 	   	SelectModeType=AVMode;
		 		AVFlag=1;
	 	   	}
	 		else
	 		{
		 	    if(SelectModeType>=Maxsource)
		 	     SelectModeType=AVMode;
		 	    else
		 	   	 SelectModeType++;
		 	}
	    }
	//trigger AV
	else
	#endif

#ifdef HTRV  //Pinchi 20150826 add
	if (ParkFlag==1 /*&& TriggerMode!=VGA_TRIG*/)
	{
	   	if(AVFlag==0)
	   	{
	 	   	SelectModeType=AVMode;
	 		AVFlag=1;
	   	}
		else
		{
	 	    if(SelectModeType>=Maxsource)
				SelectModeType = CAM_A;  //Pinchi 20150827 change to CAM_A by follow HTRV spec.
			else if (SelectModeType == CAM_R)  //Pinchi 20150827 add by follow HTRV spec.
				SelectModeType=AVMode;
			else if (SelectModeType==AVMode)
			{
			#ifdef USE_CAMD		
			 	SelectModeType=CAM_D;	
			#else
			 	SelectModeType=CAM_AB;  //Pinchi 20150826 change to CAM_AB by follow HTRV spec.
			#endif	
			}
	 	    else
				SelectModeType++;
	 	}
	}
	#if 0	
	//trigger VGA
	else if (ParkFlag==0 && TriggerMode==VGA_TRIG)
		{
		if(SelectModeType>=Maxsource)
			SelectModeType=VGAMode;
		else
			SelectModeType++;
		}
	#endif	
	//no trigger
    else
#endif  //#ifdef HTRV
    {
        if(SelectModeType>=Maxsource)
        {
 	    #ifdef USE_CAMD		
			SelectModeType=CAM_D;	
		#else
	//>>>>>>>>>>>>>>>>>>>>>>>>>		//william @20130813
		  #ifdef AWT_ML072Q		
		     	#if 0 //def HTRV  //Pinchi 20150826 disable for duplicate setting
		    	SelectModeType=CAM_A;
		    	#else
		  			if (Priority == 0)  //Pinchi 20140911 add for AWT ML072Q
					SelectModeType = CAM_A;
					else
					SelectModeType = AVMode;
		    	#endif
		  #else
	//<<<<<<<<<<<<<<<<<<<<<<<<<	
			SelectModeType=CAM_A;
		  #endif
		#endif
 	   }
 	   else
 	   {
		#ifdef AWT_ML072Q  //Pinchi 20140911 add for AWT ML072Q
			if (Priority == 0)  //Priority=ON
			{
				if (SelectModeType == AVMode)
				{
					SelectModeType = CAM_AB;
				#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
					IsDrawNoVideoSignal = 0;
			  	#endif
				}
				else if (SelectModeType == CAM_R)
					SelectModeType = AVMode;
				else
					SelectModeType++;
			}
			else
		#endif
			#if 0
			{
				if (SelectModeType == AVMode)
					SelectModeType = CAM_A;
				else
					SelectModeType++;
			}
			#endif
			{
			#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
				if (SelectModeType == AVMode)
				{
					IsDrawNoVideoSignal = 0;
			  	}
			#endif
	 	   	 	SelectModeType++;
			}
 	   }
    }
#if 0  //pinchi test
   if (ReadEEP(EEP_COSDMode) !=0 )  //Pinchi 20141014 add for AWT ML072Q
   {
   		dPressSelectTime = SystemClock;
		IsPressSelectKey = 1;
   }
#endif
   SetSourceMode(SelectModeType,Attr_A,Attr_B,Attr_C,Attr_R); 

 #if 1//ryan@20170906
 
   	WriteEEP(EEP_SelectMode,SelectModeType);

 #else
   if(!(SelectModeType==AVMode/*||SelectModeType==VGAMode*/))
   {
   		WriteEEP(EEP_SelectMode,SelectModeType);
   }
  #endif

  WriteEEP(EEP_NowModeState,NowModeState);
   
#if 1  //Pinchi 20141024 modify
	if (ReadEEP(EEP_COSDMode) == 1)
		displayhold_flag = 3;
#else
	if (ReadEEP(EEP_COSDMode) == 1)  //Pinchi 20141024 modify to display AV 2s
	{
 		if (SelectModeType == AVMode)
			displayhold_flag = 4;
		else
			displayhold_flag = 3;
	}
#endif
   // Printf("\r\nSelectModeType=%d",(WORD)SelectModeType);
}

#else
void SetSelectMode(void)
{
	
		NowModeState=SelectMode;
		if(SEQFlag==1)
		{
		   	SEQFlag=0;  	
		  	 //ParkIndex=ParkIndex1;
			 CheckSourceMode(SelectModeType);
			 return;
		} 	
		//william-v1.0-970718>>>>>>>>>>>>>>>>>>>>>>
		//push source cancel jump mode 
#if 1	
		
		
	if(ParkFlag)
	{
	
		if(AVFlag==0)
		{
		        if(SelectModeType!=SOURCE_AV)//andy-980428
			   //ParkIndex1=ParkIndex;	//wiiliam-v1.0-970804
			SelectModeType=SOURCE_AV;
			AVFlag=1;
			CheckSourceMode(SelectModeType);
		}
		else
		{
		#ifdef AWT_ML072S	
				#ifdef HS
			if(SelectModeType==1)
					SelectModeType=4;	
			else if(SelectModeType==4)
					SelectModeType=2;	
			else if(SelectModeType==2)
					SelectModeType=3;	
			//if(SelectModeType<4)				
				#else				
 			if(SelectModeType<3)
				#endif
		#else
			if(SelectModeType<4)
		#endif
 				//SelectModeType++;
			 else
 			 SelectModeType=1;
			// ParkIndex1=ParkIndex;	//wiiliam-v1.0-970804
		  	CheckSourceMode(SelectModeType);
		}

			 #ifdef Hs_debug
			 Printf("\r\n (*ParkFlag=1)");
			 #endif
		
	}
#endif
	//william-ml072s-971230
	else
	{
		
	  	//sourceindex CAM A-->CAM B-->CAM R
	  	#ifdef HS
			if(SelectModeType==1)
					SelectModeType=4;	
			else if(SelectModeType==4)
					SelectModeType=2;	
			else
					SelectModeType=1;
		#else
	  	#ifdef AWT_ML072S
 			if(SelectModeType<2)
		#else
			if(SelectModeType<3)
		#endif
 				SelectModeType++;
			 else
 				SelectModeType=1;
		#endif
			
			 
			 //ParkIndex1=ParkIndex;	//wiiliam-v1.0-970804
		  	CheckSourceMode(SelectModeType);

			 #ifdef Hs_debug
			 Printf("\r\n (**ParkFlag=0)");
			 #endif
	
	}

	if(!(SelectModeType==SOURCE_AV/*||SelectModeType==VGAMode*/))
    	{WriteEEP(EEP_SelectMode,SelectModeType);}
   	WriteEEP(EEP_NowModeState,NowModeState);
}

/*------------------------------*/
/*    選擇SourceMode顯示畫面    */
/*------------------------------*/
//         Bit3  Bit2  Bit1  Bit0
//Attr_x=> Tigger   Tigger     OSD ON/OFF      MH 
void CheckSourceMode(BYTE sorce)
{

	switch(sorce)
	{
		case SOURCE_A:
			#ifdef Hs_debug
			Printf("\r\n****ChangeInput(Source_A); ");
			#endif		
			ChangeInput(COMPOSITE1); 
			break;

		#ifndef AWT_ML072S
			case SOURCE_B:
				#ifdef Hs_debug
				Printf("\r\n****ChangeInput(SOURCE_B); ");
				#endif
			ChangeInput(COMPOSITE2);
			break;
		#endif

		#ifdef  HS
			case SOURCE_B:
				#ifdef Hs_debug
				Printf("\r\n****ChangeInput(SOURCE_B); ");
				#endif
			ChangeInput(COMPOSITE4);
			break;
		#endif
		
		case SOURCE_R:
		#ifdef AWT_ML072S	
				#ifdef Hs_debug 		
				Printf("\r\n****ChangeInput(SOURCE_R); ");
				#endif
			ChangeInput(COMPOSITE2); 
		#else
			ChangeInput(COMPOSITE3); 
		#endif
			break;

		case SOURCE_AV:
		#ifdef AWT_ML072S
				#ifdef Hs_debug 		
				Printf("\r\n****ChangeInput(SOURCE_AV); ");
				#endif
			ChangeInput(COMPOSITE3); 
		#else
			ChangeInput(COMPOSITE4); 
		#endif
			break;

		case SEQ:
			SEQIndex=0;
			SEQFlag=1;
			SEQTime=TimeStep;
			DisplayInput();
			break;
	}

// if(ParkTime<10)
 //{
	if(!(SelectModeType==SOURCE_AV))
		WriteEEP(EEP_SelectMode,SelectModeType); 
	
	Printf("\r\nSelectModeType=%d",(WORD)SelectModeType);

 //WriteEEP(EEP_SourceModebuf,ParkIndex1); 		//william-v1.0-970804
 //}
//CheckMirror();

//DisplayHandler();		//william-v1.0-970725
//LCDPowerON(0);//WILLIAM-V1.42-961204

#if 0
//william-v1.0-971112>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
if(Gaugeflag==1)                                    //當設定為單一畫面CAM R時切換成4:3   
	    {
             WriteDecoder(0x0a,0x21);	//william-v1.0-971112 
             WriteDecoder(0x60,0xdf);
             WriteDecoder(0x66,0x60);   
	     }
else
	ChangeMode16_9();
#endif
  //william-v1.0-970716>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
#endif

void SEQMode(void)
{
#ifdef AWT_ML072S  //Pinchi add for compiler warning
	#ifdef HS
	#else
	BYTE val;
	#endif
#endif

#ifdef QUAD
	SetSourceMode(SEQTable[SEQIndex],Attr_A,Attr_B,Attr_C,Attr_R);
#else
	CheckSourceMode(SEQIndex);
#endif
#ifdef HS

if(SEQIndex==1)
 	SEQIndex=4;
else if(SEQIndex==4)
 	SEQIndex=2;
else if((SEQIndex==2)&&(!JUMPAVFlag&&PARK_T))
	SEQIndex=3;
else
	SEQIndex=1;


#else
#ifdef USE_CAMD	
	if(SEQIndex<4)
#else
	#ifdef AWT_ML072S		//william @20130902 v1.0.1.2
		if(!JUMPAVFlag&&PARK_T)
			val=SOURCE_AV;
		else
			val=SOURCE_R;
	
		if(SEQIndex<val)
	#else
		if(SEQIndex<3)
	#endif
#endif
		SEQIndex++;
	else
#ifdef QUAD		
		SEQIndex=0;
#else	
		SEQIndex=1;
#endif

#endif
}

void SetJumpMode(void)
{
   BYTE val;
 	//Printf("\r\nNowModeState",(WORD)NowModeState);
   if(NowModeState==JumpMode)
   {   
	 val=ReadEEP(EEP_JUMPMode);
#ifdef QUAD	 
	 if(val==0x01)
	 	TW2835Cmd("\n\rmode 2\n\r");
	 else
     	TW2835Cmd("\n\rmode 1\n\r");
     SetSourceMode(JumpTable[val],Attr_A,Attr_B,Attr_C,Attr_R);
#else
	#ifdef AWT_ML072S
		CheckSourceMode(SEQ);
	#else
		CheckSourceMode(JumpTable_S[val]);
	#endif  
#endif
   	} 
   else
   	{
   	  //NowModeState=SelectMode;
	  SEQFlag=0;
 	#ifdef QUAD
     	TW2835Cmd("\n\rmode 0\n\r");
		SetSourceMode(SelectModeType,Attr_A,Attr_B,Attr_C,Attr_R); 
	#else
	 	CheckSourceMode(SelectModeType);

		#ifdef AWT_ML072S
		WriteStringToAddr(INPUTINFO_ADDR+9," " ,1); 
		#else
		WriteStringToAddr(INPUTINFO_ADDR+8," " ,1); 
		#endif
	#endif
    }
    WriteEEP(EEP_NowModeState,NowModeState);

#if 1  //Pinchi 20141024 modify
	if (ReadEEP(EEP_COSDMode) == 1)
		displayhold_flag = 3;
#endif
}

#ifndef QUAD
/*-----------------------------------------*/
/*                CHECK MIRROR MODE                       */
/*-----------------------------------------*/
void CheckMirror(void)
{
BYTE val;

switch(InputSelection)
	{
 	case SOURCE_A:
	val=ReadEEP(EEP_CAMAMode);
	 if(val==0)
	 	{
		WriteDecoder(0xff, 0x01);
		Wait_ms(5);
	 	//WriteDecoder(0x82, 0x0d);
	 	WriteDecoder(0x82, 0x00);////mirror mode
		Wait_ms(5);
		WriteDecoder(0xff, 0x00);

	 	}
	 else	
	 	{
		WriteDecoder(0xff, 0x01);
		Wait_ms(5);
	 	//WriteDecoder(0x82, 0x0c);
	 	WriteDecoder(0x82, 0x01);///normal mode
		Wait_ms(5);
		WriteDecoder(0xff, 0x00);
		
	 	}
		break;

 	case SOURCE_B:
	val=ReadEEP(EEP_CAMBMode);
	 if(val==0)
	 	{
		WriteDecoder(0xff, 0x01);
		Wait_ms(5);
	 	//WriteDecoder(0x82, 0x0d);
	 	WriteDecoder(0x82, 0x00);
		Wait_ms(5);
		WriteDecoder(0xff, 0x00);
	 	}
	 else	
	 	{
		WriteDecoder(0xff, 0x01);
		Wait_ms(5);
	 	//WriteDecoder(0x82, 0x0c);
	 	WriteDecoder(0x82, 0x01);
		Wait_ms(5);
		WriteDecoder(0xff, 0x00);
	 	}
		break;
	
 	case SOURCE_R:
	val=ReadEEP(EEP_CAMRMode);
	 if(val==0)
	 	{
		WriteDecoder(0xff, 0x01);
		Wait_ms(5);
	 	//WriteDecoder(0x82, 0x0d);
		WriteDecoder(0x82, 0x00);
		Wait_ms(5);
		WriteDecoder(0xff, 0x00);


	 	}
	 else	
	 	{
		WriteDecoder(0xff, 0x01);
		Wait_ms(5);
	 	//WriteDecoder(0x82, 0x0c);
		WriteDecoder(0x82, 0x01);
		Wait_ms(5);
		WriteDecoder(0xff, 0x00);

	 	}
		break;
	 
  	case SOURCE_AV:
		WriteDecoder(0xff, 0x01);
		Wait_ms(5);
	 	//WriteDecoder(0x82, 0x0c);
	 	WriteDecoder(0x82, 0x01);
		Wait_ms(5);
		WriteDecoder(0xff, 0x00);
		break;
	}
}
#endif

void SetNowMode(void)
{
	BYTE val;
    Printf("\r\n[MSG]SetNowMode()=> NowModeState=%02x",(WORD)NowModeState);
	if(NowModeState==SelectMode)
	{
	#ifdef QUAD
   	 	TW2835Cmd("\n\rmode 0\n\r");
	 	SetSourceMode(SelectModeType,Attr_A,Attr_B,Attr_C,Attr_R); 
	#else
	 	CheckSourceMode(SelectModeType);
	#endif
	 	SEQFlag=0;
	}
	else
	{
		val=ReadEEP(EEP_JUMPMode);
	#ifdef QUAD 
		if(val==0x01)
	 		TW2835Cmd("\n\rmode 2\n\r");
		else
			TW2835Cmd("\n\rmode 1\n\r");
		
	    SetSourceMode(JumpTable[val],Attr_A,Attr_B,Attr_C,Attr_R);
	#else
	 	CheckSourceMode(JumpTable_S[val]);
	#endif
	}   	
}

void SetRearSource(void)
{ 
	#ifdef AWT_ML072Q
  BYTE rev;
	#endif
#ifdef QUAD
   rev=ReadEEP(EEP_RearMode);
   SetSourceMode(RearTable[rev],0x02|(Attr_A&0x01),0x02|(Attr_B&0x01),0x02|(Attr_C&0x01),0x0E|(Attr_R&0x01));
#else
	ChangeInput(SOURCE_R); 
#endif

//	Printf("\r\n[MSG]SetRearSource() => ReverseModeFlag=%bx ,RearTable[rev]=%bx",ReverseModeFlag,RearTable[rev]);  //pinchi test

#ifdef AWT_ML072Q
	if(ReverseModeFlag==1 && RearTable[rev]==CAM_R)
#else
		  #ifdef HTRV  //Pinchi 20150827 change condition for HTRV
			if (RearTable[rev] == CAM_R)
		  #else
			if(ReverseModeFlag==1)
		  #endif
#endif
	{
	#ifdef QUAD  //Pinchi 20150827 add
	  #ifdef HTRV_SUPPORT_4_3_SCREEN  //Pinchi 20151209 add
		#ifdef HTRV_REDUCE_SCREEN_CHANGE  //Pinchi 20150828 add
		if (ReadDecoder(0x66) == 0x00)
		#endif
	  	{
			WriteDecoder(0x0a,0x13); 
			WriteDecoder(0x61,0xa6);
			WriteDecoder(0x66,0x60);//<William-960905>  
		//	Printf("\r\n[MSG]SetRearSource() => Reverse trigger to 4:3 & ReadDecoder(0x0a)=%bx , ReadDecoder(0x66)=%bx",ReadDecoder(0x0a),ReadDecoder(0x66));  //pinchi test
		}
	  #endif

	  #ifdef AWT_SUPPORT_4_3_SCREEN//Pinchi 20151209 add
		if (ReadDecoder(0x66) == 0x00)
	  	{
			WriteDecoder(0x0a,0x13); 
			WriteDecoder(0x61,0xa6);
			WriteDecoder(0x66,0x60);//<William-960905>  
		//	Printf("\r\n[MSG]SetRearSource() => Reverse trigger to 4:3 & ReadDecoder(0x0a)=%bx , ReadDecoder(0x66)=%bx",ReadDecoder(0x0a),ReadDecoder(0x66));  //pinchi test
		}
	  #endif



	  
	  Printf("\r\n[MSG]SetRearSource() => Reverse trigger & keep 16:9 ,ReadDecoder(0x66)=%bx",ReadDecoder(0x66));  //pinchi test
	#else

#if 1//ryan@20180122
		if(InitVideoDataSrc==PAL)
			{
			WriteDecoder(0x61,0xa2);
			WriteDecoder(0x66,0x5A);
			WriteDecoder(0xB5,0x45);
			}
		else
			{		
		WriteDecoder(0x0a,0x13); 
		WriteDecoder(0x61,0xa9);
		WriteDecoder(0x66,0x50);
		WriteDecoder(0xB5,0x1A);
			}
#else
		WriteDecoder(0x0a,0x13); 
		WriteDecoder(0x61,0xac);
		WriteDecoder(0x66,0x60);//<William-960905>  
#endif
			//WriteDecoder(0x66,0x50);
	
	#endif
	}

#if 1  //Pinchi add   
   if( ReadEEP(EEP_GAUGEMode)==0 && ReadEEP(EEP_RearMode)==0)
  	  DisplayGaugeOSD();
#endif 
}

void SetLeftSource(void)
{
#ifdef QUAD	
    BYTE rev;

	#ifdef AWT_ML072Q
	    rev=ReadEEP(EEP_IMAGE_A_Mode);
	#else
	    rev=ReadEEP(EEP_IMAGEMode);
	#endif
	    SetSourceMode(LeftTable[rev],0x06|(Attr_A&0x01),0x02|(Attr_B&0x01),0x02|(Attr_C&0x01),0x02|(Attr_R&0x01));
#else
	ChangeInput(SOURCE_A); 
#endif
}

void SetRightSource(void)
{
#ifdef QUAD
    BYTE rev;
	#ifdef AWT_ML072Q
   		rev=ReadEEP(EEP_IMAGE_B_Mode);
	#else
    	rev=ReadEEP(EEP_IMAGEMode);
	#endif
    	SetSourceMode(RightTable[rev],0x02|(Attr_A&0x01),0x0A|(Attr_B&0x01),0x02|(Attr_C&0x01),0x02|(Attr_R&0x01));
#else
	ChangeInput(SOURCE_B); 
#endif
}

#ifdef AWT_ML072Q  //Pinchi 20150826 add
void SetTriggerCSource(void)
{
    BYTE rev;
	rev=ReadEEP(EEP_IMAGE_C_Mode);
#ifdef AWT_ML072Q

	  Wait_ms(500);///延遲顯示 ryan@20171019

//  #if 1  //Pinchi 20140925 modify for trigger C setting of AWT ML072Q
  #ifdef AWT_TW2835_DRAW_T_ICON  //Pinchi 20150415 add to draw T icon by TW2835 when CAM C trigger
 //   SetSourceMode(TriggerC_Table[rev],0x02|(Attr_A&0x01),0x0A|(Attr_B&0x01),0x02|(Attr_C&0x01),0x02|(Attr_R&0x01));
    SetSourceMode(TriggerC_Table[rev],0x02|(Attr_A&0x01),0x02|(Attr_B&0x01),0x22|(Attr_C&0x01),0x02|(Attr_R&0x01));
  #else
    SetSourceMode(TriggerC_Table[rev],0x02|(Attr_A&0x01),0x02|(Attr_B&0x01),0x02|(Attr_C&0x01),0x02|(Attr_R&0x01));

	//Pinchi 20140925 add for trigger C display char of AWT ML072Q 
	ClearOSDInfo();
	InitOSDWindow(Init_Osd_DisplayInput_M);

	ClearDataCnt(INPUTINFO_ADDR , 4); // Total 42 Char.
	SetDisplayedOSD(INPUTINFO);
	DrawAttrCnt(INPUTINFO_ADDR , Trigger_COLOR , 4 );  
	WriteStringToAddr(INPUTINFO_ADDR ,"T" , 1); 

    ShowOSDWindow(INPUTINFO_OSDWIN-1 , TRUE);
    ShowOSDWindowAll(1);  //0x09c  第4bit : OSD ON, 1: OSD OFF
    WriteTW88(TW88_WINBLENDING,0x08);
  #endif
#else
    SetSourceMode(CAM_C,Attr_A,Attr_B,Attr_C,Attr_R);
#endif
}
#endif

#ifdef SUPPORT_NEW_TRIGGER_FUNCTION

BYTE CheckTrigger(void)
{
BYTE TriggerFlagtemp;

#ifdef HS
static BYTE /*PT=0,POT=0,POTF=0,*/CPON=0,PPON=0/*,BT[4]={0,0,0,0}*/;
BYTE x;

TriggerFlagtemp=TriggerFlag;
  	TriggerFlag=0x00;

 LEFT_T=1;
   if(LEFT_T==0)
   {
      Wait_ms(2);
	  if(LEFT_T==0)
	  	TriggerFlag=TriggerFlag|0x80;   
   }

   Right_T=1;
   if(Right_T==0)
   {
      Wait_ms(2);
	  if(Right_T==0)
	  	TriggerFlag=TriggerFlag|0x40;  
   }

   REVERSE_T=1;
   if(REVERSE_T==0)
   {
      Wait_ms(2);
	  if(REVERSE_T==0)
	  	TriggerFlag=TriggerFlag|0x20;  
   }
   
   if(PARK_T==1)
   	{
   	   Wait_ms(2);
	      if(PARK_T==1)
	  	TriggerFlag=TriggerFlag|0x01;  
   	}

if((TriggerFlag&(~0x01))!=TriggerFlagtemp)
{

					if((TriggerFlag!=CPON))//got left trigger
					{
						Wait_ms(50);

						TriggerFlag=0;
						
						 LEFT_T=1;
						   if(LEFT_T==0)
						   {
							  Wait_ms(2);
							  if(LEFT_T==0)
								TriggerFlag=TriggerFlag|0x80;  
						   }


						  Right_T=1;
						   if(Right_T==0)
						   {
							  Wait_ms(2);
							  if(Right_T==0)
								TriggerFlag=TriggerFlag|0x40;  
						   }
  					
					   REVERSE_T=1;
					   if(REVERSE_T==0)
					   {
						  Wait_ms(2);
						  if(REVERSE_T==0)
							TriggerFlag=TriggerFlag|0x20;  
					   }

					   
						}
						else
							{
							TriggerFlag=PPON;
							return PPON;
							}
						
				CPON=TriggerFlag;

				x=(TriggerFlag&0xE0);

				 if(TriggerFlag&0x20)//rear
				{
					;
				}
				 //else if(((x==0x88)||(x==0x48)||(x==0xc8)||(x==0xc0))&&((TriggerFlagtemp)==0))
			 	 else if((x==0xc0)&&(TriggerFlagtemp==0))
				{
				PPON=0x00;
				TriggerFlag=0x00;
				return 0x00;
				}
			else if((x==0xA0)||(x==0x60)||(x==0xE0)||(x==0xC0))
			{
				TriggerFlag=TriggerFlagtemp;
				PPON=TriggerFlagtemp;
				
			}
			
}

			if(PARK_T==0)
			 TriggerFlag=TriggerFlag&(~0x01);  
			 
			  if(TriggerFlag&0x01==0x01)
				{
				 ParkFlag=1;
				}
				else
				   ParkFlag=0;

#else
       TriggerFlag=0x00;


  LEFT_T=1;
   REVERSE_T=1;
    PARK_T=1;
      

   if(LEFT_T==0)
	  	TriggerFlag=TriggerFlag|0x80;   

   if(REVERSE_T==0)
	  	TriggerFlag=TriggerFlag|0x20;  

   if(PARK_T==1)
	  	TriggerFlag=TriggerFlag|0x01;  

TriggerFlagtemp=TriggerFlag;

Wait_ms(2);

   if(LEFT_T==1)
	  	TriggerFlag=TriggerFlag&(~0x80);   

   if(REVERSE_T==1)
	  	TriggerFlag=TriggerFlag&(~0x20);  


   if(PARK_T==0)
	  	TriggerFlag=TriggerFlag&(~0x01);  

		 if(TriggerFlag&0x01==0x01)
		   {
		  	ParkFlag=1;
		   }
		   else
			  ParkFlag=0;

#endif

TriggerFlag&=0xfe;///clear PARK trigger

  
     
	  
return TriggerFlag;
   
}


#else 

BYTE CheckTrigger(void)
{
	BYTE TriggerFlagtemp;
#ifdef AWT_ML072S
static BYTE PT=0,POT=0,POTF=0/*,CPON=0,PPON=0,BT[4]={0,0,0,0}*/;
/*BYTE x;*/
	#else	
static BYTE PT=0,POT=0,POTF=0,CPON=0,PPON=0,BT[4]={0,0,0,0};
BYTE x;
#endif
#ifdef AWT_ADD_TRIGGER_DELAY_FUN  //Pinchi 20150210 add
//   BYTE j , num;
#endif



#ifdef AWT_ML720Q_NEW_TRIGGER_FUN  //Pinchi 20141031 add for AWT request each trigger can work by PRIORITY OFF
//	CheckNewTriggerFunc();
#endif

	TriggerFlagtemp=TriggerFlag;
   	TriggerFlag=0x00;

   LEFT_T=1;
   if(LEFT_T==0)
   {
//   	Printf("\r\nTriggerFlag=%02x",(WORD)TriggerFlag);
      Wait_ms(2);
	  if(LEFT_T==0)
	  	TriggerFlag=TriggerFlag|0x80;   
   }

#ifdef AWT_ML072Q
   Right_T=1;
   if(Right_T==0)
   {
      Wait_ms(2);
	  if(Right_T==0)
	  	TriggerFlag=TriggerFlag|0x40;  
   }
#endif

   REVERSE_T=1;
   if(REVERSE_T==0)
   {
      Wait_ms(2);
	  if(REVERSE_T==0)
	  	TriggerFlag=TriggerFlag|0x20;  
   }

#ifndef AWT_ML072Q
   		    PARK_T=1;
		   if(PARK_T==1)
		   {
		      Wait_ms(2);
			  if(PARK_T==1)
			  	ParkFlag=1;
			 //Printf("\r\nTriggerPARK_T",0); 
		   }
		   else
		   	{
		   	 ParkFlag=0;
		   	}

#endif
   
#if 0
   VGA_T=1;
   if(VGA_T==0)
   {
      Wait_ms(10);
	  if(VGA_T==0)
	  	TriggerFlag=TriggerFlag|0x08;  
   }

    CAMD_T=1;
   if(CAMD_T==0)
   {
      Wait_ms(10);
	  if(CAMD_T==0)
	  	TriggerFlag=TriggerFlag|0x04;  
   }
#endif

//#ifndef QUAD
#ifdef AWT_ML072Q  //Pinchi 20140902 add to change condition for AWT ML072Q

   CAMC_T=1;
   if(CAMC_T==0)
   {
      Wait_ms(2);
	  if(CAMC_T==0)
	  	TriggerFlag=TriggerFlag|0x08;  
   }
#endif




      #ifdef AWT_ADD_TRIGGER_DELAY_FUN  //Pinchi 20150206 add for AWT request each trigger can setup trigger delay
	      if (Priority == 0)
	      {
              bLastTrigger = 3;
	      }
       #endif			


#ifdef AWT_ML072Q
	  	if(TriggerFlag!=TriggerFlagtemp)
  	 	{
	 							
			if(Priority==0)
			{///priority on

		#ifdef Trigger_debug				
		Printf("\r\nTriggerFlag=%02x  TriggerFlagtemp=%02x  CPON=%02x",(WORD)TriggerFlag,(WORD)TriggerFlagtemp,(WORD)CPON);
		#else
	//	Printf("\r\nTriggerFlag=%02x",(WORD)TriggerFlag);
		#endif				
							////左右C一起的trigger 

							if((TriggerFlag!=CPON))//got left trigger
							{
								Wait_ms(50);

								TriggerFlag=0;
								
								 LEFT_T=1;
								   if(LEFT_T==0)
								   {
								      Wait_ms(2);
									  if(LEFT_T==0)
									  	TriggerFlag=TriggerFlag|0x80;  
								   }


								  Right_T=1;
								   if(Right_T==0)
								   {
								      Wait_ms(2);
									  if(Right_T==0)
									  	TriggerFlag=TriggerFlag|0x40;  
								   }
							#ifdef AWT_ML072Q//20171204
								 CAMC_T=1;
								if(CAMC_T==0)
								   {
							      Wait_ms(2);
	  							if(CAMC_T==0)
							  	TriggerFlag=TriggerFlag|0x08;  
   								}
							#endif
							
							   REVERSE_T=1;
							   if(REVERSE_T==0)
							   {
							      Wait_ms(2);
								  if(REVERSE_T==0)
								  	TriggerFlag=TriggerFlag|0x20;  
							   }
								}
								else
									{
									TriggerFlag=PPON;
									return PPON;
									}
								
						CPON=TriggerFlag;

						x=(TriggerFlag&0xc8);

						 if(TriggerFlag&0x20)//rear
						{
							;
						}
						 else if(((x==0x88)||(x==0x48)||(x==0xc8)||(x==0xc0))&&((TriggerFlagtemp)==0))
						{
						PPON=0x00;
						TriggerFlag=0x00;
						return 0x00;
						}
					else if((x==0x88)||(x==0x48)||(x==0xc8)||(x==0xc0))
					{
						TriggerFlag=TriggerFlagtemp;
						PPON=TriggerFlagtemp;
						
					}
					
	
			}
			else
			{	
			///priority off
		
	PT=TriggerFlag&(~TriggerFlagtemp);
	
					if(PT==0)
					{
					#ifdef Trigger_debug
					Printf("\r\n(PT=0)");
					#endif
					PT=TriggerFlag;		
					}

			if(PT==0)
				{
				BT[0]=0;
				BT[1]=0;
				BT[2]=0;
				BT[3]=0;
				#ifdef Trigger_debug
				Printf("\r\n(CLR)");
				#endif
				}
			else
				{
						 if(BT[3]&PT)
						{
						PT=PT&BT[3];	
						#ifdef Trigger_debug
						Printf("\r\n(D2)");
						#endif
	
						}
						 else if(BT[2]&PT)
						{
						PT=PT&BT[2];	
							if((BT[3]&TriggerFlag))
							{
							BT[2]=BT[3];
							BT[3]=PT;
							}
							else
								{
								BT[3]=0;
								}
						
						#ifdef Trigger_debug
						Printf("\r\n(C2)");
						#endif
						
						}
						else if(BT[1]&PT)
						{
						PT=PT&BT[1];	
							if((BT[3]&TriggerFlag))
							{
							BT[2]=BT[3];
							BT[1]=BT[2];
							BT[3]=PT;
							}
							else if((BT[2]&TriggerFlag))
							{
							BT[3]=0;
							BT[1]=BT[2];
							BT[2]=PT;
							}
							else
								{
							BT[3]=0;
							BT[2]=0;
								}
							
						#ifdef Trigger_debug
						Printf("\r\n(B2)");
						#endif
								
						}
						else if(BT[0]&PT)
							{
							PT=PT&BT[0];	
							if((BT[3]&TriggerFlag))
							{
							BT[2]=BT[3];
							BT[1]=BT[2];							
							BT[0]=BT[1];
							BT[3]=PT;
							}
							else if((BT[2]&TriggerFlag))
							{
							BT[3]=0;
							
							BT[1]=BT[2];
							BT[0]=BT[1];
							BT[2]=PT;
							}
							else if((BT[1]&TriggerFlag))
							{
							BT[3]=0;
							BT[2]=0;
							
							BT[0]=BT[1];
							BT[1]=PT;
							}
							else
								{
							BT[3]=0;
							BT[2]=0;
							BT[1]=0;							
								}

								#ifdef Trigger_debug
								Printf("\r\n(A2)");
								#endif
							}
					 	else if(BT[0]==0)
						{
						BT[0]=PT;
						#ifdef Trigger_debug
						Printf("\r\n(A)");
						#endif
						}
						else if(BT[1]==0)
						{
						BT[1]=PT;
						#ifdef Trigger_debug
						Printf("\r\n(B)");
						#endif
						}
						else if(BT[2]==0)
						{
						BT[2]=PT;	
						#ifdef Trigger_debug
						Printf("\r\n(C)");
						#endif
						}
						else if(BT[3]==0)
						{
						BT[3]=PT;	
						#ifdef Trigger_debug
						Printf("\r\n(D)");
						#endif
						}

							for(x=0;x<4;x++)//clear no trigger
								if((BT[x]&TriggerFlag)==0)
									{
										BT[x]=0;	
										
										if(x==0)
											{
											BT[0]=BT[1];
											BT[1]=BT[2];
											BT[2]=BT[3];
											BT[3]=0;
											}
										else if(x==1)
											{
											BT[1]=BT[2];
											BT[2]=BT[3];
											BT[3]=0;
											}
										else if(x==2)
											{
											BT[2]=BT[3];
											BT[3]=0;
											}
									}
					}
			

if((PowerFlag==0))///power off狀態
{
						////左右C一起的trigger 
							if(TriggerFlag&0xc8)//got left trigger
							{
								Wait_ms(50);

								 LEFT_T=1;
								   if(LEFT_T==0)
								   {
								      Wait_ms(2);
									  if(LEFT_T==0)
									  	TriggerFlag=TriggerFlag|0x80;  
								   }


								  Right_T=1;
								   if(Right_T==0)
								   {
								      Wait_ms(2);
									  if(Right_T==0)
									  	TriggerFlag=TriggerFlag|0x40;  
								   }
			#ifdef AWT_ML072Q//20171204
								 CAMC_T=1;
								if(CAMC_T==0)
								   {
							      Wait_ms(2);
	  							if(CAMC_T==0)
							  	TriggerFlag=TriggerFlag|0x08;  
   								}
				#endif
								/*
							   REVERSE_T=1;
							   if(REVERSE_T==0)
							   {
							      Wait_ms(2);
								  if(REVERSE_T==0)
								  	TriggerFlag=TriggerFlag|0x20;  
							   }
   								*/
								  // #ifdef Trigger_debug
								 //  Printf("\r\n(*R)");
								  // #endif
							}
				
						x=(TriggerFlag&0xe8);

	//Printf("\r\n(EE x=%02x POTF=%02x)",(WORD)x,(WORD)POTF);						

						if(x==0)
						POTF=0;
						
						if(TriggerFlag&0x20)
						 {
						 //	if(x&0xc8)
						//	POTF=1;

							POT=0x20;
						 }
						else if(POTF==1)
							{
							;
							}
						else if((x==0x88)||(x==0x48)||(x==0xc8)||(x==0xc0)||(x==0))
						{
						POT=0x00;
	
						}
						else
							{
							POTF=1;
							POT=PT;
							}
					

}



#ifdef Trigger_debug			
Printf("\r\nTriggerFlag=%02x  TriggerFlagtemp=%02x  PT=%02x Priority=%02x",(WORD)TriggerFlag,(WORD)TriggerFlagtemp,(WORD)PT,(WORD)Priority);
#else
//Printf("\r\nTriggerFlag=%02x",(WORD)TriggerFlag);
#endif
}


			
		}
#endif
      //_Anderson_20140425_Modify_xx_B 	   
//	  if((LEFT_T == 0)&&(Right_T==0)&&(REVERSE_T==1))
//	   TriggerFlag = 0x00;

//return TriggerFlag;

			
			if(Priority==0)
			{///priority on
			return TriggerFlag;
			}
			else if((PowerFlag==0)&&(POTF==0))	return POT;
			else
				{
				//if(POT==0x20)
				//	{
				//	POT=0;
				//	return 0x20;
				//	}
				//else
				return PT;
				}




			
}

#endif

void TriggerHandler(BYTE T_Flag)
{

#if (defined AWT_ML072Q) || (defined AWT_ML072S) || (defined SUPPORT_ML84TQ_TRIGGER_DELAY)  //Pinchi 20160126 add
	BYTE i;
#endif
	BYTE ReverseMask,LeftMask,RightMask,CamCMask,CamDMask,VGAMask;
//#ifdef HTRV  //Pinchi 20150908 change condition for HTRV  //Pinchi 20140918 add for AWT ML072Q
#ifdef  SUPPORT_ML84TQ_TRIGGER_DELAY  //Pinchi 20150825 add for function define
	BYTE delaytrigger,j;
#endif

#ifdef  AWT_ADD_TRIGGER_DELAY_FUN  //ryan@20170907
	BYTE delaytrigger,j,CTri=TriggerMode;
#endif



#ifdef TW8816

	if(Priority==0)
	{///priority on
		ReverseMask=0x00;
		LeftMask=0x00;
		RightMask=0x00;
		CamCMask=0x00;//0xEA;
		CamDMask=0xE8;//0xEC;
		VGAMask=0x20;//0xE6;
	}
	else
	{
		///priority off
		ReverseMask=0x00;
		LeftMask=0x00;
		RightMask=0x00;
		CamCMask=0x00;//0xCA;
		
		CamDMask=0xC4;//0xCC;
		VGAMask=0xC6;
	}
#else
	if(Priority==0)
	{
		ReverseMask=0x00;
		LeftMask=0x66;
		RightMask=0xA6;
		CamCMask=0xE4;//0xEA;
		CamDMask=0xE8;//0xEC;
		VGAMask=0x20;//0xE6;
	}
	else
	{
		ReverseMask=0xC0;
		LeftMask=0x40;
		RightMask=0x80;
		CamCMask=0xC2;//0xCA;
		CamDMask=0xC4;//0xCC;
		VGAMask=0xC6;
	}
#endif

     if((T_Flag&0x20)!= 0 && (T_Flag&ReverseMask)==0) //RearMode
  	 {
         if(TriggerMode!=REVERSE_TRIG)
         {
         #ifdef SUPPORT_TRIGGER_EXIT_MENU  //Pinchi 20150827 add
           #if 0  //Pinchi 20151209 disable //def HTRV  //Pinchi 20150831 add
            if (GaugeSetup || (GetDisplayedOSD() & MENU))
           #else
            if (GetDisplayedOSD() & MENU)
           #endif
            {
                ClearOSDInfo();
                InitOSDMenu();
                Change_OSDColorLookup();
            #if 0  //Pinchi 20151209 disable //def HTRV  //Pinchi 20150831 add
                GaugeSetup = 0;
            #endif
            }
         #endif
		 #ifdef SUPPORT_AC_ON_REDUCE_TIME  //Pinchi 20150903 add
			if (IsFirstRunfromAC == 1)
			{
				IsFirstRunfromAC = 0;
			//	Printf("\r\n[MSG]TriggerHandler() => AC On 1st time do CAM Trigger"); //pinchi test
			}
		 #endif

          	Printf("\r\nREVERSE_TRIG\n",0);
  		    TriggerMode=REVERSE_TRIG;
  		    SetRearSource();
  		    TriggerStatus=4;
		////   Hs_DvrTxCmdPaser(SendAlarm);
         }
		 return;
     }

 
	 if((T_Flag&0x80)!=0 && (T_Flag&LeftMask)==0)
	 {
         if(TriggerMode!=LEFT_TRIG)
         {
         #ifdef SUPPORT_TRIGGER_EXIT_MENU  //Pinchi 20150827 add
           #if 0  //Pinchi 20151209 disable //def HTRV  //Pinchi 20150831 add
            if (GaugeSetup || (GetDisplayedOSD() & MENU))
           #else
            if (GetDisplayedOSD() & MENU)
           #endif
            {
                ClearOSDInfo();
                InitOSDMenu();
                Change_OSDColorLookup();
            #if 0  //Pinchi 20151209 disable //def HTRV  //Pinchi 20150831 add
                GaugeSetup = 0;
            #endif
            }
         #endif
		 #ifdef SUPPORT_AC_ON_REDUCE_TIME  //Pinchi 20150903 add
			if (IsFirstRunfromAC == 1)
			{
				IsFirstRunfromAC = 0;
			//	Printf("\r\n[MSG]TriggerHandler() => AC On 1st time do CAM Trigger"); //pinchi test
			}
		 #endif
            Printf("\r\nLEFT_TRIG\n",0);
            ClearGAUGEINFO();
	        TriggerMode=LEFT_TRIG;    
            SetLeftSource();	
			TriggerStatus=1;
		#ifdef AWT_ML072S//ryan@20170907
		//Printf("\r\n[MSG]SetSourceMode() => CAM to 16:9");  //pinchi test
		if(InitVideoDataSrc!=PAL)
		WriteDecoder(0x0a,0x26); ///_FULLPANEL_20140313_xx
		//WriteDecoder(0x61,(0x80|ReadDecoder(0x61))-1);
		WriteDecoder(0x61,0x80);//ryan@20180122
		WriteDecoder(0x66,0x00);
		 #endif	
			
		////    Hs_DvrTxCmdPaser(SendAlarm);	
		 }
		 return;
	 }

	 if((T_Flag&0x40)!=0 &&(T_Flag&RightMask)==0)
	 {
         if(TriggerMode!=RIGHT_TRIG)
         {
         #ifdef SUPPORT_TRIGGER_EXIT_MENU  //Pinchi 20150827 add
           #if 0  //Pinchi 20151209 disable //def HTRV  //Pinchi 20150831 add
            if (GaugeSetup || (GetDisplayedOSD() & MENU))
           #else
            if (GetDisplayedOSD() & MENU)
           #endif
            {
                ClearOSDInfo();
                InitOSDMenu();
                Change_OSDColorLookup();
            #if 0  //Pinchi 20151209 disable //def HTRV  //Pinchi 20150831 add
                GaugeSetup = 0;
            #endif
            }
         #endif
		 #ifdef SUPPORT_AC_ON_REDUCE_TIME  //Pinchi 20150903 add
			if (IsFirstRunfromAC == 1)
			{
				IsFirstRunfromAC = 0;
			//	Printf("\r\n[MSG]TriggerHandler() => AC On 1st time do CAM Trigger"); //pinchi test
			}
		 #endif

            Printf("\r\nRIGHT_TRIG\n",0);
            ClearGAUGEINFO();
            TriggerMode=RIGHT_TRIG;
			SetRightSource();
			TriggerStatus=2;
		#ifdef AWT_ML072S//ryan@20170907
		//Printf("\r\n[MSG]SetSourceMode() => CAM to 16:9");  //pinchi test
		if(InitVideoDataSrc!=PAL)
		WriteDecoder(0x0a,0x26); ///_FULLPANEL_20140313_xx
		WriteDecoder(0x61,0x80);
		WriteDecoder(0x66,0x00);
		 #endif	
		////    Hs_DvrTxCmdPaser(SendAlarm);
		 }
         return;
	 }     

	#ifdef AWT_ML072Q  //Pinchi 20150826 add
	 if((T_Flag&0x08)!=0&& (T_Flag&CamCMask)==0)
	 {
         if(TriggerMode!=CAMC_TRIG)
         {
         #ifdef SUPPORT_TRIGGER_EXIT_MENU  //Pinchi 20150827 add
            if (GetDisplayedOSD() & MENU)
            {
                ClearOSDInfo();
                InitOSDMenu();
                Change_OSDColorLookup();
            }
         #endif
		 #ifdef SUPPORT_AC_ON_REDUCE_TIME  //Pinchi 20150903 add
			if (IsFirstRunfromAC == 1)
			{
				IsFirstRunfromAC = 0;
			//	Printf("\r\n[MSG]TriggerHandler() => AC On 1st time do CAM Trigger"); //pinchi test
			}
		 #endif

            Printf("\r\nCAMC_TRIG\n",0);
            ClearGAUGEINFO();
            TriggerMode=CAMC_TRIG;
            TW2835Cmd("\n\rmode 0\n\r");
			SetTriggerCSource();
			//SetSourceMode(CAM_C,Attr_A,Attr_B,Attr_C,Attr_R);
			TriggerStatus=3;
		#ifdef AWT_ML072S//ryan@20170907
		//Printf("\r\n[MSG]SetSourceMode() => CAM to 16:9");  //pinchi test
		if(InitVideoDataSrc!=PAL)
		WriteDecoder(0x0a,0x16); ///_FULLPANEL_20140313_xx
		WriteDecoder(0x61,0x80);
		WriteDecoder(0x66,0x00);
		 #endif	
		 //// 	Hs_DvrTxCmdPaser(SendAlarm);
		 }
         return;
	 }
	#endif
	   
	#ifdef USE_CAMD	  
	   if((T_Flag&0x04)!=0 && (T_Flag&CamDMask)==0)
	   {
           if(TriggerMode!=CAMD_TRIG)
           {
               Printf("\r\nCAMD_TRIG\n",0);
               ClearGAUGEINFO();
               TriggerMode=CAMD_TRIG;
			   SetSourceMode(CAM_D,Attr_A,Attr_B,Attr_C,Attr_R);
		   }
            return;
	   }
	#endif

	#if 0
	if(ReadEEP(EEP_TriggerVGA)==0)
		{
		     if((T_Flag&0x08)!=0 && (T_Flag&VGAMask)==0)
		   	   {
	            if(TriggerMode!=VGA_TRIG)
	              {
	               Printf("\r\nTriggerVGA");
	               ClearGAUGEINFO();
	               TriggerMode=VGA_TRIG;
			 SelectModeType=VGAMode;	   			//WILLIAM-AWT1.2-20110107
				   SetSourceMode(SelectModeType,Attr_A,Attr_B,Attr_C,Attr_R);
			      }
	             return;   
		       }
		}
	#endif

#if 1 //Pinchi 20140904 move from above by compare with ML074Q
	if (TriggerMode != No_TRIG)
	{
		Printf("\r\nNo_TRIG",0);
	
	//	if (PowerFlag)  //Pinchi 20140918 disable for AWT ML072Q
		{
		#if (defined AWT_ML072Q) || (defined AWT_ML072S)  //Pinchi 20150908 add for AWT ML072Q/ML072S  //Pinchi 20140918 add for AWT ML072Q
		//#ifndef  SUPPORT_ML84TQ_TRIGGER_DELAY  //Pinchi 20150825 add for function define	
		  #ifdef SUPPORT_AC_ON_REDUCE_TIME  //Pinchi 20150903 add
			if (IsFirstRunfromAC == 1)
			{
				IsFirstRunfromAC = 0;
			//	Printf("\r\n[MSG]TriggerHandler() => AC On 1st No Trigger & skip delay time"); //pinchi test
			}
			else
		  #endif
		  	{
		  		#ifdef AWT_ADD_TRIGGER_DELAY_FUN //ryan@20170907

						  			switch(TriggerMode)
									{
										case REVERSE_TRIG:	
											delaytrigger=ReadEEP(EEP_CamRDelay);
										break;

										case LEFT_TRIG:	
											delaytrigger=ReadEEP(EEP_CamADelay);
										break;

										case RIGHT_TRIG:	
											delaytrigger=ReadEEP(EEP_CamBDelay);
										break;

									#ifdef AWT_ML072Q  //Pinchi 20150908 add
										case CAMC_TRIG:	
											delaytrigger=ReadEEP(EEP_CamCDelay);
										break;
									#endif
									#ifdef USE_CAMD
										case CAMD_TRIG:	
											delaytrigger=ReadEEP(EEP_DELAYCAMD);
										break;
									#endif	
										case No_TRIG:
										case PARK_TRIG:	
										case VGA_TRIG:	
										default:	
											delaytrigger=0;
										break;	
									}

									#ifdef AWT_ML072S

										if(PowerFlag==1)
										{
											for(j=0;j<delaytrigger;j++) 
											{
													for(i=0;i<(100-20);i++) 
													{
														CheckTrigger();
														if(TriggerFlag!=0)//andy HTRV 980625
														   return;											
														Wait_ms(7);	//william-v1.44a-970923
													}
											}
										}
										else
										{

											for(j=0;j<delaytrigger;j++) 
											{
												for(i=0;i<(100-20-3);i++) 
												{
												CheckTrigger();
												if(TriggerFlag!=0)//andy HTRV 980625
												   return;											
												Wait_ms(7);	//william-v1.44a-970923
												}
											}
										}
									
									#else
									
									for(j=0;j<delaytrigger;j++) 
									{
										for(i=0;i<100;i++) 
										{
											CheckTrigger();
											if(TriggerFlag!=0)//andy HTRV 980625
											   return;
											Wait_ms(7);	//william-v1.44a-970923
										}
									}
									
									#endif

			#ifdef AWT_ML072S
			//Printf("\r\n[MSG]SetSourceMode() => CAM to 16:9");  //pinchi test
			if(TriggerMode==REVERSE_TRIG)
			{
			clrBacklight();
			WriteDecoder(0x0a,0x16); ///_FULLPANEL_20140313_xx
			WriteDecoder(0x61,0x80);
			WriteDecoder(0x66,0x00);
			}
			#endif
									
				#else
				for (i=0 ; i<100 ; i++) 
				{
					CheckTrigger();
					if (TriggerFlag != 0)
						return;

					Wait_ms(14);
				}
				#endif
		  	}
		#else
		
		  #ifdef  SUPPORT_ML84TQ_TRIGGER_DELAY  //Pinchi 20160126 add
			switch(TriggerMode)
			{
				case REVERSE_TRIG:	
					delaytrigger=ReadEEP(EEP_DELAYCAMR);
				break;

				case LEFT_TRIG:	
					delaytrigger=ReadEEP(EEP_DELAYCAMA);
				break;

				case RIGHT_TRIG:	
					delaytrigger=ReadEEP(EEP_DELAYCAMB);
				break;

			#ifdef AWT_ML072Q  //Pinchi 20150908 add
				case CAMC_TRIG:	
					delaytrigger=ReadEEP(EEP_DELAYCAMC);
				break;
			#endif
			#ifdef USE_CAMD
				case CAMD_TRIG:	
					delaytrigger=ReadEEP(EEP_DELAYCAMD);
				break;
			#endif	
				
				case No_TRIG:
				case PARK_TRIG:	
				case VGA_TRIG:	
				default:	
					delaytrigger=0;
				break;	
			}

			for(j=0;j<delaytrigger;j++) 
			{
				for(i=0;i<100;i++) 
				{
					CheckTrigger();
					if(TriggerFlag!=0)//andy HTRV 980625
					   return;
					Wait_ms(4);	//william-v1.44a-970923
				}
			}
		  #endif
		#endif
     	} 
    	TriggerMode=No_TRIG;		 
    	ClearGAUGEINFO();
		
	#ifdef QUAD  //Pinchi 20150903 change condition for common use when enter Standby mode no action  //AWT_ML072Q  //Pinchi 20140922 add for AWT ML072Q
		if (PowerFlag)
	#endif
		{
        #ifdef HTRV  //Pinchi 20151209 add
            if (GaugeSetup == 1)
            {
                GaugeSetup = 0;
                GaugeInfoOSD = 0;  //Pinchi 20151209 add to clear GaugeSetup
                SelectModeType = ReadEEP(EEP_SelectMode);  //Pinchi 20151209 add to restore original cam
            }
        #endif
			#ifdef AWT_ML072S
			#else
			DisplayInput();		//william-20100420
			#endif
		#if 0
		  if(SelectModeType==VGAMode)				//william-awt1.2 20110107
		  	SelectModeType=ReadEEP(EEP_SelectMode);
		#endif

	
if(RELEASE_TR_JUMP_Flag==1) 
{
	TR_JUMP_Flag=0;
	NowModeState=TR_JUMP_HOLD;
	RELEASE_TR_JUMP_Flag=0;
	Printf("\r\n(SelectModeType=%02x    NowModeState=%02x)",(WORD)SelectModeType,(WORD)NowModeState);
}

			IsDrawNoVideoSignal=0;//ryan@20170921
			#ifdef AWT_ML072S
			if (PowerFlag)
				{
				
	if(ParkFlag==0)
	{
		AVFlag=0;
	
						if(SelectModeType==SOURCE_AV)
						{							
										
								 delaytrigger=ReadEEP(EEP_CamCDelay);

								if((CTri==REVERSE_TRIG)||(CTri==LEFT_TRIG))
								delaytrigger=0;			
			
									for(j=0;j<delaytrigger;j++) 
									{
										for(i=0;i<(100-20);i++) 
										{
											CheckTrigger();
											if(TriggerFlag!=0)
											   return;
											else if(ParkFlag==1)
												return;
											
											Wait_ms(7);	
										}
									}							
						SelectModeType=ReadEEP(EEP_SelectMode);
			
						} 
	}

				
				SetNowMode();
				}
			#else
			SetNowMode();
			#endif
		#if 1  //Pinchi 20150901 add to setup 2s for Display OFF
			if (ReadEEP(EEP_COSDMode) == 1)
				displayhold_flag = 3;
		#endif
		}

#if 0  //Pinchi 20150827 disable for wrong action
	#ifdef AWT_ML072Q
		if(ReadDecoder(0x0a)==0x13)
		{
			WriteDecoder(0x0a,0x1b);
			WriteDecoder(0x61,0x80);
			WriteDecoder(0x66,0x00);
			Printf("\r\n[MSG]TriggerHandler() => TriggerMode=No_TRIG 4:3 to 16:9 !!");  //pinchi test
		}
	#else
		if(ReadDecoder(0x0a)==0x13)
	    {
			WriteDecoder(0x0a,0x0f); 
			WriteDecoder(0x61,0x88);
			WriteDecoder(0x66,0x00);//<William-960905>  
	    }
	#endif
#endif
	}
#endif




#ifndef AWT_ML072Q			//william @20130813
	if(ParkFlag==0)
	{
		AVFlag=0;
	#ifdef QUAD	
		if(SelectModeType==AVMode)
	#else
		if(SelectModeType==SOURCE_AV)
	#endif
		{
								#ifdef AWT_ML072S///add by  ryan@20171214

								#ifdef Hs_debug
								Printf("\r\n***delay AV trigger release");
								#endif
										
								 delaytrigger=ReadEEP(EEP_CamCDelay);

								if((CTri==REVERSE_TRIG)||(CTri==LEFT_TRIG))
								delaytrigger=0;			
			
									for(j=0;j<delaytrigger;j++) 
									{
										for(i=0;i<(100-20);i++) 
										{
											CheckTrigger();
											if(TriggerFlag!=0)//andy HTRV 980625
											   return;
											else if(ParkFlag==1)
												return;
											
											Wait_ms(7);	//william-v1.44a-970923
										}
									}
								#endif
								
			SelectModeType=ReadEEP(EEP_SelectMode);
			SetNowMode();
		} 
	}

		
#endif

	

}

#if 0
//#else
//============================================================================= 
//                       Trigger偵測控制                                                       
//=============================================================================
//          Bit3     Bit2        Bit1         Bit0
//Attr_x=> Tigger   Tigger     OSD ON/OFF      MH 
void  CheckTrigger()
{
 //  BYTE TComm,TIndex,val;

   if(ReverseFlag  )         //倒車(CkTmode=1)
   {
      if(!(TriggerMode==REVERSE_TRIG))
      { 	
         CkTMode=REVERSE_TRIG;        
         TGFlag1=1; 
	  Gaugeflag=1;		//william-970724
	// ParkIndex1= ParkIndex; 		//william-v1.0-970804
	 ParkIndex=SOURCE_R;	//william-v1.0-970724 
	//ChangeInput(COMPOSITE4); 	 
	CheckSourceMode();

	//william-v1.0-970717>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	
      } 	  
      return;
   }
   else
   {
       if(( RtFlag)&&(!LtFlag))          //右轉(CkTMode=4) ,切換成右轉時設定的畫面模式
       { 
		//william-v1.0-970718>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>		
	  	if(!(CkTMode==LEFT_TRIG))
	  	{
		CkTMode=LEFT_TRIG;
        TGFlag1=1;	
		Gaugeflag=0;
		//ParkIndex1 = ParkIndex;		//william-v1.0-970804 	 
		ParkIndex=SOURCE_A;	//william-v1.0-970724 
		//ChangeInput(COMPOSITE1); 	
		CheckSourceMode();
	  	}
	  	 return; 
      //william-v1.0-970718>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>              return;  
                   }
	 if (ParkTime>10)      //手煞車(CkTMode=6)
              	{
              	
                           if(!(CkTMode==PARK_TRIG))
                             {

  				//    CkTMode=PARK_TRIG;
                                TGFlag1=0;
                                CkPARK=1;
                              }   
              	}  	
	 else
	{
	if(AVFlag)
	{CkTMode=PARK_TRIG;}
   			CkPARK=0;
   			AVFlag=0;
	 }
//#endif
	 if(!(CkTMode==OTHERS_TRIG)/*&&!(CkTMode==PARK_TRIG)*/)  //其他狀態,清除ckpark,tgflag1//<william-961004-ver1.41>	//william-v1.0-970717
     {
		//william-v1.0-970717>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>			
			CkTMode=OTHERS_TRIG;
            		TGFlag1=0; 
			Gaugeflag=0;	//william-v1.0-970724
		//	if((ParkIndex1==SOURCE_A)||(ParkIndex1==SOURCE_B)||(ParkIndex1==SOURCE_R))
			ParkIndex=ParkIndex1; 		//william-v1.0-970724
			//ChangeInput(COMPOSITE3);
           
			if(SEQFlag==1)		//william-v1.1-970818
				CheckJUMPMode();  
			else
				CheckSourceMode();
                   }
		//william-v1.0-970717>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      }
   }
#endif

#ifdef SUPPORT_SDCARD  //Pinchi 20140903 add for AWT ML072Q
void SelectBoxHandler(void)
{
	//BYTE i,j;
	BYTE val;
	//BYTE delaytrigger;
	
	ADCTL=0xEE;
	while((ADCTL&0x10)==1);
	Wait_ms(50);
	val=ADCV;

	#if 1
	//if( SelectBoxADC!=val)
	 // Printf("\r\nADC=%d",(WORD)val);
	  SelectBoxADC=val;
	#endif

	if(val>245)	
	{
        if(SelectBoxMode!=EVENT_SELECT)
          {
           Printf("\r\nEVENT_SELECT",0);
		   SelectBoxMode=EVENT_SELECT;
		    //TriggerMode=No_TRIG;
		   Hs_DvrTxCmdPaser(BOOKMARK);
		   BookMarkState|=0x02;
          }
		return;
	}

	
	if(val>214&&val<234)	
	{
        if(SelectBoxMode!=REVERSE_SELECT)
          {
           Printf("\r\nREVERSE_SELECT",0);
		   SelectBoxMode=REVERSE_SELECT;
		    //TriggerMode=No_TRIG;
		   SetRearSource();
		   TriggerStatus=4;
		   Hs_DvrTxCmdPaser(SendAlarm);
          }
		return;
	}

	
	if(val>168&&val<188)
	{
          if(SelectBoxMode!=LEFT_SELECT)
            {
              Printf("\r\nLEFT_SELECT",0);
            ClearGAUGEINFO();
	     SelectBoxMode=LEFT_SELECT;   
	     //TriggerMode=No_TRIG;
            SetLeftSource();
	     TriggerStatus=1;
	     Hs_DvrTxCmdPaser(SendAlarm);
	     }
		  return;		
	}
	
	
	if(val>111&&val<131)	
	{
         if(SelectBoxMode!=RIGHT_SELECT)
           {
           Printf("\r\nRIGHT_SELECT",0);
            ClearGAUGEINFO();
            SelectBoxMode=RIGHT_SELECT;
	     //TriggerMode=No_TRIG;	
	     SetRightSource();
	     TriggerStatus=2;
	     Hs_DvrTxCmdPaser(SendAlarm);
	     }
         return;
	}

	
	if(val>49&&val<69)	
	{
             if(SelectBoxMode!=CAMC_SELECT)
               {
               Printf("\r\nCAMC_SELECT",0);
                ClearGAUGEINFO();
                SelectBoxMode=CAMC_SELECT;
		  //TriggerMode=No_TRIG;		
                TW2835Cmd("\n\rmode 0\n\r");
		  SetTriggerCSource();
		  TriggerStatus=3;
		  Hs_DvrTxCmdPaser(SendAlarm);
		  }
            return;
	}			
	
	if(val>14&&val<34)
	{
           if(SelectBoxMode!=JUMP_SELECT)
              {
               Printf("\r\nJUMP_SELECT",0);
                ClearGAUGEINFO();
                SelectBoxMode=JUMP_SELECT;
		  //TriggerMode=No_TRIG;
		val=ReadEEP(EEP_JUMPMode);	
		 if(val==0x01)
	 		TW2835Cmd("\n\rmode 2\n\r");
	 	else
     			TW2835Cmd("\n\rmode 1\n\r");
		
		  SetSourceMode(JumpTable[val],Attr_A,Attr_B,Attr_C,Attr_R);		
		 // SelectModeType=ReadEEP(EEP_SelectMode);
	      	  //SetNowMode(); 		
		 // SetSourceMode(CAM_D,Attr_A,Attr_B,Attr_C,Attr_R);
		 }
            return;
	}

	
#if 1
	if((/*val>247||*/val<8)/*&&(TriggerMode==No_TRIG)*/)
	{
	   if(SelectBoxMode!=No_SELECT)
         {
         Printf("\r\nNo_SELECT",0);
#if  0		 
         if(PowerFlag)
         	{
         	switch(SelectBoxMode)
         		{
			case REVERSE_SELECT:	
				delaytrigger=ReadEEP(EEP_DELAYCAMR);
			break;

			case LEFT_SELECT:	
				delaytrigger=ReadEEP(EEP_DELAYCAMA);
			break;

			case RIGHT_SELECT:	
				delaytrigger=ReadEEP(EEP_DELAYCAMB);
			break;

			case CAMC_SELECT:	
				delaytrigger=ReadEEP(EEP_DELAYCAMC);
			break;

			case CAMD_SELECT:	
				delaytrigger=ReadEEP(EEP_DELAYCAMD);
			break;
			
			case No_SELECT:
			//case PARK_TRIG:	
			//case VGA_TRIG:	
			default:	
				delaytrigger=0;
			break;	

			}

		for(j=0;j<delaytrigger;j++) 
		 {
		   for(i=0;i<250;i++) 
			{
			CheckTrigger();
			if(TriggerFlag!=0)//andy HTRV 980625
			   return;	
			   Wait_ms(4);	//william-v1.44a-970923		
			}
		 }
         	} 
		 #endif
		if(SelectBoxMode!=EVENT_SELECT)
			{
		  	
			if (!CheckTrigger())
				{
				SelectModeType=ReadEEP(EEP_SelectMode);
	      	  		SetNowMode();
				ClearGAUGEINFO();
	   			DisplayInput();		//william-201004
				}
			else
				TriggerMode=No_TRIG;
			}
			BookMarkState&=0xFD;
		 	 SelectBoxMode=No_SELECT;	
				
	   	 }
	}
#endif
}
#endif


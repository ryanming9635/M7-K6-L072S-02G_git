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
#include "etc_eep.h"
#include "panel.h"
#include "osdmenu.h"
#include "HS_DisplayOSD.h"
#include "HS_DVRProtocol.h"

//============================================================================= 
//                       倒車車幅線控制                                                       
//=============================================================================

#ifdef TW8816//ryan@20170907

#ifdef AWT_ML072S
	CODE BYTE GaugeString[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,/*0x03,*/0x02,ROMFONT,0}; // 0x31 -> 0x2e  Jusitn 拿掉3M
	CODE BYTE GaugeString1[]= {RAMFONT,0x01,ROMFONT,0};    //....顯示"/-" 
	CODE BYTE GaugeString2[]= {RAMFONT,0x02,ROMFONT,0};    //....顯示"-\"
	CODE BYTE GaugeString3[]= {RAMFONT,0x05,ROMFONT,0};    //....顯示"/"
	CODE BYTE GaugeString4[]= {RAMFONT,0x06,ROMFONT,0};    //....顯示"\"
	CODE BYTE GaugeString5[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,/*0x03,*/0x02,ROMFONT,0};  // 0x30 -> 0x2e  Jusitn 拿掉2M
	CODE BYTE GaugeString6[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x04,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,/*0x03,*/0x02,ROMFONT,0};
	CODE BYTE GaugeString7[]= {RAMFONT,0x01,/*0x03,*/0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x56,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0};
#else
	CODE BYTE GaugeString[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0}; // 0x31 -> 0x2e  Jusitn 拿掉3M
	CODE BYTE GaugeString1[]= {RAMFONT,0x01,ROMFONT,0};    //....顯示"/-" 
	CODE BYTE GaugeString2[]= {RAMFONT,0x02,ROMFONT,0};    //....顯示"-\"
	CODE BYTE GaugeString3[]= {RAMFONT,0x05,ROMFONT,0};    //....顯示"/"
	CODE BYTE GaugeString4[]= {RAMFONT,0x06,ROMFONT,0};    //....顯示"\"
	CODE BYTE GaugeString5[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0};  // 0x30 -> 0x2e  Jusitn 拿掉2M
	CODE BYTE GaugeString6[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x04,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0};
	CODE BYTE GaugeString7[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x56,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0};
#endif
#else
CODE BYTE GaugeString[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0}; // 0x31 -> 0x2e  Jusitn 拿掉3M
CODE BYTE GaugeString1[]= {RAMFONT,0x01,ROMFONT,0};    //....顯示"/-" 
CODE BYTE GaugeString2[]= {RAMFONT,0x02,ROMFONT,0};    //....顯示"-\"
CODE BYTE GaugeString3[]= {RAMFONT,0x05,ROMFONT,0};    //....顯示"/"
CODE BYTE GaugeString4[]= {RAMFONT,0x06,ROMFONT,0};    //....顯示"\"
CODE BYTE GaugeString5[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0};  // 0x30 -> 0x2e  Jusitn 拿掉2M
CODE BYTE GaugeString6[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x04,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0};
CODE BYTE GaugeString7[]= {RAMFONT,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x56,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,ROMFONT,0};
#endif

#ifdef AWT_ML072S
#define GAUGEINFO_ADDR    (0 +34)
extern BYTE vloss_flag;
#else
#define GAUGEINFO_ADDR    0 
#endif

bit Init_DisplayInput=0;

extern BYTE BookMarkState;
extern BYTE	year1,year2,month,day,hour,minute,second;
extern BYTE	DVR_SDCardAvailable		;
extern BYTE	DVR_RecordMode;
extern BYTE	DVR_Resolution;
extern BYTE	DVR_RecordStatus		;
extern BYTE	DVR_Busy				;
extern BYTE DVRVersion[11];
extern BYTE DVRVersionLen;
extern BYTE	DATA DVR_buf[DVR_BUF_MAX];
extern BYTE DisplayedOSD;
extern BYTE GPSState;
extern BYTE FormatSDCard;
extern CODE BYTE Init_Osd_DisplayGAUGEWindow[];               
extern CODE BYTE Init_Osd_DisplayInput[]; 
//extern bit DisplayInputHold;
extern BYTE displayhold_flag;  //Pinchi 20150319 add

 extern BYTE mirror_flag;
//倒車車幅線屬性
CODE BYTE Init_Osd_DisplayGAUGEWindow[] = {
    17,
    OSD_Win_Num             ( BACK_COLOR|RATINGINFO_OSDWIN ),   // 2 bytes
    OSD_Win_Attr            ( WIN_BG_COLOR_EX0 | BACK_COLOR | WIN_3D_TYPE0 | WIN_3D_EN0 | WIN_EN ),
#ifdef TW8816
	#ifdef AWT_ML072S
//	OSD_Win_Start           ( 45-8,67),  // 120->40   24->        
#ifdef HS
OSD_Win_Start           ( 45-8-10+16,67),  // 120->40   24->        
#else
OSD_Win_Start           ( 45-8-10,67),  // 120->40   24->        
#endif
	#else
	OSD_Win_Start           ( 45,60-5),  // 120->40   24->        
    	#endif
#else
    OSD_Win_Start           ( 45,60),  // 120->40   24->               
#endif
    OSD_Win_Width           ( 30 ),
    OSD_Win_Height          ( 5 ),
    OSD_Win_Border          ( WIN_BD_EN | BG_COLOR_WHITE | WIN_BD_WIDTH(0) ),
    OSD_Win_HBorder         ( WIN_BD_COLOR_EX0 | WIN_H_BD_W(0x00) ),
    OSD_Win_VBorder         ( WIN_V_BD_W(0x00) ),
    OSD_Win_CH_Space        ( WIN_CH_HSPACE(0) | WIN_CH_VSPACE(0) ),
    OSD_Win_ZM_SAddr        ( WIN_VZOOM(WINZOOMx4), WIN_HZOOM(WINZOOMx2), WIN_SADDR(RATINGINFO_ADDR) ), // 2 bytes
    OSD_Win_Shadow          ( WIN_SHADOW_EN0 | BACK_COLOR | WIN_SHADOW_W(8) ),//
    OSD_Win_Blending        ( 8 ),
    OSD_Win_CH_BorderShadow ( WIN_SHADOW_COLOR_EX0 | WIN_MULTI_EN | WIN_V_EXT_EN0 
                            | WIN_CH_BDSH_SEL(SEL_BORDER) 
                            | WIN_CH_BDSH_COLOR_EX0 | CH_COLOR_BLACK ),
    0 // End of Data
};

#ifdef HTRV  //Pinchi 20150825 add model #define
extern BYTE GaugeSetup; 
#endif

void DisplayGaugeOSD(void)
#if 0	
{
   BYTE i;
   extern CODE BYTE Init_Osd_DisplayGAUGEWindow[];
  if(GaugeSetup==0)
  	{
   ClearOSDInfo();
   ClearDataCnt(GAUGEINFO_ADDR,30*5);     
   DrawAttrCnt(0,0x00,30*5);  //2007.4.25 解畫倒車線出現藍色區塊//william-v1.43-970403
  InitOSDWindow(Init_Osd_DisplayGAUGEWindow); 
  	}  
  GaugeVStart= ReadEEP(EEP_Gauge_VStart);				  //william-v1.43-970318//andy980710
  WriteDecoder(0xa2,GaugeVStart);		//OSD Win VStart //william-980428 //andy HTRV 980706
  for(i=0;i<150;i++){WriteStringToAddr(i," ",1);}  
			  
   DrawAttrCnt(GAUGEINFO_ADDR,Gauge_COLOR1,30);       
   WriteStringToAddr(GAUGEINFO_ADDR+5,GaugeString,22);
   WriteStringToAddr(GAUGEINFO_ADDR+30+4,GaugeString5,23);

   DrawAttrCnt(GAUGEINFO_ADDR+30,Gauge_COLOR2,60);   
   WriteStringToAddr(GAUGEINFO_ADDR+30*2+3,GaugeString3,3);
   WriteStringToAddr(GAUGEINFO_ADDR+30*2+26,GaugeString4,3);
   WriteStringToAddr(GAUGEINFO_ADDR+30*3+2,GaugeString6,27); 

   DrawAttrCnt(GAUGEINFO_ADDR+30*3,Gauge_COLOR3,60);  
   WriteStringToAddr(GAUGEINFO_ADDR+30*4+1,GaugeString3,3);
   WriteStringToAddr(GAUGEINFO_ADDR+30*4+28,GaugeString4,3);
  
   SetDisplayedOSD(GAUGEINFO);
   ShowOSDWindow(RATINGINFO_OSDWIN,TRUE);
   ShowOSDWindowAll(1);  //0x09c  第4bit : OSD ON, 1: OSD OFF
}
#else
{
   BYTE i;
   //extern CODE BYTE Init_Osd_DisplayGAUGEWindow[];
	
#if 0
   ClearOSDInfo();

   InitOSDWindow(Init_Osd_DisplayGAUGEWindow); 
   ClearDataCnt(GAUGEINFO_ADDR,150);     
   DrawAttrCnt(0,0x00,150);  //2007.4.25 解畫倒車線出現藍色區塊//william-v1.43-970403
#endif

   InitOSDWindow(Init_Osd_DisplayGAUGEWindow); 

#ifdef HTRV  //Pinchi 20140902 add for AWT ML072Q
   GaugeVStart= ReadEEP(EEP_Gauge_VStart);				  //william-v1.43-970318//andy980710
   WriteDecoder(0xa2,GaugeVStart);		//OSD Win VStart //william-980428 //andy HTRV 980706
#endif

	#ifdef AWT_ML072S
   for(i=37;i<150;i++){WriteStringToAddr(i," ",1);}  
	#else
   for(i=0;i<150;i++){WriteStringToAddr(i," ",1);}  
	#endif
	
	#ifdef TW8816

				   #ifdef AWT_ML072S

				   		   DrawAttrCnt(GAUGEINFO_ADDR,Gauge_COLOR1,30);       
						   WriteStringToAddr(GAUGEINFO_ADDR+7+1,GaugeString,18-1);
						   WriteStringToAddr(GAUGEINFO_ADDR+36+1,GaugeString5,19-1);

						   DrawAttrCnt(GAUGEINFO_ADDR+30,Gauge_COLOR2,60);   
						   WriteStringToAddr(GAUGEINFO_ADDR+65+1,GaugeString3,3);
						   WriteStringToAddr(GAUGEINFO_ADDR+84-1+1,GaugeString4,3);
						   
						   if(mirror_flag)  
						   	  WriteStringToAddr(GAUGEINFO_ADDR+94+1,GaugeString6,23-1); ///normal
						   else
						   	  WriteStringToAddr(GAUGEINFO_ADDR+94+1,GaugeString7,23-1); ///mirror

						   DrawAttrCnt(GAUGEINFO_ADDR+90,Gauge_COLOR3,60);  
						   WriteStringToAddr(GAUGEINFO_ADDR+123+1,GaugeString3,3);
						   WriteStringToAddr(GAUGEINFO_ADDR+146-1+1,GaugeString4,3);

				   #else
				   DrawAttrCnt(GAUGEINFO_ADDR,Gauge_COLOR1,30);       
				   WriteStringToAddr(GAUGEINFO_ADDR+5+2,GaugeString,22-4);
				   WriteStringToAddr(GAUGEINFO_ADDR+30+4+2,GaugeString5,23-4);

				   DrawAttrCnt(GAUGEINFO_ADDR+30,Gauge_COLOR2,60);   
				   WriteStringToAddr(GAUGEINFO_ADDR+30*2+3+2,GaugeString3,3);
				   WriteStringToAddr(GAUGEINFO_ADDR+30*2+26-2,GaugeString4,3);
				   
				   if(mirror_flag)  
				   	  WriteStringToAddr(GAUGEINFO_ADDR+30*3+2+2,GaugeString6,27-4); 
				   else
				   	  WriteStringToAddr(GAUGEINFO_ADDR+30*3+2+2,GaugeString7,27-4); 

				   DrawAttrCnt(GAUGEINFO_ADDR+30*3,Gauge_COLOR3,60);  
				   WriteStringToAddr(GAUGEINFO_ADDR+30*4+1+2,GaugeString3,3);
				   WriteStringToAddr(GAUGEINFO_ADDR+30*4+28-2,GaugeString4,3);
   				  #endif
	#else
   DrawAttrCnt(GAUGEINFO_ADDR,Gauge_COLOR1,30);       
   WriteStringToAddr(GAUGEINFO_ADDR+5,GaugeString,22);
   WriteStringToAddr(GAUGEINFO_ADDR+30+4,GaugeString5,23);

   DrawAttrCnt(GAUGEINFO_ADDR+30,Gauge_COLOR2,60);   
   WriteStringToAddr(GAUGEINFO_ADDR+30*2+3,GaugeString3,3);
   WriteStringToAddr(GAUGEINFO_ADDR+30*2+26,GaugeString4,3);
   
   if(mirror_flag)  
   	  WriteStringToAddr(GAUGEINFO_ADDR+30*3+2,GaugeString6,27); 
   else
   	  WriteStringToAddr(GAUGEINFO_ADDR+30*3+2,GaugeString7,27); 

   DrawAttrCnt(GAUGEINFO_ADDR+30*3,Gauge_COLOR3,60);  
   WriteStringToAddr(GAUGEINFO_ADDR+30*4+1,GaugeString3,3);
   WriteStringToAddr(GAUGEINFO_ADDR+30*4+28,GaugeString4,3);
   #endif
   SetDisplayedOSD(GAUGEINFO);


#ifdef AWT_ML072S
//ClearVlossOsd();
ClearDisplayedOSD(VLOSSINFO);
VlossHandler();
#endif

   ShowOSDWindow(RATINGINFO_OSDWIN,TRUE);
   ShowOSDWindowAll(1);  //0x09c  第4bit : OSD ON, 1: OSD OFF
   WriteTW88(TW88_WINBLENDING,0x08);	   //wiliiam-v1.1-970827
}
#endif

void ClearGAUGEINFO(void)
{
	ShowOSDWindow(RATINGINFO_OSDWIN ,FALSE);
	DisplayedOSD &= (~(GAUGEINFO));
}

#ifdef SUPPORT_SDCARD  //Pinchi 20140918 enable for AWT ML072Q
void DisplayNumber(BYTE addr,WORD val,BYTE type)
{
    #define Number_LENGTH 6 
    #define Number_LENGTH2 2
    // BYTE i;
    //WORD addr;
    BYTE Bar_str[Number_LENGTH]={ ' ',' ','.',' ',' ','V' };
	BYTE Bar_str_AC[Number_LENGTH]={ ' ',' ',' ','.',' ','V' };
	BYTE Bar_str_Battery[Number_LENGTH]={ ' ','.',' ',' ',' ','V' };
	BYTE Num_str[Number_LENGTH2]={ ' ',' ' };

	switch(type)
	{
		case 1:
		//if(ModeIndex==MODE_AC)
		//{
		    //if( Bar_str[0] == 0x01 ) Bar_str[0] = 0x02; // |..
		    Bar_str_AC[4] = val % 10 + '0';    val /= 10;
		    Bar_str_AC[2] = val % 10 + '0';    val /= 10;
		    Bar_str_AC[1] =  val % 10 + '0';    val /= 10;
		    Bar_str_AC[0] = val + '0';
		    if( Bar_str_AC[0] == '0' ) Bar_str_AC[0] = ' ';
			if( (Bar_str_AC[1] == '0') && (Bar_str_AC[0] == ' ') ) Bar_str_AC[1] = ' ';
		//}	
			DrawAttrCnt(addr, DEFAULT_COLOR, Number_LENGTH ); 
			WriteStringToAddr(addr, Bar_str_AC, Number_LENGTH );
			break;

		case 2:
		//{
		    Bar_str_Battery[4] = val % 10 + '0';    val /= 10;
		    Bar_str_Battery[3] = val % 10 + '0';    val /= 10;
		    Bar_str_Battery[2] = val % 10 + '0';    val /= 10;
		    Bar_str_Battery[0] = val + '0';
		   // if( Bar_str[0] == '0' ) Bar_str[0] = ' ';
		   DrawAttrCnt(addr, DEFAULT_COLOR, Number_LENGTH ); 
		   WriteStringToAddr(addr, Bar_str_Battery, Number_LENGTH );
		//}
			break;

		case 3:
		//else
		//{
		    // Number
		    Bar_str[4] = val % 10 + '0';    val /= 10;
		    Bar_str[3] = val % 10 + '0';    val /= 10;
		    Bar_str[1] =  val % 10 + '0';    val /= 10;
		    Bar_str[0] = val + '0';
		    if( Bar_str[0] == '0' ) Bar_str[0] = ' ';
			//if( Bar_str[2] == '0' ) Bar_str[0] = ' ';
		//}
			DrawAttrCnt(addr, DEFAULT_COLOR, Number_LENGTH ); 
			WriteStringToAddr(addr, Bar_str, Number_LENGTH );
			break;

		case 4:
			// Number
			Num_str[1] =  val % 10 + '0';	 val /= 10;
			Num_str[0] = val + '0';

			//DrawAttrCnt(addr, DEFAULT_COLOR, Number_LENGTH2 ); 
			WriteStringToAddr(addr, Num_str, Number_LENGTH2 );
			break;
		    //addr = OSDMENU_MAINADDR; // 
	}
}
#endif

void DisplayInformation(BYTE info)  
{
#ifndef QUAD  //Pinchi 20140902 add condition for compiler warning
CODE BYTE Str_LOCK_Mirror[] = {RAMFONT,0x57,0x58,0x5A,0x53,ROMFONT,'O',RAMFONT,0x50,ROMFONT,' ','U',RAMFONT,0x59,0x58,ROMFONT,'M',' ',RAMFONT,0x57,0x55,ROMFONT,'O',0};
CODE BYTE Str_ACTIVE_Mirror[] = {RAMFONT,0x58,ROMFONT,'V','I','T',RAMFONT,0x53,ROMFONT,'A',' ','U',RAMFONT,0x59,0x58,ROMFONT,'M',' ',RAMFONT,0x57,0x55,ROMFONT,'O',0};
#endif

			#ifdef TW8816	
   				ClearDataCnt(GAUGEINFO_ADDR,30*5);		
			#else
   			ClearOSDInfo();
   			ClearDataCnt(GAUGEINFO_ADDR,30*5);
			#endif

			 InitOSDWindow(Init_Osd_DisplayGAUGEWindow);   
			  
   switch(info)
   {
	case InfoOSDMENULOCKED: 
	#ifndef QUAD 
		if(mirror_flag==1)
		{///normal
		DrawAttrCnt(37,Gauge_COLOR3,150);   //設定位址的屬性 
  		WriteStringToAddr((30*3+7)+8-3,"OSD MENU LOCKED",15);
		}
		else
		{////mirror
		DrawAttrCnt(37,Gauge_COLOR3,150);   //設定位址的屬性 
  		WriteStringToAddr((30*3+7)+8-4,Str_LOCK_Mirror,23);
		}
	#else
		DrawAttrCnt(0,Gauge_COLOR3,30*5);   //設定位址的屬性 
  		WriteStringToAddr((30*3+7)+8,"OSD MENU LOCKED",15);
	#endif
		break;
 
	case InfoOSDMENUATCIVE: 
	#ifndef QUAD
		if(mirror_flag==1)
			{///normal
	   		DrawAttrCnt(37,Gauge_COLOR1,150);   //設定位址的屬性 
	   		WriteStringToAddr((30*3+7)+8-3,"OSD MENU ACTIVE",15);
			}
		else
			{///mirror
			DrawAttrCnt(37,Gauge_COLOR1,150);   //設定位址的屬性 
	  		WriteStringToAddr((30*3+7)+8-4,Str_ACTIVE_Mirror,23);
			}
	#else
		DrawAttrCnt(0,Gauge_COLOR1,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+7,"OSD MENU ACTIVE",15);
	#endif
		break;

#ifdef SUPPORT_SDCARD  //Pinchi 20150319 add	
	case InfoFORMATSDCARD:
   		DrawAttrCnt(0,Gauge_COLOR2,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+8,"FORMAT SD CARD",14);
		break;

	case InfoFORMATSUCCESS:
   		DrawAttrCnt(0,Gauge_COLOR1,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+8,"FORMAT SUCCESS",14);
		break;

	case InfoFORMATFAIL:
   		DrawAttrCnt(0,Gauge_COLOR3,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+10,"FORMAT FAIL",11);
		break;

	case InfoPLZRESETSYSTEM:
   		DrawAttrCnt(0,Gauge_COLOR2,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+5,"PLEASE RESET SYSTEM",19);;
		break;
		
	case InfoRECORDERROR:
   		DrawAttrCnt(0,Gauge_COLOR3,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+9,"RECORD ERROR",12);
		break; 
		
	case InfoPASSWORDERROR:
   		DrawAttrCnt(0,Gauge_COLOR3,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+8,"PASSWORD ERROR",14);
		break; 

	case InfoFWUpdate:
   		DrawAttrCnt(0,Gauge_COLOR2,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+10,"FW Update...",12);
		break;

	case InfoFWUpdateSUCCESS:
   		DrawAttrCnt(0,Gauge_COLOR1,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+7,"FW Update SUCCESS",17);
		break;

	case InfoFWUpdateFAIL:
  		DrawAttrCnt(0,Gauge_COLOR3,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+8,"FW Update FAIL",14);
		break;

	case InfoSDCARDReset:
		DrawAttrCnt(0,Gauge_COLOR3,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+10,"SD CARD Reset",13);
		break;
	
	case InfoSDCARDNotReady:
		DrawAttrCnt(0,Gauge_COLOR3,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+6,"SD CARD Not Ready",17);
		break;
		
   	case InfoUpdateConfigStart: 
		DrawAttrCnt(0,Gauge_COLOR2,30*5);   //設定位址的屬性 
  	 	WriteStringToAddr(30*3+7,"Search Config ...",17);
		break;

	case InfoUpdateConfigSuccess: 
		DrawAttrCnt(0,Gauge_COLOR1,30*5);   //設定位址的屬性 
  	 	WriteStringToAddr(30*3+3,"Update Config SUCCESS",21);
		break; 

	case InfoUpdateConfigFail: 
		DrawAttrCnt(0,Gauge_COLOR3,30*5);   //設定位址的屬性 
  	 	WriteStringToAddr(30*3+5,"Search Config FAIL",18);
		break; 
#endif

	case InfoAutoDayNight_Auto:
   		DrawAttrCnt(0,Gauge_COLOR1,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+13,"Auto",4);
		break; 

	case InfoAutoDayNight_Day:
   		DrawAttrCnt(0,Gauge_COLOR1,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+13,"Day",3);
		break; 
	
	case InfoAutoDayNight_Night:
   		DrawAttrCnt(0,Gauge_COLOR1,30*5);   //設定位址的屬性 
   		WriteStringToAddr(30*3+13,"Night",5);
		break;

#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
		case InfoNoVideoSignal:
		
		    ShowOSDWindow(INPUTINFO_OSDWIN,FALSE);
		    ShowOSDWindow(OSDCURSORWINDOW,FALSE);

		    ShowOSDWindow(OSDMENU_TOPWIN,FALSE);
		
	//		 ShowOSDWindow(OSDMENUWINDOW,TRUE);	
		
		#if 1
   		DrawAttrCnt(0,(BG_COLOR_CYAN|CH_COLOR_WHITE),30*5);   //設定位址的屬性      	
		WaitEndofDisplayArea();
   		WriteStringToAddr(30*2+8+4,"VLoss",5);//ryan@20170906
		#endif

	//WriteTW88( 0xff, 0x00);//page 0
	//WriteTW88( 0x73, 0x00);
		
   		//WriteStringToAddr(30*2+8,"NO VIDEO SIGNAL",15);
		break;
#endif
   }	

   SetDisplayedOSD(GAUGEINFO);  //Pinchi 20150319 enable
   ShowOSDWindow(RATINGINFO_OSDWIN,TRUE);
   ShowOSDWindowAll(1);  //0x09c  第4bit : OSD ON, 1: OSD OFF
   WriteTW88(TW88_WINBLENDING,0x08);	   //wiliiam-v1.1-970827
}

#ifdef SUPPORT_SDCARD  //Pinchi 20160929 add for no DVR function
void DisplayFWVersion(void)  //2007.4.11 Justin
{
   extern CODE BYTE Str_VER_E[];
#ifdef SUPPORT_SDCARD  //Pinchi 20140924 add for AWT ML072Q
   BYTE i;
   BYTE Str_DVRVersion[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',0}; //  william-1.45-971106

	for(i=0;i<DVRVersionLen;i++) 
	{
		Str_DVRVersion[i]=DVRVersion[i];
	}
#endif

   ClearOSDInfo();
   InitOSDWindow(Init_Osd_DisplayGAUGEWindow);
   ClearDataCnt(GAUGEINFO_ADDR,30*5);
   DrawAttrCnt(0,Gauge_COLOR1,30*5);   //設定位址的屬性   
   WriteStringToAddr(30*0,"LCD:",4);
   
   WriteStringToAddr(30*1,Str_VER_E,11);

#ifdef SUPPORT_SDCARD
   WriteStringToAddr(30*2,"DVR:",4);
   WriteStringToAddr(30*3,Str_DVRVersion,DVRVersionLen);
 //  #endif
 // #if 0 
   	for(i=0;i<DVR_BUF_MAX;i++) 
	{  
		DisplayNumber(30*0+i*2,DVR_buf[i],4);
	}
#endif
   SetDisplayedOSD(GAUGEINFO);
   ShowOSDWindow(RATINGINFO_OSDWIN,TRUE);
   ShowOSDWindowAll(1);  //0x09c  第4bit : OSD ON, 1: OSD OFF
   WriteTW88(TW88_WINBLENDING,0x08);	   //wiliiam-v1.1-970827
}
//#endif	//#ifdef SUPPORT_SDCARD

//#ifdef SUPPORT_SDCARD  //Pinchi 20140918 enable for AWT ML072Q
void DisplayDVRStatus(void)
{
	extern CODE BYTE SDCARD_ICON[];
	extern CODE BYTE RECORDSDCARD_ICON[];
	extern CODE BYTE NoSDCard_ICON[];
	extern CODE BYTE SDCardOverWrite_ICON[];
	extern CODE BYTE Init_Osd_DisplayInput[] ;
	extern CODE BYTE GPS_ICON[];	
	extern CODE BYTE NoGPS_ICON[];
	extern CODE BYTE NoGPS_ICON2[];
	extern CODE BYTE Gsensor_ICON[];
	extern CODE BYTE NoGsensor_ICON[];
	extern CODE BYTE WiFi_ICON[];
	extern CODE BYTE NoWiFi_ICON[];
	extern CODE BYTE BookMark_ICON[];
	extern CODE BYTE WiFiLittle_ICON[];
	//CODE BYTE Str_720[] = {RAMFONT,0x08,0x09,ROMFONT,0};
	//CODE BYTE Str_352[] = {RAMFONT,0x0A,0x0B,ROMFONT,0};
	BYTE RecordStatus=0;

	if(Init_DisplayInput==0)
		{
		InitOSDWindow(Init_Osd_DisplayInput);
		if((( DisplayedOSD & GAUGEINFO)||( DisplayedOSD & INPUTINFO))==0)
			ClearOSDInfo();
   		ClearDataCnt(DVRStatus_ADDR,37);
		DrawAttrCnt(DVRStatus_ADDR,0x00,37);
		DisplayedOSD |= INPUTINFO;
   		Init_DisplayInput=1;
		Printf("\r\nDisplayDVRStatus init", 0);
		}
	//display date & time
	DrawAttrCnt(DVRStatus_ADDR,0x02,25);   //設定位址的屬性   
	DrawAttrCnt(DVRStatus_ADDR+26,Gauge_COLOR3,1);   //設定位址的屬性   
	DrawAttrCnt(DVRStatus_ADDR+28,Gauge_COLOR2,2);   //設定位址的屬性 
	DisplayNumber(DVRStatus_ADDR+1,year1,4);
	DisplayNumber(DVRStatus_ADDR+3,year2,4);
	WriteStringToAddr(DVRStatus_ADDR+5,"/",1);
	DisplayNumber(DVRStatus_ADDR+6,month,4);
	WriteStringToAddr(DVRStatus_ADDR+8,"/",1);
	DisplayNumber(DVRStatus_ADDR+9,day,4);
	DisplayNumber(DVRStatus_ADDR+12,hour,4);
	DisplayNumber(DVRStatus_ADDR+15,minute,4);

	if(second&0x01)
		WriteStringToAddr(DVRStatus_ADDR+14,":",1);
	else
		 ClearDataCnt(DVRStatus_ADDR+14,1);	

	//WriteStringToAddr(DVRStatus_ADDR+16,":",1);
	//DisplayNumber(DVRStatus_ADDR+17,second,4);

	//display dvr status
	if(DVR_SDCardAvailable!=0xff)
	{
		if((DVR_RecordStatus&NORMAL_Record)==NORMAL_Record)	
		{
			if((DVR_RecordStatus&OverWrite_Record)==OverWrite_Record)	
			{
			  	WriteStringToAddr(DVRStatus_ADDR+26,SDCardOverWrite_ICON,3);
				//DisplayNumber(DVRStatus_ADDR+22,DVR_SDCardAvailable,4);
				//WriteStringToAddr(DVRStatus_ADDR+24,"%",1);
			}
			else
		  		WriteStringToAddr(DVRStatus_ADDR+26,RECORDSDCARD_ICON,3);
			//DisplayNumber(DVRStatus_ADDR+22,DVR_SDCardAvailable,4);
			//WriteStringToAddr(DVRStatus_ADDR+24,"%",1);
			FormatSDCard=1;
		}
		else
		{
		  	WriteStringToAddr(DVRStatus_ADDR+26,SDCARD_ICON,3);
			//DisplayNumber(DVRStatus_ADDR+22,DVR_SDCardAvailable,4);
			//WriteStringToAddr(DVRStatus_ADDR+24,"%",1);
		}

	#if 0
		if((DVR_RecordStatus&ALARM_Record)==ALARM_Record)
		   {
			 WriteStringToAddr(DVRStatus_ADDR+26,"A",1);
			 #if 0
			 if(DVR_Resolution==1)		//720*480
			   {
				 WriteStringToAddr(DVRStatus_ADDR+28,Str_720,4);
			   }
			 else if(DVR_Resolution==2) //352*234
			   {
				 WriteStringToAddr(DVRStatus_ADDR+28,Str_352,4);
			   }
			 #endif
			RecordStatus=1; 
		   }
		else if((DVR_RecordStatus&Manual_Record)==Manual_Record && RecordStatus==0)
		   {
			 WriteStringToAddr(DVRStatus_ADDR+26,"M",1);
			 #if 0
			 if(DVR_Resolution==1)		//720*480
			   {
				 WriteStringToAddr(DVRStatus_ADDR+28,Str_720,4);
			   }
			 else if(DVR_Resolution==2) //352*234
			   {
				 WriteStringToAddr(DVRStatus_ADDR+28,Str_352,4);
			   } 
			 #endif
			 RecordStatus=1; 
		   }
		else if((DVR_RecordStatus&NORMAL_Record)==NORMAL_Record && RecordStatus==0)
		   {
			 WriteStringToAddr(DVRStatus_ADDR+26,"R",1);
			#if 0 
			 if(DVR_Resolution==1)		//720*480
			   {
				 WriteStringToAddr(DVRStatus_ADDR+28,Str_720,4);
			   }
			 else if(DVR_Resolution==2) //352*234
			   {
				 WriteStringToAddr(DVRStatus_ADDR+28,Str_352,4);
			   }
			 #endif
			 RecordStatus=1; 
		   }
		if(RecordStatus==0)
    		 ClearDataCnt(DVRStatus_ADDR+26,4);	
	#endif		
	}
	else
	{
		WriteStringToAddr(DVRStatus_ADDR+26,NoSDCard_ICON,4);
		FormatSDCard=1;			//WILLIAM-20120523
		//ClearDataCnt(DVRStatus_ADDR+22,8);
	}

	//if(GPSState==0)
	//	{
	if((DVR_RecordStatus&GPS)==GPS)	
		WriteStringToAddr(DVRStatus_ADDR+29,GPS_ICON,4);
	else
		WriteStringToAddr(DVRStatus_ADDR+29,NoGPS_ICON,4);
	//	}
	//else
	//	{
	//			WriteStringToAddr(DVRStatus_ADDR+29,NoGPS_ICON2,4);
	//	}

	if((DVR_RecordStatus&G_Sensor)==G_Sensor)
		WriteStringToAddr(DVRStatus_ADDR+32,Gsensor_ICON,4);
	else
		WriteStringToAddr(DVRStatus_ADDR+32,NoGsensor_ICON,4);

	if((DVR_RecordStatus&WIFI)==WIFI)
		{
		if((DVR_RecordStatus&WIFI_Signal)==WIFI_Signal)
			WriteStringToAddr(DVRStatus_ADDR+35,WiFiLittle_ICON,4);
		else
			WriteStringToAddr(DVRStatus_ADDR+35,WiFi_ICON,4);
		}
	else
		WriteStringToAddr(DVRStatus_ADDR+35,NoWiFi_ICON,4);

	if(BookMarkState)
		WriteStringToAddr(DVRStatus_ADDR+23,BookMark_ICON,4);
	else
		 ClearDataCnt(DVRStatus_ADDR+23,2);	
	
	if(ReadEEP(EEP_DVRDisplay)==0)
		ShowOSDWindow(DVRStatus_OSDWIN,TRUE);
	else
		ShowOSDWindow(DVRStatus_OSDWIN,FALSE);

   ShowOSDWindowAll(1);  //0x09c  第4bit : OSD ON, 1: OSD OFF
   WriteTW88(TW88_WINBLENDING,0x08);	   //wiliiam-v1.1-970827

}
#endif	//#ifdef SUPPORT_SDCARD

#if 0 //def AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
void AWT_Display_NoVideoSignal(BYTE bOnOff)
{
	if ((SelectModeType == AVMode) && !(GetDisplayedOSD() & MENU))
	{
		//	if ((SelectModeType == AVMode) && !(GetDisplayedOSD() & MENU))
		if (bOnOff == ON)  //Input=No signal
		{
			//	if ((ReadDecoder(0x01) & 0x80) != 0x00)
			if (DisplayInputHold == 0)
			{
				DisplayInputHold = 1;
				displayhold_flag = 0;
				DisplayInformation(InfoNoVideoSignal);
				//	VideoLossShowTime = GetTime_ms();
			}
		}
		else
		{
			//	ClearInput();
			if (DisplayInputHold == 1)
			{
				DisplayInputHold = 0;
				DisplayInput();
			}
		}
	}
}
#endif



//
#include "Config.h"

#include "typedefs.h"
#include "Debug.h"
#include "main.h"


#include "osdbasic.h"
#include "printf.h"
#include "CPU.h"
#include "osdmenu.h"
#include "dispinfo.h"
#include "tw88.h"
#include "i2c.h"
#include "etc_eep.h"
#include "audio.h"
#include "measure.h"
#include "pc_eep.h"
#include "RegMap.h"
#include "panel.h"
#include "HS_DisplayOSD.h"
#include "HS_keyremo.h"
//----------------------------------------------------------------------
//extern  CODE  BYTE InputSelectionString[][16];
extern BYTE Gauge_Flag;

extern  CODE  struct struct_IdName struct_InputSelection[];
extern  CODE  struct struct_IdName struct_InputSelection_S[];
extern  CODE  struct struct_IdName struct_VInputStd[];

#ifdef AWT_ML072S
BYTE vloss_flag=0,vloss_buf=0;
#endif
BYTE  DisplayedOSD = 0;
BYTE  mirror_flag;
extern  bit   TVChManual;
//extern BYTE cLastSyncLoss;
static	DATA WORD  OSDDisplayedTime;		//in ms

#ifdef SUPPORT_COMPONENT
extern  BYTE  ComponentMode;
#endif
extern CODE BYTE Init_Osd_DisplayLogo[];
extern CODE BYTE Init_Osd_DisplayInput[];
#ifndef QUAD
extern CODE BYTE Init_Osd_DisplayInput_M[];
#endif
#ifdef ADD_ANALOGPANEL
extern CODE BYTE Init_Osd_DisplayLogo_A[];
extern CODE BYTE Init_Osd_DisplayInput_A[];
#endif

extern CODE BYTE Init_Osd_BarWindow[];
extern CODE BYTE Init_Osd_DisplayPCInfo[];
extern CODE BYTE *StrVolume[];
#ifdef E_Wintek
extern CODE BYTE *StrVolume2[];
#endif
extern CODE BYTE *Str_Brightness[];
extern bit SpeedDomeMode;
//#ifndef QUAD
extern BYTE	displayhold_flag;  //Pinchi 20150319 enable
//#endif

#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
extern bit IsDrawNoVideoSignal;
#endif

#ifdef TW9908
CODE BYTE TW9908String[]=	{ "   TW9908   "};
CODE BYTE TW9905String[]=	{ "   TW9905   "};
#endif

CODE BYTE TW8806String[]=	{ "   TW8806   "};

CODE BYTE TechwellString[]=	{ "Techwell,Inc" };

#ifdef SUPPORT_COMPONENT
CODE BYTE COMPONENT_STR[][15] = {
    "YPbPr 480i",	// 0
    "YPbPr 576i",	// 1
    "YPbPr 480p",	// 2
    "YPbPr 576p",	// 3
    "YPbPr 1080i",	// 4
    "YPbPr 720p",	// 5
	"YPbPr 720p50",	
    "YPbPr 1080i50",
};
#endif

//================================================================
//					Display information
//================================================================
#ifdef DISPLAY_TECHWELL_LOGO  //Pinchi 2050903 add
/*
void DisplayLogo(void)
{
	BYTE CODE *str;
	//ClearOSDInfo();

	#ifdef TW9908
	if( (ReadDecoder(0) & 0xf8) == 0x28 ) str = TW9905String;
	else                                  str = TW9908String;
	#else
	str = TW8806String;
	#endif

	InitOSDWindow(Init_Osd_DisplayLogo);
	#ifdef ADD_ANALOGPANEL
	if(IsAnalogOn())
		InitOSDWindow(Init_Osd_DisplayLogo_A);
	#endif
	
	ClearDataCnt(LOGO_ADDR, 12*2); // Total 12*2 Char.

	DrawAttrCnt(LOGO_ADDR, CH_COLOR_WHITE, 12 );	 
	DrawAttrCnt(LOGO_ADDR+12, CH_COLOR_RED, 12 );

	WriteStringToAddr(LOGO_ADDR, str, 12);
	WriteStringToAddr(LOGO_ADDR+12*1, TechwellString,12);

	ShowOSDWindow(TECHWELLOGO_OSDWIN,TRUE);
	
}
*/
void ClearLogo(void)
{
	ShowOSDWindow(TECHWELLOGO_OSDWIN,FALSE);
	#ifdef DEBUG_OSD
	dPrintf("\r\n++(ClearLogo)");
	#endif
}
#endif

void ClearDisplayedOSD( BYTE newd )
{
	DisplayedOSD &= (~(newd));
}

void SetDisplayedOSD( BYTE newd )
{
	DisplayedOSD |= newd;
}

BYTE GetDisplayedOSD(void)
{
	return DisplayedOSD;
}

void ClearOSDInfo(void)
{
	BYTE dt;

#ifdef DISPLAY_TECHWELL_LOGO  //Pinchi 2050903 add
	ClearLogo();
#endif
	dt = GetDisplayedOSD(); 
	#if 1 //def DEBUG_OSD
	Printf("\r\n++(ClearOSDInfo): DisplayedOSD:%2x",(WORD) GetDisplayedOSD());
	#endif
	#ifdef SUPPORT_PC
	if( dt & PCINFO)		ClearPCInfo();
	#endif

		if( (dt & TVVOL) || ( dt & TVCHN) )
		{
		
		ClearTVInfo();
			#ifdef AWT_NO_SIGNAL_MSG  //ryan@20170906
			IsDrawNoVideoSignal = 0;
			#endif
		}
	if( dt & MUTE ) 		ClearMuteInfo();
	if( dt & INPUTINFO ) 	ClearInput();
	if( dt & MENU ) 		CloseOSDMenu();
	if( dt & GAUGEINFO ) 	ClearGAUGEINFO(); 
	if(dt& VLOSSINFO)	 	ClearVlossOsd();
}


#ifdef AWT_ML072S

/*-------------------------------*/
/*                VlossHandler                 */
/*-------------------------------*/
void VlossHandler(void)
{
	CODE BYTE Str_VLOSS[] = {'V','L','o','s','s',0};
	CODE BYTE Str_VLOSS_M[] = {RAMFONT,0x5b,0x5b,ROMFONT,'o',RAMFONT,0x50,ROMFONT,'V',0};

#ifdef HS
return;
#endif
	
    vloss_buf= ReadDecoder(0x01);	
	
    if(((vloss_buf&0x80)==0x80)&&(!(GetDisplayedOSD() & (VLOSSINFO)))) 
   	{
   	vloss_flag=1;
	if(mirror_flag==1)///no mirror
	{
	DrawAttrCnt(107/*OSD_VLOSS_ADDR*/, OSD_VLOSS_COLOR, 5 );  
	WriteStringToAddr(107/*OSD_VLOSS_ADDR*/, Str_VLOSS, 5); 
	SetDisplayedOSD(VLOSSINFO);
	ShowOSDWindowAll(1);
	ShowOSDWindow(RATINGINFO_OSDWIN/*VLOSSINFO_OSDWIN*/-1,TRUE);////vloss osd
	}
	else///mirror
	{
	DrawAttrCnt(106/*OSD_VLOSS_ADDR*/, OSD_VLOSS_COLOR, 5 );  
	WriteStringToAddr(106/*OSD_VLOSS_ADDR*/, Str_VLOSS_M, 9); 
	SetDisplayedOSD(VLOSSINFO);
	ShowOSDWindowAll(1);
	ShowOSDWindow(RATINGINFO_OSDWIN/*VLOSSINFO_OSDWIN*/-1,TRUE);////vloss osd
	}

	//  if( ReadEEP(EEP_GAUGEMode)==0 && ReadEEP(EEP_RearMode)==0&&(TriggerMode==REVERSE_TRIG))
  	//  DisplayGaugeOSD();


	#ifdef Hs_debug
	Printf("\r\nvloss_flag==1");
	#endif

	
    	}
	else if(((vloss_buf&0x80)==0)&&(GetDisplayedOSD() & (VLOSSINFO)))
		{   	
//		DisplayedOSD &= (~(INPUTINFO));///reset input info for 2s
		ClearDisplayedOSD(INPUTINFO);///reset input info for 2s
		vloss_flag=0;
		//ClearVlossOsd();
		ClearDisplayedOSD(VLOSSINFO);
		
	if(mirror_flag==1)///no mirror
	ClearDataCnt(107, 5);
	else///mirror
	ClearDataCnt(106, 5);
	
		#ifdef Hs_debug
		Printf("\r\nvloss_flag==0");
		#endif
		}
}
#endif

void DisplayInput(void)
{
	BYTE inputs, len1, i, SystemAddr; //len2

#ifdef	AWT_ML072S  //Pinchi 20140902 add for AWT ML072S
//	CODE BYTE Str_CAM_E[] = {'C','A','M',0};
	//CODE BYTE *Str_CAM[] = {Str_CAM_E};
//	BYTE len;
//	BYTE *Str;

	CODE BYTE Str_CAM_A[] = {'C','A','M',' ','A',' ',' ',' ',0};
	CODE BYTE Str_CAM_B[] = {'C','A','M',' ','B',' ',' ',' ',' ',0};
	CODE BYTE Str_CAM_R[] = {'C','A','M',' ','R',' ',' ',' ',' ',0};
	CODE BYTE Str_AV[] = {'A','V',' ',' ',' ',' ',' ',' ',' ',0};	//william-ml072s-971230

	CODE BYTE Str_CAM_Mirror_A[] = {' ',RAMFONT,0x07,ROMFONT,' ','A',' ','M','A',RAMFONT,0x53,ROMFONT,0};
	CODE BYTE Str_CAM_Mirror_B[] = {' ',RAMFONT,0x07,ROMFONT,' ',RAMFONT,0x51,ROMFONT,' ','M','A',RAMFONT,0x53,ROMFONT,0};
	CODE BYTE Str_CAM_Mirror_R[] = {' ',' ',RAMFONT,0x07,ROMFONT,' ',RAMFONT,0x52,ROMFONT,' ','M','A',RAMFONT,0x53,ROMFONT,0};	
/*	CODE BYTE Str_CAM_Mirror_A[] = {' ',' ','M',' ',' ','A',' ','M','A',RAMFONT,0x53,ROMFONT,0};
	CODE BYTE Str_CAM_Mirror_B[] = {' ',' ','M',' ',' ',RAMFONT,0x51,ROMFONT,' ','M','A',RAMFONT,0x53,ROMFONT,0};
	CODE BYTE Str_CAM_Mirror_R[] = {' ',' ','M',' ',' ',RAMFONT,0x52,ROMFONT,' ','M','A',RAMFONT,0x53,ROMFONT,0};	*/
	CODE BYTE Str_Mirror_J[] = {RAMFONT,0x54,ROMFONT,0};
	#ifdef AWT_ML072S

//	CODE BYTE Str_Mirror_S[] = {0x90,0x91,0};
	CODE BYTE Str_Mirror_S[] = {RAMFONT,0x55,ROMFONT,0};
		#ifndef HS
		CODE BYTE Str_S[] = {0x90,0x91,0};	//william-ml072s-971230
		#endif
	#else
	CODE BYTE Str_Mirror_S[] = {RAMFONT,0x55,ROMFONT,0};
	#endif
#endif
#ifdef DEBUG_OSD
	Printf("\r\n++(DisplayInput): DisplayedOSD:%2x",(WORD) GetDisplayedOSD());
#endif	
	SystemAddr=INPUTINFO1_ADDR;

	ClearOSDInfo();

	InitOSDWindow(Init_Osd_DisplayInput);
	ClearDataCnt(INPUTINFO_ADDR, 255); // Total 42 Char.
	DrawAttrCnt(INPUTINFO_ADDR, OSD_INFO_COLOR, 255 );	
	for(i=0;i<240;i++){WriteStringToAddr(i," ",1);}  	//william-v1.0-970729
	DisplayedOSD |= INPUTINFO;

	inputs = GetInputSelection();

	#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
	if( inputs==PC || inputs==DTV )
		len2 = strlen( GetPCInputSourceName() );
	else
	#endif
	//	len2 = strlen( struct_VInputStd[GetVInputStdInx()].Name );  //Pinchi 20150902 disable for unuse

#ifdef QUAD
//	if(ReadEEP(EEP_COSDMode)==1||inputs==CH_TW2835)		//Display Off		william-991221
  #if 1  //Pinchi 20150901 change condition by AV and TW2835 is independent
	if (inputs == CH_TW2835)
  #else
	if ((ReadEEP(EEP_COSDMode)==1 && (SelectModeType != AVMode)) || inputs==CH_TW2835)	//Pinchi 20141024 modify to display AV 2s
  #endif
		return;

	for (i=1; ;i++)
		if( struct_InputSelection[i].Id==inputs )  break;

	len1 = strlen(struct_InputSelection[i].Name);	
	WriteStringToAddr(INPUTINFO_ADDR, struct_InputSelection[i].Name, len1);

	if ((ReadEEP(EEP_COSDMode) == 1) && (SelectModeType == AVMode))  //Pinchi 20141024 modify to display AV 2s
	{
		displayhold_flag = 5;
		Printf("\r\n[MSG]DisplayInput() => SelectModeType=AVMode to set time & displayhold_flag=%bx",displayhold_flag);  //pinchi test
	}

#else
		//if(ReadEEP(EEP_COSDMode)==1)		//Display Off		william-991221
		//	return;	

	for (i=1; ;i++)
		if( struct_InputSelection_S[i].Id==inputs )  break;

	len1 = strlen(struct_InputSelection_S[i].Name);

	switch(i)
	{
		case COMPOSITE1:
			mirror_flag=ReadEEP(EEP_CAMAMode);

			if(mirror_flag==1)
		 	{
		 		#ifndef AWT_ML072S			
				DrawAttrCnt(32, Trigger_COLOR, 1 );		//wiliiam-v1.1-970827
				#else
				DrawAttrCnt(INPUTINFO_ADDR, Trigger_COLOR, 10 );		//wiliiam-v1.1-970827
				#endif
				DrawAttrCnt(24, OSD_INFO_COLOR, 8 );  
				WriteStringToAddr(24+2, Str_CAM_A, 8); 

				if (TriggerFlag)
					#ifndef AWT_ML072S
					WriteStringToAddr(32,"T" ,1); 
					#else
					WriteStringToAddr(INPUTINFO_ADDR+8,"T" ,1); 
					#endif
				
				else if(NowModeState==JumpMode)
				{
					if(SEQFlag)
					{
						DrawAttrCnt(INPUTINFO_ADDR+8, Jump_COLOR,1 );
						#ifndef AWT_ML072S
						WriteStringToAddr(21,Str_S,2); 
						#else
						WriteStringToAddr(INPUTINFO_ADDR+8,"S" ,1); 
						#endif
					}
					else	
				   	{
						DrawAttrCnt(INPUTINFO_ADDR+8, Jump_COLOR,1 );
						WriteStringToAddr(INPUTINFO_ADDR+8,"J" ,1); 
					}
				} 	
			 }
			else	
		 	{
				//InitOSDWindow(Init_Osd_DisplayInput_M);
			    //WriteTW88(TW88_WINBLENDING,0x04);		//wiliiam-v1.1-970827
				DrawAttrCnt(INPUTINFO_MIRROR_ADDR+25, Trigger_COLOR/*OSD_INFO_COLOR*/,9);    
				//DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Mirror_COLOR, 3 );
				DrawAttrCnt(INPUTINFO_MIRROR_ADDR+1, OSD_INFO_COLOR, 8 );   			
				WriteStringToAddr(INPUTINFO_MIRROR_ADDR+1, Str_CAM_Mirror_A, 12); 
				if (TriggerFlag)
					{
					WriteStringToAddr(INPUTINFO_MIRROR_ADDR+32-7,"T" ,1); 
					}
				else if(NowModeState==JumpMode)
				{
					if(SEQFlag)
					{
					      DrawAttrCnt(25, Jump_COLOR,1 );
					      	#ifdef HS
						WriteStringToAddr(25,Str_Mirror_S,2); 							
							#else
						WriteStringToAddr(10,Str_Mirror_S,2); 
						  #endif
					}
					else	
					{
						DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Jump_COLOR,1 );
						WriteStringToAddr(INPUTINFO_MIRROR_ADDR,Str_Mirror_J,3); 
					}
				}	 
				if(SEQFlag && !TriggerFlag)
				{
		   	        //DrawAttrCnt(INPUTINFO_MIRROR_ADDR+10, Gauge_COLOR1, 2 );   
		   	        //WriteStringToAddr(INPUTINFO_MIRROR_ADDR+10,Str_reverse,2);  
				} 
			}
		break;

	 case COMPOSITE2:
	 	mirror_flag=ReadEEP(EEP_CAMBMode);
		 if(mirror_flag==1)
		 	{
		 		#ifndef AWT_ML072S			
				DrawAttrCnt(32, Trigger_COLOR, 1 );		//wiliiam-v1.1-970827
				#else
				DrawAttrCnt(INPUTINFO_ADDR, Trigger_COLOR, 10 );		//wiliiam-v1.1-970827
				#endif
		 	 //WriteTW88(TW88_WINBLENDING,0x04);	//wiliiam-v1.1-970827
		     //DrawAttrCnt(INPUTINFO_ADDR, Trigger_COLOR, 10 );		//wiliiam-v1.1-970827
		     DrawAttrCnt(INPUTINFO_ADDR, OSD_INFO_COLOR, 8 );  
	         WriteStringToAddr(24+2, Str_CAM_B, 9); 
			 if(TriggerFlag)
			    WriteStringToAddr(INPUTINFO_ADDR+8,"T" ,1); 
			 else if(NowModeState==JumpMode)
			{
			if(SEQFlag)
				{
				DrawAttrCnt(INPUTINFO_ADDR+8, Jump_COLOR,1 );
				WriteStringToAddr(INPUTINFO_ADDR+8,"S" ,1); 
				}
			else	
			   {
				DrawAttrCnt(INPUTINFO_ADDR+8, Jump_COLOR,1 );
				WriteStringToAddr(INPUTINFO_ADDR+8,"J" ,1); 
				}
			   	}

			 }
		 else	
		 	{
		 	DrawAttrCnt(INPUTINFO_MIRROR_ADDR+25, Trigger_COLOR/*OSD_INFO_COLOR*/,9);    
				//DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Mirror_COLOR, 3 );
				DrawAttrCnt(INPUTINFO_MIRROR_ADDR+1, OSD_INFO_COLOR, 8 );   			
				WriteStringToAddr(INPUTINFO_MIRROR_ADDR+1, Str_CAM_Mirror_B, 12+1); 
				/*
	    	DrawAttrCnt(INPUTINFO_MIRROR_ADDR, OSD_INFO_COLOR, 9 );    
		   DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Mirror_COLOR, 3 );
	          DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Trigger_COLOR, 1 );    
	          WriteStringToAddr(INPUTINFO_MIRROR_ADDR, Str_CAM_Mirror_B, 20); 
			  */
			  if(TriggerFlag)
			  WriteStringToAddr(INPUTINFO_MIRROR_ADDR+25,"T" ,1); 
			else if(NowModeState==JumpMode)
			{
			if(SEQFlag)
				{
				DrawAttrCnt(INPUTINFO_MIRROR_ADDR+25, Jump_COLOR,1 );
				WriteStringToAddr(INPUTINFO_MIRROR_ADDR+25,Str_Mirror_S,3); 
				}
			else	
		   	       {
				DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Jump_COLOR,1 );
				WriteStringToAddr(INPUTINFO_MIRROR_ADDR,Str_Mirror_J,3); 
				}
		 	       } 
	  	 	}
		 break;

	//william-ml072s-v1.0-971230		 
	 case COMPOSITE3:
	 	 mirror_flag=ReadEEP(EEP_CAMRMode);

		 if(mirror_flag==1)
		 	{
		   DrawAttrCnt(32, Trigger_COLOR,1 );		//wiliiam-v1.1-970827
		   DrawAttrCnt(INPUTINFO_ADDR, OSD_INFO_COLOR, 8 );
	          WriteStringToAddr(24+2, Str_CAM_R, 9); 

			  if(TriggerFlag)
			  	{
				#ifndef AWT_ML072S
				WriteStringToAddr(32,"T" ,1); 		
				#else
				WriteStringToAddr(INPUTINFO_ADDR+8,"T" ,1); 
				#endif
			  	}
			   else if(NowModeState==JumpMode)
			{
			if(SEQFlag)
				{
				DrawAttrCnt(INPUTINFO_ADDR+8, Jump_COLOR,1 );
				WriteStringToAddr(INPUTINFO_ADDR+8,"S" ,1); 
				}
			else	
			   	{
				DrawAttrCnt(INPUTINFO_ADDR+8, Jump_COLOR,1 );
				WriteStringToAddr(INPUTINFO_ADDR+8,"J" ,1); 
				}
			   	}
		 	}
		 else	
		 	{
		 	 //WriteTW88(TW88_WINBLENDING,0x04);	//wiliiam-v1.1-970827
			//InitOSDWindow(Init_Osd_DisplayInput_M);
		   DrawAttrCnt(INPUTINFO_MIRROR_ADDR, OSD_INFO_COLOR,14 );    
//		   DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Mirror_COLOR, 3 );
	          DrawAttrCnt(INPUTINFO_MIRROR_ADDR+25, Trigger_COLOR, 1 );
	          WriteStringToAddr(INPUTINFO_MIRROR_ADDR, Str_CAM_Mirror_R, 14); 
			  
			  if(TriggerFlag)
			  WriteStringToAddr(INPUTINFO_MIRROR_ADDR+25,"T" ,1); 
			  else if(NowModeState==JumpMode)
				{		
					if(SEQFlag)
						{
						DrawAttrCnt(INPUTINFO_MIRROR_ADDR+25, Jump_COLOR,1 );
							#ifndef AWT_ML072S
							WriteStringToAddr(INPUTINFO_MIRROR_ADDR+10,Str_Mirror_S,2); 
							#else				
							WriteStringToAddr(INPUTINFO_MIRROR_ADDR+25,Str_Mirror_S,3); 
							#endif
						}
					else	
				   	       {
						DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Jump_COLOR,1 );
						WriteStringToAddr(INPUTINFO_MIRROR_ADDR,Str_Mirror_J,3); 
						}
		 	      } 
		 	}
		 break;

	 case COMPOSITE4:
		mirror_flag=1;
		  //WriteTW88(TW88_WINBLENDING,0x04);	//wiliiam-v1.1-970827
		   DrawAttrCnt(INPUTINFO_ADDR, Trigger_COLOR,10 );		//wiliiam-v1.1-970827
		   DrawAttrCnt(INPUTINFO_ADDR, OSD_INFO_COLOR, 8 );
		   #ifndef AWT_ML072S
		   WriteStringToAddr(24, Str_AV, 9); 
		   #else
		   WriteStringToAddr(INPUTINFO_ADDR+24+2, Str_AV, 9);
		   #endif
		   
	       		if(SEQFlag && !TriggerFlag)
			   	{
			   	 //DrawAttrCnt(INPUTINFO_ADDR-3, Gauge_COLOR1, 2 );
		  		 //WriteStringToAddr(INPUTINFO_ADDR-3,Str_reverse,2);  	 
		  		 #ifdef AWT_ML072S
		 		DrawAttrCnt(INPUTINFO_ADDR+8, Jump_COLOR,1 );
				WriteStringToAddr(INPUTINFO_ADDR+8,"S",1); 
		  		 #endif
			   	}
		  break;

	}

		displayhold_flag=4;
	
#endif

#if 0
	Str = Str_CAM[GetOSDLang()];
	len = strlen(Str);
	if(SpeedDomeMode==1)
	{
		DrawAttrCnt(INPUTINFO_ADDR+len1,OSD_INFO_COLOR,len);
		WriteStringToAddr(INPUTINFO_ADDR+len1,Str,len);
	}
	else
	{
		ClearDataCnt(INPUTINFO_ADDR+len1, len); // Total 42 Char.
		DrawAttrCnt(INPUTINFO_ADDR+len1, OSD_INFO_COLOR, len );
	}
#endif

	ShowOSDWindow(INPUTINFO_OSDWIN-1,TRUE);


#if 0
if(ReadEEP(EEP_DVRDisplay)==0)
	ShowOSDWindow(DVRStatus_OSDWIN,TRUE);
else
	ShowOSDWindow(DVRStatus_OSDWIN,FALSE);
#endif

	//ShowOSDWindow(INPUTINFO_OSDWIN,TRUE);
	ShowOSDWindowAll(1);
	#ifdef AWT_ML072S
	VlossHandler();
	#endif

	OSDDisplayedTime = GetTime_ms();	
}



//#ifdef _DisplayHandler
#ifndef QUAD
/*-------------------------------*/
/*                DisplayHandler                 */
/*-------------------------------*/
#ifdef AWT_ML072S
#else
void DisplayHandler()
{
  BYTE i,len1,inputs; //dat,mirror_flag 
   //extern CODE BYTE Init_Osd_DisplayInput_S[];
   //Ryan@970729
 CODE BYTE Str_CAM_A[] = {'C','A','M',' ','A',' ',' ',' ',' ',0};
 CODE BYTE Str_CAM_B[] = {'C','A','M',' ','B',' ',' ',' ',' ',0};
 CODE BYTE Str_CAM_R[] = {'C','A','M',' ','R',' ',' ',' ',' ',0};
 CODE BYTE Str_AV[] = {'A','V',' ',' ',' ',' ',' ',' ',' ',0};	//william-ml072s-971230
//CODE BYTE Str_CAM_Mirror_A[] = {' ',' ',RAMFONT,0x41,ROMFONT,' ','A',' ','M','A',RAMFONT,0x36,ROMFONT,0};
// CODE BYTE Str_CAM_Mirror_B[] = {' ',' ',RAMFONT,0x41,ROMFONT,' ',RAMFONT,0x35,ROMFONT,' ','M','A',RAMFONT,0x36,ROMFONT,0};
// CODE BYTE Str_CAM_Mirror_R[] = {' ',' ',RAMFONT,0x41,ROMFONT,' ',RAMFONT,0x38,ROMFONT,' ','M','A',RAMFONT,0x36,ROMFONT,0};
 CODE BYTE Str_reverse[] = {0x90,0x91,0};
  // extern CODE BYTE Init_Osd_DisplayInput[];
   ShowOSDWindowAll(0);  //0x09c  第4bit : OSD ON, 1: OSD OFF
   // InitOSDWindow(Init_Osd_DisplayInput_S); 


   ClearDataCnt(0,INPUTINFO_WIDTH*6);   

  DrawAttrCnt(0,0x00,INPUTINFO_WIDTH*6);  //2007.4.25 解畫倒車線出現藍色區塊//william-v1.43-970403

  for(i=0;i<240;i++){WriteStringToAddr(i," ",1);}  	//william-v1.0-970729
	 inputs = GetInputSelection();
  for(i=1; ;i++)
    {
       if( struct_InputSelection[i].Id==inputs )  
         break;
    }
   // len1 = strlen(struct_InputSelection[i].Name);
   len1 = 20;
//	WriteTW88( TW88_WINBLENDING,  0x00 );
/////////////////////////////////////////////////////////////////////////
switch(i)
{
 case SOURCE_A:
 	mirror_flag=ReadEEP(EEP_CAMAMode);
//   if(ReadEEP(EEP_COSDMode)==0){
	 if(mirror_flag==1)
	 	{
	    //InitOSDWindow(Init_Osd_DisplayInput_A);
	      WriteTW88(TW88_WINBLENDING,0x04);		//wiliiam-v1.1-970827
	  DrawAttrCnt(INPUTINFO_ADDR, Trigger_COLOR, 10 );		//wiliiam-v1.1-970827
	   DrawAttrCnt(INPUTINFO_ADDR, DEFAULT_COLOR, 8 );  
          WriteStringToAddr(INPUTINFO_ADDR, Str_CAM_A, 9); 
		  if(TriggerFlag)
		    WriteStringToAddr(INPUTINFO_ADDR+8,"T" ,1); 
		  if(SEQFlag && !TriggerFlag)
		   	{
		   	 DrawAttrCnt(INPUTINFO_ADDR-3, Gauge_COLOR1, 2 );
	  		 WriteStringToAddr(INPUTINFO_ADDR-3,Str_reverse,2);  	 
		   	}
		 }
	 else	
	 	{
	 	#ifdef _MIRROR
	  // InitOSDWindow(Init_Osd_DisplayInput_M);
	   WriteTW88(TW88_WINBLENDING,0x04);		//wiliiam-v1.1-970827
	   DrawAttrCnt(INPUTINFO_MIRROR_ADDR, DEFAULT_COLOR,9 );    
	   DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Mirror_COLOR, 3 );
          DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Trigger_COLOR, 1 );   
          WriteStringToAddr(INPUTINFO_MIRROR_ADDR, Str_CAM_Mirror_A, len1); 
	         if(TriggerFlag)
		     WriteStringToAddr(INPUTINFO_MIRROR_ADDR,"T" ,1); 
		  if(SEQFlag && !TriggerFlag)
	   	       {
	   	        DrawAttrCnt(INPUTINFO_MIRROR_ADDR+10, Gauge_COLOR1, 2 );   
	   	        WriteStringToAddr(INPUTINFO_MIRROR_ADDR+10,Str_reverse,2);  
	 	       } 
		  #endif
	         }
//   	}
#if 0
    vloss_buf= ReadDecoder(0x01);	
    if((vloss_buf&0x80)!=0x00) 
   	{
   	vloss_flag=1;
	DrawAttrCnt(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4,Gauge_COLOR3,30); 
	if(!mirror_flag)
   	WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+9,Str_Mirror_Vloss,16);//william-v1.0-970725
	else
   	WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+8,Str_Vloss,10);//william-v1.0-970725
   	}
 	else 
	vloss_flag=0;
#endif
	 break;

 case SOURCE_B:
 	mirror_flag=ReadEEP(EEP_CAMBMode);
//if(ReadEEP(EEP_COSDMode)==0){
	 if(mirror_flag==1)
	 	{
	 	 WriteTW88(TW88_WINBLENDING,0x04);	//wiliiam-v1.1-970827
	//   InitOSDWindow(Init_Osd_DisplayInput_A);
	     DrawAttrCnt(INPUTINFO_ADDR, Trigger_COLOR, 10 );		//wiliiam-v1.1-970827
	     DrawAttrCnt(INPUTINFO_ADDR, DEFAULT_COLOR, 8 );  
         WriteStringToAddr(INPUTINFO_ADDR, Str_CAM_B, 9); 
		 if(TriggerFlag)
		    WriteStringToAddr(INPUTINFO_ADDR+8,"T" ,1); 
		 if(SEQFlag && !TriggerFlag)
		   {
		   	 DrawAttrCnt(INPUTINFO_ADDR-3, Gauge_COLOR1, 2 );
	  		 WriteStringToAddr(INPUTINFO_ADDR-3,Str_reverse,2);  	 
		   	}

		 }
	 else	
	 	{
	 	#ifdef _MIRROR
	 	 WriteTW88(TW88_WINBLENDING,0x04);	//wiliiam-v1.1-970827
	//   InitOSDWindow(Init_Osd_DisplayInput_M);
    	DrawAttrCnt(INPUTINFO_MIRROR_ADDR, DEFAULT_COLOR, 9 );    
	   DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Mirror_COLOR, 3 );
          DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Trigger_COLOR, 1 );    
          WriteStringToAddr(INPUTINFO_MIRROR_ADDR, Str_CAM_Mirror_B, len1); 
		  if(TriggerFlag)
		  WriteStringToAddr(INPUTINFO_MIRROR_ADDR,"T" ,1); 
		  if(SEQFlag && !TriggerFlag)
	   	       {
	   	        DrawAttrCnt(INPUTINFO_MIRROR_ADDR+10, Gauge_COLOR1, 2 );   
	   	        WriteStringToAddr(INPUTINFO_MIRROR_ADDR+10,Str_reverse,2);  
	 	       } 
		  #endif
  	 	}
//}
#if 0
    vloss_buf= ReadDecoder(0x01);	
    if((vloss_buf&0x80)!=0x00) 
   	{
   	vloss_flag=1;
	DrawAttrCnt(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4,Gauge_COLOR3,30); 
	if(!mirror_flag)
   	WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+9,Str_Mirror_Vloss,16);//william-v1.0-970725
	else
   	WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+8,Str_Vloss,10);//william-v1.0-970725
   	}
	else 
	vloss_flag=0;
#endif
	 break;
//william-ml072s-v1.0-971230	 
 case SOURCE_AV:
	mirror_flag=1;
	  WriteTW88(TW88_WINBLENDING,0x04);	//wiliiam-v1.1-970827
	   DrawAttrCnt(INPUTINFO_ADDR, Trigger_COLOR,10 );		//wiliiam-v1.1-970827
	   DrawAttrCnt(INPUTINFO_ADDR, DEFAULT_COLOR, 8 );
          WriteStringToAddr(INPUTINFO_ADDR, Str_AV, 9); 
#if 0
    vloss_buf = ReadDecoder(0x01);	
   	   	if((vloss_buf&0x80)!=0x00) 
   	      {
   	   vloss_flag=1;
   	       WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+8,Str_Vloss,10);//william-v1.0-970725
   	       }
   	 else 
	   vloss_flag=0;
       if(SEQFlag && !TGFlag1)
		   	{
		   	 DrawAttrCnt(INPUTINFO_ADDR-3, Gauge_COLOR1, 2 );
	  		 WriteStringToAddr(INPUTINFO_ADDR-3,Str_reverse,2);  	 
		   	}
#endif	   
	  break;
//william-ml072s-v1.0-971230		 
 case SOURCE_R:
 	 mirror_flag=ReadEEP(EEP_CAMRMode);
 //    if(ReadEEP(EEP_COSDMode)==0){
	 if(mirror_flag==1)
	 	{
	 	 WriteTW88(TW88_WINBLENDING,0x04);	//wiliiam-v1.1-970827
	//   InitOSDWindow(Init_Osd_DisplayInput_A);
	   DrawAttrCnt(INPUTINFO_ADDR, Trigger_COLOR,10 );		//wiliiam-v1.1-970827
	   DrawAttrCnt(INPUTINFO_ADDR, DEFAULT_COLOR, 8 );
          WriteStringToAddr(INPUTINFO_ADDR, Str_CAM_R, 9); 
		  if(TriggerFlag)
		  WriteStringToAddr(INPUTINFO_ADDR+8,"T" ,1); 
		  if(SEQFlag && !TriggerFlag)
		   	{
		   	 DrawAttrCnt(INPUTINFO_ADDR-3, Gauge_COLOR1, 2 );
	  		 WriteStringToAddr(INPUTINFO_ADDR-3,Str_reverse,2);  	 
		   	}

	 	}
	 else	
	 	{
	 #ifdef _MIRROR	
	 	 WriteTW88(TW88_WINBLENDING,0x04);	//wiliiam-v1.1-970827
	//   InitOSDWindow(Init_Osd_DisplayInput_M);
	   DrawAttrCnt(INPUTINFO_MIRROR_ADDR, DEFAULT_COLOR, 9 );    
	   DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Mirror_COLOR, 3 );
          DrawAttrCnt(INPUTINFO_MIRROR_ADDR, Trigger_COLOR, 1 );
          WriteStringToAddr(INPUTINFO_MIRROR_ADDR, Str_CAM_Mirror_R, len1); 
		  if(TriggerFlag)
		  WriteStringToAddr(INPUTINFO_MIRROR_ADDR,"T" ,1); 
		  if(SEQFlag && !TriggerFlag)
	   	       {
	   	        DrawAttrCnt(INPUTINFO_MIRROR_ADDR+10, Gauge_COLOR1, 2 );   
	   	        WriteStringToAddr(INPUTINFO_MIRROR_ADDR+10,Str_reverse,2);  
	 	       } 
	#endif	  
	 	}
 //    	}
 #if 0
    vloss_buf = ReadDecoder(0x01);	
   	   	if((vloss_buf&0x80)!=0x00) 
   	      {
   	   vloss_flag=1;
	   DrawAttrCnt(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4,Gauge_COLOR3,30); 
          	if(!mirror_flag)
              WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+9,Str_Mirror_Vloss,16);//william-v1.0-970725
	       else
   	       WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+8,Str_Vloss,10);//william-v1.0-970725
   	       }
   	 else 
	vloss_flag=0;
#endif

	 break;
}		
////////////////////////////////////////////////////////////////////////////////////////
   // DrawAttrCnt(INPUTINFO_ADDR, Gauge_COLOR1, 51 );    
   // WriteStringToAddr(INPUTINFO_ADDR, struct_InputSelection[i].Name, len1); 
//    ShowOSDWindow(INPUTINFO_OSDWIN-1,TRUE);
   // ShowOSDWindowAll(1);//0x09c  第4bit : OSD ON, 1: OSD OFF
   // DisplayedOSD |= INPUTINFO;

#ifdef _gauge
if(CkTMode==REVERSE_TRIG && ReadEEP(EEP_GAUGEMode)==0 ) 
{
   DrawAttrCnt(GAUGEINFO_ADDR,Gauge_COLOR1,40);       
   WriteStringToAddr(GAUGEINFO_ADDR+5,GaugeString,/*22*/19);//william-v1.0-970724
   WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH+4,GaugeString5,/*23*/20);//william-v1.0-970724

   DrawAttrCnt(GAUGEINFO_ADDR+INPUTINFO_WIDTH,Gauge_COLOR2,80);   
   WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*2+3,GaugeString3,3);
   WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*2+/*26*/23,GaugeString4,3);
   if(mirror_flag)
   WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*3+2,GaugeString6,/*27*/24); //william-v1.0-970724
   else
   WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*3+2,GaugeString7,/*27*/24); //william-v1.0-970724

   DrawAttrCnt(GAUGEINFO_ADDR+INPUTINFO_WIDTH*3,Gauge_COLOR3,80);  
   WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+1,GaugeString3,3);
   WriteStringToAddr(GAUGEINFO_ADDR+INPUTINFO_WIDTH*4+/*28*/25,GaugeString4,3);
   //SetDisplayedOSD(GAUGEINFO);
}   
#endif
  
   ShowOSDWindow(RATINGINFO_OSDWIN,TRUE);
   ShowOSDWindowAll(1);  //0x09c  第4bit : OSD ON, 1: OSD OFF
   
   //displayhold_flag=0;
   //vlossflash_flag=0;

}
	#endif
#endif

BYTE ClearInput(void)
{
	ShowOSDWindowAll(0);
	ShowOSDWindow(INPUTINFO_OSDWIN-1,FALSE);
	//ShowOSDWindow(INPUTINFO_OSDWIN,FALSE);

	DisplayedOSD &= (~(INPUTINFO));
	#ifdef DEBUG_OSD
	Printf("\r\n++(ClearInput) & DisplayedOSD()=%bx",GetDisplayedOSD());
	#endif

	return 1;
//	ClearBlending();
}

BYTE ClearInput2s(void)
{
	///ShowOSDWindowAll(0);
	ShowOSDWindow(INPUTINFO_OSDWIN-1,FALSE);
	//ShowOSDWindow(INPUTINFO_OSDWIN,FALSE);

	//DisplayedOSD &= (~(INPUTINFO));
	#ifdef DEBUG_OSD
	Printf("\r\n++(ClearInput) & DisplayedOSD()=%bx",GetDisplayedOSD());
	#endif

	return 1;
}

BYTE ClearVlossOsd(void)
{
	//ShowOSDWindowAll(0);
	ShowOSDWindow(VLOSSINFO_OSDWIN-1,FALSE);
//	DisplayedOSD &= (~(VLOSSINFO));
	ClearDisplayedOSD(VLOSSINFO);
	#ifdef DEBUG_OSD
	Printf("\r\n++(ClearVlossOsd) & DisplayedOSD()=%bx",GetDisplayedOSD());
	#endif

	return 1;
}
void DisplayVol(void)
{
	BYTE CODE *Str ;
	BYTE len;

	#ifdef Hs_debug
	Printf("\r\n++(DisplayVol)");
	#endif

	WriteDecoder(0xff, 0x01);
	Wait_ms(5);
	//	WriteDecoder(0x82, 0x0c);
	WriteDecoder(0x82, 0x01);
	Wait_ms(5);
	WriteDecoder(0xff, 0x00);
	
	if(( DisplayedOSD & TVVOL ) == 0 ) 
	{
		ClearOSDInfo();
		#ifdef REFERENCE
		Change_OSDColorLookup();
		#endif
		delay(10);

		InitOSDWindow(Init_Osd_BarWindow);

		ClearDataCnt(OSDMENU_BARADDR, 50); // Total 25*2 Char.
		DrawAttrCnt(OSDMENU_BARADDR, BG_COLOR_CYAN | CH_COLOR_WHITE, 25 );	 
		#ifdef TW8816
		DrawAttrCnt(OSDMENU_BARADDR+21, BG_COLOR_WHITE | CH_COLOR_CYAN, 25 );
		#else
		DrawAttrCnt(OSDMENU_BARADDR+25, BG_COLOR_WHITE | CH_COLOR_CYAN, 25 );
		#endif
#ifdef E_Wintek
		Str = StrVolume2[GetOSDLang()];
#else
		Str = StrVolume[GetOSDLang()];
#endif
		len=CStrlen(Str);
		WriteStringToAddr(OSDMENU_BARADDR, Str, len);  

		ShowOSDWindow(OSDBARWINDOW,TRUE);
		ShowOSDWindow(DVRStatus_OSDWIN,FALSE);
		ShowOSDWindowAll(1);
	}
	//if((NowModeState==SelectMode&&SelectModeType==VGAMode)||(NowModeState==JumpMode&&((ReadEEP(EEP_JUMPMode)==14)||SelectModeType==VGAMode)))		//william-v1.1-20110114
	if(VGAAudio)
		DisplayVolumebar(PCAudioVol);
	else	
		DisplayVolumebar(AudioVol);

	DisplayedOSD |= TVVOL;
	OSDDisplayedTime = GetTime_ms();
}

#if 0
void DisplayBrightness(void)
{
	BYTE CODE *Str ;
	BYTE len;

	//#ifdef DEBUG_OSD
	Printf("\r\n++(DisplayBrightness)");
	//#endif
	
	if(( DisplayedOSD & TVCHN ) == 0 ) 
	{

	ClearOSDInfo();
	#ifdef REFERENCE
	Change_OSDColorLookup();
	#endif
	delay(10);


	InitOSDWindow(Init_Osd_BarWindow);

	ClearDataCnt(OSDMENU_BARADDR, 50); // Total 25*2 Char.
	DrawAttrCnt(OSDMENU_BARADDR, BG_COLOR_CYAN | CH_COLOR_WHITE, 25 );	 
	DrawAttrCnt(OSDMENU_BARADDR+25, BG_COLOR_WHITE | CH_COLOR_CYAN, 25 );
#ifdef E_Wintek
	Str = Str_Brightness[GetOSDLang()];
#else
	Str = Str_Brightness[GetOSDLang()];
#endif
	len=CStrlen(Str);
	WriteStringToAddr(OSDMENU_BARADDR, Str, len);  

	ShowOSDWindow(OSDBARWINDOW,TRUE);
	ShowOSDWindow(DVRStatus_OSDWIN,FALSE);
	ShowOSDWindowAll(1);

	}
	//if(VGAAudio)
	//DisplayVolumebar(PCAudioVol);
	//else	
	DisplayVolumebar(GetItemValue(VIDEO_BRIGHTNESS));

	DisplayedOSD |= TVCHN;
	OSDDisplayedTime = GetTime_ms();

}
#endif
#if 0
void DisplayMuteInfo(void)
{
	BYTE CODE	*Str ;
	BYTE len;
	extern CODE BYTE Init_Osd_DisplayMuteInfo[];
	extern CODE BYTE *MuteOnStr[];

	ClearOSDInfo();
	InitOSDWindow(Init_Osd_DisplayMuteInfo);

	Str = MuteOnStr[GetOSDLang()];
	len = strlen(Str);
	WriteStringToAddr(MUTEINFO_ADDR, Str, len);  
	DrawAttrCnt(MUTEINFO_ADDR, BACK_COLOR|CH_COLOR_RED, len );	 

	ShowOSDWindow(TVINFO_OSDWIN,TRUE);
	ShowOSDWindowAll(1);
	DisplayedOSD |= MUTE;
}
#endif
void ClearMuteInfo(void)
{
	ShowOSDWindow(TVINFO_OSDWIN,FALSE);
	DisplayedOSD &= (~(MUTE));
}

BYTE CheckAndClearOSD(void)
{
	WORD	ctime,  stime, diff;
	BYTE	dt;
	BYTE	Result=0;

	dt = GetDisplayedOSD();
	if ( dt & ( MENU | INPUTINFO | TVVOL |TVCHN) ) {

		if( dt & MENU )	{ 
			stime = GetOSDLastKeyInTime();	
			diff =  20 * 100; //GetOSDDuration()
		}
		else { 
			stime = OSDDisplayedTime;	
			diff = 2 * 100;	
		}
	
		ctime = GetTime_ms();			

		if( DiffTime_ms( stime, ctime ) >= diff ) {

			if( dt & (TVVOL|TVCHN))	
			{
				#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
				cLastSyncLoss=0;		//pc mode update SyncLoss
				#endif
				Result = ClearTVInfo();
				DisplayInput();

				#ifdef AWT_NO_SIGNAL_MSG  //ryan@20170906
				IsDrawNoVideoSignal = 0;
				#endif
			
			}

			if( dt & MENU )			
			{
				#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
				cLastSyncLoss=0;		//pc mode update SyncLoss
				#endif
				Result = CloseOSDMenu();
			#if 1  //Pinchi 20150901 add to setup 2s for Display OFF
				if (ReadEEP(EEP_COSDMode) == 1)
					displayhold_flag = 3;
			#endif
				DisplayInput();
			#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
				IsDrawNoVideoSignal = 0;
			#endif
			}
		#if 0		//william-981029
			if( Result == 1){
				if( DisplayInputHold ) DisplayInput();
				else {

					if( IsAudioMuteOn() )	DisplayMuteInfo();
				}
			}
		#endif	
			
			return 1;
		}
	}

	return 0;
}

#if defined( SUPPORT_PC ) || defined (SUPPORT_TV)

void SetWindowStart(WORD x, WORD y)
{
	WriteDecoder(TW88_WINSTART_HI, (x>>8) | ((y>>8)<<4));
	WriteDecoder(TW88_WINXSTART, (BYTE)x);
	WriteDecoder(TW88_WINYSTART, (BYTE)y);
}
#endif

#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )

void SetWindowWidth(BYTE width)
{
	WriteDecoder(TW88_WINWIDTH, width);
}

void DisplayPCInfo(BYTE CODE *ptr)
{
	WORD xstart, ystart;
	BYTE len;

	#ifdef DEBUG_PC
	Printf("\r\n==== DisplayPCInfo (%s) ====", ptr);
	#endif

	Clear_bypass();								// HHY 1.52

	AutoPHPCalDisable();
	SetPHP( GetPHR() + 0x100 ); // for Sharp-NoTicon by RYU-101205	// Set PHP

	PanelFreeRun(1);							// FreeRun
	// WriteDecoder(0x06, 0x80);		// Soft Reset
	PanelBlack(1);

	len  = strlen(ptr);

	xstart = ( PHR_ - len*PCINFO_ZOOM*FONT_WIDTH ) / 2;
	ystart =  PVR_ / 3;
	
	InitOSDWindow(Init_Osd_DisplayPCInfo);
	SetWindowStart(xstart, ystart);
	SetWindowWidth(len);

	ClearDataCnt(PCMEASUREINFO_ADDR, len);
	DrawAttrCnt(PCMEASUREINFO_ADDR, CH_COLOR_RED,len);	 

	WriteStringToAddr(PCMEASUREINFO_ADDR, (BYTE CODE *)ptr, len);
	ShowOSDWindow(PCINFO_OSDWIN,TRUE);
	ShowOSDWindowAll(1);
	
	DisplayedOSD |=PCINFO;

}

void ClearPCInfo(void)
{
	if( !(DisplayedOSD & PCINFO) )		return;			//ljy070803

	DisplayedOSD &= (~(PCINFO));
	ShowOSDWindow(PCINFO_OSDWIN,FALSE);
	dPuts("\r\n== ClearPCInfo ==");

//	PanelMute(0);								// HHY 1.63
}

extern CODE BYTE AutoAdjustInfo[]; 

void DisplayAutoAdjust(void)
{
	InitOSDWindow(Init_Osd_BarWindow);
	ClearDataCnt(OSDMENU_BARADDR, 50); // Total 25*2 Char.
	DrawAttrCnt(OSDMENU_BARADDR, BG_COLOR_CYAN | CH_COLOR_WHITE, 50 );
	WriteStringToAddr(OSDMENU_BARADDR, AutoAdjustInfo, 25);
	ShowOSDWindow(OSDBARWINDOW,TRUE);
	ShowOSDWindowAll(1);
}
void ClearAutoAdjust(void)
{
	ShowOSDWindow(OSDBARWINDOW,FALSE);
}

#endif	// SUPPORT_PC

//==================================================================
//						TV Info
//==================================================================

BYTE ClearTVInfo(void)
{
	
	if( DisplayedOSD & TVVOL )		
	{	
		#ifdef AWT_ML072S///修正disable時會有雜點出現ryan@20171214
		ShowOSDWindowAll(0);   
		#endif
		ShowOSDWindow(OSDBARWINDOW, FALSE);
		DisplayedOSD &= (~(TVVOL));


	}
	else
	{
		ShowOSDWindow(TVINFO_OSDWIN, FALSE);
		DisplayedOSD &= (~(TVCHN));
	}
	#ifndef QUAD
	CheckMirror();
	#endif
	return 1;
}


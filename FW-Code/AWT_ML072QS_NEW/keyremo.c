//
// KeyRemo.h
// Default function for Key Input and Remocon Input
//
//=============================================================================
//		                    Operation Key Mapping
//=============================================================================
#include "config.h"
#include "typedefs.h"
#include "keyremo.h"
#include "measure.h"
#include "audio.h"
#include "dispinfo.h"
#include "main.h"
#include "i2c.h"
#include "osdmenu.h"
#include "debug.h"
#include "cpu.h"
#include "printf.h"
#include "regmap.h"
#include "reg.h"
#include "etc_eep.h"
#include "osdbasic.h"
#include "HS_keyremo.h"
#include "HS_DisplayOSD.h"
#include "HS_DVRProtocol.h"
#include "HS_IOdef.h"
#include "audio.h"


bit CAM_PTZ_RUN_flag;
BYTE lock_keycnt; 
BYTE KeyBuffer=0;
BYTE LockKeyState=0; 
BYTE BookMarkState=0;
BYTE DayNightLevel=0;

BYTE Disp_Input=0;//ryan@21071019

BYTE TR_JUMP_Flag=0;//ryan@20170912
BYTE TR_JUMP_HOLD=0;//ryan@20170912
BYTE RELEASE_TR_JUMP_Flag=0;//ryan@20170912

BYTE OSD_LOCKF=0;//ryan@21071018
	
extern bit SpeedDomeMode;
extern bit OnChangingValue;
extern bit RepeatKey;
extern bit Init_DisplayInput;
#ifdef SUPPORT_DEBUG
extern  bit Debug_On;
#endif
extern  BYTE  PcMode;
extern  		WORD  OSDLastKeyInTime;		// in ms
//extern   		bit   DisplayInputHold;		//william-981029
extern  DATA  WORD  tic_pc;
extern  		bit KeyReady;
extern  DATA BYTE Key;
extern  BYTE 	keyticSec;
#ifdef REMO_RC5
extern   BYTE	RemoDataReady;
#endif
extern BYTE RemoSystemCode, RemoDataCode;
//#ifdef Format_SDCard
extern BYTE FormatSDCard;
//#endif
extern	bit	ChannelEdit_Flag;
extern 	bit	ChannelEdit_on;
extern 	bit	GetDVRStatusflag;
extern 	BYTE    OSDMenuLevel;
#ifdef E_Wintek
extern	bit	FactoryMenu;
#endif
extern BYTE  updn_reg[4];
extern bit ChangeKey;

extern bit  IsDrawNoVideoSignal;//ryan@20170922

#ifdef HTRV  //Pinchi 20150825 add model #define
extern BYTE GaugeVStart;

BYTE GaugeSetup =0;
BYTE GaugeInfoOSD =0;
#endif

#ifdef SUPPORT_2835_CLK_TUNE_BACK_DOOR  //Pinchi 20160929 add
DATA bit IsRun2835ClkTune=0;
DATA BYTE b2835ClkTuneVal=0;

DATA bit IsEnter2835ClkTune=0;
DATA DWORD Enter2835TuneClock;
extern DATA DWORD SystemClock;

void HS_Display2835ClkTuneVal(WORD val);
extern CODE BYTE Init_Osd_DisplayInput_B[];
#endif

#ifdef HS_NEWOSDMENU
void RemoMenu_MenuKey(BYTE isREMOTE)
{
	if(GetDisplayedOSD() & MENU) 	
		OSDHighMenu();       
	else
		{
		/*	//Weylis -@121008 
		//FMONFLG = 3;
		if(GetInputSelection()== soDVDAV || GetInputSelection()== soCOMPONENT)
			{
				if(isREMOTE)
					OpenOSDMenu(1);
				else
					OpenOSDMenu(0);
			}
		else
		*/
			OpenOSDMenu(1);
		}
}
#else 
void RemoMenu_MenuKey(void)
{


		
	if(  GetDisplayedOSD() & MENU  ) 		OSDHighMenu();
	else
		{
		#ifdef AWT_ML072S
		ClearOSDInfo();
		WriteDecoder(0xff, 0x01);
		Wait_ms(5);
	 	WriteDecoder(0x82, 0x01);////normal mode
		Wait_ms(5);
		WriteDecoder(0xff, 0x00);
		#endif
		
		OpenOSDMenu();
		}
}
#endif

void RemoChnUp_UpKey(void)
{
	#ifdef SUPPORT_DEBUG
	if( Debug_On ) {
		DebugWindowData(UP);
		return;
	}
	else 
	#endif	
	if( GetDisplayedOSD() & MENU  )	
		#ifdef PAL_TV
		if( ChannelEdit_Flag) {
			if( ChannelEdit_on )					ChannelEdit_Char(UP);
			else {		
				UpDownTVChannel(DN);
				ChannelEdit_display();
			}
		}
		else
		#endif	
		OSDCursorMove(UP);	
	#ifdef SUPPORT_PC
	else if( GetInputSelection()==PC )		AutoAdjust();
	#endif
	else	
		return;
}

void RemoChnDn_DnKey(void)
{
	#ifdef SUPPORT_DEBUG
	if( Debug_On ) {
		DebugWindowData(DN);
		return;
	}
	else 
	#endif	
	if( GetDisplayedOSD() & MENU  ) {
		OSDCursorMove(DN);	
	}
	else
		#ifdef SUPPORT_LINE_OSDDEMO
		DisplayLineOSD();
		#endif
		return;
}

void RemoVolUp_RightKey(void)
{
	#ifdef SUPPORT_DEBUG
	if( Debug_On ) {
		DebugWindowCursor(UP);
		return;
	}
	else 
	#endif	
	if(  GetDisplayedOSD() & MENU  ) {
		if( OnChangingValue ) 					OSDValueUpDn(UP );
		else										OSDSelect();			
	}
	else //if(GetDisplayedOSD() & TVVOL)
	{
	#ifdef HTRV  //Pinchi 20150827 add
	    if(GaugeSetup)//william-v1.43-970319
			OSDValueUpDn(UP );	
		else
	#endif
		{
			ChangeVol(1);
			DisplayVol();
		}
	}
}

void RemoVolDn_LeftKey(void)
{
	#ifdef SUPPORT_DEBUG
	if( Debug_On ) {
		DebugWindowCursor(DN);
		return;
	}
	else 
	#endif
	if(  GetDisplayedOSD() & MENU  ) 
		{
		if( OnChangingValue )						
			OSDValueUpDn(DN );
		else 
			OSDHighMenu();	
		}
	else //if(GetDisplayedOSD() & TVVOL)
	{
	#ifdef HTRV  //Pinchi 20150827 add
	    if(GaugeSetup)//william-v1.43-970319
			OSDValueUpDn(DN);	
		else
	#endif
		{
			ChangeVol(-1);
			DisplayVol();
		}
	}
}

//=============================================================================
//
//=============================================================================
BYTE ActionRemo(BYTE _RemoDataCode, BYTE AutoKey)
{
	SetOSDLastKeyInTime();
	
	 #if (defined SUPPORT_PC) || (defined SUPPORT_DTV) 	
     #if 0//andy ML084 980930
	  if( (PcMode==EE_PC_NO_SIGNAL) && (GetInputSelection()==PC || GetInputSelection()==DTV) ) {
		 if( PcMode==EE_PC_NO_SIGNAL ) {
			 switch (_RemoDataCode) {
			   case REMO_INPUT:
			 //case REMO_STANDBY:	
			 break;
				
			default:
				tic_pc = 0;
				return 1;
			}
		}
	}
     #endif
	#endif // SUPPORT_PC

	switch(_RemoDataCode) {

	case REMO_STANDBY:				// power
		#ifdef DEBUG_KEYREMO
		dPrintf("\r\nSTANDBY Mode, Autokey:%02x", AutoKey);
		#endif
		OSDLastKeyInTime = 0xffff;
		if( AutoKey ) return 1;
		return 0;					// power off

	case REMO_MUTE:
		#if 0
		#ifdef DEBUG_KEYREMO
		dPrintf("\r\nMUTE Mode, Autokey:%02x", AutoKey);
		#endif
		if( AutoKey ) return 1;
		ToggleAudioMute();
		if( IsAudioMuteOn() )		DisplayMuteInfo();
		else{						
			ClearMuteInfo();
			//if( DisplayInputHold ) DisplayInput();		//william-981029
		}
		#endif
		break;

	case REMO_INPUT:
		#ifdef DEBUG_KEYREMO
		dPrintf("\r\nChange INPUT, Autokey:%02x", AutoKey);
		#endif
		ChangeInput(GetNextInputSelection());
		return 1;

	case REMO_INFO:
		#ifdef DEBUG_KEYREMO
		dPrintf("\r\nINFO display, Autokey:%02x", AutoKey);
		#endif
		if( GetDisplayedOSD() & INPUTINFO )	ClearInput();
		else		DisplayInput();
		return 1;

	case REMO_NUM0:
	case REMO_NUM1:
	case REMO_NUM2:
	case REMO_NUM3:
	case REMO_NUM4:
	case REMO_NUM5:
	case REMO_NUM6:
	case REMO_NUM7:
	case REMO_NUM8:
	case REMO_NUM9:
		#ifdef DEBUG_KEYREMO
		dPrintf("\r\nNumber %02x Key Pressed, Autokey:%02x", (_RemoDataCode-0x30), AutoKey);
		#endif
		if( AutoKey )								return 1;

		else										return 1;
		break;

	case REMO_CHNUP:
		#ifdef DEBUG_KEYREMO
		dPuts("\r\nChannel UP");
		#endif
		RemoChnUp_UpKey();
		break;
	
	case REMO_CHNDN:
		#ifdef DEBUG_KEYREMO
		dPuts("\r\nChannel DOWN");
		#endif
		RemoChnDn_DnKey();
		break;
	
	case REMO_SELECT:
		#ifdef DEBUG_KEYREMO
		dPrintf("\r\nSELECT key pressed, Autokey:%02x", AutoKey);
		#endif
		if( AutoKey ) return 1;
		if(  GetDisplayedOSD() & MENU  )		{
				OSDSelect();
		}
		break;

	case REMO_VOLUP:
		#ifdef DEBUG_KEYREMO
		dPuts("\r\nVolumn UP");
		#endif
		RemoVolUp_RightKey();
		break;
	case REMO_VOLDN:
		#ifdef DEBUG_KEYREMO
		dPuts("\r\nVolumn DOWN");
		#endif
		RemoVolDn_LeftKey();
		break;


	case REMO_MENU:
		#ifdef DEBUG_KEYREMO
		dPrintf("\r\nMENU display, Autokey:%02x", AutoKey);
		#endif
		if( AutoKey ) return 1;
	#ifdef HS_NEWOSDMENU	
		RemoMenu_MenuKey(1);
	#else
		RemoMenu_MenuKey();
	#endif
		break;

	case REMO_EXIT:
		#ifdef DEBUG_KEYREMO
		dPuts("\r\n EXIT");
		#endif
		if(  GetDisplayedOSD() & MENU  )		
			DoAction(EXITMENU);
		break;

	#ifdef SUPPORT_PC
	case REMO_AUTO:
		#ifdef DEBUG_KEYREMO
		dPuts("\r\n AUTO mode adjust for PC input");
		#endif
		if( GetInputSelection()==PC )
			AutoAdjust();
		break;
	#endif

	#ifdef WIDE_SCREEN
	case REMO_ASPECT:
		#ifdef DEBUG_KEYREMO
		dPuts("\r\n Screen Aspect Ratio change to WIDE");
		#endif
		SetItemValue(WIDESCREEN,UP);
		break;
	#endif
	}

	#ifdef SUPPORT_DEBUG
	switch(_RemoDataCode) {		
	case REMO_DEBUG:		DebugWindowControl();		break;
	case REMO_READ:			Debug_Read();		break;
	case REMO_WRITE:		Debug_Write();	
							Debug_Read();	// Read back
												break;
	}
	#endif

	return 1;
}

BYTE CheckKeyIn(void)
{
	BYTE ret=1, ikey,OSD_LOCK;

#ifdef SUPPORT_2835_CLK_TUNE_BACK_DOOR	//Pinchi 20160929 add
	if ((IsEnter2835ClkTune == 1) && (IsRun2835ClkTune == 0))
	{
		if ((SystemClock - Enter2835TuneClock) >= 10)
			IsEnter2835ClkTune = 0;
	}
#endif
		
	if( (ikey = GetKey(1)) ) 
	{
		#ifdef Hs_debug//ryan@20171002

		switch (ikey) {
			case POWERKEY: Printf("\r\nPOWER key pressed"); break;
			case MENUKEY: Printf("\r\nMENU key pressed"); break;
			case INPUTSOURCEKEY: Printf("\r\nINPUTSOURCE key pressed"); break;
			case UPKEY:	 Printf("\r\nUP key pressed"); break;
			case DOWNKEY: Printf("\r\nDOWN key pressed"); break;
            case SELECTKEY: Printf("\r\nSELECTKEY key pressed"); break;//Printf("\r\nSELECTKEY key pressed"); break;
			default: Printf("\r\nNOT ASSIGNED key pressed"); break;
		}		
  		#endif

	 //   if(TriggerFlag&&(ikey!=INPUTSOURCEKEY))     //判斷是否進入Tigger Mode
	   // { 
	     // ikey=0;
	     // return 1;
	   // }
		
	//mask by ryan@20171018	OSD_LOCK = ReadEEP(EEP_ONOFFChoice);
	OSD_LOCK=OSD_LOCKF;

		
	#ifdef AWT_NEW_SLIM_MODEL  //Pinchi 20150203 add for AWT new slim model
		if (((~P2 & UnLockKEY) == UnLockKEY) && (OSD_LOCK == 0))   //	解osd lock
	#else
		if((~P2&0x90)==0x90 && OSD_LOCK==0)   //	解osd lock
	#endif
		{ 
			Wait_ms(2000);
		#ifdef AWT_NEW_SLIM_MODEL  //Pinchi 20150203 add for AWT new slim model
			if (((~P2 & UnLockKEY) == UnLockKEY) || (LockKeyState == 3))
		#else
			if((~P2&0x90)==0x90||LockKeyState==3)
		#endif
			{
				WriteEEP(EEP_ONOFFChoice,0x01);
				OSD_LOCK=1;//ryan@20170908
				OSD_LOCKF=1;
				DisplayInformation(InfoOSDMENUATCIVE);
				ikey=0;
				Wait_ms(2000);

				if(TriggerFlag&0x20)//if rear trigger
				{
				DisplayGaugeOSD();
				}
				else
				{
				ClearGAUGEINFO();
				lock_keycnt=0;
				LockKeyState=0;
				DisplayInput();
			
				}
				
			
			#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
			IsDrawNoVideoSignal = 0;
			#endif
			
			//	return 1;  //Pinchi 20150825 add  //Pinchi 20150825 disable
			}
		}

	    if(TriggerFlag&&(ikey!=INPUTSOURCEKEY))     //判斷是否進入Tigger Mode
	    { 
	      ikey=0;
	      return 1;
	    }
	
	#ifndef AWT_ML072Q  //Pinchi 20140911 add for AWT ML072Q
		if(LockKeyState==3 && OSD_LOCK==0)
		{
			WriteEEP(EEP_ONOFFChoice,0x01);
			OSD_LOCKF=1;
			DisplayInformation(InfoOSDMENUATCIVE);
			Wait_ms(2000);
			//lock_keycnt=0;
			DisplayInput();
			LockKeyState=0;
			PowerLED(ON);
			
			#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
			IsDrawNoVideoSignal = 0;
			#endif
		}
	#endif

		if(lock_keycnt==0 && OSD_LOCK==0 && LockKeyState!=0)
		{
			LockKeyState=0;
			PowerLED(ON);
		}

 
	#ifdef AWT_ML072Q  //Pinchi 20140918 add for AWT ML072Q
	  #ifdef AWT_NEW_SLIM_MODEL  //Pinchi 20150203 add for AWT new slim model
		if (ikey && (OSD_LOCK == 0) && ((~P2 & UnLockKEY) != UnLockKEY))
	  #else
		if (ikey && (OSD_LOCK == 0) && ((~P2 & 0x90) != 0x90)&&(TriggerFlag==0))
	  #endif
		{
			ClearOSDInfo();//ryan@20170922
			DisplayInformation(InfoOSDMENULOCKED);
			delay(500);
			ClearGAUGEINFO(); 
			DisplayInput();
			#ifdef Hs_debug
			Printf("\r\n***OSD_LOCK",0);
			#endif
								#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
								IsDrawNoVideoSignal = 0;
								#endif
			return 1;
		}
	#endif

	#ifdef AWT_ML072S ////add by ryan@20171212 
		if (ikey && (OSD_LOCK == 0) && ((~P2 & 0x90) != 0x90)&&(TriggerFlag==0))
		{
			ClearOSDInfo();
			DisplayInformation(InfoOSDMENULOCKED);
			delay(500);
			ClearGAUGEINFO(); 
			DisplayInput();
			#ifdef Hs_debug
			Printf("\r\n*****OSD_LOCK",0);
			#endif
								#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150320 add
								IsDrawNoVideoSignal = 0;
								#endif
			return 1;
		}
	#endif
	
		SetOSDLastKeyInTime();

		switch( ikey ) {
			case  POWERKEY :
				Printf("\r\nPOWER key ");
			#ifdef SUPPORT_2835_CLK_TUNE_BACK_DOOR	//Pinchi 20160929 add
				if (IsRun2835ClkTune == 1)
				{
					if (b2835ClkTuneVal >= 15)
						b2835ClkTuneVal = 0;
					else
						b2835ClkTuneVal++;

					switch(b2835ClkTuneVal)
					{
						case 0 :
						default :
							TW2835Cmd("\n\rbusw 0 1 7E 80\r\n");
							break;

						case 1 :
							TW2835Cmd("\n\rbusw 0 1 7E 81\r\n");
							break;

						case 2 :
							TW2835Cmd("\n\rbusw 0 1 7E 82\r\n");
							break;

						case 3 :
							TW2835Cmd("\n\rbusw 0 1 7E 83\r\n");
							break;

						case 4 :
							TW2835Cmd("\n\rbusw 0 1 7E 84\r\n");
							break;

						case 5 :
							TW2835Cmd("\n\rbusw 0 1 7E 85\r\n");
							break;

						case 6 :
							TW2835Cmd("\n\rbusw 0 1 7E 86\r\n");
							break;

						case 7 :
							TW2835Cmd("\n\rbusw 0 1 7E 87\r\n");
							break;

						case 8 :
							TW2835Cmd("\n\rbusw 0 1 7E 88\r\n");
							break;

						case 9 :
							TW2835Cmd("\n\rbusw 0 1 7E 89\r\n");
							break;

						case 10 :
							TW2835Cmd("\n\rbusw 0 1 7E 8A\r\n");
							break;

						case 11 :
							TW2835Cmd("\n\rbusw 0 1 7E 8B\r\n");
							break;

						case 12 :
							TW2835Cmd("\n\rbusw 0 1 7E 8C\r\n");
							break;

						case 13 :
							TW2835Cmd("\n\rbusw 0 1 7E 8D\r\n");
							break;

						case 14 :
							TW2835Cmd("\n\rbusw 0 1 7E 8E\r\n");
							break;

						case 15 :
							TW2835Cmd("\n\rbusw 0 1 7E 8F\r\n");
							break;
					}

					HS_Display2835ClkTuneVal(b2835ClkTuneVal);
				}
				else
			#endif
				{
				
					if(SpeedDomeMode==0)
					{
						if(TriggerFlag==0x00)
						{
							//ret = ActionRemo( REMO_STANDBY, RepeatKey );
							ret = ActionRemo( REMO_STANDBY, 0 );
							PowerFlag=0;
							//Hs_DvrTxCmdPaser(Halt_Start);
		                	WriteEEP(EEP_Powerflag,PowerFlag);//2007.3.28 Justin
						}
					}
					else
					{
						SpeedDomeMode=0;
						//RS232Select=0;
						//ClearDataCnt(INPUTINFO_ADDR,19);
						//DrawAttrCnt(INPUTINFO_ADDR,0x00,19); 
						DisplayInput();
					}
				}
                break;

			case MENUKEY:
				Printf("\r\nMENUKEY key ");
				//Printf("\r\nSpeedDomeMode=%02x",(WORD)SpeedDomeMode);
			#ifdef SUPPORT_2835_CLK_TUNE_BACK_DOOR	//Pinchi 20160929 add
				if (IsRun2835ClkTune == 1)
				{
					HS_Display2835ClkTuneVal(b2835ClkTuneVal);
				}
				else
			#endif
				{
				#ifdef HTRV
					if(GaugeInfoOSD)
					{
						GaugeInfoOSD =0;
						GaugeSetup=0;
						WriteDecoder(0x0a,0x16); ///_FULLPANEL_20140313_xx
						WriteDecoder(0x61,0x80);
						WriteDecoder(0x66,0x00);

						SelectModeType = ReadEEP(EEP_SelectMode);

	 					////	SelectModeType = CAM_A;
						ClearOSDInfo();
						CloseOSDMenu();

					#if 0  //Pinchi 20150901 add to setup 2s for Display OFF
						if (ReadEEP(EEP_COSDMode) == 1)
							displayhold_flag = 3;
					#endif
	                   	break;
				    }
				#endif

					if(SpeedDomeMode==0)
					{
					#ifdef AWT_ML072S//Pinchi 20150825 modify //ndef AWT_ML072Q  //Pinchi 20140918 add for AWT ML072Q
						if(SEQFlag)
						{
						;  
						}
						else	if(OSD_LOCK==0)
						{
							//DisplaylockOSD();
							DisplayInformation(InfoOSDMENULOCKED);
							delay(500);
							ClearGAUGEINFO(); 
							DisplayInput();
							Printf("\r\n *OSD_LOCK",0);
						}
						else
					#else ////AWT_ML072S
						 if(OSD_LOCK==0)
						{
							//DisplaylockOSD();
							DisplayInformation(InfoOSDMENULOCKED);
							delay(500);
							ClearGAUGEINFO(); 
							DisplayInput();
							Printf("\r\n *OSD_LOCK",0);
						}
						else				
					#endif
						{
				            if(  GetDisplayedOSD() & MENU  ) 
				            {
				                if( OnChangingValue )
									ret = ActionRemo( REMO_MENU, 0 );
									//ret = ActionRemo( REMO_MENU, RepeatKey );
								else
								 	OSDSelect();
				            }
							else if( GetDisplayedOSD() & TVVOL)
							{
								//ClearOSDInfo();
							//	CloseOSDMenu();
								//DisplayInput();
								;
							}
	
							else 
							{
								//#ifdef Format_SDCard
							#ifdef SUPPORT_SDCARD  //Pinchi 20140918 add
								if(FormatSDCard>=60)
								{
									//OpenFORMATMenu();
									FormatSDCard=0;
									ClearOSDInfo();
		   							//ClearDataCnt(GAUGEINFO_ADDR,30*5);
								}

								WriteDecoder(0xff, 0x01);
								Wait_ms(5);
		 						//WriteDecoder(0x82, 0x0c);
		 						WriteDecoder(0x82, 0x01);
								Wait_ms(5);
								WriteDecoder(0xff, 0x00);
								//Printf("\r\nwilliam_test",0);
								//Wait_ms(2000);
							#endif
								ret = ActionRemo( REMO_MENU, 0 );  
							}
						}
					}
					else
					{
						CAM_TxCommand_toRS485(CAM_Iris_Open);
						CAM_PTZ_RUN_flag = 1;
					}
				}
				break;

			//------------------------------------------------------------------------		
			
			case UPKEY:
				if(SpeedDomeMode==0)
				{
					if(  GetDisplayedOSD() & MENU  ) 
					{
						if( OnChangingValue )				
							OSDValueUpDn(UP );
						else		
						{
							//if(OSDMenuLevel == 1||OSDMenuLevel == 2)
							//   OSDCursorMove( DN);
							//else	
							   OSDCursorMove( UP );
						}
					}
					else	
					{
						#ifdef Hs_debug
						Printf("\r\nREMO_VOLUP",0);
						#endif
						#ifdef AWT_ML072S
						if(GetDisplayedOSD()&INPUTINFO)ClearOSDInfo();
						#endif						
	                    ret=ActionRemo(REMO_VOLUP,0);
						return 1;
					}
				}
				else
				{
					CAM_TxCommand_toRS485(CAM_PTZ_UP);
					CAM_PTZ_RUN_flag = 1;

				}
				break;
		
			case DOWNKEY:
				if(SpeedDomeMode==0)
				{
					if(  GetDisplayedOSD() & MENU  )
					{
						if( OnChangingValue )				
							OSDValueUpDn(DN );
						else		
						{
							//if(OSDMenuLevel == 1||OSDMenuLevel == 2)
							//   OSDCursorMove( UP);
							//else	
							OSDCursorMove( DN);
						}
					}
					else
					{
						#ifdef Hs_debug
						Printf("\r\nREMO_VOLDN",0);
						#endif
						#ifdef AWT_ML072S
						if(GetDisplayedOSD()&INPUTINFO)ClearOSDInfo();
						#endif
                    			ret=ActionRemo(REMO_VOLDN,0);
						return 1;
					}
				}
				else
				{
					CAM_TxCommand_toRS485(CAM_PTZ_DOWN);
					CAM_PTZ_RUN_flag = 1;

				}
				break;

			case SELECTKEY:
				if(SpeedDomeMode==0)
				{
					if((SelectModeType == AVMode)&&(GetDisplayedOSD() & MENU))
					CloseOSDMenu();

					if(GetDisplayedOSD() & INPUTINFO)
								ClearInput();
					
					SetSelectMode();
				}
				else
				{
					CAM_TxCommand_toRS485(CAM_PTZ_LEFT);
					CAM_PTZ_RUN_flag = 1;

				}
				break;

			//------------------------------------------------------------------------		

			case INPUTSOURCEKEY:
				
					if((TriggerFlag)&&(Priority==0))//ryan@20170907
					{
						//not change state... ryan@20170914
						;//Printf("\r\n*INPUTSOURCEKEY* Priority=%02x", (WORD)Priority);
					}
				else if(TriggerFlag&&(TR_JUMP_Flag==0)&&(Priority==1))
					{					
					if(ReadEEP(EEP_ONOFFChoice)==1)//unlock key work
					{
					if((TriggerFlag&0x20))
					 ClearGAUGEINFO();					 

						TR_JUMP_Flag=1;
						
					if(RELEASE_TR_JUMP_Flag==0) TR_JUMP_HOLD=NowModeState;					

					RELEASE_TR_JUMP_Flag=1;
					
					NowModeState=JumpMode;

					SetJumpMode();		
					}
					
					}
				else if(SpeedDomeMode==0)
				{
				
					if(TR_JUMP_Flag)
					{
				    TriggerFlag=0;			
				    TriggerMode=No_TRIG;
					TR_JUMP_Flag=0;
					NowModeState=SelectMode;
				//Printf("\r\n((SelectModeType=%02x    NowModeState=%02x))",(WORD)SelectModeType,(WORD)NowModeState);
					}
					else
					{


	if((SelectModeType == AVMode)&&(GetDisplayedOSD() & MENU))
			CloseOSDMenu();
					
					
						if(NowModeState==SelectMode)
						NowModeState=JumpMode;
						else
						NowModeState=SelectMode;
						
                				SetJumpMode();
						
					}
				}
				else
				{
					CAM_TxCommand_toRS485(CAM_PTZ_RIGHT);	
					CAM_PTZ_RUN_flag = 1;

				}
			break;

		#ifdef QUAD
			case  EVENTKEY:
				Printf("\r\nEVENTKEY key pressed");
		////	Hs_DvrTxCmdPaser(BOOKMARK);				
               	break;
		#endif

		#ifdef SUPPORT_SDCARD  //Pinchi 20160929 disable for no DVR function
			case VersionKEY:
				#ifdef E_Wintek
				FactoryMenu=1;
				#endif
				Printf("\r\nVersionKEY key pressed");
			#ifdef SUPPORT_SDCARD	
				if(DVR_Ready)
				{
				#if  1
					if(AudioVol==15)
					{
						Hs_DvrTxCmdPaser(GetDVRVersion);
					}
					#ifndef SUPPORT_SDCARD
					else
						DisplayDVRStatus();
					#endif
				#endif
				}
			#else
				if(AudioVol==15)
				{
					WriteDecoder(0xff, 0x01);
					Wait_ms(5);
					//WriteDecoder(0x82, 0x0c);
					WriteDecoder(0x82, 0x01);
					Wait_ms(5);
					WriteDecoder(0xff, 0x00);
					DisplayFWVersion();
				}
			#endif
				//else
				//	{
				//	CloseOSDMenu();	
				//	DisplayInput();
				//	}
				break;
		#endif

		#ifdef SUPPORT_2835_CLK_TUNE_BACK_DOOR  //Pinchi 20160929 add
			case Tune2835ClkKEY :
				if ((AudioVol == 20) && (IsEnter2835ClkTune == 1))
				{
					if (IsRun2835ClkTune == 1)
					{
						IsRun2835ClkTune = 0;
						PowerLED(ON);
						ClearDataCnt(INPUTINFO_ADDR, 2);
						IsEnter2835ClkTune = 0;
					}
					else
					{
						IsRun2835ClkTune = 1;
						PowerLED(2);
						HS_Display2835ClkTuneVal(b2835ClkTuneVal);
					}

					Printf("\r\n[MSG]CheckKeyIn()=> IsRun2835ClkTune=%bx",(BYTE)IsRun2835ClkTune);
				}
				break;

			case Enter2835TuneKEY :
				if (AudioVol == 23)
				{
					PowerLED(2);
					Wait_ms(100);
					PowerLED(ON);
					Wait_ms(100);
					PowerLED(2);
					Wait_ms(100);
					PowerLED(ON);
					Wait_ms(100);
					PowerLED(2);
					Wait_ms(100);
					PowerLED(ON);
					IsEnter2835ClkTune = 1;
					Enter2835TuneClock = SystemClock;
				}
				break;
		#endif
		}
	}
	return (ret);
}

//=============================================================================
//		Get Key 
//=============================================================================
#define CUPKEY 	DOWNKEY
#define CDOWNKEY 	UPKEY

BYTE GetKey(BYTE repeat)
{

	bit ready;
	//BYTE KeyBuffer2;  //Pinchi disable for compiler warning
	ready = KeyReady;
	KeyReady = 0;


	#if 1//ryan@20170914
	if((ChangeKey==1)&&(Key==0))
	{
		ready=1;
		if((updn_reg[0] == 3) && (updn_reg[1] == 2)&& (updn_reg[2] == 0)&& (updn_reg[3] == 1))  		//Up Key     
			Key=CUPKEY;  
		else	if((updn_reg[0] == 3) && (updn_reg[1] == 1)&& (updn_reg[2] == 0)&& (updn_reg[3] == 2))  //Down Key    
			Key=CDOWNKEY;  
		
		ChangeKey = 0;		
	}   

	
	#elif 0
	if(ChangeKey==1)
	{

		ready=1;
		
		if((updn_reg[0] == 1) && (updn_reg[1] == 3) && (updn_reg[2] == 2)&& (updn_reg[3] == 0))  //UP Key
			Key|=CUPKEY;
		//else if((updn_reg[0] == 3) && (updn_reg[1] == 2)&& (updn_reg[2] == 0)&& (updn_reg[3] == 1))  //UP Key
		//	Key|=CUPKEY;

		if((updn_reg[0] == 1) && (updn_reg[1] == 0)&& (updn_reg[2] == 2)&& (updn_reg[3] == 3))  //DN Key
			Key|=CDOWNKEY;
		//else if((updn_reg[0] == 3) && (updn_reg[1] == 1)&& (updn_reg[2] == 0)&& (updn_reg[3] == 2))  //DN Key
		//	Key|=CDOWNKEY;
		
		ChangeKey = 0;	

		
	}   
	

	#else
	if(ChangeKey==1)//Kane @HS 2007 0814 Ver1.31<<<<
	{
		ready=1;

		if((updn_reg[0] == 0) && (updn_reg[1] == 1) && (updn_reg[2] == 3)&& (updn_reg[3] == 2))  //UP Key
			Key|=UPKEY;
		if((updn_reg[0] == 3) && (updn_reg[1] == 2)&& (updn_reg[2] == 0)&& (updn_reg[3] == 1))  //UP Key
			Key|=UPKEY;

		if((updn_reg[0] == 0) && (updn_reg[1] == 2)&& (updn_reg[2] == 3)&& (updn_reg[3] == 1))  //DN Key
			Key|=DOWNKEY;
		if((updn_reg[0] == 3) && (updn_reg[1] == 1)&& (updn_reg[2] == 0)&& (updn_reg[3] == 2))  //DN Key
			Key|=DOWNKEY;
		 
		//if(OnChangingValue==1)
		if ((GetDisplayedOSD() & MENU) == 0) 	//william-v1.42-961203
		{
			if((updn_reg[0] == 1) && (updn_reg[1] == 3)&& (updn_reg[2] == 2)&& (updn_reg[3] == 0))  //UP Key
				Key|=UPKEY;
			if((updn_reg[0] == 2) && (updn_reg[1] == 0)&& (updn_reg[2] == 1)&& (updn_reg[3] == 3))  //UP Key
				Key|=UPKEY;
			if((updn_reg[0] == 2) && (updn_reg[1] == 3)&& (updn_reg[2] == 1)&& (updn_reg[3] == 0))  //DN Key
				Key|=DOWNKEY;
			if((updn_reg[0] == 1) && (updn_reg[1] == 0)&& (updn_reg[2] == 2)&& (updn_reg[3] == 3))  //DN Key
				Key|=DOWNKEY;
		}
		ChangeKey = 0;		//william-v1.42-961130
	}   

	#endif
	
	if( !ready ) return 0;
	if( repeat ) return Key;
	if( !RepeatKey ) return Key;

	return 0;

}


//=============================================================================
//		CheckRemo
//=============================================================================
#ifdef REMO_RC5

BYTE IsRemoDataReady(BYTE *DataCode, BYTE *AutoKey)
{
	bit togglebit;
	static bit	LastToggle=0;
	static BYTE AutoWait=0;

	BYTE _RemoSystemCode, _RemoDataCode, _RemoDataReady;

	if( !RemoDataReady ) return 0;

	_RemoDataReady = RemoDataReady;
	_RemoDataCode = RemoDataCode;
	_RemoSystemCode = RemoSystemCode;

	*AutoKey = 0;

	EnableRemoconInt();

	#ifdef DEBUG_KEYREMO
	dPrintf("\r\n(CheckRemo)R-S:%02x, R-D:%02x", (WORD)_RemoSystemCode, (WORD)_RemoDataCode);
	#endif

	if( (_RemoSystemCode & 0xc0) != 0xc0 ) return 0;
	if( (_RemoSystemCode & 0x1f) != REMO_CUSTOM ) return 0;

	togglebit = LastToggle;
	if( _RemoSystemCode & 0x20 ) LastToggle = 1;
	else LastToggle = 0;

	#ifdef DEBUG_KEYREMO
	dPrintf("**** %d  %d ", (WORD)LastToggle, (WORD)_RemoDataReady);
	#endif

	if( LastToggle != togglebit ) {			// new key
		AutoWait =  0;
	}
	else if( AutoWait>=4 ) {				// auto key
		AutoWait++;
		if( AutoWait>=6 ) {
			AutoWait = 4;
			*AutoKey = 1;
		}
		else return 0;
	}
	else {									// wait auto key
		AutoWait++;
		return 0;
	}
	
	#ifdef DEBUG_KEYREMO
	if( *AutoKey ) {
		dPuts(" ---> AutoKey ");
	}
	else {
		dPuts(" ---> New Key ");
	}
	#endif

	*DataCode = _RemoDataCode;
	return 1;
}

#elif defined REMO_NEC
extern DATA		BYTE	 RemoData[4];

BYTE IsRemoDataReady(BYTE *DataCode, BYTE *AutoKey)
{
	static BYTE AutoWait=0;
	static IDATA BYTE LastDataCode=0xff;
	static IDATA BYTE repeatcnt=0;
	BYTE ret =0 ;

	*AutoKey = 0;
	switch ( RemoDataReady ) {

	case 0: return 0;

	case 1:
		#ifdef DEBUG_KEYREMO
		dPrintf("\r\nNEC RemoData = %02x %02x %02x %02x", (WORD)RemoData[0], (WORD)RemoData[1], (WORD)RemoData[2], (WORD)RemoData[3] );
		#endif
		if( (RemoData[0]==REMO_CUSTOM1) && (RemoData[1]==REMO_CUSTOM2 ) && (RemoData[2]+RemoData[3])==0xff ) {
			RemoDataCode = RemoData[2];
			LastDataCode = RemoDataCode;
			AutoWait = 0;
			*AutoKey = 0;
			repeatcnt = 0;
		}
		else {
			RemoDataCode = 0xff;
			LastDataCode = 0xff;

			EnableRemoconInt();		//
			return 0;
		}
		break;

	case 2:
		AutoWait++;
		if( AutoWait>=6 ) {
			RemoDataCode = LastDataCode;
			repeatcnt++;
			if( repeatcnt>=5 ) {
				AutoWait = 5;
			}
			else
				AutoWait = 4;

			*AutoKey = 1;
		}
		else {
			EnableRemoconInt();		//
			return 0;
		}
		break;

	}

	EnableRemoconInt();		////LJY052902
	if( RemoDataCode==0xff )	return 0;

	#ifdef DEBUG_KEYREMO
	dPrintf("(R-D:%02x)  ", (WORD)RemoDataCode);
	#endif

	*DataCode = RemoDataCode;
	return 1;
}

#endif	// REMO_NEC

#ifdef SUPPORT_2835_CLK_TUNE_BACK_DOOR  //Pinchi 20160929 add
void HS_Display2835ClkTuneVal(WORD val)
{
	BYTE mstr[]={ ' ',' ' };
	//Printf("\r\n[MSG]Display2835ClkTuneVal()=> enter to draw 2835ClkTuneVal",0);  //pinchi test
	mstr[1] =  val % 10 + '0';	 val /= 10;
	mstr[0] = val + '0';

	InitOSDWindow(Init_Osd_DisplayInput_B);
	SetDisplayedOSD(INPUTINFO);
	ClearDataCnt(INPUTINFO_ADDR, 2);
	DrawAttrCnt(INPUTINFO_ADDR , BG_COLOR_CYAN|CH_COLOR_WHITE, 2);
	WriteStringToAddr(INPUTINFO_ADDR , mstr, 2);
	
	ShowOSDWindow(INPUTINFO_OSDWIN-1,TRUE);
	ShowOSDWindowAll(1);  //0x09c  第4bit : OSD ON, 1: OSD OFF
}
#endif



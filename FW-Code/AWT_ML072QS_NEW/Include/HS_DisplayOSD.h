#ifndef _HS_DisplayOSD_
#define _HS_DisplayOSD_


enum DisplayInformation
{
	InfoOSDMENULOCKED,
	InfoOSDMENUATCIVE,
#ifdef SUPPORT_SDCARD  //Pinchi 20150319 add
	InfoFORMATSDCARD,
	InfoFORMATSUCCESS,
	InfoFORMATFAIL,
	InfoRECORDERROR,
	InfoPASSWORDERROR,
	InfoFWUpdate,
	InfoFWUpdateSUCCESS,
	InfoFWUpdateFAIL,
	InfoSDCARDReset,
	InfoSDCARDNotReady,
	InfoUpdateConfigStart,
	InfoUpdateConfigFail,
	InfoUpdateConfigSuccess,
#endif
	InfoAutoDayNight_Auto,
	InfoAutoDayNight_Day,
	InfoAutoDayNight_Night,
	InfoPLZRESETSYSTEM,
#ifdef AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
	InfoNoVideoSignal,
#endif

};

//#define		InfoUpdateConfigStart	0x01
//#define		InfoUpdateConfigFail		0x02
//#define		InfoUpdateConfigSuccess	0x03

#define		NORMAL_Record  	0x01
#define		Manual_Record	0x02
#define		ALARM_Record	0x04
#define		GPS				0x08
#define		G_Sensor		0x10
#define		WIFI			0x20 
#define		WIFI_Signal		0x40
#define		OverWrite_Record	0x80

void DisplayGaugeOSD(void);
void ClearGAUGEINFO(void);
void DisplaylockOSD(void); 
void DisplayactvOSD(void); 
void DisplayNumber(BYTE addr,WORD val,BYTE type);
//#ifdef SUPPORT_SDCARD
void DisplayDVRStatus(void);
void DisplayFormatOSD(void);
void DisplayFormatOkOSD(void);
void DisplayFormatFailOSD(void);
void DisplayFWUpDate(void);
void DisplayFWUpDateOK(void);
void DisplayFWUpDateFail(void);
void DisplayFWVersion(void) ;
void DisplayDVRnotReady(void);
void DisplayInformation(BYTE info);
//#endif		//#ifdef SUPPORT_SDCARD

#if 0 //def AWT_NO_SIGNAL_MSG  //Pinchi 20150319 add for to display "NO VIDEO SIGNAL" by AWT request of 20150302
void AWT_Display_NoVideoSignal(BYTE bOnOff);
#endif

#endif


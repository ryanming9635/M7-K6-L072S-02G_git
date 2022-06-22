#ifndef	_HS_IOdef_
#define	_HS_IOdef_


#include "Reg.h"

#ifdef AWT_ML072S
	#ifdef HS
#define LEFT_T 			P0_0
#define Right_T			P0_1
	#else	
#define LEFT_T 			P0_1
#define Right_T			P0_0
	#endif
#else
#define LEFT_T 			P0_0
#define Right_T			P0_1
#endif
#define REVERSE_T 		P0_2
//#define VGA_T 		P0_4

#ifdef	AWT_ML072Q  //Pinchi 20140902 add for AWT ML072Q
  #ifdef AWT_NEW_SLIM_MODEL  //Pinchi 20150203 add for AWT new slim model
  #define AV_T 			P0_3
  #define CAMC_T 		P0_4
  #else
  #define CAMC_T 		P0_3
  #endif
#else  //AWT_ML072S & HTRV
#define PARK_T  		P0_3
#endif

#ifdef USE_CAMD  //Pinchi 20150826 add
#define CAMD_T 			P0_5
#endif

#ifdef SUPPORT_SDCARD  //Pinchi 20150826 add 
#define SB_ADC 			P1_6
#define ACC_B			P0_6
#define PPWR			P3_6
#define Door_Det 		P1_7
#endif

#define Audio_Select1 	P1_4
#define Audio_Select2 	P1_5
#define Audio_Mute 		P1_7
//#define AVOutPutSelect  P1_7
//#define RS232Select     P4_0

//#define GPS_PWR		P3_2
//#define GM8126_WD1	P2_0
//#define GM8126_WD2	P3_5

#endif


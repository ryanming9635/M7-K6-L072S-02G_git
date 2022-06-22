#ifndef __CPU__
#define __CPU__

/*
#ifdef INTERNAL_MCU
#define	I2C_SCL		P2_0
#else
#define	I2C_SCL		P1_0
#endif
#define	I2C_SDA		P1_1
*/
#define	I2C_SCL			P1_0
#define	I2C_SDA 		P1_1
#ifdef SUPPORT_SDCARD  //ryan@20170824 
#define BUF_MAX 		8
#define DVR_BUF_MAX 	30
#else
#define BUF_MAX 		20
#define DVR_BUF_MAX 	8
#endif

#ifdef REMO_RC5
#define	EnableRemoconInt()	{ RemoDataReady = 0;	EX0 = 1;}
#endif
void 	InitCPU(void);
void	InitVars(void);
void	InitTechwell(void);
void 	main_init (void);
void	PowerDown( void );
#if 0
BYTE 	OKSleepTime(void);
#endif
#ifdef REMO_RC5
void 	InitForRemo(void);
#endif
void 	PowerLED(BYTE flag);
void    Wait_ms(WORD Tms);
BYTE    TW2835Command(char,char,char,char,char);

#ifdef Monitor_debug
BYTE RS_rx(void);
#endif

#endif


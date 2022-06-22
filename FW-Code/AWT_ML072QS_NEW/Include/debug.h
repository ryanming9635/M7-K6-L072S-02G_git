#ifndef __DEBUG__
#define __DEBUG__

#define DEBUG_ERR	1
#define DEBUG_WARN	2
#define DEBUG_INFO	3
#define DEBUG_BREAK	4

#ifdef DEBUG_PAUSE
#define Pause(a)	{ Printf("\r\n"); Printf(a); while(!RS_ready()); RS_rx(); }
#endif
//#define BURSTLOCK	7

void DebugWindowControl (void) ;
void Draw_Debug_Char(void);
void DebugWindowCursor( BYTE flag ) ;
void DebugWindowData( BYTE flag ) ;
void Debug_Write(void);
void Debug_Read(void);



#endif	// __DEBUG__

#ifdef CHIP_MANUAL_TEST
BYTE DelaynCheck(void);
void ChipManualTest(void);

#endif
#ifndef	_HS_keyremo_
#define	_HS_keyremo_

//
// KeyRemo.h
// Default function for Key Input and Remocon Input
//
//=============================================================================
//		                    Operation Key Mapping
//=============================================================================



#define  SelectMode 0
#define  JumpMode	1

#define COMPOSITE1          1
#define COMPOSITE2          2
#define COMPOSITE3          3
#define COMPOSITE4          4


#ifndef QUAD

#define COMPOSITE1          1
#define COMPOSITE2          2
#define COMPOSITE3          3
#define COMPOSITE4          4

#ifdef AWT_ML072S
#define SOURCE_A			1			
#define SOURCE_R          	2		
#define SOURCE_AV         	3
#define SOURCE_B          	4	
#else
#define SOURCE_A			1		
#define SOURCE_B          	2		
#define SOURCE_R          	3		
#define SOURCE_AV         	4
#endif

void CheckSourceMode(BYTE sorce);
#endif



extern BYTE NowModeState;
extern BYTE TriggerFlag;
extern bit	ParkFlag;
extern BYTE  Attr_A,Attr_B,Attr_C,Attr_R; 
extern BYTE TimeStep;
extern BYTE SEQFlag;
extern BYTE SEQIndex;
extern BYTE TriggerMode;
extern bit AVFlag;
extern bit VGAAudio;



//BYTE TW2835Command(char,char,char,char,char);
void SetSourceMode(BYTE Index,char ,char ,char ,char );
void SetJumpSource(BYTE Index,char ,char ,char ,char );  //Pinchi 20150825 add
void SetSelectMode(void);
//void PriorityOffSelectMode(void);
void SetJumpMode(void);
void SetNowMode(void);
void SetRearSource(void);
void SetLeftSource(void);
void SetRightSource(void);
void CheckMirror(void);
BYTE CheckTrigger(void);
void TriggerHandler(BYTE T_Flag);
void SEQMode(void);

void SelectBoxHandler(void);

extern void CheckNewTriggerFunc(void);

#endif

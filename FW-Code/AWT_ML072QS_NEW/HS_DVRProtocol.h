
#ifndef _HS_DVRProtocol_
#define _HS_DVRProtocol_

//==================================================
//
//==================================================

#define bSetDVRParam 	0x0001
#define bSetDVRDefault 	0x0002
#define bSetDATETIME 	0x0004
#define bGetDVRParam 	0x0008
#define bGetDVRStatus	0x0010
#define bGetDATETIME	0x0020
#define bBOOKMARK		0x0040
#define bSetSystem 		0x0080
#define bHalt_Start 	0x0100
#define bSetFormatSD  	0x0200	
#define bGetDVRVersion 	0x0400	
#define bFW_Update_Start 0x0800
#define bUpdate_CONFIG 	0x1000
#define bDoorClose 		0x2000
#define bDoorOpen 		0x4000


enum HS_DvrCommand
{
	CMD_NULL,
	SetDVRParam,	// 1
	SetDVRDefault,
	SetDATETIME,
	GetDVRParam,
	GetDVRStatus,
	GetDATETIME, 
	SetFormatSD, 
	SendAlarm, 
	GetDVRVersion=0x09, 
	SendDVRStatus=0x14,
	GetLCDMode=0x15,
	SendDVRParam=0x16,
	SendDVRParamDT=0x17,
	SetFormatSDDone=0x18,
	GetInformation=0x19,
	SetSystem=0x1a,
	GPSReset=0x1b,
	Halt_Start=0xc8,
	Halt_OK=0xc9,
	FW_Update_Start=0xca,
	FW_Update_OK=0xcb,
	MANUALRECSTART=0xdc,
	MANUALRECSTOP=0xdd,
	SNAPSHOT=0xde,
	BOOKMARK=0xdf,
	Update_CONFIG=0xe0,
	Update_CONFIG_OK=0xe1,
	DoorOpen=0xe2,
	DoorClose=0xe3,
	CMD_UNKNOWN=0xff,
	CMD_NUM
};

//RS485 TX or RX define
enum
{
	RS485_TX,		//RS485 Transmit	
	RS485_RX		//Rs485 Receive
};

enum
{
	Baud_rate2400,		
	Baud_rate4800,	
	Baud_rate9600
};


//Camera Command ID define
enum
{
//	CAM_CLEAR,				//Clear 
	CAM_ZOOM_OUT_START,			//Zoom Out  Start
//	CAM_ZOOM_OUT_END,			//Zoom Out  End
	CAM_ZOOM_IN_START,			//Zoom In Start
//	CAM_ZOOM_IN_END,			//Zoom In End
//	CAM_IRIS_CLOSE_START,		//IRIS Close Start
//	CAM_IRIS_CLOSE_END,		//IRIS Close End
//	CAM_IRIS_OPEN_START,			//IRIS Open Start
//	CAM_IRIS_OPEN_END,			//IRIS Open End
//	CAM_FOCUS_FAR_START,		//Focus Far Start
//	CAM_FOCUS_FAR_END,		//Focus Far End
//	CAM_FOCUS_NEAR_START,		//Focus Near Start
//	CAM_FOCUS_NEAR_END,		//Focus Near End
	CAM_SET,				//Set 
	CAM_CALL,				//Call 
//	CAM_FOCUS_SPEED,		//Focus Speed
//	CAM_ZOOM_SPEED,		//Zoom Speed
	CAM_PTZ_RIGHT,			//PTZ Right 
	CAM_PTZ_LEFT,			//PTZ Left
	CAM_PTZ_UP,			//PTZ Up
	CAM_PTZ_DOWN,			//PTZ Down
	CAM_MENU_ENTER,			//PTZ Down
	CAM_Iris_Open,

//	CAM_PTZ_RIGHT_UP,		//PTZ Right with Up
//	CAM_PTZ_RIGHT_DOWN,	//PTZ Right with Down
//	CAM_PTZ_LEFT_UP,		//PTZ Left with Up
//	CAM_PTZ_LEFT_DOWN,	//PTZ Left with Down
	CAM_PTZ_STOP			//PTZ Control Stop
};

void Hs_DvrTxCmdPaser(BYTE Cmd_Id );
void Hs_Protocol_Init(void);
BYTE DvrReceivePaser(void);
void DVRCommandReSend(void);

#if 0
BYTE TW2835ReceivePaser(void);
#endif
extern bit	 DVR_Ready;
void CAM_TxCommand_toRS485(BYTE Com_ID);
void Send_PelcoP_Command(void);
void Send_PelcoD_Command(void);
void Send_GE_Command(void);

#endif


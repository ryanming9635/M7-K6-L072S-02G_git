//#define DEGITALDEVICE // OSD Type
//Techwell menu
#define OSDMENU_X_BORDER		0x8//16
#define OSDMENU_Y_BORDER		0x6//4
#define OUTLINE_WIDTH			2
#define NO_TITLE_COLOR			NIL

// Color style IV ---------------------------------------------
/*
#define BACK_COLOR				BG_COLOR_BLACK | EXTENDED_COLOR
#define DEFAULT_COLOR			BG_COLOR_BLACK   | CH_COLOR_WHITE | EXTENDED_COLOR
#define ACTIVE_COLOR			BG_COLOR_WHITE   | CH_COLOR_BLUE | EXTENDED_COLOR	

#define TITLE_COLOR				BG_COLOR_BLACK    | CH_COLOR_YELLOW | EXTENDED_COLOR   
#define CURSOR_COLOR			BG_COLOR_YELLOW | CH_COLOR_BLACK | EXTENDED_COLOR

#define OSD_INFO_COLOR			DEFAULT_COLOR

#define BAR_COLOR				DEFAULT_COLOR	
#define BAR_NUM_COLOR			BAR_COLOR
#define NUM_COLOR				DEFAULT_COLOR
*/
/*
#define BACK_COLOR				BG_COLOR_CYAN
#define DEFAULT_COLOR			BG_COLOR_CYAN   | CH_COLOR_WHITE
//#define ACTIVE_COLOR			BG_COLOR_YELLOW | CH_COLOR_WHITE
#define TITLE_BACK_COLOR		BG_COLOR_BLUE
#define TITLE_COLOR				TITLE_BACK_COLOR | CH_COLOR_WHITE
#define CURSOR_COLOR			BG_COLOR_YELLOW | CH_COLOR_BLUE
#define OSD_INFO_COLOR			DEFAULT_COLOR

#define BAR_COLOR				DEFAULT_COLOR	
#define BAR_NUM_COLOR			DEFAULT_COLOR
#define NUM_COLOR				DEFAULT_COLOR

#define OSDMENU_OUTLINE_COLOR	BG_COLOR_WHITE
*///#define SPACES_BETWEEN_ICON_DESC		0			

#define ICON_X					0
#define ICON_COLOR				DEFAULT_COLOR
#define TOPICON_COLOR			DEFAULT_COLOR
#define NO_ICON_COLOR			NIL

#define DESC_X					2
#define DESC_X_NO_ICON			0
#define DESC_COLOR				DEFAULT_COLOR

//#define CURSOR_START			0

#define ITEMSTARTX				0
#define TITLESTARTX				0


#define BAR_NUM_RADIX			10
#define NUM_RADIX				10

//===================================================================
// OSD Menu Icon define.
//
#define COLORFONT				COLORFONT_START+0x100


CODE BYTE TV_ICON[]={		RAMFONT, COLORFONT+0x0c,	COLORFONT+0x0f, 0};
CODE BYTE INPUT_ICON[]={	RAMFONT, COLORFONT+0x12,	COLORFONT+0x15, 0};
CODE BYTE VIDEO_ICON[]={	RAMFONT, COLORFONT+0x00,	COLORFONT+0x03, 0};
CODE BYTE UTIL_ICON[]={	RAMFONT, COLORFONT+0x18,	COLORFONT+0x1b, 0}; 
CODE BYTE SDCARD_ICON[]={	RAMFONT, COLORFONT+0x06,	COLORFONT+0x09, 0};
CODE BYTE RECORDSDCARD_ICON[]={	RAMFONT, COLORFONT+0x24,	COLORFONT+0x27, 0};
CODE BYTE PC_ADJ_ICON[]={	RAMFONT, 0x01,	0x02,						0};
CODE BYTE NoSDCard_ICON[]={	RAMFONT, COLORFONT+0x1e,	COLORFONT+0x21, 0};
CODE BYTE SDCardOverWrite_ICON[]={	RAMFONT, COLORFONT+0x2A,	COLORFONT+0x2D, 0};
CODE BYTE GPS_ICON[]={	RAMFONT, COLORFONT+0x30,	COLORFONT+0x33, 0};
CODE BYTE NoGPS_ICON[]={	RAMFONT, COLORFONT+0x36,	COLORFONT+0x39, 0};
CODE BYTE NoGPS_ICON2[]={	RAMFONT, COLORFONT+0x60,	COLORFONT+0x63, 0};
CODE BYTE Gsensor_ICON[]={	RAMFONT, COLORFONT+0x3C,	COLORFONT+0x3F, 0};
CODE BYTE NoGsensor_ICON[]={	RAMFONT, COLORFONT+0x42,	COLORFONT+0x45, 0};
CODE BYTE WiFi_ICON[]={	RAMFONT, COLORFONT+0x48,	COLORFONT+0x4B, 0};
CODE BYTE NoWiFi_ICON[]={	RAMFONT, COLORFONT+0x4E,	COLORFONT+0x51, 0};
CODE BYTE WiFiLittle_ICON[]={	RAMFONT, COLORFONT+0x54,	COLORFONT+0x57, 0};
CODE BYTE BookMark_ICON[]={	RAMFONT, COLORFONT+0x5A,	COLORFONT+0x5D, 0};
/*
#define UTIL_ICON				COLORFONT+0x18,	COLORFONT+0x1b 
#define INPUT_ICON				COLORFONT+0x12,	COLORFONT+0x15
#define TV_ICON					COLORFONT+0x0c,	COLORFONT+0x0f
#define VIDEO_ICON				COLORFONT+0x00,	COLORFONT+0x03
#define AUDIO_ICON				COLORFONT+0x06,	COLORFONT+0x09
#define PC_ADJ_ICON				0x118,	0x119


#define INFO_ICON				0x21,	0x20
#define WIDE_ICON				0x102,	0x103
#define SRCSEL_ICON				0x104,	0x105
#define SATU_ICON				0x114,	0x115
#define HUE_ICON				0x110,	0x111
#define SHARP_ICON				0x112,	0x113
#define RESET_ICON				0x10c,	0x10d
#define BRIGHTNESS_ICON			0x10,	0x11
#define CONTRAST_ICON			0x0e,	0x0f
#define PC_COLOR_ICON			0x10e,	0x10f
#define PC_CLOCK_ICON			0x17,	0x18
#define PC_PHASE_ICON			0x19,	0x1a
#define PC_VPOS_ICON			0x0a,	0x0b
#define PC_HPOS_ICON			0x0c,	0x0d
*/

//==================================================================================
//Common
CODE BYTE NumberOnly[]=	{0};
CODE BYTE DefaultBar[]=	{0};

//==========================================================================
//  Menu Structure define
//
#define INPUTSELECT_H	3
CODE BYTE InputSelectMenu[]=
	{
				MENU_WIDTH,		INPUTSELECT_H,
				TITLE_COLOR,
				CURSOR_COLOR,
};

#ifdef fullcode
CODE struct DefineMenu DMINPUTSELECT[]={
		{	{0},											Str_Composite,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,			NO,
			CHANGE_TO_COMPOSITE,
		},
	#ifdef SUPPORT_SVIDEO
		{	{0},											Str_Svideo,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,			NO,
			CHANGE_TO_SVIDEO,
		},
	#endif
	#ifdef SUPPORT_COMPONENT
		{	{0},											Str_Component,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,			NO,
			CHANGE_TO_COMPONENT,
		},
	#endif
	#ifdef SUPPORT_DTV
		{	{0},											Str_Dtv,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,			NO,
			CHANGE_TO_DTV,
		},
	#endif
	#ifdef SUPPORT_PC
		{	{0},											Str_Pc,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,			NO,
			CHANGE_TO_PC,
		},
	#endif
	#ifdef SUPPORT_DIGITALVGA
		{	{0},											Str_DigitalVGA,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,			NO,
			CHANGE_TO_DIGITALVGA,
		},
	#endif
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

#endif
#ifdef SUPPORT_SVIDEO
#define ADD_SVIDEO		1
#else
#define ADD_SVIDEO		0
#endif

#ifdef SUPPORT_COMPONENT
#define ADD_COMPONENT	1
#else
#define ADD_COMPONENT	0
#endif

#ifdef SUPPORT_PC
#define ADD_PC			1
#else
#define ADD_PC			0
#endif

#ifdef SUPPORT_TV
#define ADD_TV			1
#else
#define ADD_TV			0
#endif

#ifdef SUPPORT_DTV
#define ADD_DTV			1
#else
#define ADD_DTV			0
#endif

#define MAX_SUPPORT		(2 + ADD_SVIDEO+ ADD_COMPONENT + ADD_PC + ADD_TV + ADD_DTV)	// +1 default CVBS
#define	INPUTCTRL_H		MAX_SUPPORT

CODE BYTE InputSourceMenu[]=
			{	//3,
				MENU_WIDTH,		INPUTCTRL_H,
				TITLE_COLOR,
				CURSOR_COLOR,
};


#ifdef SUPPORT_RS485
/*-----------------------------------------------------*/ 
/* 第3層OSD --> DISPLAY -->RS485-->*/ 
/*-----------------------------------------------------*/ 
#define RS485SELECT_H  2                                  
CODE BYTE RS485SelectMenu[]={                                    
    MENU_WIDTH,                                                  
    RS485SELECT_H,          
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     FORMATSD OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu RS485SELECT[]={                                       
                                                                     
               {   {0},                     //ICON位置                       
            Str_CAMNumber,             //顯示"Display"字串               
            NIL,                     //上頁ID                         
            NIL,                     //下頁ID                         
            NO_ICON_COLOR,           //ICON顯示Flag                   
            DESC_COLOR,              //字串顯示Flag                   
            0,                       //目前OSD頁內容(第三層OSD)
            NUMBER,             //目前OSD型態(字串)
            NO,                                                 
            //CAMOSDONOFF,             //動作(回到上一頁)         
            CAMNumberChoice,             //動作(回到上一頁)     
            NumberOnly,//DefaultBar      //Ryan@979715       
            //ONOFFChoiceString,       //                         
        },                                                            

        {   {0},                     //ICON位置                       
            Str_Pelco,            //顯示"DISTANCE GAUGE"字串               
            NIL,                     //上頁ID                         
            NIL,                     //下頁ID                         
            NO_ICON_COLOR,           //ICON顯示Flag                   
            DESC_COLOR,              //字串顯示Flag                   
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,             //目前OSD型態(字串) 
            NO,                                                 
           // GAUGEChoice,             //動作(回到上一頁)      
            PelcoChoice,             //動作(回到上一頁)    
            PDChoiceString,       //                         
        },   

        {   {0},                     //ICON位置                       
            Str_Baud_rate,            //顯示"DISTANCE GAUGE"字串               
            NIL,                     //上頁ID                         
            NIL,                     //下頁ID                         
            NO_ICON_COLOR,           //ICON顯示Flag                   
            DESC_COLOR,              //字串顯示Flag                   
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,             //目前OSD型態(字串) 
            NO,                                                 
           // GAUGEChoice,             //動作(回到上一頁)      
            Baud_rateChoice,             //動作(回到上一頁)    
            bpsChoiceString,       //                         
        },  
        
	{	{0},					 //ICON位置 					   
		Str_CameraOSD,			 //顯示"RETRUN"字串 			   
		NIL,					 //上頁ID						   
		NIL,					 //下頁ID						   
		NO_ICON_COLOR,			 //ICON顯示Flag 				   
		DESC_COLOR, 			 //字串顯示Flag 				   
		0,						 //目前OSD頁內容(第三層OSD) 	   
		ACTION, 				 //目前OSD型態	  Abel Test 	   
		NO, 													   
		CameraOSD,				 //動作(回到上一頁) 			   
	},

      {   {0},                     //ICON位置             
          Str_RETURN,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU//動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                     
};
#endif

CODE struct DefineMenu DMINPUTSOURCE[]={
        /////////////>>>>>>>>>>>>>>>>>>>>>>>andy AWT8.4 980811
	 #ifdef QUAD
	    {   {0},                     //ICON位置                                          
            Str_Auto_Day_Night,      //顯示"Auto Day & Night"字串 
            NIL,                     //上頁ID                     
            NIL,                     //下頁ID                                                     
            NO_ICON_COLOR,           //ICON顯示Flag                                                       
            DESC_COLOR,              //字串顯示Flag                                                       
            0,                       //目前OSD頁內容(第三層OSD)                                           
            ENUM_STRING,             //目前OSD型態(字串)
            NO, 
            DayChoice,               //動作(回到上一頁)
        #ifdef SUPPORT_ML072Q_AUTO_DAY_NIGHT  //Pinchi 20150825 add  //AWT_ML072Q  //Pinchi 20140903 add for AWT ML072Q
			ONOFFChoiceString,       //
		#else
            DayChoiceString,       //
        #endif
        },
	#endif
                                                          
        {   {0},                     //ICON位置                       
            Str_DISPLAY,             //顯示"Display"字串               
            NIL,                     //上頁ID                         
            NIL,                     //下頁ID                         
            NO_ICON_COLOR,           //ICON顯示Flag                   
            DESC_COLOR,              //字串顯示Flag                   
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,             //目前OSD型態(字串)
            NO,                                                 
            CAMOSDONOFF,             //動作(回到上一頁)         
            ONOFFChoiceString,       //                         
        },

	#ifdef SUPPORT_SDCARD	
	{   {0},                     //ICON位置                       
            Str_DVR_DISPLAY,             //顯示"Display"字串               
            NIL,                     //上頁ID                         
            NIL,                     //下頁ID                         
            NO_ICON_COLOR,           //ICON顯示Flag                   
            DESC_COLOR,              //字串顯示Flag                   
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,             //目前OSD型態(字串)
            NO,                                                 
            DVRDisplay,             //動作(回到上一頁)         
            ONOFFChoiceString,       //                         
        },   	
	#endif

        {   {0},                     //ICON位置                       
            Str_DISTANCE,            //顯示"DISTANCE GAUGE"字串               
            NIL,                     //上頁ID                         
            NIL,                     //下頁ID                         
            NO_ICON_COLOR,           //ICON顯示Flag                   
            DESC_COLOR,              //字串顯示Flag                   
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,             //目前OSD型態(字串) 
            NO,                                                 
            GAUGEChoice,             //動作(回到上一頁)         
            ONOFFChoiceString,       //                         
        },

 	#ifdef  AWT_ML072S
	    {   {0},                     //ICON位置                                          
            Str_Auto_Day_Night,      //顯示"Auto Day & Night"字串 
            NIL,                     //上頁ID                     
            NIL,                     //下頁ID                                                     
            NO_ICON_COLOR,           //ICON顯示Flag                                                       
            DESC_COLOR,              //字串顯示Flag                                                       
            0,                       //目前OSD頁內容(第三層OSD)                                           
            ENUM_STRING,             //目前OSD型態(字串)
            NO, 
            DayChoice,               //動作(回到上一頁)                         
            #ifdef AWT_ML072S
            ONOFFChoiceString,       //   
		#else
            DayChoiceString,       //   
            #endif
        },                                                                   
	#endif

	#ifdef HTRV
	////_Anderson_20140310_add_xx_B
		{   {0},                     //ICON位置                       
            Str_GAUGE_STEP,            //顯示"DISTANCE GAUGE"字串               
            NIL,                     //上頁ID                         
            NIL,                     //下頁ID                         
            NO_ICON_COLOR,           //ICON顯示Flag                   
            DESC_COLOR,              //字串顯示Flag                   
            0,                       //目前OSD頁內容(第三層OSD)
            GRAPH,////ACTION,             //目前OSD型態(字串) 
            NO,                                                 
            Gauge_VStart,             //動作(回到上一頁)         
            DefaultBar ,       //                         
        },
	////_Anderson_20140310_Disable_xx_E
	#endif

        {   {0},                     //ICON位置                       
            Str_OSD_LOCK,            //顯示"OSD LOCK"字串               
            NIL,                     //上頁ID                         
            NIL,                     //下頁ID                         
            NO_ICON_COLOR,           //ICON顯示Flag                   
            DESC_COLOR,              //字串顯示Flag                   
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,             //目前OSD型態(字串) 
            NO,                                                 
            OsdLockChoice,             //動作(回到上一頁)         
            ONOFFChoiceString,       //                         
        },

#ifndef HTRV
	#ifdef AWT_ML072Q
        {	 {0},					  //ICON位置					   
			 Str_PRIORITY,			  //顯示"PRIORITY"字串				 
			 NIL,					  //上頁ID						   
			 NIL,					  //下頁ID						   
			 NO_ICON_COLOR, 		  //ICON顯示Flag				   
			 DESC_COLOR,			  //字串顯示Flag				   
			 0, 					  //目前OSD頁內容(第三層OSD)
			 ENUM_STRING,			  //目前OSD型態(字串) 
			 NO,												 
			 PRIORITYChoice,			  //動作(回到上一頁)		 
			 ONOFFChoiceString, 	  //						 
	    },    
	#endif

	    //#ifdef Func_ReversMode
		#ifdef HS
		#else
		{  {0},					   //ICON位置						
		   Str_ReversMode,			 //顯示"OSD LOCK"字串				
		   NIL,					   //上頁ID 						
		   NIL,					   //下頁ID 						
		   NO_ICON_COLOR,		   //ICON顯示Flag					
		   DESC_COLOR,			   //字串顯示Flag					
		   0,					   //目前OSD頁內容(第三層OSD)
		   ENUM_STRING,			   //目前OSD型態(字串) 
		   NO,												  
		   ReverseMode,			   //動作(回到上一頁)		  
		   ReversModeString, 	  //						 
		 },
		#endif
		 //#endif
#endif

	#ifdef SUPPORT_RS485
		{	{0},					 //ICON位置 					   
		    Str_RS485,			 //顯示"RETRUN"字串 			   
   		    NIL,					  //上頁ID				 
   		    NIL,					  //下頁ID				 
   		    NO_ICON_COLOR,		  //ICON顯示Flag		 
   		    DESC_COLOR,			  //字串顯示Flag		 
   		    RS485SELECT,		   //目前OSD頁內容(第三層OSD)	  
   		    OSDMENU,//CHOICEMENU, 			//目前OSD型態				   
   		    NO,											 
   		    0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
   		   RS485SelectMenu 	   //動作Flag				   
		},
	#endif
			
		{	{0},                     //ICON位置                     
            Str_RETURN,              //顯示"RETRUN"字串             
            NIL,                     //上頁ID                       
            NIL,                     //下頁ID                       
            NO_ICON_COLOR,           //ICON顯示Flag                 
            DESC_COLOR,              //字串顯示Flag                 
            0,                       //目前OSD頁內容(第三層OSD)     
            ACTION,                  //目前OSD型態(設定動作)     
            NO,                                                     
            TOHIGHMENU               //動作(回到上一頁)             
        },             

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<andy AWT8.4 980811
        
		#if 0 
		{	{0},											Str_Input,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			DMINPUTSELECT,
			CHOICEMENU,			NO,
			INPUTSELECTION,
			InputSelectMenu
		},

		{	{0},										Str_Information,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,		NO,
			DISP_INFO ,
		},
		#endif
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
#define		UTILITY_H			4
/*CODE BYTE SleepTimerNumber[]=
			{//0,		
			UTILITY_H+1,	MENU_WIDTH,		
			BACK_COLOR,		
			NUM_RADIX,		NUM_COLOR,
			0};*/
#if 0			
CODE BYTE UtilityMenu[]=
			{
			MENU_WIDTH,		UTILITY_H,
			TITLE_COLOR,	
			CURSOR_COLOR,
};

CODE struct DefineMenu DMUtility[]={
		{	{0},											Str_SleepTimer,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			NUMBER,	NO,
			SLEEP_TIMER,
			NumberOnly
		},
#ifdef WIDE_SCREEN
		{	{0},										Str_WideScreen,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ENUM_STRING,		NO,
			WIDESCREEN,
			WideScreenChoice
		},
#endif // WIDE_SCREEN
#ifdef SUPPORT_OSDPOSITIONMOVE
		{	{0},										Str_OSDPosition,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ENUM_STRING,		NO,
			OSDPOSITIONMODE,
			OsdPositionModeChoice
		},
#endif
		{	{0},											Str_OSDLang,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			ENUM_STRING,			NO,
			OSDLANG,
			OSDLangString,
		},
		{	{0},									Str_Reset,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,			NO,
			RESET_VIDEOVALUE
		},
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
#endif		

/*-----------------------------------------------------*/ 
/* 第3層OSD ---> EXIT --->FWUpdate						*/ 
/*-----------------------------------------------------*/ 
#define FWUpdateSELECT_H  2                                  
CODE BYTE FWUpdateSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    FWUpdateSELECT_H,          
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     FWUpdate OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu FWUpdateSELECT[]={                                       
                                                                     
        {	{0},								
    		Str_NO,
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR, 			 //字串顯示Flag 				   
			0,						 //目前OSD頁內容(第三層OSD) 	   
			ACTION, 				 //目前OSD型態	  Abel Test 	   
			NO, 													   
			TOHIGHMENU , 	 //動作(回到上一頁) 	  

    	},     
 	
        {   {0},                 //ICON位置     
       		Str_YES,
   		    NIL,					   //上頁ID 						 
   		    NIL,					   //下頁ID 						 
   		    NO_ICON_COLOR,		   //ICON顯示Flag					 
   		    DESC_COLOR,			   //字串顯示Flag					 
   		    0,					   //目前OSD頁內容(第三層OSD)		 
   		    ACTION,				   //目前OSD型態	Abel Test		 
   		    NO,														 
   		    FirmwareUpdate,	   //動作(回到上一頁)		                        
       },
			                                               
       {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
       },                   
};
//#ifdef SUPPORT_SDCARD	
/*-----------------------------------------------------*/ 
/* 第4層OSD --> EXIT -->FORMAT SD CARD-->Change Password*/ 
/*-----------------------------------------------------*/ 
#define ChangePasswordSELECT_H  2                                  
CODE BYTE ChangePasswordSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    ChangePasswordSELECT_H,          
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     FORMATSD OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu ChangePasswordSELECT[]={                                       
                                                                     
        {	{0},								
    		Str_FirstNumber,
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		FirstNumber,
    		DefaultBar
    	},     
 	
        {   {0},                 //ICON位置                                      
            Str_SecondNumber,            //顯示"CAMA"字串                               
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		SecondNumber,
    		DefaultBar        
       },
			
       {	{0},								
    		Str_ThirdNumber,
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		ThridNumber,
    		DefaultBar
       }, 

	   {	{0},								
			Str_FourthNumber,
			NIL,	
			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER, 		
			NO,
			FourthNumber,
			DefaultBar
	    }, 
		
		{	{0},					 //ICON位置 					   
			Str_ChangePassword,			 //顯示"RETRUN"字串 			   
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR, 			 //字串顯示Flag 				   
			0,						 //目前OSD頁內容(第三層OSD) 	   
			ACTION, 				 //目前OSD型態	  Abel Test 	   
			NO, 													   
			ChangePassword ,				 //動作(回到上一頁) 			   
		},


      {   {0},                     //ICON位置             
          Str_RETURN,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU//動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                     
};


/*-----------------------------------------------------*/ 
/* 第3層OSD ---> EXIT --->FORMAT SD CARD						*/ 
/*-----------------------------------------------------*/ 
#define FORMATSDSELECT_H  2                                  
CODE BYTE FORMATSDSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    FORMATSDSELECT_H,          
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     FORMATSD OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu FORMATSDSELECT[]={                                       
                                                                     
        {	{0},								
    		Str_FirstNumber,
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		FirstNumber,
    		DefaultBar
    	},     
 	
        {   {0},                 //ICON位置                                      
            Str_SecondNumber,            //顯示"CAMA"字串                               
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		SecondNumber,
    		DefaultBar        
       },
			
       {	{0},								
    		Str_ThirdNumber,
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		ThridNumber,
    		DefaultBar
       }, 

	   {	{0},								
			Str_FourthNumber,
			NIL,	
			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER, 		
			NO,
			FourthNumber,
			DefaultBar
	    }, 

		{	{0},					 //ICON位置 					   
			Str_FormatSD,			 //顯示"RETRUN"字串 			   
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR, 			 //字串顯示Flag 				   
			0,						 //目前OSD頁內容(第三層OSD) 	   
			ACTION, 				 //目前OSD型態	  Abel Test 	   
			NO, 													   
			FormatSD ,				 //動作(回到上一頁) 			   
		},
		
		{	{0},					 //ICON位置 					   
			Str_ChangePassword,			 //顯示"RETRUN"字串 			   
   		    NIL,					  //上頁ID				 
   		    NIL,					  //下頁ID				 
   		    NO_ICON_COLOR,		  //ICON顯示Flag		 
   		    DESC_COLOR,			  //字串顯示Flag		 
   		    ChangePasswordSELECT,		   //目前OSD頁內容(第三層OSD)	  
   		    OSDMENU,//CHOICEMENU, 			//目前OSD型態				   
   		    NO,											 
   		    0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
   		    ChangePasswordSelectMenu 	   //動作Flag				   
		},

		

      {   {0},                     //ICON位置             
          Str_RETURN,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU//動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                     
};


//#endif//		#ifdef SUPPORT_SDCARD	
/*-----------------------------------------------------*/ 
/*         第三層OSD ---> SDCARD --->DATE TIME	                   */ 
/*-----------------------------------------------------*/ 
#define DateTimeSELECT_H  5                                  
CODE BYTE DateTimeSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    DateTimeSELECT_H,          
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     DateTimeSET OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu DateTimeSELECT[]={  

		{	{0},								
			Str_TimeZone,
			NIL,	
			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ENUM_STRING, 		NO,
			TimeZone,
			TimeZoneChoiceString
		},

       	{	{0},								
       		Str_Year,
       		NIL,	
       		NIL,	
       		NO_ICON_COLOR,
       		DESC_COLOR,
       		0,
       		NUMBER,			NO,
       		Year,
       		DefaultBar
       	},                                                                     
       
       	{	{0},								
       		Str_Month,
       		NIL,	
       		NIL,	
       		NO_ICON_COLOR,
       		DESC_COLOR,
       		0,
       		NUMBER,			NO,
       		Month,
       		DefaultBar
       	}, 
       	
           {	{0},								
       		Str_Day,
       		NIL,	
       		NIL,	
       		NO_ICON_COLOR,
       		DESC_COLOR,
       		0,
       		NUMBER,			NO,
       		Day,
       		DefaultBar
       	},   
       
       	{	{0},								
       		Str_Hour,
       		NIL,	
       		NIL,	
       		NO_ICON_COLOR,
       		DESC_COLOR,
       		0,
       		NUMBER,			NO,
       		Hour,
       		DefaultBar
       	},
       
       	{	{0},								
       		Str_Minute,
       		NIL,	
       		NIL,	
       		NO_ICON_COLOR,
       		DESC_COLOR,
       		0,
       		NUMBER,			NO,
       		Minute,
       		DefaultBar
       	},
       	



      {   {0},                     //ICON位置             
          Str_RETURNAPPLY,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          DATETIMEApply				//動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                   
};
#ifdef AWT_ML073G
//#ifdef SUPPORT_SDCARD	
/*-----------------------------------------------------*/ 
/* 第四層OSD ---> SDCARD --->DATE TIME--->DaylightSaving--->TimeBegines*/ 
/*-----------------------------------------------------*/ 
#define StandardTimeBeginesSELECT_H  5                                  
CODE BYTE StandardTimeBeginesSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    StandardTimeBeginesSELECT_H,          
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     DateTimeSET OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu StandardTimeBeginesSELECT[]={                                       
                                                                     
        {	{0},								
    		Str_Month,
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		StandardTimeBeginesMonth,
    		DefaultBar
    	},     
 	
        {   {0},                 //ICON位置                                      
           Str_Week,            //顯示"CAMA"字串                               
           NIL,                 //上頁ID                                        
           NIL,                 //下頁ID                                        
           NO_ICON_COLOR,       //ICON顯示Flag                                  
           DESC_COLOR,          //字串顯示Flag                                  
           0,
           ENUM_STRING,         //目前OSD型態    Abel Test 
           NO,                                             
           StandardTimeBeginesWeek,           //動作(回到上一頁)         
           TimeBeginesWeekChoiceString    //                         
       },
			
       {	{0},								
    		Str_Time,
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		StandardTimeBeginesTime,
    		DefaultBar
    }, 



      {   {0},                     //ICON位置             
          Str_RETURNAPPLY,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          DATETIMEApply               //動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                   
};


/*-----------------------------------------------------*/ 
/* 第四層OSD ---> SDCARD --->DATE TIME--->DaylightSaving--->TimeBegines*/ 
/*-----------------------------------------------------*/ 
#define TimeBeginesSELECT_H  5                                  
CODE BYTE TimeBeginesSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    TimeBeginesSELECT_H,          
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     DateTimeSET OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu TimeBeginesSELECT[]={                                       
                                                                     
        {	{0},								
    		Str_Month,
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		TimeBeginesMonth,
    		DefaultBar
    	},     
 	
       {   {0},                 //ICON位置                                      
          Str_Week,            //顯示"CAMA"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          TimeBeginesWeek,           //動作(回到上一頁)         
          TimeBeginesWeekChoiceString    //                         
      },
			
        {	{0},								
    		Str_Time,
    		NIL,	
    		NIL,	
    		NO_ICON_COLOR,
    		DESC_COLOR,
    		0,
    		NUMBER,			
    		NO,
    		TimeBeginesTime,
    		DefaultBar
    	}, 



      {   {0},                     //ICON位置             
          Str_RETURNAPPLY,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          DATETIMEApply               //動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                   
};





/*-----------------------------------------------------*/ 
/* 第三層OSD ---> SDCARD --->DATE TIME--->DaylightSaving*/ 
/*-----------------------------------------------------*/ 
#define DaylightSavingSELECT_H  5                                  
CODE BYTE DaylightSavingSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    DaylightSavingSELECT_H,          
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     DateTimeSET OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu DaylightSavingSELECT[]={                                       
      {   {0},                 //ICON位置                                      
          Str_DaylightSaving,            //顯示"CAMA"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          DaylightSaving,           //動作(回到上一頁)         
          DaylightSavingChoiceString    //                         
      },                                                                     
    #if 0
	  {   {0},					  //ICON位置			 
		  Str_TimeBegines,			  //顯示"MIRRO"字串 			
		  NIL,					  //上頁ID				 
		  NIL,					  //下頁ID				 
		  NO_ICON_COLOR,		  //ICON顯示Flag		 
		  DESC_COLOR,			  //字串顯示Flag		 
		  TimeBeginesSELECT, 		   //目前OSD頁內容(第三層OSD)	  
		  OSDMENU,//CHOICEMENU, 			//目前OSD型態				   
		  NO,											 
		  0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
		  TimeBeginesSelectMenu		   //動作Flag			  
	  }, 

 	  {   {0},					  //ICON位置			 
		  Str_Standard,			  //顯示"MIRRO"字串 			
		  NIL,					  //上頁ID				 
		  NIL,					  //下頁ID				 
		  NO_ICON_COLOR,		  //ICON顯示Flag		 
		  DESC_COLOR,			  //字串顯示Flag		 
		  StandardTimeBeginesSELECT, 		   //目前OSD頁內容(第三層OSD)	  
		  OSDMENU,//CHOICEMENU, 			//目前OSD型態				   
		  NO,											 
		  0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
		  StandardTimeBeginesSelectMenu		   //動作Flag			  
	  },       	
  #endif
			

      {   {0},                     //ICON位置             
          Str_RETURNAPPLY,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          DATETIMEApply               //動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                   
};
#endif

CODE struct DefineMenu DMRecallSELECT[]={                                       
     
      {   {0},                     //ICON位置             
          Str_YES,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,
          RESET_VIDEOVALUE,                                             
          //YESNOChoiceString               //動作(回到上一頁)     
      },                                                  

	  
 

 {   {0},                     //ICON位置             
          Str_NO,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU               //動作(回到上一頁)     
    },                                                  

     {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                  
      
 
};   

CODE struct DefineMenu DMMonitorRecallSELECT[]={                                       
     
      {   {0},                     //ICON位置             
          Str_YES,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,
          RESET_MonitorVALUE,                                             
          //YESNOChoiceString               //動作(回到上一頁)     
      },                                                  

	  
 

 {   {0},                     //ICON位置             
          Str_NO,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU               //動作(回到上一頁)     
    },                                                  

     {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                  
      
 
};   

CODE struct DefineMenu DMDVRRecallSELECT[]={                                       
     
      {   {0},                     //ICON位置             
          Str_YES,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,
          RESET_DVRVALUE,                                             
          //YESNOChoiceString               //動作(回到上一頁)     
      },                                                  

	  
 

 {   {0},                     //ICON位置             
          Str_NO,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU               //動作(回到上一頁)     
    },                                                  

     {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                  
      
 
};   

CODE struct DefineMenu RecallMenu[]={                                       
	  
{   {0},                     //ICON位置                        
              Str_MonitorRECALL,              //顯示"RETRUN"字串                
              NIL,                     //上頁ID                          
              NIL,                     //下頁ID                          
              NO_ICON_COLOR,           //ICON顯示Flag                    
              DESC_COLOR,              //字串顯示Flag                    
              DMMonitorRecallSELECT,                       //目前OSD頁內容(第三層OSD)        
              OSDMENU,             //目前OSD型態(字串) 
              NO,                                                 
              0,
              InputSelectMenu,       //                        
          },                                     

{   {0},                     //ICON位置                        
              Str_DVRRECALL,              //顯示"RETRUN"字串                
              NIL,                     //上頁ID                          
              NIL,                     //下頁ID                          
              NO_ICON_COLOR,           //ICON顯示Flag                    
              DESC_COLOR,              //字串顯示Flag                    
              DMDVRRecallSELECT,                       //目前OSD頁內容(第三層OSD)        
              OSDMENU,             //目前OSD型態(字串) 
              NO,                                                 
              0,
              InputSelectMenu,       //                        
          },     
          
        {   
            {0},                     //ICON位置                     
            Str_RETURN,              //顯示"RETRUN"字串             
            NIL,                     //上頁ID                       
            NIL,                     //下頁ID                       
            NO_ICON_COLOR,           //ICON顯示Flag                 
            DESC_COLOR,              //字串顯示Flag                 
            0,                       //目前OSD頁內容(第三層OSD)     
            ACTION,                  //目前OSD型態(設定動作)     
            NO,                                                     
            TOHIGHMENU               //動作(回到上一頁)             
        },         
        
     {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },      
      
 
};   

	#define INFORMATION_H	4
CODE BYTE InformationMenu[]=
{
			MENU_WIDTH,		
			INFORMATION_H,
			TITLE_COLOR,
			CURSOR_COLOR,
};

CODE struct DefineMenu DMINFORMATION[]=
{


		{	{0},					 //ICON位置 					   
			Str_WIFI_IP,				//顯示"RETRUN"字串				  
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			VER_COLOR,				//字串顯示Flag					  
			0,						 //目前OSD頁內容(第三層OSD) 	   
			TEXT_STR,				   //目前OSD型態	Abel Test		 
			NO, 													   
			TOHIGHMENU ,				 //動作(回到上一頁) 			   
		},	

		{	{0},					 //ICON位置 					   
			NO,				//顯示"RETRUN"字串				  
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR,				//字串顯示Flag					  
			0,						 //目前OSD頁內容(第三層OSD) 	   
			INFORMATION,			
			NO,	  				 //目前OSD型態	Abel Test		 
			WIFIIPNumber, 													   
			DefaultBar ,			 //動作(回到上一頁) 			   
		},	
		
		{	{0},					 //ICON位置 					   
			Str_WIFI_MAC,				//顯示"RETRUN"字串				  
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			VER_COLOR,				//字串顯示Flag					  
			0,						 //目前OSD頁內容(第三層OSD) 	   
			TEXT_STR,				   //目前OSD型態	Abel Test		 
			NO, 													   
			TOHIGHMENU ,				 //動作(回到上一頁) 			   
		},	

		{	{0},					 //ICON位置 					   
			NO,				//顯示"RETRUN"字串				  
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			VER_COLOR,				//字串顯示Flag					  
			0,						 //目前OSD頁內容(第三層OSD) 	   
			INFORMATION,				   //目前OSD型態	Abel Test		 
			NO, 													   
			WIFIMACNumber ,				 //動作(回到上一頁) 
			DefaultBar ,
		},	
		
		{	{0},					 //ICON位置 					   
			Str_GETWAY,				//顯示"RETRUN"字串				  
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			VER_COLOR,				//字串顯示Flag					  
			0,						 //目前OSD頁內容(第三層OSD) 	   
			TEXT_STR,				   //目前OSD型態	Abel Test		 
			NO, 													   
			TOHIGHMENU ,				 //動作(回到上一頁) 			   
		},	

		{	{0},					 //ICON位置 					   
			NO,				//顯示"RETRUN"字串				  
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			VER_COLOR,				//字串顯示Flag					  
			0,						 //目前OSD頁內容(第三層OSD) 	   
			INFORMATION,				   //目前OSD型態	Abel Test		 
			NO, 													   
			GETWAYNumber,				 //動作(回到上一頁) 
			DefaultBar ,
		},	
		
	       {   
	        	{0},                     //ICON位置                     
	        	Str_RETURN,              //顯示"RETRUN"字串             
	        	NIL,                     //上頁ID                       
	        	NIL,                     //下頁ID                       
	       	 NO_ICON_COLOR,           //ICON顯示Flag                 
	        	DESC_COLOR,              //字串顯示Flag                 
	        	0,                       //目前OSD頁內容(第三層OSD)     
	        	ACTION,                  //目前OSD型態(設定動作)     
	        	NO,                                                     
	        	TOHIGHMENU               //動作(回到上一頁)             
	       },  
			
		{	
			{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

CODE BYTE UtilityMenu[]={                                                             
    MENU_WIDTH,                                                                       
    UTILITY_H,                                                                        
    TITLE_COLOR,                                                                      
    CURSOR_COLOR,};                                                                                                                                         
                
CODE struct DefineMenu DMUtility[]={

	#ifdef SUPPORT_SDCARD	
      	{	 {0},					  //ICON位置					   
			 Str_SDCARDCOVERDET,			  //顯示"PRIORITY"字串				 
			 NIL,					  //上頁ID						   
			 NIL,					  //下頁ID						   
			 NO_ICON_COLOR, 		  //ICON顯示Flag				   
			 DESC_COLOR,			  //字串顯示Flag				   
			 0, 					  //目前OSD頁內容(第三層OSD)
			 ENUM_STRING,			  //目前OSD型態(字串) 
			 NO,												 
			 SDCardDetect,			  //動作(回到上一頁)		 
			 ONOFFChoiceString, 	  //						 
		 },    

        {   {0},                    //ICON位置             
           	Str_DateTime,             //顯示"MIRRO"字串             
            	NIL,                    //上頁ID               
            	NIL,                    //下頁ID               
            	NO_ICON_COLOR,          //ICON顯示Flag         
            	DESC_COLOR,             //字串顯示Flag         
            	DateTimeSELECT,            //目前OSD頁內容(第三層OSD)     
            	OSDMENU,//CHOICEMENU,             //目前OSD型態                  
            	NO,                                            
            	0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            	DateTimeSelectMenu         //動作Flag             
        },

 		#ifdef AWT_ML073G
	 	{   {0},                    //ICON位置             
            	Str_DaylightSaving,             //顯示"MIRRO"字串             
            	NIL,                    //上頁ID               
            	NIL,                    //下頁ID               
            	NO_ICON_COLOR,          //ICON顯示Flag         
            	DESC_COLOR,             //字串顯示Flag         
            	DaylightSavingSELECT,            //目前OSD頁內容(第三層OSD)     
            	OSDMENU,//CHOICEMENU,             //目前OSD型態                  
            	NO,                                            
            	0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            	DaylightSavingSelectMenu         //動作Flag             
        }, 

	 	{   {0},                     //ICON位置                        
            Str_Informmation,              //顯示"RETRUN"字串                
          	NIL,                     //上頁ID                          
          	NIL,                     //下頁ID                          
          	NO_ICON_COLOR,           //ICON顯示Flag                    
          	DESC_COLOR,              //字串顯示Flag                    
          	DMINFORMATION,                       //目前OSD頁內容(第三層OSD)        
          	OSDMENU,             //目前OSD型態(字串) 
          	NO,                                                 
          	0,
          	InformationMenu,       //                        
        },

     	{   {0},					   //ICON位置						 
      		Str_UpdateConfig,		   //顯示"RETRUN"字串				 
      		NIL,					   //上頁ID 						 
      		NIL,					   //下頁ID 						 
      		NO_ICON_COLOR,		   //ICON顯示Flag					 
      		DESC_COLOR,			   //字串顯示Flag					 
      		0,					   //目前OSD頁內容(第三層OSD)		 
      		ACTION,				   //目前OSD型態	Abel Test		 
      		NO,														 
      		UpdateConfig ,	   //動作(回到上一頁)				 
   	    },
		#endif
	#endif		

	#ifdef QUAD  //Pinchi 20150901 change to QUAD condition
     	#ifdef SUPPORT_SDCARD 
     	{   {0},                     //ICON位置                        
     		Str_RECALL,              //顯示"RETRUN"字串                
     		NIL,                     //上頁ID                          
     		NIL,                     //下頁ID                          
     		NO_ICON_COLOR,           //ICON顯示Flag                    
     		DESC_COLOR,              //字串顯示Flag                    
     		RecallMenu,              //目前OSD頁內容(第三層OSD)        
     		OSDMENU,                 //目前OSD型態(字串) 
     		NO,                                                 
     		0,
     		InputSelectMenu,
     	},     		     
		#else
     	{   {0},					 //ICON位置
     		Str_RECALL,			     //顯示"RETRUN"字串
     		NIL,					 //上頁ID
     		NIL,					 //下頁ID
     		NO_ICON_COLOR,		     //ICON顯示Flag
     		DESC_COLOR,			     //字串顯示Flag
     		0,					     //目前OSD頁內容(第三層OSD)
     		ACTION,				     //目前OSD型態	Abel Test
     		NO,
     		RESET_VIDEOVALUE ,	   //動作(回到上一頁)
     	},
		#endif

		#ifdef HTRV  //Pinchi 20140902 add for AWT ML072Q
		////_Anderson_20140310_add_xx_B
		{   {0},                     //ICON位置                        
			Str_GAUGE_RECALL,              //顯示"RETRUN"字串                
			NIL,                     //上頁ID                          
			NIL,                     //下頁ID                          
			NO_ICON_COLOR,           //ICON顯示Flag                    
			DESC_COLOR,              //字串顯示Flag                    
			0,                       //目前OSD頁內容(第三層OSD)        
			ACTION,                  //目前OSD型態    Abel Test        
			NO,                                                        
			RESET_GAUGESETUP,       //動作(回到上一頁)                
		},
		#endif

     	{   {0},                     //ICON位置
     		Str_EXIT,                //顯示"RETRUN"字串
     		NIL,                     //上頁ID
     		NIL,                     //下頁ID
     		NO_ICON_COLOR,           //ICON顯示Flag
     		DESC_COLOR,              //字串顯示Flag
     		0,                       //目前OSD頁內容(第三層OSD)
     		ACTION,                  //目前OSD型態    Abel Test
     		NO,
     		EXITMENU ,               //動作(回到上一頁)
     	},
	#endif
#ifndef AWT_ML072S
		{	{0},					 //ICON位置
			Str_SPACE,				 //顯示"RETRUN"字串
			NIL,					 //上頁ID
			NIL,					 //下頁ID
			NO_ICON_COLOR,			 //ICON顯示Flag
			DESC_COLOR, 			 //字串顯示Flag
			0,						 //目前OSD頁內容(第三層OSD)
			TEXT_STR,				   //目前OSD型態	Abel Test
			NO,
			EXITMENU ,				 //動作(回到上一頁)
		},

		{	{0},					 //ICON位置
			Str_SPACE,				  //顯示"RETRUN"字串
			NIL,					 //上頁ID
			NIL,					 //下頁ID
			NO_ICON_COLOR,			 //ICON顯示Flag
			DESC_COLOR, 			 //字串顯示Flag
			0,						 //目前OSD頁內容(第三層OSD)
			TEXT_STR,				   //目前OSD型態	Abel Test
			NO,
			EXITMENU ,				 //動作(回到上一頁)
		},	 

		{	{0},					 //ICON位置
			Str_SPACE,				 //顯示"RETRUN"字串
			NIL,					 //上頁ID
			NIL,					 //下頁ID
			NO_ICON_COLOR,			 //ICON顯示Flag
			DESC_COLOR, 			 //字串顯示Flag
			0,						 //目前OSD頁內容(第三層OSD)
			TEXT_STR,				 //目前OSD型態	Abel Test
			NO,
			EXITMENU ,				 //動作(回到上一頁)
		},
	#endif
	#ifdef TW8816
							#ifdef AWT_ML072S
						{	{0},					 //ICON位置
							Str_SPACE,				 //顯示"RETRUN"字串
							NIL,					 //上頁ID
							NIL,					 //下頁ID
							NO_ICON_COLOR,			 //ICON顯示Flag
							DESC_COLOR, 			 //字串顯示Flag
							0,						 //目前OSD頁內容(第三層OSD)
							TEXT_STR,				   //目前OSD型態	Abel Test
							NO,
							EXITMENU ,				 //動作(回到上一頁)
						},

						{	{0},					 //ICON位置
							Str_SPACE,				  //顯示"RETRUN"字串
							NIL,					 //上頁ID
							NIL,					 //下頁ID
							NO_ICON_COLOR,			 //ICON顯示Flag
							DESC_COLOR, 			 //字串顯示Flag
							0,						 //目前OSD頁內容(第三層OSD)
							TEXT_STR,				   //目前OSD型態	Abel Test
							NO,
							EXITMENU ,				 //動作(回到上一頁)
						},	 
							#endif
	{	{0},					 //ICON位置
			Str_VER,				 //顯示"RETRUN"字串
			NIL,					 //上頁ID
			NIL,					 //下頁ID
			NO_ICON_COLOR,			 //ICON顯示Flag
			VER_COLOR,				 //字串顯示Flag
			0,						 //目前OSD頁內容(第三層OSD)
			TEXT_STR,				 //目前OSD型態	Abel Test
			NO,
			EXITMENU ,				 //動作(回到上一頁)
		},

		#endif


	{	{0},					 //ICON位置
			Str_SPACE,				 //顯示"RETRUN"字串
			NIL,					 //上頁ID
			NIL,					 //下頁ID
			NO_ICON_COLOR,			 //ICON顯示Flag
			DESC_COLOR, 			 //字串顯示Flag
			0,						 //目前OSD頁內容(第三層OSD)
			TEXT_STR,				 //目前OSD型態	Abel Test
			NO,
			EXITMENU ,				 //動作(回到上一頁)
		},		

	#ifdef AWT_ML072S
		{	{0},					 //ICON位置 					   
			Str_SPACE,				  //顯示"RETRUN"字串				
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR, 			 //字串顯示Flag 				   
			0,						 //目前OSD頁內容(第三層OSD) 	   
			TEXT_STR,				   //目前OSD型態	Abel Test		 
			NO, 													   
			EXITMENU ,				 //動作(回到上一頁) 			   
		},	
		
		{	{0},					 //ICON位置 					   
			Str_SPACE,				  //顯示"RETRUN"字串				
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR, 			 //字串顯示Flag 				   
			0,						 //目前OSD頁內容(第三層OSD) 	   
			TEXT_STR,				   //目前OSD型態	Abel Test		 
			NO, 													   
			EXITMENU ,				 //動作(回到上一頁) 			   
		},	

           {   {0},                     //ICON位置                        
              Str_EXIT,                //顯示"RETRUN"字串                
              NIL,                     //上頁ID                          
              NIL,                     //下頁ID                          
              NO_ICON_COLOR,           //ICON顯示Flag                    
              DESC_COLOR,              //字串顯示Flag                    
              0,                       //目前OSD頁內容(第三層OSD)        
              TEXT_STR,                  //目前OSD型態    Abel Test        
              NO,                                                        
              EXITMENU ,               //動作(回到上一頁)                
          },   
	#endif

          { {0},                                                                      
            0,//Terminator                                                            
            0,                                                                        
            0,                                                                        
            NIL,                                                                      
            NIL,                                                                      
            0,                                                                        
            0,                                                                        
            0,                                                                        
          },   
};

/*-----------------------------------------------------*/ 
/*         第三層OSD ---> SDCARD --->RECORDMODE               */ 
/*-----------------------------------------------------*/ 
#define RecordSELECT_H  5                                  
CODE BYTE RecordSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    RecordSELECT_H,          //第三層OSD ---> UTILITY --->Input   
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     CAMSELECT OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu RECORDSELECT[]={     
	#if 0
      {   {0},                 //ICON位置                                      
          Str_RecordMode,            //顯示"CAMA"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          RecordMode,           //動作(回到上一頁)         
          RecordModeChoiceString    //                         
      },                                                                       
     #endif                                                                          
      {   {0},                 //ICON位置                                      
          Str_RecordLength,            //顯示"CAMB"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          RecordLength,         //動作(回到上一頁)         
          RecordLengthChoiceString    //                         
      },              

     {  {0},                 //ICON位置                                       
          Str_PostAlarmLength,            //顯示"CAMR"字串                                
          NIL,                 //上頁ID                                         
          NIL,                 //下頁ID                                         
          NO_ICON_COLOR,       //ICON顯示Flag                                   
          DESC_COLOR,          //字串顯示Flag                                   
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                                 
          PostAlarmLength,         //動作(回到上一頁)         
          PostAlarmLengthChoiceString    //                         
      },        
#if 0                                                                               
      {   {0},                 //ICON位置                                      
          Str_PreAlarmLength,            //顯示"CAMC"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          PreAlarmLength,         //動作(回到上一頁)         
          PreAlarmLengthChoiceString    //                         
      },                                                                       
                                                                               
                                                               
                 
	    {   {0},                     //ICON位置                                          
            Str_Str_OverWrite,      //顯示"Auto Day & Night"字串 
            NIL,                     //上頁ID                     
            NIL,                     //下頁ID                                                     
            NO_ICON_COLOR,           //ICON顯示Flag                                                       
            DESC_COLOR,              //字串顯示Flag                                                       
            0,                       //目前OSD頁內容(第三層OSD)                                           
            ENUM_STRING,             //目前OSD型態(字串)
            NO, 
            OverWrite,               //動作(回到上一頁)                         
            ONOFFChoiceString1,       //                                              
        },     
#endif   
      {  {0},                 //ICON位置                                       
          Str_AudioRecord,            //顯示"CAMR"字串                                
          NIL,                 //上頁ID                                         
          NIL,                 //下頁ID                                         
          NO_ICON_COLOR,       //ICON顯示Flag                                   
          DESC_COLOR,          //字串顯示Flag                                   
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                                 
          AudioRecord,         //動作(回到上一頁)         
          AudioRecordChoiceString    //                         
      }, 


      {   {0},                     //ICON位置             
          Str_RETURNAPPLY,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          DVRParamApply               //動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                   
};



//----------------------------------------------------------------------------------

#define		SDCARD_H			4
CODE BYTE SDCARDMenu[]=
			{//3,
			MENU_WIDTH,		SDCARD_H,
			TITLE_COLOR,
			CURSOR_COLOR,    
};




CODE struct DefineMenu SDCARD[]={

	    	{   {0},                    //ICON位置             
            		Str_RecordMode,             //顯示"MIRRO"字串             
            		NIL,                    //上頁ID               
            		NIL,                    //下頁ID               
            		NO_ICON_COLOR,          //ICON顯示Flag         
            		DESC_COLOR,             //字串顯示Flag         
            		RECORDSELECT,            //目前OSD頁內容(第三層OSD)     
            		OSDMENU,//CHOICEMENU,             //目前OSD型態                  
            		NO,                                            
            		0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            		RecordSelectMenu         //動作Flag             
        	},
#if 0        
		{	{0},											
			Str_Resolution,
			NIL,	
			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ENUM_STRING,
			NO,
			Resolution,
			ResolutionChoiceString
		},
#endif		
		{	{0},											
			Str_FPS,
			NIL,	
			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ENUM_STRING,
			NO,
			FPS,
			FPSChoiceString
		},
		
		{	{0},											
			Str_Quality,
			NIL,	
			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ENUM_STRING,
			NO,
			Quality,
			QualityChoiceString
		},
		
	      {     	{0},					   //ICON位置						 
		      	Str_FormatSD, 		   //顯示"RETRUN"字串				 
		  	NIL,					  //上頁ID				 
		  	NIL,					  //下頁ID				 
		  	NO_ICON_COLOR,		  //ICON顯示Flag		 
		  	DESC_COLOR,			  //字串顯示Flag		 
		  	FORMATSDSELECT,		   //目前OSD頁內容(第三層OSD)	  
		  	OSDMENU,//CHOICEMENU, 			//目前OSD型態				   
		  	NO,											 
		  	0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
		  	FORMATSDSelectMenu 	   //動作Flag				 
	  	},
	 
	  	{   {0},					   //ICON位置						 
		  	Str_FirmwareUpdate, 		   //顯示"RETRUN"字串				 
		  	NIL,					  //上頁ID				 
		  	NIL,					  //下頁ID				 
		  	NO_ICON_COLOR,		  //ICON顯示Flag		 
		  	DESC_COLOR,			  //字串顯示Flag		 
		  	FWUpdateSELECT,		   //目前OSD頁內容(第三層OSD)	  
		  	OSDMENU,//CHOICEMENU, 			//目前OSD型態				   
		  	NO,											 
		  	0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
		  	FWUpdateSelectMenu 	   //動作Flag		  
	  	},

		{   {0},                     //ICON位置                     
            		Str_RETURNAPPLY,              //顯示"RETRUN"字串             
            		NIL,                     //上頁ID                       
            		NIL,                     //下頁ID                       
            		NO_ICON_COLOR,           //ICON顯示Flag                 
            		DESC_COLOR,              //字串顯示Flag                 
            		0,                       //目前OSD頁內容(第三層OSD)     
            		ACTION,                  //目前OSD型態    Abel Test     
            		NO,                                                     
            		DVRParamApply // EXITMENU , //動作(回到上一頁)             
        	},  
        
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};
//#endif		//#ifdef SUPPORT_SDCARD	
#if 0
/*-----------------------------------------------------*/ 
/*             第二層OSD ---> AUDIO                    */ 
/*-----------------------------------------------------*/ 
#define     SOUND_H        2                                                        
CODE BYTE SoundMenu[]={//3,                                                          
    MENU_WIDTH,                                                                      
    SOUND_H,                                                                         
    TITLE_COLOR,                                                                     
    CURSOR_COLOR,};                                                                  
                                                                                     
CODE struct DefineMenu DMSound[]={                                                   
        {   {0},                     //ICON位置                                      
            Str_Volume,              //顯示字串                                      
            NIL,                     //上頁ID                                        
            NIL,                     //下頁ID                                        
            NO_ICON_COLOR,           //ICON顯示Flag                                  
            DESC_COLOR,              //字串顯示Flag                                  
            0,                                                                       
            BAR,                                                                     
            NO,                                                                      
            AUDIO_VOLUME,            //                                              
            DefaultBar                                                               
        },                                                                           
                                                                                     
        {   {0},                     //ICON位置                     
            Str_RETURN,              //顯示"RETRUN"字串             
            NIL,                     //上頁ID                       
            NIL,                     //下頁ID                       
            NO_ICON_COLOR,           //ICON顯示Flag                 
            DESC_COLOR,              //字串顯示Flag                 
            0,                       //目前OSD頁內容(第三層OSD)     
            ACTION,                  //目前OSD型態    Abel Test     
            NO,                                                     
            TOHIGHMENU // EXITMENU , //動作(回到上一頁)             
        },                                                          
                                                                                     
        {   {0},                                                
            0,//Terminator       
            0,              
            0,                                                       
            NIL,                                                                     
            NIL,                                                                     
            0,                                                                       
            0,              
            0,                                                       
        },                                                                           
};     

#endif
#if 0
//----------------------------------------------------------------------------------
#define PCCOLOR_H				4
CODE BYTE PCColorTempMenu[]=
			{//3,
			MENU_WIDTH,		PCCOLOR_H,	
			TITLE_COLOR,
			CURSOR_COLOR,
};


CODE struct DefineMenu DMPCColor[]={
		{	{0},												Str_ColorTemp,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			ENUM_STRING,			NO,
			PC_COLOR_TEMP,
			ModeChoice,
		},
		{	{0},												Str_Red,
			NIL,			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			BAR,	NO,
			PC_COLOR_R,
			DefaultBar
		},
		{	{0},												Str_Green,
			NIL,			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			BAR,	NO,
			PC_COLOR_G,
			DefaultBar
		},
		{	{0},												Str_Blue,
			NIL,			NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			BAR,	NO,
			PC_COLOR_B,
			DefaultBar
		},
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};
#endif
//============================================================================================

//============================================================================================
//Picture
#define		USER_PICTURE_H		5
CODE BYTE UserPictureMenuType[]=
			{
			MENU_WIDTH,		USER_PICTURE_H,
			TITLE_COLOR,
			CURSOR_COLOR,
};

CODE struct DefineMenu DMUserPicture[]={
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

#define		PICTURE_H		4
CODE BYTE PictureMenu[]=
			{//3,
			MENU_WIDTH,		PICTURE_H,
			TITLE_COLOR,
			CURSOR_COLOR,
};

CODE struct DefineMenu DMPicture[]={
        #if 0
		{	{0},												Str_Picture,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			ENUM_STRING,			NO,
			VIDEO_MODE,
			ModeChoice,
		},
        #endif
		{	{0},								Str_Brightness,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			#ifdef AWT_ML072S
			NUMBER,////NUMBER,
			#else
			BAR,
			#endif
			NO,
			VIDEO_BRIGHTNESS,
			DefaultBar
		},

		{	{0},								Str_Contrast,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			#ifdef AWT_ML072S
			NUMBER,////NUMBER,
			#else
			BAR,
			#endif	
			NO,
			VIDEO_CONTRAST,
			DefaultBar
		},

		{	{0},									Str_Saturation,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			#ifdef AWT_ML072S
			NUMBER,////NUMBER,
			#else
			BAR,
			#endif	
			NO,
			VIDEO_SATURATION,
			DefaultBar
		},
		{	{0},										Str_Hue,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			#ifdef AWT_ML072S
			NUMBER,////NUMBER,
			#else
			BAR,
			#endif	
			NO,
			VIDEO_HUE,
			DefaultBar
		},
		{	{0},									Str_Sharpness,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			#ifdef AWT_ML072S
			NUMBER,////NUMBER,
			#else
			BAR,
			#endif	
			NO,
			VIDEO_SHARPNESS,
			DefaultBar
		},
        {   
            {0},                     //ICON位置                     
            Str_RETURN,              //顯示"RETRUN"字串             
            NIL,                     //上頁ID                       
            NIL,                     //下頁ID                       
            NO_ICON_COLOR,           //ICON顯示Flag                 
            DESC_COLOR,              //字串顯示Flag                 
            0,                       //目前OSD頁內容(第三層OSD)     
            ACTION,                  //目前OSD型態(設定動作)     
            NO,                                                     
            TOHIGHMENU               //動作(回到上一頁)             
        },                           
		



		#if 0
		{	{0},									Str_Backlight,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			BAR,	NO,
			VIDEO_BACKLIGHT,
			DefaultBar
		},
        #endif
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

/*-----------------------------------------------------*/ 
/*         第三層OSD ---> CAMERA --->MIRROR            */ 
/*-----------------------------------------------------*/ 
#define CAMSELECT_H  5                                  
CODE BYTE CAMSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    CAMSELECT_H,          //第三層OSD ---> UTILITY --->Input   
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     CAMSELECT OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu DMCAMSELECT[]={                                       
      {   {0},                 //ICON位置                                      
          Str_CAMA,            //顯示"CAMA"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          CAMAONOFF,           //動作(回到上一頁)         
          ONOFFChoiceString    //                         
      },                                                                       
#ifndef AWT_ML072S  
      {   {0},                 //ICON位置                                      
          Str_CAMB,            //顯示"CAMB"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          CAMBONOFF,         //動作(回到上一頁)         
          ONOFFChoiceString    //                         
      }, 
 #endif     
#ifdef QUAD                                                                               
      {   {0},                 //ICON位置                                      
          Str_CAMC,            //顯示"CAMC"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          CAMCONOFF,         //動作(回到上一頁)         
          ONOFFChoiceString    //                         
      },                                                                       
#endif                                                                               
       {  {0},                 //ICON位置                                       
          Str_CAMR,            //顯示"CAMR"字串                                
          NIL,                 //上頁ID                                         
          NIL,                 //下頁ID                                         
          NO_ICON_COLOR,       //ICON顯示Flag                                   
          DESC_COLOR,          //字串顯示Flag                                   
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                                 
          CAMRONOFF,         //動作(回到上一頁)         
          ONOFFChoiceString    //                         
      },                                                                       
                    

      {   {0},                     //ICON位置             
          Str_RETURN,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU               //動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                   
};

//#ifndef	AWT_ML072Q  //Pinchi 20140918 add for AWT ML072Q
#ifdef  SUPPORT_ML84TQ_TRIGGER_DELAY  //Pinchi 20150825 add for function define
/*-----------------------------------------------------*/ 
/* 第四層OSD ---> CAMERA --->TRIGGER SET-->trigger delay  */ 
/*-----------------------------------------------------*/ 
#define 	TRIGGERDELAYSELECT_H  5                                  
CODE BYTE TRIGGERDELAYMenu[]={                                    
    MENU_WIDTH,                                                  
    TRIGGERDELAYSELECT_H,          //第三層OSD ---> UTILITY --->Input   
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     CAMSELECT OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu TRIGGERDELAYSELECT[]={      

      {   {0},                 //ICON位置                                      
          Str_CAMA,            //顯示"CAMA"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          NUMBER,         //目前OSD型態    Abel Test 
          NO,                                             
          DELAYCAMA,           //動作(回到上一頁)         
          DefaultBar    //                         
      },                                                                       
                                                                               
      {   {0},                 //ICON位置                                      
          Str_CAMB,            //顯示"CAMB"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          NUMBER,         //目前OSD型態    Abel Test 
          NO,                                             
          DELAYCAMB,         //動作(回到上一頁)         
          DefaultBar    //                         
      },                                                                       
                                                                               
      {   {0},                 //ICON位置                                      
          Str_CAMC,            //顯示"CAMC"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          NUMBER,         //目前OSD型態    Abel Test 
          NO,                                             
          DELAYCAMC,         //動作(回到上一頁)         
          DefaultBar    //                         
      }, 
  #ifdef USE_CAMD    
             {  {0},                 //ICON位置                                       
          Str_CAMD,            //顯示"CAMR"字串                                
          NIL,                 //上頁ID                                         
          NIL,                 //下頁ID                                         
          NO_ICON_COLOR,       //ICON顯示Flag                                   
          DESC_COLOR,          //字串顯示Flag                                   
          0,
          NUMBER,         //目前OSD型態    Abel Test 
          NO,                                                 
          DELAYCAMD,         //動作(回到上一頁)         
          DefaultBar    //                         
      },     
#endif                                                                               
       {  {0},                 //ICON位置                                       
          Str_CAMR,            //顯示"CAMR"字串                                
          NIL,                 //上頁ID                                         
          NIL,                 //下頁ID                                         
          NO_ICON_COLOR,       //ICON顯示Flag                                   
          DESC_COLOR,          //字串顯示Flag                                   
          0,
          NUMBER,         //目前OSD型態    Abel Test 
          NO,                                                 
          DELAYCAMR,         //動作(回到上一頁)         
          DefaultBar    //                         
      },                                                                       
                    

      {   {0},                     //ICON位置             
          Str_RETURN,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU               //動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                   
};
#endif

#ifdef AWT_ADD_TRIGGER_DELAY_FUN  //Pinchi 20150209 add

/*------------------------------*/
/*   TRIGGER DELAY SELECT OSD Menu    */
/*------------------------------*/
CODE struct DefineMenu DelaySelectMenu[]={
      {   {0},                     //ICON位置
          Str_CamADelay,           //顯示"CAM A"字串
          NIL,                     //上頁ID
          NIL,                     //下頁ID
          NO_ICON_COLOR,           //ICON顯示Flag
          DESC_COLOR,              //字串顯示Flag
          0,
          #ifdef AWT_ML072S
          NUMBER,                     //目前OSD型態  
	   #else
          BAR,                     //目前OSD型態
          #endif
          NO,
          TRIGGER_CamADelay,      //動作(回到上一頁)
          DefaultBar
      },
#ifndef AWT_ML072S
      {   {0},                     //ICON位置
          Str_CamBDelay,           //顯示"CAM B"字串
          NIL,                     //上頁ID
          NIL,                     //下頁ID
          NO_ICON_COLOR,           //ICON顯示Flag
          DESC_COLOR,              //字串顯示Flag
          0,
          BAR,                     //目前OSD型態
          NO,
          TRIGGER_CamBDelay,      //動作(回到上一頁)
          DefaultBar
      },

      {   {0},                     //ICON位置
          Str_CamCDelay,           //顯示"CAM C"字串
          NIL,                     //上頁ID
          NIL,                     //下頁ID
          NO_ICON_COLOR,           //ICON顯示Flag
          DESC_COLOR,              //字串顯示Flag
          0,
          BAR,                     //目前OSD型態
          NO,
          TRIGGER_CamCDelay,      //動作(回到上一頁)
          DefaultBar
      },
#endif
      {   {0},                     //ICON位置
          Str_CamRDelay,           //顯示"CAM R"字串
          NIL,                     //上頁ID
          NIL,                     //下頁ID
          NO_ICON_COLOR,           //ICON顯示Flag
          DESC_COLOR,              //字串顯示Flag
          0,
          #ifdef AWT_ML072S
          NUMBER,                     //目前OSD型態  
	   #else
          BAR,                     //目前OSD型態
          #endif
          NO,
          TRIGGER_CamRDelay,      //動作(回到上一頁)
          DefaultBar
      },
      
#ifdef AWT_ML072S
      {   {0},                     //ICON位置
          Str_CamCDelay,           //顯示"CAM C"字串
          NIL,                     //上頁ID
          NIL,                     //下頁ID
          NO_ICON_COLOR,           //ICON顯示Flag
          DESC_COLOR,              //字串顯示Flag
          0,
          #ifdef AWT_ML072S
          NUMBER,                     //目前OSD型態  
	   #else
          BAR,                     //目前OSD型態
          #endif
          NO,
          TRIGGER_CamCDelay,      //動作(回到上一頁)
          DefaultBar
      },
#endif

      {   {0},                     //ICON位置
          Str_RETURN,              //顯示"RETRUN"字串
          NIL,                     //上頁ID
          NIL,                     //下頁ID
          NO_ICON_COLOR,           //ICON顯示Flag
          DESC_COLOR,              //字串顯示Flag
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態
          NO,
          TOHIGHMENU               //動作(回到上一頁)
      },

      {   {0},
          0,  //Terminator
          0,
          0,
          NIL,
          NIL,
          0,
          0,
          0,
      },
};

#endif
/*-----------------------------------------------------*/ 
/*         第三層OSD ---> CAMERA --->TRIGGER            */ 
/*-----------------------------------------------------*/ 
#define TRIGGERSELECT_H  5                                  
CODE BYTE TRIGGERSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    TRIGGERSELECT_H,          //第三層OSD ---> UTILITY --->Input   
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     TRIGGERSELECT OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu DMTRIGGERSELECT[]={  

      {   {0},                 //ICON位置                                      
          Str_DIR_IMAGE_CAMA,            //顯示"CAMA"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          IMAGE_A_Choice,           //動作(回到上一頁)         
          IMAGE_A_String//                         
      },                                                                       
                                                                               
      {   {0},                 //ICON位置                                      
          Str_DIR_IMAGE_CAMB,            //顯示"CAMB"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          IMAGE_B_Choice,         //動作(回到上一頁)         
          IMAGE_B_String//                         
      },                                                                       
                                                                               
      {   {0},                 //ICON位置                                      
          Str_DIR_IMAGE_CAMC,            //顯示"CAMC"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          IMAGE_C_Choice,         //動作(回到上一頁)         
          IMAGE_C_String//                         
      }, 
 #if 0     
        {   {0},                     //ICON位置                        
            Str_REAR_SETUP,          //顯示"Rear Setup"字串               
            NIL,                     //上頁ID                          
            NIL,                     //下頁ID                          
            NO_ICON_COLOR,           //ICON顯示Flag                    
            DESC_COLOR,              //字串顯示Flag                    
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,//ACTION,    //目前OSD型態(字串)     
            NO,                                                 
            REARChoice,              //動作(回到上一頁)         
            REARString,                                        
        },                                                                
              
        {   {0},                     //ICON位置                        
            Str_TriggerVGA,          //顯示"Rear Setup"字串               
            NIL,                     //上頁ID                          
            NIL,                     //下頁ID                          
            NO_ICON_COLOR,           //ICON顯示Flag                    
            DESC_COLOR,              //字串顯示Flag                    
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,//ACTION,    //目前OSD型態(字串)     
            NO,                                                 
            TriggerVGA,              //動作(回到上一頁)         
            ONOFFChoiceString,                                        
        },    

        {   {0},                    //ICON位置             
            Str_TriggerDelay,             //顯示"MIRRO"字串             
            NIL,                    //上頁ID               
            NIL,                    //下頁ID               
            NO_ICON_COLOR,          //ICON顯示Flag         
            DESC_COLOR,             //字串顯示Flag         
            TRIGGERDELAYSELECT,            //目前OSD頁內容(第三層OSD)     
            OSDMENU,//CHOICEMENU,             //目前OSD型態                  
            NO,                                            
            0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            InputSelectMenu         //動作Flag             
        }, 
#endif
      {   {0},                     //ICON位置             
          Str_RETURN,              //顯示"RETRUN"字串     
          NIL,                     //上頁ID               
          NIL,                     //下頁ID               
          NO_ICON_COLOR,           //ICON顯示Flag         
          DESC_COLOR,              //字串顯示Flag         
          0,                       //目前OSD頁內容(第三層O
          ACTION,                  //目前OSD型態    Abel T
          NO,                                             
          TOHIGHMENU               //動作(回到上一頁)     
      },                                                  
                                                           
      {   {0},                                       
          0,//Terminator   
          0,               
          0,               
          NIL,             
          NIL,             
          0,               
          0,               
          0,               
      },                   
};

/*-----------------------------------------------------*/  
/*             第二層OSD ---> CAMERA                   */  
/*-----------------------------------------------------*/  
#define     CAMERA_H   8 //ryan@20170904	7 //  5 

CODE BYTE CAMERAMenu[]={                          
    MENU_WIDTH,                                            
    CAMERA_H,                                           
    TITLE_COLOR,                                           
    CURSOR_COLOR,};                                        
                                                           
CODE struct DefineMenu DMCAMERA[]={       

	#ifndef AWT_ML072S
        {   {0},                    //ICON位置             
            Str_MIRROR,             //顯示"MIRRO"字串             
            NIL,                    //上頁ID               
            NIL,                    //下頁ID               
            NO_ICON_COLOR,          //ICON顯示Flag         
            DESC_COLOR,             //字串顯示Flag         
            DMCAMSELECT,            //目前OSD頁內容(第三層OSD)     
            OSDMENU,//CHOICEMENU,             //目前OSD型態                  
            NO,                                            
            0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            InputSelectMenu         //動作Flag             
        },     
	#else
       {   {0},                 //ICON位置                                      
          Str_CAMA,            //顯示"CAMA"字串                               
          NIL,                 //上頁ID                                        
          NIL,                 //下頁ID                                        
          NO_ICON_COLOR,       //ICON顯示Flag                                  
          DESC_COLOR,          //字串顯示Flag                                  
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                             
          CAMAONOFF,           //動作(回到上一頁)         
          ONOFFChoiceString    //                         
      },         
      #ifdef HS
	{  {0}, 				//ICON位置										 
	 Str_CAMB,			  //顯示"CAMR"字串								  
	 NIL,				  //上頁ID										   
	 NIL,				  //下頁ID										   
	 NO_ICON_COLOR, 	  //ICON顯示Flag								   
	 DESC_COLOR,		  //字串顯示Flag								   
	 0,
	 ENUM_STRING,		  //目前OSD型態    Abel Test 
	 NO,												 
	 CAMBONOFF, 		//動作(回到上一頁)		   
	 ONOFFChoiceString	  //						 
	 },    
	 #endif

       {  {0},                 //ICON位置                                       
          Str_CAMR,            //顯示"CAMR"字串                                
          NIL,                 //上頁ID                                         
          NIL,                 //下頁ID                                         
          NO_ICON_COLOR,       //ICON顯示Flag                                   
          DESC_COLOR,          //字串顯示Flag                                   
          0,
          ENUM_STRING,         //目前OSD型態    Abel Test 
          NO,                                                 
          CAMRONOFF,         //動作(回到上一頁)         
          ONOFFChoiceString    //                         
      },    
	#endif

     //V1.1 03/19/07 simonsung    
	#ifdef QUAD		
	  #ifdef AWT_ML072Q
        {   {0},                    //ICON位置             
            Str_TriggerSet,             //顯示"Dir Image"字串             
            NIL,                    //上頁ID               
            NIL,                    //下頁ID               
            NO_ICON_COLOR,          //ICON顯示Flag         
            DESC_COLOR,             //字串顯示Flag         
            DMTRIGGERSELECT,            //目前OSD頁內容(第三層OSD)     
            OSDMENU,//CHOICEMENU,             //目前OSD型態                  
            NO,                                            
            0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            InputSelectMenu         //動作Flag             
        },   
	  #else  //HTRV
         {   {0},                     //ICON位置                        
            Str_DIR_IMAGE,           //顯示"Dir Image"字串               
            NIL,                     //上頁ID                          
            NIL,                     //下頁ID                          
            NO_ICON_COLOR,           //ICON顯示Flag                    
            DESC_COLOR,              //字串顯示Flag                    
            0,                       //目前OSD頁內容(第三層OSD)        
            ENUM_STRING,//ACTION,    //目前OSD型態(字串)        
            NO,               
            IMAGEChoice,             //動作(回到上一頁) 
            IMAGEString, 
        },
	  #endif

        {   {0},                     //ICON位置                        
            Str_REAR_SETUP,          //顯示"Rear Setup"字串               
            NIL,                     //上頁ID                          
            NIL,                     //下頁ID                          
            NO_ICON_COLOR,           //ICON顯示Flag                    
            DESC_COLOR,              //字串顯示Flag                    
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,//ACTION,    //目前OSD型態(字串)     
            NO,                                                 
            REARChoice,              //動作(回到上一頁)         
            REARString,
        },

        {   {0},                    //ICON位置                                           
            Str_JUMP,               //顯示"JUMP"字串                             
            NIL,                    //上頁ID                                             
            NIL,                    //下頁ID                                             
            NO_ICON_COLOR,          //ICON顯示Flag                                       
            DESC_COLOR,             //字串顯示Flag        
            0,                      //目前OSD頁內容(第三層OSD) 
            ENUM_STRING,            //目前OSD型態    Abel Test 
            NO,                                                 
            JUMPChoice,             //動作(回到上一頁)         
            JUMPString                                        
        },      

	    {   {0},                    //ICON位置                    
            Str_CAM_OUT,            //顯示"CAM OUT"字串             
            NIL,                    //上頁ID                      
            NIL,                    //下頁ID                      
            NO_ICON_COLOR,          //ICON顯示Flag                
            DESC_COLOR,             //字串顯示Flag                
            0,                      //目前OSD頁內容(第三層OSD)    
            ENUM_STRING,            //目前OSD型態    Abel Test 
            NO,                                                 
            CAMOUTChoice,           //動作(回到上一頁)         
            CAMOUTString,                                        
        },    
 	#endif

        {   {0},                    //ICON位置                    
            Str_SEQ_TIME_STEP,      //顯示"SEQ TIME STEP"字串             
            NIL,                    //上頁ID                      
            NIL,                    //下頁ID                      
            NO_ICON_COLOR,          //ICON顯示Flag                
            DESC_COLOR,             //字串顯示Flag            
            0,                      //目前OSD頁內容(第三層OSD)     
			#ifdef AWT_ML072S
			NUMBER,////NUMBER,
			#else
			BAR,
			#endif 
			NO,                                                     
            STIME_STEP,             //動作(回到上一頁)              
            DefaultBar              //選擇字串                                
        },     
        
#if  (defined AWT_ADD_TRIGGER_DELAY_FUN) //add by ryan@20170824
	#ifndef AWT_ML072S
        {   {0},                     //ICON位置
            Str_TriggerDelay,        //顯示"Trigger Delay"字串
            NIL,                     //上頁ID
            NIL,                     //下頁ID
            NO_ICON_COLOR,           //ICON顯示Flag
            DESC_COLOR,              //字串顯示Flag
            DelaySelectMenu,         //目前OSD頁內容(第三層OSD)
            OSDMENU,                 //目前OSD型態(字串) 
            NO,
            0,                       //動作(回到上一頁) 
            InputSelectMenu, 
        },
        #endif
#endif

	#ifdef AWT_ML072S
	 {   {0},                    //ICON位置                    
            Str_JumpAV,       //顯示"JumpAV"字串             
            NIL,                    //上頁ID                      
            NIL,                    //下頁ID                      
            NO_ICON_COLOR,          //ICON顯示Flag                
            DESC_COLOR,             //字串顯示Flag            
            0,                      //目前OSD頁內容(第三層OSD)     
            ENUM_STRING,                    //目前OSD型態(調整String)          
            NO,                                                     
            JUMP_AV,             //動作(回到上一頁)              
            ONOFFChoiceString//選擇字串                                
        },  
	#ifdef HS
	#else
	{   {0},                     //ICON位置
            Str_TriggerDelay,        //顯示"Trigger Delay"字串
            NIL,                     //上頁ID
            NIL,                     //下頁ID
            NO_ICON_COLOR,           //ICON顯示Flag
            DESC_COLOR,              //字串顯示Flag
            DelaySelectMenu,         //目前OSD頁內容(第三層OSD)
            OSDMENU,                 //目前OSD型態(字串) 
            NO,
            0,                       //動作(回到上一頁) 
            InputSelectMenu, 
        },
        #endif
	  {   {0},					   //ICON位置						 
		  Str_RECALL,			   //顯示"RETRUN"字串				 
		  NIL,					   //上頁ID 						 
		  NIL,					   //下頁ID 						 
		  NO_ICON_COLOR,		   //ICON顯示Flag					 
		  DESC_COLOR,			   //字串顯示Flag					 
		  0,					   //目前OSD頁內容(第三層OSD)		 
		  ACTION,				   //目前OSD型態	Abel Test		 
		  NO,														 
		  RESET_VIDEOVALUE ,	   //動作(回到上一頁)				 
	  },
	#endif
 
        {   {0},                     //ICON位置                  
            Str_RETURN,              //顯示"RETRUN"字串           
            NIL,                     //上頁ID                    
            NIL,                     //下頁ID                    
            NO_ICON_COLOR,           //ICON顯示Flag              
            DESC_COLOR,              //字串顯示Flag              
            0,                       //目前OSD頁內容(第三層OSD)  
            ACTION,                  //目前OSD型態    Abel Test             
            NO,                                                 
            TOHIGHMENU // EXITMENU , //動作(回到上一頁)                             
        },                                           
                                
        {   {0},                                           
            0,//Terminator                                 
            0,                                             
            0,                                             
            NIL,                                           
            NIL,                                           
            0,                                             
            0,                                             
            0,                                             
        },                                                 
};                                                        

//----------------------------------------------------------------------------------
CODE BYTE TVMainMenu[]=
			{//4,
			TOPMENU_WIDTH,		TOPMENU_HEIGHT,
			NIL,
			DEFAULT_COLOR,
};
CODE struct DefineMenu DMMainMenu[]={

	    {
			TV_ICON,                //Display的ICON
            0,//Str_Picture,           //顯示字串
            NIL,                    //上頁ID
            NIL,                    //下頁ID
            TOPICON_COLOR,          //ICON顯示Flag(ON)
            NIL,                    //字串顯示Flag(OFF)
            DMPicture,              //目前OSD頁內容(第二層OSD)
            OSDMENU,                //目前OSD型態
            NO,
            VIDEOPICTURE,
            PictureMenu
        },

		{	INPUT_ICON,
		    0,
			NIL,
			NIL,
			TOPICON_COLOR,
			NIL,
			DMINPUTSOURCE,
			OSDMENU,
			NO,
			0,
			InputSourceMenu
		},

		{	VIDEO_ICON,
		    0,
			NIL,
			NIL,
			TOPICON_COLOR,
			NIL,
			DMCAMERA,
			OSDMENU,
			NO,
			VIDEOPICTURE,
			CAMERAMenu
		},

	#ifdef SUPPORT_SDCARD
		{	RECORDSDCARD_ICON,								
			0,
			NIL,	NIL,	
			TOPICON_COLOR,
			NIL,
			SDCARD,
			OSDMENU,
			NO,
			0,
			SDCARDMenu
		},
	#endif

	#ifdef AWT_ML072S
        {   UTIL_ICON,                 //Display的ICON
            0,//Str_Utility,               //顯示字串
            NIL,                       //上頁ID
            NIL,                       //下頁ID
            TOPICON_COLOR,             //ICON顯示Flag(ON)
            NIL,                       //字串顯示Flag(OFF)
            DMUtility,                 //目前OSD頁內容(第二層OSD)
            TEXT_STR_exit,             //Ryan
            NO,
            0,
            UtilityMenu
        },
	#else
		{	UTIL_ICON,
		    0,
			NIL,
			NIL,
			TOPICON_COLOR,
			NIL,
			DMUtility,
			OSDMENU,
			NO,
			0,
			UtilityMenu
		},
	#endif

		{	0,
			0,				//Terminator
			0,
			0,
			NIL,
			NIL,
			0,
			0,
			0,
		},
};

//----------------------------------------------------------------------------------
CODE struct DefineMenu DefaultMenu[]={
////	WORD						Icon[ICON_BUF_SZ];
//  CODE_P	BYTE				*Icon;
//	CODE_P	BYTE				**Desc;
//	BYTE						PreFnId, 
//								PostFnId;
//	BYTE						IconColor;			//NIL: not to display icon
//	BYTE						DescColor;			//NIL: not to display desc. (IconColor==NIL && DescColor==NIL)->Last Item
//	CODE_P struct DefineMenu	*Child;
//	BYTE						Type;				// MENU, CHOICEMENU, BAR, NUMBER, TIME, ACTION, YESNO
//	BYTE						ActiveWithCursor;
//	BYTE						Id;
//	CODE_P BYTE					*TypeData;	//MenuType, BarType, NumType,,,
		{	0,										0,
			NIL,	NIL,	
			ICON_COLOR,
			NIL,
			DMMainMenu,
			OSDMENU,		NO,
			0,
			TVMainMenu
		},
		{	0,												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};


//#endif

/*		//Weylis -@121008  
#ifdef HS_NEWOSDMENU
CODE struct DefineMenu OSDSetupMenu[]={
////	WORD						Icon[ICON_BUF_SZ];
//  CODE_P	BYTE				*Icon;
//	CODE_P	BYTE				**Desc;
//	BYTE						PreFnId, 
//								PostFnId;
//	BYTE						IconColor;			//NIL: not to display icon
//	BYTE						DescColor;			//NIL: not to display desc. (IconColor==NIL && DescColor==NIL)->Last Item
//	CODE_P struct DefineMenu	*Child;
//	BYTE						Type;				// MENU, CHOICEMENU, BAR, NUMBER, TIME, ACTION, YESNO
//	BYTE						ActiveWithCursor;
//	BYTE						Id;
//	CODE_P BYTE					*TypeData;	//MenuType, BarType, NumType,,,
		{	0,										
			0,
			NIL,
			NIL,	
			ICON_COLOR,
			NIL,
			OSDMainMenu,
			OSDMENU,		
			NO,
			0,
			TVMainMenu
		},
		{	
			0,												
			0,//Terminator
			0,				
			0,		
			NIL,
			NIL,
			0,
			0,				
			0,
		},
};
#endif
*/
//============================================================================================
#ifdef SUPPORT_PC

//----------------------------------------------------------------------------------
#define		PCUTILITY_H			3
CODE BYTE PCUtilityMenu[]=
			{//3,
			MENU_WIDTH,		PCUTILITY_H,
			TITLE_COLOR,
			CURSOR_COLOR,
};

CODE struct DefineMenu DMPCUtility[]={
#ifdef AWT_ML073G
       {   {0},                     //ICON位置                        
              Str_RECALL,              //顯示"RETRUN"字串                
              NIL,                     //上頁ID                          
              NIL,                     //下頁ID                          
              NO_ICON_COLOR,           //ICON顯示Flag                    
              DESC_COLOR,              //字串顯示Flag                    
              DMRecallSELECT,                       //目前OSD頁內容(第三層OSD)        
              OSDMENU,             //目前OSD型態(字串) 
              NO,                                                 
              0,
              InputSelectMenu,       //                        
          },
     
 #else         
		{	{0},					 //ICON位置 					   
			Str_RECALL, 			 //顯示"RETRUN"字串 			   
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR, 			 //字串顯示Flag 				   
			0,						 //目前OSD頁內容(第三層OSD) 	   
			ACTION, 				 //目前OSD型態	  Abel Test 	   
			NO, 													   
			RESET_PCVALUE ,		 //動作(回到上一頁) 			   
		},
#endif
		

		{	{0},					 //ICON位置 					   
			Str_EXIT,				 //顯示"RETRUN"字串 			   
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR, 			 //字串顯示Flag 				   
			0,						 //目前OSD頁內容(第三層OSD) 	   
			ACTION, 				 //目前OSD型態	  Abel Test 	   
			NO, 													   
			EXITMENU ,				 //動作(回到上一頁) 			   
		},		  
#if 0		
		{	{0},					 //ICON位置 					   
			Str_SPACE,				  //顯示"RETRUN"字串				
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			DESC_COLOR, 			 //字串顯示Flag 				   
			0,						 //目前OSD頁內容(第三層OSD) 	   
			TEXT_STR,				   //目前OSD型態	Abel Test		 
			NO, 													   
			EXITMENU ,				 //動作(回到上一頁) 			   
		},	 
	  
		{	{0},					 //ICON位置 					   
			Str_VER,				//顯示"RETRUN"字串				  
			NIL,					 //上頁ID						   
			NIL,					 //下頁ID						   
			NO_ICON_COLOR,			 //ICON顯示Flag 				   
			VER_COLOR,				//字串顯示Flag					  
			0,						 //目前OSD頁內容(第三層OSD) 	   
			TEXT_STR,				   //目前OSD型態	Abel Test		 
			NO, 													   
			EXITMENU ,				 //動作(回到上一頁) 			   
		},			
#endif	
		{ {0},																		
		  0,//Terminator															
		  0,																		
		  0,																		
		  NIL,																		
		  NIL,																		
		  0,																		
		  0,																		
		  0,																		
		},	

};


//----------------------------------------------------------------------------------
#define		PCPICTURE_H		6
CODE BYTE PCPictureMenu[]=
			{//3,
			MENU_WIDTH,		PCPICTURE_H,
			TITLE_COLOR,
			CURSOR_COLOR,
};

CODE struct DefineMenu DMPCPicture[]={
		{	{0},								Str_Brightness,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,			NO,
			PANEL_BRIGHTNESS,
			DefaultBar
		},
		{	{0},								Str_Contrast,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,			NO,
			PANEL_CONTRAST,
			DefaultBar
		},
		{	{0},									Str_HPosition,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,	NO,
			PC_HPOS,
			DefaultBar
		},
		{	{0},									Str_VPosition,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,	NO,
			PC_VPOS,
			DefaultBar
		},
		#if 0
		{	{0},								Str_Phase,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,	NO,
			PC_PHASE,
			NumberOnly
		},
		{	{0},								Str_Clock,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,	NO,
			PC_CLOCK,
			NumberOnly
		},
		#endif

		{	{0},									Str_AutoAdjust,
			NIL,		NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,NO,
			AUTOADJUST
		},
		{	{0},									Str_AutoColor,
			NIL,		NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,NO,
			PCCOLORADJUST
		},

		
        {   {0},                     //ICON位置                  
            Str_RETURN,              //顯示"RETRUN"字串           
            NIL,                     //上頁ID                    
            NIL,                     //下頁ID                    
            NO_ICON_COLOR,           //ICON顯示Flag              
            DESC_COLOR,              //字串顯示Flag              
            0,                       //目前OSD頁內容(第三層OSD)  
            ACTION,                  //目前OSD型態    Abel Test             
            NO,                                                 
            TOHIGHMENU // EXITMENU , //動作(回到上一頁)                             
        },  

		
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

//----------------------------------------------------------------------------------
CODE BYTE PCMainMenu[]=
			{//4,
			TOPMENU_WIDTH,		TOPMENU_HEIGHT,		
			NIL,
			DEFAULT_COLOR,
};

CODE struct DefineMenu DMPCMenuList[]={

		{	{TV_ICON},									
			0,//Str_Picture,
			NIL,	
			NIL,	
			TOPICON_COLOR,
			NIL,
			DMPCPicture,
			OSDMENU,		NO,
			0,
			PCPictureMenu
		},
#ifdef Holtz
		
		{	VIDEO_ICON,								
		    0,
			NIL,	
			NIL,	
			TOPICON_COLOR,
			NIL,
			DMCAMERA,
			OSDMENU,		NO,
			VIDEOPICTURE,
			CAMERAMenu
		},

		{	{INPUT_ICON},									
			0,//Str_Input,
			NIL,	NIL,	
			TOPICON_COLOR,
			NIL,
			DMINPUTSOURCE,
			OSDMENU,		NO,
			0,
			InputSourceMenu
		},
#else
		{	{INPUT_ICON},									
			0,//Str_Input,
			NIL,	NIL,	
			TOPICON_COLOR,
			NIL,
			DMINPUTSOURCE,
			OSDMENU,		NO,
			0,
			InputSourceMenu
		},
		
		{	VIDEO_ICON,								
		    0,
			NIL,	
			NIL,	
			TOPICON_COLOR,
			NIL,
			DMCAMERA,
			OSDMENU,		NO,
			VIDEOPICTURE,
			CAMERAMenu
		},
#endif		

#ifdef SUPPORT_SDCARD	       
		{	{RECORDSDCARD_ICON},										
			0,
			NIL,	NIL,	
			TOPICON_COLOR,
			NIL,
			SDCARD,
			OSDMENU,		NO,
			0,
			SDCARDMenu
		},
#endif	//#ifdef SUPPORT_SDCARD			

		{	UTIL_ICON,										
		    0,
			NIL,	NIL,	
			TOPICON_COLOR,
			NIL,
			DMUtility,//DMPCUtility,
			OSDMENU,		NO,
			0,
			UtilityMenu//PCUtilityMenu
		},
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};


//----------------------------------------------------------------------------------
CODE struct DefineMenu PCMenu[]={
		//{	icon,										desc,
		//	PreFn,	PostFn,	
		//  IconColor,
		//  DescColor,
		// 	*chd,
		//  type,		DispWithCursor		
		//	*typedata
		//},
		{	0,					0,
			NIL,	NIL,	
			ICON_COLOR,
			NIL,
			DMPCMenuList,		OSDMENU,		NO,
			0,
			PCMainMenu
		},
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

//----------------------------------------------------------------------------------

#ifdef E_Wintek

CODE struct DefineMenu ChinesePicture[]={
		{	{0},								
			Str_Brightness2,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,	
			NO,
			VIDEO_BRIGHTNESS,
			DefaultBar
		},

		{	{0},								
			Str_Contrast2,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,	
			NO,
			VIDEO_CONTRAST,
			DefaultBar
		},

		{	{0},									
			Str_Saturation2,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			NUMBER,	
			NO,
			VIDEO_SATURATION,
			DefaultBar
		},
				
	        {   
	            {0},                     //ICON位置                     
	            Str_RETURN2,              //顯示"RETRUN"字串             
	            NIL,                     //上頁ID                       
	            NIL,                     //下頁ID                       
	            NO_ICON_COLOR,           //ICON顯示Flag                 
	            DESC_COLOR,              //字串顯示Flag                 
	            0,                       //目前OSD頁內容(第三層OSD)     
	            ACTION,                  //目前OSD型態(設定動作)     
	            NO,                                                     
	            TOHIGHMENU               //動作(回到上一頁)             
	        },                           
		



		#if 0
		{	{0},									Str_Backlight,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,	
			BAR,	NO,
			VIDEO_BACKLIGHT,
			DefaultBar
		},
        #endif
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

CODE struct DefineMenu ChineseUtility[]={

	    {   {0},                     //ICON位置                                          
            Str_Auto_Day_Night2,      //顯示"Auto Day & Night"字串 
            NIL,                     //上頁ID                     
            NIL,                     //下頁ID                                                     
            NO_ICON_COLOR,           //ICON顯示Flag                                                       
            DESC_COLOR,              //字串顯示Flag                                                       
            0,                       //目前OSD頁內容(第三層OSD)                                           
            ENUM_STRING,             //目前OSD型態(字串)
            NO, 
            DayChoice,               //動作(回到上一頁)                         
            ONOFFChineseChoiceString,       //                                              
        },    

	  {   {0},                     //ICON位置                        
            Str_DIR_IMAGE2,           //顯示"Dir Image"字串               
            NIL,                     //上頁ID                          
            NIL,                     //下頁ID                          
            NO_ICON_COLOR,           //ICON顯示Flag                    
            DESC_COLOR,              //字串顯示Flag                    
            0,                       //目前OSD頁內容(第三層OSD)        
            ENUM_STRING,//ACTION,    //目前OSD型態(字串)        
            NO,               
            IMAGEChoice,             //動作(回到上一頁) 
            IMAGEChineseString, 
        },                                                             

        {   {0},                     //ICON位置                        
            Str_REAR_SETUP2,          //顯示"Rear Setup"字串               
            NIL,                     //上頁ID                          
            NIL,                     //下頁ID                          
            NO_ICON_COLOR,           //ICON顯示Flag                    
            DESC_COLOR,              //字串顯示Flag                    
            0,                       //目前OSD頁內容(第三層OSD)
            ENUM_STRING,//ACTION,    //目前OSD型態(字串)     
            NO,                                                 
            REARChoice,              //動作(回到上一頁)         
            REARString,                                        
        },    

        {   {0},                    //ICON位置                                           
            Str_JUMP2,               //顯示"JUMP"字串                             
            NIL,                    //上頁ID                                             
            NIL,                    //下頁ID                                             
            NO_ICON_COLOR,          //ICON顯示Flag                                       
            DESC_COLOR,             //字串顯示Flag        
            0,                      //目前OSD頁內容(第三層OSD) 
            ENUM_STRING,            //目前OSD型態    Abel Test 
            NO,                                                 
            JUMPChoice,             //動作(回到上一頁)         
            JUMPChineseString                                        
        }, 
        
	  {
		{0},					   //ICON位置						 
		  Str_RECALL2,			   //顯示"RETRUN"字串				 
		  NIL,					   //上頁ID 						 
		  NIL,					   //下頁ID 						 
		  NO_ICON_COLOR,		   //ICON顯示Flag					 
		  DESC_COLOR,			   //字串顯示Flag					 
		  0,					   //目前OSD頁內容(第三層OSD)		 
		  ACTION,				   //目前OSD型態	Abel Test		 
		  NO,														 
		  RESET_USERVALUE,	   //動作(回到上一頁)				 
	  },

          {   {0},                     //ICON位置                        
              Str_EXIT2,                //顯示"RETRUN"字串                
              NIL,                     //上頁ID                          
              NIL,                     //下頁ID                          
              NO_ICON_COLOR,           //ICON顯示Flag                    
              DESC_COLOR,              //字串顯示Flag                    
              0,                       //目前OSD頁內容(第三層OSD)        
              ACTION,                  //目前OSD型態    Abel Test        
              NO,                                                        
              EXITMENU ,               //動作(回到上一頁)                
          },        

#if 0         
          {   {0},                     //ICON位置                        
              Str_SPACE,                //顯示"RETRUN"字串                
              NIL,                     //上頁ID                          
              NIL,                     //下頁ID                          
              NO_ICON_COLOR,           //ICON顯示Flag                    
              DESC_COLOR,              //字串顯示Flag                    
              0,                       //目前OSD頁內容(第三層OSD)        
              TEXT_STR,                  //目前OSD型態    Abel Test        
              NO,                                                        
              EXITMENU ,               //動作(回到上一頁)                
          },   
        
          {   {0},                     //ICON位置                        
              Str_VER,                //顯示"RETRUN"字串                
              NIL,                     //上頁ID                          
              NIL,                     //下頁ID                          
              NO_ICON_COLOR,           //ICON顯示Flag                    
              VER_COLOR,              //字串顯示Flag                    
              0,                       //目前OSD頁內容(第三層OSD)        
              TEXT_STR,                  //目前OSD型態    Abel Test        
              NO,                                                        
              EXITMENU ,               //動作(回到上一頁)                
          },          
#endif      
          { {0},                                                                      
            0,//Terminator                                                            
            0,                                                                        
            0,                                                                        
            NIL,                                                                      
            NIL,                                                                      
            0,                                                                        
            0,                                                                        
            0,                                                                        
          },   
};

CODE struct DefineMenu ChineseMenuList[]={

	    {   
	     TV_ICON,                //Display的ICON                         
            0,//Str_Picture,           //顯示字串                    
            NIL,                       //上頁ID        
            NIL,                       //下頁ID                        
            TOPICON_COLOR,             //ICON顯示Flag(ON)                          
            NIL,                       //字串顯示Flag(OFF)                          
            ChinesePicture,                 //目前OSD頁內容(第二層OSD)                         
            OSDMENU,                   //目前OSD型態   
            NO,                                
            VIDEOPICTURE,                                      
            PictureMenu                                        
        },

		{	UTIL_ICON,										
		    0,
			NIL,	NIL,	
			TOPICON_COLOR,
			NIL,
			ChineseUtility,//DMPCUtility,
			OSDMENU,		NO,
			0,
			UtilityMenu//PCUtilityMenu
		},
		
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},

};


CODE struct DefineMenu ChineseMenu[]={
		//{	icon,										desc,
		//	PreFn,	PostFn,	
		//  IconColor,
		//  DescColor,
		// 	*chd,
		//  type,		DispWithCursor		
		//	*typedata
		//},
		{	0,					0,
			NIL,	NIL,	
			ICON_COLOR,
			NIL,
			ChineseMenuList,		OSDMENU,		NO,
			0,
			PCMainMenu
		},
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

CODE struct DefineMenu ChinesePCPicture[]={
		{	{0},								
			Str_Brightness2,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,			NO,
			PANEL_BRIGHTNESS,
			DefaultBar
		},
		
		{	{0},								
			Str_Contrast2,
			NIL,	NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			NUMBER,			NO,
			PANEL_CONTRAST,
			DefaultBar
		},

		{	{0},									
			Str_AutoAdjust2,
			NIL,		NIL,	
			NO_ICON_COLOR,
			DESC_COLOR,
			0,
			ACTION,NO,
			AUTOADJUST
		},
		
             {   {0},                     //ICON位置                  
                 Str_RETURN2,              //顯示"RETRUN"字串           
                 NIL,                     //上頁ID                    
                 NIL,                     //下頁ID                    
                 NO_ICON_COLOR,           //ICON顯示Flag              
                 DESC_COLOR,              //字串顯示Flag              
                 0,                       //目前OSD頁內容(第三層OSD)  
                 ACTION,                  //目前OSD型態    Abel Test             
                 NO,                                                 
                 TOHIGHMENU // EXITMENU , //動作(回到上一頁)                             
             },  

		
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

CODE struct DefineMenu ChinesePCMenuList[]={

		{	{TV_ICON},									
			0,//Str_Picture,
			NIL,	
			NIL,	
			TOPICON_COLOR,
			NIL,
			ChinesePCPicture,
			OSDMENU,		NO,
			0,	
			PictureMenu
		},
			

		{	UTIL_ICON,										
		    0,
			NIL,	NIL,	
			TOPICON_COLOR,
			NIL,
			ChineseUtility,//DMPCUtility,
			OSDMENU,		NO,
			0,
			UtilityMenu//PCUtilityMenu
		},
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};

CODE struct DefineMenu ChinesePCMenu[]={
		//{	icon,										desc,
		//	PreFn,	PostFn,	
		//  IconColor,
		//  DescColor,
		// 	*chd,
		//  type,		DispWithCursor		
		//	*typedata
		//},
		{	0,					0,
			NIL,	NIL,	
			ICON_COLOR,
			NIL,
			ChinesePCMenuList,		OSDMENU,		NO,
			0,
			PCMainMenu
		},
		{	{0},												0,//Terminator
			0,				0,		
			NIL,
			NIL,
			0,
			0,				0,
		},
};
#endif
#endif


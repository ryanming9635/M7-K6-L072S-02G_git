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
/* ??3?hOSD --> DISPLAY -->RS485-->*/ 
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
                                                                     
               {   {0},                     //ICON???m                       
            Str_CAMNumber,             //????"Display"?r??               
            NIL,                     //?W??ID                         
            NIL,                     //?U??ID                         
            NO_ICON_COLOR,           //ICON????Flag                   
            DESC_COLOR,              //?r??????Flag                   
            0,                       //???eOSD?????e(???T?hOSD)
            NUMBER,             //???eOSD???A(?r??)
            NO,                                                 
            //CAMOSDONOFF,             //???@(?^???W?@??)         
            CAMNumberChoice,             //???@(?^???W?@??)     
            NumberOnly,//DefaultBar      //Ryan@979715       
            //ONOFFChoiceString,       //                         
        },                                                            

        {   {0},                     //ICON???m                       
            Str_Pelco,            //????"DISTANCE GAUGE"?r??               
            NIL,                     //?W??ID                         
            NIL,                     //?U??ID                         
            NO_ICON_COLOR,           //ICON????Flag                   
            DESC_COLOR,              //?r??????Flag                   
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,             //???eOSD???A(?r??) 
            NO,                                                 
           // GAUGEChoice,             //???@(?^???W?@??)      
            PelcoChoice,             //???@(?^???W?@??)    
            PDChoiceString,       //                         
        },   

        {   {0},                     //ICON???m                       
            Str_Baud_rate,            //????"DISTANCE GAUGE"?r??               
            NIL,                     //?W??ID                         
            NIL,                     //?U??ID                         
            NO_ICON_COLOR,           //ICON????Flag                   
            DESC_COLOR,              //?r??????Flag                   
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,             //???eOSD???A(?r??) 
            NO,                                                 
           // GAUGEChoice,             //???@(?^???W?@??)      
            Baud_rateChoice,             //???@(?^???W?@??)    
            bpsChoiceString,       //                         
        },  
        
	{	{0},					 //ICON???m 					   
		Str_CameraOSD,			 //????"RETRUN"?r?? 			   
		NIL,					 //?W??ID						   
		NIL,					 //?U??ID						   
		NO_ICON_COLOR,			 //ICON????Flag 				   
		DESC_COLOR, 			 //?r??????Flag 				   
		0,						 //???eOSD?????e(???T?hOSD) 	   
		ACTION, 				 //???eOSD???A	  Abel Test 	   
		NO, 													   
		CameraOSD,				 //???@(?^???W?@??) 			   
	},

      {   {0},                     //ICON???m             
          Str_RETURN,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU//???@(?^???W?@??)     
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
	    {   {0},                     //ICON???m                                          
            Str_Auto_Day_Night,      //????"Auto Day & Night"?r?? 
            NIL,                     //?W??ID                     
            NIL,                     //?U??ID                                                     
            NO_ICON_COLOR,           //ICON????Flag                                                       
            DESC_COLOR,              //?r??????Flag                                                       
            0,                       //???eOSD?????e(???T?hOSD)                                           
            ENUM_STRING,             //???eOSD???A(?r??)
            NO, 
            DayChoice,               //???@(?^???W?@??)
        #ifdef SUPPORT_ML072Q_AUTO_DAY_NIGHT  //Pinchi 20150825 add  //AWT_ML072Q  //Pinchi 20140903 add for AWT ML072Q
			ONOFFChoiceString,       //
		#else
            DayChoiceString,       //
        #endif
        },
	#endif
                                                          
        {   {0},                     //ICON???m                       
            Str_DISPLAY,             //????"Display"?r??               
            NIL,                     //?W??ID                         
            NIL,                     //?U??ID                         
            NO_ICON_COLOR,           //ICON????Flag                   
            DESC_COLOR,              //?r??????Flag                   
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,             //???eOSD???A(?r??)
            NO,                                                 
            CAMOSDONOFF,             //???@(?^???W?@??)         
            ONOFFChoiceString,       //                         
        },

	#ifdef SUPPORT_SDCARD	
	{   {0},                     //ICON???m                       
            Str_DVR_DISPLAY,             //????"Display"?r??               
            NIL,                     //?W??ID                         
            NIL,                     //?U??ID                         
            NO_ICON_COLOR,           //ICON????Flag                   
            DESC_COLOR,              //?r??????Flag                   
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,             //???eOSD???A(?r??)
            NO,                                                 
            DVRDisplay,             //???@(?^???W?@??)         
            ONOFFChoiceString,       //                         
        },   	
	#endif

        {   {0},                     //ICON???m                       
            Str_DISTANCE,            //????"DISTANCE GAUGE"?r??               
            NIL,                     //?W??ID                         
            NIL,                     //?U??ID                         
            NO_ICON_COLOR,           //ICON????Flag                   
            DESC_COLOR,              //?r??????Flag                   
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,             //???eOSD???A(?r??) 
            NO,                                                 
            GAUGEChoice,             //???@(?^???W?@??)         
            ONOFFChoiceString,       //                         
        },

 	#ifdef  AWT_ML072S
	    {   {0},                     //ICON???m                                          
            Str_Auto_Day_Night,      //????"Auto Day & Night"?r?? 
            NIL,                     //?W??ID                     
            NIL,                     //?U??ID                                                     
            NO_ICON_COLOR,           //ICON????Flag                                                       
            DESC_COLOR,              //?r??????Flag                                                       
            0,                       //???eOSD?????e(???T?hOSD)                                           
            ENUM_STRING,             //???eOSD???A(?r??)
            NO, 
            DayChoice,               //???@(?^???W?@??)                         
            #ifdef AWT_ML072S
            ONOFFChoiceString,       //   
		#else
            DayChoiceString,       //   
            #endif
        },                                                                   
	#endif

	#ifdef HTRV
	////_Anderson_20140310_add_xx_B
		{   {0},                     //ICON???m                       
            Str_GAUGE_STEP,            //????"DISTANCE GAUGE"?r??               
            NIL,                     //?W??ID                         
            NIL,                     //?U??ID                         
            NO_ICON_COLOR,           //ICON????Flag                   
            DESC_COLOR,              //?r??????Flag                   
            0,                       //???eOSD?????e(???T?hOSD)
            GRAPH,////ACTION,             //???eOSD???A(?r??) 
            NO,                                                 
            Gauge_VStart,             //???@(?^???W?@??)         
            DefaultBar ,       //                         
        },
	////_Anderson_20140310_Disable_xx_E
	#endif

        {   {0},                     //ICON???m                       
            Str_OSD_LOCK,            //????"OSD LOCK"?r??               
            NIL,                     //?W??ID                         
            NIL,                     //?U??ID                         
            NO_ICON_COLOR,           //ICON????Flag                   
            DESC_COLOR,              //?r??????Flag                   
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,             //???eOSD???A(?r??) 
            NO,                                                 
            OsdLockChoice,             //???@(?^???W?@??)         
            ONOFFChoiceString,       //                         
        },

#ifndef HTRV
	#ifdef AWT_ML072Q
        {	 {0},					  //ICON???m					   
			 Str_PRIORITY,			  //????"PRIORITY"?r??				 
			 NIL,					  //?W??ID						   
			 NIL,					  //?U??ID						   
			 NO_ICON_COLOR, 		  //ICON????Flag				   
			 DESC_COLOR,			  //?r??????Flag				   
			 0, 					  //???eOSD?????e(???T?hOSD)
			 ENUM_STRING,			  //???eOSD???A(?r??) 
			 NO,												 
			 PRIORITYChoice,			  //???@(?^???W?@??)		 
			 ONOFFChoiceString, 	  //						 
	    },    
	#endif

	    //#ifdef Func_ReversMode
		#ifdef HS
		#else
		{  {0},					   //ICON???m						
		   Str_ReversMode,			 //????"OSD LOCK"?r??				
		   NIL,					   //?W??ID 						
		   NIL,					   //?U??ID 						
		   NO_ICON_COLOR,		   //ICON????Flag					
		   DESC_COLOR,			   //?r??????Flag					
		   0,					   //???eOSD?????e(???T?hOSD)
		   ENUM_STRING,			   //???eOSD???A(?r??) 
		   NO,												  
		   ReverseMode,			   //???@(?^???W?@??)		  
		   ReversModeString, 	  //						 
		 },
		#endif
		 //#endif
#endif

	#ifdef SUPPORT_RS485
		{	{0},					 //ICON???m 					   
		    Str_RS485,			 //????"RETRUN"?r?? 			   
   		    NIL,					  //?W??ID				 
   		    NIL,					  //?U??ID				 
   		    NO_ICON_COLOR,		  //ICON????Flag		 
   		    DESC_COLOR,			  //?r??????Flag		 
   		    RS485SELECT,		   //???eOSD?????e(???T?hOSD)	  
   		    OSDMENU,//CHOICEMENU, 			//???eOSD???A				   
   		    NO,											 
   		    0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
   		   RS485SelectMenu 	   //???@Flag				   
		},
	#endif
			
		{	{0},                     //ICON???m                     
            Str_RETURN,              //????"RETRUN"?r??             
            NIL,                     //?W??ID                       
            NIL,                     //?U??ID                       
            NO_ICON_COLOR,           //ICON????Flag                 
            DESC_COLOR,              //?r??????Flag                 
            0,                       //???eOSD?????e(???T?hOSD)     
            ACTION,                  //???eOSD???A(?]?w???@)     
            NO,                                                     
            TOHIGHMENU               //???@(?^???W?@??)             
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
/* ??3?hOSD ---> EXIT --->FWUpdate						*/ 
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
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR, 			 //?r??????Flag 				   
			0,						 //???eOSD?????e(???T?hOSD) 	   
			ACTION, 				 //???eOSD???A	  Abel Test 	   
			NO, 													   
			TOHIGHMENU , 	 //???@(?^???W?@??) 	  

    	},     
 	
        {   {0},                 //ICON???m     
       		Str_YES,
   		    NIL,					   //?W??ID 						 
   		    NIL,					   //?U??ID 						 
   		    NO_ICON_COLOR,		   //ICON????Flag					 
   		    DESC_COLOR,			   //?r??????Flag					 
   		    0,					   //???eOSD?????e(???T?hOSD)		 
   		    ACTION,				   //???eOSD???A	Abel Test		 
   		    NO,														 
   		    FirmwareUpdate,	   //???@(?^???W?@??)		                        
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
/* ??4?hOSD --> EXIT -->FORMAT SD CARD-->Change Password*/ 
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
 	
        {   {0},                 //ICON???m                                      
            Str_SecondNumber,            //????"CAMA"?r??                               
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
		
		{	{0},					 //ICON???m 					   
			Str_ChangePassword,			 //????"RETRUN"?r?? 			   
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR, 			 //?r??????Flag 				   
			0,						 //???eOSD?????e(???T?hOSD) 	   
			ACTION, 				 //???eOSD???A	  Abel Test 	   
			NO, 													   
			ChangePassword ,				 //???@(?^???W?@??) 			   
		},


      {   {0},                     //ICON???m             
          Str_RETURN,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU//???@(?^???W?@??)     
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
/* ??3?hOSD ---> EXIT --->FORMAT SD CARD						*/ 
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
 	
        {   {0},                 //ICON???m                                      
            Str_SecondNumber,            //????"CAMA"?r??                               
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

		{	{0},					 //ICON???m 					   
			Str_FormatSD,			 //????"RETRUN"?r?? 			   
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR, 			 //?r??????Flag 				   
			0,						 //???eOSD?????e(???T?hOSD) 	   
			ACTION, 				 //???eOSD???A	  Abel Test 	   
			NO, 													   
			FormatSD ,				 //???@(?^???W?@??) 			   
		},
		
		{	{0},					 //ICON???m 					   
			Str_ChangePassword,			 //????"RETRUN"?r?? 			   
   		    NIL,					  //?W??ID				 
   		    NIL,					  //?U??ID				 
   		    NO_ICON_COLOR,		  //ICON????Flag		 
   		    DESC_COLOR,			  //?r??????Flag		 
   		    ChangePasswordSELECT,		   //???eOSD?????e(???T?hOSD)	  
   		    OSDMENU,//CHOICEMENU, 			//???eOSD???A				   
   		    NO,											 
   		    0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
   		    ChangePasswordSelectMenu 	   //???@Flag				   
		},

		

      {   {0},                     //ICON???m             
          Str_RETURN,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU//???@(?^???W?@??)     
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
/*         ???T?hOSD ---> SDCARD --->DATE TIME	                   */ 
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
       	



      {   {0},                     //ICON???m             
          Str_RETURNAPPLY,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          DATETIMEApply				//???@(?^???W?@??)     
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
/* ???|?hOSD ---> SDCARD --->DATE TIME--->DaylightSaving--->TimeBegines*/ 
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
 	
        {   {0},                 //ICON???m                                      
           Str_Week,            //????"CAMA"?r??                               
           NIL,                 //?W??ID                                        
           NIL,                 //?U??ID                                        
           NO_ICON_COLOR,       //ICON????Flag                                  
           DESC_COLOR,          //?r??????Flag                                  
           0,
           ENUM_STRING,         //???eOSD???A    Abel Test 
           NO,                                             
           StandardTimeBeginesWeek,           //???@(?^???W?@??)         
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



      {   {0},                     //ICON???m             
          Str_RETURNAPPLY,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          DATETIMEApply               //???@(?^???W?@??)     
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
/* ???|?hOSD ---> SDCARD --->DATE TIME--->DaylightSaving--->TimeBegines*/ 
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
 	
       {   {0},                 //ICON???m                                      
          Str_Week,            //????"CAMA"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          TimeBeginesWeek,           //???@(?^???W?@??)         
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



      {   {0},                     //ICON???m             
          Str_RETURNAPPLY,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          DATETIMEApply               //???@(?^???W?@??)     
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
/* ???T?hOSD ---> SDCARD --->DATE TIME--->DaylightSaving*/ 
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
      {   {0},                 //ICON???m                                      
          Str_DaylightSaving,            //????"CAMA"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          DaylightSaving,           //???@(?^???W?@??)         
          DaylightSavingChoiceString    //                         
      },                                                                     
    #if 0
	  {   {0},					  //ICON???m			 
		  Str_TimeBegines,			  //????"MIRRO"?r?? 			
		  NIL,					  //?W??ID				 
		  NIL,					  //?U??ID				 
		  NO_ICON_COLOR,		  //ICON????Flag		 
		  DESC_COLOR,			  //?r??????Flag		 
		  TimeBeginesSELECT, 		   //???eOSD?????e(???T?hOSD)	  
		  OSDMENU,//CHOICEMENU, 			//???eOSD???A				   
		  NO,											 
		  0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
		  TimeBeginesSelectMenu		   //???@Flag			  
	  }, 

 	  {   {0},					  //ICON???m			 
		  Str_Standard,			  //????"MIRRO"?r?? 			
		  NIL,					  //?W??ID				 
		  NIL,					  //?U??ID				 
		  NO_ICON_COLOR,		  //ICON????Flag		 
		  DESC_COLOR,			  //?r??????Flag		 
		  StandardTimeBeginesSELECT, 		   //???eOSD?????e(???T?hOSD)	  
		  OSDMENU,//CHOICEMENU, 			//???eOSD???A				   
		  NO,											 
		  0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
		  StandardTimeBeginesSelectMenu		   //???@Flag			  
	  },       	
  #endif
			

      {   {0},                     //ICON???m             
          Str_RETURNAPPLY,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          DATETIMEApply               //???@(?^???W?@??)     
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
     
      {   {0},                     //ICON???m             
          Str_YES,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,
          RESET_VIDEOVALUE,                                             
          //YESNOChoiceString               //???@(?^???W?@??)     
      },                                                  

	  
 

 {   {0},                     //ICON???m             
          Str_NO,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU               //???@(?^???W?@??)     
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
     
      {   {0},                     //ICON???m             
          Str_YES,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,
          RESET_MonitorVALUE,                                             
          //YESNOChoiceString               //???@(?^???W?@??)     
      },                                                  

	  
 

 {   {0},                     //ICON???m             
          Str_NO,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU               //???@(?^???W?@??)     
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
     
      {   {0},                     //ICON???m             
          Str_YES,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,
          RESET_DVRVALUE,                                             
          //YESNOChoiceString               //???@(?^???W?@??)     
      },                                                  

	  
 

 {   {0},                     //ICON???m             
          Str_NO,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU               //???@(?^???W?@??)     
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
	  
{   {0},                     //ICON???m                        
              Str_MonitorRECALL,              //????"RETRUN"?r??                
              NIL,                     //?W??ID                          
              NIL,                     //?U??ID                          
              NO_ICON_COLOR,           //ICON????Flag                    
              DESC_COLOR,              //?r??????Flag                    
              DMMonitorRecallSELECT,                       //???eOSD?????e(???T?hOSD)        
              OSDMENU,             //???eOSD???A(?r??) 
              NO,                                                 
              0,
              InputSelectMenu,       //                        
          },                                     

{   {0},                     //ICON???m                        
              Str_DVRRECALL,              //????"RETRUN"?r??                
              NIL,                     //?W??ID                          
              NIL,                     //?U??ID                          
              NO_ICON_COLOR,           //ICON????Flag                    
              DESC_COLOR,              //?r??????Flag                    
              DMDVRRecallSELECT,                       //???eOSD?????e(???T?hOSD)        
              OSDMENU,             //???eOSD???A(?r??) 
              NO,                                                 
              0,
              InputSelectMenu,       //                        
          },     
          
        {   
            {0},                     //ICON???m                     
            Str_RETURN,              //????"RETRUN"?r??             
            NIL,                     //?W??ID                       
            NIL,                     //?U??ID                       
            NO_ICON_COLOR,           //ICON????Flag                 
            DESC_COLOR,              //?r??????Flag                 
            0,                       //???eOSD?????e(???T?hOSD)     
            ACTION,                  //???eOSD???A(?]?w???@)     
            NO,                                                     
            TOHIGHMENU               //???@(?^???W?@??)             
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


		{	{0},					 //ICON???m 					   
			Str_WIFI_IP,				//????"RETRUN"?r??				  
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			VER_COLOR,				//?r??????Flag					  
			0,						 //???eOSD?????e(???T?hOSD) 	   
			TEXT_STR,				   //???eOSD???A	Abel Test		 
			NO, 													   
			TOHIGHMENU ,				 //???@(?^???W?@??) 			   
		},	

		{	{0},					 //ICON???m 					   
			NO,				//????"RETRUN"?r??				  
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR,				//?r??????Flag					  
			0,						 //???eOSD?????e(???T?hOSD) 	   
			INFORMATION,			
			NO,	  				 //???eOSD???A	Abel Test		 
			WIFIIPNumber, 													   
			DefaultBar ,			 //???@(?^???W?@??) 			   
		},	
		
		{	{0},					 //ICON???m 					   
			Str_WIFI_MAC,				//????"RETRUN"?r??				  
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			VER_COLOR,				//?r??????Flag					  
			0,						 //???eOSD?????e(???T?hOSD) 	   
			TEXT_STR,				   //???eOSD???A	Abel Test		 
			NO, 													   
			TOHIGHMENU ,				 //???@(?^???W?@??) 			   
		},	

		{	{0},					 //ICON???m 					   
			NO,				//????"RETRUN"?r??				  
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			VER_COLOR,				//?r??????Flag					  
			0,						 //???eOSD?????e(???T?hOSD) 	   
			INFORMATION,				   //???eOSD???A	Abel Test		 
			NO, 													   
			WIFIMACNumber ,				 //???@(?^???W?@??) 
			DefaultBar ,
		},	
		
		{	{0},					 //ICON???m 					   
			Str_GETWAY,				//????"RETRUN"?r??				  
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			VER_COLOR,				//?r??????Flag					  
			0,						 //???eOSD?????e(???T?hOSD) 	   
			TEXT_STR,				   //???eOSD???A	Abel Test		 
			NO, 													   
			TOHIGHMENU ,				 //???@(?^???W?@??) 			   
		},	

		{	{0},					 //ICON???m 					   
			NO,				//????"RETRUN"?r??				  
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			VER_COLOR,				//?r??????Flag					  
			0,						 //???eOSD?????e(???T?hOSD) 	   
			INFORMATION,				   //???eOSD???A	Abel Test		 
			NO, 													   
			GETWAYNumber,				 //???@(?^???W?@??) 
			DefaultBar ,
		},	
		
	       {   
	        	{0},                     //ICON???m                     
	        	Str_RETURN,              //????"RETRUN"?r??             
	        	NIL,                     //?W??ID                       
	        	NIL,                     //?U??ID                       
	       	 NO_ICON_COLOR,           //ICON????Flag                 
	        	DESC_COLOR,              //?r??????Flag                 
	        	0,                       //???eOSD?????e(???T?hOSD)     
	        	ACTION,                  //???eOSD???A(?]?w???@)     
	        	NO,                                                     
	        	TOHIGHMENU               //???@(?^???W?@??)             
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
      	{	 {0},					  //ICON???m					   
			 Str_SDCARDCOVERDET,			  //????"PRIORITY"?r??				 
			 NIL,					  //?W??ID						   
			 NIL,					  //?U??ID						   
			 NO_ICON_COLOR, 		  //ICON????Flag				   
			 DESC_COLOR,			  //?r??????Flag				   
			 0, 					  //???eOSD?????e(???T?hOSD)
			 ENUM_STRING,			  //???eOSD???A(?r??) 
			 NO,												 
			 SDCardDetect,			  //???@(?^???W?@??)		 
			 ONOFFChoiceString, 	  //						 
		 },    

        {   {0},                    //ICON???m             
           	Str_DateTime,             //????"MIRRO"?r??             
            	NIL,                    //?W??ID               
            	NIL,                    //?U??ID               
            	NO_ICON_COLOR,          //ICON????Flag         
            	DESC_COLOR,             //?r??????Flag         
            	DateTimeSELECT,            //???eOSD?????e(???T?hOSD)     
            	OSDMENU,//CHOICEMENU,             //???eOSD???A                  
            	NO,                                            
            	0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            	DateTimeSelectMenu         //???@Flag             
        },

 		#ifdef AWT_ML073G
	 	{   {0},                    //ICON???m             
            	Str_DaylightSaving,             //????"MIRRO"?r??             
            	NIL,                    //?W??ID               
            	NIL,                    //?U??ID               
            	NO_ICON_COLOR,          //ICON????Flag         
            	DESC_COLOR,             //?r??????Flag         
            	DaylightSavingSELECT,            //???eOSD?????e(???T?hOSD)     
            	OSDMENU,//CHOICEMENU,             //???eOSD???A                  
            	NO,                                            
            	0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            	DaylightSavingSelectMenu         //???@Flag             
        }, 

	 	{   {0},                     //ICON???m                        
            Str_Informmation,              //????"RETRUN"?r??                
          	NIL,                     //?W??ID                          
          	NIL,                     //?U??ID                          
          	NO_ICON_COLOR,           //ICON????Flag                    
          	DESC_COLOR,              //?r??????Flag                    
          	DMINFORMATION,                       //???eOSD?????e(???T?hOSD)        
          	OSDMENU,             //???eOSD???A(?r??) 
          	NO,                                                 
          	0,
          	InformationMenu,       //                        
        },

     	{   {0},					   //ICON???m						 
      		Str_UpdateConfig,		   //????"RETRUN"?r??				 
      		NIL,					   //?W??ID 						 
      		NIL,					   //?U??ID 						 
      		NO_ICON_COLOR,		   //ICON????Flag					 
      		DESC_COLOR,			   //?r??????Flag					 
      		0,					   //???eOSD?????e(???T?hOSD)		 
      		ACTION,				   //???eOSD???A	Abel Test		 
      		NO,														 
      		UpdateConfig ,	   //???@(?^???W?@??)				 
   	    },
		#endif
	#endif		

	#ifdef QUAD  //Pinchi 20150901 change to QUAD condition
     	#ifdef SUPPORT_SDCARD 
     	{   {0},                     //ICON???m                        
     		Str_RECALL,              //????"RETRUN"?r??                
     		NIL,                     //?W??ID                          
     		NIL,                     //?U??ID                          
     		NO_ICON_COLOR,           //ICON????Flag                    
     		DESC_COLOR,              //?r??????Flag                    
     		RecallMenu,              //???eOSD?????e(???T?hOSD)        
     		OSDMENU,                 //???eOSD???A(?r??) 
     		NO,                                                 
     		0,
     		InputSelectMenu,
     	},     		     
		#else
     	{   {0},					 //ICON???m
     		Str_RECALL,			     //????"RETRUN"?r??
     		NIL,					 //?W??ID
     		NIL,					 //?U??ID
     		NO_ICON_COLOR,		     //ICON????Flag
     		DESC_COLOR,			     //?r??????Flag
     		0,					     //???eOSD?????e(???T?hOSD)
     		ACTION,				     //???eOSD???A	Abel Test
     		NO,
     		RESET_VIDEOVALUE ,	   //???@(?^???W?@??)
     	},
		#endif

		#ifdef HTRV  //Pinchi 20140902 add for AWT ML072Q
		////_Anderson_20140310_add_xx_B
		{   {0},                     //ICON???m                        
			Str_GAUGE_RECALL,              //????"RETRUN"?r??                
			NIL,                     //?W??ID                          
			NIL,                     //?U??ID                          
			NO_ICON_COLOR,           //ICON????Flag                    
			DESC_COLOR,              //?r??????Flag                    
			0,                       //???eOSD?????e(???T?hOSD)        
			ACTION,                  //???eOSD???A    Abel Test        
			NO,                                                        
			RESET_GAUGESETUP,       //???@(?^???W?@??)                
		},
		#endif

     	{   {0},                     //ICON???m
     		Str_EXIT,                //????"RETRUN"?r??
     		NIL,                     //?W??ID
     		NIL,                     //?U??ID
     		NO_ICON_COLOR,           //ICON????Flag
     		DESC_COLOR,              //?r??????Flag
     		0,                       //???eOSD?????e(???T?hOSD)
     		ACTION,                  //???eOSD???A    Abel Test
     		NO,
     		EXITMENU ,               //???@(?^???W?@??)
     	},
	#endif
#ifndef AWT_ML072S
		{	{0},					 //ICON???m
			Str_SPACE,				 //????"RETRUN"?r??
			NIL,					 //?W??ID
			NIL,					 //?U??ID
			NO_ICON_COLOR,			 //ICON????Flag
			DESC_COLOR, 			 //?r??????Flag
			0,						 //???eOSD?????e(???T?hOSD)
			TEXT_STR,				   //???eOSD???A	Abel Test
			NO,
			EXITMENU ,				 //???@(?^???W?@??)
		},

		{	{0},					 //ICON???m
			Str_SPACE,				  //????"RETRUN"?r??
			NIL,					 //?W??ID
			NIL,					 //?U??ID
			NO_ICON_COLOR,			 //ICON????Flag
			DESC_COLOR, 			 //?r??????Flag
			0,						 //???eOSD?????e(???T?hOSD)
			TEXT_STR,				   //???eOSD???A	Abel Test
			NO,
			EXITMENU ,				 //???@(?^???W?@??)
		},	 

		{	{0},					 //ICON???m
			Str_SPACE,				 //????"RETRUN"?r??
			NIL,					 //?W??ID
			NIL,					 //?U??ID
			NO_ICON_COLOR,			 //ICON????Flag
			DESC_COLOR, 			 //?r??????Flag
			0,						 //???eOSD?????e(???T?hOSD)
			TEXT_STR,				 //???eOSD???A	Abel Test
			NO,
			EXITMENU ,				 //???@(?^???W?@??)
		},
	#endif
	#ifdef TW8816
							#ifdef AWT_ML072S
						{	{0},					 //ICON???m
							Str_SPACE,				 //????"RETRUN"?r??
							NIL,					 //?W??ID
							NIL,					 //?U??ID
							NO_ICON_COLOR,			 //ICON????Flag
							DESC_COLOR, 			 //?r??????Flag
							0,						 //???eOSD?????e(???T?hOSD)
							TEXT_STR,				   //???eOSD???A	Abel Test
							NO,
							EXITMENU ,				 //???@(?^???W?@??)
						},

						{	{0},					 //ICON???m
							Str_SPACE,				  //????"RETRUN"?r??
							NIL,					 //?W??ID
							NIL,					 //?U??ID
							NO_ICON_COLOR,			 //ICON????Flag
							DESC_COLOR, 			 //?r??????Flag
							0,						 //???eOSD?????e(???T?hOSD)
							TEXT_STR,				   //???eOSD???A	Abel Test
							NO,
							EXITMENU ,				 //???@(?^???W?@??)
						},	 
							#endif
	{	{0},					 //ICON???m
			Str_VER,				 //????"RETRUN"?r??
			NIL,					 //?W??ID
			NIL,					 //?U??ID
			NO_ICON_COLOR,			 //ICON????Flag
			VER_COLOR,				 //?r??????Flag
			0,						 //???eOSD?????e(???T?hOSD)
			TEXT_STR,				 //???eOSD???A	Abel Test
			NO,
			EXITMENU ,				 //???@(?^???W?@??)
		},

		#endif


	{	{0},					 //ICON???m
			Str_SPACE,				 //????"RETRUN"?r??
			NIL,					 //?W??ID
			NIL,					 //?U??ID
			NO_ICON_COLOR,			 //ICON????Flag
			DESC_COLOR, 			 //?r??????Flag
			0,						 //???eOSD?????e(???T?hOSD)
			TEXT_STR,				 //???eOSD???A	Abel Test
			NO,
			EXITMENU ,				 //???@(?^???W?@??)
		},		

	#ifdef AWT_ML072S
		{	{0},					 //ICON???m 					   
			Str_SPACE,				  //????"RETRUN"?r??				
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR, 			 //?r??????Flag 				   
			0,						 //???eOSD?????e(???T?hOSD) 	   
			TEXT_STR,				   //???eOSD???A	Abel Test		 
			NO, 													   
			EXITMENU ,				 //???@(?^???W?@??) 			   
		},	
		
		{	{0},					 //ICON???m 					   
			Str_SPACE,				  //????"RETRUN"?r??				
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR, 			 //?r??????Flag 				   
			0,						 //???eOSD?????e(???T?hOSD) 	   
			TEXT_STR,				   //???eOSD???A	Abel Test		 
			NO, 													   
			EXITMENU ,				 //???@(?^???W?@??) 			   
		},	

           {   {0},                     //ICON???m                        
              Str_EXIT,                //????"RETRUN"?r??                
              NIL,                     //?W??ID                          
              NIL,                     //?U??ID                          
              NO_ICON_COLOR,           //ICON????Flag                    
              DESC_COLOR,              //?r??????Flag                    
              0,                       //???eOSD?????e(???T?hOSD)        
              TEXT_STR,                  //???eOSD???A    Abel Test        
              NO,                                                        
              EXITMENU ,               //???@(?^???W?@??)                
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
/*         ???T?hOSD ---> SDCARD --->RECORDMODE               */ 
/*-----------------------------------------------------*/ 
#define RecordSELECT_H  5                                  
CODE BYTE RecordSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    RecordSELECT_H,          //???T?hOSD ---> UTILITY --->Input   
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     CAMSELECT OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu RECORDSELECT[]={     
	#if 0
      {   {0},                 //ICON???m                                      
          Str_RecordMode,            //????"CAMA"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          RecordMode,           //???@(?^???W?@??)         
          RecordModeChoiceString    //                         
      },                                                                       
     #endif                                                                          
      {   {0},                 //ICON???m                                      
          Str_RecordLength,            //????"CAMB"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          RecordLength,         //???@(?^???W?@??)         
          RecordLengthChoiceString    //                         
      },              

     {  {0},                 //ICON???m                                       
          Str_PostAlarmLength,            //????"CAMR"?r??                                
          NIL,                 //?W??ID                                         
          NIL,                 //?U??ID                                         
          NO_ICON_COLOR,       //ICON????Flag                                   
          DESC_COLOR,          //?r??????Flag                                   
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                                 
          PostAlarmLength,         //???@(?^???W?@??)         
          PostAlarmLengthChoiceString    //                         
      },        
#if 0                                                                               
      {   {0},                 //ICON???m                                      
          Str_PreAlarmLength,            //????"CAMC"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          PreAlarmLength,         //???@(?^???W?@??)         
          PreAlarmLengthChoiceString    //                         
      },                                                                       
                                                                               
                                                               
                 
	    {   {0},                     //ICON???m                                          
            Str_Str_OverWrite,      //????"Auto Day & Night"?r?? 
            NIL,                     //?W??ID                     
            NIL,                     //?U??ID                                                     
            NO_ICON_COLOR,           //ICON????Flag                                                       
            DESC_COLOR,              //?r??????Flag                                                       
            0,                       //???eOSD?????e(???T?hOSD)                                           
            ENUM_STRING,             //???eOSD???A(?r??)
            NO, 
            OverWrite,               //???@(?^???W?@??)                         
            ONOFFChoiceString1,       //                                              
        },     
#endif   
      {  {0},                 //ICON???m                                       
          Str_AudioRecord,            //????"CAMR"?r??                                
          NIL,                 //?W??ID                                         
          NIL,                 //?U??ID                                         
          NO_ICON_COLOR,       //ICON????Flag                                   
          DESC_COLOR,          //?r??????Flag                                   
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                                 
          AudioRecord,         //???@(?^???W?@??)         
          AudioRecordChoiceString    //                         
      }, 


      {   {0},                     //ICON???m             
          Str_RETURNAPPLY,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          DVRParamApply               //???@(?^???W?@??)     
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

	    	{   {0},                    //ICON???m             
            		Str_RecordMode,             //????"MIRRO"?r??             
            		NIL,                    //?W??ID               
            		NIL,                    //?U??ID               
            		NO_ICON_COLOR,          //ICON????Flag         
            		DESC_COLOR,             //?r??????Flag         
            		RECORDSELECT,            //???eOSD?????e(???T?hOSD)     
            		OSDMENU,//CHOICEMENU,             //???eOSD???A                  
            		NO,                                            
            		0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            		RecordSelectMenu         //???@Flag             
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
		
	      {     	{0},					   //ICON???m						 
		      	Str_FormatSD, 		   //????"RETRUN"?r??				 
		  	NIL,					  //?W??ID				 
		  	NIL,					  //?U??ID				 
		  	NO_ICON_COLOR,		  //ICON????Flag		 
		  	DESC_COLOR,			  //?r??????Flag		 
		  	FORMATSDSELECT,		   //???eOSD?????e(???T?hOSD)	  
		  	OSDMENU,//CHOICEMENU, 			//???eOSD???A				   
		  	NO,											 
		  	0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
		  	FORMATSDSelectMenu 	   //???@Flag				 
	  	},
	 
	  	{   {0},					   //ICON???m						 
		  	Str_FirmwareUpdate, 		   //????"RETRUN"?r??				 
		  	NIL,					  //?W??ID				 
		  	NIL,					  //?U??ID				 
		  	NO_ICON_COLOR,		  //ICON????Flag		 
		  	DESC_COLOR,			  //?r??????Flag		 
		  	FWUpdateSELECT,		   //???eOSD?????e(???T?hOSD)	  
		  	OSDMENU,//CHOICEMENU, 			//???eOSD???A				   
		  	NO,											 
		  	0,//INPUTSELECTION,			   //<william-961004-ver1.41>				   
		  	FWUpdateSelectMenu 	   //???@Flag		  
	  	},

		{   {0},                     //ICON???m                     
            		Str_RETURNAPPLY,              //????"RETRUN"?r??             
            		NIL,                     //?W??ID                       
            		NIL,                     //?U??ID                       
            		NO_ICON_COLOR,           //ICON????Flag                 
            		DESC_COLOR,              //?r??????Flag                 
            		0,                       //???eOSD?????e(???T?hOSD)     
            		ACTION,                  //???eOSD???A    Abel Test     
            		NO,                                                     
            		DVRParamApply // EXITMENU , //???@(?^???W?@??)             
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
/*             ???G?hOSD ---> AUDIO                    */ 
/*-----------------------------------------------------*/ 
#define     SOUND_H        2                                                        
CODE BYTE SoundMenu[]={//3,                                                          
    MENU_WIDTH,                                                                      
    SOUND_H,                                                                         
    TITLE_COLOR,                                                                     
    CURSOR_COLOR,};                                                                  
                                                                                     
CODE struct DefineMenu DMSound[]={                                                   
        {   {0},                     //ICON???m                                      
            Str_Volume,              //?????r??                                      
            NIL,                     //?W??ID                                        
            NIL,                     //?U??ID                                        
            NO_ICON_COLOR,           //ICON????Flag                                  
            DESC_COLOR,              //?r??????Flag                                  
            0,                                                                       
            BAR,                                                                     
            NO,                                                                      
            AUDIO_VOLUME,            //                                              
            DefaultBar                                                               
        },                                                                           
                                                                                     
        {   {0},                     //ICON???m                     
            Str_RETURN,              //????"RETRUN"?r??             
            NIL,                     //?W??ID                       
            NIL,                     //?U??ID                       
            NO_ICON_COLOR,           //ICON????Flag                 
            DESC_COLOR,              //?r??????Flag                 
            0,                       //???eOSD?????e(???T?hOSD)     
            ACTION,                  //???eOSD???A    Abel Test     
            NO,                                                     
            TOHIGHMENU // EXITMENU , //???@(?^???W?@??)             
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
            {0},                     //ICON???m                     
            Str_RETURN,              //????"RETRUN"?r??             
            NIL,                     //?W??ID                       
            NIL,                     //?U??ID                       
            NO_ICON_COLOR,           //ICON????Flag                 
            DESC_COLOR,              //?r??????Flag                 
            0,                       //???eOSD?????e(???T?hOSD)     
            ACTION,                  //???eOSD???A(?]?w???@)     
            NO,                                                     
            TOHIGHMENU               //???@(?^???W?@??)             
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
/*         ???T?hOSD ---> CAMERA --->MIRROR            */ 
/*-----------------------------------------------------*/ 
#define CAMSELECT_H  5                                  
CODE BYTE CAMSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    CAMSELECT_H,          //???T?hOSD ---> UTILITY --->Input   
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     CAMSELECT OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu DMCAMSELECT[]={                                       
      {   {0},                 //ICON???m                                      
          Str_CAMA,            //????"CAMA"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          CAMAONOFF,           //???@(?^???W?@??)         
          ONOFFChoiceString    //                         
      },                                                                       
#ifndef AWT_ML072S  
      {   {0},                 //ICON???m                                      
          Str_CAMB,            //????"CAMB"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          CAMBONOFF,         //???@(?^???W?@??)         
          ONOFFChoiceString    //                         
      }, 
 #endif     
#ifdef QUAD                                                                               
      {   {0},                 //ICON???m                                      
          Str_CAMC,            //????"CAMC"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          CAMCONOFF,         //???@(?^???W?@??)         
          ONOFFChoiceString    //                         
      },                                                                       
#endif                                                                               
       {  {0},                 //ICON???m                                       
          Str_CAMR,            //????"CAMR"?r??                                
          NIL,                 //?W??ID                                         
          NIL,                 //?U??ID                                         
          NO_ICON_COLOR,       //ICON????Flag                                   
          DESC_COLOR,          //?r??????Flag                                   
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                                 
          CAMRONOFF,         //???@(?^???W?@??)         
          ONOFFChoiceString    //                         
      },                                                                       
                    

      {   {0},                     //ICON???m             
          Str_RETURN,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU               //???@(?^???W?@??)     
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
/* ???|?hOSD ---> CAMERA --->TRIGGER SET-->trigger delay  */ 
/*-----------------------------------------------------*/ 
#define 	TRIGGERDELAYSELECT_H  5                                  
CODE BYTE TRIGGERDELAYMenu[]={                                    
    MENU_WIDTH,                                                  
    TRIGGERDELAYSELECT_H,          //???T?hOSD ---> UTILITY --->Input   
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     CAMSELECT OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu TRIGGERDELAYSELECT[]={      

      {   {0},                 //ICON???m                                      
          Str_CAMA,            //????"CAMA"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          NUMBER,         //???eOSD???A    Abel Test 
          NO,                                             
          DELAYCAMA,           //???@(?^???W?@??)         
          DefaultBar    //                         
      },                                                                       
                                                                               
      {   {0},                 //ICON???m                                      
          Str_CAMB,            //????"CAMB"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          NUMBER,         //???eOSD???A    Abel Test 
          NO,                                             
          DELAYCAMB,         //???@(?^???W?@??)         
          DefaultBar    //                         
      },                                                                       
                                                                               
      {   {0},                 //ICON???m                                      
          Str_CAMC,            //????"CAMC"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          NUMBER,         //???eOSD???A    Abel Test 
          NO,                                             
          DELAYCAMC,         //???@(?^???W?@??)         
          DefaultBar    //                         
      }, 
  #ifdef USE_CAMD    
             {  {0},                 //ICON???m                                       
          Str_CAMD,            //????"CAMR"?r??                                
          NIL,                 //?W??ID                                         
          NIL,                 //?U??ID                                         
          NO_ICON_COLOR,       //ICON????Flag                                   
          DESC_COLOR,          //?r??????Flag                                   
          0,
          NUMBER,         //???eOSD???A    Abel Test 
          NO,                                                 
          DELAYCAMD,         //???@(?^???W?@??)         
          DefaultBar    //                         
      },     
#endif                                                                               
       {  {0},                 //ICON???m                                       
          Str_CAMR,            //????"CAMR"?r??                                
          NIL,                 //?W??ID                                         
          NIL,                 //?U??ID                                         
          NO_ICON_COLOR,       //ICON????Flag                                   
          DESC_COLOR,          //?r??????Flag                                   
          0,
          NUMBER,         //???eOSD???A    Abel Test 
          NO,                                                 
          DELAYCAMR,         //???@(?^???W?@??)         
          DefaultBar    //                         
      },                                                                       
                    

      {   {0},                     //ICON???m             
          Str_RETURN,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU               //???@(?^???W?@??)     
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
      {   {0},                     //ICON???m
          Str_CamADelay,           //????"CAM A"?r??
          NIL,                     //?W??ID
          NIL,                     //?U??ID
          NO_ICON_COLOR,           //ICON????Flag
          DESC_COLOR,              //?r??????Flag
          0,
          #ifdef AWT_ML072S
          NUMBER,                     //???eOSD???A  
	   #else
          BAR,                     //???eOSD???A
          #endif
          NO,
          TRIGGER_CamADelay,      //???@(?^???W?@??)
          DefaultBar
      },
#ifndef AWT_ML072S
      {   {0},                     //ICON???m
          Str_CamBDelay,           //????"CAM B"?r??
          NIL,                     //?W??ID
          NIL,                     //?U??ID
          NO_ICON_COLOR,           //ICON????Flag
          DESC_COLOR,              //?r??????Flag
          0,
          BAR,                     //???eOSD???A
          NO,
          TRIGGER_CamBDelay,      //???@(?^???W?@??)
          DefaultBar
      },

      {   {0},                     //ICON???m
          Str_CamCDelay,           //????"CAM C"?r??
          NIL,                     //?W??ID
          NIL,                     //?U??ID
          NO_ICON_COLOR,           //ICON????Flag
          DESC_COLOR,              //?r??????Flag
          0,
          BAR,                     //???eOSD???A
          NO,
          TRIGGER_CamCDelay,      //???@(?^???W?@??)
          DefaultBar
      },
#endif
      {   {0},                     //ICON???m
          Str_CamRDelay,           //????"CAM R"?r??
          NIL,                     //?W??ID
          NIL,                     //?U??ID
          NO_ICON_COLOR,           //ICON????Flag
          DESC_COLOR,              //?r??????Flag
          0,
          #ifdef AWT_ML072S
          NUMBER,                     //???eOSD???A  
	   #else
          BAR,                     //???eOSD???A
          #endif
          NO,
          TRIGGER_CamRDelay,      //???@(?^???W?@??)
          DefaultBar
      },
      
#ifdef AWT_ML072S
      {   {0},                     //ICON???m
          Str_CamCDelay,           //????"CAM C"?r??
          NIL,                     //?W??ID
          NIL,                     //?U??ID
          NO_ICON_COLOR,           //ICON????Flag
          DESC_COLOR,              //?r??????Flag
          0,
          #ifdef AWT_ML072S
          NUMBER,                     //???eOSD???A  
	   #else
          BAR,                     //???eOSD???A
          #endif
          NO,
          TRIGGER_CamCDelay,      //???@(?^???W?@??)
          DefaultBar
      },
#endif

      {   {0},                     //ICON???m
          Str_RETURN,              //????"RETRUN"?r??
          NIL,                     //?W??ID
          NIL,                     //?U??ID
          NO_ICON_COLOR,           //ICON????Flag
          DESC_COLOR,              //?r??????Flag
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A
          NO,
          TOHIGHMENU               //???@(?^???W?@??)
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
/*         ???T?hOSD ---> CAMERA --->TRIGGER            */ 
/*-----------------------------------------------------*/ 
#define TRIGGERSELECT_H  5                                  
CODE BYTE TRIGGERSelectMenu[]={                                    
    MENU_WIDTH,                                                  
    TRIGGERSELECT_H,          //???T?hOSD ---> UTILITY --->Input   
    TITLE_COLOR,                                                 
    CURSOR_COLOR,};                                              
/*------------------------------*/                                             
/*     TRIGGERSELECT OSD Menu       */                                             
/*------------------------------*/                                             
CODE struct DefineMenu DMTRIGGERSELECT[]={  

      {   {0},                 //ICON???m                                      
          Str_DIR_IMAGE_CAMA,            //????"CAMA"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          IMAGE_A_Choice,           //???@(?^???W?@??)         
          IMAGE_A_String//                         
      },                                                                       
                                                                               
      {   {0},                 //ICON???m                                      
          Str_DIR_IMAGE_CAMB,            //????"CAMB"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          IMAGE_B_Choice,         //???@(?^???W?@??)         
          IMAGE_B_String//                         
      },                                                                       
                                                                               
      {   {0},                 //ICON???m                                      
          Str_DIR_IMAGE_CAMC,            //????"CAMC"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          IMAGE_C_Choice,         //???@(?^???W?@??)         
          IMAGE_C_String//                         
      }, 
 #if 0     
        {   {0},                     //ICON???m                        
            Str_REAR_SETUP,          //????"Rear Setup"?r??               
            NIL,                     //?W??ID                          
            NIL,                     //?U??ID                          
            NO_ICON_COLOR,           //ICON????Flag                    
            DESC_COLOR,              //?r??????Flag                    
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,//ACTION,    //???eOSD???A(?r??)     
            NO,                                                 
            REARChoice,              //???@(?^???W?@??)         
            REARString,                                        
        },                                                                
              
        {   {0},                     //ICON???m                        
            Str_TriggerVGA,          //????"Rear Setup"?r??               
            NIL,                     //?W??ID                          
            NIL,                     //?U??ID                          
            NO_ICON_COLOR,           //ICON????Flag                    
            DESC_COLOR,              //?r??????Flag                    
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,//ACTION,    //???eOSD???A(?r??)     
            NO,                                                 
            TriggerVGA,              //???@(?^???W?@??)         
            ONOFFChoiceString,                                        
        },    

        {   {0},                    //ICON???m             
            Str_TriggerDelay,             //????"MIRRO"?r??             
            NIL,                    //?W??ID               
            NIL,                    //?U??ID               
            NO_ICON_COLOR,          //ICON????Flag         
            DESC_COLOR,             //?r??????Flag         
            TRIGGERDELAYSELECT,            //???eOSD?????e(???T?hOSD)     
            OSDMENU,//CHOICEMENU,             //???eOSD???A                  
            NO,                                            
            0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            InputSelectMenu         //???@Flag             
        }, 
#endif
      {   {0},                     //ICON???m             
          Str_RETURN,              //????"RETRUN"?r??     
          NIL,                     //?W??ID               
          NIL,                     //?U??ID               
          NO_ICON_COLOR,           //ICON????Flag         
          DESC_COLOR,              //?r??????Flag         
          0,                       //???eOSD?????e(???T?hO
          ACTION,                  //???eOSD???A    Abel T
          NO,                                             
          TOHIGHMENU               //???@(?^???W?@??)     
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
/*             ???G?hOSD ---> CAMERA                   */  
/*-----------------------------------------------------*/  
#define     CAMERA_H   8 //ryan@20170904	7 //  5 

CODE BYTE CAMERAMenu[]={                          
    MENU_WIDTH,                                            
    CAMERA_H,                                           
    TITLE_COLOR,                                           
    CURSOR_COLOR,};                                        
                                                           
CODE struct DefineMenu DMCAMERA[]={       

	#ifndef AWT_ML072S
        {   {0},                    //ICON???m             
            Str_MIRROR,             //????"MIRRO"?r??             
            NIL,                    //?W??ID               
            NIL,                    //?U??ID               
            NO_ICON_COLOR,          //ICON????Flag         
            DESC_COLOR,             //?r??????Flag         
            DMCAMSELECT,            //???eOSD?????e(???T?hOSD)     
            OSDMENU,//CHOICEMENU,             //???eOSD???A                  
            NO,                                            
            0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            InputSelectMenu         //???@Flag             
        },     
	#else
       {   {0},                 //ICON???m                                      
          Str_CAMA,            //????"CAMA"?r??                               
          NIL,                 //?W??ID                                        
          NIL,                 //?U??ID                                        
          NO_ICON_COLOR,       //ICON????Flag                                  
          DESC_COLOR,          //?r??????Flag                                  
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                             
          CAMAONOFF,           //???@(?^???W?@??)         
          ONOFFChoiceString    //                         
      },         
      #ifdef HS
	{  {0}, 				//ICON???m										 
	 Str_CAMB,			  //????"CAMR"?r??								  
	 NIL,				  //?W??ID										   
	 NIL,				  //?U??ID										   
	 NO_ICON_COLOR, 	  //ICON????Flag								   
	 DESC_COLOR,		  //?r??????Flag								   
	 0,
	 ENUM_STRING,		  //???eOSD???A    Abel Test 
	 NO,												 
	 CAMBONOFF, 		//???@(?^???W?@??)		   
	 ONOFFChoiceString	  //						 
	 },    
	 #endif

       {  {0},                 //ICON???m                                       
          Str_CAMR,            //????"CAMR"?r??                                
          NIL,                 //?W??ID                                         
          NIL,                 //?U??ID                                         
          NO_ICON_COLOR,       //ICON????Flag                                   
          DESC_COLOR,          //?r??????Flag                                   
          0,
          ENUM_STRING,         //???eOSD???A    Abel Test 
          NO,                                                 
          CAMRONOFF,         //???@(?^???W?@??)         
          ONOFFChoiceString    //                         
      },    
	#endif

     //V1.1 03/19/07 simonsung    
	#ifdef QUAD		
	  #ifdef AWT_ML072Q
        {   {0},                    //ICON???m             
            Str_TriggerSet,             //????"Dir Image"?r??             
            NIL,                    //?W??ID               
            NIL,                    //?U??ID               
            NO_ICON_COLOR,          //ICON????Flag         
            DESC_COLOR,             //?r??????Flag         
            DMTRIGGERSELECT,            //???eOSD?????e(???T?hOSD)     
            OSDMENU,//CHOICEMENU,             //???eOSD???A                  
            NO,                                            
            0,//INPUTSELECTION,              //<william-961004-ver1.41>                  
            InputSelectMenu         //???@Flag             
        },   
	  #else  //HTRV
         {   {0},                     //ICON???m                        
            Str_DIR_IMAGE,           //????"Dir Image"?r??               
            NIL,                     //?W??ID                          
            NIL,                     //?U??ID                          
            NO_ICON_COLOR,           //ICON????Flag                    
            DESC_COLOR,              //?r??????Flag                    
            0,                       //???eOSD?????e(???T?hOSD)        
            ENUM_STRING,//ACTION,    //???eOSD???A(?r??)        
            NO,               
            IMAGEChoice,             //???@(?^???W?@??) 
            IMAGEString, 
        },
	  #endif

        {   {0},                     //ICON???m                        
            Str_REAR_SETUP,          //????"Rear Setup"?r??               
            NIL,                     //?W??ID                          
            NIL,                     //?U??ID                          
            NO_ICON_COLOR,           //ICON????Flag                    
            DESC_COLOR,              //?r??????Flag                    
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,//ACTION,    //???eOSD???A(?r??)     
            NO,                                                 
            REARChoice,              //???@(?^???W?@??)         
            REARString,
        },

        {   {0},                    //ICON???m                                           
            Str_JUMP,               //????"JUMP"?r??                             
            NIL,                    //?W??ID                                             
            NIL,                    //?U??ID                                             
            NO_ICON_COLOR,          //ICON????Flag                                       
            DESC_COLOR,             //?r??????Flag        
            0,                      //???eOSD?????e(???T?hOSD) 
            ENUM_STRING,            //???eOSD???A    Abel Test 
            NO,                                                 
            JUMPChoice,             //???@(?^???W?@??)         
            JUMPString                                        
        },      

	    {   {0},                    //ICON???m                    
            Str_CAM_OUT,            //????"CAM OUT"?r??             
            NIL,                    //?W??ID                      
            NIL,                    //?U??ID                      
            NO_ICON_COLOR,          //ICON????Flag                
            DESC_COLOR,             //?r??????Flag                
            0,                      //???eOSD?????e(???T?hOSD)    
            ENUM_STRING,            //???eOSD???A    Abel Test 
            NO,                                                 
            CAMOUTChoice,           //???@(?^???W?@??)         
            CAMOUTString,                                        
        },    
 	#endif

        {   {0},                    //ICON???m                    
            Str_SEQ_TIME_STEP,      //????"SEQ TIME STEP"?r??             
            NIL,                    //?W??ID                      
            NIL,                    //?U??ID                      
            NO_ICON_COLOR,          //ICON????Flag                
            DESC_COLOR,             //?r??????Flag            
            0,                      //???eOSD?????e(???T?hOSD)     
			#ifdef AWT_ML072S
			NUMBER,////NUMBER,
			#else
			BAR,
			#endif 
			NO,                                                     
            STIME_STEP,             //???@(?^???W?@??)              
            DefaultBar              //?????r??                                
        },     
        
#if  (defined AWT_ADD_TRIGGER_DELAY_FUN) //add by ryan@20170824
	#ifndef AWT_ML072S
        {   {0},                     //ICON???m
            Str_TriggerDelay,        //????"Trigger Delay"?r??
            NIL,                     //?W??ID
            NIL,                     //?U??ID
            NO_ICON_COLOR,           //ICON????Flag
            DESC_COLOR,              //?r??????Flag
            DelaySelectMenu,         //???eOSD?????e(???T?hOSD)
            OSDMENU,                 //???eOSD???A(?r??) 
            NO,
            0,                       //???@(?^???W?@??) 
            InputSelectMenu, 
        },
        #endif
#endif

	#ifdef AWT_ML072S
	 {   {0},                    //ICON???m                    
            Str_JumpAV,       //????"JumpAV"?r??             
            NIL,                    //?W??ID                      
            NIL,                    //?U??ID                      
            NO_ICON_COLOR,          //ICON????Flag                
            DESC_COLOR,             //?r??????Flag            
            0,                      //???eOSD?????e(???T?hOSD)     
            ENUM_STRING,                    //???eOSD???A(????String)          
            NO,                                                     
            JUMP_AV,             //???@(?^???W?@??)              
            ONOFFChoiceString//?????r??                                
        },  
	#ifdef HS
	#else
	{   {0},                     //ICON???m
            Str_TriggerDelay,        //????"Trigger Delay"?r??
            NIL,                     //?W??ID
            NIL,                     //?U??ID
            NO_ICON_COLOR,           //ICON????Flag
            DESC_COLOR,              //?r??????Flag
            DelaySelectMenu,         //???eOSD?????e(???T?hOSD)
            OSDMENU,                 //???eOSD???A(?r??) 
            NO,
            0,                       //???@(?^???W?@??) 
            InputSelectMenu, 
        },
        #endif
	  {   {0},					   //ICON???m						 
		  Str_RECALL,			   //????"RETRUN"?r??				 
		  NIL,					   //?W??ID 						 
		  NIL,					   //?U??ID 						 
		  NO_ICON_COLOR,		   //ICON????Flag					 
		  DESC_COLOR,			   //?r??????Flag					 
		  0,					   //???eOSD?????e(???T?hOSD)		 
		  ACTION,				   //???eOSD???A	Abel Test		 
		  NO,														 
		  RESET_VIDEOVALUE ,	   //???@(?^???W?@??)				 
	  },
	#endif
 
        {   {0},                     //ICON???m                  
            Str_RETURN,              //????"RETRUN"?r??           
            NIL,                     //?W??ID                    
            NIL,                     //?U??ID                    
            NO_ICON_COLOR,           //ICON????Flag              
            DESC_COLOR,              //?r??????Flag              
            0,                       //???eOSD?????e(???T?hOSD)  
            ACTION,                  //???eOSD???A    Abel Test             
            NO,                                                 
            TOHIGHMENU // EXITMENU , //???@(?^???W?@??)                             
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
			TV_ICON,                //Display??ICON
            0,//Str_Picture,           //?????r??
            NIL,                    //?W??ID
            NIL,                    //?U??ID
            TOPICON_COLOR,          //ICON????Flag(ON)
            NIL,                    //?r??????Flag(OFF)
            DMPicture,              //???eOSD?????e(???G?hOSD)
            OSDMENU,                //???eOSD???A
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
        {   UTIL_ICON,                 //Display??ICON
            0,//Str_Utility,               //?????r??
            NIL,                       //?W??ID
            NIL,                       //?U??ID
            TOPICON_COLOR,             //ICON????Flag(ON)
            NIL,                       //?r??????Flag(OFF)
            DMUtility,                 //???eOSD?????e(???G?hOSD)
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
       {   {0},                     //ICON???m                        
              Str_RECALL,              //????"RETRUN"?r??                
              NIL,                     //?W??ID                          
              NIL,                     //?U??ID                          
              NO_ICON_COLOR,           //ICON????Flag                    
              DESC_COLOR,              //?r??????Flag                    
              DMRecallSELECT,                       //???eOSD?????e(???T?hOSD)        
              OSDMENU,             //???eOSD???A(?r??) 
              NO,                                                 
              0,
              InputSelectMenu,       //                        
          },
     
 #else         
		{	{0},					 //ICON???m 					   
			Str_RECALL, 			 //????"RETRUN"?r?? 			   
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR, 			 //?r??????Flag 				   
			0,						 //???eOSD?????e(???T?hOSD) 	   
			ACTION, 				 //???eOSD???A	  Abel Test 	   
			NO, 													   
			RESET_PCVALUE ,		 //???@(?^???W?@??) 			   
		},
#endif
		

		{	{0},					 //ICON???m 					   
			Str_EXIT,				 //????"RETRUN"?r?? 			   
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR, 			 //?r??????Flag 				   
			0,						 //???eOSD?????e(???T?hOSD) 	   
			ACTION, 				 //???eOSD???A	  Abel Test 	   
			NO, 													   
			EXITMENU ,				 //???@(?^???W?@??) 			   
		},		  
#if 0		
		{	{0},					 //ICON???m 					   
			Str_SPACE,				  //????"RETRUN"?r??				
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			DESC_COLOR, 			 //?r??????Flag 				   
			0,						 //???eOSD?????e(???T?hOSD) 	   
			TEXT_STR,				   //???eOSD???A	Abel Test		 
			NO, 													   
			EXITMENU ,				 //???@(?^???W?@??) 			   
		},	 
	  
		{	{0},					 //ICON???m 					   
			Str_VER,				//????"RETRUN"?r??				  
			NIL,					 //?W??ID						   
			NIL,					 //?U??ID						   
			NO_ICON_COLOR,			 //ICON????Flag 				   
			VER_COLOR,				//?r??????Flag					  
			0,						 //???eOSD?????e(???T?hOSD) 	   
			TEXT_STR,				   //???eOSD???A	Abel Test		 
			NO, 													   
			EXITMENU ,				 //???@(?^???W?@??) 			   
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

		
        {   {0},                     //ICON???m                  
            Str_RETURN,              //????"RETRUN"?r??           
            NIL,                     //?W??ID                    
            NIL,                     //?U??ID                    
            NO_ICON_COLOR,           //ICON????Flag              
            DESC_COLOR,              //?r??????Flag              
            0,                       //???eOSD?????e(???T?hOSD)  
            ACTION,                  //???eOSD???A    Abel Test             
            NO,                                                 
            TOHIGHMENU // EXITMENU , //???@(?^???W?@??)                             
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
	            {0},                     //ICON???m                     
	            Str_RETURN2,              //????"RETRUN"?r??             
	            NIL,                     //?W??ID                       
	            NIL,                     //?U??ID                       
	            NO_ICON_COLOR,           //ICON????Flag                 
	            DESC_COLOR,              //?r??????Flag                 
	            0,                       //???eOSD?????e(???T?hOSD)     
	            ACTION,                  //???eOSD???A(?]?w???@)     
	            NO,                                                     
	            TOHIGHMENU               //???@(?^???W?@??)             
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

	    {   {0},                     //ICON???m                                          
            Str_Auto_Day_Night2,      //????"Auto Day & Night"?r?? 
            NIL,                     //?W??ID                     
            NIL,                     //?U??ID                                                     
            NO_ICON_COLOR,           //ICON????Flag                                                       
            DESC_COLOR,              //?r??????Flag                                                       
            0,                       //???eOSD?????e(???T?hOSD)                                           
            ENUM_STRING,             //???eOSD???A(?r??)
            NO, 
            DayChoice,               //???@(?^???W?@??)                         
            ONOFFChineseChoiceString,       //                                              
        },    

	  {   {0},                     //ICON???m                        
            Str_DIR_IMAGE2,           //????"Dir Image"?r??               
            NIL,                     //?W??ID                          
            NIL,                     //?U??ID                          
            NO_ICON_COLOR,           //ICON????Flag                    
            DESC_COLOR,              //?r??????Flag                    
            0,                       //???eOSD?????e(???T?hOSD)        
            ENUM_STRING,//ACTION,    //???eOSD???A(?r??)        
            NO,               
            IMAGEChoice,             //???@(?^???W?@??) 
            IMAGEChineseString, 
        },                                                             

        {   {0},                     //ICON???m                        
            Str_REAR_SETUP2,          //????"Rear Setup"?r??               
            NIL,                     //?W??ID                          
            NIL,                     //?U??ID                          
            NO_ICON_COLOR,           //ICON????Flag                    
            DESC_COLOR,              //?r??????Flag                    
            0,                       //???eOSD?????e(???T?hOSD)
            ENUM_STRING,//ACTION,    //???eOSD???A(?r??)     
            NO,                                                 
            REARChoice,              //???@(?^???W?@??)         
            REARString,                                        
        },    

        {   {0},                    //ICON???m                                           
            Str_JUMP2,               //????"JUMP"?r??                             
            NIL,                    //?W??ID                                             
            NIL,                    //?U??ID                                             
            NO_ICON_COLOR,          //ICON????Flag                                       
            DESC_COLOR,             //?r??????Flag        
            0,                      //???eOSD?????e(???T?hOSD) 
            ENUM_STRING,            //???eOSD???A    Abel Test 
            NO,                                                 
            JUMPChoice,             //???@(?^???W?@??)         
            JUMPChineseString                                        
        }, 
        
	  {
		{0},					   //ICON???m						 
		  Str_RECALL2,			   //????"RETRUN"?r??				 
		  NIL,					   //?W??ID 						 
		  NIL,					   //?U??ID 						 
		  NO_ICON_COLOR,		   //ICON????Flag					 
		  DESC_COLOR,			   //?r??????Flag					 
		  0,					   //???eOSD?????e(???T?hOSD)		 
		  ACTION,				   //???eOSD???A	Abel Test		 
		  NO,														 
		  RESET_USERVALUE,	   //???@(?^???W?@??)				 
	  },

          {   {0},                     //ICON???m                        
              Str_EXIT2,                //????"RETRUN"?r??                
              NIL,                     //?W??ID                          
              NIL,                     //?U??ID                          
              NO_ICON_COLOR,           //ICON????Flag                    
              DESC_COLOR,              //?r??????Flag                    
              0,                       //???eOSD?????e(???T?hOSD)        
              ACTION,                  //???eOSD???A    Abel Test        
              NO,                                                        
              EXITMENU ,               //???@(?^???W?@??)                
          },        

#if 0         
          {   {0},                     //ICON???m                        
              Str_SPACE,                //????"RETRUN"?r??                
              NIL,                     //?W??ID                          
              NIL,                     //?U??ID                          
              NO_ICON_COLOR,           //ICON????Flag                    
              DESC_COLOR,              //?r??????Flag                    
              0,                       //???eOSD?????e(???T?hOSD)        
              TEXT_STR,                  //???eOSD???A    Abel Test        
              NO,                                                        
              EXITMENU ,               //???@(?^???W?@??)                
          },   
        
          {   {0},                     //ICON???m                        
              Str_VER,                //????"RETRUN"?r??                
              NIL,                     //?W??ID                          
              NIL,                     //?U??ID                          
              NO_ICON_COLOR,           //ICON????Flag                    
              VER_COLOR,              //?r??????Flag                    
              0,                       //???eOSD?????e(???T?hOSD)        
              TEXT_STR,                  //???eOSD???A    Abel Test        
              NO,                                                        
              EXITMENU ,               //???@(?^???W?@??)                
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
	     TV_ICON,                //Display??ICON                         
            0,//Str_Picture,           //?????r??                    
            NIL,                       //?W??ID        
            NIL,                       //?U??ID                        
            TOPICON_COLOR,             //ICON????Flag(ON)                          
            NIL,                       //?r??????Flag(OFF)                          
            ChinesePicture,                 //???eOSD?????e(???G?hOSD)                         
            OSDMENU,                   //???eOSD???A   
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
		
             {   {0},                     //ICON???m                  
                 Str_RETURN2,              //????"RETRUN"?r??           
                 NIL,                     //?W??ID                    
                 NIL,                     //?U??ID                    
                 NO_ICON_COLOR,           //ICON????Flag              
                 DESC_COLOR,              //?r??????Flag              
                 0,                       //???eOSD?????e(???T?hOSD)  
                 ACTION,                  //???eOSD???A    Abel Test             
                 NO,                                                 
                 TOHIGHMENU // EXITMENU , //???@(?^???W?@??)                             
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


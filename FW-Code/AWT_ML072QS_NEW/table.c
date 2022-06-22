#include "Config.h"
#include "typedefs.h"
#include "pc_eep.h"
#include "measure.h"
/*===========================================================================

xx_x_SS.txt		for Samsung panel
xx_x_LP.txt		for LG-Philips panel
xx_x_Sh.txt		for Sharp panel
xx_x_PV.txt		for Prime View panel

/*===========================================================================*/
/*                              NTSC Mode                                    */
/*===========================================================================*/
CODE BYTE NTSC_Regs[] ={

	#if   defined SXGA
						#include "data\SX_N.txt"
	#elif defined XGA	
						#include "data\X_N_LVDS.txt"
					//	#include "data\X_N.txt"	
	#elif defined SVGA
						#include "data\S_N.txt"
	#elif defined VGA
		#if defined HITACHI_640_B_160
						#include "data\V_N(HITACHI_6416).txt"
		#elif defined AND_640_480
						#include "data\V_N(AND_6448).txt"
		#else
						#include "data\V_N.txt"
		#endif
	#elif defined QVGA
		#if defined HITACHI_TX09D73
						#include "data\QV_N(HITACHI_TX09D73).txt"
		#elif defined AU_DELTARGB
						#include "data\QVGA_Delta_AU.txt"
		#elif defined SHARP_LQ050Q5DR01
						#include "data\QV_N(LQ050Q5DR01_SHARP).TXT"
		#elif defined SHARP_LQ035
						#include "data\QV_LQ035Q5DG02_sharp.txt"
		#elif defined TMD
						#include "data\QV_N_TMD.txt"
		#else
						#include "data\QV_N_new.txt"
		#endif
	#elif defined WXGA
			#ifdef WX_SHARP_LQ106K1LA
						#include "data\WX_N_SHARP_LQ106K1LA.txt"
			#else
						#include "data\WX_N.txt"
			#endif
	#elif defined WSVGA
						#include "data\WS_N.txt"
	#elif defined WVGA
		#if defined AU_10INCH
						#include "data\WV_N.txt"
		#elif defined WVGA_TPO
						#include "data\WV_N_TPO.txt"
		#elif defined SAMSUNG_10INCH
						#include "data\Wv_n_Samsung.txt"
		#elif defined SAMSUNG_TICONLESS_10INCH
						#include "data\Wv_n1(Samsung_Notion).txt"
		#elif defined SHARP_TICONLESS_7INCH
						//#include "data\WV_N( SHARP LQ080Y5DR02).txt"
						//#include "data\WV_N(Sharp TCON less panel_7).txt"
						#include "data\WV_N3(WVGA SHARP_TLE_CCFL).txt"
		#elif defined AU_TICONLESS_7INCH
						//#include "data\WV_N_Temp.txt"
						//#include "data\WV_N3(WVGA AUO TCON LESS 7INCH_STD).TXT"
						//#include "data\WV_N3(WVGA AUO TCON LESS 8_4 INCH_STD).TXT"
						#include "data\WQV_N3(WVGA AUO T-CON LESS ANALOG 7INCH).TXT"
						//#include "data\Digital_NTSC_7INCH_800_480.TXT"		//WILLIAM_2012917
		#elif defined AU_G084SN05V8_8_4INCH
						#include "data\WV_N3(WVGA AUO TCON LESS 8_4 INCH_STD).TXT"
		#elif defined HSD070IDW1_7INCH
				#ifdef QUAD
						#include "data\WV_NQ(WVGA HANNSTAR TCON LESS 7 INCH_STD).TXT"
				#else
						#include "data\WV_N3(WVGA HANNSTAR TCON LESS 7 INCH_STD).TXT"

				#endif
						
						//#include "data\WV_N3(WVGA AUO TCON LESS 8_4 INCH_STD).TXT"
		#elif defined AU_TICONLESS_7INCH_CCFL
						#include "data\WV_N3(WVGA AUO TCON LESS 7INCH_CCFL).TXT"
		#elif defined AU_TICONLESS_10INCH	
						#include "data\WV_N3(WVGA AUO TCON LESS 10INCH).TXT"
		#elif defined HITACHI_T01
						#include "data\WV_N(WVGA_HITACHI_T_01).TXT"
		#elif defined HITACHI_TX23D12
						#include "data\WV_N(HITACHI_TX23D12).TXT"
		#elif defined HITACHI_TX18D24
						#include "data\WV_N(HITACHI_TX18D24).txt"
		#elif defined HITACHI_TX18D16
						#include "data\WV_N(HITACHI_TX18D16).txt"
		#elif defined TMD_LTA070A320F
						#include "data\WV_N(TMD_LTA070A320F).txt"
		#elif defined TMD_LTA080B
						#include "data\WV_N(WVGA TMD_LTA080B).txt"
		#elif defined INNOLUX_AT080TN03
						#include "data\WV_N(INNOLUX_AT080TN03).TXT"
		#elif defined CMO
						#include "data\WV_N(WVGA CMO TCON LESS 7INCH_CCFL).TXT"
		#else
						#include "data\WV_N.txt"
		#endif
    #elif defined WQVGA
        #if defined ANALOG_7INCH  
						#include "data\WQV_N(AUO T-CON LESS ANALOG 7INCH).TXT"
		#elif defined SHARP_LQ043T3DX02
						#include "data\WQV_N_sh(LQ043T3DX02).txt" // 8bit TTL panel 480*237
		#elif defined LG_ANALOG
						#include "data\WQV_N_LGANALOG.txt" // 8bit TTL panel 480*237
		#elif defined TMD_ANALOG
						#include "data\WQVGA_N_TMD(LTA05B352A).txt"
		#elif defined T_51945GD
						#include "data\WQV_N(T-51945GD).TXT"
		#endif
			
	#endif

};

#ifdef ADD_ANALOGPANEL
CODE BYTE NTSC_Regs_Analog[] ={
		#ifdef ADD_ANALOG_7INCH
						#include "data\WQV_N3(WVGA AUO T-CON LESS ANALOG 7INCH).TXT"
		#elif defined ADD_TMD_LTA05B352A
						#include "data\WQVGA_N_TMD(LTA05B352A).txt"
		#endif
};
#endif

#ifdef SUPPORT_DVI
CODE BYTE DVI_Regs[] ={
		#include "data\DVI_WQVGA.txt"
};
#endif

/*===========================================================================*/
/*                              PAL Mode                                     */
/*===========================================================================*/
CODE BYTE	PAL_Regs[]   = {	

	#if   defined SXGA
						#include "data\SX_P.txt"
	#elif defined XGA
						#include "data\X_P.txt"
	#elif defined SVGA
						#include "data\S_P.txt"
	#elif defined VGA
		#if defined HITACHI_640_B_160
						#include "data\V_N(HITACHI_6416).txt"
		#else
						#include "data\V_P.txt"
		#endif
	#elif defined QVGA
		#if defined AU_DELTARGB
						#include "data\QVGA_P_Delta_AU.txt"
		#elif defined SHARP_LQ050Q5DR01
						#include "data\QV_P(LQ050Q5DR01_SHARP).TXT"
		#elif defined TMD
						#include "data\QV_P_TMD.txt"
		#else
						#include "data\QV_P.txt"
		#endif
	#elif defined WXGA 
			#ifdef WX_SHARP_LQ106K1LA
						#include "data\WX_P_SHARP_LQ106K1LA.txt"
			#else
						#include "data\WX_P.txt"
			#endif
	#elif defined WSVGA
						#include "data\WS_P.txt"
	#elif defined WVGA
		#if defined AU_10INCH
						#include "data\WV_P.txt"
		#elif defined WVGA_TPO
						#include "data\WV_P_TPO.txt"
		#elif defined SAMSUNG_10INCH
						#include "data\Wv_P_Samsung.txt"
		#elif defined SAMSUNG_TICONLESS_10INCH
						#include "data\WV_P(Samsung_Noticon).txt"
		#elif defined SHARP_TICONLESS_7INCH
						#include "data\WV_P(LQ080Y5DR02).TXT"
						//#include "data\WV_P3(Sharp TCON less panel_1).txt"
		#elif defined AU_TICONLESS_7INCH
						//#include "data\WV_P3(WVGA AUO TCONLESS 7INCH PANEL).TXT"
						//#include "data\WV_P3(WVGA AUO TCON LESS 8_4 INCH_STD).TXT"
						#include "data\WQV_P3(WVGA AUO T-CON LESS ANALOG 7INCH).TXT"
		#elif defined AU_G084SN05V8_8_4INCH
						#include "data\WV_P3(WVGA AUO TCON LESS 8_4 INCH_STD).TXT"	
		#elif defined HSD070IDW1_7INCH
				#ifdef QUAD
						#include "data\WV_PQ(WVGA HANNSTAR TCON LESS 7 INCH_STD).TXT"		
				#else
						#include "data\WV_P3(WVGA HANNSTAR TCON LESS 7 INCH_STD).TXT"	
				#endif
						
		#elif defined AU_TICONLESS_7INCH_CCFL
						#include "data\WV_P3(WVGA AUO TCONLESS 7INCH PANEL).TXT"
		#elif defined AU_TICONLESS_10INCH	
						#include "data\WV_P3(WVGA AUO T-CON LESS).txt"
		#elif defined CMO
						#include "data\WV_P(WVGA CMO TCONLESS 7INCH PANEL).TXT"
		#elif defined HITACHI_T01
						#include "data\WV_N(WVGA_HITACHI_T_01).TXT"
		#elif defined HITACHI_TX23D12
						#include "data\WV_N(HITACHI_TX23D12).TXT"
		#elif defined HITACHI_TX18D24
						#include "data\WV_N(HITACHI_TX18D24).txt"
		#elif defined HITACHI_TX18D16
						#include "data\WV_P(HITACHI_TX18D16).txt"
		#elif defined TMD_LTA070A320F
						#include "data\WV_N(TMD_LTA070A320F).txt"
		#elif defined TMD_LTA080B
						#include "data\WV_N(WVGA TMD_LTA080B).txt"
		#elif defined INNOLUX_AT080TN03
						#include "data\WV_N(INNOLUX_AT080TN03).TXT"
		#endif
    #elif defined WQVGA
		#if defined T_51945GD
						#include "data\WQV_N(T-51945GD).TXT"
		#else
						#include "data\WQV_P(AUO T-CON LESS ANALOG 7INCH).TXT"
		#endif
	#endif


};

#ifdef ADD_ANALOGPANEL
CODE BYTE	PAL_Regs_Analog[]   = {	
		#ifdef ADD_ANALOG_7INCH
						#include "data\WQV_N3(WVGA AUO T-CON LESS ANALOG 7INCH).TXT"
		#elif defined ADD_TMD_LTA05B352A
						#include "data\WQVGA_N_TMD(LTA05B352A).txt"
		#endif
};
#endif
/*===========================================================================*/
/*                              PC Mode Table                                */
/*===========================================================================*/
#ifdef SUPPORT_PC

#if   defined SXGA
						#include "data\PC_SXGA.txt"
#elif defined XGA
						#include "data\PC_XGA.txt"
#elif defined SVGA
						#include "data\PC_SVGA.txt"
#elif defined VGA
						#include "data\PC_VGA.txt"
#elif defined WXGA
						#include "data\PC_WXGA.txt"
#elif defined WVGA
						#include "data\PC_WVGA.txt"
#elif defined WQVGA
						#include "data\PC_WQVGA.txt"
#else
						#include "data\PC_VGA.txt"
#endif

#endif	// SUPPORT_PC

/*===========================================================================*/
/*                              Component YPbPr Table                        */
/*===========================================================================*/
#ifdef SUPPORT_COMPONENT

#if   defined SXGA
						#include "data\CV_SXGA.txt"
#elif defined XGA
						#include "data\CV_XGA.txt"
#elif defined SVGA
						#include "data\CV_SVGA.txt"
#elif defined VGA
						#include "data\CV_VGA.txt"
#elif defined WXGA
						#include "data\CV_WXGA.txt"
#elif defined WVGA
						#include "data\CV_WVGA.txt"
#elif defined WQVGA
						#include "data\CV_WQVGA.txt"
#elif defined QVGA
						#include "data\CV_QVGA.txt"
#else
						#include "data\CV_VGA.txt"
#endif

#endif //SUPPORT_COMPONENT

/* Monitor.c */

#include "config.h"

#ifdef SERIAL

#include "typedefs.h"
#include "main.h"
#include "i2c.h"
#include "dispinfo.h"
#include "reg.h"
#include "regmap.h"
#include "printf.h"
//#include "dispinfo.h"
//#include "video.h"
//#include "eeprom.h"
//#include "measure.h"
#include "tw88.h"
#include "etc_eep.h"
#include "osdbasic.h"
#include "monitor.h"
#include "cpu.h"
#include "Measure.h"
#include "Adc.h"

#include "spi.h"

	IDATA BYTE MonAddress = 0x8a;		// initialize value should be placed to IDATA area
	BYTE MonIndex;
	BYTE MonRdata, MonWdata;

BYTE monstr[30];		// buffer for input string
BYTE *argv[7];
BYTE argc=0;
bit	echo=1;

static bit indirect=0;

//extern		  bit	AutoDetect;
extern   BYTE InputSelection;
extern	      BYTE	DebugLevel;
extern  CODE  struct struct_IdName struct_InputSelection[];
extern 		  bit	NoInitAccess;
 		  bit	AccessEnable;

//void Loader(BYTE);

//=============================================================================
//
//=============================================================================

#ifdef Monitor_debug
void Prompt(void)
{

	if ( MonAddress == TW88I2CAddress )
		Printf("\r\nMCU_I2C[%02x]>", (WORD)MonAddress);
	else
		Printf("\r\nI2C[%02x]>", (WORD)MonAddress);
}


void Mon_tx(BYTE ch)
{
	RS_tx(ch);
}



//=============================================================================
//		Convert ASCII to Binery                                             
//=============================================================================

DWORD a2i(BYTE *str)
{
	DWORD num=0;
	BYTE i;

	for(i=0; ; i++, str++) {
		if( *str=='\0' || *str==' ' ) break;
		num = num*10 + *str - '0';
	}
	return num;
}

BYTE Asc1Bin(BYTE asc)
{
	if(asc>='0' && asc <='9') return (asc - '0');
	if(asc>='a' && asc <='f') return (asc - 'a' + 0x0a);
	if(asc>='A' && asc <='F') return (asc - 'A' + 0x0a);

	#ifndef  Hs_debug
	return ('0');  //Pinchi 20150302 add for compiler warning
	#endif
}

BYTE Asc2Bin(PDATA_P BYTE *s)
{
	WORD bin;

	bin = 0;
	while(*s != '\0' && *s !=' ') {
		bin = bin<<4;
		bin = bin + Asc1Bin(*s);
		s++;
	}
	return (bin);
}


//=============================================================================
BYTE toupper(BYTE ch)
{
	if( ch>='a' && ch<='z' )
		return (ch - 'a' + 'A');

	#ifndef  Hs_debug
	return ('A');  //Pinchi 20150302 add for compiler warning
	#endif
}


int stricmp(BYTE *ptr1, BYTE *ptr2)
{
	int		i;
	int		ret;
	
	for(i=0; *ptr1; i++) {
		ret = toupper(*ptr1++) - toupper(*ptr2++);
		if( ret ) return ret;
	}
	return 0;
}
#endif
//=============================================================================
//
//=============================================================================
#ifdef Monitor_debug
void SetMonAddress(BYTE addr)
{
	MonAddress = addr;
}
#endif

#ifdef Monitor_debug
void MonReadI2C(void)
{
	if( argc>=2 ) MonIndex = Asc2Bin( argv[1] );
	else	{
		Printf("   --> Missing parameter !!!");
		return;
	}

	if ( MonAddress == TW88I2CAddress )
		MonRdata = ReadTW88(MonIndex);
	else
		MonRdata = ReadI2C(MonAddress, MonIndex);

	if( echo )
		Printf("\r\nRead %2xh:%2xh", (WORD)MonIndex, (WORD)MonRdata);	
	
	MonWdata = MonRdata;
}


void MonWriteI2C(void)
{
	if( argc<3 ) {
		Printf("   --> Missing parameter !!!");
		return;
	}
	
	MonIndex = Asc2Bin( argv[1] );
	MonWdata = Asc2Bin( argv[2] );
	
	if( echo ) {
		Printf("\r\nWrite %2xh:%2xh ", (WORD)MonIndex, (WORD)MonWdata);
		if ( MonAddress == TW88I2CAddress ) {
			WriteTW88(MonIndex, MonWdata);
			MonRdata = ReadTW88(MonIndex);
		}
		else {
			WriteI2C(MonAddress, MonIndex, MonWdata);
			MonRdata = ReadI2C(MonAddress, MonIndex);
		}
   		Printf("==> Read %2xh:%2xh", (WORD)MonIndex, (WORD)MonRdata);
	}
	else {
		if ( MonAddress == TW88I2CAddress ) {
			WriteTW88(MonIndex, MonWdata);
		}
		else {
			WriteI2C(MonAddress, MonIndex, MonWdata);
		}
	}
}

#endif


#ifdef Monitor_debug
void MonIncDecI2C(BYTE inc)
{

	switch(inc){
	case 0:  MonWdata--;	break;
	case 1:  MonWdata++;	break;
	case 10: MonWdata-=0x10;	break;
	case 11: MonWdata+=0x10;	break;
	}


	if ( MonAddress == TW88I2CAddress ) {
		WriteTW88(MonIndex, MonWdata);
		MonRdata = ReadTW88(MonIndex);
	}
	else {
		WriteI2C(MonAddress, MonIndex, MonWdata);
		MonRdata = ReadI2C(MonAddress, MonIndex);
	}

	if( echo ) {
		Printf("Write %2xh:%2xh ", (WORD)MonIndex, (WORD)MonWdata);
		Printf("==> Read %2xh:%2xh", (WORD)MonIndex, (WORD)MonRdata);
	}

	Prompt();

}

void MonDumpI2C(void)
{
	BYTE ToMonIndex;
	int  cnt=8;

	if( argc>=2 ) MonIndex = Asc2Bin(argv[1]);
	if( argc>=3 ) ToMonIndex = Asc2Bin(argv[2]);
	else ToMonIndex = MonIndex+cnt;
	if ( ToMonIndex < MonIndex ) ToMonIndex = 0xFF;
	cnt = ToMonIndex - MonIndex + 1;

	if( echo ) {
		if ( MonAddress == TW88I2CAddress ) {
			for ( ; cnt > 0; cnt-- ) {
				MonRdata = ReadTW88(MonIndex);
				Printf("\r\n==> Read %2xh:%2xh", (WORD)MonIndex, (WORD)MonRdata);
				MonIndex++;
			}
		}
		else {
			for ( ; cnt > 0; cnt-- ) {
				MonRdata = ReadI2C(MonAddress, MonIndex);
				Printf("\r\n==> Read %2xh:%2xh", (WORD)MonIndex, (WORD)MonRdata);
				MonIndex++;
			}
		}
	}
	else {
		if ( MonAddress == TW88I2CAddress ) {
			for ( ; cnt > 0; cnt-- ) {
				MonRdata = ReadTW88(MonIndex);
				MonIndex++;
			}
		}
		else {
			for ( ; cnt > 0; cnt-- ) {
				MonRdata = ReadI2C(MonAddress, MonIndex);
				MonIndex++;
			}
		}
	}
}

//-----------------------------------------------------------------------------

void MonNewReadI2C(void)
{
	BYTE Slave;

	if( argc>=3 ) MonIndex = Asc2Bin( argv[2] );
	else	{
		Printf("   --> Missing parameter !!!");
		return;
	}
	Slave = Asc2Bin(argv[1]);

	if ( Slave == TW88I2CAddress )
		MonRdata = ReadTW88(MonIndex);
	else
		MonRdata = ReadI2C(Slave, MonIndex);

	if( echo )
		Printf("\r\n<R>%2x[%2x]=%2x", (WORD)Slave, (WORD)MonIndex, (WORD)MonRdata);
	
	MonWdata = MonRdata;
}

void MonNewWriteI2C(void)
{
	BYTE Slave;

	if( argc<4 ) {
		Printf("   --> Missing parameter !!!");
		return;
	}
	
	MonIndex = Asc2Bin( argv[2] );
	MonWdata = Asc2Bin( argv[3] );
	Slave = Asc2Bin(argv[1]);
	
	if ( Slave == TW88I2CAddress ) {
		WriteTW88(MonIndex, MonWdata);
		MonRdata = ReadTW88(MonIndex);
	}
	else {
		WriteI2C(Slave, MonIndex, MonWdata);
		MonRdata = ReadI2C(Slave, MonIndex);
   	}

	if( echo )
		Printf("\r\n<R>%2x[%2x]=%2x", (WORD)Slave, (WORD)MonIndex, (WORD)MonRdata);

}

void MonNewDumpI2C(void)
{
	BYTE 	ToMonIndex, Slave;
	WORD	i;
	
	if( argc>=2 ) MonIndex = Asc2Bin(argv[2]);
	if( argc>=3 ) ToMonIndex = Asc2Bin(argv[3]);
	Slave = Asc2Bin(argv[1]);

	if( echo ) {
		if ( Slave == TW88I2CAddress ) {
			for(i=MonIndex; i<=ToMonIndex; i++) {
				MonRdata = ReadTW88(i);
        		Printf("\r\n<R>%2x[%2x]=%2x", (WORD)Slave, (WORD)i, (WORD)MonRdata);
			}
		}
		else {
			for(i=MonIndex; i<=ToMonIndex; i++) {
				MonRdata = ReadI2C(Slave, i);
        		Printf("\r\n<R>%2x[%2x]=%2x", (WORD)Slave, (WORD)i, (WORD)MonRdata);
			}
		}
	}
	else {
		if ( Slave == TW88I2CAddress ) {
			for(i=MonIndex; i<=ToMonIndex; i++) {
				MonRdata = ReadTW88(i);
			}
		}
		else {
			for(i=MonIndex; i<=ToMonIndex; i++) {
				MonRdata = ReadI2C(Slave, i);
			}
		}
	}
}


void MonWriteBit(void)
{
	BYTE mask, i, FromBit, ToBit,  MonMask, val;
	BYTE Slave;
	// b 88 index startbit|endbit data

	if( argc<5 ) {
		Printf("   --> Missing parameter !!!");
		return;
	}
	Slave = Asc2Bin(argv[1]);

	MonIndex = Asc2Bin( argv[2] );
	FromBit  = (Asc2Bin( argv[3] ) >> 4) & 0x0f;
	ToBit  = Asc2Bin( argv[3] )  & 0x0f;
	MonMask  = Asc2Bin( argv[4] );

	if( FromBit<ToBit || FromBit>7 || ToBit>7) {
		Printf("\r\n   --> Wrong range of bit operation !!!");
		return;
	}
	
	mask = 0xff; 
	val=0x7f;
	for(i=7; i>FromBit; i--) {
		mask &= val;
		val = val>>1;
	}

	val=0xfe;
	for(i=0; i<ToBit; i++) {
		mask &= val;
		val = val<<1;
	}

	if ( Slave == TW88I2CAddress ) {
		MonRdata = ReadTW88(MonIndex);
		MonWdata = (MonRdata & (~mask)) | (MonMask & mask);
				
		WriteTW88(MonIndex, MonWdata);
		MonRdata = ReadTW88(MonIndex);
	}
	else {
		MonRdata = ReadI2C(Slave, MonIndex);
		MonWdata = (MonRdata & (~mask)) | (MonMask & mask);
				
		WriteI2C(Slave, MonIndex, MonWdata);
		MonRdata = ReadI2C(Slave, MonIndex);
	}

	if( echo )
		Printf("\r\n<R>%2x[%2x]=%2x", (WORD)Slave, (WORD)MonIndex, (WORD)MonRdata);

}
#endif

#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
void PclkAccess(void)
{
	DWORD pclk;

	if( argc > 2 ) {
		Printf("   --> Too many parameter !!!");
		return;
	}

	if( argc==2 ) {
		pclk = (DWORD)a2i(argv[1]) * 1000000;
		Printf("\r\n --> Set Pclk:  %ld Hz ", pclk);
//		Printf("\r\n Not Suuport ");
		ChangeInternPLL(pclk);
	}
	
	if( argc==1)   GetPPF();
	
}
#endif

#ifdef  Monitor_debug
void MonTxDump(void)
{
	WORD	count;

	if ( argc < 2 ) {
		Puts("\r\nInsufficient parameters...");
		return;
	}
	count = (WORD)a2i(argv[1]);
	do {
		RS_tx((count&0x1F)+0x20);
		count--;
	} while ( count != 0 );
}
#endif
//=============================================================================
//			Help Message
//=============================================================================
#ifdef Monitor_debug
void MonHelp(void)
{
	Printf("\r\n=======================================================");
	Printf("\r\n>>>     Welcome to Techwell Monitor  Rev 1.00     <<<");
	Printf("\r\n=======================================================");
	Printf("\r\n   R ii             ; Read data");
	Printf("\r\n   W ii dd          ; Write data");
	Printf("\r\n   D [ii] [cc]      ; Dump");
	Printf("\r\n   C aa             ; Change I2C address");
	Printf("\r\n   M ?              ; Current Input");
	Printf("\r\n   M dd             ; Change Input");
	Printf("\r\n   Access [0,1]     ; Program TW88xx Access OFF/ON");
	Printf("\r\n   AutoDetect [0,1] ; PC Automode OFF/ON");
	Printf("\r\n   PCAuto		    ; RUN PC Auto Adjust");
	Printf("\r\n   Debug [0..255]   ; Debuging display level");
	Printf("\r\n   Echo On/Off      ; Terminal Echoing On/Off");
	Printf("\r\n   Delta            ; Init DeltaRGB Panel");
	Printf("\r\n   Delta w ii dh dl; SPI Write to DeltaRGB Panel");
	Printf("\r\n");
	Printf("\r\n=======================================================");
	Printf("\r\n");
}

//=============================================================================
//
//=============================================================================
BYTE MonGetCommand(void)
{
	static BYTE comment=0;
	static BYTE incnt=0, last_argc=0;
	BYTE i, ch;
	BYTE ret=0;

	if( !RS_ready() ) return 0;
#ifdef Monitor_debug
	ch = RS_rx();
#endif
	//----- if comment, echo back and ignore -----
	if( comment ) {
		if( ch=='\r' || ch==0x1b ) comment = 0;
		else { 
			Mon_tx(ch);
			return 0;
		}
	}
	else if( ch==';' ) {
		comment = 1;
		Mon_tx(ch);
		return 0;
	}

	//=====================================
	switch( ch ) {

	case 0x1b:
		argc = 0;
		incnt = 0;
		comment = 0;
		Prompt();
		return 0;

	//--- end of string
	case '\r':

		if( incnt==0 ) {
			Prompt();
			break;
		}

		monstr[incnt++] = '\0';
		argc=0;

		for(i=0; i<incnt; i++) if( monstr[i]!=' ' ) break;

		if( !monstr[i] ) {
			incnt = 0;
			comment = 0;
			Prompt();
			return 0;
		}
		argv[0] = &monstr[i];
		for(; i<incnt; i++) {
			if( monstr[i]==' ' || monstr[i]=='\0' ) {
				monstr[i]='\0';
     			 //Printf("(%s) ",  argv[argc]);
				i++;
				while( monstr[i]==' ' ) i++;
				argc++;
				if( monstr[i] ){
     			 argv[argc] = &monstr[i];
				}
			}
		}

		ret = 1;
		last_argc = argc;
		incnt = 0;
		
		break;

	//--- repeat command
	case '/':
		argc = last_argc;
		ret = 1;
		break;

	//--- back space
	case 0x08:
		if( incnt ) {
			incnt--;
			Mon_tx(ch);
			Mon_tx(' ');
			Mon_tx(ch);
		}
		break;

	//--- decreamental write
	case ',':
		if( incnt ) {
			Mon_tx(ch);
			monstr[incnt++] = ch;
		}
		else
			MonIncDecI2C(0);
		break;

	case '<':
		if( incnt ) {
			Mon_tx(ch);
			monstr[incnt++] = ch;
		}
		else
			MonIncDecI2C(10);
		break;
	//--- increamental write
	case '.':
		if( incnt ) {
			Mon_tx(ch);
			monstr[incnt++] = ch;
		}
		else
			MonIncDecI2C(1);
		break;

	case '>':
		if( incnt ) {
			Mon_tx(ch);
			monstr[incnt++] = ch;
		}
		else
			MonIncDecI2C(11);
		break;

	default:
		Mon_tx(ch);
		monstr[incnt++] = ch;
		break;
	}

	if( ret ) {
		comment = 0;
		last_argc = argc;
		return ret;
	}
	else {
		return ret;
	}
}
#endif
//*****************************************************************************
//				Monitoring Command
//*****************************************************************************
#ifdef Monitor_debug
void Monitor(void)
{
	if( !MonGetCommand() ) return;

	//--------------------------------------------------
	// Check Indirect command
	/*
	if( !stricmp( argv[0], "I" ) ) 			indirect=1;	
	else if( !stricmp( argv[0], "O" ) ) 	indirect=1;	

	else if( !stricmp( argv[0], "," ) ) 	indirect=0;	
	else if( !stricmp( argv[0], ">" ) ) 	indirect=0;	
	else if( !stricmp( argv[0], "<" ) ) 	indirect=0;	
	else if( !stricmp( argv[0], "." ) ) 	indirect=0;	
	else  indirect=0;	
	*/
	indirect = 0;

	//---------------- Write Register -------------------
	if( !stricmp( argv[0], "W" ) ) {
		MonWriteI2C();
	}
	else if( !stricmp( argv[0], ")" ) ) {
		indirect=0;
		MonNewWriteI2C();
	}
	/*
	else if( !stricmp( argv[0], "O" ) ) {			// inderect addressing for 8806
		MonIndex = Asc2Bin( argv[1] );
		MonWdata = Asc2Bin( argv[2] );
		WriteI2C(MonAddress, 0xc5, MonIndex);
		WriteI2C(MonAddress, 0xc6, MonWdata);
		MonRdata = ReadI2C(MonAddress, 0xc6);
		Printf("\r\n==> Read %2xh:%2xh", (WORD)MonIndex, (WORD)MonRdata);
	}
	*/
	//---------------- Read Register --------------------
	else if ( !stricmp( argv[0], "R" ) ) {
		MonReadI2C();
	}
	else if ( !stricmp( argv[0], "(" ) ) {
		indirect=0;
		MonNewReadI2C();
	}
	/*
	else if( !stricmp( argv[0], "i" ) ) {
		MonIndex = Asc2Bin( argv[1] );
		WriteI2C(MonAddress, 0xc5, MonIndex);
		MonRdata = ReadI2C(MonAddress, 0xc6);
		Printf("\r\n==> Read %2xh:%2xh", (WORD)MonIndex, (WORD)MonRdata);

	}
	*/
	//---------------- Dump Register --------------------
	else if( !stricmp( argv[0], "D" ) ) {
		Puts("\r\ndump start");
		MonDumpI2C();
	}
	else if( !stricmp( argv[0], "&" ) ) {
		indirect=0;
		MonNewDumpI2C();
	}

	//---------------- Bit Operation --------------------
	else if( !stricmp( argv[0], "B" ) ) {// Write bits - B AA II bb DD
		MonWriteBit();
	}
	/*	no indirect addressing in TW8816
    //---------------------------------------------------
	else if( !stricmp( argv[0], "@" ) ) { // Indirect address bit access

					BYTE Slave, mask, FromBit, ToBit,  MonMask, val,i;
					// @ 8a iaddr idata index  startbit|endbit  data
					// 0  1   2    3     4     5                 6

					if( argc<7 ) {
						Printf("   --> Missing parameter !!!");
						return;
					}

					Slave = Asc2Bin(argv[1]);
					
					FromBit = Asc2Bin( argv[5] );
					FromBit  = ( FromBit >> 4) & 0x0f;
					ToBit = Asc2Bin( argv[5] );
					ToBit  =  ToBit & 0x0f;
					MonMask  = Asc2Bin( argv[6] );

					if( FromBit<ToBit || FromBit>7 || ToBit>7) {
						Printf("\r\n   --> Wrong range of bit operation !!!");
						return;
					}
	
					mask = 0xff; 
					val=0x7f;
					for(i=7; i>FromBit; i--) {
						mask &= val;
						val = val>>1;
					}

					val=0xfe;
					for(i=0; i<ToBit; i++) {
						mask &= val;
						val = val<<1;
					}

					// @ 8a iaddr idata index  startbit|endbit  data
					// 0  1   2    3     4     5                 6
					MonIndex = Asc2Bin(argv[2]);
					MonWdata = Asc2Bin(argv[4]);
					WriteI2C( Slave, MonIndex, MonWdata);

					MonRdata = ReadI2C(Slave, Asc2Bin( argv[3]));
					MonWdata = (MonRdata & (~mask)) | (MonMask & mask);
					MonIndex = Asc2Bin(argv[3]);
					WriteI2C(Slave, MonIndex, MonWdata);

					MonRdata = ReadI2C(Slave, MonIndex);

					Printf("\r\n<R>%2x[%2x]=%2x", (WORD)Slave, (WORD)MonIndex, (WORD)MonRdata);

	}
	//------------------------------------------------------------------				
	else if( !stricmp( argv[0], "!" ) ) //  Indirect address write access
	{
					BYTE Slave;
					// @ 8a iaddr idata index data
					if( argc<6 ) {
						Printf("   --> Missing parameter !!!");
						return;
					}

					Slave = Asc2Bin(argv[1]);

					MonIndex = Asc2Bin(argv[2]);
					MonWdata = Asc2Bin(argv[4]);
					WriteI2C(Slave, MonIndex, MonWdata);

					MonIndex = Asc2Bin(argv[3]);
					MonWdata = Asc2Bin(argv[5]);
					WriteI2C(Slave, MonIndex, MonWdata);

					MonRdata = ReadI2C(Slave, MonIndex);

					Printf("\r\n<R>%2x[%2x]=%2x", (WORD)Slave, (WORD)MonIndex, (WORD)MonRdata);

	}
	*/    

	//---------------- Change I2C -----------------------
	else if( !stricmp( argv[0], "C" ) ) {
		MonAddress = Asc2Bin( argv[1] );
	}

	//---------------- Help -----------------------------
	else if( !stricmp( argv[0], "H" ) || !stricmp( argv[0], "HELP" ) || !stricmp( argv[0], "?" ) ) {
		MonHelp();

	}
	//---------------------------------------------------
	else if( !stricmp( argv[0], "*" ) ) {
			
				if( argc==1 ) {
					Printf("\r\n  * 0 : Program default Loader");
					Printf("\r\n  * 1 : Program external Loader");
					Printf("\r\n  * 2 : Execute Loader");
				}
				else { 
					BYTE mode;
					mode = Asc2Bin(argv[1]);
					//Loader(mode);
				}
	}

	//---------------------------------------------------
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
	else if( !stricmp( argv[0], "PCLK" ) ) {
		PclkAccess();			
	}
#endif	
	#ifdef Hs_debug	 //Pinchi 20150316 add
	//---------------------------------------------------
	else if( !stricmp( argv[0], "POWER" ) ) {
		LCDPower();
	}
	#endif
	//---------------------------------------------------
#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
	else if( !stricmp( argv[0], "M" ) ) {
		if( argc==2 ) {
			if( !stricmp( argv[1], "?" ) ) {
				BYTE i;
				Printf("\r\nCurrent Input:%d \r\n", (WORD)InputSelection);
				for(i=1; struct_InputSelection[i].Id!=0 ; i++)
						Printf("%s:%d  ",struct_InputSelection[i].Name,(WORD)struct_InputSelection[i].Id );
				Printf("\r\n");
			}
			else
				ChangeInput(Asc2Bin( argv[1] ));
		}
		else
			ChangeInput(GetNextInputSelection());
	}	
	//---------------------------------------------------
	else if( !stricmp( argv[0], "ACCESS" ) ) {
		if( argc==2 ) {
			AccessEnable = Asc2Bin(argv[1]);
		}
		Printf("\r\nTW88xx AUTO ACCESS = %d", (WORD)AccessEnable);
	}
	#if 0
	//---------------------------------------------------
	else if( !stricmp( argv[0], "AUTODETECT" ) ) {
		if( argc==2 ) {
			AutoDetect = Asc2Bin(argv[1]);
		}
		Printf("\r\nPC Auto Detect = %d", (WORD)AutoDetect);
	}	
	#endif
	//---------------------------------------------------
	else if( !stricmp( argv[0], "PCAUTO" ) ) {
		Puts("\r\nPC Auto Measurement");
		AutoAdjust();
	}	
	//---------------------------------------------------
	else if( !stricmp( argv[0], "PCCOLOR" ) ) {
		Puts("\r\nPC Color Auto Measurement");
		AutoColorAdjust();
	}	
	//---------------------------------------------------
	else if( !stricmp( argv[0], "7" ) ) {
		Puts("\r\nGet HPN / VPN");
		GetHpnVpn(DebugLevel);
	}	
#endif
	//---------------- Debug Level ---------------------
	else if ( !stricmp( argv[0], "DEBUG" ) ) {
		if( argc==2 ) {
			DebugLevel = Asc2Bin(argv[1]);
			SaveDebugLevelEE(DebugLevel);
		}
		Printf("\r\nDebug Level = %2x", (WORD)DebugLevel);
	}
	
	//---------------- Display on/off -------------------
	else if ( !stricmp( argv[0], "echo" ) ) {
		if( !stricmp( argv[1], "off" ) ) {
			echo = 0;
			Printf("\r\necho off");
		}
		else {
			echo = 1;
			Printf("\r\necho on");
		}
	}
	//---------------- RESET/ TEST / POWER_DOWN -------------------
	else if ( !stricmp( argv[0], "reset" ) ) {
		if( !stricmp( argv[1], "0" ) ) {
			P3_4 = 0;
			Printf("\r\nTW_reset_pin => 0");
		}
		else if( !stricmp( argv[1], "1" ) ) {
			P3_4 = 1;
			Printf("\r\nTW_reset_pin => 1");
		}
		else {
			Printf("\r\nTW_reset_pin = %d", (WORD)P3_4);
		}
	}
	else if ( !stricmp( argv[0], "test" ) ) {
		if( !stricmp( argv[1], "0" ) ) {
			//P0_7 = 0;
			Printf("\r\nTW_test_pin => 0");
		}
		else if( !stricmp( argv[1], "1" ) ) {
			//P0_7 = 1;
			Printf("\r\nTW_test_pin => 1");
		}
		else {
			Printf("\r\nTW_test_pin = %d", (WORD)P0_7);
		}
	}
	else if ( !stricmp( argv[0], "pdn" ) ) {
		if( !stricmp( argv[1], "0" ) ) {
			P3_7 = 0;
			Printf("\r\nTW_PowerDown_pin => 0");
		}
		else if( !stricmp( argv[1], "1" ) ) {
			P3_7 = 1;
			Printf("\r\nTW_PowerDown_pin => 1");
		}
		else {
			Printf("\r\nTW_PowerDown_pin = %d", (WORD)P3_7);
		}
	}
	//---------------- OSD test for parallel -----------------------------------
	else if( !stricmp( argv[0], "OSD" ) ) {
		if( !stricmp( argv[1], "logo" ) ) {
//			DisplayLogo();
		}
		else if( !stricmp( argv[1], "end" ) ) {
		  	Puts("\r\nIf you'd like to exit, press any Key....");
	 		while ( !RS_ready() ){
				P2 = ReadTW88( 0x95 );
			}
		}
		else if( !stricmp( argv[1], "input" ) ) {
			DisplayInput();
		}
		else if( !stricmp( argv[1], "off" ) ) {
			ShowOSDWindowAll(OFF);
		}
		//else if( !stricmp( argv[1], "grid" ) ) {
		//	DisplayGrid();
		//}
#if 0		
#ifndef BANKING
		else if( !stricmp( argv[1], "cone" ) ) {
			DisplayCone();
			DisplayJapanese();
		}
#endif		
#endif
		#ifdef BANKING
		else if( !stricmp( argv[1], "agrid" ) ) {
		  	BYTE i, j, k;
		  	Puts("\r\nIf you'd like to exit, press any Key....");
			j = 0;
			k = 0;
			DisplayMessage();
			if ( argc == 3 )
				i = Asc2Bin(argv[2]);
			else i = 0;
	 		while ( !RS_ready() ){
				if ( j < 9 )
					DisplayGridBank0(j);
				else
					DisplayGridBank1(j);
				if ( i )
					delay(10*i);
				if (k==0) {
					if (j==16) {
						k = 1;
						j--;
					}
					else j++;
				}
				else {
					if ( j==0 ) {
						k = 0;
						j++;
					}
					else j--;
				}
			}
		}
		else if( !stricmp( argv[1], "cgrid" ) ) {
		  	BYTE i, j, k;
		  	Puts("\r\nIf you'd like to exit, press any Key....");
			j = 0;
			k = 0;
			DisplayChinese();
			if ( argc == 3 )
				i = Asc2Bin(argv[2]);
			else i = 0;
	 		while ( !RS_ready() ){
				if ( j < 9 )
					DisplayGridBank0(j);
				else
					DisplayGridBank1(j);
				if ( i )
					delay(10*i);
				if (k==0) {
					if (j==16) {
						k = 1;
						j--;
					}
					else j++;
				}
				else {
					if ( j==0 ) {
						k = 0;
						j++;
					}
					else j--;
				}
			}
		}
		else if( !stricmp( argv[1], "jgrid" ) ) {
		  	BYTE i, j, k;
		  	Puts("\r\nIf you'd like to exit, press any Key....");
			j = 0;
			k = 0;
			DisplayJapanese();
			if ( argc == 3 )
				i = Asc2Bin(argv[2]);
			else i = 0;
	 		while ( !RS_ready() ){
				if ( j < 9 )
					DisplayGridBank0(j);
				else
					DisplayGridBank1(j);
				if ( i )
					delay(10*i);
				if (k==0) {
					if (j==16) {
						k = 1;
						j--;
					}
					else j++;
				}
				else {
					if ( j==0 ) {
						k = 0;
						j++;
					}
					else j--;
				}
			}
		}
		else if( !stricmp( argv[1], "kgrid" ) ) {
		  	BYTE i, j, k;
		  	Puts("\r\nIf you'd like to exit, press any Key....");
			j = 0;
			k = 0;
			DisplayKorean();
			if ( argc == 3 )
				i = Asc2Bin(argv[2]);
			else i = 0;
	 		while ( !RS_ready() ){
				if ( j < 9 )
					DisplayGridBank0(j);
				else
					DisplayGridBank1(j);
				if ( i )
					delay(10*i);
				if (k==0) {
					if (j==16) {
						k = 1;
						j--;
					}
					else j++;
				}
				else {
					if ( j==0 ) {
						k = 0;
						j++;
					}
					else j--;
				}
			}
		}
		#endif
	}
	
	//---------------- serial tx test with some number -----------------------------------
	else if( !stricmp( argv[0], "TX" ) ) {
		MonTxDump();
	}
	#ifdef Hs_debug	 //Pinchi 20150316 add
	//---------------- OSD FONTtest for parallel -----------------------------------
	else if( !stricmp( argv[0], "FONT" ) ) {
		if ( !stricmp( argv[1], "RAM" ) ) {
			DisplayRAMFont( Asc2Bin(argv[2]) );
		}
		else if ( !stricmp( argv[1], "ROM" ) ) {
			DisplayROMFont(Asc2Bin(argv[2]));
		}
		else {
			Puts("\r\n Font ROM # or Font RAM # for testing");
		}
	}
	#endif
	//---------------- Delta RGB Panel Test -------------------------
	#ifdef SUPPORT_DELTA_RGB

	else if( !stricmp( argv[0], "delta" ) ) {
		if( argc==1 )	DeltaRGBPanelInit();
		else {
			
			if( !stricmp( argv[1], "w" ) ) {

				WORD val;
				val= Asc2Bin(argv[3])<<8 | Asc2Bin(argv[4]);
				Printf("\r\n SPI Write: Addr:%2x  Data:%4x", (WORD)Asc2Bin(argv[2]), val);
				WriteSPI(Asc2Bin(argv[2]), val );
			}
			else if( !stricmp( argv[1], "r" ) ) {
				WORD val;
				val = ReadSPI(Asc2Bin(argv[2]));
				Printf("\r\n SPI Read: Addr:%2x  Data:%4x", (WORD)Asc2Bin(argv[2]), val);
			}
		}
	}
	#endif
	//----------------------------------------------------
	else {
		Printf("\r\nInvalid command...");
	}

	Prompt();

}

#endif
//-------------------------------------------------------------------------

#endif

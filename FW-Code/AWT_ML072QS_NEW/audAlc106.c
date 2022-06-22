//=========================================
//	FILE: AUDALC106.c
//	FUNCTION: REALTEK ALC106 AUDIO AMPLIFIER DRIVER
//														By Kane Ling Jul. 20, 2010
//=========================================

#include "Config.h"

#include "reg.h"
#include "typedefs.h"
#include "cpu.h"
#include "I2C.h"
#include "main.h"
#include "debug.h"
#include "printf.h"
#include "osdbasic.h"
#include "CPU.h"
#include "audAlc106.h"


//#define AUDIO_USE == ALC106
#ifdef ALC106

#define xDEBUG_ALC106
	
#define MAX_SOUND_VOLUME 50
Alc106VoulmeCtrlType	Alc106VolumCtrl;
Alc106MainCtrlType	Alc106MainCtrl;
//****************************************************
//	LOCAL FUNCTIONS
//****************************************************
#if 1
BOOL audAlc106_Write(BYTE Reg, BYTE* Data);
BOOL audAlc106_ReadWord(BYTE Reg, BYTE* Data);
#endif
//****************************************************
//	CODE START
//****************************************************
void audAlc106_Init(void)
{
	Alc106VolumCtrl.Mute_L = ALC106_MUTE_ON;
	Alc106VolumCtrl.Mute_R = ALC106_MUTE_ON;
	Alc106VolumCtrl.SpkVoulme_L = 0x1F;//same as audio mute
	Alc106VolumCtrl.SpkVoulme_R = 0x1F;//same as audio mute
	Alc106VolumCtrl.Resever1 = 0;
	Alc106VolumCtrl.Resever1 = 0;

	
	Alc106MainCtrl.RstOverCurrent  =1;
	Alc106MainCtrl.CorePower= 1;
	Alc106MainCtrl.OverCurrentProtect = TRUE;
	Alc106MainCtrl.OutPut_Select = OUT_BTL;
	Alc106MainCtrl.AutoPowerOff = FALSE;// TRUE;
	Alc106MainCtrl.Resever1 = 0;
	Alc106MainCtrl.Resever2 = 0;
	Alc106MainCtrl.Resever3 = 0;
	Alc106MainCtrl.OverCurrent_L = 0;
	Alc106MainCtrl.OverCurrent_R = 0;

	//audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);
	//audAlc106_Write(ALC106_MAIN_CTRL_REG, (BYTE *)&Alc106MainCtrl);
	#ifdef DEBUG_ALC106
	{
		//WORD Data=0;
		printf("\r\n>>>>Initial ALC106", 0);
		//	audAlc106_ReadWord(ALC106_VOLUME_CTRL_REG, (BYTE *) &Data);
		//Data = 0;
		//audAlc106_ReadWord(ALC106_MAIN_CTRL_REG, (BYTE *) &Data);
	}
	#endif

}
void audAlc106_VolumeAdj(BYTE volume)
{
	#ifdef DEBUG_ALC106
	BYTE Ext_Volume = volume ;
	#endif
	
	volume =volume + (0x1F-MAX_SOUND_VOLUME);//Kane @2010 0929 Ver0.13.03 add
	if(volume>=0x1F)
		volume=0x1F;
	
	//Ext_Volume = volume;
	Alc106VolumCtrl.SpkVoulme_L = volume;
	Alc106VolumCtrl.SpkVoulme_R = volume;
	audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);
	
	#ifdef DEBUG_ALC106
	{
		WORD Data = 0;
		printf("\r\n>>>>Ext_Volume=%d", Ext_Volume);
		audAlc106_ReadWord(ALC106_VOLUME_CTRL_REG, (BYTE *) &Data);
	}
	#endif
}

void audAlc106_SetMuteCtrl(BYTE mute)
{
		if(mute)
		{
			Alc106VolumCtrl.Mute_L = ALC106_MUTE_OFF;
			Alc106VolumCtrl.Mute_R = ALC106_MUTE_OFF;
		}
		else
		{
			Alc106VolumCtrl.Mute_L = ALC106_MUTE_ON;
			Alc106VolumCtrl.Mute_R = ALC106_MUTE_ON;
		}	
		audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);
		#ifdef DEBUG_ALC106
		{
			WORD Data = 0;
			printf("\r\n>>>>mute=%d", mute);
			audAlc106_ReadWord(ALC106_VOLUME_CTRL_REG, (BYTE *) &Data);
		}
		#endif
}

void audAlc106_PowerOn(void)
{
	Alc106MainCtrl.CorePower= 1;//Power up core
	audAlc106_Write(ALC106_MAIN_CTRL_REG, (BYTE *)&Alc106MainCtrl);
	Alc106VolumCtrl.Mute_L = ALC106_MUTE_ON;
	Alc106VolumCtrl.Mute_R = ALC106_MUTE_ON;
	Alc106VolumCtrl.SpkVoulme_L = 0x1E;//same as audio mute//Kane @2010 1110 Ver0.14.01 add for resolve pop noise
	Alc106VolumCtrl.SpkVoulme_R = 0x1E;//same as audio mute//Kane @2010 1110 Ver0.14.01 add for resolve pop noise
	audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);//Kane @2010 1110 Ver0.14.01 add for resolve pop noise
	#if 0
	audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);
	Delay1ms(50);
	Alc106VolumCtrl.Mute_L = ALC106_MUTE_OFF;
	Alc106VolumCtrl.Mute_R = ALC106_MUTE_OFF;
	audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);
	Delay1ms(50);
	Alc106VolumCtrl.SpkVoulme_L = Ext_Volume;
	Alc106VolumCtrl.SpkVoulme_R = Ext_Volume;
	audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);
	#endif
	#ifdef DEBUG_ALC106
	{
		WORD Data = 0;
		printf("\r\n>>>>audAlc106_PowerOn", 0);
		audAlc106_ReadWord(ALC106_VOLUME_CTRL_REG, (BYTE *) &Data);
		Data =0;
		audAlc106_ReadWord(ALC106_MAIN_CTRL_REG, (BYTE *) &Data);
	}
	#endif
 	Wait_ms(50);
}

void audAlc106_PowerOff(void)
{
	Alc106VolumCtrl.Mute_L = ALC106_MUTE_ON;
	Alc106VolumCtrl.Mute_R = ALC106_MUTE_ON;
	audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);
	Wait_ms(50);
	Alc106VolumCtrl.SpkVoulme_L = 0x1E;//same as audio mute
	Alc106VolumCtrl.SpkVoulme_R = 0x1E;//same as audio mute
	audAlc106_Write(ALC106_VOLUME_CTRL_REG, (BYTE *) &Alc106VolumCtrl);
	Wait_ms(50);
	
	Alc106MainCtrl.CorePower= 0;//Power down core
	audAlc106_Write(ALC106_MAIN_CTRL_REG, (BYTE *)&Alc106MainCtrl);
	#ifdef DEBUG_ALC106
	{
		WORD Data = 0;
		printf("\r\n>>>>audAlc106_Power OFF", 0);
		audAlc106_ReadWord(ALC106_VOLUME_CTRL_REG, (BYTE *) &Data);
		Data =0;
		audAlc106_ReadWord(ALC106_MAIN_CTRL_REG, (BYTE *) &Data);
	}
	#endif
}

#if 1
BOOL audAlc106_Write(BYTE index, BYTE* Data)
{
    BYTE ucDummy; // loop dummy

	//#if (TELI_MODEL ==	T15MUA)
	//return 1;
	//#endif//#if (TELI_MODEL ==	T15MUA)
    
	#ifdef DEBUG_ALC106
	WORD temp;
	temp = Data[0]& 0x00FF;
	temp <<=8;
	temp |=Data[1];
	printf("\r\n>>>>WriteReg[%d] = ", Reg);	
	printf("0x%x ",temp);	
	
	#endif

	BYTE addr;
	//BYTE dat1,dat2;

	//dat2=Data&0x00ff;
	//dat1=(Data>>8)&0x00ff;
		
	addr = (ALC106I2CAddress | (index>>7)) & 0xfe;

	I2CStart();
	I2CWriteData(addr);
	I2CWriteData((BYTE)addr);
	I2CWriteData(*(Data));
	dd();
	I2CWriteData(*Data+1);
	I2CStop();

	//#ifdef DEBUG_EEP
		Printf("Write %02xh to [Adrs(%02xh)Index(%02xh)\r\n", (WORD)dat, (WORD)addr, (WORD)index );
	//#endif

#if 0
	
	ucDummy = I2C_ACCESS_DUMMY_TIME;
    while(ucDummy--)
    {
		if (i2c_AccessStart(AUD_ALC106_ID, I2C_TRANS_WRITE) == FALSE)
		    continue;

		if(i2c_SendByte(Reg)== I2C_NON_ACKNOWLEDGE)  //Send Register
			continue;

		i2c_SendByte(*(Data)); // send high byte
		i2c_SendByte(*Data+1); // send low byte
		

        break;
    } // while

    i2c_Stop();
    Delay1ms(10);
	if(ucDummy == 0)
	{
		g_unErrorState=Sys_Error_HW2_Audio;//Kane @2010 1116 Ver0.14.02 add for external control
		return FALSE;
	}
	else
		return TRUE;

#endif	
}

BOOL audAlc106_ReadWord(BYTE Reg, BYTE* index)
{

	WORD val;
	BYTE addr;

	addr = (ALC106I2CAddress | (index>>7)) & 0xfe;

	val = ReadI2CWORD(addr,(BYTE)index);
	//#ifdef DEBUG_OSD
		Printf("Read [Adrs:%02xh,Index:%02xh] %xh\r\n", (WORD)addr, (WORD)index, (WORD)val);
	//#endif
	delay(2);
	return val;

#if 0
    BYTE ucDummy; // loop dummy
	//#if (TELI_MODEL ==	T15MUA)
	//return 1;
	//#endif//#if (TELI_MODEL ==	T15MUA
    ucDummy = I2C_ACCESS_DUMMY_TIME;
    while(ucDummy--)
    {
        if (i2c_AccessStart(AUD_ALC106_ID, I2C_TRANS_WRITE) == FALSE)
            continue;

         if(i2c_SendByte(Reg)== I2C_NON_ACKNOWLEDGE)  // //Send Register
			continue;
        if (i2c_AccessStart(AUD_ALC106_ID, I2C_TRANS_READ) == FALSE)
            continue;
				
		Data[0] = i2c_ReceiveByte(TRUE); // receive byte

		Data[1] = i2c_ReceiveByte(FALSE); // receive byte
		
        break;
    } // while
    i2c_Stop();
	#ifdef DEBUG_ALC106
	{
		WORD temp;
		temp = Data[0]& 0x00FF;
		temp <<=8;
		temp |=Data[1];
		printf("\r\n>>>>Read Reg[%d] = ", Reg);	
		printf("0x%x ",temp);	
	}
	#endif

		
	if(ucDummy == 0)
	{
		g_unErrorState=Sys_Error_HW2_Audio;//Kane @2010 1116 Ver0.14.02 add for external control
		return FALSE;
	}
	else
		return TRUE;
#endif
}
#endif
BYTE audAlc106_GetMuteCtrl(void)
{
	if( Alc106VolumCtrl.Mute_L == ALC106_MUTE_ON)
		return ALC106_MUTE_ON;
	else
		return ALC106_MUTE_OFF;
}

#endif//#if(AUDIO_USE == ALC106)

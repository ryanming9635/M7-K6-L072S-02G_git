//=========================================
//	FILE: AUDALC106.h
//	FUNCTION: REALTEK ALC106 AUDIO AMPLIFIER DRIVER
//														By Kane Ling Jul. 20, 2010
//=========================================
#ifndef __AUDALC106_H__
#define __AUDALC106_H__

//#define ALC106

//#if(AUDIO_USE == ALC106)
#ifdef ALC106

#define AUD_ALC106_ID	0x4A
#define ALC106_VOLUME_CTRL_REG	0x02
#define ALC106_MAIN_CTRL_REG	0x04

typedef struct Alc106VoulmeCtrlStruct
{
	UINT SpkVoulme_R	:5;//bit[0:4]
	UINT Resever1			:2;//bit[5:6]
	UINT Mute_R				:1;//bit 7
	UINT SpkVoulme_L	:5;//bit[8:12]
	UINT Resever2			:2;//bit[13:14]
	UINT Mute_L				:1;//bit 15
}Alc106VoulmeCtrlType;

typedef struct Alc106MainCtrlStruct
{
	UINT Resever1						:6;//bit[0:5]
	UINT OverCurrent_R			:1;//bit 6
	UINT OverCurrent_L			:1;//bit 7
	UINT RstOverCurrent			:1;//bit 8
	UINT Resever2						:1;//bit 9
	UINT AutoPowerOff				:1;//bit 10
	UINT OutPut_Select				:1;//bit 11
	UINT Resever3						:2;//bit[12:13]
	UINT OverCurrentProtect	:1;//bit 14
	UINT CorePower					:1;//bit 15
}Alc106MainCtrlType;

enum 
{
	ALC106_MUTE_OFF,
	ALC106_MUTE_ON
};//Alc106MuteType

enum 
{
	OUT_BTL,
	OUT_SINGLE
};//Alc106OutputSelectType

void audAlc106_Init(void);
void audAlc106_VolumeAdj(BYTE volume);
void audAlc106_SetMuteCtrl(BYTE mute);
BYTE audAlc106_GetMuteCtrl(void);
void audAlc106_PowerOn(void);
void audAlc106_PowerOff(void);

#endif//#if(AUDIO_USE == ALC106)	

#endif//__AUDALC106_H__


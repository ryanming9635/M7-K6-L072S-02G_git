
#define MAX_SOUND_VOLUME 50
extern  BYTE	AudioVol;
extern  BYTE	PCAudioVol;

//BYTE ResetMSP(void);
//void SetMSPSCARTPrescale(void);
//void SetMSPSourceSel(void);
//void SetMSPVol(void);

//BYTE AudioAutoStdDetection(void);
//BYTE SteroMonoDetection(void);

//BYTE TunerAudio(void);
//void ExtAudio(void);
//id PCAudio(void);
//id MuteOn(void);
//BYTE GetAudioVol(void);
BYTE ChangeVol(char);
//BYTE GetAudioBalance(void);
//BYTE ChangeBalance(char);
//BYTE GetAudioBass(void);
//BYTE ChangeBass(char);
//BYTE GetAudioTreble(void);
//BYTE ChangeTreble(char);
//BYTE GetAudioEffect(void);
//BYTE ChangeAudioEffect(char amount);
//void ToggleAudioMute(void);
//void CheckAndClearMuteOn(void);

//BYTE IsAudioMuteOn(void);
//void SetAudioMute(BYTE on );
//void ChangeMTS(BYTE type);
//void AudioOff(void);
void AudioMute(bit mute);
extern void    Wait_ms(WORD Tms);

//#define AudioOn()			SetMSPVol()
//void ResetAudioValue();

#ifndef __RGBMIX__
#define __RGBMIX__

#include "RegMap.h"

//#define	SetDigitalVideoContrastReg(vcval)				WriteTW88(0x3b, vcval)
//#define	SetDigitalVideoBrightnessReg(vbval)				WriteTW88(0x3c,	vbval )
//#define	SetDigitalVideoHueReg(vhval)					WriteTW88(0x32,	vhval )
//#define	SetDigitalVideoSaturationReg(gain, vhval)		WriteTW88(0x3d+gain, (ReadTW88(0x3d+gain)&0x80) + vhval )
#define	SetDigitalVideoContrastReg(vcval)				WriteI2C(DECODERADDRESS, SCONTRAST, vcval)
#define	SetDigitalVideoBrightnessReg(vbval)				WriteI2C(DECODERADDRESS, SBRIGHT,	vbval )
#define	SetDigitalVideoHueReg(vhval)					WriteI2C(DECODERADDRESS, SHUE,	vhval )
#define	SetDigitalVideoSaturationReg(gain, vhval)		WriteI2C(DECODERADDRESS, SCbGAIN+gain, (ReadI2C(DECODERADDRESS, SCbGAIN+gain)&0x80) + vhval )

#endif // __RGBMIX__
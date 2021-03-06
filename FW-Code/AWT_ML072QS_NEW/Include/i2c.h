#ifndef	__I2C_H__
#define	__I2C_H__


void I2CReadByte3(BYTE *);
void I2CRead8Byte(BYTE *);
#if 0
void I2CReadByteMSP(BYTE addr, BYTE index, BYTE *pd, BYTE cnt);
#endif
BYTE I2CWriteByte2(BYTE);
BYTE I2CWriteByte3(BYTE*);
BYTE I2CWrite8Byte(BYTE *);

void I2CStart(void);
void I2CWriteData(BYTE value);
BYTE I2CReadData(void);
#if 0
BYTE I2CReadDataWithACK(void);
#endif
void I2CStop(void);
void I2Cdelay(void);


#define WriteTW88(a,b)		WriteI2C(TW88I2CAddress, a, b)
#define ReadTW88(a)			ReadI2C(TW88I2CAddress, a)

BYTE WriteTW88_Wait	(BYTE, BYTE);
void WriteADC		(BYTE, BYTE);
BYTE ReadADC		(BYTE);
BYTE ReadADC_TW88(BYTE index);
void WriteADC_TW88(BYTE index, BYTE dat);

void WriteEEP		(WORD, BYTE);
BYTE ReadEEP		(WORD);
WORD ReadALC106(WORD index);
void WriteALC106(WORD index, WORD  dat);
WORD ReadI2CWORD(BYTE addr, BYTE index);
BYTE ReadI2C		(BYTE addr, BYTE index);
void WriteI2C		(BYTE addr, BYTE index, BYTE val);

void WriteI2Cn_(BYTE addr, BYTE *val, BYTE cnt);
void WriteI2Cn (BYTE addr, BYTE index, BYTE *val, BYTE cnt);
void WriteI2CnD(BYTE addr, BYTE index, BYTE val, BYTE cnt);

void ReadI2Cmn(BYTE addr, BYTE wcnt, BYTE rcnt, BYTE *rwdata);

#define		WriteADC(a,b)	WriteADC_TW88(a,b)
#define		ReadADC(a)		ReadADC_TW88(a)

#endif	/* __I2C_H__ */

/****************************************************************/
/*                      TW88xx RAM FONT                         */
/****************************************************************/
/* <FILE TYPE>=TW88xx */
/* <COLOR START>=0xff */

/* <IMAGE SIZE>=337x254 */

#define NofFonts 28
#define NofChars 28
/* <Look Up Table> */
code unsigned char JapaneseLUT[] = { 0x00, 0xE0, 0x1C, 0x03, 0xFC, 0x1F, 0xE3, 0xFF, 0x00, 0x80, 0x10, 0x02, 0x90, 0x12, 0x82, 0xDB };
/* <GRID INFORMATION> */
code int JapanesePos0[] = { 0, 218, 28, 1 };    // x, y, w, h
code char JapaneseColor0[] = { 0x04, };    // LUT no.s
/* <CHAR POSITION DATA> */
code unsigned char JapaneseChar[] = {
 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A
};
/* <FONT DATA> */
code unsigned char Japanese[][27] = {
#ifndef DEBUG
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x10,0x18,0x00,0x02,0x84,0x00,0x10,0x88,0x00,0x02,0x8B,0x00,0x00,0xB8,0x00,0x00,0x88,0x00,0x00,0x0B,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x42,0x80,0x12,0x69,0x80,0x00,0xB4,0xC4,0x70,0x7C,0x82,0x11,0x58,0x08,0x11,0xD2,0x80,0x21,0x00,0x06,0x04,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x11,0x0F,0x88,0x11,0x0F,0x88,0x11,0xF0,0x88,0x11,0x22,0x84,0x11,0xC1,0x80,0x83,0x00,0x04,0x07,0x0F,0x0C,0x00,0x00,0x00},
 {0x00,0x00,0x00,0xF0,0x30,0xF8,0x99,0x00,0x88,0xF9,0x07,0x2F,0x99,0x70,0xF2,0x99,0x20,0x22,0x0F,0x01,0x22,0x00,0x00,0x06,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x10,0x00,0x10,0x11,0x10,0xF1,0x19,0x00,0x11,0x91,0x00,0x11,0x11,0x10,0x1F,0x11,0x01,0xE1,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x24,0x00,0x00,0x01,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x22,0x00,0x0F,0x2F,0x00,0x40,0x8F,0x00,0x44,0x8F,0x00,0x44,0x8F,0x00,0x44,0x0F,0x00,0x07,0x0F,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x44,0x0F,0x18,0xE4,0x2E,0x00,0x45,0x2E,0x10,0xD6,0x2E,0x00,0x44,0x0E,0x00,0x44,0x0F,0x08,0x0D,0x00,0x00,0x00},
 {0x00,0x00,0x00,0xF1,0xE0,0x10,0x24,0x84,0x02,0x0F,0x0F,0x10,0xF2,0xF0,0x02,0xC4,0x44,0x00,0x32,0xC8,0x00,0x0C,0x03,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x18,0x42,0x80,0x84,0x69,0x80,0x88,0xB4,0xC4,0x8B,0x7C,0x82,0xB8,0x58,0x08,0x88,0xD2,0x80,0x0B,0x00,0x06,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x11,0x00,0x07,0x2F,0x0F,0x00,0x22,0x00,0x00,0x23,0x1F,0x00,0x44,0x11,0x10,0x08,0x11,0x02,0x00,0x0E,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x11,0x30,0x0D,0x2F,0x0C,0x00,0x43,0x58,0x10,0x18,0x4E,0x00,0x22,0x04,0x00,0x12,0xF0,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0xF0,0x70,0x00,0x22,0x15,0xC0,0x72,0xB2,0x00,0xC4,0xBE,0x00,0x44,0xBA,0x80,0x74,0xAA,0x00,0x00,0x03,0x00,0x00,0x00},
 {0x00,0x00,0x00,0xF8,0x80,0x0E,0x20,0x09,0x0F,0xF4,0x81,0x0E,0xF4,0x01,0x0E,0xF4,0x11,0x2E,0x44,0x11,0x22,0x0F,0x09,0x0E,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x07,0x9F,0x40,0x12,0x19,0x44,0x42,0x19,0x44,0x10,0x06,0x44,0x20,0x28,0x44,0xAA,0x51,0x12,0x0B,0x0C,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x2F,0x00,0x00,0x42,0x00,0x40,0x84,0x00,0x84,0x08,0xE1,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x3C,0x00,0x00,0x80,0x03,0x00,0x88,0x10,0x87,0xC8,0x11,0x78,0x0A,0x22,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x44,0x11,0x44,0x74,0x80,0x80,0x8C,0x44,0x24,0x08,0x44,0x22,0x00,0x84,0x00,0x34,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x01,0x3C,0x00,0x20,0x00,0x00,0x22,0xF0,0x80,0x47,0x00,0x24,0x00,0x00,0x22,0x00,0xF0,0x84,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x01,0xA3,0x2F,0x00,0x01,0x2F,0x30,0x91,0x2F,0x00,0x99,0x2F,0x00,0x89,0x2F,0x10,0x49,0x2F,0x02,0x03,0x0F,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x2E,0x71,0xC0,0x0C,0x71,0xC0,0x4C,0x75,0xD4,0x4C,0x75,0xC4,0x0C,0x71,0xC0,0x0C,0x11,0x00,0x0E,0x01,0x03,0x00,0x00,0x00},
 {0x00,0x00,0x00,0xF0,0x90,0x00,0x00,0x11,0x00,0xF0,0xD1,0x00,0x44,0x11,0x00,0x84,0x91,0x00,0xB8,0x48,0x78,0x0C,0x04,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x03,0x0C,0x00,0x00,0x21,0x10,0x00,0x22,0x21,0x00,0x22,0x84,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0xF0,0xC0,0x70,0x84,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0xF0,0xF0,0xC0,0x11,0x00,0x01,0x11,0x68,0x00,0x11,0x01,0x00,0x11,0x00,0x11,0x11,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x88,0x20,0x0F,0x4F,0x2A,0x00,0x24,0x22,0x87,0x3E,0x22,0x00,0x01,0x12,0x78,0xC0,0x01,0x00,0x00,0x00,0x00,0x00,0x00},
#endif
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x11,0x00,0x00,0x00,0x88,0x40,0x00,0x88,0x84,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
};
/* <DISPLAY DATA> */
code unsigned char JapaneseDisplay[] = {

 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x00
};
/* <STRUCTURE DATA> */
struct MultiGridInfo
{
	unsigned char	NFonts;
	unsigned char	NChars;
	unsigned char	*LUT;
	unsigned char	NofWindows;
	unsigned int	*WPos0;
	unsigned char	*WColors0;
	unsigned int	*WPos1;
	unsigned char	*WColors1;
	unsigned int	*WPos2;
	unsigned char	*WColors2;
	unsigned int	*WPos3;
	unsigned char	*WColors3;
	unsigned char	*CharPos;
	unsigned char	*FontData;
	unsigned char	*DisplayData;
};
/* <INFORMATION DATA> */
code struct MultiGridInfo Japanese_Info = {
        28,           // No of Fonts
        28,           // No of Chars
        JapaneseLUT,        // Color LUT
        1,           // No of Windows
        JapanesePos0,      // Windows 0 Pos
        JapaneseColor0,    // Windows 0 Color
        0,            // Window 1 Pos
        0,            // Windows 1 Color
        0,            // Window 2 Pos
        0,            // Windows 2 Color
        0,            // Window 3 Pos
        0,            // Windows 3 Color
        JapaneseChar,       // Char Position data
        Japanese,           // Font data
        JapaneseDisplay,    // Display data

};

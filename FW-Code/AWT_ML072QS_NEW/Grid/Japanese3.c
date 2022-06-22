/****************************************************************/
/*                      TW88xx RAM FONT                         */
/****************************************************************/
/* <FILE TYPE>=TW88xx */
/* <COLOR START>=0xff */

/* <IMAGE SIZE>=320x240 */

#define NofFonts 27
#define NofChars 52
/* <Look Up Table> */
code unsigned char JapaneseLUT[] = { 0x00, 0xE0, 0x1C, 0x03, 0xFC, 0x1F, 0xE3, 0xFF, 0x00, 0x80, 0x10, 0x02, 0x90, 0x12, 0x82, 0xDB };
/* <GRID INFORMATION> */
code int JapanesePos[] = {  3, 220, 26, 2 };    // x, y, w, h
code char JapaneseColor[] = { 0x01, 0x01, };    // LUT no.s
/* <CHAR POSITION DATA> */
code unsigned char JapaneseChar[] = {
 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19
};
/* <FONT DATA> */
code unsigned char Japanese[][27] = {
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x00,0x01,0x6B,0x00,0x10,0xCD,0x00,0x00,0xCC,0x00,0x00,0xCD,0x00,0x00,0x0D,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x63,0xC0,0x13,0x3F,0xC8,0x00,0x6F,0x0E,0x17,0xE7,0xCC,0x11,0x3F,0x88,0x31,0x0E,0x0E,0x06,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xB3,0x3F,0x10,0x33,0x3F,0x11,0xBB,0x6F,0x11,0xBB,0xB7,0x19,0xCF,0x01,0x09,0x07,0x0F,0x08,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF3,0xC0,0xFE,0xF3,0xE0,0xEE,0x00,0xCC,0xEF,0xCF,0xCE,0x0E,0x06,0xCC,0x00,0x01,0x0C,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0xCC,0xCC,0x0F,0xCF,0xCC,0x00,0xCC,0xCC,0x70,0xCC,0xCC,0xCC,0xFE,0x0C,0x07,0x08,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x80,0x00,0x00,0x0C,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x70,0xF3,0xF0,0x00,0xF3,0xE0,0x66,0xFC,0xE6,0x66,0xCC,0x66,0x66,0x0F,0x0E,0x07,0x0F,0x0F,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x66,0xF3,0x01,0x6F,0x66,0x00,0x76,0x3F,0x01,0x6F,0x6F,0x00,0x66,0x3E,0x08,0x0E,0x0E,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x31,0x18,0xCC,0x16,0x8F,0x0E,0x73,0x17,0xCE,0x33,0x31,0xCC,0x33,0x07,0x06,0x03,0x07,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xBC,0x00,0x00,0xFE,0x01,0x1F,0x8F,0x08,0x11,0xBF,0x00,0x31,0xEE,0x00,0x63,0x0B,0x08,0x0C,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0x00,0x00,0x8F,0x0E,0x1F,0xF8,0x80,0x63,0x19,0x88,0x1C,0x11,0x88,0x33,0x07,0x00,0x01,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xDC,0xC0,0xF0,0x8F,0x00,0x66,0x7F,0x0C,0xF7,0xBF,0x00,0x77,0x00,0x00,0x77,0x0F,0x0C,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xF1,0xF8,0x03,0x3D,0x6B,0x03,0xEF,0xCF,0x03,0xEF,0xCF,0x03,0xEF,0xCF,0x33,0x07,0x0F,0x03,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xCF,0xDC,0x0D,0xEC,0xDD,0x3D,0x38,0x9D,0x0C,0x60,0x11,0xFC,0xFC,0xCD,0x0F,0x0F,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x88,0x00,0x03,0x88,0x00,0x11,0x88,0x30,0x31,0xC8,0x63,0x03,0x07,0x0C,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0x00,0x00,0xCF,0x17,0x81,0x88,0x66,0x00,0x38,0xE6,0x00,0x66,0x77,0x90,0x03,0x0C,0x01,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x33,0xCC,0x6F,0x7C,0x80,0x66,0x66,0x6C,0xCC,0x66,0x66,0xBC,0xC6,0x00,0x09,0x0C,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x3E,0x80,0x33,0x00,0x00,0x33,0x8F,0xC8,0x67,0x00,0x66,0x00,0x00,0xC6,0x00,0x0F,0x08,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x13,0xE7,0xDF,0x00,0x33,0xFF,0x17,0xBB,0xFF,0x11,0x8B,0xCF,0x31,0xCF,0xCF,0x06,0x07,0x0F,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x98,0xF6,0xF0,0x10,0xF6,0x80,0x11,0xFF,0x9F,0x11,0xFF,0xB9,0x18,0xF6,0xE3,0x08,0x06,0x07,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xC0,0x00,0x00,0xCC,0x00,0x8E,0xCC,0x00,0x08,0xCC,0x10,0xEC,0x6C,0x31,0x0E,0x03,0x0E,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xF0,0x01,0x0F,0xC6,0x00,0x11,0x88,0x80,0x11,0x88,0x08,0x01,0xC8,0x00,0x00,0x07,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x07,0x3F,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x08,0x00,0x03,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x08,0x11,0x00,0x03,0x1F,0x7C,0x00,0xF0,0x00,0x31,0x08,0x00,0x13,0x80,0x00,0x00,0x0F,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x88,0x60,0x00,0x8E,0x66,0x00,0xCC,0x66,0x00,0x6E,0x66,0x00,0x00,0x33,0xCC,0x0C,0x01,0x08,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
};
/* <DISPLAY DATA> */
code unsigned char JapaneseDisplay[] = {

 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00
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
        27,           // No of Fonts
        52,           // No of Chars
        JapaneseLUT,        // Color LUT
        1,           // No of Windows
        JapanesePos,            // Window 0 Pos
        JapaneseColor,            // Windows 0 Color
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

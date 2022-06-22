/****************************************************************/
/*                      TW88xx RAM FONT                         */
/****************************************************************/
/* <FILE TYPE>=TW88xx */
/* <COLOR START>=0xff */

/* <IMAGE SIZE>=320x239 */

#define NofFonts 25
#define NofChars 28
/* <Look Up Table> */
code unsigned char ChineseLUT[] = { 0x00, 0xE0, 0x1C, 0x03, 0xFC, 0x1F, 0xE3, 0xFF, 0x00, 0x80, 0x10, 0x02, 0x90, 0x12, 0x82, 0xDB };
/* <GRID INFORMATION> */
code int ChinesePos0[] = { 81, 210, 14, 2 };    // x, y, w, h
code char ChineseColor0[] = { 0x01, 0x01, };    // LUT no.s
/* <CHAR POSITION DATA> */
code unsigned char ChineseChar[] = {
 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0F, 0x10, 0x11, 0x12,
 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A
};
/* <FONT DATA> */
code unsigned char Chinese[][27] = {
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x17,0x8F,0x00,0x11,0x88,0x00,0x31,0x08,0x00,0x33,0xF9,0x00,0x73,0x99,0x00,0x77,0x99},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCF,0xC0,0x19,0x9F,0x8E,0x73,0xF1,0xF9,0x3F,0x33,0x11,0xFB,0xF3,0xF1,0xBB,0x33,0x11,0xBB,0x0F,0x1F},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x80,0x00,0x00,0xCC,0xC8,0x00,0xC0,0x88,0x0F,0xCE,0x88,0x00,0xCC,0x88,0x00,0xCC,0x88,0x00,0xFC},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCE,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x11,0xCC,0x00,0x11,0xCC,0x00,0x31,0x6E,0x00,0x33,0x33,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x67,0x0F,0x00,0x66,0x00,0x00,0x67,0x0F,0x00,0x66,0x00,0x00,0x66,0xCF,0x00,0x66,0xCC},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x30,0xF3,0x00,0x0E,0x00,0x00,0x00,0x00,0xC0,0x0F,0x0F,0x0E,0x00,0x00,0x00,0x0F,0x1F,0x8C,0x00,0x11,0x88},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x30,0xF0,0xF1,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x63,0x00,0x00,0x66,0x00,0x00,0xC6},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x8C,0x00,0x00,0xF8,0xF1,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x6F,0x00,0x00,0x66,0x00,0x00,0x66,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x10,0xF0,0xF3,0x73,0x00,0x67,0x00,0x00,0xC6,0x07,0x1F,0x8F,0x00,0x31,0x08,0x00,0x77,0xC0},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0xF0,0xF3,0x80,0x00,0x06,0x00,0x00,0x30,0x80,0x3F,0x0F,0x0C,0x63,0x00,0x00,0xC6,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xF0,0xE0,0x00,0x10,0x9F,0x00,0x63,0x08,0x10,0x8C,0x00,0xC7,0x0F,0x6F,0x00,0x00,0x66,0x01,0x0F,0x6F},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x6C,0x00,0x00,0x73,0xE8,0x00,0x0F,0x06,0x00,0x30,0x00,0x00,0x0F,0x08,0x00},
 {0x00,0x11,0x99,0x00,0x11,0xF9,0x00,0x01,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xEB,0x00,0x11,0xEE,0x00,0xF1,0x0C,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x88,0x00,0xEE,0x88,0x00,0xDC,0x08,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xC6,0x11,0x88,0x8C,0x00,0xEC,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0xCC,0xCC,0x10,0x8C,0xFC,0x01,0x08,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x11,0x88,0xF0,0xF1,0x88,0x00,0x01,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x11,0x8C,0x00,0x63,0x10,0x01,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x66,0x00,0xD0,0xCE,0x00,0x07,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x37,0x00,0x10,0xC6,0x03,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xEC,0x00,0x00,0x03,0xE8,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x66,0x00,0x00,0x66,0x07,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0xC0,0x00,0x0F,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
};
/* <DISPLAY DATA> */
code unsigned char ChineseDisplay[] = {

 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x00, 0x00, 0x0D,
 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x00
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
code struct MultiGridInfo Chinese_Info = {
        25,           // No of Fonts
        28,           // No of Chars
        ChineseLUT,        // Color LUT
        1,           // No of Windows
        ChinesePos0,      // Windows 0 Pos
        ChineseColor0,    // Windows 0 Color
        0,            // Window 1 Pos
        0,            // Windows 1 Color
        0,            // Window 2 Pos
        0,            // Windows 2 Color
        0,            // Window 3 Pos
        0,            // Windows 3 Color
        ChineseChar,       // Char Position data
        Chinese,           // Font data
        ChineseDisplay,    // Display data

};

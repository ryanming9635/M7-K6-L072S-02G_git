/****************************************************************/
/*                      TW88xx RAM FONT                         */
/****************************************************************/
/* <FILE TYPE>=TW88xx */
/* <COLOR START>=0xff */

/* <IMAGE SIZE>=320x240 */

#define NofFonts 77
#define NofChars 165
/* <Look Up Table> */
code unsigned char GMULTI_RR4LUT[] = { 0x00, 0xE0, 0x1C, 0x03, 0xFC, 0x1F, 0xE3, 0xFF, 0x00, 0x80, 0x10, 0x02, 0x90, 0x12, 0x82, 0xDB };
/* <GRID INFORMATION> */
code int GMULTI_RR4Pos0[] = { 89, 44, 15, 4 };    // x, y, w, h
code char GMULTI_RR4Color0[] = { 0x04, 0x04, 0x04, 0x04, };    // LUT no.s
code int GMULTI_RR4Pos1[] = { 38, 115, 21, 5 };    // x, y, w, h
code char GMULTI_RR4Color1[] = { 0x04, 0x04, 0x04, 0x04, 0x04, };    // LUT no.s
/* <CHAR POSITION DATA> */
code unsigned char GMULTI_RR4Char[] = {
 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x12, 0x13, 0x14, 0x16, 0x17, 0x18, 0x19,
 0x1A, 0x1B, 0x1C, 0x1F, 0x20, 0x21, 0x2B, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3F, 0x40, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x53,
 0x54, 0x63, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
 0x75, 0x76, 0x77, 0x78, 0x79, 0x7B, 0x7C, 0x8D, 0x8E, 0x90, 0xA3, 0xA4
};
/* <FONT DATA> */
code unsigned char GMULTI_RR4[][27] = {
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x00,0x10,0xFF},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF3,0x00,0xF3,0xEF,0x73,0xEF,0x08,0xEF,0x08,0x00,0x0C,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x10,0x80,0x10,0xF7,0x8C,0xF3,0xCF,0x00,0xEF,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x77,0xFF,0x00,0x33,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF0,0xF0,0xFF,0xFF,0xFF,0x03,0x0F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xC0,0x00,0xFF,0xFF,0xFF,0x0F,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xF0,0xF0,0xFF,0xFF,0xFF,0x07,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x88,0x10,0xEE,0x00,0x11,0xCC,0x00,0x11,0xCC,0x00,0x33,0x8C},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0xF3,0x00,0x31,0xEF},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x71,0x00,0x10,0xFF,0x00,0xF7,0x8C,0x71,0xCF,0x00,0xFF,0x08,0x00,0x8C,0x00,0x00,0x00,0x00,0x00},
 {0x00,0xF7,0x8E,0xF3,0xCF,0x00,0xEF,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xF6,0xF0,0xF0,0x7F,0xFF,0xFF,0x07,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xF0,0x00,0x00,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0xFF,0xF8,0xF0,0xFF,0xFF,0xFF,0x01,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0xF0,0xE0,0x00,0xFF,0xFF,0xFF,0x0F,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0x00,0x03,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xC0,0xFF,0xFF,0xEE,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x33,0x88,0x00,0x73,0x88,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0xF7,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0xF7,0x00,0x31,0xCF,0x00,0xF7,0x08,0x31,0xCE,0x00,0xF7,0x08,0x00,0xCE,0x00,0x00},
 {0x10,0xFF,0x08,0x73,0x8E,0x00,0xEF,0x00,0x00,0x8C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x00,0x00,0xF7,0x00,0x11,0xCE,0x00,0x73,0x8C},
 {0x00,0x10,0xFF,0x00,0x73,0x8E,0x00,0xF7,0x00,0x31,0xCE,0x00,0xF7,0x08,0x00,0xCE,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x80,0x00,0x33,0xFF,0xFF,0x11,0xFF,0xFF,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0x00,0x00,0x07},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0x0F,0x0F,0x0F},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xC0,0x00,0xFF,0xFF,0xFF,0x0F,0xFF,0xFF},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xE0,0x00,0xFF,0xFF,0x00},
 {0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xEE,0x00,0x00,0xFE,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x73,0x00,0x10,0xEF,0x00,0x31,0xCC},
 {0x00,0x10,0xEF,0x00,0x73,0x8C,0x10,0xEF,0x00,0x33,0x8C,0x00,0xF7,0x08,0x00,0xCE,0x00,0x00,0x8C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x01,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x7F,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xFF,0xFF,0xCE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0xFE,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x13,0x00,0x00,0x11,0x00,0x00,0x11},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xEC,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x00,0x00,0x77,0x00,0x00,0xEF,0x00,0x31,0xCE,0x00,0x73,0x88},
 {0x00,0xF7,0x08,0x10,0xEE,0x00,0x73,0x8C,0x00,0xF7,0x00,0x00,0xCE,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xEE,0x00,0x00,0xFE,0x00,0x00,0x77,0x00,0x00,0x77,0x80,0x00,0x33,0x88,0x00,0x33,0xC8,0x00,0x11,0xCC,0x00,0x01,0xEE,0x00,0x00,0xFE,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x73,0x00,0x00,0xF7,0x00,0x11,0xCE,0x00,0x73,0x8C},
 {0x00,0xEF,0x00,0x31,0xCE,0x00,0x73,0x88,0x00,0xEF,0x00,0x00,0xCE,0x00,0x00,0x8C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x33,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x80,0x60,0x10,0xCC,0xFF,0x33,0x08,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x80,0x60,0x00,0xCC,0xFF,0x31,0x08,0x06,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xC8,0xF6,0x31,0x8C,0x6F,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xC8,0xF6,0x10,0x8C,0x6F,0x33,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x10,0xCC,0xFF,0x33,0x08,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x10,0xCC,0xFF,0x33,0x08,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0xCC,0xF6,0x31,0x08,0x6F,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC8,0xF6,0x31,0x8C,0x6F,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC8,0xF6,0x31,0x8C,0x6F,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC8,0xF6,0x31,0x8C,0x6F,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC8,0x60,0x10,0x8C,0xFF,0x33,0x00,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x10,0xCC,0xFF,0x33,0x08,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x10,0xCC,0xFF,0x33,0x08,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0xCC,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x77,0x00,0x00,0x37,0x88,0x00,0x33,0xC8,0x00,0x11,0xCC,0x00,0x11,0xEE,0x00,0x11,0xFE,0x00,0x00,0xFF,0x00,0x00,0x77,0x00,0x00,0x33},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x88,0x00,0x00,0xCC,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x33,0x00,0x00,0x77,0x00,0x00,0xEF},
 {0x00,0xF7,0x00,0x10,0xEE,0x00,0x31,0xCC,0x00,0x73,0x88,0x00,0xEF,0x00,0x00,0xCE,0x00,0x00,0x8C,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0xEE,0x00,0x00,0xFF,0x00,0x00,0x77,0x80,0x00,0x33,0xC8,0x00,0x13,0xCC,0x00,0x01,0xEE,0x00,0x00,0x7F,0x00,0x00,0x37,0x88,0x00,0x13,0xCC},
 {0x00,0x11,0xCE,0x00,0x33,0x8C,0x00,0xF7,0x08,0x10,0xEE,0x00,0x31,0xCC,0x00,0x73,0x88,0x00,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x01,0xEE,0x00,0x00,0x7F,0x00,0x00,0x37,0x00,0x00,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
 {0x00,0x00,0x00,0x00,0x00,0x00,0xC8,0x00,0x00,0xEC,0x00,0x00,0xFE,0x00,0x00,0x77,0x80,0x00,0x33,0xC8,0x00,0x11,0xEC,0x00,0x00,0x4E,0x00},
};
/* <DISPLAY DATA> */
code unsigned char GMULTI_RR4Display[] = {

 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x00,
 0x00, 0x00, 0x0A, 0x0B, 0x0C, 0x00, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x00, 0x00, 0x14,
 0x15, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x18, 0x19, 0x1A,
 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x26,
 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x00,
 0x00, 0x00, 0x00, 0x30, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x00, 0x46, 0x47, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x49, 0x00,
 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x4B, 0x4C
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
code struct MultiGridInfo GMULTI_RR4_Info = {
        77,           // No of Fonts
        165,           // No of Chars
        GMULTI_RR4LUT,        // Color LUT
        2,           // No of Windows
        GMULTI_RR4Pos0,      // Windows 0 Pos
        GMULTI_RR4Color0,    // Windows 0 Color
        GMULTI_RR4Pos1,      // Windows 1 Pos
        GMULTI_RR4Color1,    // Windows 1 Color
        0,            // Window 2 Pos
        0,            // Windows 2 Color
        0,            // Window 3 Pos
        0,            // Windows 3 Color
        GMULTI_RR4Char,       // Char Position data
        GMULTI_RR4,           // Font data
        GMULTI_RR4Display,    // Display data

};

/****************************************************************/
/*                      TW88xx RAM FONT                         */
/****************************************************************/
/* <FILE TYPE>=TW8804 */
/* <NUMBER OF FONTS>=0xC6(198) */
/* <COLOR START>=0x60 */

/* <LOOK-UP TABLE> */
code unsigned char OSD_Color_LookUp_Data_Table[][8] = {
     {0x92,0x2F,0x9C,0x06,0xE8,0x37,0xF8,0xFF},
     {0xBB,0x2F,0x08,0x92,0x01,0x49,0x37,0xDB}
};

/* <FONT DATA> */
code unsigned char RAMFONTDATA[][27] = {
    /*0x00(  0)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x01(  1)*/ {0x00,0x00,0x33,0x00,0x00,0xCF,0x00,0x30,0xCC,0x00,0x33,0x00,0x00,0xCF,0x00,0x30,0xCC,0x00,0x33,0x00,0x00,0xFF,0xF0,0xF0,0xCC,0x00,0x00},
    /*0x02(  2)*/ {0xCC,0x00,0x00,0x3F,0x00,0x00,0x33,0xC0,0x00,0x00,0xCC,0x00,0x00,0x3F,0x00,0x00,0x33,0xC0,0x00,0x00,0xCC,0xF0,0xF0,0xFF,0x00,0x00,0x33},
    /*0x03(  3)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0x00,0x00,0x00},
    /*0x04(  4)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x20,0x20,0x13,0x32,0x62,0x11,0x23,0xAE,0x31,0xA2,0x2A},
    /*0x05(  5)*/ {0x00,0x00,0x33,0x00,0x00,0xCF,0x00,0x30,0xCC,0x00,0x33,0x00,0x00,0xCF,0x00,0x30,0xCC,0x00,0x33,0x00,0x00,0xFF,0x00,0x00,0xCC,0x00,0x00},
    /*0x06(  6)*/ {0xCC,0x00,0x00,0x3F,0x00,0x00,0x33,0xC0,0x00,0x00,0xCC,0x00,0x00,0x3F,0x00,0x00,0x33,0xC0,0x00,0x00,0xCC,0x00,0x00,0xFF,0x00,0x00,0x33},
    /*0x07(  7)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0xFF,0xC0,0x67,0x00,0xCC,0x66,0x00,0xCC,0x76,0x30,0xEC,0x13,0xC9,0x8C,0x00,0x00,0x00},
    /*0x08(  8)*/ {0x00,0x00,0x10,0x01,0x0F,0x0F,0x00,0x11,0x0F,0x00,0x11,0xF0,0x00,0x71,0xF0,0x10,0x88,0x40,0x01,0x00,0x84,0x00,0x10,0x08,0x00,0xC2,0x00},
    /*0x09(  9)*/ {0x80,0x20,0x00,0x0F,0x0F,0x00,0x1F,0x08,0x00,0xF1,0x00,0x00,0xF1,0xE0,0x00,0xC0,0x44,0x00,0x88,0x00,0x00,0x88,0x22,0x00,0x3C,0xE3,0x00},
    /*0x0A( 10)*/ {0x00,0x00,0x00,0x00,0x47,0x0F,0x00,0x44,0x23,0x00,0x47,0x2F,0x00,0x44,0x23,0x00,0x44,0xF0,0x00,0x44,0x12,0x00,0x88,0x00,0x10,0x18,0xE1},
    /*0x0B( 11)*/ {0x44,0x10,0x80,0x0F,0x0F,0x08,0x00,0x9C,0x00,0x0F,0x8F,0x08,0x0F,0x88,0x00,0xF0,0xE0,0x00,0x00,0x8C,0x00,0x7D,0x00,0x00,0x08,0x1E,0x00},
    /*0x0C( 12)*/ {0x10,0x30,0x80,0x00,0xAA,0xA9,0x10,0xF2,0xFC,0x00,0x48,0x42,0x10,0xF4,0xF4,0x00,0x11,0x20,0x00,0x1F,0x0F,0x00,0x11,0x60,0x11,0x0F,0x08},
    /*0x0D( 13)*/ {0x00,0x60,0x00,0x00,0x44,0x00,0x80,0x54,0x00,0x0F,0x4F,0x08,0x40,0x44,0x00,0x22,0x44,0x00,0x00,0x44,0x00,0x00,0x44,0x00,0x07,0x8C,0x00},
    /*0x0E( 14)*/ {0x00,0xC0,0x00,0x00,0x88,0x00,0x00,0x88,0x40,0x00,0x8F,0x0E,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,0xE0,0x10,0xCB,0x00},
    /*0x0F( 15)*/ {0x80,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x8F,0x0E,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,0x11,0x00,0xF8,0xF1,0x00},
    /*0x10( 16)*/ {0x00,0x40,0x30,0x00,0x02,0x22,0x01,0xC0,0x32,0x00,0x04,0x23,0x10,0xE0,0x22,0x00,0x44,0x44,0x00,0x44,0x94,0x00,0x97,0x06,0x01,0x00,0x1E},
    /*0x11( 17)*/ {0xF0,0xF2,0x00,0x00,0x00,0x00,0xF0,0xE0,0x00,0x80,0x44,0x00,0x48,0x88,0x00,0x33,0x00,0x00,0x85,0x68,0x00,0x00,0x02,0x00,0xF0,0xF3,0x00},
    /*0x12( 18)*/ {0x00,0x00,0x00,0x00,0xF0,0xF0,0x00,0x88,0x00,0x00,0x88,0xF0,0x00,0x88,0x88,0x00,0x88,0x88,0x00,0x88,0x8F,0x00,0x88,0x00,0x00,0x8F,0x0F},
    /*0x13( 19)*/ {0x00,0x00,0x00,0xF0,0xF2,0x00,0x00,0x22,0x00,0xE2,0x22,0x00,0x22,0x22,0x00,0x22,0x22,0x00,0x2E,0x22,0x00,0x00,0x22,0x00,0x0F,0x2E,0x00},
    /*0x14( 20)*/ {0x10,0xF1,0xB0,0x00,0x00,0xA2,0x01,0x0F,0x2A,0x10,0xF1,0xB2,0x10,0xF1,0xA2,0x00,0x10,0x22,0x11,0x1F,0x22,0x11,0x11,0x44,0x11,0x0F,0x84},
    /*0x15( 21)*/ {0xF0,0xF0,0x00,0x20,0x11,0x00,0x2F,0x1D,0x00,0xF2,0xD5,0x00,0x00,0x91,0x00,0x47,0x99,0x00,0x74,0x99,0x00,0x04,0x19,0x00,0x01,0x2F,0x00},
    /*0x16( 22)*/ {0x00,0x00,0xD0,0x00,0x0F,0x8F,0x00,0x47,0x9F,0x00,0x74,0xF9,0x00,0x21,0x9E,0x00,0x7C,0xF8,0x00,0x00,0xC0,0x00,0x00,0x88,0x00,0xF0,0xF8},
    /*0x17( 23)*/ {0x10,0x80,0x00,0x39,0xF1,0x80,0xE2,0x22,0x00,0x11,0x44,0x00,0x30,0x3C,0x00,0xFC,0xF3,0x00,0x88,0x40,0x00,0x8F,0x0E,0x00,0xF8,0xF0,0x88},
    /*0x18( 24)*/ {0x10,0xF0,0xC0,0x11,0xF0,0xC4,0x11,0xF0,0xC4,0x11,0x00,0x04,0x11,0x03,0x4F,0x11,0x70,0xF4,0x11,0x00,0x44,0x11,0x10,0x08,0x11,0x02,0x00},
    /*0x19( 25)*/ {0xF0,0xF0,0x00,0xF8,0xE2,0x00,0xF8,0xE2,0x00,0x18,0x22,0x00,0x8F,0x2A,0x00,0xF9,0xA2,0x00,0x88,0x22,0x00,0x88,0x22,0x00,0x09,0x4E,0x00},
    /*0x1A( 26)*/ {0x10,0xF0,0xC0,0x11,0xF0,0xC4,0x11,0xF0,0xC4,0x11,0x00,0x88,0x11,0x13,0x86,0x11,0x61,0xF2,0x11,0x11,0x2A,0x11,0x11,0x4C,0x11,0x30,0x08},
    /*0x1B( 27)*/ {0xF0,0xF0,0x00,0xF8,0xE2,0x00,0xF8,0xE2,0x00,0x44,0x22,0x00,0x69,0x2A,0x00,0xF4,0xAA,0x00,0x9D,0x2A,0x00,0x9F,0x22,0x00,0x88,0x2E,0x00},
    /*0x1C( 28)*/ {0x10,0xF0,0xF0,0x11,0x00,0x55,0x01,0x8F,0x0D,0x00,0x47,0x2F,0x00,0x47,0x2F,0x00,0x74,0xF2,0x00,0x04,0x22,0x03,0x0F,0x2F,0x00,0x00,0x22},
    /*0x1D( 29)*/ {0xF0,0xE0,0x00,0x00,0x44,0x00,0x0F,0x8C,0x00,0x0F,0x8C,0x00,0x0F,0x88,0x00,0xF0,0x88,0x00,0x00,0x68,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00},
    /*0x1E( 30)*/ {0x00,0x00,0x11,0x10,0xF7,0xFF,0x00,0x70,0xF1,0x00,0x70,0xF1,0x10,0xF0,0xF1,0x00,0x70,0xF0,0x00,0x74,0xF1,0x00,0x74,0xF1,0x10,0xF8,0xF0},
    /*0x1F( 31)*/ {0x00,0x80,0x00,0xFF,0xF9,0x00,0xF0,0x88,0x00,0xF0,0xEC,0x00,0xF0,0xF2,0x00,0xF0,0xC0,0x00,0xF0,0x88,0x00,0xF0,0x88,0x00,0xF1,0xF2,0x00},
    /*0x20( 32)*/ {0x10,0xF0,0xF0,0x00,0x00,0x21,0x00,0xF0,0xF2,0x00,0x88,0x88,0x00,0x88,0x8F,0x00,0x88,0x88,0x00,0x88,0x8F,0x00,0x88,0x88,0x00,0x8F,0x0F},
    /*0x21( 33)*/ {0xF0,0xF2,0x00,0x00,0x00,0x00,0xF0,0xE0,0x00,0x44,0x22,0x00,0x4C,0x22,0x00,0x44,0x22,0x00,0x4C,0x22,0x00,0x44,0x22,0x00,0x0F,0x2E,0x00},
    /*0x22( 34)*/ {0x00,0x43,0x86,0x00,0xC7,0xAF,0x01,0x47,0xAF,0x00,0x47,0x9F,0x00,0x47,0x0F,0x00,0x03,0x4F,0x00,0x00,0x12,0x00,0x00,0x70,0x00,0x0F,0x08},
    /*0x23( 35)*/ {0x23,0x56,0x00,0x47,0xAF,0x08,0x4F,0x9F,0x00,0x47,0x8F,0x80,0x47,0x0F,0x08,0x0F,0x88,0x00,0xE1,0x00,0x00,0x1E,0xF0,0x80,0x00,0x01,0x00},
    /*0x24( 36)*/ {0x00,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x0F,0x0F,0x00,0x00,0x00},
    /*0x25( 37)*/ {0xF0,0xE4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00},
    /*0x26( 38)*/ {0x00,0xF0,0xF0,0x00,0x88,0x44,0x00,0x88,0x44,0x00,0x88,0x84,0x00,0x98,0x08,0x00,0xCA,0x00,0x00,0x88,0x00,0x00,0x8F,0x0F,0x00,0x00,0x00},
    /*0x27( 39)*/ {0xF0,0xF2,0x00,0x44,0x22,0x00,0x44,0x22,0x00,0x44,0xA2,0x00,0x64,0xEA,0x00,0x01,0x22,0x00,0x00,0x22,0x00,0x0F,0x2E,0x00,0x00,0x00,0x00},
    /*0x28( 40)*/ {0x00,0x00,0x60,0x00,0x00,0x88,0x00,0x21,0x00,0x00,0xB4,0xF0,0x01,0x00,0x42,0x00,0x00,0x44,0x00,0x00,0x88,0x00,0x21,0x10,0x00,0x0C,0x00},
    /*0x29( 41)*/ {0x2F,0x00,0x00,0x11,0x00,0x00,0x00,0x48,0x00,0xF0,0xD2,0xC0,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0xD1,0x00,0x00,0x02,0x00,0x00},
    /*0x2A( 42)*/ {0x00,0x00,0x8E,0x10,0x0F,0x8F,0x00,0xF0,0x8F,0x00,0xF0,0xF9,0x00,0xF0,0xF8,0x00,0xF0,0xF0,0x00,0x88,0x00,0x00,0xF8,0xF0,0x00,0x08,0x00},
    /*0x2B( 43)*/ {0x40,0x23,0x00,0x9F,0x2A,0x00,0x11,0x22,0x00,0x91,0x22,0x00,0x99,0x22,0x00,0xD1,0x22,0x00,0x89,0x22,0x00,0x98,0x22,0x00,0x08,0x0E,0x00},
    /*0x2C( 44)*/ {0x00,0x00,0x10,0x00,0x70,0xF2,0x00,0x44,0x00,0x00,0x74,0xF0,0x00,0x44,0x00,0x00,0x74,0xF0,0x00,0x44,0x00,0x00,0x44,0x00,0x00,0x47,0x0F},
    /*0x2D( 45)*/ {0x00,0x00,0x00,0xF0,0xC0,0x00,0x00,0x44,0x00,0xF0,0xC4,0x00,0x00,0x44,0x00,0xF0,0xC4,0x00,0x00,0x44,0x00,0x00,0x44,0x00,0x0F,0x4C,0x00},
    /*0x2E( 46)*/ {0x00,0x00,0xF0,0x01,0x1F,0x10,0x11,0x1F,0x1F,0x00,0x9F,0x1F,0x00,0x9F,0x1F,0x00,0xF9,0xF1,0x10,0xF1,0xF1,0x00,0x11,0x30,0x11,0x0F,0x1C},
    /*0x2F( 47)*/ {0x10,0x00,0x00,0x11,0x00,0x00,0x79,0xF0,0x00,0x19,0x11,0x00,0x11,0x11,0x00,0x22,0x11,0x00,0x22,0x22,0x00,0x84,0x22,0x00,0x09,0xC6,0x00},
    /*0x30( 48)*/ {0x00,0x00,0x10,0x00,0x24,0x11,0x00,0x11,0x11,0x00,0x01,0x19,0x01,0x0F,0x8F,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0x21,0x00,0x10,0x84,0x00},
    /*0x31( 49)*/ {0x80,0x00,0x00,0x00,0x84,0x00,0x10,0x08,0x00,0x42,0x20,0x00,0x8F,0x0F,0x00,0x88,0x00,0x00,0x88,0x10,0x00,0x88,0x22,0x00,0x78,0xC3,0x00},
    /*0x32( 50)*/ {0x00,0x00,0x60,0x00,0x00,0x44,0x00,0x0F,0x8F,0x00,0x00,0x88,0x00,0x11,0xF0,0x00,0x22,0x00,0x00,0x84,0x00,0x11,0x00,0x00,0x00,0xF0,0xF0},
    /*0x33( 51)*/ {0x00,0x00,0x00,0x00,0x20,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0xF0,0xE4,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0x88,0x00,0x00,0xF8,0xF0,0x80},
    /*0x34( 52)*/ {0x00,0x00,0x60,0x00,0x00,0x44,0x00,0x0F,0x8F,0x00,0x00,0x88,0x00,0x21,0x80,0x00,0x42,0x8F,0x10,0x08,0x88,0x02,0x00,0xF8,0x00,0x00,0x08},
    /*0x35( 53)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x0F,0x88,0x00,0x00,0x88,0x00,0xF0,0x88,0x00,0x00,0x08,0x00},
    /*0x36( 54)*/ {0x00,0x10,0x80,0x00,0xF1,0xE5,0x00,0xF1,0xC0,0x00,0x99,0x44,0x00,0x9F,0x4C,0x00,0x9F,0x5D,0x00,0xF1,0xF5,0x00,0x11,0x00,0x00,0x11,0x00},
    /*0x37( 55)*/ {0x10,0x90,0x00,0x1F,0x0F,0x08,0x9F,0x2F,0x08,0x9F,0x2E,0x00,0x1F,0x2E,0x00,0x0F,0xDD,0x00,0x0F,0x8F,0x08,0x4C,0x88,0x00,0x34,0x88,0x00},
    /*0x38( 56)*/ {0x00,0x32,0x00,0x00,0x42,0x2F,0x00,0x44,0x44,0x10,0x5C,0xE9,0x21,0x44,0x23,0x00,0x45,0x2F,0x00,0x44,0x22,0x00,0x54,0xF2,0x00,0x45,0x00},
    /*0x39( 57)*/ {0x40,0x10,0x80,0x0E,0xD1,0x00,0x48,0x99,0x00,0x2E,0x99,0x00,0x40,0x99,0x00,0x0E,0x99,0x00,0x00,0x99,0x00,0x0C,0x11,0x00,0x00,0x2F,0x00},
    /*0x3A( 58)*/ {0x00,0x00,0x11,0x10,0xF0,0xF1,0x00,0x20,0x11,0x00,0x23,0x1F,0x00,0x23,0x1F,0x00,0x32,0xF1,0x00,0x02,0x11,0x03,0x0F,0x1F,0x00,0x00,0x11},
    /*0x3B( 59)*/ {0x00,0x00,0x00,0xF0,0xF2,0x00,0x00,0x80,0x00,0x0F,0x88,0x00,0x0F,0x88,0x00,0xF0,0x88,0x00,0x00,0x18,0x00,0x0F,0x0F,0x08,0x00,0x00,0x00},
    /*0x3C( 60)*/ {0x00,0xF0,0x80,0x00,0x88,0x88,0x00,0x88,0x99,0x00,0x2F,0x08,0x00,0xE2,0x40,0x00,0xAB,0x3D,0x00,0xAA,0x00,0x00,0xBA,0x94,0x00,0x8C,0x42},
    /*0x3D( 61)*/ {0x40,0x80,0x00,0x44,0x88,0x00,0x44,0x99,0x08,0xCC,0xCA,0x00,0x44,0xC8,0x00,0x4C,0x9B,0x80,0x84,0x88,0x00,0x08,0x88,0x80,0x00,0x78,0x08},
    /*0x3E( 62)*/ {0x00,0x00,0x11,0x00,0x00,0x21,0x00,0x00,0x42,0x00,0xF0,0xF8,0x00,0x00,0x00,0x00,0x11,0x0F,0x00,0x11,0x00,0x00,0x11,0x00,0x00,0x11,0x0F},
    /*0x3F( 63)*/ {0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x00,0xC3,0x1F,0x80,0x00,0x00,0x08,0x0F,0x2F,0x00,0x00,0x22,0x00,0x00,0x22,0x00,0x0F,0x2E,0x00},
    /*0x40( 64)*/ {0x00,0xF0,0xC0,0x00,0x00,0x40,0x01,0x0F,0x8E,0x00,0x0F,0x1C,0x00,0xF0,0xD8,0x00,0xF0,0x80,0x00,0x88,0x88,0x00,0x88,0x88,0x00,0x0F,0x38},
    /*0x41( 65)*/ {0x70,0xC0,0x00,0x44,0x44,0x00,0x84,0x44,0x80,0x08,0x34,0x08,0xF0,0xF0,0x00,0x88,0x42,0x00,0x24,0x84,0x00,0x21,0xC0,0x00,0x0C,0x07,0x80},
    /*0x42( 66)*/ {0x00,0x00,0x10,0x00,0xF0,0xF1,0x10,0x08,0x00,0x00,0xF0,0xF0,0x00,0x10,0x91,0x00,0x11,0x11,0x00,0x32,0x11,0x00,0x45,0x91,0x10,0x08,0x07},
    /*0x43( 67)*/ {0x80,0x00,0x00,0xF0,0xF0,0x00,0x00,0x42,0x00,0xF0,0xCC,0x00,0x00,0x00,0x00,0xF0,0xC8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0x08},
    /*0x44( 68)*/ {0x00,0x00,0x00,0x00,0x0F,0x1F,0x01,0x0F,0x1F,0x00,0x47,0x1F,0x00,0x74,0xF1,0x00,0x74,0xF1,0x00,0x04,0x11,0x00,0x0F,0x1F,0x10,0xF0,0xF1},
    /*0x45( 69)*/ {0xF0,0x80,0x00,0x00,0x20,0x00,0x0F,0x0F,0x00,0x0F,0x88,0x00,0xF0,0x88,0x00,0xF0,0x88,0x00,0x00,0x48,0x00,0x0F,0x0E,0x00,0xF0,0xF1,0x80},
    /*0x46( 70)*/ {0x00,0xF0,0xF0,0x00,0x88,0x88,0x00,0x0F,0x1F,0x01,0x2F,0x1F,0x00,0x9D,0x0F,0x00,0x99,0x0F,0x00,0x99,0x0F,0x00,0x99,0x0F,0x00,0x8F,0x0F},
    /*0x47( 71)*/ {0xF0,0xE0,0x00,0x44,0x22,0x00,0x0F,0x1E,0x00,0x0F,0x8F,0x00,0x0F,0x8C,0x00,0x0F,0x88,0x00,0x0F,0x88,0x00,0x0F,0x98,0x00,0x0F,0x0F,0x00},
    /*0x48( 72)*/ {0x00,0x00,0x10,0x00,0x07,0x0F,0x00,0x00,0x48,0x00,0xF0,0xF4,0x00,0x10,0x00,0x00,0x11,0x0F,0x00,0x11,0xF0,0x00,0x11,0x00,0x00,0x11,0x0F},
    /*0x49( 73)*/ {0x80,0x40,0x00,0x2F,0x0E,0x00,0x23,0x00,0x00,0xF4,0xF3,0x80,0x00,0x80,0x00,0x0F,0x88,0x00,0xF0,0x88,0x00,0x00,0x88,0x00,0x0F,0x88,0x00},
    /*0x4A( 74)*/ {0x00,0x30,0xF0,0x00,0x32,0xF0,0x00,0x32,0xF0,0x10,0xF0,0xF0,0x00,0x23,0x1F,0x00,0x23,0x1F,0x00,0x23,0x1F,0x00,0x0F,0x1F,0x10,0xF0,0xF1},
    /*0x4B( 75)*/ {0xF0,0x80,0x00,0xF0,0x88,0x00,0xF0,0x88,0x00,0xF0,0xF3,0x00,0x0F,0x88,0x00,0x0F,0x88,0x00,0x0F,0xC8,0x00,0x0F,0x0E,0x00,0xF0,0xF1,0x00},
    /*0x4C( 76)*/ {0x00,0x20,0x00,0x00,0x43,0x58,0x10,0x69,0x1D,0x00,0xF8,0xE5,0x00,0xF8,0xC4,0x00,0xF8,0xC4,0x00,0x88,0x88,0x00,0xB8,0x48,0x01,0x0C,0x00},
    /*0x4D( 77)*/ {0xC0,0x00,0x00,0x08,0x10,0x00,0x0F,0x2F,0x00,0xF0,0xA2,0x00,0x99,0x22,0x00,0xF9,0x22,0x00,0x9A,0xC2,0x00,0x88,0x11,0x00,0x0F,0x0F,0x00},
    /*0x4E( 78)*/ {0x00,0x00,0x70,0x00,0x07,0x88,0x00,0x00,0x98,0x00,0x1F,0x8F,0x00,0x21,0xAC,0x00,0x42,0x89,0x00,0x84,0x88,0x01,0x00,0x88,0x00,0x00,0x88},
    /*0x4F( 79)*/ {0x00,0x00,0x00,0x70,0xF1,0x80,0x44,0x11,0x00,0x4C,0x11,0x00,0x44,0x11,0x00,0x44,0x11,0x00,0x44,0x11,0x00,0x74,0xF1,0x00,0x04,0x01,0x00},
    /*0x50( 80)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x33,0xFF,0xCC,0x00,0x00,0x00},
    /*0x51( 81)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xFF,0xCC,0x33,0x08,0xCC,0x13,0xF8,0xCC,0x31,0x8F,0xCC,0x33,0x80,0xCC,0x01,0xFF,0xCC,0x00,0x00,0x00},
    /*0x52( 82)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xFF,0xCC,0x33,0x08,0xCC,0x13,0xF8,0xCC,0x00,0x6F,0xCC,0x10,0xCE,0xCC,0x33,0x08,0xCC,0x00,0x00,0x00},
    /*0x53( 83)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xFF,0x80,0x33,0x09,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x33,0x90,0xCC,0x01,0xFF,0x08,0x00,0x00,0x00},
    /*0x54( 84)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x33,0xEE,0x00,0x11,0x88,0x00,0x11,0x88,0x00,0x11,0x88,0x00,0x11,0xD8,0xCC,0x00,0x7F,0x08,0x00,0x00,0x00},
    /*0x55( 85)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xFF,0x80,0x33,0x09,0xCC,0x00,0x71,0x8C,0x31,0x8E,0xC0,0x33,0x90,0xCC,0x01,0xFF,0x08,0x00,0x00,0x00},
    /*0x56( 86)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x80,0x64,0xC4,0x8C,0x57,0x4C,0x88,0x45,0x54,0xC8},
    /*0x57( 87)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xFF,0xCC,0x33,0x08,0xCC,0x33,0x00,0xCC,0x33,0x00,0xCC,0x33,0x80,0xCC,0x01,0xFF,0xCC,0x00,0x00,0x00},
    /*0x58( 88)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x33,0xFF,0xCC,0x00,0x00,0xCC,0x10,0xF0,0xCC,0x01,0x0F,0xCC,0x00,0x00,0xCC,0x33,0xFF,0xCC,0x00,0x00,0x00},
    /*0x59( 89)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x10,0xCC,0x33,0x31,0xCC,0x33,0x63,0xCC,0x33,0xC6,0xCC,0x33,0x8C,0xCC,0x33,0x08,0xCC,0x00,0x00,0x00},
    /*0x5A( 90)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x80,0xCC,0x01,0xEC,0xCC,0x00,0x37,0xCC,0x00,0x73,0xCC,0x10,0xCE,0xCC,0x33,0x08,0xCC,0x00,0x00,0x00},
    /*0x5B( 91)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x31,0x0F,0xC8,0x10,0xF0,0x8C,0x33,0x00,0xC0,0x01,0xFF,0x08,0x00,0x00,0x00},
    /*0x5C( 92)*/ {0x00,0x00,0x10,0x00,0x88,0x11,0x00,0x88,0x11,0x00,0x88,0x11,0x00,0x0F,0x1F,0x10,0x00,0x11,0x11,0x00,0x11,0x11,0x00,0x11,0x11,0x0F,0x0F},
    /*0x5D( 93)*/ {0x80,0x00,0x00,0x00,0x22,0x00,0x00,0x22,0x00,0x00,0x22,0x00,0x0F,0x0E,0x00,0x00,0x10,0x80,0x00,0x11,0x00,0x00,0x11,0x00,0x0F,0x1F,0x00},
    /*0x5E( 94)*/ {0x00,0x00,0x80,0x00,0x11,0x01,0x00,0x22,0x0F,0x00,0x62,0x30,0x10,0x2A,0x30,0x00,0x22,0x10,0x00,0x22,0x11,0x00,0x22,0x11,0x00,0x22,0x11},
    /*0x5F( 95)*/ {0x00,0x20,0x00,0x0F,0x0F,0x80,0x0F,0x0F,0x0C,0xF0,0xF2,0x00,0xF0,0xF2,0x00,0x00,0x20,0x00,0x0F,0x2E,0x00,0x00,0x22,0x00,0x0F,0x2E,0x00},
    /* Multi Color Font */
    /*0x60( 96)*/ {0x00,0x00,0x30,0x00,0x00,0xF7,0x00,0x00,0xFF,0x00,0x00,0x37,0x00,0x00,0x70,0x00,0x31,0xFF,0x10,0xFF,0xFF,0x33,0xFF,0xFF,0x03,0x0F,0x0F},
    /*0x61( 97)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x62( 98)*/ {0xFF,0xFF,0xCF,0xFF,0xFF,0x7B,0xFF,0xFF,0x77,0xFF,0xFF,0xCB,0xFF,0xFF,0x8F,0xFF,0xDE,0xF7,0xEF,0x73,0xFF,0xCC,0xFF,0xFF,0xFC,0xF0,0xF0},
    /* Multi Color Font */
    /*0x63( 99)*/ {0xC0,0x00,0x00,0xFE,0x00,0x00,0xFF,0x00,0x00,0xCE,0x00,0x00,0xE0,0x00,0x00,0xFF,0xC8,0x00,0xFF,0xFF,0x80,0xFF,0xFF,0xCC,0x0F,0x0F,0x0C},
    /*0x64(100)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x65(101)*/ {0x3F,0xFF,0xFF,0xED,0xFF,0xFF,0xEE,0xFF,0xFF,0x3D,0xFF,0xFF,0x1F,0xFF,0xFF,0xFE,0xB7,0xFF,0xFF,0xEC,0x7F,0xFF,0xFF,0x33,0xF0,0xF0,0xF3},
    /* Multi Color Font */
    /*0x66(102)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x67(103)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x68(104)*/ {0xFF,0xFF,0xFF,0xCC,0x00,0x00,0xCC,0xEF,0x6F,0xCC,0xDD,0xEA,0xCC,0xFE,0x6E,0xCC,0xDF,0xAA,0xCC,0xFE,0xF6,0xCC,0x00,0x00,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x69(105)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x6A(106)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x6B(107)*/ {0xFF,0xFF,0xFF,0x00,0x00,0x33,0x3F,0xFF,0x33,0xED,0xFF,0x33,0xEE,0xFF,0x33,0xDE,0xEF,0x73,0xF3,0x9C,0xFF,0x00,0x73,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x6C(108)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xCF,0x00,0xFF,0xCC,0x00,0xFF,0xCC,0x00,0xFF,0xCC,0x00,0x0F,0x0F,0x00,0x00,0x00},
    /*0x6D(109)*/ {0xFF,0xFF,0xB7,0xFF,0xFF,0xED,0xCE,0x00,0x00,0xCC,0xCF,0x3F,0xCC,0xCC,0x33,0xCC,0xCC,0x33,0xCC,0xCC,0x33,0xCC,0x0F,0x0F,0xFE,0xF0,0xF0},
    /*0x6E(110)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0x0F,0xFF,0xCC,0x00,0xFF,0xCC,0x00,0xFF,0xCC,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x6F(111)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0x00,0x33,0xFF,0x00,0x33,0xFF,0x00,0x33,0xFF,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00},
    /*0x70(112)*/ {0xDE,0xFF,0xFF,0x7B,0xFF,0xFF,0x00,0x00,0x37,0xCF,0x3F,0x33,0xCC,0x33,0x33,0xCC,0x33,0x33,0xCC,0x33,0x33,0x0F,0x0F,0x33,0xF0,0xF0,0xF7},
    /*0x71(113)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x72(114)*/ {0x10,0xF0,0xF0,0x73,0xFF,0xFF,0x77,0xFF,0xFF,0x13,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x73(115)*/ {0xEF,0x0F,0x0F,0xBD,0xFF,0xFF,0xBB,0xFF,0xFF,0xED,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x98,0xFF,0xFF,0xFA,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x74(116)*/ {0xEF,0x0F,0x0F,0xAD,0xAF,0xAF,0xAB,0xAF,0xAF,0xED,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x75(117)*/ {0x00,0x00,0x00,0xC8,0x00,0x00,0xCC,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0xF7,0x80,0x11,0xFF,0xCC,0x01,0xFF,0x8C,0x00,0x07,0x00},
    /*0x76(118)*/ {0xFF,0xFF,0xFF,0xB7,0xFF,0xFF,0xBB,0xD3,0x7F,0xF7,0xCE,0x77,0xFF,0xFF,0xFF,0xFF,0x78,0x7F,0xEE,0xFF,0xBB,0xFE,0x7F,0x7B,0xFF,0xF8,0xFF},
    /*0x77(119)*/ {0xFF,0xFF,0xFF,0xB7,0xFF,0xFF,0xBB,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x78,0x7F,0xEE,0xDF,0xBB,0xFE,0x7F,0x7B,0xFF,0xF8,0xFF},
    /* Multi Color Font */
    /*0x78(120)*/ {0x00,0x00,0x00,0x00,0x10,0x87,0x00,0x42,0x00,0x00,0x84,0x00,0x00,0x88,0x11,0x00,0x88,0x31,0x00,0x64,0x97,0x00,0x12,0x00,0x00,0x00,0x0F},
    /*0x79(121)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x7A(122)*/ {0xFF,0xFF,0xFF,0xFF,0xEF,0x78,0xFF,0xBD,0xFF,0xFF,0x7B,0xFF,0xFF,0x77,0xEE,0xFF,0x77,0xCE,0xFF,0x9B,0x68,0xFF,0xED,0xFF,0xFF,0xFF,0xF0},
    /* Multi Color Font */
    /*0x7B(123)*/ {0x00,0x00,0x00,0x1E,0x80,0x00,0xC0,0x24,0x00,0x0C,0x12,0x00,0x88,0x11,0x00,0x00,0x11,0x00,0xC2,0x22,0x00,0x10,0x84,0x00,0x0E,0x00,0x00},
    /*0x7C(124)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x7D(125)*/ {0xFF,0xFF,0xFF,0xE1,0x7F,0xFF,0x3F,0xDB,0xFF,0xF3,0xED,0xFF,0x77,0xEE,0xFF,0xFF,0xEE,0xFF,0x3D,0xDD,0xFF,0xEF,0x7B,0xFF,0xF1,0xFF,0xFF},
    /* Multi Color Font */
    /*0x7E(126)*/ {0x00,0x00,0x00,0x33,0xFF,0xFF,0x33,0x10,0x90,0x33,0x22,0x15,0x33,0x01,0x91,0x33,0x20,0x55,0x33,0x01,0x09,0x33,0xFF,0xFF,0x00,0x00,0x00},
    /*0x7F(127)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x80(128)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x81(129)*/ {0x00,0x00,0x00,0xFF,0xFF,0xCC,0xC0,0x00,0xCC,0x12,0x00,0xCC,0x11,0x00,0xCC,0x21,0x10,0x8C,0x0C,0x63,0x00,0xFF,0x8C,0x00,0x00,0x00,0x00},
    /*0x82(130)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x83(131)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x84(132)*/ {0x00,0x00,0x00,0x33,0xFF,0xFF,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0xFF,0xFF,0x00,0x00,0x00},
    /*0x85(133)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x86(134)*/ {0xFF,0xFF,0xFF,0xCC,0x00,0x00,0xCC,0xEF,0x6F,0xCC,0xDD,0xEA,0xCC,0xFE,0x6E,0xCC,0xDF,0xAA,0xCC,0xFE,0xF6,0xCC,0x00,0x00,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x87(135)*/ {0x00,0x00,0x00,0xFF,0xFF,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x10,0x8C,0x00,0x63,0x00,0xFF,0x8C,0x00,0x00,0x00,0x00},
    /*0x88(136)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x89(137)*/ {0xFF,0xFF,0xFF,0x00,0x00,0x33,0x3F,0xFF,0x33,0xED,0xFF,0x33,0xEE,0xFF,0x33,0xDE,0xEF,0x73,0xF3,0x9C,0xFF,0x00,0x73,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x8A(138)*/ {0x00,0x00,0x00,0x33,0xFF,0xFF,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0x00,0x00,0x33,0xFF,0xFF,0x00,0x00,0x00},
    /*0x8B(139)*/ {0xFF,0xFF,0xFF,0xCC,0x00,0x00,0xCC,0xFF,0xFF,0xCC,0xFF,0xFF,0xCC,0xFF,0xFF,0xCC,0xFF,0xFF,0xCC,0xFF,0xFF,0xCC,0x00,0x00,0xFF,0xFF,0xFF},
    /*0x8C(140)*/ {0xFF,0xFF,0xFF,0xCC,0x00,0x00,0xCC,0xEF,0x6F,0xCC,0xDD,0xEA,0xCC,0xFE,0x6E,0xCC,0xDF,0xAA,0xCC,0xFE,0xF6,0xCC,0x00,0x00,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x8D(141)*/ {0x00,0x00,0x00,0xFF,0xFF,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x10,0x8C,0x00,0x63,0x00,0xFF,0x8C,0x00,0x00,0x00,0x00},
    /*0x8E(142)*/ {0xFF,0xFF,0xFF,0x00,0x00,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xEF,0x73,0xFF,0x9C,0xFF,0x00,0x73,0xFF,0xFF,0xFF,0xFF},
    /*0x8F(143)*/ {0xFF,0xFF,0xFF,0x00,0x00,0x33,0x3F,0xFF,0x33,0xED,0xFF,0x33,0xEE,0xFF,0x33,0xDE,0xEF,0x73,0xF3,0x9C,0xFF,0x00,0x73,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x90(144)*/ {0x00,0x10,0xF7,0x00,0x67,0x38,0x00,0xCC,0xE7,0x11,0xB9,0x8C,0x11,0xBB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x91(145)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x92(146)*/ {0xFF,0xEF,0x08,0xFF,0x98,0xC7,0xFF,0x33,0x18,0xEE,0x46,0x43,0xEE,0x44,0xEC,0xFF,0xFF,0xEC,0xFF,0xFF,0x1B,0xFF,0xFE,0x00,0xFF,0xFF,0xB9},
    /* Multi Color Font */
    /*0x93(147)*/ {0x88,0x00,0x00,0x80,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x94(148)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x95(149)*/ {0x77,0xFF,0xFF,0x7F,0xFF,0xFF,0xF7,0x1B,0xFF,0xBE,0x00,0xF7,0x01,0xF9,0xFF,0x00,0x37,0xFF,0x80,0xF7,0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x96(150)*/ {0x00,0x10,0xF7,0x00,0x67,0x38,0x00,0xCC,0xE7,0x11,0xB9,0xBC,0x11,0xBB,0x13,0x00,0x00,0x13,0x00,0x00,0xE4,0x00,0x01,0xFF,0x00,0x00,0x46},
    /*0x97(151)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x98(152)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x99(153)*/ {0x88,0x00,0x00,0x80,0x00,0x00,0x08,0xE4,0x00,0x41,0xFF,0x08,0xFE,0x06,0x00,0xFF,0xC8,0x00,0x7F,0x08,0x00,0x02,0x00,0x00,0x00,0x00,0x00},
    /*0x9A(154)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x9B(155)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x9C(156)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x9D(157)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0xFF,0xFF,0x00,0xFF,0xFF,0x88,0xFF,0xFF,0xFE},
    /*0x9E(158)*/ {0xFF,0xFF,0xDE,0xFF,0xFF,0xBD,0xDE,0x7F,0x7B,0x7B,0xA7,0xF7,0xFF,0xDA,0xFF,0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x9F(159)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0xA0(160)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE1,0xFF,0xFF,0x8F,0x7F,0xFF,0xCC,0xFF,0xFF,0xF1,0xFF,0xFF},
    /*0xA1(161)*/ {0x7F,0xFF,0xFF,0xB7,0xFF,0xFF,0xBB,0xDF,0xFF,0xCB,0x7A,0x97,0xFD,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0xA2(162)*/ {0x00,0x00,0x21,0x00,0x00,0x42,0x21,0x80,0x84,0x84,0x58,0x08,0x00,0x25,0x00,0x00,0x02,0x73,0x00,0x00,0xFF,0x00,0x00,0x77,0x00,0x00,0x01},
    /*0xA3(163)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xA4(164)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0xA5(165)*/ {0x80,0x00,0x00,0x48,0x00,0x00,0x44,0x20,0x00,0x34,0x85,0x68,0x02,0x00,0x01,0x1E,0x00,0x00,0x70,0x80,0x00,0x33,0x00,0x00,0x0E,0x00,0x00},
    /*0xA6(166)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xA7(167)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0xA8(168)*/ {0x00,0x20,0x00,0x00,0xE7,0x00,0x31,0x8C,0xE4,0x63,0x31,0x9C,0x36,0x13,0xC9,0x13,0xC8,0x4C,0x00,0x7E,0x00,0x00,0x02,0x00,0x00,0x00,0x00},
    /*0xA9(169)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xAA(170)*/ {0xFF,0xDF,0xFF,0xFF,0x18,0xFF,0xCE,0x73,0x1B,0x9C,0xCE,0x63,0xC9,0xEC,0x36,0xEC,0x37,0xA3,0xFF,0x81,0xCE,0xFF,0xFD,0xCC,0xFF,0xFF,0xFC},
    /* Multi Color Font */
    /*0xAB(171)*/ {0x00,0x40,0x00,0x00,0x7E,0x00,0x72,0x13,0xC8,0x93,0xC8,0x6C,0x39,0x8C,0xC6,0x23,0x31,0x8C,0x00,0xE7,0x00,0x00,0x04,0x00,0x00,0x00,0x00},
    /*0xAC(172)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xAD(173)*/ {0xFF,0xBF,0xFF,0xFF,0x81,0xFF,0x8D,0xEC,0x37,0x6C,0x37,0x93,0xC6,0x73,0x39,0x5C,0xCE,0x73,0x37,0x18,0xFF,0x33,0xFB,0xFF,0xF3,0xFF,0xFF},
    /* Multi Color Font */
    /*0xAE(174)*/ {0x00,0x20,0x00,0x00,0xE7,0x00,0x31,0x8C,0xE4,0x63,0x31,0x9C,0x36,0x13,0xC9,0x13,0xC8,0x5C,0x00,0x7E,0x31,0x00,0x02,0x33,0x00,0x00,0x03},
    /*0xAF(175)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xB0(176)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0xB1(177)*/ {0x00,0x40,0x00,0x00,0x7E,0x00,0x72,0x13,0xC8,0x93,0xC8,0x6C,0x39,0x8C,0xC6,0xA3,0x31,0x8C,0xC8,0xE7,0x00,0xCC,0x04,0x00,0x0C,0x00,0x00},
    /*0xB2(178)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xB3(179)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0xB4(180)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0xB5(181)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xB6(182)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0xFE,0xFF,0xFF,0xEF,0xFF,0xFF,0xCE,0xFF,0xFF,0xCC,0xFF,0xFF,0xFC},
    /* Multi Color Font */
    /*0xB7(183)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0xB8(184)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xB9(185)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xF7,0xFF,0xFF,0x7F,0xFF,0xFF,0x37,0xFF,0xFF,0x33,0xFF,0xFF,0xF3,0xFF,0xFF},
    /* Multi Color Font */
    /*0xBA(186)*/ {0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x10,0xFF,0x00,0x33,0xFF,0x00,0x77,0xFF,0x00,0x37,0xFF,0x00,0x13,0xFF,0x00,0x00,0x3F,0x00,0x00,0x00},
    /*0xBB(187)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xEF,0x00,0xFF,0xCC,0x00,0xFF,0x88,0x00,0xFF,0xC8,0x00,0xFF,0xEC,0x00,0xFF,0xFF,0xC0,0xFF,0xFF,0xFF},
    /*0xBC(188)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xEF,0x00,0xFF,0xCC,0x00,0xFF,0x88,0x00,0xFF,0xC8,0x00,0xFF,0xEC,0x00,0xFF,0xFF,0xC0,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0xBD(189)*/ {0x00,0x00,0x00,0x80,0x00,0x00,0xFE,0x00,0x00,0xFF,0x88,0x00,0xFF,0xCC,0x00,0xFF,0x8C,0x00,0xFF,0x08,0x00,0x8E,0x00,0x00,0x00,0x00,0x00},
    /*0xBE(190)*/ {0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0x77,0xFF,0x00,0x33,0xFF,0x00,0x73,0xFF,0x00,0xF7,0xFF,0x71,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xBF(191)*/ {0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0x01,0xFF,0xFF,0x00,0x77,0xFF,0x00,0x33,0xFF,0x00,0x73,0xFF,0x00,0xF7,0xFF,0x71,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0xC0(192)*/ {0x00,0x10,0xF7,0x00,0x67,0x38,0x00,0xCC,0xE7,0x11,0xB9,0xBC,0x11,0xBB,0x13,0x00,0x00,0x13,0x00,0x00,0xE4,0x00,0x01,0xFF,0x00,0x00,0x46},
    /*0xC1(193)*/ {0xFF,0xEF,0x08,0xFF,0x98,0xC7,0xFF,0x33,0x18,0xEE,0x46,0x43,0xEE,0x44,0xEC,0xFF,0xFF,0xEC,0xFF,0xFF,0x1B,0xFF,0xFE,0x00,0xFF,0xFF,0xB9},
    /*0xC2(194)*/ {0xFF,0xEF,0x08,0xFF,0x98,0xC7,0xFF,0x33,0x18,0xEE,0x46,0x43,0xEE,0x44,0xEC,0xFF,0xFF,0xEC,0xFF,0xFF,0x1B,0xFF,0xFE,0x00,0xFF,0xFF,0xB9},
    /* Multi Color Font */
    /*0xC3(195)*/ {0x88,0x00,0x00,0x80,0x00,0x00,0x08,0xE4,0x00,0x41,0xFF,0x08,0xFE,0x06,0x00,0xFF,0xC8,0x00,0x7F,0x08,0x00,0x02,0x00,0x00,0x00,0x00,0x00},
    /*0xC4(196)*/ {0x77,0xFF,0xFF,0x7F,0xFF,0xFF,0xF7,0x1B,0xFF,0xBE,0x00,0xF7,0x01,0xF9,0xFF,0x00,0x37,0xFF,0x80,0xF7,0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0xC5(197)*/ {0x77,0xFF,0xFF,0x7F,0xFF,0xFF,0xF7,0x1B,0xFF,0xBE,0x00,0xF7,0x01,0xF9,0xFF,0x00,0x37,0xFF,0x80,0xF7,0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF}
};

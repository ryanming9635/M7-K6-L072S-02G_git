/****************************************************************/
/*                      TW88xx RAM FONT                         */
/****************************************************************/
/* <FILE TYPE>=TW8804 */
/* <NUMBER OF FONTS>=0x4C(76) */
/* <COLOR START>=0x3A */

/* <LOOK-UP TABLE> */
code unsigned char OSD_Color_LookUp_Data_Table_KRS[][8] = {
     {0xDF,0x32,0x9C,0x4A,0xE8,0x5B,0xF8,0xFF},
     {0xBB,0x2F,0x08,0x92,0x01,0x49,0x37,0xDB}
};

/* <FONT DATA> */
code unsigned char RAMFONTDATA_KRS[][27] = {
    /*0x00(  0)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x01(  1)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0xFF,0x00,0x77,0xCE,0x00,0xFF,0xCC,0x11,0xFF,0xCC,0x31,0xFF,0xCC,0x33,0xFF,0xCC},
    /*0x02(  2)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xE8,0x00,0x13,0xFF,0x00,0x11,0xFF,0x88,0x11,0xFF,0xCC,0x11,0xFF,0xEC,0x11,0xFF,0xEE},
    /*0x03(  3)*/ {0x33,0xFF,0xCC,0x33,0xFF,0xCC,0x33,0xFF,0xCC,0x13,0xFF,0xCC,0x11,0xFF,0xCC,0x00,0xFF,0xCC,0x00,0x77,0xEC,0x00,0x03,0xFF,0x00,0x00,0x00},
    /*0x04(  4)*/ {0x11,0xFF,0xEE,0x11,0xFF,0xEE,0x11,0xFF,0xEE,0x11,0xFF,0xCE,0x11,0xFF,0xCC,0x11,0xFF,0x88,0x31,0xFF,0x00,0xFF,0x8E,0x00,0x00,0x00,0x00},
    /*0x05(  5)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x06(  6)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00},
    /*0x07(  7)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x08(  8)*/ {0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0x00,0x00,0x00},
    /*0x09(  9)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x71,0xFF,0x10,0xCF,0x00,0x11,0xCC,0x00,0x00,0xEE,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x0A( 10)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xE8,0x00,0x03,0xFF,0x80,0x00,0x77,0xCC,0x00,0x33,0xEE,0x00,0x33,0xEE,0x00,0x73,0xCE},
    /*0x0B( 11)*/ {0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0xF7,0x00,0x31,0xEF,0x00,0x77,0x08,0x00,0xCE,0x00,0x11,0xFC,0xF0,0x11,0xFF,0xFF,0x00,0x00,0x00},
    /*0x0C( 12)*/ {0x10,0xFF,0x8C,0xF7,0xEF,0x00,0xEF,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xE0,0xFF,0xFF,0xEE,0x00,0x00,0x00},
    /*0x0D( 13)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x71,0xFF,0x10,0xCF,0x00,0x11,0xCC,0x00,0x00,0xEE,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x0E( 14)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xE8,0x00,0x03,0xFF,0x80,0x00,0x77,0xCC,0x00,0x77,0xEE,0x00,0xF7,0xCE,0x71,0xFF,0x88},
    /*0x0F( 15)*/ {0x00,0x00,0x33,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x00,0x11,0xCC,0x00,0x01,0xFC,0x00,0x00,0x17,0xFF,0x00,0x00,0x00},
    /*0x10( 16)*/ {0xFF,0xEF,0x00,0x17,0xFF,0x80,0x00,0x7F,0xC8,0x00,0x77,0xEC,0x00,0x77,0xEE,0x00,0xFF,0xCC,0x31,0xFF,0x08,0xFF,0x8E,0x00,0x00,0x00,0x00},
    /*0x11( 17)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x33,0x00,0x00,0x77,0x00,0x00,0xEE},
    /*0x12( 18)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x73,0xFF,0x88,0xF7,0xFF,0x88,0xFF,0xFF,0x88,0xBB,0xFF,0x88,0x33,0xFF,0x88,0x33,0xFF,0x88},
    /*0x13( 19)*/ {0x00,0x11,0xCC,0x00,0x33,0x88,0x00,0x77,0x00,0x00,0xEE,0x00,0x11,0xCC,0x00,0x33,0x88,0x00,0x33,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x14( 20)*/ {0x33,0xFF,0x88,0x33,0xFF,0x88,0x33,0xFF,0x88,0x33,0xFF,0x88,0x33,0xFF,0x88,0x33,0xFF,0x88,0xFF,0xFF,0xEE,0x33,0xFF,0x88,0x00,0x00,0x00},
    /*0x15( 21)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0xFF,0xFF,0x11,0xFF,0xFF,0x11,0x8F,0x0F,0x11,0x88,0x10,0x11,0xB8,0xFF,0x11,0xEF,0x0F},
    /*0x16( 22)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xCC,0xFF,0xFF,0xCC,0x0F,0x0F,0x0C,0xF0,0x80,0x00,0xFF,0xFE,0x00,0xFF,0xFF,0xC8},
    /*0x17( 23)*/ {0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x11,0xEE,0x00,0x11,0xEE,0x00,0x00,0xFE,0x00,0x00,0x13,0xFF,0x00,0x00,0x00},
    /*0x18( 24)*/ {0x13,0xFF,0xEC,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x11,0xFF,0xCC,0x73,0xFF,0x08,0xFF,0x8E,0x00,0x00,0x00,0x00},
    /*0x19( 25)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0xF0,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF},
    /*0x1A( 26)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xC0,0x0F,0x0F,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xCC,0x00,0x00,0x00},
    /*0x1B( 27)*/ {0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x77,0xFF,0x00,0x07,0x0F},
    /*0x1C( 28)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    /*0x1D( 29)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0xEE,0x00,0x77,0xFF,0x00,0x77,0xFF,0x88,0x67,0xFF,0xCC,0x66,0x7F,0xFE,0x66,0x37,0xFF},
    /*0x1E( 30)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xEE,0x11,0xFF,0xEE,0x33,0xFF,0xEE,0x66,0xFF,0xEE,0xCC,0xFF,0xEE,0x88,0xFF,0xEE},
    /*0x1F( 31)*/ {0x66,0x13,0xFF,0x66,0x01,0xEE,0x66,0x00,0x0C,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x66,0x00,0x00,0x00,0x00,0x00},
    /*0x20( 32)*/ {0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0xFF,0xEE,0x00,0x00,0x00},
    /*0x21( 33)*/ {0x10,0xF0,0x80,0x33,0x99,0xCC,0x77,0x99,0xEE,0x77,0x99,0xEE,0x77,0x99,0xEE,0x77,0x99,0xEE,0x37,0x99,0xCE,0x13,0xF9,0x8C,0x00,0x00,0x00},
    /*0x22( 34)*/ {0x00,0x30,0xE0,0x00,0x11,0xEE,0x00,0x11,0xEE,0x00,0x11,0xEE,0x00,0x11,0xEE,0x00,0x11,0xEE,0x00,0x11,0xEE,0x00,0x11,0xEE,0x00,0x00,0x00},
    /*0x23( 35)*/ {0x10,0xF0,0x80,0x63,0x13,0xFE,0x06,0x00,0xFF,0x00,0x00,0xFF,0x00,0x31,0xEF,0x10,0xE7,0x0C,0x73,0xF0,0xF0,0x77,0xFF,0xFF,0x00,0x00,0x00},
    /*0x24( 36)*/ {0x30,0xF0,0xC0,0x67,0x00,0x7E,0x00,0x00,0x77,0x00,0x10,0xEF,0x00,0x17,0xEC,0x00,0x00,0x7F,0x60,0x00,0x67,0x37,0xF0,0x8C,0x00,0x00,0x00},
    /*0x25( 37)*/ {0x00,0x10,0xC0,0x00,0x33,0xCC,0x00,0x77,0xCC,0x00,0xDD,0xCC,0x11,0x99,0xCC,0x31,0x11,0xCC,0x62,0x11,0xCC,0x07,0x1F,0xCF,0x00,0x00,0x00},
    /*0x26( 38)*/ {0x70,0xF0,0xF0,0x67,0x0F,0x0F,0x66,0x70,0xC0,0x77,0x0F,0xEE,0x00,0x00,0x77,0x00,0x00,0x77,0x73,0x00,0x77,0x37,0xF8,0xCE,0x00,0x00,0x00},
    /*0x27( 39)*/ {0x00,0xF0,0xC0,0x31,0x8C,0x06,0x73,0x00,0x00,0x77,0xF7,0xC8,0x77,0x08,0x7E,0x77,0x00,0x77,0x77,0x00,0x77,0x13,0xF8,0xCE,0x00,0x00,0x00},
    /*0x28( 40)*/ {0x70,0x00,0x70,0x77,0x80,0xFF,0x77,0xD9,0x7F,0x55,0xEF,0x77,0x44,0xCE,0x77,0x44,0x04,0x77,0x44,0x00,0x77,0x44,0x00,0x77,0x00,0x00,0x00},
    /*0x29( 41)*/ {0x70,0x80,0xF0,0x77,0x88,0xFF,0x77,0x88,0xFF,0x77,0x8F,0xFF,0x77,0x88,0xFF,0x77,0x88,0xFF,0x77,0x88,0xFF,0x77,0x88,0xFF,0x00,0x00,0x00},
    /*0x2A( 42)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x0F,0xCC,0x00,0x31,0x8C,0x00,0xE7,0x00,0x31,0x8C,0x00,0x77,0xF0,0xC0,0x00,0x00,0x00},
    /*0x2B( 43)*/ {0x00,0xF0,0xC0,0x31,0x08,0x66,0x73,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x33,0x00,0x20,0x01,0xF8,0xC6,0x00,0x00,0x00},
    /*0x2C( 44)*/ {0x70,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x1F,0xC8,0x77,0x00,0xEE,0x77,0x00,0xEE,0x77,0x00,0xEE,0x77,0x00,0xEE,0x00,0x00,0x00},
    /*0x2D( 45)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xF0,0xF0,0x73,0x08,0x7F,0x77,0x00,0x77,0x77,0x00,0x77,0x03,0xF8,0x7F,0x00,0x00,0x00},
    /*0x2E( 46)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0xF0,0xC0,0x77,0x08,0x7E,0x77,0x00,0x77,0x77,0x00,0x77,0x77,0x00,0x77,0x00,0x00,0x00},
    /*0x2F( 47)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0xF0,0xC0,0x73,0x08,0x7E,0x77,0xF0,0xEF,0x77,0x00,0x30,0x13,0xF8,0xC6,0x00,0x00,0x00},
    /*0x30( 48)*/ {0x70,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x77,0x00,0x00,0x00,0x00,0x00},
    /*0x31( 49)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x0C,0x00,0x00,0x00,0x00},
    /*0x32( 50)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00},
    /*0x33( 51)*/ {0x10,0xF0,0xE0,0x73,0x08,0x37,0x77,0x80,0x00,0x37,0xFE,0xC0,0x01,0x7F,0xFE,0x66,0x01,0x7F,0x37,0x00,0x33,0x03,0xFC,0xC6,0x00,0x00,0x00},
    /*0x34( 52)*/ {0x70,0xF0,0xE0,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00},
    /*0x35( 53)*/ {0x00,0x70,0x00,0x00,0x77,0x00,0x00,0xFF,0x88,0x10,0xBF,0xC8,0x31,0x33,0xCC,0x23,0x11,0xEE,0x47,0x0F,0xFE,0x8C,0x00,0xFF,0x00,0x00,0x00},
    /*0x36( 54)*/ {0x70,0xF0,0xE0,0x77,0x88,0x00,0x77,0xF8,0xE0,0x77,0x88,0x00,0x77,0x88,0x00,0x77,0x88,0x00,0x77,0x88,0x00,0x77,0x88,0x00,0x00,0x00,0x00},
    /*0x37( 55)*/ {0x70,0xF0,0xC0,0x77,0x9B,0xFE,0x77,0x88,0xFF,0x77,0x98,0xFF,0x77,0xFB,0xCE,0x77,0x88,0x00,0x77,0x88,0x00,0x77,0x88,0x00,0x00,0x00,0x00},
    /*0x38( 56)*/ {0xE0,0x00,0x10,0xFF,0x00,0x31,0x7F,0x80,0x62,0x77,0x88,0xC4,0x33,0xCC,0x8C,0x13,0xFD,0x08,0x11,0xFF,0x00,0x00,0xEE,0x00,0x00,0x00,0x00},
    /*0x39( 57)*/ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x8F,0xEC,0x77,0x00,0x77,0x77,0x00,0x77,0x13,0xF8,0xCE,0x00,0x00,0x00},
    /* Multi Color Font */
    /*0x3A( 58)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x3B( 59)*/ {0x30,0xF0,0xF0,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x33,0xFF,0xFF,0x00,0x00,0x00},
    /*0x3C( 60)*/ {0xFF,0xFF,0xFF,0xFF,0x0F,0x0F,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x3D( 61)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x3E( 62)*/ {0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00},
    /*0x3F( 63)*/ {0xFF,0xFF,0xFF,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x40( 64)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x41( 65)*/ {0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00},
    /*0x42( 66)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x43( 67)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /*0x44( 68)*/ {0xF0,0xF0,0xC0,0x0F,0x0F,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0x00,0x00,0xCC,0xFF,0xFF,0xCC,0x00,0x00,0x00},
    /*0x45( 69)*/ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* Multi Color Font */
    /*0x46( 70)*/ {0x00,0x00,0xE8,0x07,0x0E,0x9F,0x00,0x00,0xE8,0x07,0x0E,0x89,0x00,0x00,0x88,0x14,0xFF,0x8B,0x11,0xFF,0x08,0x60,0x0E,0xD1,0x00,0x00,0x01},
    /*0x47( 71)*/ {0x00,0x00,0x00,0x07,0x0E,0x00,0x00,0x00,0x00,0x07,0x0E,0x00,0x00,0x00,0x00,0x04,0x10,0x03,0x00,0x63,0x00,0x60,0x00,0xC0,0x00,0x00,0x00},
    /*0x48( 72)*/ {0x00,0x00,0x00,0x07,0x0E,0x00,0x00,0x00,0x00,0x07,0x0E,0x00,0x00,0x00,0x00,0x04,0xF0,0x03,0x00,0xEF,0x00,0x60,0x00,0xC0,0x00,0x00,0x00},
    /* Multi Color Font */
    /*0x49( 73)*/ {0x00,0x00,0x00,0xE8,0x0F,0x0C,0x17,0x88,0x00,0x68,0x8B,0x0C,0x01,0x88,0x00,0x0E,0x8B,0x0C,0xF0,0x88,0x00,0xFF,0x8B,0x0C,0xEF,0x00,0x00},
    /*0x4A( 74)*/ {0x00,0x00,0x00,0x00,0x0F,0x0C,0x00,0x00,0x00,0x00,0x03,0x0C,0x00,0x00,0x00,0x0E,0x03,0x0C,0x00,0x00,0x00,0x31,0x03,0x0C,0x0E,0x00,0x00},
    /*0x4B( 75)*/ {0x00,0x00,0x00,0x00,0x0F,0x0C,0x00,0x00,0x00,0x00,0x03,0x0C,0x00,0x00,0x00,0x0E,0x03,0x0C,0x00,0x00,0x00,0xFF,0x03,0x0C,0x0E,0x00,0x00}
};

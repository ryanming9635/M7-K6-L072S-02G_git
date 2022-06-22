//********************************************************************
//
//	Functions for OSD Menu.: MYSON
//
//********************************************************************
/*void ChangeFont(BYTE type)
{
	BYTE dt;

	dt = ReadTW88(TW88_ENABLERAM);
	if( type==FONT_ROM )	dt &= 0x7f;
	else					dt |= 0x80;
	WriteTW88(TW88_ENABLERAM, dt);
}

void WriteCharToOSDRAMWithAutoInc(BYTE addr, BYTE ch, BYTE attr)
{
	addr = addr;
	WriteTW88(TW88_OSDRAMDATALO, attr);	// @@ Alert @@ For TW8801 : do not change the order
	WriteTW88(TW88_OSDRAMDATAHI, ch);
}

//-----------------------------------------------------------------------------
//	CopyCharToOSDWindow(BYTE winno, BYTE xoff, BYTE yoff, BYTE attr, BYTE ch)
//	- For FONT ROM Char.
//-----------------------------------------------------------------------------
void CopyCharToOSDWindow(BYTE winno, BYTE xoff, BYTE yoff, BYTE attr, BYTE ch)
{
	BYTE w;
	WORD addr;

	SetOSDWindowNum(winno);

//	addr = ReadTW88(TW88_WINSADDR);
	addr = ReadTW88(TW88_WINSADDRLO);
	addr = addr + ((ReadTW88(TW88_WINSADDRHI) & 0x01)<<8);
	w = ReadTW88(TW88_WINWIDTH);

	addr = addr + w*yoff + xoff;

	EnableOSDRAMAndChangeFont( FONT_ROM );
	WriteCharToOSDRAM(  addr, ch, attr );
}

#if defined( SUPPORT_PC ) || defined( SUPPORT_DTV )
BYTE CreateOSDWindowBorder(BYTE winno, BYTE w, BYTE h)
{
	if( winno<1 || winno>8 ) return FALSE;
	if ( w>0x7f || h>0x7f ) return FALSE;

	SetOSDWindowNum(winno);
	WriteTW88(TW88_WINBRDWIDTH, w);
	WriteTW88(TW88_WINBRDHEIGHT, h);
	return TRUE;
}

BYTE CreateOSDWindowOutline(BYTE winno, BYTE w, BYTE color)
{
	BYTE rd;

	if( winno<1 || winno>8 ) return FALSE;
	if ( w > 0x0f ) return FALSE;

	SetOSDWindowNum(winno);

	if( w==0 ) rd = 0;
	else       rd = 0x80 | color | w ;

	WriteTW88(TW88_WINBRDATTR , rd);
	return TRUE;

}
#endif // SUPPORT_PC || SUPPORT_DTV
*/
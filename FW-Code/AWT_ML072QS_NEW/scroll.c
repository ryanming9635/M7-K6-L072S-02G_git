
///////////////////////////////////////////////
{
	BYTE _a2[4];
	WORD _v[4];
	BYTE _w[4], _sa[4], _cl[4];
	char i;

	for( i=3; i>=0; i-- ) {
		
		SetOSDWindowNum(i+1);
		_w[i]  = ReadTW88(TW88_WINWIDTH);
		_sa[i] = ReadTW88(TW88_WINSADDRLO);
		_cl[i] = ReadTW88(TW88_WINATTR) & 0xfe;
		
		_a2[i] = ReadTW88(TW88_WINSTART_HI);
		_v[i] = (_a2[i] & 0x30) << 4;
		_v[i] += ReadTW88(TW88_WINYSTART);
		_v[i] += 18*2;
	}

	WaitVSync();

	for( i=3; i>=0; i-- ) {
		
		SetOSDWindowNum(i+1);
		WriteTW88(TW88_WINATTR, 0);

		WriteTW88( TW88_WINSTART_HI, (_a2[i]&0x0f) | ((_v[i]>>8)<<4) );
		WriteTW88( TW88_WINYSTART, (BYTE)_v[i] );

		if( i==3 ) continue;

		SetOSDWindowNum(i+2);
		WriteTW88(TW88_WINWIDTH, _w[i]);
		WriteTW88(TW88_WINSADDRLO, _sa[i]);
		
		_cl[i] += _w[i]? 1:0;
		WriteTW88(TW88_WINATTR, _cl[i]);
	}
}

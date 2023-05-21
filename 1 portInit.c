
	OutputPinWith1(FSS);//Altera Load SPI
	OutputPinWith1(FMOSI);
	InputPinWithPullUp(FMISO);
	OutputPinWith1(FSCK);
	
	///PORT F - AD9889b I2C init bus
	OutputPinWireAndWith1(SDAa);
	OutputPinWireAndWith1(SCLa);
	
	OutputPinWith0(NRES);
	
	//Altera registers SPI
	OutputPinWith1(SS1);
	OutputPinWith1(MOSI);
	InputPinWithPullUp(MISO);
	OutputPinWith1(SCK);

	///PORT H
	OutputPinWith0(NCONF);
	InputPinWithZState(NSTAT);
	OutputPinWith0(DCLK);
	InputPinWithZState(CONFD);



/* Порты для передачи данных между микроконтроллером и ПЛИС - шина SPI*/
OutputPinWith1(FSS);//Altera Load SPI
OutputPinWith1(FMOSI);
InputPinWithPullUp(FMISO);
OutputPinWith1(FSCK);

/* Порты для шины I2C - инициализация AD9889b */
OutputPinWireAndWith1(SDAa);
OutputPinWireAndWith1(SCLa);

/* Порт сброса внутренней логики ПЛИС */
OutputPinWith0(NRES);

/* Порты для передачи данных между микроконтроллером и флэш памятью*/
OutputPinWith1(SS1);
OutputPinWith1(MOSI);
InputPinWithPullUp(MISO);
OutputPinWith1(SCK);

/* Порты для загрузки ПЛИС по методу Passive Serial */
OutputPinWith0(NCONF);
InputPinWithZState(NSTAT);
OutputPinWith0(DCLK);
InputPinWithZState(CONFD);

/* Порт сканирования роторного переключателя */
InputPortWithPullUp(PORTB);//rotary switchs port

do{	/*	Проверка флага изменения состояния 	роторного переключателя	*/
	if(CheckFlag(FlagsScanner, FlRotReady))	
	{	/* Сброс флага */
		ClrFlag(FlagsScanner, FlRotReady);
		/* Запись нового значения в ПЛИС */
		InitHDMI_Select();
	}
}while(1);


void InitHDMI_Select(void)
{
	/* Временный буффер для хранения 
		текущего состояния переключателя
	*/
	u8b buffer[4];
	/* Внутренний адрес регистра на шине SPI */
	u8b SPIAddr = 1;
	/* Длина блока передачи */
	u8b TransfLen = 1;
	/* Копирование данных в буфер */
	buffer[0] = RotState;
	/* Передача данных по шине SPI */
	OutputPinWith0(SS1);
		WrSPI(&SPIF, &buffer[0]);
	OutputPinWith1(SS1);
}
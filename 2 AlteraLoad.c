#define DMATransmit \
PORTFSCK.OUTCLR = 1 << FSCK; PORTFSCK.OUTSET = 1 << FSCK;\
PORTDCLK.OUTSET = 1 << DCLK; PORTDCLK.OUTCLR = 1 << DCLK;

u8b ALTERAload(void)
{
	__watchdog_reset();
	/* Сброс предыдущего состояния ПЛИС */
	OutputPinWith0 (NCONF);
	/* Ожидание завершения сброса */
	do __delay_cycles(uS(10.0));
	while (PORTNSTAT.IN & (1<<NSTAT));

	/* Ожидание готовности ПЛИС к новой загрузке */
	do __delay_cycles(uS(10.0));
	while (PORTCONFD.IN & (1<<CONFD));
	__delay_cycles(mS(1.0));

	/* Запрос на начало процесса загрузки прошивки */
	OutputPinWith1 (NCONF);
	__delay_cycles(mS(1.0));
	/* Ожидание ответа */
		do __delay_cycles(uS(10.0));
		while ((PORTNSTAT.IN & (1<<NSTAT)) == 0);
	__watchdog_reset();
	__delay_cycles(uS(1.0));

	/* Передача данных из флеш */

	/* Активация запроса к Флеш */
	OutputPinWith0 (FSS);
	/*  */
	ByteFlashTransmit(ReadDataS25Instruction);
	/* Передача начального адреса в памяти флеш 0x00000000 для данного проекта */
	ByteFlashTransmit(0);
	ByteFlashTransmit(0);
	ByteFlashTransmit(0);
	do{
		/* сброс сторожевого таймера */
		__watchdog_reset();
		/* Перекачка данных из флеш в ПЛИС */
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		DMATransmit
		/* В процессе передачи произошла ошибка - выходим из функции
		и возвращаем 0 */
		if (!(PORTNSTAT.IN & (1<<NSTAT)))
		return 0;
		}while (!(PORTCONFD.IN & (1<<CONFD)));
		
		/* Закрываем транзакцию передачи данных из флеш */
		OutputPinWith1 (FSS);
		/* Выход из функции - возвращаем 1 */
		return 1;
}

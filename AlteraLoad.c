void ALTERAload(void)
  {
	u8b register low_FSCK, high_FSCK, low_DCLK, high_DCLK;
  __watchdog_reset();
  __delay_cycles(mS(10.0));

	/* Проверка предыдущего состояния ПЛИС */
	OutputPinWith0 (NCONF);
	do __delay_cycles(uS(10.0));
	while (PORTNSTAT.IN & (1<<NSTAT));

	/* Проверка предыдущего состояния ПЛИС */
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
	/* Передача начального адреса в памяти флеш  */
	ByteFlashTransmit(0);
	ByteFlashTransmit(0);
	ByteFlashTransmit(0);

	low_FSCK = (PORTFSCK.OUT & ~(1<<FSCK));
	high_FSCK = (PORTFSCK.OUT | (1<<FSCK));
	high_DCLK = (PORTDCLK.OUT | (1<<DCLK));
	low_DCLK = (PORTDCLK.OUT & ~(1<<DCLK));

	if ((PORT_t *)&PORTFSCK == (PORT_t *)&PORTA)
	{VirtualPort(0, 0);}
	else
	if ((PORT_t *)&PORTFSCK == (PORT_t *)&PORTB)
	{VirtualPort(0, 1);}
	else
	if ((PORT_t *)&PORTFSCK == (PORT_t *)&PORTC)
	{VirtualPort(0, 2);}
	else
	if ((PORT_t *)&PORTFSCK == (PORT_t *)&PORTD)
	{VirtualPort(0, 3);}
	else
	if ((PORT_t *)&PORTFSCK == (PORT_t *)&PORTE)
	{VirtualPort(0, 4);}
	else
	if ((PORT_t *)&PORTFSCK == (PORT_t *)&PORTF)
	{VirtualPort(0, 5);}
	else {VirtualPort(0, 9);}
	#define VIRTFSCK VPORT0

	if ((PORT_t *)&PORTDCLK == (PORT_t *)&PORTA)
	{VirtualPort(1, 0);}
	else
	if ((PORT_t *)&PORTDCLK == (PORT_t *)&PORTB)
	{VirtualPort(1, 1);}
	else
	if ((PORT_t *)&PORTDCLK == (PORT_t *)&PORTC)
	{VirtualPort(1, 2);}
	else
	if ((PORT_t *)&PORTDCLK == (PORT_t *)&PORTD)
	{VirtualPort(1, 3);}
	else
	if ((PORT_t *)&PORTDCLK == (PORT_t *)&PORTE)
	{VirtualPort(1, 4);}
	else
	if ((PORT_t *)&PORTDCLK == (PORT_t *)&PORTF)
	{VirtualPort(1, 5);}
	else
	if ((PORT_t *)&PORTDCLK == (PORT_t *)&PORTH)
	{VirtualPort(1, 7);}
	else{VirtualPort(1, 9);}
	#define VIRTDCLK VPORT1

         do
         { __watchdog_reset();
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
			  if (!(PORTNSTAT.IN & (1<<NSTAT)))
			  JumpToZeroCode();
		 }
         while (!(PORTCONFD.IN & (1<<CONFD)));

  OutputPinWith1 (FSS);
  __delay_cycles(mS(10.0));
  __watchdog_reset();
  }




/* Инициализация таймера с прерыванием каждые 20 миллисекунд */
InitCounterNorm(&TCC0, 20000.0, 0x02);



#pragma vector = TCC0_OVF_vect
__interrupt void SysTimer(void)
{	__watchdog_reset();
	
	/*	Определение количества циклов стабильного
		состояния	для борьбы с дребезгом контактов
	*/
	#define MaxScanDelay	5
	/* Внутренние переменные функции сканирования состояния порта */
	static u8b Rot_Value,Rot_oldValue,ScanDelay2,PrevButton2;

	/* Считывание текущего состояния регистра порта */
	Rot_Value = PORTB.IN;
	/* Текущее значение не равно предыдущему*/
	if(Rot_Value != Rot_oldValue)
	{
		ClrFlag(FlagsScanner,FlRotEqual);
	}

	/* Состояние не изменилось в текущем цикле */
	if (CheckFlag(FlagsScanner, FlRotEqual))
	{
		/*	Состояние кнопки не менялось в течении установленного 
			интервала - защита от дребезга контактов
		*/
		if (ScanDelay2 >= MaxScanDelay)
		{
			/*	Текущее стабильное состояние 
				кнопки отличается от предыдущего 
			*/
			if(PrevButton2 != Rot_Value)
			{
				/* Установка внутреннего флага сканирования */
				SetFlag(FlagsScanner, FlRotEqual);
				/*	Установка флага готовности нового состояния 
					переключателя для основной программы
				*/
				SetFlag(FlagsScanner, FlRotReady);
				/* Запись нового значения в глобальную переменную */
				RotState = Rot_Value;
				PrevButton2 = Rot_Value;
			}
		}
		else
		{
			/* Выдержка интервала для защиты от дребезга контактов */
			ScanDelay2++;
		}
		
	}
	else
	{
		/* Сброс счетчика защиты от дребезга контактов */
		ScanDelay2 = 0;
		SetFlag(FlagsScanner, FlRotEqual);
	}
	/* Замена предыдущего состояния текущим */
	Rot_oldValue = Rot_Value;
}



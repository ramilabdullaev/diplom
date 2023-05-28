


/* ������������� ������� � ����������� ������ 20 ����������� */
InitCounterNorm(&TCC0, 20000.0, 0x02);



#pragma vector = TCC0_OVF_vect
__interrupt void SysTimer(void)
{	__watchdog_reset();
	
	/*	����������� ���������� ������ �����������
		���������	��� ������ � ��������� ���������
	*/
	#define MaxScanDelay	5
	/* ���������� ���������� ������� ������������ ��������� ����� */
	static u8b Rot_Value,Rot_oldValue,ScanDelay2,PrevButton2;

	/* ���������� �������� ��������� �������� ����� */
	Rot_Value = PORTB.IN;
	/* ������� �������� �� ����� �����������*/
	if(Rot_Value != Rot_oldValue)
	{
		ClrFlag(FlagsScanner,FlRotEqual);
	}

	/* ��������� �� ���������� � ������� ����� */
	if (CheckFlag(FlagsScanner, FlRotEqual))
	{
		/*	��������� ������ �� �������� � ������� �������������� 
			��������� - ������ �� �������� ���������
		*/
		if (ScanDelay2 >= MaxScanDelay)
		{
			/*	������� ���������� ��������� 
				������ ���������� �� ����������� 
			*/
			if(PrevButton2 != Rot_Value)
			{
				/* ��������� ����������� ����� ������������ */
				SetFlag(FlagsScanner, FlRotEqual);
				/*	��������� ����� ���������� ������ ��������� 
					������������� ��� �������� ���������
				*/
				SetFlag(FlagsScanner, FlRotReady);
				/* ������ ������ �������� � ���������� ���������� */
				RotState = Rot_Value;
				PrevButton2 = Rot_Value;
			}
		}
		else
		{
			/* �������� ��������� ��� ������ �� �������� ��������� */
			ScanDelay2++;
		}
		
	}
	else
	{
		/* ����� �������� ������ �� �������� ��������� */
		ScanDelay2 = 0;
		SetFlag(FlagsScanner, FlRotEqual);
	}
	/* ������ ����������� ��������� ������� */
	Rot_oldValue = Rot_Value;
}



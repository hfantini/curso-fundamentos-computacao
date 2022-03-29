wchar_t* convertByteToBinaryNotation( unsigned char value )
{
	wchar_t* retValue = new wchar_t[9]{ L'0', L'0', L'0', L'0', L'0', L'0', L'0', L'0', L'\0' };

	if (value == 0)
	{
		return retValue;
	}
	else if (value > 255)
	{
		for (int count = 0; count < 8; count++)
		{
			retValue[count] = L'?';
		}
	}
	else
	{
		char count = 0;
		unsigned char quocient = value;
		unsigned char remainder = -1;

		do 
		{
			remainder = quocient % 2;
			quocient = quocient / 2;
			
			retValue[7 - count] = (remainder == 0 ? L'0' : L'1');

			count++;

		} while (quocient > 1);

		retValue[7 - count] = (quocient == 0 ? L'0' : L'1');
	}

	return retValue;
}
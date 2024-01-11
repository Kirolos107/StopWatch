#include <util/delay.h>
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "CLCD_interface.h"

/********************************************************************************************/
/********************************************************************************************/
void STW_voidStartScreen(void)
{
	CLCD_voidSendCmd(1);
	CLCD_voidGoToXY(2, 0);
	CLCD_u8SendString(" 'StopWatch'");
	_delay_ms(2000);

	CLCD_voidSendCmd(1);
	CLCD_voidGoToXY(3, 0);
	CLCD_u8SendString("Created By");
	CLCD_voidGoToXY(1,1);
	CLCD_u8SendString("'Kirolos Milad'");
	_delay_ms(2000);

	CLCD_voidSendCmd(1);
	CLCD_voidGoToXY(0, 0);
	CLCD_u8SendString("Please, Enter ");
	CLCD_voidGoToXY(0, 1);
	CLCD_u8SendString("The Duration '-'");
	_delay_ms(2000);
}
/********************************************************************************************/
/********************************************************************************************/
void STW_voidInterface(uint8 Copy_u8Seconds, uint8 Copy_u8Minutes, uint8 Copy_u8Hours)
{
	if(Copy_u8Seconds < 10)
	{
		CLCD_voidGoToXY(10,0);
		CLCD_voidSendData('0');

		CLCD_voidGoToXY(11,0);
		CLCD_voidSendNumber(Copy_u8Seconds);
	}
	else
	{
		CLCD_voidGoToXY(10,0);
		CLCD_voidSendNumber(Copy_u8Seconds);
	}


	if(Copy_u8Minutes < 10)
	{
		CLCD_voidGoToXY(7,0);
		CLCD_voidSendData('0');

		CLCD_voidGoToXY(8,0);
		CLCD_voidSendNumber(Copy_u8Minutes);
	}
	else
	{
		CLCD_voidGoToXY(7,0);
		CLCD_voidSendNumber(Copy_u8Minutes);
	}


	CLCD_voidGoToXY(9,0);
	CLCD_voidSendData(':');

	CLCD_voidGoToXY(6,0);
	CLCD_voidSendData(':');


	if(Copy_u8Hours < 10)
	{
		CLCD_voidGoToXY(4,0);
		CLCD_voidSendData('0');

		CLCD_voidGoToXY(5,0);
		CLCD_voidSendNumber(Copy_u8Hours);
	}
	else
	{
		CLCD_voidGoToXY(4,0);
		CLCD_voidSendNumber(Copy_u8Hours);
	}
}
/********************************************************************************************/
/********************************************************************************************/
void STW_voidPutSeconds(uint8 Copy_u8Sec_Iterator)
{
	if(Copy_u8Sec_Iterator < 10)
	{
		CLCD_voidGoToXY(10,0);
		CLCD_voidSendData('0');

		CLCD_voidGoToXY(11,0);
		CLCD_voidSendNumber(Copy_u8Sec_Iterator);
		_delay_ms(5);
	}
	else
	{
		CLCD_voidGoToXY(10,0);
		CLCD_voidSendNumber(Copy_u8Sec_Iterator);
		_delay_ms(5);
	}
}
/********************************************************************************************/
/********************************************************************************************/
void STW_voidPutMinutes(uint8 Copy_u8Minutes)
{
	if(Copy_u8Minutes < 10)
	{
		CLCD_voidGoToXY(7,0);
		CLCD_voidSendData('0');

		CLCD_voidGoToXY(8,0);
		CLCD_voidSendNumber(Copy_u8Minutes);
		_delay_ms(5);
	}
	else
	{
		CLCD_voidGoToXY(7,0);
		CLCD_voidSendNumber(Copy_u8Minutes);
		_delay_ms(5);
	}
}
/********************************************************************************************/
/********************************************************************************************/
void STW_voidPutHours(uint8 Copy_u8Hours)
{
	if(Copy_u8Hours < 10)
	{
		CLCD_voidGoToXY(4,0);
		CLCD_voidSendData('0');

		CLCD_voidGoToXY(5,0);
		CLCD_voidSendNumber(Copy_u8Hours);
		_delay_ms(5);
	}
	else
	{
		CLCD_voidGoToXY(4,0);
		CLCD_voidSendNumber(Copy_u8Hours);
		_delay_ms(5);
	}
}
/********************************************************************************************/
/********************************************************************************************/
uint8 STW_u8DecrementDuration(uint8* Copy_p8Sec_Iterator, uint8* Copy_u8Minutes, uint8* Copy_u8Hours)
{
	if((*Copy_u8Hours == 0) && (*Copy_u8Minutes == 0u) && (*Copy_p8Sec_Iterator == 0u))
	{
		return 0;
	}
	else if((*Copy_u8Minutes == 0u) && (*Copy_p8Sec_Iterator == 0u))
	{
		*Copy_u8Hours -= 1;
		*Copy_u8Minutes = 60;
		*Copy_p8Sec_Iterator = 60;
	}
	else if(*Copy_p8Sec_Iterator == 0u)
	{
		*Copy_u8Minutes -= 1;
		*Copy_p8Sec_Iterator = 60;
	}

	STW_voidPutMinutes(*Copy_u8Minutes);

	STW_voidPutHours(*Copy_u8Hours);

	return 1;
}
/********************************************************************************************/
/********************************************************************************************/
void STW_voidGetHoursDuration(uint8* Copy_pu8Hours)
{
	uint8 Local_u8Iterator;
	uint8 Local_u8Exit_Iterator;
	uint8 Local_u8New = 0u;
	uint8 Local_u8It = 1u;
	uint8 Local_u8DurationNum = 0u;
	uint8 Local_u8KeypadKey_Arr[3];

	CLCD_voidGoToXY(0, 0);
	CLCD_u8SendString("Hours : ");

	CLCD_voidGoToXY(8, 0);
	for(Local_u8Iterator = 0u; Local_u8Iterator < 3; Local_u8Iterator++)
	{
		do
		{
			Local_u8KeypadKey_Arr[Local_u8Iterator] = KPD_u8GetPressedKey();
			if(Local_u8KeypadKey_Arr[Local_u8Iterator] == 61)
			{
				Local_u8Exit_Iterator = Local_u8Iterator;
				break;
			}

		}while(Local_u8KeypadKey_Arr[Local_u8Iterator] == 0xff);

		if(Local_u8KeypadKey_Arr[Local_u8Iterator] == 61)
		{
			break;
		}
		CLCD_voidSendNumber(Local_u8KeypadKey_Arr[Local_u8Iterator]);
	}

	for(Local_u8Iterator = 0u; Local_u8Iterator < Local_u8Exit_Iterator; Local_u8Iterator++)
	{
		Local_u8New = Local_u8KeypadKey_Arr[Local_u8Exit_Iterator - 1 - Local_u8Iterator] * Local_u8It;
		Local_u8DurationNum += Local_u8New;
		Local_u8It *= 10;
	}

	*Copy_pu8Hours = Local_u8DurationNum;
}
/********************************************************************************************/
/********************************************************************************************/
void STW_voidGetMinutesDuration(uint8* Copy_pu8Minutes)
{
	uint8 Local_u8Iterator;
	uint8 Local_u8Exit_Iterator;
	uint8 Local_u8New = 0u;
	uint8 Local_u8It = 1u;
	uint8 Local_u8DurationNum = 0u;
	uint8 Local_u8KeypadKey_Arr[3];

	CLCD_voidGoToXY(0, 0);
	CLCD_u8SendString("Minutes : ");

	CLCD_voidGoToXY(10, 0);
	for(Local_u8Iterator = 0u; Local_u8Iterator < 3; Local_u8Iterator++)
	{
		do
		{
			Local_u8KeypadKey_Arr[Local_u8Iterator] = KPD_u8GetPressedKey();
			if(Local_u8KeypadKey_Arr[Local_u8Iterator] == 61)
			{
				Local_u8Exit_Iterator = Local_u8Iterator;
				break;
			}

		}while(Local_u8KeypadKey_Arr[Local_u8Iterator] == 0xff);

		if(Local_u8KeypadKey_Arr[Local_u8Iterator] == 61)
		{
			break;
		}
		CLCD_voidSendNumber(Local_u8KeypadKey_Arr[Local_u8Iterator]);
	}

	for(Local_u8Iterator = 0u; Local_u8Iterator < Local_u8Exit_Iterator; Local_u8Iterator++)
	{
		Local_u8New = Local_u8KeypadKey_Arr[Local_u8Exit_Iterator - 1 - Local_u8Iterator] * Local_u8It;
		Local_u8DurationNum += Local_u8New;
		Local_u8It *= 10;
	}

	*Copy_pu8Minutes = Local_u8DurationNum;
}
/********************************************************************************************/
/********************************************************************************************/
void STW_voidGetSecondsDuration(uint8* Copy_pu8Seconds)
{
	uint8 Local_u8Iterator;
	uint8 Local_u8Exit_Iterator;
	uint8 Local_u8New = 0u;
	uint8 Local_u8It = 1u;
	uint8 Local_u8DurationNum = 0u;
	uint8 Local_u8KeypadKey_Arr[3];

	CLCD_voidGoToXY(0, 0);
	CLCD_u8SendString("Seconds : ");

	CLCD_voidGoToXY(10, 0);
	for(Local_u8Iterator = 0u; Local_u8Iterator < 3; Local_u8Iterator++)
	{
		do
		{
			Local_u8KeypadKey_Arr[Local_u8Iterator] = KPD_u8GetPressedKey();
			if(Local_u8KeypadKey_Arr[Local_u8Iterator] == 61)
			{
				Local_u8Exit_Iterator = Local_u8Iterator;
				break;
			}

		}while(Local_u8KeypadKey_Arr[Local_u8Iterator] == 0xff);

		if(Local_u8KeypadKey_Arr[Local_u8Iterator] == 61)
		{
			break;
		}
		CLCD_voidSendNumber(Local_u8KeypadKey_Arr[Local_u8Iterator]);
	}

	for(Local_u8Iterator = 0u; Local_u8Iterator < Local_u8Exit_Iterator; Local_u8Iterator++)
	{
		Local_u8New = Local_u8KeypadKey_Arr[Local_u8Exit_Iterator - 1 - Local_u8Iterator] * Local_u8It;
		Local_u8DurationNum += Local_u8New;
		Local_u8It *= 10;
	}

	*Copy_pu8Seconds = Local_u8DurationNum;
}
/********************************************************************************************/
/********************************************************************************************/
void STW_voidUserChoice(uint8* Copy_pu8UserChoice)
{
	CLCD_voidSendCmd(1);
	CLCD_voidGoToXY(0,0);
	CLCD_u8SendString("Time Is Finished");
	CLCD_voidGoToXY(7,1);
	CLCD_u8SendString("(:");
	DIO_u8SetPinDirection(DIO_u8PORTC, DIO_u8PIN5, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN5, DIO_u8PIN_HIGH);
	_delay_ms(1000);

	CLCD_voidSendCmd(1);
	CLCD_voidGoToXY(0,0);
	CLCD_u8SendString("To Restart (1)");
	CLCD_voidGoToXY(0,1);
	CLCD_u8SendString("To Exit (0) : ");

	CLCD_voidGoToXY(14, 1);
	do
	{
		*Copy_pu8UserChoice = KPD_u8GetPressedKey();

	}while(*Copy_pu8UserChoice == 0xff);
	CLCD_voidSendNumber(*Copy_pu8UserChoice);
	_delay_ms(500);

	if(*Copy_pu8UserChoice == 1)
	{
		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN5, DIO_u8PIN_LOW);

		*Copy_pu8UserChoice = 1u;
	}
	else if(*Copy_pu8UserChoice == 0u)
	{
		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN5, DIO_u8PIN_LOW);

		CLCD_voidSendCmd(1);
		CLCD_voidGoToXY(4,0);
		CLCD_u8SendString("GoodBye !");
		_delay_ms(2000);
		CLCD_voidSendCmd(1);
	}
}

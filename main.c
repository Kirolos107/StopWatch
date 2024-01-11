#include <util/delay.h>
#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"

#include "App.h"

void main(void)
{
	PORT_voidInit();

	CLCD_voidInit();

	uint8 STW_u8Seconds;
	uint8 STW_u8Minutes;
	uint8 STW_u8Hours;

	uint8 STW_u8Sec_Iterator = 0u;

	uint8 STW_u8User_Choice;
	uint8 STW_u8Program_Status = 1u;


	while(1)
	{
		if(STW_u8Program_Status == 0)
		{
			break;
		}

		STW_voidStartScreen();

		CLCD_voidSendCmd(1);
		STW_voidGetHoursDuration(&STW_u8Hours);

		CLCD_voidSendCmd(1);
		STW_voidGetMinutesDuration(&STW_u8Minutes);

		CLCD_voidSendCmd(1);
		STW_voidGetSecondsDuration(&STW_u8Seconds);

		CLCD_voidSendCmd(1);
		STW_voidInterface(STW_u8Seconds, STW_u8Minutes, STW_u8Hours);

		for(STW_u8Sec_Iterator = STW_u8Seconds; STW_u8Sec_Iterator >= 0u; STW_u8Sec_Iterator--)
		{
			if(STW_u8Program_Status == 0)
			{
				break;
			}

			STW_voidPutSeconds(STW_u8Sec_Iterator);

			STW_u8Program_Status = STW_u8DecrementDuration(&STW_u8Sec_Iterator, &STW_u8Minutes, &STW_u8Hours);
		}

		STW_voidUserChoice(&STW_u8Program_Status);
	}
}





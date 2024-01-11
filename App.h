#ifndef APP_H_
#define APP_H_

void STW_voidStartScreen(void);

void STW_voidInterface(uint8 Copy_u8Seconds, uint8 Copy_u8Minutes, uint8 Copy_u8Hours);

void STW_voidPutSeconds(uint8 Copy_u8Sec_Iterator);

void STW_voidPutMinutes(uint8 Copy_u8Minutes);

void STW_voidPutHours(uint8 Copy_u8Hours);

uint8 STW_u8DecrementDuration(uint8* Copy_p8Sec_Iterator, uint8* Copy_u8Minutes, uint8* Copy_u8Hours);

void STW_voidGetHoursDuration(uint8* Copy_pu8Hours);

void STW_voidGetMinutesDuration(uint8* Copy_pu8Minutes);

void STW_voidGetSecondsDuration(uint8* Copy_pu8Seconds);

void STW_voidUserChoice(uint8* Copy_pu8UserChoice);

#endif

/*
	Истомин А.О., задержки для STM32xxx
	Версия:	1.0
	Дата:		11.02.2022
*/

#ifndef __DWTDELAY_H
#define __DWTDELAY_H

/*
	НЕ ЗАБЫВАЕМ НАСТРОИТЬ параметры в файле DWTDelay.c, а так же помним,
	что вызов DWT_Init() необходимо делать после HAL_Init() & SystemClock_Config()!
	Так же, если используем задержки для работы ногодрыгом, выставить максимальную скорость GPIO.
*/

#include "stdint.h"

// Инициализация
void DWT_Init(void);
// Задержка в секундах
void DWT_Delay_sec(uint32_t Sec);
// Задержка в миллисекундах
void DWT_Delay_ms(uint32_t mSec);
// Задержка в микросекундах
void DWT_Delay_us(uint32_t uSec);
// Инициализирован ?
uint8_t DWT_Inited(void);

#endif

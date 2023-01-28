#include "DWTDelay.h"
#include "stm32f1xx_hal.h"

/*
	Число циклов ядра на присвоение и умножение в начале функции задержки.
	Подбирать при помощи хорошего осцилографа /логического анализатора если требуется прицизная точность,
	cледует учитывать что значение должно быть меньше < (SystemCoreClock / 1000000).
	Так же можно поиграться с уровнем оптимизации компилятора, для подстройки точности.
	Калибровку лучше всего проводить дерганием пина, с задежкой например 5 мкСек подгоняя до максимально
	близкого значения при помощи BASE_CYCLES_COUNT и O*...
*/
#define BASE_CYCLES_COUNT 51ul

extern uint32_t SystemCoreClock;						// Частота ядра в Герцах
static uint32_t Delay_us = 0, Delay_ms = 0;

// Обновляет множители тактов
void DWT_DelayUpdate(void)
{
    Delay_ms = SystemCoreClock / 1000;			// Число тактов ядра за миллисекунду.
    Delay_us = SystemCoreClock / 1000000;		// Число тактов ядра за микросекунду.
}

// Настройка и включение DWT
void DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT_DelayUpdate();
}

// [!] УРОВЕНЬ ОПТИМИЗАЦИИ ФНКЦИЙ ЗАДЕРЖКИ, НЕ ДОЛЖЕН ЗАВИСИТЬ ОТ УРОВНЯ ПРОЕКТА.
#pragma push
#pragma O3

// Задержка в секундах
void DWT_Delay_sec(uint32_t Sec)
{
    uint32_t Count = DWT->CYCCNT;
    Sec *= SystemCoreClock;
    while((DWT->CYCCNT - Count) < Sec);
}

// Задержка в миллисекундах
void DWT_Delay_ms(uint32_t mSec)
{
    if (mSec == 0) return;
		uint32_t Count = DWT->CYCCNT;
    mSec *= Delay_ms;
		mSec -= BASE_CYCLES_COUNT;
    while((DWT->CYCCNT - Count) < mSec);
}

// Задержка в микросекундах
void DWT_Delay_us(uint32_t uSec)
{
		if (uSec == 0) return;
    uint32_t Count = DWT->CYCCNT;
    uSec *= Delay_us;
		uSec -= BASE_CYCLES_COUNT;
    while((DWT->CYCCNT - Count) < uSec);
}

#pragma pop 

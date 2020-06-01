#include "STD_TYPES.h"
#include "Timer.h"

#define TCCR0 *((u8*)0x53)
#define TCNT0 *((u8*)0x52)

#define TIMER0_NORMAL_MODE         (0xB7)
#define TIMER0_CLK_NO_PRESCALING   (0x01)

void TIMER0_init(void)
{
	TCCR0 &= TIMER0_NORMAL_MODE;
	TCCR0 |= TIMER0_CLK_NO_PRESCALING;
}


u8 TIMER0_getCount(void)
{
	return TCNT0;
}

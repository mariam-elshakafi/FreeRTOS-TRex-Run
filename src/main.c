#include "STD_TYPES.h"
#include "GAME.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"


int main(void)
{

	LCD_init();
	SWITCH_init();
	GAME_init();

	vTaskStartScheduler();

	while(1)
	{

	}
}

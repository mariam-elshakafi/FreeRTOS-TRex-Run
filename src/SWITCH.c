#include "STD_TYPES.h"
#include "GPIO.h"
#include "SWITCH.h"
#include "SWITCH_CFG.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Switch task info */
#define TASK_SWITCH_FREQUENCY 	    	(5)
#define TASK_SWITCH_PRIORITY	    	(3)


volatile u8 SWITCH_state = SWITCH_NOT_PRESSED;

static void Task_Switch( void *pvParameters );

void SWITCH_init(void)
{

	GPIO_SetPinDir(SWITCH_PORT, SWITCH_PIN, GPIO_DIR_IN_PULLUP);

	xTaskCreate( Task_Switch,
			"Task_S",
			100,
			NULL,
			TASK_SWITCH_PRIORITY,
			NULL );
}


u8 SWITCH_GetSwitchValue(void)
{
	return SWITCH_state;
}



static void Task_Switch( void *pvParameters )
{
	static u8 prevState;
	static u8 counter;
	u8 currentState;

	while(1)
	{
		GPIO_GetPinVal(SWITCH_PORT, SWITCH_PIN, &currentState);
		if (currentState == prevState)
		{
			counter++;
		}
		else
		{
			counter = 0;
		}

		if (counter == 4)
		{
			SWITCH_state = currentState;
			counter = 0;
		}

		prevState = currentState;
		vTaskDelay(TASK_SWITCH_FREQUENCY);
	}
}

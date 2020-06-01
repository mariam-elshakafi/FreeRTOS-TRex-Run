#include "STD_TYPES.h"
#include <stdlib.h>

#include "LCD.h"
#include "SWITCH.h"
#include "Timer.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"


/* Values for obstacle position */
#define OBSTACLE_NONE            (0)
#define OBSTACLE_GROUND          (1)
#define OBSTACLE_AIR             (2)

/* Values of playerHitPos flag */
#define PLAYER_HIT_POS_UP         (1)
#define PLAYER_HIT_POS_DOWN       (0)

/* Priorities at which the tasks are created. */
#define TASK_PLAYER_PRIORITY		(1)
#define TASK_OBSTACLES_PRIORITY		(2)
#define TASK_GAMEOVER_PRIORITY		(4)


/* The times are converted from milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define TASK_PLAYER_FREQUENCY			(500)
#define TASK_OBSTACLES_FREQUENCY 	  	(100)
#define TASK_GAMEOVER_FREQUENCY 	  	(100)


SemaphoreHandle_t lcdSem;
u8 playerHitPos = PLAYER_HIT_POS_DOWN;
u32 score = 0;

TaskHandle_t PlayerHandle;
TaskHandle_t ObsHandle;

static void Task_Player( void *pvParameters );
static void Task_Obstacles( void *pvParameters );
static void Task_GameOver( void *pvParameters );


void GAME_init(void)
{
	lcdSem = xSemaphoreCreateBinary();

	/* Used for random number generation */
	TIMER0_init();

	xTaskCreate( Task_Player,
			"Task_P",
			100,
			NULL,
			TASK_PLAYER_PRIORITY,
			&PlayerHandle );


	xTaskCreate( Task_Obstacles,
			"Task_O",
			100,
			NULL,
			TASK_OBSTACLES_PRIORITY,
			&ObsHandle );

	xTaskCreate( Task_GameOver,
			"Task_G",
			100,
			NULL,
			TASK_GAMEOVER_PRIORITY,
			NULL );
}

static void Task_Player( void *pvParameters )
{

	static volatile u8 count = 0;

	while(1)
	{
		count ^= 1;

		if(count)
		{
			LCD_SetCGRAM(MAN_WALKING, 0b01000000);
		}
		else
		{
			LCD_SetCGRAM(MAN_SWITCHING_LEGS, 0b01000000);
		}

		if(SWITCH_GetSwitchValue() == SWITCH_PRESSED)
		{
			LCD_writeCmd(LCD_LINE_2);
			LCD_writeData('_');
			LCD_writeCmd(LCD_LINE_1);
			playerHitPos = PLAYER_HIT_POS_UP;
		}
		else
		{
			LCD_writeCmd(LCD_LINE_1);
			LCD_writeData(' ');
			LCD_writeCmd(LCD_LINE_2);
			playerHitPos = PLAYER_HIT_POS_DOWN;
		}

		LCD_writeData(0);
		vTaskDelay(TASK_PLAYER_FREQUENCY);
	}
}

static void Task_Obstacles( void *pvParameters )
{
	static u8 obsPos[16] = {0};
	static u8 changeTime = 5;
	static u8 speedCount;

	while(1)
	{

		/* Draw obstacles */
		for( u8 i = 1; i < 16; i++)
		{
			/* Ground Obstacle */
			if(obsPos[i] == OBSTACLE_GROUND)
			{
				LCD_writeCmd(LCD_LINE_1 | i);
				LCD_writeData(' ');
				LCD_writeCmd(LCD_LINE_2 | i);
				LCD_writeData('|');
			}
			/* Air Obstacle */
			else if(obsPos[i] == OBSTACLE_AIR)
			{
				LCD_writeCmd(LCD_LINE_2 | i);
				LCD_writeData('_');
				LCD_writeCmd(LCD_LINE_1 | i);
				LCD_writeData('|');
			}
			/* No obstacles */
			else
			{
				LCD_writeCmd(LCD_LINE_1 | i);
				LCD_writeData(' ');
				LCD_writeCmd(LCD_LINE_2 | i);
				LCD_writeData('_');
			}
		}

		/* Change speed according to score */
		speedCount++;
		if (speedCount == changeTime)
		{
			/* Update obstacle array for next time */
			for( u8 i = 0; i < 15; i++)
			{
				obsPos[i] = obsPos[i+1];
			}

			/* Randomly generate a new obstacle, evading impossible situations */
			if( obsPos[14] == 1 )
			{
				obsPos[15] = TIMER0_getCount() % 2;
			}
			else if( obsPos[14] == 2)
			{
				obsPos[15] = (TIMER0_getCount() % 2) * OBSTACLE_AIR;
			}
			else
			{
				obsPos[15] = TIMER0_getCount() % 3;
			}

			speedCount = 0;

			if (((playerHitPos == PLAYER_HIT_POS_DOWN) && (obsPos[0] == 1)) || ((playerHitPos == PLAYER_HIT_POS_UP) && (obsPos[0] == 2)))
			{
				xSemaphoreGive(lcdSem);
			}
			else if (((playerHitPos == PLAYER_HIT_POS_UP) && (obsPos[0] == 1)) || ((playerHitPos == PLAYER_HIT_POS_DOWN) && (obsPos[0] == 2)))
			{
				score++;
				if (((score % 3) == 0) && changeTime > 2)
				{
					changeTime--;
				}
			}
		}

		vTaskDelay(TASK_OBSTACLES_FREQUENCY);
	}
}


static void Task_GameOver( void *pvParameters )
{
	while(1)
	{
		char scoreStr[4];
		if(xSemaphoreTake(lcdSem, TASK_GAMEOVER_FREQUENCY) == pdTRUE)
		{
			vTaskDelete(PlayerHandle);
			vTaskDelete(ObsHandle);
			LCD_writeCmd(LCD_CLEAR_SCREEN);
			LCD_writeStr("Game Over!");
			LCD_writeCmd(LCD_LINE_2);
			LCD_writeStr("Score: ");
			itoa (score, scoreStr, 10);
			LCD_writeStr(scoreStr);
		}
	}
}

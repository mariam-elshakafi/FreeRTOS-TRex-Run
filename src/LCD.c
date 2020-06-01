#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define F_CPU         (16000000)
#include <util/delay.h>

#include "GPIO.h"
#include "LCD.h"
#include "LCD_CFG.h"

static void LCD_writePort(u8 data);

void LCD_init(void)
{
	volatile u32 i = 0;

	GPIO_SetPinDir(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_DIR_OUT);
	GPIO_SetPinDir(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_DIR_OUT);

	GPIO_SetPinDir(LCD_DATA_PORT, LCD_D4_PIN, GPIO_DIR_OUT);
	GPIO_SetPinDir(LCD_DATA_PORT, LCD_D5_PIN, GPIO_DIR_OUT);
	GPIO_SetPinDir(LCD_DATA_PORT, LCD_D6_PIN, GPIO_DIR_OUT);
	GPIO_SetPinDir(LCD_DATA_PORT, LCD_D7_PIN, GPIO_DIR_OUT);

	_delay_ms(20);
	LCD_writeCmd(0b00000010);
	LCD_writeCmd(0b00101000);
	LCD_writeCmd(0b00001100);
	LCD_writeCmd(0b00000001);
	_delay_ms(5);
}

void LCD_writeData(u8 data)
{
	u8 dataPart = data & 0xF0;
	/* RS = 1 */
	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_PIN_SET);
	LCD_writePort(dataPart);

	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_PIN_SET);
	_delay_us(1);

	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_PIN_RESET);
	_delay_us(1);


	dataPart = (data & 0x0F) << 4;

	LCD_writePort(dataPart);

	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_PIN_SET);
	_delay_us(1);

	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_PIN_RESET);
	_delay_ms(2);

}

void LCD_writeCmd(u8 cmd)
{

	u8 dataPart = cmd & 0xF0;
	/* RS =  */
	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
	LCD_writePort(dataPart);

	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_PIN_SET);
	_delay_us(1);

	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_PIN_RESET);
	_delay_us(1);


	dataPart = (cmd & 0x0F) << 4;

	LCD_writePort(dataPart);

	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_PIN_SET);
	_delay_us(1);

	GPIO_SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_PIN_RESET);
	_delay_ms(2);

}

void LCD_writeStr(u8* str)
{
	u8 counter = 0;
	for(; str[counter] != '\0'; counter++)
	{
		LCD_writeData(str[counter]);
	}
}



void LCD_SetCGRAM(u8 symbol, u8 address)
{
	LCD_writeCmd(address);
	if (symbol == MAN_WALKING)
	{
		LCD_writeData(0b00001110);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00000100);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00010001);
	}

	else if (symbol == MAN_SWITCHING_LEGS)
	{
		LCD_writeData(0b00001110);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00000100);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00001110);
		LCD_writeData(0b00000100);
	}

}


void LCD_writePort(u8 data)
{
	u8 pinVal;

	pinVal = GET_BIT(data, 4);
	GPIO_SetPinVal(LCD_DATA_PORT, LCD_D4_PIN, pinVal);

	pinVal = GET_BIT(data, 5);
	GPIO_SetPinVal(LCD_DATA_PORT, LCD_D5_PIN, pinVal);

	pinVal = GET_BIT(data, 6);
	GPIO_SetPinVal(LCD_DATA_PORT, LCD_D6_PIN, pinVal);

	pinVal = GET_BIT(data, 7);
	GPIO_SetPinVal(LCD_DATA_PORT, LCD_D7_PIN, pinVal);
}

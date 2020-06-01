#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO.h"


#define PORTA *((u8*)0x3B)
#define  DDRA *((u8*)0x3A)
#define  PINA *((u8*)0x39)

#define PORTB *((u8*)0x38)
#define  DDRB *((u8*)0x37)
#define  PINB *((u8*)0x36)

#define PORTC *((u8*)0x35)
#define  DDRC *((u8*)0x34)
#define  PINC *((u8*)0x33)

#define PORTD *((u8*)0x32)
#define  DDRD *((u8*)0x31)
#define  PIND *((u8*)0x30)


extern errStat GPIO_SetPinDir(u8 port, u8 pin, u8 dir){
  errStat status = ERR_STAT_OK;
  switch(port){
    case 'A': 
            if (dir == GPIO_DIR_IN_PULLUP)
            {
              CLR_BIT(DDRA, pin);
              SET_BIT(PORTA, pin);
            }
            else if (dir == GPIO_DIR_IN_FLOAT)
            {
              CLR_BIT(DDRA, pin);
              CLR_BIT(PORTA, pin);
            }
            else
            {
              SET_BIT(DDRA, pin);
            }
            break;
      
    case 'B': 
            if (dir == GPIO_DIR_IN_PULLUP)
            {
              CLR_BIT(DDRB, pin);
              SET_BIT(PORTB, pin);
            }
            else if (dir == GPIO_DIR_IN_FLOAT)
            {
              CLR_BIT(DDRB, pin);
              CLR_BIT(PORTB, pin);
            }
            else
            {
              SET_BIT(DDRB, pin);
            }
            break;
      
    case 'C': 
            if (dir == GPIO_DIR_IN_PULLUP)
            {
              CLR_BIT(DDRC, pin);
              SET_BIT(PORTC, pin);
            }
            else if (dir == GPIO_DIR_IN_FLOAT)
            {
              CLR_BIT(DDRC, pin);
              CLR_BIT(PORTC, pin);
            }
            else
            {
              SET_BIT(DDRC, pin);
            }
            break;
      
    case 'D': 
            if (dir == GPIO_DIR_IN_PULLUP)
            {
              CLR_BIT(DDRD, pin);
              SET_BIT(PORTD, pin);
            }
            else if (dir == GPIO_DIR_IN_FLOAT)
            {
              CLR_BIT(DDRD, pin);
              CLR_BIT(PORTD, pin);
            }
            else
            {
              SET_BIT(DDRD, pin);
            }
            break;
    default:
            status = ERR_STAT_NOK;
            break;
  }
  return status;
}



extern errStat GPIO_SetPinVal(u8 port, u8 pin, u8 val){
  errStat status = ERR_STAT_OK;
  switch(port){
    case 'A': 
            if (val == GPIO_PIN_RESET)
            {
              CLR_BIT(PORTA, pin);
            }
            else
            {
              SET_BIT(PORTA, pin);
            }
            break;
      
    case 'B': 
            if (val == GPIO_PIN_RESET)
            {
              CLR_BIT(PORTB, pin);
            }
            else
            {
              SET_BIT(PORTB, pin);
            }
            break;
      
    case 'C': 
            if (val == GPIO_PIN_RESET)
            {
              CLR_BIT(PORTC, pin);
            }
            else
            {
              SET_BIT(PORTC, pin);
            }
            break;
      
    case 'D': 
            if (val == GPIO_PIN_RESET)
            {
              CLR_BIT(PORTD, pin);
            }
            else
            {
              SET_BIT(PORTD, pin);
            }
            break;
    default:
            status = ERR_STAT_NOK;
            break;
  }
  return status;
}

extern errStat GPIO_GetPinVal(u8 port, u8 pin, u8 *val){
  errStat status = ERR_STAT_OK;
  switch(port){
    case 'A': 
            *val = GET_BIT(PINA, pin);
            break;
      
    case 'B': 
            *val = GET_BIT(PINB, pin);
            break;
      
    case 'C': 
            *val = GET_BIT(PINC, pin);
            break;
      
    case 'D': 
            *val = GET_BIT(PIND, pin);
            break;
    default:
            status = ERR_STAT_NOK;
            break;
  }
  return status;
}

#ifndef GPIO_H
#define GPIO_H

#define GPIO_PIN_0     0
#define GPIO_PIN_1     1
#define GPIO_PIN_2     2
#define GPIO_PIN_3     3
#define GPIO_PIN_4     4
#define GPIO_PIN_5     5
#define GPIO_PIN_6     6
#define GPIO_PIN_7     7

#define GPIO_PORT_A  'A'
#define GPIO_PORT_B  'B'
#define GPIO_PORT_C  'C'
#define GPIO_PORT_D  'D'

#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0

#define GPIO_DIR_IN_PULLUP    0
#define GPIO_DIR_IN_FLOAT     1
#define GPIO_DIR_OUT          2

extern errStat GPIO_SetPinDir(u8 port, u8 pin, u8 dir);
extern errStat GPIO_SetPinVal(u8 port, u8 pin, u8 val);
extern errStat GPIO_GetPinVal(u8 port, u8 pin, u8 *val);

#endif

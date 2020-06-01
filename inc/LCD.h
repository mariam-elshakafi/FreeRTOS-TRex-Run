#ifndef LCD_H
#define LCD_H

/* LCD Commands */
#define LCD_CLEAR_SCREEN       (0x01)
#define LCD_LINE_1             (0x80)
#define LCD_LINE_2             (0xC0)

/* Man Positions */
#define MAN_WALKING            (0)
#define MAN_SWITCHING_LEGS     (1)

extern void LCD_init(void);
extern void LCD_writeData(u8 data);
extern void LCD_writeCmd(u8 cmd);
extern void LCD_writeStr(u8* str);
extern void LCD_SetCGRAM(u8 symbol, u8 address);

#endif

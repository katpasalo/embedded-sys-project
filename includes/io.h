#ifndef __io_h__
#define __io_h__

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_WriteData (unsigned char char_data);
void LCD_Cursor (unsigned char column);
void LCD_String(char *str);
void LCD_String_xy (char row, char col, char *str);
void LCD_DisplayString(unsigned char column ,const char *string);
void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
void _delay_ms(int miliSec);
#endif


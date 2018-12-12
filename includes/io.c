#include <avr/interrupt.h>
#include <stdio.h>
#include "io.h"

/*-------------------------------------------------------------------------*/
#define LCD_Data_Dir DDRB	/* Define LCD data port direction */
#define LCD_Command_Dir DDRD	/* Define LCD command port direction register */
#define LCD_Data_Port PORTB	/* Define LCD data port */
#define LCD_Command_Port PORTD	/* Define LCD data port */
#define RS PD0			/* Define Register Select signal pin */
#define RW PD1			/* Define Read/Write signal pin */
#define EN PD2			/* Define Enable signal pin */
/*-------------------------------------------------------------------------*/

void LCD_ClearScreen() {
	LCD_WriteCommand (0x01);		/* clear display */
	LCD_WriteCommand (0x80);		/* cursor at home position */
}

void LCD_init (void) {			/* LCD Initialize function */
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_WriteCommand (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_WriteCommand (0x0C);		/* Display ON Cursor OFF */
	LCD_WriteCommand (0x06);		/* Auto Increment cursor */
	LCD_WriteCommand (0x01);		/* clear display */
	_delay_ms(2);			/* Clear display command delay> 1.63 ms */
	LCD_WriteCommand (0x80);		/* Cursor at home position */
}

void LCD_WriteCommand(unsigned char cmnd) {
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_ms(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(2);
}

void LCD_WriteData (unsigned char char_data) { /* LCD data write function */
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_ms(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(2);			/* Data write delay */
}

void LCD_String (char *str)	{	/* Send string to LCD function */
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_WriteData (str[i]);
	}
}

void LCD_String_xy (char row, char col, char *str) { /* Send string to LCD with xy position */
	if (row == 0 && col < 16)
	LCD_WriteCommand((col & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && col < 16)
	LCD_WriteCommand((col & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Cursor(unsigned char column) {
	if ( column < 17 ) { // 16x1 LCD: column < 17
		// 16x2 LCD: column < 17
		// 20x4 LCD: column < 20
		LCD_WriteCommand(0x80 + column - 1);
		} 
	else {
		LCD_WriteCommand(0xB8 + column - 9);	// 16x1 LCD: column - 1
		// 16x2 LCD: column - 9
	}
}

void LCD_DisplayString( unsigned char column, const char* string) {
	unsigned char c = column;
	while(*string) {
		LCD_Cursor(c++);
		LCD_WriteData(*string++);
	}
}

void LCD_Custom_Char (unsigned char loc, unsigned char *msg) {
	unsigned char i;
	if(loc<8)
	{
		LCD_WriteCommand (0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_WriteData(msg[i]);
	}
}

void _delay_ms(int miliSec) { //for 8 Mhz crystal 
	int i,j;
	for(i=0;i<miliSec;i++)
	for(j=0;j<775;j++)
	{
		asm("nop");
	}
}
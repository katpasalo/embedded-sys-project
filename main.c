/* 	  By: Katherine Pasalo (kpasa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Final Project
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>
#include <avr/eeprom.h>
#include "io.c"
#include "Game.h"
#include "Player.h"
#include "Ghosts.h"
#include "Attack.h"
#include "Heartpoints.h"
#include "Highscore.h"
#include "timer.h"

int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF; // Buttons
	DDRB = 0xFF; PORTB = 0x00; // LCD data lines
	DDRC = 0xFF; PORTC = 0x00; // 7 Segment LED
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	
	TimerSet(30);
	TimerOn();
	// Initializes the LCD display
	LCD_init();
	
	unsigned char girlNeutral[8] = { 0x0E, 0x0E, 0x1F, 0x04, 0x0E, 0x15, 0x0A, 0x0A };
	unsigned char girlRight[8] = { 0x0E, 0x0E, 0x0F, 0x04, 0x0F, 0x04, 0x0A, 0x0A };
	unsigned char girlLeft[8] = { 0x0E, 0x0E, 0x1E, 0x04, 0x1E, 0x04, 0x0A, 0x0A };
	
	unsigned char emptyHeart[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };
	unsigned char halfHeart[8] = { 0x00, 0x0A, 0x1D, 0x1D, 0x0E, 0x04, 0x00, 0x00 };
	unsigned char fullHeart[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 };
	
	unsigned char enemy[8] = { 0x0E, 0x1F, 0x15, 0x1F, 0x1B, 0x1B, 0x1F, 0x1F };
	
	LCD_Custom_Char(0, girlNeutral);
	LCD_Custom_Char(1, girlRight);
	LCD_Custom_Char(2, girlLeft);
	LCD_Custom_Char(3, emptyHeart);
	LCD_Custom_Char(4, halfHeart);
	LCD_Custom_Char(5, fullHeart);
	LCD_Custom_Char(6, enemy);
	
	while(1) {
		Player_Tick();
		Attack_Tick();
		Heartpoints_Tick();
		Ghosts_Tick();
		Game_Tick();
		Highscore_Tick();
		while (!TimerFlag) {}
		TimerFlag = 0;
	}
}
/* 	  By: Katherine Pasalo (kpasa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Final Project
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
enum HP_States {HP_init, HP_wait, HP_decr, HP_gameover} HP_state;

void Heartpoints_Tick() {
	
	switch (HP_state) {
		case HP_init:
			currHeart = 27;
			cntHeart = 0;
			LCD_DisplayString(17,"<ATK        L/R>");
			for (unsigned char i = 22; i < 28; i++) {
				LCD_Cursor(i);
				LCD_WriteData(5);
			}
			HP_state = HP_wait;
			break;
		case HP_wait:
			if (gameOver || gameDone || softReset) { HP_state = HP_gameover; }
			else if ((gmap[(i + n - 1) % 53]) == 6 && currHeart > 21) { cntHeart = 0; gmap[(i + n - 1) % 53] = ' '; hitMax--; hitCount--; HP_state = HP_decr; }
			else { HP_state = HP_wait; }
			break;
		case HP_decr:
			if (cntHeart < 3) {
				HP_state = HP_decr;
			}
			else {
				LCD_Cursor(currHeart);
				LCD_WriteData(3);
				currHeart--;
				if (currHeart == 21) { gameOver = 1; }
				HP_state = HP_wait;
			}
			break;
		case HP_gameover:
			if (softReset) { HP_state = HP_init; }
			else { HP_state = HP_gameover; }
			break;
	}
	switch (HP_state) {
		case HP_init:
			break;
		case HP_wait:
			break;
		case HP_decr:
			LCD_Cursor(currHeart);
			LCD_WriteData(4);
			cntHeart++;
			break;
		case HP_gameover:
			break;
	}
}
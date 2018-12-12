/* 	  By: Katherine Pasalo (kpasa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Final Project
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
enum Player_States {PLYR_init, PLYR_wait, PLYR_disp1, PLYR_disp2, PLYR_gameover} PLYR_state;

void Player_Tick() {
	tmpA = ~PINA;
	
	switch (PLYR_state) {
		case PLYR_init:
			i = 6;
			j = 0;
			cntNeutral = 0;
			PLYR_state = PLYR_wait;
			break;
		case PLYR_wait:
			if (gameOver || gameDone || softReset) { PLYR_state = PLYR_gameover; }
			else if (tmpA == 0x01) {
				PLYR_state = PLYR_disp1;
				if (i > 6) { LCD_Cursor(i); LCD_WriteData(' '); i--; }
			}
			else if (tmpA == 0x02) {
				PLYR_state = PLYR_disp2;
				if (i < 11) { LCD_Cursor(i); LCD_WriteData(' '); i++; }
			}
			else {
				PLYR_state = PLYR_wait;
				cntNeutral++;
			}
			break;
		case PLYR_disp1:
			if (gameOver || gameDone || softReset) { PLYR_state = PLYR_gameover; }
			else if (tmpA == 0x01) {
				PLYR_state = PLYR_disp1;
				if (i > 6) { LCD_Cursor(i); LCD_WriteData(' '); i--; }
			}
			else {
				PLYR_state = PLYR_wait;
				cntNeutral = 0;
			}
			break;
		case PLYR_disp2:
			if (gameOver || gameDone || softReset) { PLYR_state = PLYR_gameover; }
			else if (tmpA == 0x02) {
				PLYR_state = PLYR_disp2;
				if (i < 11) { LCD_Cursor(i); LCD_WriteData(' '); i++; }
			}
			else {
				PLYR_state = PLYR_wait;
				cntNeutral = 0;
			}
			break;
		case PLYR_gameover:
			if (softReset) { PLYR_state = PLYR_init; }
			else { PLYR_state = PLYR_gameover; }
			break;
		default:
			PLYR_state = PLYR_init;
			break;
	}
	switch (PLYR_state) {
		case PLYR_init:
			break;
		case PLYR_wait:
			LCD_Cursor(i);
			LCD_WriteData(j);
			if (cntNeutral > 4) { j = 0; }
			break;
		case PLYR_disp1:
			j = 1;
			LCD_Cursor(i);
			LCD_WriteData(j);
			break;
		case PLYR_disp2:
			j = 2;
			LCD_Cursor(i);
			LCD_WriteData(j);
			break;
		case PLYR_gameover:
			break;
	}
}
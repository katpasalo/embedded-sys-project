/* 	  By: Katherine Pasalo (kpasa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Final Project
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
enum G_States {G_init, G_wait, G_left, G_right, G_gameover} G_state;

void Ghosts_Tick() {
	tmpA = ~PINA;
	
	switch (G_state) {
		case G_init:
			for (unsigned char g = 0; g < 54; g++) {
				gmap[g] = gmapReset[g];	
			}
			m = 0;
			n = 0;
			for (m = 0; m < 17; m++) {
				LCD_Cursor(m);
				LCD_WriteData(gmap[(m + n - 1) % 53]);
			}
			G_state = G_wait;
			break;
		case G_wait:
			if (gameOver || gameDone || softReset) { G_state = G_gameover; }
			else if (i == 6 && tmpA == 0x01) { G_state = G_left; }
			else if (i == 11 && tmpA == 0x02) { G_state = G_right; }
			else { G_state = G_wait; }
			break;
		case G_left:
			if (gameOver || gameDone || softReset) { G_state = G_gameover; }
			else if (i == 6 && tmpA == 0x01) { G_state = G_left; }
			else { G_state = G_wait; }
			break;
		case G_right:
			if (gameOver || gameDone || softReset) { G_state = G_gameover; }
			else if (i == 11 && tmpA == 0x02) { G_state = G_right; }
			else { G_state = G_wait; }
			break;
		case G_gameover:
			if (softReset) { G_state = G_init; }
			else { G_state = G_gameover; }
			break;
		default:
			G_state = G_init;
			break;
	}
	switch (G_state) {
		case G_init:
			break;
		case G_wait:
			break;
		case G_left:
			n = (n > 0) ? n - 1 : 53; 
			for (m = 0; m < 17; m++) {
				if (m != i) {
					LCD_Cursor(m);
					LCD_WriteData(gmap[(m + n - 1) % 53]);
				}
			}
			break;
		case G_right:
			n = (n < 53) ? n + 1 : 0;
			for (m = 0; m < 17; m++) {
				if (m != i) {
					LCD_Cursor(m);
					LCD_WriteData(gmap[(m + n - 1) % 53]);
				}
			}
			break;
		case G_gameover:
			break;			
	}
}
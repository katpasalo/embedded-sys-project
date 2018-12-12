/* 	  By: Katherine Pasalo (kpasa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Final Project
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
enum testAttack_States {ATK_init, ATK_wait, ATK_hit1, ATK_hit2, ATK_gameover } ATK_state;

void Attack_Tick() {
	tmpA = ~PINA;
	
	switch (ATK_state) {
		case ATK_init:
			hitCount = 0;
			hitMax = 10;
			cntAttack = 0;
			ATK_state = ATK_wait;
			break;
		case ATK_wait:
			if (gameOver || gameDone || softReset) { ATK_state = ATK_gameover; }
			else if (tmpA == 0x04) {
				ATK_state = ATK_hit1;
				cntAttack = 0;
				lr = j;
				k = i + 1;
				l = i - 1;
			}
			else {
				ATK_state = ATK_wait;
			}
			break;
		case ATK_hit1:
			if (gameOver || gameDone || softReset) { ATK_state = ATK_gameover; }
			else {ATK_state = ATK_hit2;}
			break;
		case ATK_hit2:
			if (gameOver || gameDone || softReset) { ATK_state = ATK_gameover; }
			else if (cntAttack < 3) {
				ATK_state = ATK_hit2;
			}
			else {
				ATK_state = ATK_wait;
				if (lr == 1) {
					LCD_Cursor(l);
					LCD_WriteData(' ');
					LCD_Cursor(l - 1);
					LCD_WriteData(' ');
				}
				else {
					LCD_Cursor(k);
					LCD_WriteData(' ');
					LCD_Cursor(k + 1);
					LCD_WriteData(' ');	
				}
			}
			break;
		case ATK_gameover:
			if (softReset) { ATK_state = ATK_init; }
			else { ATK_state = ATK_gameover; }
			break;
		default:
			ATK_state = ATK_init;
			break;
	}
	switch (ATK_state) {
		case ATK_init:
			break;
		case ATK_wait:
			break;
		case ATK_hit1:
			if (lr == 1) {
				LCD_Cursor(l);
				LCD_WriteData('*');
				if (gmap[(l + n - 1) % 53] == 6) { gmap[(l + n - 1) % 53] = ' '; hitCount++; gameDone = (hitCount == hitMax) ? 1 : 0; }
			}
			else {
				LCD_Cursor(k);
				LCD_WriteData('*');
				if (gmap[(k + n - 1) % 53] == 6) { gmap[(k + n - 1) % 53] = ' '; hitCount++; gameDone = (hitCount == hitMax) ? 1 : 0; }
			}
			break;
		case ATK_hit2:
			if (lr == 1) {
				LCD_Cursor(l - 1);
				LCD_WriteData('(');
				if (gmap[(l + n - 2) % 53] == 6) { gmap[(l + n - 2) % 53] = ' '; hitCount++; gameDone = (hitCount == hitMax) ? 1 : 0; }
			}
			else {
				LCD_Cursor(k + 1);
				LCD_WriteData(')');
				if (gmap[(k + n) % 53] == 6) { gmap[(k + n) % 53] = ' '; hitCount++; gameDone = (hitCount == hitMax) ? 1 : 0; }
			}
			cntAttack++;
			break;
		case ATK_gameover:
			break;
	}
}
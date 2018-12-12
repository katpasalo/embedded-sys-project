/* 	  By: Katherine Pasalo (kpasa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Final Project
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
enum GM_States {GM_init, GM_wait, GM_over, GM_done, GM_static} GM_state;

//Player
unsigned char tmpA;
unsigned char i; //character position
unsigned char j; //character orientation
unsigned char cntNeutral;
//Ghosts
unsigned char gmap[53] = { 6, 6, ' ', ' ', 6, ' ', ' ', ' ', ' ', ' ', 6, 6, ' ', 6, ' ', ' ', ' ', ' ', ' ', 6,
	' ', ' ', 6, ' ', 6, ' ', ' ', ' ', ' ', 6, 6, ' ', ' ', ' ', ' ', 6, ' ', 6, ' ', ' ', ' ', 6, ' ', 6, 6, 
	' ', ' ', 6, ' ', 6, ' ', 6, 6 };
unsigned char gmapReset[53] = { 6, 6, ' ', ' ', 6, ' ', ' ', ' ', ' ', ' ', 6, 6, ' ', 6, ' ', ' ', ' ', ' ', ' ', 6,
	' ', ' ', 6, ' ', 6, ' ', ' ', ' ', ' ', 6, 6, ' ', ' ', ' ', ' ', 6, ' ', 6, ' ', ' ', ' ', 6, ' ', 6, 6,
' ', ' ', 6, ' ', 6, ' ', 6, 6 };
unsigned char m;
unsigned char n;
//Attack
unsigned char hitCount;
unsigned char hitMax;
unsigned char k; //position of attack right
unsigned char l; //position of attack left
unsigned char lr; //left or right flag (2 if left, 1 if right)
unsigned char cntAttack;
//Heartpoints
unsigned char currHeart;
unsigned char cntHeart;
//Game
unsigned char gameOver; //lost
unsigned char gameDone; //finished
unsigned char softReset;
unsigned char scoreX;
unsigned char scoreY;
unsigned char score;
//Highscore
unsigned char seg_code[]={0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x19,0x00};
uint8_t byteRead;
unsigned char highscore;


void Game_Tick() {
	tmpA = ~PINA;
	
	switch (GM_state) {
		case GM_init:
			gameOver = 0;
			gameDone = 0;
			softReset = 0;
			scoreX = '0';
			scoreY = '0';
			score = 0;
			GM_state = GM_wait;
			break;
		case GM_wait:
			if (gameOver) { GM_state = GM_over; }
			else if (gameDone) { GM_state = GM_done; }
			else if (tmpA == 0x08) { GM_state = GM_init; gameDone = 0; softReset = 1; }
			break;
		case GM_over:
			GM_state = GM_static;
			break;
		case GM_done:
			GM_state = GM_static;
			break;
		case GM_static:
			if (tmpA == 0x08) { GM_state = GM_init; softReset = 1; }
			else { GM_state = GM_static; }
			break;
	}
	switch (GM_state) {
		case GM_init:
			break;
		case GM_wait:
			break;
		case GM_over:
			LCD_ClearScreen();
			for (unsigned char i = 0; i < 33; i++) {
				LCD_Cursor(i);
				LCD_WriteData(6);
			}
			LCD_DisplayString(7, "GAME");
			LCD_DisplayString(23, "OVER");
			break;
		case GM_done:
			_delay_ms(300);
			LCD_ClearScreen();
			
			LCD_DisplayString(1, "(*");
			LCD_Cursor(3);
			LCD_WriteData(1);
			LCD_Cursor(14);
			LCD_WriteData(2);
			LCD_DisplayString(15, "*)");
			LCD_DisplayString(4, "WELL DONE!");
			
			LCD_DisplayString(18, "YOUR SCORE: ");
			score = hitCount / 2;
			switch (score) {
				case 0:
					scoreX = '0';
					scoreY = '0';
					break;
				case 1:
					scoreX = '0';
					scoreY = '1';
					break;
				case 2:
					scoreX = '0';
					scoreY = '2';
					break;
				case 3:
					scoreX = '0';
					scoreY = '3';
					break;
				case 4:
					scoreX = '0';
					scoreY = '4';
					break;
				case 5:
					scoreX = '0';
					scoreY = '5';
					break;
				case 6:
					scoreX = '0';
					scoreY = '6';
					break;
				case 7:
					scoreX = '0';
					scoreY = '7';
					break;
				case 8:
					scoreX = '0';
					scoreY = '8';
					break;
				case 9:
					scoreX = '0';
					scoreY = '9';
					break;
				case 10:
					scoreX = '1';
					scoreY = '0';
					break;
			}
			LCD_Cursor(30);
			LCD_WriteData(scoreX);
			LCD_Cursor(31);
			LCD_WriteData(scoreY);
			break;
		case GM_static:
			break;
	}
}
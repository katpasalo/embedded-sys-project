/* 	  By: Katherine Pasalo (kpasa001@ucr.edu)
 *    Lab Section: B21
 *    Assignment: Final Project
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
void transmit_data(unsigned char data) {
	int i;
	for (i = 0; i < 8 ; i++) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTC = 0x08;
		// set SER = next bit of data to be sent.
		PORTC |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTC |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	PORTC |= 0x04;
	// clears all lines in preparation of a new transmission
	PORTC = 0x00;
}

enum Highscore_States {HS_init, HS_disp, HS_update} HS_state;

void Highscore_Tick() {
	switch (HS_state) {
		case HS_init:
			byteRead = eeprom_read_byte((uint8_t*)46);
			highscore = byteRead;
			transmit_data(seg_code[highscore]);
			HS_state = HS_disp;
			break;
		case HS_disp:
			if (gameDone) { HS_state = HS_update; }
			break;
		case HS_update:
			HS_state = HS_disp;
			break;
		default:
			HS_state = HS_init;
			break;
	}
	switch (HS_state) {
		case HS_init:
			break;
		case HS_disp:
			break;
		case HS_update:
			if (score > highscore) { score = (hitCount / 2); }
			transmit_data(seg_code[highscore]);
			eeprom_update_byte (( uint8_t *)46, highscore);
			break;
	}
}
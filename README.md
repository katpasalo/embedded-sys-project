# embedded-sys-project

## Source Files

### Game.h
Keeps track of the status of the game (i.e. user lost, user finished, soft reset)
### Attack.h
Responsible for attack animation and keeping track of how many attacks successfully hit a ghost
### Player.h
FSM for controlling the player's movement and rest animation
### Ghosts.h
Contains array with environment and implements side scrolling
### Heartpoints.h
Records when player intersects a ghost and decrements accordingly with animation
### Highscore.h
Updates the highscore of any user using EEPROM and displays onto 7 segment display
### timer.h
Implements timer for appropriate scheduling
### io.c
Has functions used to control the 16x2 LCD display
### main.c
Contains information for custom LCD characters and tick function calls

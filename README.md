# Magician's Mission

## High Level Description
In the “Magician’s Mission” side-scrolling game, the user takes on the role of a magician. The user can cast a spell on surrounding ghosts or otherwise take damage when crossing paths with them. The user can also strive to get their score displayed as the overall high score; alternatively, if they lose all their hearts, they lose the game, and the ghosts dominate.

## User Guide 
### Rules
* For every two ghosts killed, your score increases by one
* When you run into a ghost, your score decreases by one, and your health points decrease by one heart
* If you lose all of your hearts, you lose - it’s “GAME OVER”
* You win after encountering all ghosts in the map without dying
### Controls
* Attack with the button on the left
* Move left or right with the buttons on the right
### Other Features
* Soft reset with the button on the upper right
* High score maintains value after hard reset

## Technologies and Components
* Atmel Studio 7.0
* ATmega1284-PU
* 16x2 LCD Display
* Buttons
* Game logic
* EEPROM
* Custom characters
* Shift Register
* 7-Segment display

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

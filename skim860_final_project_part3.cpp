/*        Sangyun Kim skim860@ucr.edu

*          Discussion Section:024

 *         Assignment:Custom LAB 

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.
 */
/*
PART1: used LCD screen effectively. 

PART2: implemented bug free game logic.

Things to do in PART3: (LCD screen that was in lab kit)
Implement health system and show it on the LCD screen (need custom character, so maybe create like hearts or squre bar)
Show current score in real time on the LCD screen

*/

#include "timerISR-Fixed.h"
#include "ST7735_helper.h"
#include "periph.h"
#include "LCD_helper.h"


#define NUM_TASKS 6

//shared global variables for inter task communication. 
unsigned char Direction = 0b0000; //Joystick direction L,R,U,D in 4 bits
unsigned char GameInProgress = 0; //will be used to check if game is in progress. 
unsigned char player_x = 60;
unsigned char player_y = 60;
char player_HP = 2; 
unsigned char player_Score = 0;

//Task struct for concurrent synchSMs implmentations
typedef struct _task{
	signed 	 char state; 		//Task's current state
	unsigned long period; 		//Task period
	unsigned long elapsedTime; 	//Time elapsed since last task tick
	int (*TickFct)(int); 		//Task tick function
} task;
task tasks[NUM_TASKS];

//Periods for each task
const unsigned long TASK1_PERIOD = 100;
const unsigned long TASK2_PERIOD = 100;
const unsigned long TASK3_PERIOD = 50;
const unsigned long TASK4_PERIOD = 50;
const unsigned long TASK5_PERIOD = 100;
const unsigned long TASK6_PERIOD = 500;

const unsigned long GCD_PERIOD = 50;


//tick functions for each task
enum Joystick_States {read_Joystick};
enum Update_Character_States {player_Idle, player_MovingL, player_MovingR, player_MovingU, player_MovingD};
enum Bullets_States {bullet_Idle, bullet_Spawn, bullet_Update};
enum Mobs_States {mob_Idle, mob_Spawn, mob_Update};
enum Game_States {game_Start, game_InProgress, game_Over};
enum LCD_States {LCD_Idle, LCD_Update};

int TickFct_Joystick (int state);
int TickFct_Character (int state);
int TickFct_Bullet (int state);
int TickFct_Mob (int state);
int TickFct_Game (int state);
int TickFct_LCD (int state);


void TimerISR() {
	for ( unsigned int i = 0; i < NUM_TASKS; i++ ) {                   // Iterate through each task in the task array
		if ( tasks[i].elapsedTime == tasks[i].period ) {           // Check if the task is ready to tick
			tasks[i].state = tasks[i].TickFct(tasks[i].state); // Tick and set the next state for this task
			tasks[i].elapsedTime = 0;                          // Reset the elapsed time for the next tick
		}
		tasks[i].elapsedTime += GCD_PERIOD;                        // Increment the elapsed time by GCD_PERIOD
	}
}

int main(void) {
    //TODO: initialize all your inputs and ouputs
    DDRC   = 0xE0; //0b1110 0000 or 0xE0 set PC0-4 as input (012) (vRX, vRY, Button), (3,4) (Right Button(start), Left Button(reset))
    PORTC  = 0x1F; //0b0001 1111 or 0x1F initialize input pins high

    DDRB   = 0x2F; //0b0010 1111 or 0x3F set PB5, 3-0 as output (532, 1, 0) (SCK, MOSI, SS, A0/DC, RESET), PB4 as input MISO;
    PORTB  = 0xD0; //0b1101 0000 or 0xD0 set output pins low, input pins high.

    DDRD   = 0xFC; //0b1111 1100 or 0xFC set PD7-2 as output (7654, 3 and 2) (D7-4, RS and E);
    PORTD  = 0x03; //0b0000 0011 or 0x03 set output pins low;

    unsigned char i = 0;
    tasks[i].period = TASK1_PERIOD;
    tasks[i].state = read_Joystick;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_Joystick;
    ++i;
    tasks[i].period = TASK2_PERIOD;
    tasks[i].state = player_Idle;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_Character;
    ++i;
    tasks[i].period = TASK3_PERIOD;
    tasks[i].state = bullet_Idle;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_Bullet;
    ++i;
    tasks[i].period = TASK4_PERIOD;
    tasks[i].state = mob_Idle;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_Mob;
    ++i;
    tasks[i].period = TASK5_PERIOD;
    tasks[i].state = game_Start;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_Game;
    ++i;
    tasks[i].period = TASK6_PERIOD;
    tasks[i].state = LCD_Idle;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_LCD;
    ++i;

    ADC_init();

    SPI_INIT();
    ST7735_init();
    player_init_colors();
    fill_screen(C_BLACK);
    player_draw(player_x, player_y);
    draw_gameStart();

    lcd_init();
    lcd_clear();
    load_Custom_Char();
    lcd_clear();


    srand(time(NULL));

    TimerSet(GCD_PERIOD);
    TimerOn();


    while (1) {}

    return 0;
}



int TickFct_Joystick (int state) {
  static const int centerX = ADC_read(0);
  static const int centerY = ADC_read(1);
  const int THRESHOLD = 120;
  int x, y, dx, dy; 

  switch (state) {
    case read_Joystick:
      x = ADC_read(0);
      y = ADC_read(1);
      dx = (x - centerX) >= 0 ? (x - centerX) : -(x - centerX);
      dy = (y - centerY) >= 0 ? (y - centerY) : -(y - centerY);

      if      ((x < centerX - THRESHOLD) && (dx > dy)) {Direction = 0b0100;}
      else if ((x > centerX + THRESHOLD) && (dx > dy)) {Direction = 0b1000;}
      else if ((y < centerY - THRESHOLD) && (dy > dx)) {Direction = 0b0001;}
      else if ((y > centerY + THRESHOLD) && (dy > dx)) {Direction = 0b0010;}
      else                                             {Direction = 0b0000;}

      state = read_Joystick;

      break;

    default:
      break;
  }

  switch (state) {
    case read_Joystick:
      break;

    default:
      break;
  }

  return state;
}

int TickFct_Character (int state) {
    switch (state) {
        case player_Idle: //wish I have known this before Final :(
        case player_MovingL:
        case player_MovingR:
        case player_MovingU:
        case player_MovingD:

            if      (Direction == 0b1000) state = player_MovingL;
            else if (Direction == 0b0100) state = player_MovingR;
            else if (Direction == 0b0010) state = player_MovingU;
            else if (Direction == 0b0001) state = player_MovingD;
            else                          state = player_Idle;

            break;

        default:
            break;
}

    switch (state) {
        case player_Idle:
            if (!GameInProgress) {
                player_x = 60;
                player_y = 60;
            }
            else {move_player(0, 0);}
            break;
        case player_MovingL:
            if (!GameInProgress) {
                player_x = 60;
                player_y = 60;
            }
            else {move_player(-1, 0);}
            break;
        case player_MovingR:
            if (!GameInProgress) {
                player_x = 60;
                player_y = 60;
            }
            else {move_player(1,0);}
            break;
        case player_MovingD:
            if (!GameInProgress) {
                player_x = 60;
                player_y = 60;
            }
            else {move_player(0, -1);}
            break;
        case player_MovingU:
            if (!GameInProgress) {
                player_x = 60;
                player_y = 60;
            }
            else {move_player(0, 1);}
            break;

        default:
            break;
    }

    return state;
}

int TickFct_Bullet (int state) {
    static unsigned char bullet_cnt = 0;

    switch (state) {
        case bullet_Idle:
            if (GameInProgress) {
                state = bullet_Spawn;
            }
            else {
                state = bullet_Idle;
            }
            break;

        case bullet_Spawn:
            if (!GameInProgress) {
                state = bullet_Idle;
            }
            else {
                state = bullet_Update;
            }
            break;
        
        case bullet_Update:
            if (!GameInProgress) {
                state = bullet_Idle;
                bullet_cnt = 0;
            }
            else if (bullet_cnt < 80) {
                ++bullet_cnt; 
                state = bullet_Update;
            }
            else {
                bullet_cnt = 0;
                state = bullet_Spawn;
            }
            break;

        default:
            break;
    }
    
    switch (state) {
        case bullet_Idle:
            break;

        case bullet_Spawn:
            spawn_bullets_8_way();
            break;
        
        case bullet_Update:
            bullets_update();
            break;

        default:
            break;
    }

    return state;
}

int TickFct_Mob (int state) {
    static unsigned char mob_cnt = 0;

    switch (state) {
        case mob_Idle:
            if (GameInProgress) {
                state = mob_Spawn;
            }
            else {
                state = mob_Idle;
            }
            break;

        case mob_Spawn:
            if (!GameInProgress) {
                state = mob_Idle;
            }
            else {
                state = mob_Update;
            }
            break;

        case mob_Update:
            if (!GameInProgress) {
                state = mob_Idle;
            }
            else if (mob_cnt < 50) {
                ++mob_cnt;
                state = mob_Update;
            }
            else {
                state = mob_Spawn;
                mob_cnt = 0;
            }
            break;

        default:
            break;
    }

    switch (state) {
        case mob_Idle:
            break;

        case mob_Spawn:
            spawn_mob();
            break;

        case mob_Update:
            if (mob_cnt % 10 == 0){
                mobs_update();
            }
            break;

        default:
            break;
    }

    return state;
}

int TickFct_Game (int state) {
    switch (state) {
        case game_Start:
            if (GetBit(PINC, 4)) {
                GameInProgress = 1;
                state = game_InProgress;
                fill_screen(C_BLACK);
                player_HP = 2;
                player_Score = 0;
            }
            else {
                state = game_Start;
            }
            break;
        
        case game_InProgress:
            if (GetBit(PINC, 3)) {
                state = game_Over;
            }
            else if (player_HP == 0) {
                state = game_Over;
            }
            else {
                state = game_InProgress;
            }
            break;

        case game_Over:
            if (GetBit(PINC, 4)) {
                state = game_InProgress;
                GameInProgress = 1;
                fill_screen(C_BLACK);
                player_HP = 2;
                player_Score = 0;
            }
            else {
                state = game_Over;
            }
            break;

        default:
            break;
    }
    
    switch (state) {
        case game_Start:
            if (GameInProgress) {
                mob_eraseAll();
                bullets_eraseAll();
                draw_gameStart();
                GameInProgress = 0;
            }
            break;
        
        case game_InProgress:
            break;

        case game_Over:
            if (GameInProgress) {
                mob_eraseAll();
                bullets_eraseAll();
                draw_gameOver();
                draw_score();
                GameInProgress = 0;
            }
            break;

        default:
            break;
    }

    return state;
}

int TickFct_LCD (int state) {
    unsigned char HP_whitespace = 13 - player_HP;
    char scoreStr[6];
    char idleMsg1[17] = "Welcome Back!   ";
    char idleMsg2[17] = "Press Start!    ";
    char HPMsg[4] = "HP:";
    char space[2] = " ";
    char ScoreMsg[12] = "Score:     ";

    switch(state) {
        case LCD_Idle:
            if (GameInProgress) {
                state = LCD_Update;
                char_to_string(player_Score, scoreStr);
            }
            else {
                state = LCD_Idle;
            }
            break;

        case LCD_Update:
            if (!GameInProgress) {
                state = LCD_Idle;
            }
            else {
                state = LCD_Update;
                char_to_string(player_Score, scoreStr);
            }
            break;
        
        default:
            break;
    }

    switch(state) {
        case LCD_Idle:
            lcd_goto_xy(0,0);
            lcd_write_str(idleMsg1);
            lcd_goto_xy(1,0);
            lcd_write_str(idleMsg2);
            break;
        
        case LCD_Update:
            lcd_goto_xy(0,0);
            lcd_write_str(HPMsg);
            for (unsigned char j = 0; j < HP_whitespace; ++j) {
                lcd_write_str(space);
            }
            for (unsigned char i = 0; i < player_HP; ++i) {
                lcd_write_character(0);
            }
            lcd_goto_xy(1,0);
            lcd_write_str(ScoreMsg);
            lcd_write_str(scoreStr);
            break;

        default:
            break;
    }

    return state;
}
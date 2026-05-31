
#ifndef ST7735_HELPER_H
#define ST7735_HELPER_H

#include <ST7735.h>
#include <stdlib.h>
#include <time.h>


//helper functions for pixel editing
#define PLAYER_W  6
#define PLAYER_H  8

#define MOB_W     6
#define MOB_H     8

#define MENU_W    88
#define MENU_H    32

#define OVER_W    96
#define OVER_H    32

#define NUM_W     8
#define NUM_H     15

//color def
#define C_BLACK   set_color(0, 0, 0)
#define C_WHITE   set_color(255, 255, 255)
#define C_RED     set_color(255, 0, 0)
#define C_GREEN   set_color(0, 255, 0)
#define C_BLUE    set_color(0, 0, 255)
#define C_YELLOW  set_color(255, 255, 0)
#define C_BROWN   set_color(140, 94, 57)
#define C_SKIN    set_color(227, 181, 135)

#define MAX_BULLET 64
#define MAX_SPAWN_PER_DIR 8

#define MAX_MOBS 5

// 1 bit per pixel, 1 is white 0 is black, 6x8
// each index will have a value of 6 pixel at that row/index
const unsigned int playerSprite[PLAYER_H][PLAYER_W] = {
    {C_BLACK, C_GREEN, C_GREEN, C_GREEN, C_GREEN, C_BLACK},
    {C_BLACK, C_GREEN, C_GREEN, C_GREEN, C_WHITE, C_GREEN},
    {C_BLACK, C_SKIN, C_BROWN, C_SKIN, C_BROWN, C_BLACK},
    {C_BLACK, C_SKIN, C_SKIN, C_SKIN, C_SKIN, C_BLACK},
    {C_GREEN, C_BLUE, C_GREEN, C_GREEN, C_BLUE, C_GREEN},
    {C_SKIN, C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_SKIN},
    {C_BLACK, C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLACK},
    {C_BLACK, C_BROWN, C_BLACK, C_BLACK, C_BROWN, C_BLACK},
};

const unsigned int mobSprite[MOB_H][MOB_W] = {
    {C_GREEN, C_GREEN, C_GREEN, C_GREEN, C_BLACK, C_BLACK},
    {C_GREEN, C_GREEN, C_GREEN, C_GREEN, C_BLACK, C_BLACK},
    {C_GREEN, C_BLACK, C_GREEN, C_BLACK, C_BLACK, C_BLACK},
    {C_GREEN, C_GREEN, C_GREEN, C_GREEN, C_BLACK, C_BLACK},
    {C_BLUE, C_RED, C_GREEN, C_GREEN, C_BLUE, C_RED},
    {C_GREEN, C_RED, C_GREEN, C_GREEN, C_BLACK, C_RED},
    {C_GREEN, C_GREEN, C_GREEN, C_GREEN, C_BLACK, C_BLACK},
    {C_BROWN, C_BLACK, C_BLACK, C_BROWN, C_BLACK, C_BLACK},
};


//32 bits or pixel of height and 11 bytes or 88 bits of pixel of width
const unsigned char gameStartSprite[MENU_H][MENU_W / 8] = {
    { 0x00, 0x01, 0xF8, 0x03, 0xF0, 0x38, 0x03, 0x8F, 0xFF, 0x00, 0x01 }, // row 0
    { 0x00, 0x01, 0xF8, 0x03, 0xF0, 0x38, 0x03, 0x8F, 0xFF, 0x00, 0x00 }, 
    { 0x00, 0x01, 0xF8, 0x03, 0xF0, 0x38, 0x03, 0x8F, 0xFF, 0x00, 0x00 }, 
    { 0x00, 0x0E, 0x00, 0x1C, 0x0E, 0x3F, 0x1F, 0x8E, 0x00, 0x00, 0x00 }, 
    { 0x00, 0x0E, 0x00, 0x1C, 0x0E, 0x3F, 0x1F, 0x8E, 0x00, 0x00, 0x00 }, 
    { 0x00, 0x0E, 0x00, 0x1C, 0x0E, 0x3F, 0x1F, 0x8E, 0x00, 0x00, 0x00 }, 
    { 0x00, 0x0E, 0x3F, 0x1F, 0xFE, 0x38, 0xE3, 0x8F, 0xF8, 0x00, 0x00 }, 
    { 0x00, 0x0E, 0x3F, 0x1F, 0xFE, 0x38, 0xE3, 0x8F, 0xF8, 0x00, 0x00 }, 
    { 0x00, 0x0E, 0x3F, 0x1F, 0xFE, 0x38, 0xE3, 0x8F, 0xF8, 0x00, 0x00 }, 
    { 0x00, 0x0E, 0x07, 0x1C, 0x0E, 0x38, 0x03, 0x8E, 0x00, 0x00, 0x00 }, 
    { 0x00, 0x0E, 0x07, 0x1C, 0x0E, 0x38, 0x03, 0x8E, 0x00, 0x00, 0x00 }, // row 10
    { 0x00, 0x0E, 0x07, 0x1C, 0x0E, 0x38, 0x03, 0x8E, 0x00, 0x00, 0x00 }, 
    { 0x00, 0x01, 0xF8, 0x1C, 0x0E, 0x38, 0x03, 0x8F, 0xFF, 0x00, 0x00 }, 
    { 0x00, 0x01, 0xF8, 0x1C, 0x0E, 0x38, 0x03, 0x8F, 0xFF, 0x00, 0x00 }, 
    { 0x00, 0x01, 0xF8, 0x1C, 0x0E, 0x38, 0x03, 0x8F, 0xFF, 0x00, 0x00 }, 
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
    { 0x1F, 0xF1, 0xFF, 0xFC, 0x0F, 0xC0, 0xFF, 0x81, 0xFF, 0xFC, 0x0E }, 
    { 0x1F, 0xF1, 0xFF, 0xFC, 0x0F, 0xC0, 0xFF, 0x81, 0xFF, 0xFC, 0x0E }, 
    { 0x1F, 0xF1, 0xFF, 0xFC, 0x0F, 0xC0, 0xFF, 0x81, 0xFF, 0xFC, 0x0E },
    { 0xE0, 0x00, 0x07, 0x00, 0x70, 0x38, 0xE0, 0x70, 0x07, 0x00, 0x0E }, //row 20
    { 0xE0, 0x00, 0x07, 0x00, 0x70, 0x38, 0xE0, 0x70, 0x07, 0x00, 0x0E },
    { 0xE0, 0x00, 0x07, 0x00, 0x70, 0x38, 0xE0, 0x70, 0x07, 0x00, 0x0E },
    { 0x1F, 0x80, 0x07, 0x00, 0x7F, 0xF8, 0xFF, 0x80, 0x07, 0x00, 0x0E }, 
    { 0x1F, 0x80, 0x07, 0x00, 0x7F, 0xF8, 0xFF, 0x80, 0x07, 0x00, 0x0E }, 
    { 0x1F, 0x80, 0x07, 0x00, 0x7F, 0xF8, 0xFF, 0x80, 0x07, 0x00, 0x0E }, 
    { 0x00, 0x70, 0x07, 0x00, 0x70, 0x38, 0xE3, 0x80, 0x07, 0x00, 0x00 }, 
    { 0x00, 0x70, 0x07, 0x00, 0x70, 0x38, 0xE3, 0x80, 0x07, 0x00, 0x00 }, 
    { 0x00, 0x70, 0x07, 0x00, 0x70, 0x38, 0xE3, 0x80, 0x07, 0x00, 0x00 }, 
    { 0xFF, 0x80, 0x07, 0x00, 0x70, 0x38, 0xE0, 0x70, 0x07, 0x00, 0x0E }, 
    { 0xFF, 0x80, 0x07, 0x00, 0x70, 0x38, 0xE0, 0x70, 0x07, 0x00, 0x0E }, // row 30
    { 0x7F, 0x80, 0x07, 0x00, 0x70, 0x20, 0xE0, 0x70, 0x07, 0x00, 0x0E }, 
};

const unsigned char gameOverSprite[OVER_H][OVER_W / 8] = {
    { 0x1F, 0x80, 0x3F, 0x07, 0x00, 0x71, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00 },
    { 0x1F, 0x80, 0x3F, 0x07, 0x00, 0x71, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00 },
    { 0x1F, 0x80, 0x3F, 0x07, 0x00, 0x71, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00 },
    { 0xE0, 0x01, 0xC0, 0xC7, 0xE3, 0xF1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE0, 0x01, 0xC0, 0xC7, 0xE3, 0xF1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE0, 0x01, 0xC0, 0xC7, 0xE3, 0xF1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE3, 0xF1, 0xFF, 0xC7, 0x1C, 0x71, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE3, 0xF1, 0xFF, 0xC7, 0x1C, 0x71, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE3, 0xF1, 0xFF, 0xC7, 0x1C, 0x71, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE0, 0x71, 0xC0, 0xC7, 0x00, 0x71, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE0, 0x71, 0xC0, 0xC7, 0x00, 0x71, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xE0, 0x71, 0xC0, 0xC7, 0x00, 0x71, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x1F, 0x81, 0xC0, 0xC7, 0x00, 0x71, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00 },
    { 0x1F, 0x81, 0xC0, 0xC7, 0x00, 0x71, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x0E, 0x01, 0xC7, 0xFF, 0x1F, 0xF0, 0x07 },
    { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x0E, 0x01, 0xC7, 0xFF, 0x1F, 0xF0, 0x07 },
    { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x0E, 0x01, 0xC7, 0xFF, 0x1F, 0xF0, 0x07 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x8E, 0x01, 0xC7, 0x00, 0x1C, 0x0E, 0x07 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x8E, 0x01, 0xC7, 0x00, 0x1C, 0x0E, 0x07 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x8E, 0x01, 0xC7, 0x00, 0x1C, 0x0E, 0x07 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x81, 0xCE, 0x07, 0xFC, 0x1F, 0xF0, 0x07 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x81, 0xCE, 0x07, 0xFC, 0x1F, 0xF0, 0x07 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x81, 0xCE, 0x07, 0xFC, 0x1F, 0xF0, 0x07 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x81, 0xCE, 0x07, 0x00, 0x1C, 0x70, 0x00 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x81, 0xCE, 0x07, 0x00, 0x1C, 0x70, 0x00 },
    { 0x00, 0x00, 0x00, 0x07, 0x03, 0x81, 0xCE, 0x07, 0x00, 0x1C, 0x70, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x30, 0x07, 0xFF, 0x1C, 0x0E, 0x07 },
    { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x30, 0x07, 0xFF, 0x1C, 0x0E, 0x07 },
    { 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x30, 0x07, 0xFF, 0x1C, 0x0E, 0x07 }
};

const unsigned char numberSprite [10][NUM_H / 3][NUM_W / 8] = {
    {{0x3C}, {0xC3}, {0xC3}, {0xC3}, {0x3C}},
    {{0x1C}, {0xFC}, {0x1C}, {0x1C}, {0xFF}},
    {{0x3C}, {0xC3}, {0x0C}, {0x30}, {0xFF}},
    {{0x3E}, {0xC3}, {0x0C}, {0xC3}, {0x3E}},
    {{0x0C}, {0x3C}, {0xCC}, {0xFF}, {0x0C}},
    {{0xFF}, {0xC0}, {0xFC}, {0x03}, {0xFC}},
    {{0x3C}, {0xC0}, {0xFC}, {0xC3}, {0x3C}},
    {{0xF8}, {0x07}, {0x07}, {0x38}, {0x38}},
    {{0x3C}, {0xC3}, {0x3C}, {0xC3}, {0x3C}},
    {{0x3C}, {0xC3}, {0x3F}, {0x03}, {0x3C}}
};


unsigned int background_color;
unsigned int bullet_color;
unsigned int bullets_in_dir[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // U, UR, R, RD, D, DL, L, LU

extern unsigned char player_x;
extern unsigned char player_y;

extern char player_HP; 
extern unsigned char player_Score;

typedef struct {
    unsigned char on_fly; //flag to check if the bullet is flying
    int curr_x; //current position
    int curr_y;
    char dir_x; //direction the bullet will fly continously. 
    char dir_y;
} Bullet;
Bullet bullets[MAX_BULLET];

typedef struct {
    unsigned char on_attack;
    int curr_x;
    int curr_y;
} Mob;
Mob mobs[MAX_MOBS];

// Call this once after display init
void player_init_colors(void) {
    background_color = C_BLACK;       // black
    bullet_color     = C_YELLOW;  
}

void player_draw(unsigned char x, unsigned char y)
{
    set_window(x, x + PLAYER_W - 1, y, y + PLAYER_H - 1);

    for (unsigned char row = 0; row < PLAYER_H; row++) {
        for (unsigned char col = 0; col < PLAYER_W; col++) {
            write_pixel(playerSprite[row][col]);
        }
    }
}

void erase_player(unsigned char x, unsigned char y) {
    set_window(x, x + PLAYER_W - 1, y, y + PLAYER_H - 1);

    for (unsigned int i = 0; i < (PLAYER_H * PLAYER_W); i++) {
        write_pixel(background_color);
    }
}

void move_player(char dx, char dy) // change in x and y. so dx = 1 will move 1 pixel right, -1 will move 1 pixel left
{
    erase_player(player_x, player_y); // clean pixels

    // update coordinates as signed int temporarily
    int new_x = (int)player_x + dx;
    int new_y = (int)player_y + dy;

    // make sure character does not go over screen limit
    if (new_x < 0)               {new_x = 0;}
    if (new_y < 0)               {new_y = 0;}
    if (new_x > 128 - PLAYER_W)  {new_x = 128 - PLAYER_W;}
    if (new_y > 128 - PLAYER_H)  {new_y = 128 - PLAYER_H;}

    //update new cord for player
    player_x = (unsigned char)new_x;
    player_y = (unsigned char)new_y;

    // draw at new position
    player_draw(player_x, player_y);
}


void fill_screen(unsigned int color) {
    set_window(0, 127, 0, 127);

    for (uint16_t i = 0; i < 128UL * 128UL; i++) {
        write_pixel(color);
    }
}

void draw_pixel_xy(unsigned char x, unsigned char y, unsigned int color) {
    set_window(x, x, y, y);
    write_pixel(color);
}


unsigned char get_dir_index(char dx, char dy) {
    if (dx == 0 && dy == -1) return 0; // U
    if (dx == 1 && dy == -1) return 1; // UR
    if (dx == 1 && dy == 0)  return 2; // R
    if (dx == 1 && dy == 1)  return 3; // DR
    if (dx == 0 && dy == 1)  return 4; // D
    if (dx == -1 && dy == 1) return 5; // DL
    if (dx == -1 && dy == 0) return 6; // L
    if (dx == -1 && dy == -1)return 7; // UL
    
    return 0;
}

void spawn_bullet(char dx, char dy) {
    unsigned char dir = get_dir_index(dx, dy);

    if (bullets_in_dir[dir] >= MAX_SPAWN_PER_DIR) {
        return; //do not spawn over 2 in the same direciton
    }

    // spawn as long as the total bullets on screen is less than 16
    for (unsigned char i = 0; i < MAX_BULLET; i++) {
        if (!bullets[i].on_fly) {
            bullets[i].on_fly = 1;

            // start near center of player sprite
            bullets[i].curr_x = player_x + PLAYER_W / 2 + (dx * (PLAYER_W / 2 + 1));
            bullets[i].curr_y = player_y + PLAYER_H / 2 + (dy * (PLAYER_H / 2 + 1));

            bullets[i].dir_x = dx;
            bullets[i].dir_y = dy;

            bullets_in_dir[dir]++;
            return; // only spawn one at one direction.
        }
    }
    // no free bullet slot means nothing will spawn
    return;
}

void spawn_bullets_8_way(void) {
    spawn_bullet( 1,  0);
    spawn_bullet(-1,  0);
    spawn_bullet( 0,  1);
    spawn_bullet( 0, -1);
    spawn_bullet( 1,  1);
    spawn_bullet( 1, -1);
    spawn_bullet(-1,  1);
    spawn_bullet(-1, -1);
}

void mob_erase(unsigned char x, unsigned char y);

void bullets_eraseAll() {
    for (unsigned char i = 0; i < MAX_BULLET; i++) {
        if (!bullets[i].on_fly) continue;
        draw_pixel_xy((unsigned char)bullets[i].curr_x, (unsigned char)bullets[i].curr_y, background_color);

        bullets[i].on_fly = 0;

        unsigned char dir = get_dir_index(bullets[i].dir_x, bullets[i].dir_y);
        bullets_in_dir[dir]--;
    }
}

void bullets_update(void) {
    for (unsigned char i = 0; i < MAX_BULLET; i++) {
        if (!bullets[i].on_fly) continue; //skip bullets that did not spawn

        //erase bullet at curr positon
        if (bullets[i].curr_x >= 0 && bullets[i].curr_x < 128 && bullets[i].curr_y >= 0 && bullets[i].curr_y < 128) {
            draw_pixel_xy((unsigned char)bullets[i].curr_x, (unsigned char)bullets[i].curr_y, background_color);
        }

        //update curr positon with direction it is moving
        bullets[i].curr_x += bullets[i].dir_x;
        bullets[i].curr_y += bullets[i].dir_y;

        //if out of LCD screen limit, the bullet will disappear 
        if (bullets[i].curr_x < 0 || bullets[i].curr_x >= 128 || bullets[i].curr_y < 0 || bullets[i].curr_y >= 128) {
            bullets[i].on_fly = 0;

            unsigned char dir = get_dir_index(bullets[i].dir_x, bullets[i].dir_y);
            bullets_in_dir[dir]--;
            continue; //move onto next bullet, skip draw.
        }

        //if the bullet hits the mob, it will despawn bullet and mob
        unsigned char collision_flag = 0;

        for (unsigned char j = 0; j < MAX_MOBS; j++) {
            if (!mobs[j].on_attack) {
                continue; //check for other mobs when the mob is not on the map
            }

            if (bullets[i].curr_x >= mobs[j].curr_x &&
                bullets[i].curr_x < mobs[j].curr_x + MOB_W && 
                bullets[i].curr_y >= mobs[j].curr_y && 
                bullets[i].curr_y < mobs[j].curr_y + MOB_H) {
                
                collision_flag = 1;
                
                bullets[i].on_fly = 0;

                unsigned char dir = get_dir_index(bullets[i].dir_x, bullets[i].dir_y);
                bullets_in_dir[dir]--;
                
                mob_erase(mobs[j].curr_x, mobs[j].curr_y);
                mobs[j].on_attack = 0;

                ++player_Score;

                break; //one bullet for one collision.
            }
        }

        if (collision_flag) continue; //go to next bullet when collision happened 

        draw_pixel_xy((unsigned char)bullets[i].curr_x, (unsigned char)bullets[i].curr_y, bullet_color);
    }
}

//change this later when mob becomes different size and defined with different H and W. 
void mob_draw(unsigned char x, unsigned char y) {
    set_window(x, x + MOB_W - 1, y, y + MOB_H - 1);

    for (unsigned char row = 0; row < MOB_H; row++) {
        for (unsigned char col = 0; col < MOB_W; col++) {
            write_pixel(mobSprite[row][col]);
        }
    }
}

void mob_erase(unsigned char x, unsigned char y) {
    set_window(x, x + MOB_W - 1, y, y + MOB_H - 1);

    for (unsigned int i = 0; i < (MOB_H * MOB_W); i++) {
        write_pixel(background_color);
    }
}

void mob_eraseAll() {
    for (unsigned char i = 0; i < MAX_MOBS; i++) {
        if (!mobs[i].on_attack) continue;

        mob_erase(mobs[i].curr_x, mobs[i].curr_y);

        mobs[i].on_attack = 0;
    }
}

unsigned char rand_wrap(unsigned char max) {
    return (unsigned char)(rand() % max);
} // output random either one of 0 to max - 1, used for random spawn of mobs

void spawn_mob(void) {
    for (unsigned char i = 0; i < MAX_MOBS; i++) {
        if (!mobs[i].on_attack) {
            mobs[i].on_attack = 1;

            unsigned char edge = rand_wrap(4); //0123 -> top, bottom, left, right
            unsigned char x = 0, y = 0;

            if (edge == 0) {
                x = rand_wrap(128 - MOB_W);
                y = 0;
            }
            else if (edge == 1) {
                x = rand_wrap(128 - MOB_W);
                y = 128 - MOB_H;
            }
            else if (edge == 2) {
                x = 0;
                y = rand_wrap(128 - MOB_H);
            }
            else if (edge == 3) {
                x = 128- MOB_W;
                y = rand_wrap(128 - MOB_H);
            }

            mobs[i].curr_x = x;
            mobs[i].curr_y = y;
            mobs[i].on_attack = 1;

            mob_draw(mobs[i].curr_x, mobs[i].curr_y);

            return; // only spawn one at one function call.
        }
    }
}

void mobs_update(void) {
    for (unsigned char i = 0; i < MAX_MOBS; i++) {
        if (!mobs[i].on_attack) continue; //skip ones that are not on attack

        unsigned char x = mobs[i].curr_x;
        unsigned char y = mobs[i].curr_y;

        mob_erase(x, y);

        int new_x = x;
        int new_y = y;
        //update comparison on the right with mob w and h later
        if (player_x + PLAYER_W/2 > x + PLAYER_W/2) { //get closer to player
            new_x++;
        }
        else if (player_x + PLAYER_W/2 < x + PLAYER_W/2) {
            new_x--;
        }
        if (player_y + PLAYER_H/2 > y + PLAYER_H/2) {
            new_y++;
        }
        else if (player_y + PLAYER_H/2 < y + PLAYER_H/2) {
            new_y--;
        }

        // if it walks off-screen, despawn
        if (new_x < 0 || new_y < 0 || new_x > 128 - PLAYER_W || new_y > 128 - PLAYER_H) {
            mobs[i].on_attack = 0;
            continue; //skip drawing and cord updating since it has despawned
        }

        //if it reach player, despawn
        if (new_x >= player_x && 
            new_x < player_x + PLAYER_W &&
            new_y >= player_y &&
            new_y < player_y + PLAYER_H) {
            
            mobs[i].on_attack = 0;
            --player_HP;

            continue;
        }

        mobs[i].curr_x = (unsigned char)new_x;
        mobs[i].curr_y = (unsigned char)new_y;

        mob_draw(mobs[i].curr_x, mobs[i].curr_y);
    }
}


void draw_gameStart () {
    fill_screen(C_BLUE);

    set_window(21, 21 + MENU_W - 1, 45, 45 + MENU_H - 1);

    for (unsigned char i = 0; i < MENU_H; i++) {
        for (char j = (MENU_W/8) - 1; j >= 0; j--) {
            unsigned char byte = gameStartSprite[i][j];
            for (char bit = 7; bit >= 0; bit--) {
                if (byte & (1 << (7 - bit))) {
                    write_pixel(C_BLACK);
                }
                else {
                    write_pixel(C_BLUE);
                }
            }
        }
    }
}


void draw_gameOver () {
    fill_screen(C_BLUE);

    set_window(16, 16 + OVER_W - 1, 10, 10 + OVER_H - 1);

    for (unsigned char i = 0; i < OVER_H; i++) {
        for (char j = (OVER_W/8) - 1; j >= 0; j--) {
            unsigned char byte = gameOverSprite[i][j];
            for (char bit = 7; bit >= 0; bit--) {
                if (byte & (1 << (7 - bit))) {
                    write_pixel(C_BLACK);
                }
                else {
                    write_pixel(C_BLUE);
                }
            }
        }
    }
}

void draw_digit(unsigned char num) {
    for (unsigned char i = 0; i < NUM_H / 3; i++) {

        for (unsigned char k = 0; k < 3; k++) {
            unsigned char byte = numberSprite[num][i][0];

            for (char bit = 7; bit >= 0; bit--) {
                if (byte & (1 << (7 - bit))) {
                    write_pixel(C_BLACK);
                }
                else {
                    write_pixel(C_BLUE);
                }
            }
        }    
    }
} 


void draw_score() {
    unsigned char dx = 10;
    set_window(dx, dx + NUM_W - 1, 50, 50 + NUM_H - 1);
    
    unsigned char digits[5] = {0, 0, 0, 0, 0};
    unsigned char temp_score = player_Score;

    for (char digit = 0; digit < 5; digit++) {
        if (temp_score > 0) {
            digits[digit] = temp_score % 10;
            temp_score = temp_score / 10;
        }
        else {
            digits[digit] = 0;
        }
    }
    
    for (unsigned char i = 0; i < 5; i++) {
        draw_digit(digits[i]);
        dx = dx + NUM_W + 3;
        set_window(dx, dx + NUM_W - 1, 50, 50 + NUM_H - 1);
    }
}

#endif

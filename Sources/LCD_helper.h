#ifndef LCD_HELPER_H
#define LCD_HELPER_H

#include <LCD.h>

#define LCD_SETCGRAM    0x40
#define LCD_SETDDRAM    0x80

//8 different custom charcters can be stored into CGRAM

uint8_t custom_HEART[8] {
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void create_Custom_Char (uint8_t location, uint8_t custom_char_map[]) {
	location &= 0x7; // we only have 8 locations 0-7

	lcd_send_command(LCD_SETCGRAM | (location << 3));
	for (int i=0; i<8; i++) {
		lcd_write_character(custom_char_map[i]);
	}
}

void load_Custom_Char () {
    create_Custom_Char (0, custom_HEART);
}

void char_to_string (unsigned char givenNum, char* outputStr) {
    unsigned char useNum = givenNum;

    for (int8_t i = 4; i >= 0; i--) {
        outputStr[i] = (useNum % 10) + '0';
        useNum = useNum / 10;
    }

    outputStr[5] = '\0';  
}

#endif

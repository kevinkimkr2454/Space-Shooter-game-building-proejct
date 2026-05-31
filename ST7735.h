#ifndef ST7735
#define ST7735

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <helper.h>
#include <spiAVR.h>

// Command definitions
#define NOP                      0x00 //No Operation
#define SWRESET                  0x01 //Software Reset

#define RDDID                    0x04 //Read Display ID
#define RDDST                    0x09 //Read display Status
#define RDDPM                    0x0A //Read Display Power
#define RDD_MADCTL               0x0B //Read Display
#define RDD_COLMOD               0x0C //Read Display Pixel
#define RDDIM                    0x0D //Read Display Image
#define RDDSM                    0x0E //Read Display Signal

#define SLPIN                    0x10 //Sleep in, booster off
#define SLPOUT                   0x11 //Sleep out, booster on

#define PTLON                    0x12 //Partial mode on
#define NORON                    0x13 //Partial mode off - default
#define INVOFF                   0x20 //Display inversion off
#define INVON                    0x21 //Display inversion on
#define GAMSET                   0x26 //Gamma curve select

#define DISPOFF                  0x28 //Display OFF
#define DISPON                   0x29 //Display ON

#define CASET                    0x2A //Column (X) Address SET
#define RASET                    0x2B //Row (Y) Address SET

#define RAMWR                    0x2C //Memory Write
#define RAMRD                    0x2E //Memory Read

#define PTLAR                    0x30
#define TEOFF                    0x34
#define TEON                     0x35
#define MADCTL                   0x36
#define IDMOFF                   0x38
#define IDMON                    0x39
#define COLMOD                   0x3A //Pixel format (color mode)
#define RDID1                    0xDA
#define RDID2                    0xDB
#define RDID3                    0xDC


void Send_Command(unsigned char command) {
    PORTB = (PORTB & 0xFD);
    SPI_SEND(command);
}

void Send_Data(unsigned char data) {
    PORTB = (PORTB & 0xFD) | 0x02;
    SPI_SEND(data);
}

void HardwareReset() {
    PORTB = SetBit(PORTB, 0, 0);
    _delay_ms(200);
    PORTB = SetBit(PORTB, 0, 1);
    _delay_ms(200);
}

void ST7735_init() {
    PORTB = SetBit(PORTB, 2, 0);
    HardwareReset();
    Send_Command(SWRESET);
    _delay_ms(150);
    Send_Command(SLPOUT);
    _delay_ms(200);
    Send_Command(COLMOD);
    Send_Data(0x05); //16bit color mode
    _delay_ms(10);
    Send_Command(MADCTL);
    Send_Data(0x80);
    Send_Command(DISPON);
    _delay_ms(200);
}

unsigned int set_color(unsigned char r, unsigned char g, unsigned char b) {
    return  ((b & 0xF8) << 8) |   // take top 5 bits of r
            ((g & 0xFC) << 3) |   // top 6 bits of g
            ((r & 0xF8) >> 3);             // top 5 bits of b
            // automatically compresses 255, 255, 255 to 31, 63, 31 color range. 
} 

void set_window(unsigned char x0, unsigned char x1, unsigned char y0, unsigned char y1) {
    // Column address set
    Send_Command(CASET);
    Send_Data(0x00); Send_Data(x0+2); //offsets for x(column) is 1, meaning range of 2-129
    Send_Data(0x00); Send_Data(x1+2);

    // Row address set
    Send_Command(RASET);
    Send_Data(0x00); Send_Data(y0+3); //offsets for y(row) is 2, meaning range of 1-128
    Send_Data(0x00); Send_Data(y1+3);

    // Start RAM write
    Send_Command(RAMWR);
}

void write_pixel(unsigned int pixel_data) {
    Send_Data(pixel_data >> 8);
    Send_Data(pixel_data);
}


#endif
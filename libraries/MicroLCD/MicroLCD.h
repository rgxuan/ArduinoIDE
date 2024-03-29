/*************************************************************************
* Arduino Text & Bitmap Display Library for multiple models of monochrome LCD display
* Distributed under GPL v2.0
* Copyright (c) 2013-2014 Stanley Huang <stanleyhuangyc@gmail.com>
* All rights reserved.
* For more information, please visit http://arduinodev.com
*************************************************************************/

#include <Arduino.h>

#define MEMORY_SAVING

typedef enum {
    FONT_SIZE_SMALL = 0,
    FONT_SIZE_MEDIUM
} FONT_SIZE;

#define FLAG_PAD_ZERO 1
#define FLAG_PIXEL_DOUBLE_H 2
#define FLAG_PIXEL_DOUBLE_V 4
#define FLAG_PIXEL_DOUBLE (FLAG_PIXEL_DOUBLE_H | FLAG_PIXEL_DOUBLE_V)

extern const PROGMEM unsigned char font5x8[][5];
extern const PROGMEM unsigned char digits8x8[][8] ;

class LCD_Common
{
public:
    LCD_Common():m_font(FONT_SIZE_SMALL),m_flags(0) {}
    void setFontSize(FONT_SIZE size) { m_font = size; }
    void setFlags(byte flags) { m_flags = flags; }
    virtual void backlight(bool on) {}
    virtual void draw(const PROGMEM byte* buffer, byte width, byte height) {}
    void printInt(uint16_t value, int8_t padding = -1);
    void printLong(uint32_t value, int8_t padding = -1);
protected:
    virtual void writeDigit(byte n) {}
    byte m_font;
    byte m_flags;
};

class LCD_Null : public LCD_Common, public Print
{
public:
    byte getLines() { return 0; }
    byte getCols() { return 0; }
    void clearLine(byte line) {}
    void clear() {}
    void begin() {}
    void setCursor(byte column, byte line) {}
    size_t write(uint8_t c) { return 0; }
};

#include "SSD1306.h"

class LCD_SSD1306 : public LCD_Common, public SSD1306, public Print
{
public:
    void setCursor(byte column, byte line);
	void setContrast(byte Contrast);
    void draw(const PROGMEM byte* buffer, byte width, byte height);
    size_t write(uint8_t c);
    void clear(byte x = 0, byte y = 0, byte width = 128, byte height = 64);
    void clearLine(byte line);
    byte getLines() { return 21; }
    byte getCols() { return 8; }
private:
    void writeDigit(byte n);
    byte m_col;
    byte m_row;
};

class LCD_SH1106 : public LCD_Common, public Print
{
public:
    void begin();
    void setCursor(byte column, byte line);
    void draw(const PROGMEM byte* buffer, byte width, byte height);
    size_t write(uint8_t c);
    void clear(byte x = 0, byte y = 0, byte width = 128, byte height = 64);
    void clearLine(byte line);
    byte getLines() { return 21; }
    byte getCols() { return 8; }
private:
    void WriteCommand(unsigned char ins);
    void WriteData(unsigned char dat);
    void writeDigit(byte n);
    byte m_col;
    byte m_row;
};



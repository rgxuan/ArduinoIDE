#if defined(__AVR__)  
// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

#ifndef _RTCLIB_H_
#define _RTCLIB_H_
/*
// Simple general-purpose date/time class (no TZ / DST / leap second handling!)
class DateTime {
public:
//    DateTime (uint32_t t =0);
    DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour =0, uint8_t min =0, uint8_t sec =0, uint32_t daySec=0);
    DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
//    DateTime (const char* date, const char* time);
    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
//    uint8_t dayOfWeek() const;
    uint32_t daystamp() const		{ return ds; }

    // 32-bit times as seconds since 1/1/1970
    // uint32_t unixtime(void) const;

protected:
    uint8_t yOff, m, d, hh, mm, ss;
	uint32_t ds;
};
*/
// RTC based on the DS1307 chip connected via I2C and the Wire library
class RTC_DS1307 {
public:
    static uint8_t begin(void);
//    static void adjust(const DateTime& dt);
    static void adjust(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);
//    uint8_t isrunning(void);
    void now();
	
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint32_t daystamp;
};

/*
// RTC using the internal millis() clock, has to be initialized before use
// NOTE: this clock won't be correct once the millis() timer rolls over (>49d?)
class RTC_Millis {
public:
    static void begin(const DateTime& dt) { adjust(dt); }
    static void adjust(const DateTime& dt);
    static DateTime now();

protected:
    static long offset;
};
*/
#endif // _RTCLIB_H_

#endif 
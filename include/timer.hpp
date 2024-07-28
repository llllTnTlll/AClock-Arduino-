#include "screen.hpp"
#include <TimerOne.h>

class Time{
private:
    struct tm
    {
        uint8_t hour;
        uint8_t min;
        uint8_t sec;
        uint16_t ms;
    };

    tm t;

public:
    Time(uint8_t hour, uint8_t min, uint8_t sec, uint16_t ms);
    Time();
    
    void AddTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds);
    void MinusTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds);
    String getCurrentTime();
    String getCurrentHour();
    String getCurrentMin();
    String getCurrentSec();
    String getCurrentMSec();

    // 运算符重载
    Time operator+(const Time& time) const{
        Time resultTime = Time(t.hour, t.min, t.sec, t.ms);
        resultTime.AddTime(time.t.hour, time.t.min, time.t.sec, time.t.ms);
        return resultTime;
    }
};

class StopWatch{
private:
    Screen* screen;
    Time* time;
public:
    StopWatch(Screen*& myScreen, uint16_t timerInterval);
    ~StopWatch();
    void showTime();
};
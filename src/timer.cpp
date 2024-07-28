#include "timer.hpp"

StopWatch::StopWatch(Screen *&myScreen, uint16_t timerInterval)
    : screen(myScreen)
{
    time = new Time();
}

StopWatch::~StopWatch()
{
    screen->~Screen();
}

void StopWatch::showTime()
{
    screen->Print(time->getCurrentTime(), {1,1});
}

Time::Time(uint8_t h, uint8_t m, uint8_t s, uint16_t ms)
{
    t.hour = h;
    t.min = m;
    t.sec = s;
    t.ms = ms;
}

Time::Time()
{
    t.hour = 0;
    t.min = 0;
    t.sec = 0;
    t.ms = 0;
}

void Time::AddTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds)
{
    t.ms += milliseconds;
    if (t.ms >= 1000)
    {
        t.sec += t.ms / 1000;
        t.ms %= 1000;
    }

    t.sec += seconds;
    if (t.sec >= 60)
    {
        t.min += t.sec / 60;
        t.sec %= 60;
    }

    t.min += minutes;
    if (t.min >= 60)
    {
        t.hour += t.min / 60;
        t.min %= 60;
    }

    t.hour += hours;

    // 处理超过24小时
}

void Time::MinusTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint16_t milliseconds)
{

    if (t.ms < milliseconds)
    {
        t.ms += 1000;
        t.sec--;
    }
    t.ms -= milliseconds;

    if (t.sec < seconds)
    {
        t.sec += 60;
        t.min--;
    }
    t.sec -= seconds;

    if (t.min < minutes)
    {
        t.min += 60;
        t.hour--;
    }
    t.min -= minutes;

    t.hour -= hours;
}

String Time::getCurrentTime()
{
    String timeStr = "";
    // timeStr += getCurrentHour();
    // timeStr += ":";
    timeStr += getCurrentMin();
    // timeStr += ":";
    timeStr += getCurrentSec();
    // timeStr += ".";
    timeStr += getCurrentMSec();

    return timeStr;
}

String Time::getCurrentHour()
{
    String hour = "";
    if (t.hour < 10)
        hour += "0";
    hour += String(t.hour);
    return hour;
}

String Time::getCurrentMin()
{
    String min = " ";
    if (t.min < 10)
        min += "0";
    min += String(t.min);
    return min;
}

String Time::getCurrentSec()
{
    String sec = "";
    if (t.sec < 10)
        sec += "0";
    sec += String(t.sec);
    return sec;
}

String Time::getCurrentMSec()
{
    String ms = "";
    if (t.ms < 10)
        ms += "00";
    else if (t.ms < 100)
        ms += "0";
    return ms;
}
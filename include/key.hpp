#include <Arduino.h>
#include <timer.hpp>

class KeyBoard
{
private:
    typedef enum
    {
        STOPCLOCK_ADD_MODE,
        STOPCLOCK_MINUS_MODE,
        STOPCLOCK_ADJUST_MODE,
    } RUN_MODE;

    static std::map<String, void(*)()> TaskList;    
    static RUN_MODE CURRENT_MODE;                   // 当前的键盘配置
    StopWatch* myWatch;

    void BeginClock();             

public:
    KeyBoard(StopWatch *watch);

    static void BtnAPressed();
    static void BtnBPressed();
    void TakeAction();
};

KeyBoard::RUN_MODE KeyBoard::CURRENT_MODE = STOPCLOCK_ADD_MODE; // 键盘默认状态
std::map<String, void(*)()> KeyBoard::TaskList; 

KeyBoard::KeyBoard(StopWatch *watch)
    : myWatch(watch)
{
    // 启用按键中断
    attachInterrupt(0, BtnAPressed, FALLING);  
    attachInterrupt(1, BtnBPressed, FALLING);  

}

void KeyBoard::BtnAPressed()
{
    // 根据当前的配置切换按键响应模式
    switch (CURRENT_MODE)
    {
    case STOPCLOCK_ADD_MODE:
        
        break;

    default:
        break;
    }
}

void KeyBoard::BtnBPressed()
{
    // 根据当前的配置切换按键响应模式
    switch (CURRENT_MODE)
    {
    case STOPCLOCK_ADD_MODE:

        break;

    default:
        break;
    }
}

void KeyBoard::TakeAction()
{
}

void KeyBoard::BeginClock(){
    myWatch->SetRunStatus(1);
}
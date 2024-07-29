#include <Arduino.h>

class KeyBoard
{
public:
    typedef enum
    {
        STOPCLOCK_ADD_MODE,
        STOPCLOCK_MINUS_MODE,
    } RUN_MODE;

    static RUN_MODE CURRENT_MODE;
    static void BtnAPressed();
};

// 键盘默认状态
KeyBoard::RUN_MODE KeyBoard::CURRENT_MODE = STOPCLOCK_ADD_MODE;

void KeyBoard::BtnAPressed()
{
    switch (KeyBoard::CURRENT_MODE)
    {
    case STOPCLOCK_ADD_MODE:
        
        break;

    default:
        break;
    }
}
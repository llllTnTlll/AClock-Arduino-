#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <Arduino.h>
#include "pt6315.hpp"
#include "font.hpp"

struct Coordinate
{
    uint8_t gridIndex;
    uint8_t segIndex;
};

class Screen
{
protected:
    uint8_t screenGirdNum;
    uint8_t screenSegNum;
    Font *font;
    PT6315 *driver;

    std::vector<String> ScreenContent;

    std::map<uint8_t, Coordinate> ScreenDigitBeginIndex;
    std::vector<Coordinate> ScreenSymbolsIndex;

    virtual void SetDigitBeginIndex() = 0;
    virtual void SetSymbolsIndex() = 0;
    inline std::vector<bool> ToBoolVec(String str)
    {
        std::vector<bool> bits;
        for (char ch : str)
        {
            if (ch == '0')
            {
                bits.push_back(0);
            }
            if (ch == '1')
            {
                bits.push_back(1);
            }
        }
        return bits;
    };

public:
    Screen(uint8_t gridNum, uint8_t segNum);
    ~Screen();

    // 使用之前必须要调用一下这个函数
    void Initialize(Font* f);

    void SetOnoffLightness(bool onOff, uint8_t lightness);
    void ClearScreen();
    void TestScreen();

    void PrintString(String content, std::vector<bool> symbolMask = {});
    void PrintNum(double num, uint8_t width, uint8_t prec, std::vector<bool> symbolMask = {});
    void PrintNum(int num, uint8_t width, uint8_t prec, std::vector<bool> symbolMask = {});
    void ScrollPirnt(String content, uint16_t interval);
    void DisplaySymbol(std::vector<bool> mask);
};

// 请参照这个类来重写新的屏幕类
class SamsungScreen : public Screen
{
protected:
    void SetDigitBeginIndex() override{
        ScreenDigitBeginIndex = {
            {0, Coordinate{3, 9}},
            {1, Coordinate{4, 1}},
            {2, Coordinate{4, 9}},
            {3, Coordinate{5, 1}},
            {4, Coordinate{5, 9}},
            {5, Coordinate{6, 1}},
            {6, Coordinate{6, 9}},
        };
    }

    void SetSymbolsIndex() override{
        ScreenSymbolsIndex = {
            Coordinate{4, 8},
            Coordinate{5, 8},
        };
    }
public:
    SamsungScreen(uint8_t gridNum, uint8_t segNum) : Screen(gridNum, segNum){
        Initialize(new MyFont());
    }
};

#endif
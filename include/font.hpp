#ifndef FONT_H
#define FONT_H

#include <ArxContainer.h>

// // 全局变量
// extern const String errString;
// extern const std::map<char, String> FontDic;

// String getOneCharCode(char word);

class Font
{
protected:
    String errString;
    std::map<char, String> FontDic;

public:
    inline String getOneCharCode(char word)
    {
        auto it = FontDic.find(word);
        if (it != FontDic.end())
        {
            return it->second;
        }
        else
        {
            return errString;
        }
    }
};

class MyFont : public Font
{
public:
    MyFont()
    {
        errString = "0000000";

        FontDic['0'] = "1110111";
        FontDic['1'] = "0100100";
        FontDic['2'] = "1101011";
        FontDic['3'] = "1101101";
        FontDic['4'] = "0111100";
        FontDic['5'] = "1011101";
        FontDic['6'] = "1011111";
        FontDic['7'] = "1100100";
        FontDic['8'] = "1111111";
        FontDic['9'] = "1111101";

        FontDic[' '] = "0000000";
    }
};
#endif
#ifndef FONT_H
#define FONT_H

#include <ArxContainer.h>

class Font
{
protected:
    String errString;
    std::map<char, String> FontDic;

    virtual void InitFontDic() = 0;
    virtual void InitErrString() = 0;

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
    void Initialize()
    {
        InitFontDic();
        InitErrString();
    }
};

// 参照以下格式创建自己的字体
class MyFont : public Font
{
protected:
    // 在这里定义你的字体
    void InitFontDic() override
    {
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
        FontDic['.'] = "0001000";
    }

    // 在这里定义字体缺失时的显示内容
    void InitErrString() override
    {
        errString = "0000000";
    }
};

#endif
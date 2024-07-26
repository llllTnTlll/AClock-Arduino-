#include <pt6315.hpp>

PT6315::PT6315(CMD1_SCAN_MODE scanMode, uint8_t lightness, uint8_t maxRow, uint8_t maxColumn)
    : registerMaxRow(maxRow),
      registerMaxColumn(maxColumn),
      registerBufferLen(registerMaxRow * (registerMaxColumn / 8)),
      CURRENT_SCAN_MODE(scanMode),
      CURRENT_LIGHTNESS(lightness)
{
    // 初始化Buffer
    Buffer = new bool *[registerMaxRow];
    for (int i = 0; i < registerMaxRow; ++i)
    {
        Buffer[i] = new bool[registerMaxColumn]{0};
    }

    // 以地址自增模式初始化芯片
    delay(200);
    PT6315_ClearAll();
    PT6315_SetScanMode(CURRENT_SCAN_MODE);
    PT6315_SetScreen(1, 7);
}

PT6315::~PT6315()
{
    // 析构时销毁Buffer
    for (int i = 0; i < registerMaxRow; ++i)
    {
        delete[] Buffer[i];
    };
    delete[] Buffer;
}

void PT6315::PT6315_SendCMD(uint8_t cmd)
{
    digitalWrite(10, LOW);
    SPI.transfer(cmd);
    digitalWrite(10, HIGH);
    delay(1);
}

void PT6315::PT6315_SendDTA_AutoAdr(uint8_t *sendBuf)
{
    PT6315_SendCMD(AUTO_ADR_WRITE_DISPLAY);

    digitalWrite(10, LOW);
    SPI.transfer(SET_ADR_TO_00H);

    for (int i = 0; i < registerBufferLen; i++)
    {
        SPI.transfer(sendBuf[i]);
    }

    digitalWrite(10, HIGH);
    delay(10);
}

void PT6315::PT6315_ClearAll()
{
    for (int i = 1; i <= registerMaxRow; ++i)
    {
        for (int j = 1; j <= registerMaxColumn; ++j)
        {
            PT6315_WriteBuffer(i, j, 0);
        }
    }

    uint8_t *buf = PT6315_GetSendBuf();
    PT6315_SendDTA_AutoAdr(buf);
    delete[] buf;
}

// 危险，注意内存溢出
uint8_t *PT6315::PT6315_GetSendBuf()
{
    uint8_t *flattenBuf = new uint8_t[registerBufferLen];
    int k = 0;
    for (int i = 0; i < registerMaxRow; ++i)
    {
        for (int j = 0; j < registerMaxColumn; j += 8)
        {
            uint8_t byte = 0;
            for (int bit = 0; bit < 8; ++bit)
            {
                byte |= (Buffer[i][j + bit] << (7 - bit));
            }
            flattenBuf[k++] = reverseByte(byte);
        }
    }
    return flattenBuf;
}

void PT6315::PT6315_ShowFrame()
{
    PT6315_SendCMD(AUTO_ADR_WRITE_DISPLAY);
    PT6315_SendCMD(SET_ADR_TO_00H);
    uint8_t *buf = PT6315_GetSendBuf();
    PT6315_SendDTA_AutoAdr(buf);
    delete[] buf;
    PT6315_SetScanMode(CURRENT_SCAN_MODE);
    PT6315_SetScreen(1, CURRENT_LIGHTNESS);
}

void PT6315::PT6315_WriteBuffer(uint8_t grid, uint8_t seg, bool bit)
{
    Buffer[grid - 1][seg - 1] = bit;
}

uint8_t PT6315::reverseByte(uint8_t byte)
{
    uint8_t reversed = 0;
    for (int i = 0; i < 8; i++)
    {
        reversed <<= 1;
        reversed |= (byte & 1);
        byte >>= 1;
    }
    return reversed;
}

void PT6315::PT6315_SetScreen(bool onOff, uint8_t lightness)
{
    if (lightness <= 7)
    {
        uint8_t cmd4_temp = 0b10000000;
        if (onOff)
        {
            cmd4_temp |= 0b00001000;
        }
        cmd4_temp |= lightness;
        PT6315_SendCMD(cmd4_temp);
    }
}

void PT6315::PT6315_SetScanMode(CMD1_SCAN_MODE scanMode)
{
    PT6315_SendCMD(scanMode);
}

void PT6315::PT6315_Test(uint8_t screenGridNum, uint8_t screenSegNum)
{
    for (int i = 0; i < screenSegNum; ++i)
    {
        PT6315_ClearAll();
        for (int j = 1; j <= screenGridNum; ++j)
        {
            PT6315_WriteBuffer(j, i, 1);
        }
        PT6315_ShowFrame();
        delay(1000);
    }
}
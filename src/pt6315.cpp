#include <pt6315.hpp>


PT6315::PT6315()
{
    // 初始化Buffer
    Buffer = new bool *[registerMaxRow];
    for (int i = 0; i < registerMaxRow; ++i)
    {
        Buffer[i] = new bool[registerMaxColumn]{0};
    }

    // 以地址自增模式初始化芯片
    delay(200);
    PT6315_ClearRegister();    // 这里的清除寄存器里已经带了cmd2和3了
    PT6315_SendCMD(SCAN_MODE_8D20S);
    PT6315_SendCMD(DISPLAY_ON_HIGH_LIGHT);
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

void PT6315::PT6315_ClearRegister(){
    uint8_t buffer[registerBufferLen]{0};
    PT6315_SendDTA_AutoAdr(buffer);
}

// 危险，注意内存溢出
uint8_t* PT6315::PT6315_GetSendBuf(){
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

void PT6315::PT6315_ShowFrame(){
    PT6315_SendCMD(AUTO_ADR_WRITE_DISPLAY);
    PT6315_SendCMD(SET_ADR_TO_00H);
    uint8_t* buf = PT6315_GetSendBuf();
    PT6315_SendDTA_AutoAdr(buf);
    delete[] buf;
    PT6315_SendCMD(SCAN_MODE_8D20S);
    PT6315_SendCMD(DISPLAY_ON_HIGH_LIGHT);
}

void PT6315::PT6315_WriteBuffer(uint8_t grid, uint8_t seg, bool bit){
    Buffer[grid-1][seg-1] = bit;
}

uint8_t PT6315::reverseByte(uint8_t byte){
    uint8_t reversed = 0;
    for (int i = 0; i < 8; i++) {
        reversed <<= 1;          
        reversed |= (byte & 1);     
        byte >>= 1;              
    }
    return reversed;
}
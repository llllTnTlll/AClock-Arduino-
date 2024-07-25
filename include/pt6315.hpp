#include <SPI.h>

// command1
/*
 * 显示模式设定
 * 0 0 - - b3 b2 b1 b0
 *
 * b3~b0: 0100 8区域16分隔符
 */
typedef enum
{
    SCAN_MODE_6D22S = 0b00000010,
    SCAN_MODE_8D20S = 0b00000100,
    SCAN_MODE_12D16S = 0b00001000,
} CMD1_SCAN_MODE;

// command2
/*
 * 数据设置命令
 * 0 1 - - b3 b2 b1 b0
 *
 * b3: 0 for 普通模式
 *     1 for 测试模式
 *
 * b2: 0 for 地址自增
 *     1 for 指定地址
 *
 * b1&b0: 00 向显示器寄存器写数据
 *        01 向驱动芯片LED写数据
 *        10 读取矩阵键盘数据
 *        11 无效
 *
 */
typedef enum
{
    AUTO_ADR_WRITE_DISPLAY = 0b01000000,
    FIXED_ADR_WRITE_DISPLAY = 0b01000100,
} CMD2_DTA_SET;

// command3
/*
 * 地址设置模式
 * 1 1 b5 b4 b3 b2 b1 b0
 *
 * b5-b0 地址
 */
typedef enum
{
    SET_ADR_TO_00H = 0b11000000,

} CMD3_ADR_SET;

// command4
/*
 * 显示开关与亮度
 * 1 0 - - b3 b2 b1 b0
 *
 * b3 for 开关显示
 * b2~b0: 显示亮度
 */
typedef enum
{
    DISPLAY_ON_HIGH_LIGHT = 0b10001111,
    DISPLAY_OFF_MID_LIGHT = 0b10000100,
} CMD4_ONOFF_LIGHT;

class PT6315
{
private:
    bool **Buffer;
    uint8_t registerMaxRow = 12;
    uint8_t registerMaxColumn = 24;
    uint8_t registerBufferLen = registerMaxRow * (registerMaxColumn / 8);
    

    void PT6315_SendCMD(uint8_t cmd);
    void PT6315_SendDTA_AutoAdr(uint8_t *sendBuf);
    void PT6315_ClearRegister();
    uint8_t* PT6315_GetSendBuf();
    uint8_t reverseByte(uint8_t byte);

public:
    PT6315();
    ~PT6315();
    void PT6315_WriteBuffer(uint8_t grid, uint8_t column, bool bit);
    void PT6315_ShowFrame();
};

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
    PT6315_SendCMD(SCAN_MODE_6D22S);
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

            uint8_t reversed = reverseByte(byte);
            flattenBuf[k++] = reversed;
            Serial.println(reversed, BIN);
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
    PT6315_SendCMD(SCAN_MODE_6D22S);
    PT6315_SendCMD(DISPLAY_ON_HIGH_LIGHT);
}

void PT6315::PT6315_WriteBuffer(uint8_t grid, uint8_t seg, bool bit){
    Buffer[grid-1][seg-1] = bit;
}

uint8_t PT6315::reverseByte(uint8_t byte){
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result <<= 1;          // 左移result
        result |= (byte & 1);     // 取出n的最低位并赋给result
        byte >>= 1;               // 右移n
    }
    return result;
}
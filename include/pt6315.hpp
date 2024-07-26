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

class PT6315
{
private:
    bool **Buffer;
    uint8_t registerMaxRow;
    uint8_t registerMaxColumn;
    uint8_t registerBufferLen;

    CMD1_SCAN_MODE CURRENT_SCAN_MODE;
    uint8_t CURRENT_LIGHTNESS;

    void PT6315_SendCMD(uint8_t cmd);
    void PT6315_SendDTA_AutoAdr(uint8_t *sendBuf);
    void PT6315_ClearAll();
    uint8_t* PT6315_GetSendBuf();
    uint8_t reverseByte(uint8_t byte);

public:
    PT6315(CMD1_SCAN_MODE scanMode, uint8_t lightness, uint8_t registerMaxRow=12, uint8_t registerMaxColumn=24);
    ~PT6315();
    void PT6315_WriteBuffer(uint8_t grid, uint8_t column, bool bit);
    void PT6315_ShowFrame();
    void PT6315_SetScreen(bool onOff, uint8_t lightness);
    void PT6315_SetScanMode(CMD1_SCAN_MODE scanMode);
    void PT6315_Test(uint8_t screenGridNum, uint8_t screenSegNum);
};
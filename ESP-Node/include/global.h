#ifndef INCLUDE_GLOBAL_H
#define INCLUDE_GLOBAL_H

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>

// Trạng thái nút nhấn (sử dụng INPUT_PULLUP: thả = HIGH/1, nhấn = LOW/0)
#define NORMAL_STATE    HIGH
#define PRESSED_STATE   LOW

// Cấu hình số lượng nút và thời gian giữ nút (theo số chu kỳ gọi getKeyInput)
// Ví dụ: gọi getKeyInput() mỗi 10ms -> 100 chu kỳ = 1000ms (1 giây)
#define MAX_BUTTON      5
#define TIME_FOR_HOLD   100

// Định nghĩa chân GPIO cho các nút trên ESP32-S3 N16R8 (chỉnh lại theo mạch thực tế)
// Lưu ý: Tránh các chân OPI PSRAM (GPIO 33-37) và USB (GPIO 19-20)
#define BUTTON_1_PIN    4
#define BUTTON_2_PIN    5
#define BUTTON_3_PIN    6
#define BUTTON_4_PIN    7
#define BUTTON_5_PIN    15

// Chỉ số (index) của từng nút trong mảng button[]
#define BTN_1           0
#define BTN_2           1
#define BTN_3           2
#define BTN_4           3
#define BTN_5           4

// Định nghĩa thành phần nút
typedef struct {
    volatile bool pressFlag;
    uint32_t timeForPress;
    volatile bool holdFlag;
    uint8_t reg0;
    uint8_t reg1;
    uint8_t reg2;
    uint8_t reg3;
} buttonFeat;

// Biến toàn cục dùng chung
extern buttonFeat button[MAX_BUTTON];
extern const uint8_t buttonPin[MAX_BUTTON];

#endif // INCLUDE_GLOBAL_H

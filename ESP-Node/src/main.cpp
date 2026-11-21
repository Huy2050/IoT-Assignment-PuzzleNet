#include <Arduino.h>
#include <Wire.h>
#include "global.h"
#include "button.h"
#include "LiquidCrystal_I2C.h"

// Cấu hình chân I2C cho ESP32-S3 (mặc định DevKitC-1: SDA = 8, SCL = 9)
#define I2C_SDA         8
#define I2C_SCL         9

// Cấu hình LCD I2C (địa chỉ thường là 0x27 hoặc 0x3F, kích thước 16x2 hoặc 20x4)
#define LCD_ADDR        0x27
#define LCD_COLS        16
#define LCD_ROWS        2

// Chu kỳ quét nút nhấn (10ms -> TIME_FOR_HOLD = 100 tương đương giữ 1 giây)
#define BUTTON_SCAN_MS  10

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

// void taskReadButton(void *pvParameters) {
//     (void)pvParameters;
//     for (;;) {
//         getKeyInput();
//         vTaskDelay(pdMS_TO_TICKS(BUTTON_SCAN_MS));
//     }
// }

void taskHandleButtons(void *pvParameters) {
    (void)pvParameters;
    for (;;) {
        for (int i = 0; i < MAX_BUTTON; i++) {
            if (isButtonPressed(i)) {
                Serial.printf("Button %d PRESSED\n", i + 1);
                lcd.setCursor(0, 1);
                lcd.printf("BTN %d: PRESSED  ", i + 1);
            }

            if (isButtonHold(i)) {
                Serial.printf("Button %d HOLD\n", i + 1);
                lcd.setCursor(0, 1);
                lcd.printf("BTN %d: HOLD     ", i + 1);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("ESP32-S3 Node Starting...");

    // Khởi tạo I2C và LCD
    Wire.begin(I2C_SDA, I2C_SCL);
    lcd.begin();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ESP32-S3 Ready");
    lcd.setCursor(0, 1);
    lcd.print("Waiting input...");

    // Khởi tạo nút nhấn và tạo các FreeRTOS task
    initButton();
    xTaskCreate(getKeyInput, "Read button", 2048, NULL, 2, NULL);
    xTaskCreate(taskHandleButtons, "Handle button", 4096, NULL, 1, NULL);

    Serial.println("Setup complete.");
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}

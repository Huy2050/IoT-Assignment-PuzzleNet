#include "button.h"

void initButton(void) {
    for (int i = 0; i < MAX_BUTTON; i++) {
        pinMode(buttonPin[i], INPUT_PULLUP);
        button[i].reg0 = NORMAL_STATE;
        button[i].reg1 = NORMAL_STATE;
        button[i].reg2 = NORMAL_STATE;
        button[i].reg3 = NORMAL_STATE;
        button[i].pressFlag = false;
        button[i].holdFlag = false;
        button[i].timeForPress = TIME_FOR_HOLD;
    }
}

bool isButtonPressed(int idx) {
    if (idx < 0 || idx >= MAX_BUTTON) {
        return false;
    }
    if (button[idx].pressFlag) {
        button[idx].pressFlag = false;
        return true;
    }
    return false;
}

bool isButtonHold(int idx) {
    if (idx < 0 || idx >= MAX_BUTTON) {
        return false;
    }
    if (button[idx].holdFlag){
        button[idx].holdFlag = false;
        return true;
    }
    return false;
}

void getKeyInput(void *pvParameters) {
    (void)pvParameters;
    for (int i = 0; i < MAX_BUTTON; i++) {
        // Dịch 3 thanh ghi trạng thái liên tiếp để chống dội (debounce)
        button[i].reg2 = button[i].reg1;
        button[i].reg1 = button[i].reg0;
        button[i].reg0 = digitalRead(buttonPin[i]);

        // Chỉ xử lý khi cả 3 lần đọc liên tiếp đều cho cùng một trạng thái
        if ((button[i].reg1 == button[i].reg0) && (button[i].reg1 == button[i].reg2)) {
            if (button[i].reg3 != button[i].reg2) {
                // Trạng thái ổn định mới khác với trạng thái ổn định trước đó
                button[i].reg3 = button[i].reg2;

                if (button[i].reg3 == PRESSED_STATE) {
                    button[i].pressFlag = true;
                    button[i].timeForPress = TIME_FOR_HOLD;
                } else {
                    // Đã thả nút
                    button[i].holdFlag = false;
                    button[i].timeForPress = TIME_FOR_HOLD;
                }
            } else {
                // Trạng thái giữ nguyên: kiểm tra nhấn giữ (hold)
                if (button[i].reg3 == PRESSED_STATE) {
                    if (button[i].timeForPress > 0) {
                        button[i].timeForPress--;
                        if (button[i].timeForPress == 0) {
                            button[i].holdFlag = true;
                        }
                    }
                }
            }
        }
    }
}

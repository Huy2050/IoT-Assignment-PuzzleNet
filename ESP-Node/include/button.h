#ifndef INCLUDE_BUTTON_H
#define INCLUDE_BUTTON_H

#include "global.h"

void initButton(void);
void getKeyInput(void *pvParameters);
bool isButtonPressed(int idx);
bool isButtonHold(int idx);

#endif // INCLUDE_BUTTON_H

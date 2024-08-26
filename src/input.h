#pragma once

#include <Arduino.h>
#include <Button2.h>

void initInput();
void loopInput();
void buttonHandler(Button2& button);
// void executeCommand(byte button);

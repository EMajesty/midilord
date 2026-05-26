#include <LiquidCrystal.h>
#include "config.h"
#include "display.h"

// The 4x40 display is two 4x20 HD44780 controllers sharing RS and the 4-bit
// data bus, distinguished by separate enable lines (EN1 / EN2).
static LiquidCrystal lcd1(LCD_RS, LCD_EN1, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
static LiquidCrystal lcd2(LCD_RS, LCD_EN2, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setupDisplay() {
    lcd1.begin(20, 4);
    lcd2.begin(20, 4);

    lcd1.setCursor(0, 0);
    lcd1.print("Hello, World!");
}

void loopDisplay() {}

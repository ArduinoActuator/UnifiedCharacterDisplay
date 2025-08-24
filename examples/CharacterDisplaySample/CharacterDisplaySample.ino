
#include "UnifiedCharacterDisplay.h"

//#define USE_GROVE
//#define USE_LIQUID_CRYSTAL
#define USE_ACM1602NI

#ifdef USE_GROVE
rgb_lcd grove_lcd;
UnifiedLCD lcd(&(grove_lcd), GROVE_LCD_RGB_BACKLIGHT, Wire);
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal liquid_crystal_h(rs, en, d4, d5, d6, d7);
UnifiedLCD liquid_crystal(&liquid_crystal_h, LIQUID_CRYSTAL);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
ACM1602NI liquid_crystal_i2c_h;  // set the LCD address to 0x27 for a 16 chars and 2 line display
UnifiedLCD liquid_crystal_i2c(&liquid_crystal_i2c_h, ACM1602NI_TYPE);
#endif /* USE_ACM1602NI */

void clearDisplay(void){
#ifdef USE_GROVE
  lcd.setCursor(0, 0);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.setCursor(0, 0);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.setCursor(0, 0);
#endif /* USE_ACM1602NI */

#ifdef USE_GROVE
  lcd.setBacklightRGB(255, 255, 255);
#endif /* USE_GROVE */

#ifdef USE_GROVE
  lcd.setCursor(0, 1);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.setCursor(0, 1);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.setCursor(0, 1);
#endif /* USE_ACM1602NI */

#ifdef USE_GROVE
  lcd.clear();
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.clear();
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.clear();
#endif /* USE_ACM1602NI */

}

void helloWorld(void){
  Serial.println("Hello World : start");

#ifdef USE_GROVE
  lcd.setCursor(0, 0);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.setCursor(0, 0);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.setCursor(0, 0);
#endif /* USE_ACM1602NI */

#ifdef USE_GROVE
  lcd.setBacklightRGB(colorR, colorG, colorB);
#endif /* USE_GROVE */

  // Print a message to the LCD.

#ifdef USE_GROVE
  lcd.print("hello, world!");
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.print("hello, world!");
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.print("hello, world!");
#endif /* USE_ACM1602NI */

  delay(100);

  for (int i=0 ; i< 100; i++) {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
#ifdef USE_GROVE
  lcd.setCursor(0, 1);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.setCursor(0, 1);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.setCursor(0, 1);
#endif /* USE_ACM1602NI */

  // print the number of seconds since reset:

#ifdef USE_GROVE
  lcd.print(millis() / 1000);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.print(millis() / 1000);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.print(millis() / 1000);
#endif /* USE_ACM1602NI */
  delay(100);
  }

  Serial.println("Hello World : end");
  
}

void autoScroll(void) {
  Serial.println("Auto Scroll : start");
#ifdef USE_GROVE
  lcd.setCursor(0, 0);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.setCursor(0, 0);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.setCursor(0, 0);
#endif /* USE_ACM1602NI */

  for (int thisChar = 0; thisChar < 10; thisChar++) {
#ifdef USE_GROVE
    lcd.print(thisChar);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
    liquid_crystal.print(thisChar);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
    liquid_crystal_i2c.print(thisChar);
#endif /* USE_ACM1602NI */
    delay(500);
  }

    // set the cursor to (16,1):
#ifdef USE_GROVE
  lcd.setCursor(16, 1);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.setCursor(16, 1);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.setCursor(16, 1);
#endif /* USE_ACM1602NI */
  // set the display to automatically scroll:
#ifdef USE_GROVE
  lcd.setMode(AUTO_SCROLL);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.setMode(AUTO_SCROLL);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.setMode(AUTO_SCROLL);
#endif /* USE_ACM1602NI */

  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
#ifdef USE_GROVE
    lcd.print(thisChar);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
    liquid_crystal.print(thisChar);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
    liquid_crystal_i2c.print(thisChar);
#endif /* USE_ACM1602NI */
    delay(500);
  }
  // turn off automatic scrolling
#ifdef USE_GROVE
  lcd.setMode(NO_AUTO_SCROLL);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.setMode(NO_AUTO_SCROLL);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.setMode(NO_AUTO_SCROLL);
#endif /* USE_ACM1602NI */

  Serial.println("Auto Scroll : end");

}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  // set up the LCD's number of columns and rows:
#ifdef USE_GROVE
  lcd.begin(16, 2);
#endif /* USE_GROVE */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.begin(16, 2);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.begin(16, 2);
#endif /* USE_ACM1602NI */
}

void loop() {
  clearDisplay();
  helloWorld();
  delay(100);
  clearDisplay();
  autoScroll();
  clearDisplay();
}


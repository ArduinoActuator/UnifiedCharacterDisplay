#ifndef __UNIFIED_CHARACTER_DISPLAY_H__
#define __UNIFIED_CHARACTER_DISPLAY_H__




#define LCD_HAL_USE_GROVE
#define LCD_HAL_USE_LIQUID_CRYSTAL
#define LCD_HAL_USE_ACM1602NI


#include "UnifiedCharacterDisplay_config.h"


#ifdef LCD_HAL_USE_GROVE
#include <Wire.h>
#include "rgb_lcd.h"
#endif /* LCD_HAL_USE_GROVE */

#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
#include "LiquidCrystal.h"
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */

#ifdef LCD_HAL_USE_ACM1602NI
#include <Wire.h>
#include <ACM1602NI.h>
#endif /* LCD_HAL_USE_ACM1602NI */


enum UnifiedLcdType {
  GROVE_LCD_RGB_BACKLIGHT =1, // https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/
  LIQUID_CRYSTAL,             // LiquidCrystal Library for Arduino https://github.com/arduino-libraries/LiquidCrystal
  LIQUID_CRYSTAL_I2C          // https://github.com/furushei/ACM1602NI-Arduino
};

enum UnifiedLcdMode {
  NO_DISPLAY = 1 ,
  ON_DISPLAY,
  NO_BLINK,
  BLINK,
  NO_CURSOR,
  CURSOR,
  SCROLL_LEFT,
  SCROLL_RIGHT,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
  AUTO_SCROLL,
  NO_AUTO_SCROLL
};

enum lcdFunctionReturnValue {
  FUNCTION_UNSUPPORTED = 1,
  FUNCTION_SUCCESS,
  FUNCTION_FAIL,
};

class UnifiedLCD : public Print {
public:
#ifdef LCD_HAL_USE_GROVE
  UnifiedLCD(rgb_lcd* lcd, UnifiedLcdType type, TwoWire  wire);
#endif /* LCD_HAL_USE_GROVE  */

#ifdef LCD_HAL_USE_ACM1602NI
  UnifiedLCD(ACM1602NI* lcd, UnifiedLcdType type);
#endif /* LCD_HAL_USE_ACM1602NI */

#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
  UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type);
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */

#if defined(LCD_HAL_USE_GROVE) || defined(LCD_HAL_USE_LIQUID_CRYSTAL)
  lcdFunctionReturnValue begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
#else /* LCD_HAL_USE_GROVE || LCD_HAL_USE_LIQUID_CRYSTAL */
  lcdFunctionReturnValue begin(uint8_t cols, uint8_t rows, uint8_t charsize = 0);
#endif /* LCD_HAL_USE_GROVE || LCD_HAL_USE_LIQUID_CRYSTAL */

  lcdFunctionReturnValue clear(void);
  lcdFunctionReturnValue home(void);
  lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
  lcdFunctionReturnValue createChar(uint8_t, uint8_t[]);
  lcdFunctionReturnValue createCharFromProgmem(uint8_t, uint8_t *);
  lcdFunctionReturnValue setCursor(uint8_t, uint8_t);
  size_t write(uint8_t);
  lcdFunctionReturnValue command(uint8_t);
  lcdFunctionReturnValue setBrightness(uint8_t = 2, uint8_t = 0x40, uint8_t = 0xc0); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  // color control
  lcdFunctionReturnValue setBacklightRGB(unsigned char r, unsigned char g, unsigned char b); // set rgb
  // blink the LED backlight
  lcdFunctionReturnValue blinkBacklight(void);
  lcdFunctionReturnValue noBlinkBacklight(void);

private:
  lcdFunctionReturnValue noDisplay(void);
  lcdFunctionReturnValue display(void);
  lcdFunctionReturnValue noBlink(void);
  lcdFunctionReturnValue blink(void);
  lcdFunctionReturnValue noCursor(void);
  lcdFunctionReturnValue cursor(void);
  lcdFunctionReturnValue scrollDisplayLeft(void);
  lcdFunctionReturnValue scrollDisplayRight(void);
  lcdFunctionReturnValue leftToRight(void);
  lcdFunctionReturnValue rightToLeft(void);
  lcdFunctionReturnValue autoscroll(void);
  lcdFunctionReturnValue noAutoscroll(void);
#if defined(LCD_HAL_USE_GROVE) || defined(LCD_HAL_USE_ACM1602NI)
  TwoWire  _i2c;
#endif /* LCD_HAL_USE_GROVE || LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_GROVE
  rgb_lcd* _lcd;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
  ACM1602NI* _liquid_crystal_i2c;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
  LiquidCrystal* _liquid_crystal;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  UnifiedLcdType _type;
};




#endif /* __UNIFIED_CHARACTER_DISPLAY_H__ */


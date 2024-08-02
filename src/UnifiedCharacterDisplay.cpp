
#include "UnifiedCharacterDisplay.h"


#ifdef LCD_HAL_USE_GROVE
UnifiedLCD::UnifiedLCD(rgb_lcd* lcd, UnifiedLcdType type, TwoWire wire):
  _lcd(lcd),
  _type(type),
  _i2c(wire)
{}
#endif /* LCD_HAL_USE_GROVE  */

#ifdef LCD_HAL_USE_ACM1602NI
UnifiedLCD::UnifiedLCD(ACM1602NI* lcd, UnifiedLcdType type):
  _liquid_crystal_i2c(lcd),
  _type(type)
{}
#endif /* LCD_HAL_USE_ACM1602NI */

#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
UnifiedLCD::UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type):
  _liquid_crystal(lcd),
  _type(type)
{}
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */

lcdFunctionReturnValue UnifiedLCD::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->begin(cols, rows, charsize, _i2c);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->begin(cols, rows);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->begin(cols, rows, charsize);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::clear(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->clear();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->clear();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->clear();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::home(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->home();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->home();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->home();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::setMode(UnifiedLcdMode mode) {
  switch(mode) {
    case NO_DISPLAY: return noDisplay();
    case ON_DISPLAY: return display();
    case NO_BLINK: return noBlink();
    case BLINK: return blink();
    case NO_CURSOR: return noCursor();
    case CURSOR: return cursor();
    case SCROLL_LEFT: return scrollDisplayLeft();
    case SCROLL_RIGHT: return scrollDisplayRight();
    case LEFT_TO_RIGHT: return leftToRight();
    case RIGHT_TO_LEFT: return rightToLeft();
    case AUTO_SCROLL: return autoscroll();
    case NO_AUTO_SCROLL: return noAutoscroll();
    case BLINK_BACKLIGHT: return blinkBacklight();
    case NO_BLINK_BACKLIGHT: return noBlinkBacklight();
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noDisplay(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noDisplay();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->noDisplay();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->noDisplay();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::display(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->display();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->display();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->display();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noBlink(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noBlink();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->noBlink();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->noBlink();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::blink(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->blink();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->blink();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->blink();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noCursor(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noCursor();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->noCursor();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->noCursor();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::cursor(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->cursor();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->cursor();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->cursor();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::scrollDisplayLeft(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->scrollDisplayLeft();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->scrollDisplayLeft();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->scrollDisplayLeft();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::scrollDisplayRight(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->scrollDisplayRight();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->scrollDisplayRight();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->scrollDisplayRight();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::leftToRight(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->leftToRight();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->leftToRight();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->leftToRight();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::rightToLeft(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->rightToLeft();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->rightToLeft();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->rightToLeft();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::autoscroll(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->autoscroll();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->autoscroll();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->autoscroll();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noAutoscroll(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noAutoscroll();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->noAutoscroll();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->noAutoscroll();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::createChar(uint8_t c, uint8_t data[]) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->createChar(c, data);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->createChar(c, data);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->createChar(c, data);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::createCharFromProgmem(uint8_t c, uint8_t * p) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->createChar(c, p);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->createChar(c, p);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->createChar(c, p);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::setCursor(uint8_t col, uint8_t row) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->setCursor(col, row);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->setCursor(col, row);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->setCursor(col, row);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

size_t UnifiedLCD::write(uint8_t value) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      return _lcd->write(value);
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      return _liquid_crystal_i2c->write(value);
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      return _liquid_crystal->write(value);
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return -1;
}

lcdFunctionReturnValue UnifiedLCD::command(uint8_t value) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->command(value);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->command(value);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->command(value);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::setBacklightRGB(unsigned char r, unsigned char g, unsigned char b) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->setRGB(r, g, b);
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::blinkBacklight(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->blinkLED();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
  }
  return FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noBlinkBacklight(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noBlinkLED();
      return FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
  }
  return FUNCTION_UNSUPPORTED;
}



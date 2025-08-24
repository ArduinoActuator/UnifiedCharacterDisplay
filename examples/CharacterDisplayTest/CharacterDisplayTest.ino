
/*
 * NanoやMKRをClassic (UNO)のシールドを使えるようにするための変換基板を使うか否かの選択
 */
#define USE_CONVERTER

/*
 * LCDの選択
 */
//#define USE_GROVE
#define USE_LIQUID_CRYSTAL
//#define USE_ACM1602NI

//#define USE_SC1602BSLB
#define USE_SC2004CSLB

/*
 * ピン番号の定義
 */
#ifdef USE_LIQUID_CRYSTAL
#ifdef USE_SC1602BSLB
#ifdef USE_CONVERTER
#define LIQUID_CRYSTAL_PIN_RS DIGITAL_7
#define LIQUID_CRYSTAL_PIN_ES DIGITAL_6
#define LIQUID_CRYSTAL_PIN_D4 DIGITAL_5
#define LIQUID_CRYSTAL_PIN_D5 DIGITAL_4
#define LIQUID_CRYSTAL_PIN_D6 DIGITAL_3
#define LIQUID_CRYSTAL_PIN_D7 DIGITAL_2
#else /* USE_CONVERTER */
#define LIQUID_CRYSTAL_PIN_RS 7
#define LIQUID_CRYSTAL_PIN_ES 6
#define LIQUID_CRYSTAL_PIN_D4 5
#define LIQUID_CRYSTAL_PIN_D5 4
#define LIQUID_CRYSTAL_PIN_D6 3
#define LIQUID_CRYSTAL_PIN_D7 2
#endif /* USE_CONVERTER */
#endif /* USE_SC1602BSLB */
#ifdef USE_SC2004CSLB
#ifdef USE_CONVERTER
#define LIQUID_CRYSTAL_PIN_RS DIGITAL_12
#define LIQUID_CRYSTAL_PIN_ES DIGITAL_10
#define LIQUID_CRYSTAL_PIN_D4 DIGITAL_5
#define LIQUID_CRYSTAL_PIN_D5 DIGITAL_4
#define LIQUID_CRYSTAL_PIN_D6 DIGITAL_3
#define LIQUID_CRYSTAL_PIN_D7 DIGITAL_2
#else /* USE_CONVERTER */
#define LIQUID_CRYSTAL_PIN_RS 12
#define LIQUID_CRYSTAL_PIN_ES 10
#define LIQUID_CRYSTAL_PIN_D4 5
#define LIQUID_CRYSTAL_PIN_D5 4
#define LIQUID_CRYSTAL_PIN_D6 3
#define LIQUID_CRYSTAL_PIN_D7 2
#endif /* USE_CONVERTER */
#endif /* USE_SC2004CSLB */

/*
 * 行と列数の定義
 */
#ifdef USE_LIQUID_CRYSTAL
#ifdef USE_SC2004CSLB
#define LCD_MAX_ROW 4
#define LCD_MAX_COLS 20
#else /* USE_SC2004CSLB */
#define LCD_MAX_ROW 2
#define LCD_MAX_COLS 16
#endif /* USE_SC2004CSLB */
#else /* USE_LIQUID_CRYSTAL */
#define LCD_MAX_ROW 2
#define LCD_MAX_COLS 16
#endif /* USE_LIQUID_CRYSTAL */


#include "UnifiedCharacterDisplay.h"
#include "detectArduinoHardware.h"

#ifdef USE_CONVERTER
#include "ArduinoShieldConverter.h"
#endif /* USE_CONVERTER */



#ifdef USE_GROVE
rgb_lcd grove_lcd;
UnifiedLCD lcd(&(grove_lcd), GROVE_LCD_RGB_BACKLIGHT, Wire);
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
#endif /* USE_GROVE */

const int rs = LIQUID_CRYSTAL_PIN_RS, en = LIQUID_CRYSTAL_PIN_ES, d4 = LIQUID_CRYSTAL_PIN_D4, d5 = LIQUID_CRYSTAL_PIN_D5, d6 = LIQUID_CRYSTAL_PIN_D6, d7 = LIQUID_CRYSTAL_PIN_D7;
LiquidCrystal liquid_crystal_h(rs, en, d4, d5, d6, d7);
UnifiedLCD lcd(&liquid_crystal_h, LIQUID_CRYSTAL);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
ACM1602NI liquid_crystal_i2c_h;
UnifiedLCD lcd(&liquid_crystal_i2c_h, ACM1602NI_TYPE);
#endif /* USE_ACM1602NI */

#define MAX_BUFF_SIZE 256

#ifdef USE_GROVE
#define MAX_TEST 8
#else
#define MAX_TEST 7
#endif

struct testResultEntity {
  bool result;
  char about[MAX_BUFF_SIZE];
  char comment[MAX_BUFF_SIZE];
} testResult[MAX_TEST];

void printStartMessage(String about, uint8_t testNumber){
  char message[MAX_BUFF_SIZE];
  for (int i=0; i<MAX_BUFF_SIZE ; i++ ){
    message[i]=0;
  }
  sprintf(message,"Wait for start test No.%d (%s)",testNumber+1, about.c_str());
  Serial.println(message);
}

void waitForStart(void){
  while (true) {
    if (Serial.available()) {
      char input = Serial.read();
    } else {
      break;
    }
  }
  Serial.print("Please press Enter key to start test : ");
  while (true) {
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n');  // Read until newline
      if (0==input.compareTo("")) {
        Serial.println("");
        break;
      } else {
        Serial.println("");
        Serial.println("Please press **Enter key Only** to start test : ");
      }
    }
  }
}

void checkTestResult(String about, uint8_t testNumber){
  char message[MAX_BUFF_SIZE];
  for (int i=0; i<MAX_BUFF_SIZE ; i++ ){
    message[i]=0;
    testResult[testNumber].about[i]=0;
    testResult[testNumber].comment[i]=0;
  }
  sprintf(message,"Please input the failure of test No.%d (%s), if the test is succeeded, press Enter only : ",testNumber+1, about.c_str());
  sprintf(testResult[testNumber].about,"%s", about.c_str());
  testResult[testNumber].result = true;
  Serial.print(message);
  int count =0;
  while (true) {
    if (Serial.available() > 0) {
      char input = Serial.read();
      if ((input != -1) && (input != '\n')) {
        testResult[testNumber].comment[count]=input;
        testResult[testNumber].result = false;
        count++;
        Serial.print(input);
      }
      if ((count == MAX_BUFF_SIZE-2) || (input == '\n')) break;
    }
  }
  Serial.println("");
}

void sumTestResult(void){
  int count = 0;
  Serial.println("======== summary of tests ========");
  for (int i=0 ; i<MAX_TEST ; i++ ) {
    char message[MAX_BUFF_SIZE];
    for (int i=0; i<MAX_BUFF_SIZE; i++) {
      message[i]=0;
    }
    if (testResult[i].result) {
      sprintf(message,"Test result of test No.%d (%s) : Success.",i+1, testResult[i].about);
    } else {
      count++;
      sprintf(message,"Test result of test No.%d (%s) : %s",i+1, testResult[i].about, testResult[i].comment);
    }
    Serial.println(message);
  }
  Serial.println("");
  char finalMessage[MAX_BUFF_SIZE];
  for (int i=0; i<MAX_BUFF_SIZE; i++) {
    finalMessage[i]=0;
  }
  sprintf(finalMessage, "Test result : all(%d) , success(%d) , fail(%d)", MAX_TEST, MAX_TEST-count, count);
  Serial.println(finalMessage);
  Serial.println("");
}

enum functionList {
  FUNCTION_CLEAR = 0,
  FUNCTION_HOME,
  FUNCTION_SETMODE,
  FUNCTION_CREATE_CHAR,
  FUNCTION_CREATE_CHAR_FROM_PROGMEM,
  FUNCTION_SET_CURSOR,
  FUNCTION_COMMAND,
  FUNCTION_SET_BACKLIGHT_RGB,
};

String functionName[8] = {
  "clear()",
  "home()",
  "setMode()",
  "createChar()",
  "createCharFromProgmem()",
  "setCursor()",
  "command()",
  "setBacklightRGB()"
};

void checkReturnValue(lcdFunctionReturnValue val, uint8_t funcType) {
  char buff[MAX_BUFF_SIZE];
  memset(buff,0,MAX_BUFF_SIZE);
  if (val == LCD_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == LCD_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

void clearDisplay(void){
  //lcd.setCursor(0, 0);
  lcd.home();


#ifdef USE_GROVE
  lcd.setBacklightRGB(255, 255, 255);
#endif /* USE_GROVE */


  lcd.clear();


}

void setCursor(uint8_t col /* column */,uint8_t row /* row */) {

  lcd.setCursor(col, row);

}

void test1() {
  String about = "test1";
  printStartMessage(about, 0);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("0");
  Serial.println("1");
  Serial.println("=== 2nd action ===");
  Serial.println("0123456789");
  Serial.println("1");
  Serial.println("=== 3rd action ===");
  Serial.println("0123456789");
  Serial.println("1  3");
  Serial.println("");
  clearDisplay();
  waitForStart();
  Serial.println("start : test1");

  lcdFunctionReturnValue value;

  // 1st action
  value = lcd.setCursor(0,0);
  checkReturnValue(value,FUNCTION_SET_CURSOR);
  lcd.print("0");
  delay(1000);
  value = lcd.setCursor(0,1);
  checkReturnValue(value,FUNCTION_SET_CURSOR);
  lcd.print("1");
  delay(3000);
  // 2nd action
  value = lcd.clear();
  checkReturnValue(value,FUNCTION_CLEAR);
  for (int i=0; i<10;i++) {
    char buff[2];
    buff[0]=0;
    buff[1]=0;
    sprintf(buff,"%d",i);
    value = lcd.setCursor(i,0);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.print(buff);
    delay(500);
  }
  value = lcd.setCursor(0,1);
  checkReturnValue(value,FUNCTION_SET_CURSOR);
  lcd.print("1");
  delay(3000);
  // 3rd action
  value = lcd.clear();
  checkReturnValue(value,FUNCTION_CLEAR);
  for (int i=0; i<10;i++) {
    char buff[2];
    buff[0]=0;
    buff[1]=0;
    sprintf(buff,"%d",i);
    value = lcd.setCursor(i,0);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.print(buff);
    delay(500);
  }
  value = lcd.setCursor(0,1);
  checkReturnValue(value,FUNCTION_SET_CURSOR);
  lcd.print("1");
  value = lcd.setCursor(3,1);
  checkReturnValue(value,FUNCTION_SET_CURSOR);
  lcd.print("3");
  value = lcd.home();
  checkReturnValue(value,FUNCTION_HOME);

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");
}


// make some custom characters:
byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

byte smiley[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b10001,
    0b01110,
    0b00000
};

byte frownie[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b10001
};

byte armsDown[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b01010
};

byte armsUp[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00100,
    0b01010
};

const byte heartp[8] PROGMEM = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

const byte smileyp[8] PROGMEM = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b10001,
    0b01110,
    0b00000
};

const byte frowniep[8] PROGMEM = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b10001
};

const byte armsDownp[8] PROGMEM = {
    0b00100,
    0b01010,
    0b00100,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b01010
};

const byte armsUpp[8] PROGMEM = {
    0b00100,
    0b01010,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00100,
    0b01010
};

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  Serial.println("=== action ===");
#ifdef USE_GROVE
  Serial.println("row 1 : heart, smiley, Bad mood, arm up, arm down ");
  Serial.println("row 2 : heart, smiley, Bad mood, arm up, arm down ");
#else /* USE_GROVE */
  Serial.println("row : heart, smiley, Bad mood, arm up, arm down ");
#endif /* USE_GROVE */
  Serial.println("");
  Serial.println("");
  clearDisplay();
  waitForStart();
  Serial.println("start : test2");

  lcdFunctionReturnValue value;

  // action
    // create a new character, heart, smiley, frownie, armsDown, armsUp
    value = lcd.createChar(0, heart);
    checkReturnValue(value,FUNCTION_CREATE_CHAR);
    value = lcd.createChar(1, smiley);
    checkReturnValue(value,FUNCTION_CREATE_CHAR);
    value = lcd.createChar(2, frownie);
    checkReturnValue(value,FUNCTION_CREATE_CHAR);
    value = lcd.createChar(3, armsDown);
    checkReturnValue(value,FUNCTION_CREATE_CHAR);
    value = lcd.createChar(4, armsUp);
    checkReturnValue(value,FUNCTION_CREATE_CHAR);
    //
    value = lcd.setCursor(0,0);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)0);
    value = lcd.setCursor(1,0);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)1);
    value = lcd.setCursor(2,0);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)2);
    value = lcd.setCursor(3,0);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)3);
    value = lcd.setCursor(4,0);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)4);

#ifdef USE_GROVE
    // create a new character from progmem , heart, smiley, frownie, armsDown, armsUp
    value = lcd.createCharFromProgmem(5, heartp);
    checkReturnValue(value,FUNCTION_CREATE_CHAR_FROM_PROGMEM);
    value = lcd.createCharFromProgmem(6, smileyp);
    checkReturnValue(value,FUNCTION_CREATE_CHAR_FROM_PROGMEM);
    value = lcd.createCharFromProgmem(7, frowniep);
    checkReturnValue(value,FUNCTION_CREATE_CHAR_FROM_PROGMEM);
    value = lcd.createCharFromProgmem(8, armsDownp);
    checkReturnValue(value,FUNCTION_CREATE_CHAR_FROM_PROGMEM);
    value = lcd.createCharFromProgmem(9, armsUpp);
    checkReturnValue(value,FUNCTION_CREATE_CHAR_FROM_PROGMEM);
    value = lcd.setCursor(0,1);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)5);
    value = lcd.setCursor(1,1);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)6);
    value = lcd.setCursor(2,1);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)7);
    value = lcd.setCursor(3,1);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)8);
    value = lcd.setCursor(4,1);
    checkReturnValue(value,FUNCTION_SET_CURSOR);
    lcd.write((unsigned char)9);
#endif /* USE_GROVE */


  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");
}

void test3() {
  String about = "test3";
  printStartMessage(about, 2);
  // テスト内容の説明
  Serial.println("=== 1st action (5sec) ===");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("=== 2nd action (5sec) ===");
  Serial.println("switch off the lcd(NO_DISPLAY).");
  Serial.println("=== 3rd action ===");
  Serial.println("switch on the lcd(ON_DISPLAY).");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test3");

  lcdFunctionReturnValue value;

  // 1st action
  value = lcd.clear();
  checkReturnValue(value,FUNCTION_CLEAR);
  for (int i=0; i<10;i++) {
    char buff[2];
    buff[0]=0;
    buff[1]=0;
    sprintf(buff,"%d",i);
    for (int j=0; j<LCD_MAX_ROW; j++) {
      value = lcd.setCursor(i,j);
      checkReturnValue(value,FUNCTION_SET_CURSOR);
      lcd.print(buff);
    }
  }
  delay(5000);
  // 2nd action
  value = lcd.setMode(NO_DISPLAY);
  checkReturnValue(value,FUNCTION_SETMODE);
  delay(5000);
  // 3rd action
  value = lcd.setMode(ON_DISPLAY);
  checkReturnValue(value,FUNCTION_SETMODE);


  checkTestResult(about, 2);
  Serial.println("");
  Serial.println("");
}

void test4() {
  String about = "test4";
  printStartMessage(about, 3);
  // テスト内容の説明
  Serial.println("=== 1st action defult (5sec) ===");
  Serial.println("default");
  Serial.println("=== 2nd action BLINK (5sec) ===");
  Serial.println("blink");
  Serial.println("=== 3rd action CURSOR (5sec) ===");
  Serial.println("cursur");
  Serial.println("=== 4th action NO_CURSOR (5sec) ===");
  Serial.println("no cursor");
  Serial.println("=== 5th action NO_BLINK (5sec) ===");
  Serial.println("no blink");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test4");

  lcdFunctionReturnValue value;

  // 1st action normal
  clearDisplay();
  lcd.print("default");
  delay(5000);
  // 2nd action
  clearDisplay();
  value = lcd.setMode(BLINK);
  checkReturnValue(value,FUNCTION_SETMODE);
  lcd.print("blink");
  delay(5000);
  clearDisplay();
  value = lcd.setMode(CURSOR);
  checkReturnValue(value,FUNCTION_SETMODE);
  lcd.print("cursor");
  delay(5000);
  clearDisplay();
  value = lcd.setMode(NO_CURSOR);
  checkReturnValue(value,FUNCTION_SETMODE);
  lcd.print("no cursor");
  delay(5000);
  clearDisplay();
  value = lcd.setMode(NO_BLINK);
  checkReturnValue(value,FUNCTION_SETMODE);
  lcd.print("no blink");

  checkTestResult(about, 3);
  Serial.println("");
  Serial.println("");

  // 復旧
  clearDisplay();

}


void test5() {
  String about = "test5";
  printStartMessage(about, 4);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("=== 2nd action ===");
  Serial.println("scroll left (SCROLL_LEFT) 4times.");
  Serial.println("=== 3rd action ===");
  Serial.println("scroll right (SCROLL_RIGHT) 4times.");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test5");

  lcdFunctionReturnValue value;

  // 1st action
  value = lcd.clear();
  checkReturnValue(value,FUNCTION_CLEAR);
  for (int i=0; i<10;i++) {
    char buff[2];
    buff[0]=0;
    buff[1]=0;
    sprintf(buff,"%d",i);
    for (int j=0; j<LCD_MAX_ROW; j++) {
      value = lcd.setCursor(i,j);
      checkReturnValue(value,FUNCTION_SET_CURSOR);
      lcd.print(buff);
    }
  }
  delay(5000);
  // 2nd action
  for (int i=0; i<4; i++) {
    value = lcd.setMode(SCROLL_LEFT);
    checkReturnValue(value,FUNCTION_SETMODE);
    delay(2000);
  }
  delay(5000);
  // 2nd action
  for (int i=0; i<4; i++) {
    value = lcd.setMode(SCROLL_RIGHT);
    checkReturnValue(value,FUNCTION_SETMODE);
    delay(2000);
  }

  checkTestResult(about, 4);
  Serial.println("");
  Serial.println("");

}


void test6() {
  String about = "test6";
  printStartMessage(about, 5);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("      Hello (left to right)");
  Serial.println("      olleH (right to left)");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test6");

  lcdFunctionReturnValue value;

  // 1st action
  value = lcd.setCursor(6,0);
  checkReturnValue(value,FUNCTION_SET_CURSOR);
  value = lcd.setMode(LEFT_TO_RIGHT);
  checkReturnValue(value,FUNCTION_SETMODE);
  lcd.print("Hello");
  delay(5000);
  value = lcd.setCursor(6,1);
  checkReturnValue(value,FUNCTION_SET_CURSOR);
  value = lcd.setMode(RIGHT_TO_LEFT);
  checkReturnValue(value,FUNCTION_SETMODE);
  lcd.print("Hello");

  checkTestResult(about, 5);
  Serial.println("");
  Serial.println("");

  // 復旧
  clearDisplay();
  lcd.setMode(LEFT_TO_RIGHT);

}


void test7() {
  String about = "test7";
  printStartMessage(about, 6);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("No auto scroll");
  Serial.println("012345678901234......");
  Serial.println("=== 2nd action ===");
  Serial.println("auto scroll");
  Serial.println("012345678901234......");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test7");

  lcdFunctionReturnValue value;

  // 1st action
  lcd.print("No auto scroll");
  value = lcd.setMode(NO_AUTO_SCROLL);
  checkReturnValue(value,FUNCTION_SETMODE);
  value = lcd.setCursor(0,1);
  checkReturnValue(value,FUNCTION_SET_CURSOR);
  for (int i=0; i<LCD_MAX_COLS*2; i++) {
    char buff[2]={0,0};
    int val = i%10;
    sprintf(buff,"%d",val);
    lcd.print(buff);
    delay(1000);
  }
  // 2nd action
  clearDisplay();
  lcd.print("Auto scroll");

  value = lcd.setCursor(0,1);
  checkReturnValue(value,FUNCTION_SET_CURSOR);

  int counter = 0;

  for (int i=0; i<LCD_MAX_COLS; i++) {
    counter = i;
    char buff[2]={0,0};
    int val = i%10;
    sprintf(buff,"%d",val);
    lcd.print(buff);
    delay(1000);
  }

  value = lcd.setMode(AUTO_SCROLL);
  checkReturnValue(value,FUNCTION_SETMODE);

  for (int i=counter+1; i<LCD_MAX_COLS*2; i++) {
    char buff[2]={0,0};
    int val = i%10;
    sprintf(buff,"%d",val);
    lcd.print(buff);
    delay(1000);
  }

  checkTestResult(about, 6);
  Serial.println("");
  Serial.println("");

  // 復旧
  clearDisplay();
  value = lcd.setCursor(0,0);
  checkReturnValue(value,FUNCTION_SET_CURSOR);

}

#ifdef USE_GROVE
void test8() {
  String about = "test8";
  printStartMessage(about, 7);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("change backlight color of LED :");
  Serial.println("red, green, blue, yellow, purple, light blue, white (5sec each)");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test8");

  lcdFunctionReturnValue value;

  // 1st action
  value = lcd.setBacklightRGB(255,0,0);
  checkReturnValue(value,FUNCTION_SET_BACKLIGHT_RGB);
  delay(5000);
  value = lcd.setBacklightRGB(0,255,0);
  checkReturnValue(value,FUNCTION_SET_BACKLIGHT_RGB);
  delay(5000);
  value = lcd.setBacklightRGB(0,0,255);
  checkReturnValue(value,FUNCTION_SET_BACKLIGHT_RGB);
  delay(5000);
  value = lcd.setBacklightRGB(255,255,0);
  checkReturnValue(value,FUNCTION_SET_BACKLIGHT_RGB);
  delay(5000);
  value = lcd.setBacklightRGB(255,0,255);
  checkReturnValue(value,FUNCTION_SET_BACKLIGHT_RGB);
  delay(5000);
  value = lcd.setBacklightRGB(0,255,255);
  checkReturnValue(value,FUNCTION_SET_BACKLIGHT_RGB);
  delay(5000);
  value = lcd.setBacklightRGB(255,255,255);
  checkReturnValue(value,FUNCTION_SET_BACKLIGHT_RGB);

  checkTestResult(about, 7);
  Serial.println("");
  Serial.println("");

  // 復旧
  value = lcd.setBacklightRGB(0,0,0);

}
#endif /* USE_GROVE */

void setup() {
  Serial.begin(9600);

  if (SERIAL_RESET) {
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
    }
  } else {
    delay(3000);
  }


  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of character LCD.");
  // set up the LCD's number of columns and rows:

  lcd.begin(LCD_MAX_COLS, LCD_MAX_ROW);

  clearDisplay();
  test1();
  clearDisplay();
  test2();
  clearDisplay();
  test3();
  clearDisplay();
  test4();
  clearDisplay();
  test5();
  clearDisplay();
  test6();
  clearDisplay();
  test7();
  clearDisplay();
#ifdef USE_GROVE
  test8();
#endif /* USE_GROVE */
  sumTestResult();
}

void loop() {

  delay(100);

}


# API


## API関数の返り値

```
typedef enum {
  GROVE_LCD_RGB_BACKLIGHT =1, // https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/
  LIQUID_CRYSTAL,             // LiquidCrystal Library for Arduino https://github.com/arduino-libraries/LiquidCrystal
  ACM1602NI_TYPE              // https://github.com/furushei/ACM1602NI-Arduino
} UnifiedLcdType;

typedef enum {
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
  NO_AUTO_SCROLL,
  BLINK_BACKLIGHT,
  NO_BLINK_BACKLIGHT
} UnifiedLcdMode;

typedef enum {
  LCD_FUNCTION_UNSUPPORTED = 1,
  LCD_FUNCTION_SUCCESS,
  LCD_FUNCTION_FAIL,
} lcdFunctionReturnValue;
```


## クラスオブジェクトの作成と初期化

### [Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]の場合(``LCD_HAL_USE_GROVE``)

```
UnifiedLCD(rgb_lcd* lcd, UnifiedLcdType type, TwoWire  wire);
lcdFunctionReturnValue begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
```


### [I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]の場合(``LCD_HAL_USE_ACM1602NI``)
```
UnifiedLCD(ACM1602NI * lcd, UnifiedLcdType type);
lcdFunctionReturnValue begin(uint8_t cols, uint8_t rows, uint8_t charsize = 0);
```

### [I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]の場合(``LCD_HAL_USE_LIQUID_CRYSTAL``)

```
UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type);
lcdFunctionReturnValue begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
```


## 画面クリア
```
lcdFunctionReturnValue clear(void);
```


## カーソル位置のホームポジションへの移動
```
lcdFunctionReturnValue home(void);
```

## 動作モード設定
```
lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
```
引数で指定できるモードは以下のように定義されている．
```
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
  NO_AUTO_SCROLL,
  BLINK_BACKLIGHT,
  NO_BLINK_BACKLIGHT
};
```

### ``NO_DISPLAY``と``ON_DISPLAY``
LCDの表示をON/OFFする機能．

[使い方参考URL](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/blob/master/examples/Display/Display.ino "Grove_LCD_RGB_Backlight用ドライバのexampleプログラム")

### ``NO_BLINK``と``BLINK``

カーソルを点滅させるか点灯したままにするかの設定．

### ``NO_CURSOR``と``CURSOR``
カーソルを消すか，点灯させるかの設定


### ``SCROLL_LEFT``と``SCROLL_RIGHT``
右もしくは左に1文字分スクロールさせる．

[使い方参考URL](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/blob/master/examples/Scroll/Scroll.ino "Grove_LCD_RGB_Backlight用ドライバのexampleプログラム")


### ``LEFT_TO_RIGHT``と``RIGHT_TO_LEFT``
印字方向の設定．


[使い方参考URL](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/blob/master/examples/TextDirection/TextDirection.ino "Grove_LCD_RGB_Backlight用ドライバのexampleプログラム")

### ``NO_AUTO_SCROLL``と``AUTO_SCROLL``
印字の際にスクロールさせるか否かの設定．

### ``NO_BLINK_BACKLIGHT``と``BLINK_BACKLIGHT``([Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]のみ対応)
バックライトをつけるか否かの設定．

## カーソル位置設定
カーソル位置を``col``列目，``row``行目に設定．

```
lcdFunctionReturnValue setCursor(uuint8_t col, uint8_t row);
```


## カスタム文字の作成とその印字

### ``createChar()``
2進数の配列で文字イメージ(ビットマップ)を定義したものを第2引数に与え，第一引数はその文字に番号をつける．
```
lcdFunctionReturnValue createChar(uint8_t, uint8_t[]);
```

上の手順で定義した文字を印字する場合は，``write()``の第一引数に定義した文字の番号を与えることで，
カーソル位置にその文字が印字される．
```
size_t write(uint8_t);
```

[使い方参考URL](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/blob/master/examples/CustomCharacter/CustomCharacter.ino "Grove_LCD_RGB_Backlight用ドライバのexampleプログラム")

### ``createCharFromProgmem()`` [Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]の場合のみ(``LCD_HAL_USE_GROVE``)
プログラムの動作としては，``createChar()``と同じであるが，作成した文字を「メモリ」上に配置されるか，「Flashメモリ」に配置されるかの違い．
```
lcdFunctionReturnValue createCharFromProgmem(uint8_t, uint8_t *);
```
[使い方参考URL](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/blob/master/examples/CustomCharacterProgmem/CustomCharacterProgmem.ino "Grove_LCD_RGB_Backlight用ドライバのexampleプログラム")

## バックライトの色設定 ([Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]の場合のみ)
``r``,``g``,``b``の値は0から255の値．
```
lcdFunctionReturnValue setBacklightRGB(unsigned char r, unsigned char g, unsigned char b);
```



## 引数で与えられた値(コマンドやデータ)をLCDに送る
引き起こす結果は，ハードウェア(LCDのコントローラーチップ等)によって異なるため，データシート等を参照のこと．
```
lcdFunctionReturnValue command(uint8_t);
```


<!-- キャラクタディスプレイ -->

|名称|動作電圧(V)|
|---|---|
|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|5|
|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|5|
|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|3.3|

<!-- Grove - LCD RGB Backlight -->
[Grove_LCD_RGB_Backlight]:https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
<!-- LCDキャラクターディスプレイモジュール(16×2行バックライト付) -->
[SC1602BSLB]:https://akizukidenshi.com/catalog/g/g100038/
<!-- I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付 -->
[ACM1602NI]:https://akizukidenshi.com/catalog/g/g105693/




<!-- Arduino 本体 -->

|機種名|コア|MCU|動作電圧|
|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|Xtensa LX6|ESP32-S3|3.3V|
|[Arduino Mega 2560][Mega2560]|AVR|ATmega2560|5V|
|[Arduino M0 pro][M0Pro]|ARM Cortex-M0+|ATSAMD21G18|3.3V|
|[Arduino UNO R4 WiFi][UnoR4WiFi]|ARM Cortex-M4|RA4M1|5V|
|[Arduino UNO R4 Minima][UnoR4Minima]|ARM Cortex-M4|RA4M1|5V|
|[Arduino Nano 33 IoT][Nano33IoT]|ARM Cortex-M0+|SAMD21|3.3V|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|ARM Cortex-M7|STM32H747XI|3.3V|
|[Arduino MKR WiFi 1010][MKRWiFi1010]|ARM Cortex-M0+|SAMD21|3.3V|
|[Ardino MKR Zero][MKRZero]|ARM Cortex-M0+|SAMD21|3.3V|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|ARM Cortex-M0+|Raspberry Pi RP2040|3.3V|

<!-- Arduino Nano ESP32 -->
[NanoESP32]:https://docs.arduino.cc/hardware/nano-esp32/
<!--Arduino Mega 2560-->
[Mega2560]:https://docs.arduino.cc/hardware/mega-2560/
<!--Arduino M0 pro-->
[M0Pro]:https://docs.arduino.cc/retired/boards/arduino-m0-pro/
<!--Arduino UNO R4 WiFi-->
[UnoR4WiFi]:https://docs.arduino.cc/hardware/uno-r4-wifi/
<!--Arduino UNO R4 Minima-->
[UnoR4Minima]:https://docs.arduino.cc/hardware/uno-r4-minima/
<!--Arduino Nano 33 IoT-->
[Nano33IoT]:https://docs.arduino.cc/hardware/nano-33-iot/
<!--Arduino Giga R1 Wifi-->
[GigaR1WiFi]:https://docs.arduino.cc/hardware/giga-r1-wifi/
<!--Arduino MKR WiFi 1010-->
[MKRWiFi1010]:https://docs.arduino.cc/hardware/mkr-wifi-1010/
<!--Ardino MKR Zero-->
[MKRZero]:https://docs.arduino.cc/hardware/mkr-zero/
<!--Arduino Nano RP2040 Connect-->
[NanoRP2040Connect]:https://docs.arduino.cc/hardware/nano-rp2040-connect/




<!--- コメント
[Adafruit Unified Sensor Driver][AdafruitUSD]
[Groveシールド][shield]
[Arduino M0 Pro][M0Pro]
[Arduino Due][Due]
[Arduino Uno R3][Uno]
[Arduino Mega2560 R3][Mega]
[Arduino Leonardo Ethernet][LeonardoEth]
[Arduino Pro mini 328 - 3.3V/8MHz][ProMini]
[ESpr one][ESPrOne]
[ESPr one 32][ESPrOne32]
[Grove][Grove]
[Seed Studio][SeedStudio]
[Arduino][Arduino]
[Sparkfun][Sparkfun]
[スイッチサイエンス][SwitchScience]
--->

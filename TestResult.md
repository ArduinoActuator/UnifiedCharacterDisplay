# 動作確認(簡易版)


## 動作確認結果のまとめ

<!--


|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|▲1|◯|－|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|✕|✕|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|✕|✕|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|◯|✕|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||

- 1 : ``createChar()``で一部文字化けする．コンパイル時のメッセージ(以下の通り)を見ると，メモリ不足が疑われる．

```
最大253952バイトのフラッシュメモリのうち、スケッチが17856バイト（7%）を使っています。
最大8192バイトのRAMのうち、グローバル変数が6115バイト（74%）を使っていて、ローカル変数で2077バイト使うことができます。
```

-->


|名称|動作電圧(V)|
|---|---|
|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|5|
|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|5|
|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|3.3|
|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|5|



|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|－|－|◯|－|
|[Arduino Mega 2560][Mega2560]|▲1|◯|－|◯|
|[Arduino M0 pro][M0Pro]|－|－|✕|－|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|✕|－|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|－|－|✕|－|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|－|－|✕|－|
|[Ardino MKR Zero][MKRZero]|－|－|✕|－|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||

- 1 : ``createChar()``で一部文字化けする．コンパイル時のメッセージ(以下の通り)を見ると，メモリ不足が疑われる．

```
最大253952バイトのフラッシュメモリのうち、スケッチが17856バイト（7%）を使っています。
最大8192バイトのRAMのうち、グローバル変数が6115バイト（74%）を使っていて、ローカル変数で2077バイト使うことができます。
```

|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|▲|一部の機能が動作しない|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|



## API一覧

```
lcdFunctionReturnValue clear(void);
lcdFunctionReturnValue home(void);
lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
lcdFunctionReturnValue createChar(uint8_t, uint8_t[]);
lcdFunctionReturnValue createCharFromProgmem(uint8_t, uint8_t *);
lcdFunctionReturnValue setCursor(uint8_t, uint8_t);
size_t write(uint8_t);
lcdFunctionReturnValue command(uint8_t);
lcdFunctionReturnValue setBacklightRGB(unsigned char r, unsigned char g, unsigned char b); // set rgb
```

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


## テストシナリオ1

### テスト対象API
```
lcdFunctionReturnValue clear(void);
lcdFunctionReturnValue home(void);
lcdFunctionReturnValue setCursor(uint8_t, uint8_t);
```

### 動作
- 画面を消し，カーソル位置をホームポジションに設定
- 画面の各行の先頭に行番号を印字
```
0
1
2
3
```
- カーソル位置をホームポジションに設定
- 画面1行目に列番号を印字
```
023456789
1
2
3
```
- ``setCursor()``で2行目，3行目に何箇所かに1文字印字
```
0123456789
1  3
2    5   
3      7
```
- 人に確認させて，応答を待つ．
- 画面を消し，カーソル位置をホームポジションに設定
- 人に確認させて，応答を待つ．

### テスト結果

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|✕|✕|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|✕|✕|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|◯|✕|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## テストシナリオ2

### テスト対象API
```
lcdFunctionReturnValue createChar(uint8_t, uint8_t[]);
lcdFunctionReturnValue createCharFromProgmem(uint8_t, uint8_t *);
size_t write(uint8_t);
```

[使い方参考URL1](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/blob/master/examples/CustomCharacter/CustomCharacter.ino "Grove_LCD_RGB_Backlight用ドライバのexampleプログラム「createChar」用")と
[使い方参考URL2](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/blob/master/examples/CustomCharacter/CustomCharacterProgmem.ino "Grove_LCD_RGB_Backlight用ドライバのexampleプログラム「createCharFromProgmem」用")
を参考に，このプログラム内で定義されている文字と同じものを印字して人の目で確認

### 動作
- 画面を消し，カーソル位置をホームポジションに設定
- 1行目に4文字(ハート，スマイリー，不機嫌な顔文字，腕up，腕ダウン)を``createChar()``で印字
- 2行目に同じ4文字を``createCharFromProgmem()``で印字
- 人に確認してもらう

### テスト結果

#### ``createChar()``
|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|✕1|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|✕|✕|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|✕|✕|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|◯|✕|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||

- 1 : 一部文字化け [Arduino Mega 2560][Mega2560]で動作しないのは，コンパイル時のメッセージ(以下の通り)を見ると，メモリ不足が疑われる．

```
最大253952バイトのフラッシュメモリのうち、スケッチが17856バイト（7%）を使っています。
最大8192バイトのRAMのうち、グローバル変数が6115バイト（74%）を使っていて、ローカル変数で2077バイト使うことができます。
```


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|



#### ``createCharFromProgmem()``
|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|✕|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|
|[Ardino MKR Zero][MKRZero]|✕|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]||

|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## テストシナリオ3

### テスト対象API
```
lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
```

```
NO_DISPLAY
ON_DISPLAY
```

### 動作
- 画面を消し，カーソル位置をホームポジションに設定
- 画面いっぱいに印字
```
0123456789
0123456789
0123456789
0123456789
```
- 人に確認してもらう
- ``NO_DISPLAY``でLCDを消す
- 人に確認してもらう
- ``ON_DISPLAY``でLCDをつける
- 人に確認してもらう

### テスト結果

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|✕|✕|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|✕|✕|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|◯|✕|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## テストシナリオ4

### テスト対象API
```
lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
```

```
NO_BLINK
BLINK
NO_CURSOR
CURSOR
```

### 動作
- 画面を消し，カーソル位置をホームポジションに設定
- 1行目1列目に``normal``を印字
- 5秒待ち
- 1行目1列目に``no blink``を印字
- ``NO_BLINK``を設定し，カーソルを消す?(つけっぱなし?)
- 5秒待ち
- 1行目1列目に``blink``を印字
- ``BLINK``を設定し，カーソルを点滅?
- 5秒待ち
- 1行目1列目に``no cursor``を印字
- ``NO_CURSOR``を設定し，カーソルを消す?
- 5秒待ち
- 1行目1列目に``cursor``を印字
- ``CURSOR``を設定し，カーソルを点灯
- 人に確認してもらう

### テスト結果

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|✕|✕|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|✕|✕|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|◯|✕|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## テストシナリオ5

### テスト対象API
```
lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
```

```
SCROLL_LEFT,
SCROLL_RIGHT,
```

### 動作
- 画面を消し，カーソル位置をホームポジションに設定
- 画面いっぱいに印字
```
0123456789
0123456789
0123456789
0123456789
```
- 人に確認(スタート合図)
- 左スクロール(``SCROLL_LEFT``)4回
- 人に確認してもらう
- 右スクロール(``SCROLL_RIGHT``)4回
- 人に確認してもらう

### テスト結果

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|✕|✕|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|✕|✕|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|◯|✕|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## テストシナリオ6

### テスト対象API
```
lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
```

```
LEFT_TO_RIGHT,
RIGHT_TO_LEFT,
```

### 動作
- 画面を消し，カーソル位置をホームポジションに設定
- 1行目の6列目にカーソルを設定
- ``LEFT_TO_RIGHT``を設定し，''Hello''を印字
- 人に確認してもらう
- カーソルを1行下に設定(2行目10列目)
- ``RIGHT_TO_LEFT``を設定し，''Hello''を印字
- 人に確認してもらう


### テスト結果

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|[Arduino Nano ESP32][NanoESP32]|✕|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|◯|✕|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|✕|✕|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|◯|✕|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## テストシナリオ7

### テスト対象API
```
lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
```

```
AUTO_SCROLL,
NO_AUTO_SCROLL,
```

### 動作
- 画面を消し，カーソル位置をホームポジションに設定
- ``NO_AUTO_SCROLL``を設定
- 1行目に``No auto scroll``と改行を印字(下図)
```
No auto scroll
□ <-カーソル位置
```
- 人に確認(スタート合図)
- 2と改行を印字
- 3と改行を印字
- 4と改行を印字
- 9と改行を印字
- 画面を消し，カーソル位置をホームポジションに設定
- ``AUTO_SCROLL``を設定
- 1行目に``auto scroll``と改行を印字(下図)
```
Auto scroll
□ <-カーソル位置
```
- 人に確認(スタート合図)
- 2と改行を印字
- 3と改行を印字
- 4と改行を印字
- 9と改行を印字
- 人に確認してもらう

### テスト結果

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|✕|✕|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|✕|✕|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|◯|✕|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## テストシナリオ8 ([Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]のみ)

### テスト対象API
```
lcdFunctionReturnValue setBacklightRGB(unsigned char r, unsigned char g, unsigned char b); // set rgb
```

### 動作
- 画面を消し，カーソル位置をホームポジションに設定
- バックライトの色を設定し
- その色になっているかを人に確認してもらう
- 上記2つの手順を色を変更しながら繰り返す(8色程度)


### テスト結果

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|✕|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕|
|[Ardino MKR Zero][MKRZero]|✕|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## テスト環境


|ソフトウェア/Arduinoファミリ|モジュール名|開発元|バージョン|
|---|---|---|---|
|Arduino IDE|－|Arduino|2.3.2|
|AVR|Arduino AVR Boards|Arduino|1.8.6|
|ESP32|Arduino ESP32 Boards|Arduino|2.0.18|
|Giga|Arduino Mbed OS Giga Boards|Arduino|4.3.1|
|Nano|Arduino Mbed OS Nano Boards|Arduino|4.3.1|
|M0|Arduino SAMD Boards (32bits ARM Cortex-M0+)|Arduino|1.8.14|
|UnoR4|Arduino Uno R4 Boards|Arduino|1.4.1|

### コンパイルテスト

|Arduino機種|コンパイル結果|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|△|
|[Arduino UNO R4 WiFi][UnoR4WiFi]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|△|Arduino MbedOS Nano boardsの場合は◯, Arduino SAMD Boardsの時は△
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|
|[Arduino MKR WiFi 1010][MKRWiFi1010]|△|
|[Ardino MKR Zero][MKRZero]|△|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|

- △ : SAMD系MCU搭載のArduinoはGrove LCD RGB Backlightのライブラリがコンパイルに失敗する．

|内容|意味|
|---|---|
|◯|コンパイル成功|
|△|条件付き|
|✕|コンパイルできない|
|-|原理的に互換性がない|
|未|未検証|


## 元々のデバイスドライバの動作

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|
|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]||||
|[Arduino Mega 2560][Mega2560]||||
|[Arduino M0 pro][M0Pro]||||
|[Arduino UNO R4 WiFi][UnoR4WiFi]||||
|[Arduino UNO R4 Minima][UnoR4Minima]||||
|[Arduino Nano 33 IoT][Nano33IoT]||||
|[Arduino Giga R1 Wifi][GigaR1WiFi]||||
|[Arduino MKR WiFi 1010][MKRWiFi1010]||||
|[Ardino MKR Zero][MKRZero]||||
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]||||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

<!-- テスト表

### テスト結果

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|
|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]||||
|[Arduino Mega 2560][Mega2560]||||
|[Arduino M0 pro][M0Pro]||||
|[Arduino UNO R4 WiFi][UnoR4WiFi]||||
|[Arduino UNO R4 Minima][UnoR4Minima]||||
|[Arduino Nano 33 IoT][Nano33IoT]||||
|[Arduino Giga R1 Wifi][GigaR1WiFi]||||
|[Arduino MKR WiFi 1010][MKRWiFi1010]||||
|[Ardino MKR Zero][MKRZero]||||
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]||||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

 -->

<!-- キャラクタディスプレイ -->

|名称|動作電圧(V)|
|---|---|
|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|5|
|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|5|
|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|3.3|
|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|5|

<!-- Grove - LCD RGB Backlight -->
[Grove_LCD_RGB_Backlight]:https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
<!-- LCDキャラクターディスプレイモジュール(16×2行バックライト付) -->
[SC1602BSLB]:https://akizukidenshi.com/catalog/g/g100038/
<!-- I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付 -->
[ACM1602NI]:https://akizukidenshi.com/catalog/g/g105693/

<!-- LCDキャラクターディスプレイモジュール 20×4行 バックライト付 -->
[SC2004CSLB]:https://akizukidenshi.com/catalog/g/g100036/


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

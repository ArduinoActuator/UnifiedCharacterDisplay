# UnifiedCharacterDisplay

このHardware Abstraction Layer(HAL)は，キャラクタディスプレイのデバイスドライバのAPIを
統一するためのラッパである．

## 動作確認済みデバイス

- [Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]
- [LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]
- [I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]


|名称|動作電圧(V)|
|---|---|
|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|5|
|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|5|
|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|3.3|

## 使い方
このライブラリは，外部のデバイスドライバのラッパとして実装されているため，
特にカスタマイズしないと複数のライブラリを取り込まれてプログラムサイズが
大きくなってしまう．

これを防止するためには，```UnifiedCharacterDisplay_config.h```の```#undef```を有効化して，
不要なものを取り込まれないようにする．以下の例では，全ての```#undef```がコメントアウトされているため，
全てのデバイスドライバを取り込む設定になっている．

```C:UnifiedCharacterDisplay_config.h
#ifndef __UNIFIED_CHARACTER_DISPLAY_CONFIG_H__
#define __UNIFIED_CHARACTER_DISPLAY_CONFIG_H__
//#undef LCD_HAL_USE_GROVE
//#undef LCD_HAL_USE_LIQUID_CRYSTAL
//#undef LCD_HAL_USE_ACM1602NI
#endif /* __UNIFIED_CHARACTER_DISPLAY_CONFIG_H__ */
```

なお，取り込まれるライブラリは以下の3種類
- [Grove - LCD RGB Backlight Library][Grove_LCD_RGB_BacklightLibrary] : 上記```LCD_HAL_USE_GROVE```に対応
- [LiquidCrystal Library for Arduino][LiquidCrystal_Library] : 上記```LCD_HAL_USE_LIQUID_CRYSTAL```に対応
- [Arduino ACM1602NI library][ACM1602NI_Library] : 上記```LCD_HAL_USE_ACM1602NI```に対応


<!-- 以下は，外部リンクの定義 
- Adafruit Unified Sensor Driver - [https://github.com/adafruit/Adafruit_Sensor][AdafruitUSD]
-->

<!-- Grove - LCD RGB Backlight Library -->
[Grove_LCD_RGB_BacklightLibrary]:https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight
<!-- Grove - LCD RGB Backlight -->
[Grove_LCD_RGB_Backlight]:https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
<!-- LiquidCrystal Library for Arduino -->
[LiquidCrystal_Library]:https://github.com/arduino-libraries/LiquidCrystal
<!-- LCDキャラクターディスプレイモジュール(16×2行バックライト付) -->
[SC1602BSLB]:https://akizukidenshi.com/catalog/g/g100038/
<!-- Arduino ACM1602NI library -->
[ACM1602NI_Library]:https://github.com/furushei/ACM1602NI-Arduino
<!-- I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付 -->
[ACM1602NI]:https://akizukidenshi.com/catalog/g/g105693/


<!-- 以下は，外部リンクの定義 -->
[GroveBarometerSensorBMP180]:http://wiki.seeedstudio.com/Grove-Barometer_Sensor-BMP180/
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[AdafruitUSD]:https://github.com/adafruit/Adafruit_Sensor
[shield]:https://www.seeedstudio.com/Base-Shield-V2-p-1378.html
[M0Pro]:https://store.arduino.cc/usa/arduino-m0-pro
[Due]:https://store.arduino.cc/usa/arduino-due
[Uno]:https://store.arduino.cc/usa/arduino-uno-rev3
[UnoWiFi]:https://store.arduino.cc/usa/arduino-uno-wifi-rev2
[Mega]:https://store.arduino.cc/usa/arduino-mega-2560-rev3
[LeonardoEth]:https://store.arduino.cc/usa/arduino-leonardo-eth
[ProMini]:https://www.sparkfun.com/products/11114
[ESPrDev]:https://www.switch-science.com/catalog/2652/
[ESPrDevShield]:https://www.switch-science.com/catalog/2811/
[ESPrOne]:https://www.switch-science.com/catalog/2620/
[ESPrOne32]:https://www.switch-science.com/catalog/3555/
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[Arduino]:http://https://www.arduino.cc/
[Sparkfun]:https://www.sparkfun.com/
[SwitchScience]:https://www.switch-science.com/
[AusExGrove3AxisDigitalAccelerometer1_5g]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-1.5g/
[AusExGrove3AxisDigitalAccelerometer16g]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-16g/
[AusExGrove3AxisDigitalGyro]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Gyro/
[AusExGroveI2cTouchSensor]:http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/
[AusExGroveAnalog1AxisGyro]:http://wiki.seeedstudio.com/Grove-Single_Axis_Analog_Gyro/
[AusExGroveAnalogCurrentSensor]:http://wiki.seeedstudio.com/Grove-Electricity_Sensor/
[AusExGroveAnalogTemperatureSensor]:http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
[AusExGroveGsr]:http://wiki.seeedstudio.com/Grove-GSR_Sensor/
[AusExGroveRotaryAngleSensor]:http://wiki.seeedstudio.com/Grove-Rotary_Angle_Sensor/
[AusExGroveSimpleLight]:http://wiki.seeedstudio.com/Grove-Light_Sensor/
[AusExGroveSimpleMoisture]:http://wiki.seeedstudio.com/Grove-Moisture_Sensor/
[AusExGroveSimpleSound]:http://wiki.seeedstudio.com/Grove-Loudness_Sensor/
[AusExDigitalSwitch]:http://wiki.seeedstudio.com/Grove-Switch-P/
[AusExGroveDustSensor]:http://wiki.seeedstudio.com/Grove-Dust_Sensor/
[AusExGroveInfraredDistanceSensor]:http://wiki.seeedstudio.com/Grove-IR_Distance_Interrupter_v1.2/
[AusExGroveInfraredReflectiveSensor]:http://wiki.seeedstudio.com/Grove-Infrared_Reflective_Sensor/
[AusExGroveTouchSensor]:http://wiki.seeedstudio.com/Grove-Touch_Sensor/
[AusExGroveUltrasonicRanger]:http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
[AusExGroveWaterSensor]:http://wiki.seeedstudio.com/Grove-Water_Sensor/
[AusExGrovePirSensor]:http://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor/


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

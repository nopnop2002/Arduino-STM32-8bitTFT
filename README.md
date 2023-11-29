# Arduino-STM32-8bitTFT
8bit TFT Library for Arduino_Core_STM32(ST Core)

I ported from here.   
https://github.com/prenticedavid/MCUFRIEND_kbv   

----

# Software requirement    

- Core library    
https://github.com/stm32duino/Arduino_Core_STM32

- Adafruit GFX Library   
https://github.com/adafruit/Adafruit-GFX-Library   

----

# Wirering for 8bit Parallel TFT   

|TFT||STM32|
|:-:|:-:|:-:|
|LCD_RD|--|PB0(*1)|
|LCD_WR|--|PB1(*1)|
|LCD_RS|--|PB5(*1)|
|LCD_CS|--|PB6(*1)|
|LCD_RST|--|PB7(*1)|
|LCD_D0|--|PA0(*2)|
|LCD_D1|--|PA1(*2)|
|LCD_D2|--|PA2(*2)|
|LCD_D3|--|PA3(*2)|
|LCD_D4|--|PA4(*2)|
|LCD_D5|--|PA5(*2)|
|LCD_D6|--|PA6(*2)|
|LCD_D7|--|PA7(*2)|
|5V|--|5V(*3)|
|3.3V|--|3.3V(*3)|
|GND|--|GND|

(\*1)   
You can change to other PB pin. To change the pin, change Arduino-STM32-8bitTFT.h.   
Some boards assign PB3 and PB4 to the JTAG debug port by default.   
Therefore, depending on the board, PB3 and PB4 may not be available as GPIO.   
These GPIO are controlled using LL_GPIO_WriteOutputPort().   

```
#define TFT_RD         LL_GPIO_PIN_0 // PB0
#define TFT_WR         LL_GPIO_PIN_1 // PB1
#define TFT_RS         LL_GPIO_PIN_5 // PB5
#define TFT_CS         LL_GPIO_PIN_6 // PB6
#define TFT_RST        LL_GPIO_PIN_7 // PB7
```


(\*2)   
__Serial.print of NUCLEO and DISC1 gose to PA2.__   
__Serial.print of STM32G series gose to PA2.__   
__Serial.print of STM32H series gose to PA0.__   
__If you are using these, you will need to do one of the following:__   

#### Change GPIO from D0 to D7   
To change the port, change Arduino-STM32-8bitTFT.h.   
D0 to D7 are controlled using CMSIS ODR Register.   
This register can change multiple IOs at once, but only IOs on the same port.   
Therefore, D0 to D7 must be the same port.   
If PORT-A is used for D0-D7, __all GPIOs on PORT-A cannot be used for other purposes.__   
Because CMSIS ODR Register manipulates all GPIOs of PORT-A.   

You can use any of the following:   
- PORT-A LOW   
 TFT Pin|D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |   
 STM32 Pin|PA7|PA6|PA5|PA4|PA3|PA2|PA1|PA0|   
- PORT-A HIGH   
 TFT Pin|D7  |D6  |D5  |D4  |D3  |D2  |D1 |D0 |   
 STM32 Pin|PA15|PA14|PA13|PA12|PA11|PA10|PA9|PA8|   
- PORT-C LOW   
 TFT Pin|D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |   
 STM32 Pin|PC7|PC6|PC5|PC4|PC3|PC2|PC1|PC0|   
- PORT-C HIGH   
 TFT Pin|D7  |D6  |D5  |D4  |D3  |D2  |D1 |D0 |   
 STM32 Pin|PC15|PC14|PC13|PC12|PC11|PC10|PC9|PC8|   
- PORT-D LOW   
 TFT Pin|D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |   
 STM32 Pin|PD7|PD6|PD5|PD4|PD3|PD2|PD1|PD0|   
- PORT-D HIGH   
 TFT Pin|D7  |D6  |D5  |D4  |D3  |D2  |D1 |D0 |   
 STM32 Pin|PD15|PD14|PD13|PD12|PD11|PD10|PD9|PD8|   

#### Change default Serial instance pins   
You can use another GPIO as a Serial object.   
GPIO that can be used as a Serial object differs depending on the MCU.   
You can know which GPIOs can be used in PeripheralPins.c of the MCU.   
PeripheralPins.c is [here](https://github.com/stm32duino/Arduino_Core_STM32/tree/main/variants).   
```
  Serial.setTx(PB3);
  Serial.setRx(PB4);
  Serial.begin(115200);
```

(\*3)   
When a regulator(It's often AMS1117) is mounted on the back, it's operated 5V.   
When a regulator is NOT mounted on the back, it's operated 3.3V.   


__Note:Keep the wire length as short as possible.__   

----

# Tested TFT    
- ILI9325 2.4inch 240x320 TFT-Shield  
- ILI9341 2.4inch 240x320 TFT-Shield   
- ILI9342 2.4inch 240x320 TFT-Shield   
- SPFD5408 2.4inch 240x320 TFT-Shield   
- R61505 2.4inch 240x320 TFT-Shield   
- ST7783 2.4inch 240x320 TFT-Shield   
- LGDP4532 2.4inch 240x320 TFT-Shield   
- R61509V 3.6inch 240x400 TFT-Shield   
- ST7793 3.6inch 240x400 TFT-Shield   
- ILI9481 3.5inch 320x480 TFT-Shield   
- ILI9486 3.5inch 320x480 TFT-Shield   
- RM68140 3.95inch 320x480 TFT-Shield   
- ST7796 3.95inch 320x480 TFT-Shield   

I found that these display cannot follow high-speed GPIO-ON and GPIO-OFF.   
- OPEN-SMART ILI9225 TFT-Shield   
- OPEN-SMART ILI9327 TFT-Shield   
- OPEN-SMART ILI9340 TFT-Shield   
- OPEN-SMART S6D1121 16Pin-Parallel   
- OPEN-SMART ST7775 16Pin-Parallel   
- OPEN-SMART ST7783 16Pin-Parallel   
- OPEN-SMART R61509V 16Pin-Parallel   
- OPEN-SMART ILI9488 16Pin-Parallel   

![TFT-SHIELD-2](https://user-images.githubusercontent.com/6020549/77811736-c0082a80-70df-11ea-861e-d2117e2718a0.JPG)


----

# Boards available    
This library uses LL GPIO Generic Driver and CMSIS ODR Register.   
Probably all boards have these available.   
I tested with these.   
- STM32F1/F4 series   
- STM32G4 series   
- STM32H5 series   

----

# Setting your TFT's resolution    

The default resolution of this library is 240x320.   
If your TFT's resolution is 320x480,   
you have to set your TFT's resolution using tft.setResoution.   

```
ID = tft.readID();
tft.setResolution(320, 480); // Set your resolution
Serial.print("Device ID: 0x"); Serial.println(ID, HEX);
tft.begin(ID);
uint32_t width = tft.width();
Serial.print("Width: "); Serial.println(width); // You will see 320
uint32_t height = tft.height();
Serial.print("Height: "); Serial.println(height); // You will see 480
```

If your TFT's resolution is 240x400,   
you have to set your TFT's resolution and TFT's offset.   

```
ID = tft.readID();
tft.setResolution(240, 400); // Set your resolution
tft.setOffset(32); // Set your offset
Serial.print("Device ID: 0x"); Serial.println(ID, HEX);
tft.begin(ID);
uint32_t width = tft.width();
Serial.print("Width: "); Serial.println(width); // You will see 240
uint32_t height = tft.height();
Serial.print("Height: "); Serial.println(height); // You will see 400
```

---

- STM32F103 + R61505 2.4 inch TFT

![r61505](https://user-images.githubusercontent.com/6020549/34552852-70d1e6bc-f167-11e7-8df9-41587ebccc79.JPG)

- STM32F103 + SPFD5408 2.4 inch TFT

![spfd5408](https://user-images.githubusercontent.com/6020549/34552862-7ae8d62e-f167-11e7-84dd-73b07476cd50.JPG)

- STM32F103 + ILI9325 2.4 inch TFT

![ili9325](https://user-images.githubusercontent.com/6020549/34552868-848b0fd0-f167-11e7-92f1-9c07e741a33e.JPG)

- STM32F103 + ILI9341 2.4 inch TFT

![ili9341](https://user-images.githubusercontent.com/6020549/34552875-8eb6c832-f167-11e7-9c8c-7e3e602887d3.JPG)

- STM32F103 + ILI9342 2.4 inch TFT

![ili9342](https://user-images.githubusercontent.com/6020549/34552887-9aa02fb2-f167-11e7-8ca6-6517de127a4a.JPG)

- STM32F401 + ILI9341 2.4 inch TFT

![STM32F401](https://user-images.githubusercontent.com/6020549/77814907-ce167500-70f8-11ea-8952-d6d1c1cc8801.JPG)

- STM32F407  + ILI9341 2.4 inch TFT

![STM32F407](https://user-images.githubusercontent.com/6020549/77814593-a540b080-70f5-11ea-93c2-564f9bb0d817.JPG)

- NUCLEO F446RE + ILI9341 2.4 inch TFT (Use PC0-PC7 for D0-D7)

![8bitTFT](https://user-images.githubusercontent.com/6020549/77814188-2ac26180-70f2-11ea-8080-9e3cac22ce5a.JPG)

- STM32H750  + ILI9341 2.4 inch TFT (Use PC0-PC7 for D0-D7)

![STM32H750](https://github.com/nopnop2002/Arduino-STM32-8bitTFT/assets/6020549/d61c0ed1-f251-464b-a680-735ffa685785)

----

# Benchmark using ILI9341(240x320)   
|Benchmark|STM32F103|STM32F303|STM32F401|STM32F411|STM32F407|STM32F446|STM32G431|STM32H750|ATmega328|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|Screen fill            |737158 |358057 |247223 |216304 |141878 |132427 |140239 |222478 |1379560|
|Text                   |58985  |37647  |25814  |22605  |15097  |14272  |16275  |14691  |344024 |
|Lines                  |556282 |336332 |235522 |206064 |137693 |130958 |134605 |147000 |3390180|
|Horiz/Vert Lines       |61299  |30165  |20825  |18221  |11958  |11173  |11847  |18372  |144664 |
|Rectangles (outline)   |39994  |20040  |13835  |12106  |7953   |7437   |8178   |11863  |104260 |
|Rectangles (filled)    |1530389|743518 |513383 |449170 |294609 |274991 |291313 |461782 |3267476|
|Circles (filled)       |215466 |120380 |83212  |72840  |48080  |45358  |58606  |59632  |1211484|
|Circles (outline)      |245302 |148705 |103680 |90733  |60769  |57622  |59807  |64510  |1475108|
|Triangles (outline)    |123427 |74211  |51938  |45477  |30354  |28766  |29767  |32825  |1075596|
|Triangles (filled)     |528554 |268777 |185711 |162496 |106788 |99944  |112922 |155465 |1721636|
|Rounded rects (outline)|101407 |58746  |40758  |35682  |23791  |22529  |23750  |27519  |506428 |
|Rounded rects (filled) |1534484|750346 |518107 |453320 |297450 |277742 |298242 |132427 |3795228|




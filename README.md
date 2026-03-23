# Arduino-STM32-8bitTFT
8bit TFT Library for Arduino_Core_STM32(ST Core)

I ported from here.   
https://github.com/prenticedavid/MCUFRIEND_kbv   

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
I tested on these.   
- STM32F0/F1/F3/F4 series   
- STM32G4 series   
- STM32H5 series   
- STM32L4 series   

----

# Software requirement    
- Arduino IDE   
	I used V1.8.19   
	![Arduino_V1_8_19](https://github.com/user-attachments/assets/f3179568-cce6-4762-99e3-509852c7fa5d)

- Arduino core support for STM32 based boards   
	https://github.com/stm32duino/Arduino_Core_STM32   
	___Note for Core version___   
	Core version 2.8 or later requires Arduino IDE 2.x.   
	I used version 2.7.1.   
	This is the final version available for Arduino IDE 1.x.   
	![](https://img.shields.io/badge/_IMPORTANT-important)  
	__There is some core library for STM32.__   
	__It doesn't work with [Arduino STM32](https://github.com/rogerclarkmelbourne/Arduino_STM32).__
	![STM32_Core_2 7 1](https://github.com/user-attachments/assets/e135c6b2-61f5-4ac8-a4e5-8878a29a2be4)

- STM32 Cube Programmer   
	The Arduino IDE uses the STM32CubeProgrammer to write firmware to the STM32.   
	Please note that older versions of STM32CubeProgrammer do not support newer models such as STM32G0.   
	I used version 2.20.   
	![Image](https://github.com/user-attachments/assets/d6b365b8-6955-4e2a-9937-7d5607e65da4)

- Adafruit GFX Library   
	https://github.com/adafruit/Adafruit-GFX-Library   
	I used version 1.11.9.   
	![Image](https://github.com/user-attachments/assets/f4a09fdf-7c9f-412a-a9fd-e3704f4dd82b)

----

# Wiring for 8bit Parallel TFT   

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
You can change to other PB pin.   
To change the pin, change Arduino-STM32-8bitTFT.h.   
Some boards assign PB3 and PB4 to the JTAG debug port by default.   
Therefore, depending on the board, PB3 and PB4 may not be available as GPIO.   
These GPIO are controlled using LL_GPIO_WriteOutputPort().   

```
#define TFT_CNTRL      GPIOB

#define TFT_RD         LL_GPIO_PIN_0 // PB0
#define TFT_WR         LL_GPIO_PIN_1 // PB1
#define TFT_RS         LL_GPIO_PIN_5 // PB5
#define TFT_CS         LL_GPIO_PIN_6 // PB6
#define TFT_RST        LL_GPIO_PIN_7 // PB7
```

These GPIOs can be changed to PC ports.   

```
//#define TFT_CNTRL      GPIOB
#define TFT_CNTRL      GPIOC

#define TFT_RD         LL_GPIO_PIN_0 // PC0
#define TFT_WR         LL_GPIO_PIN_1 // PC1
#define TFT_RS         LL_GPIO_PIN_5 // PC5
#define TFT_CS         LL_GPIO_PIN_6 // PC6
#define TFT_RST        LL_GPIO_PIN_7 // PC7
```

These GPIOs can be changed to PD ports.   

```
//#define TFT_CNTRL      GPIOB
#define TFT_CNTRL      GPIOD

#define TFT_RD         LL_GPIO_PIN_0 // PD0
#define TFT_WR         LL_GPIO_PIN_1 // PD1
#define TFT_RS         LL_GPIO_PIN_5 // PD5
#define TFT_CS         LL_GPIO_PIN_6 // PD6
#define TFT_RST        LL_GPIO_PIN_7 // PD7
```

(\*2)   
The output destination of Serial.print conflicts with these GPIOs.   
The output destination of Serial.print differs depending on the Board Part Number.   
- F103 BluePill:PA9   
- F103 BlackPill:PA9   
- Generic F103:PA2   
- NUCLEO and DISC1:PA2   
- Generic STM32G series:PA2   
- Generic STM32H series:PA0   

You will need to do one of the following:   
- Change D0 to D7 to another GPIO   
- Change default Serial instance pins   

### How to change D0 to D7 to another GPIO   
To change the GPIOs for LCD_D0 to D7, modify Arduino-STM32-8bitTFT.h.   
D0 to D7 are controlled using CMSIS ODR Register.   
This register can change multiple IOs at once, but only IOs on the same port.   
Therefore, D0 to D7 must be the same port.   
If PORT-A is used for D0-D7, __all GPIOs on PORT-A cannot be used for other purposes.__   
Because CMSIS ODR Register manipulates all GPIOs of PORT-A.   
```GPIOA->ODR = 0x00FF```   
This code not only sets D0 to D7 of PORT-A to 1, but also sets D8 to D15 of PORT-A to 0.

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

### How to change default Serial instance pins   
The STM32 can use multiple GPIOs as serial ports.    
For example, on BluePill/BlackPill, the following GPIOs can be used as serial ports:   
```
//*** UART ***

WEAK const PinMap PinMap_UART_TX[] = {
  {PA_2,  USART2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, AFIO_USART2_DISABLE)},
  {PA_9,  USART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, AFIO_USART1_DISABLE)},
  {PB_6,  USART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, AFIO_USART1_ENABLE)},
  {PB_10, USART3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, AFIO_NONE)},
  {NC,    NP,     0}
};

WEAK const PinMap PinMap_UART_RX[] = {
  {PA_3,  USART2, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, AFIO_USART2_DISABLE)},
  {PA_10, USART1, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, AFIO_USART1_DISABLE)},
  {PB_7,  USART1, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, AFIO_USART1_ENABLE)},
  {PB_11, USART3, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, AFIO_NONE)},
  {NC,    NP,     0}
};
```
The example below uses PB10/PB11 as a Serial Object.   
```
  Serial.setTx(PB10); // TX
  Serial.setRx(PB11); // RX
  Serial.begin(115200);
```

GPIO that can be used as a Serial object differs depending on the MCU.   
You can know which GPIOs can be used in PeripheralPins.c of the MCU.   
PeripheralPins.c is [here](https://github.com/stm32duino/Arduino_Core_STM32/tree/main/variants).   

(\*3)   
When a regulator(It's often AMS1117) is mounted on the back, it's operated 5V.   
When a regulator is NOT mounted on the back, it's operated 3.3V.   


__Note:Keep the wire length as short as possible.__   


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

- STM32G431 + ILI9341 2.4 inch TFT (Use Serial remapping)

![STM32G431](https://github.com/nopnop2002/Arduino-STM32-8bitTFT/assets/6020549/3ff0df09-08d8-418a-a346-5b17dc0ef67b)

- STM32H750  + ILI9341 2.4 inch TFT (Use PC0-PC7 for D0-D7)

![STM32H750](https://github.com/nopnop2002/Arduino-STM32-8bitTFT/assets/6020549/d61c0ed1-f251-464b-a680-735ffa685785)

----

# Using Port bit set/reset register   
The control ports (RD/WR/RS/CS/RST) are switched on/off using the LL_GPIO_WriteOutputPort function.   
Instead of using the LL_GPIO_WriteOutputPort function, you can use the Port bit set/reset register.   
```
//#define CNTL_INTERFACE 0 // The control port uses the LL_GPIO_WriteOutputPort function
#define CNTL_INTERFACE 1 // The control port uses Port bit set/reset (BSRR) Register
```

This option speeds up the display.   
It may not work on high-speed Valiant boards such as the F407 and F446.   
Furthermore, the wire cables must be as short as possible.   

# Benchmark using ILI9341(240x320)   
The unit is microseconds.   

Valiant is Generic F103. CPU Frequency is 64MHz.   
|Options|CNTL_INTERFACE 0|CNTL_INTERFACE 1|
|:-:|:-:|:-:|
|Screen fill            |793547 |468909 |
|Text                   |65602  |43645  |
|Lines                  |617476 |392079 |
|Horiz/Vert Lines       |66107  |39275  |
|Rectangles (outline)   |43226  |25888  |
|Rectangles (filled)    |1647687|973586 |
|Circles (filled)       |236781 |148907 |
|Circles (outline)      |272475 |173902 |
|Triangles (outline)    |136929 |86731  |
|Triangles (filled)     |572235 |344905 |
|Rounded rects (outline)|111681 |70286  |
|Rounded rects (filled) |1653430|979834 |

Valiant is F103 PillBoard. CPU Frequency is 72MHz.   
|Options|CNTL_INTERFACE 0|CNTL_INTERFACE 1|
|:-:|:-:|:-:|
|Screen fill            |705234 |416759 |
|Text                   |58300  |38791  |
|Lines                  |548765 |348480 |
|Horiz/Vert Lines       |58750  |34907  |
|Rectangles (outline)   |38415  |23009  |
|Rectangles (filled)    |1464352|865322 |
|Circles (filled)       |210432 |132348 |
|Circles (outline)      |242155 |154560 |
|Triangles (outline)    |121691 |77088  |
|Triangles (filled)     |508563 |306550 |
|Rounded rects (outline)|99252  |62469  |
|Rounded rects (filled) |1469446|870876 |


# Benchmark using ILI9341(240x320)   
The unit is microseconds.   
I used the LL_GPIO_WriteOutputPort function to turn the control port on and off.   

|Valiant|F072|F103(Generic)|F103(PillBoard)|F303|F401|F411|F407|F446|G431|H750|L452|ATmega328|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|CPU Freq|48MHz|64MHz|72MHz|72MHz|84MHz|100MHz|168MHz|180MHz|170MHz|480MHz|80MHz|20MHz|
|Core|M0|M3|M3|M4|M4|M4|M4|M4|M4|M7|M4|AVR RISC|
|Screen fill            |713964 |793547 |705234 |358057 |247241 |216304 |141878 |132427 |140239 |222478 |259637 |1379560|
|Text                   |73319  |65602  |58300  |37647  |26177  |22605  |15097  |14272  |16275  |14691  |28825  |344024 |
|Lines                  |675985 |617476 |548765 |336332 |240153 |206064 |137693 |130958 |134605 |147000 |250545 |3390180|
|Horiz/Vert Lines       |60070  |66107  |58750  |30165  |20854  |18221  |11958  |11173  |11847  |18372  |21950  |144664 |
|Rectangles (outline)   |39824  |43226  |38415  |20040  |13871  |12106  |7953   |7437   |8178   |11863  |14875  |104260 |
|Rectangles (filled)    |1482576|1647687|1464352|743518 |513445 |449170 |294609 |274991 |291313 |461782 |539271 |3267476|
|Circles (filled)       |237519 |236781 |210432 |120380 |84325  |72840  |48080  |45358  |58606  |59632  |97797  |1211484|
|Circles (outline)      |297537 |272475 |242155 |148705 |105621 |90733  |60769  |57622  |59807  |64510  |110695 |1475108|
|Triangles (outline)    |149009 |136929 |121691 |74211  |52836  |45477  |30354  |28766  |29767  |32825  |55313  |1075596|
|Triangles (filled)     |542331 |572235 |508563 |268777 |186336 |162496 |106788 |99944  |112922 |155465 |202875 |1721636|
|Rounded rects (outline)|117285 |111681 |99252  |58746  |41465  |35682  |23791  |22529  |23750  |27519  |43702  |506428 |
|Rounded rects (filled) |1495318|1653430|1469446|750346 |518461 |453320 |297450 |277742 |298242 |132427 |548296 |3795228|



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
- STM32G0/G4 series   
- STM32H5/H7 series   
- STM32L4 series   

----

# Software requirement    
- Arduino IDE   
	I used V2.3.11   
	<img width="969" height="649" alt="arduino-ide-2-3-11" src="https://github.com/user-attachments/assets/5e117a8d-38c6-445b-83b1-c43d3806b9a7" />

- Arduino core support for STM32 based boards   
	https://github.com/stm32duino/Arduino_Core_STM32   
	___Note for Core version___   
	Core version 2.8 or later requires Arduino IDE 2.x.   
	I used version 2.12.0.   
	This is the final version of V2.   
	![](https://img.shields.io/badge/_IMPORTANT-important)  
	__There is some core library for STM32.__   
	__It doesn't work with [Arduino STM32](https://github.com/rogerclarkmelbourne/Arduino_STM32).__
	<img width="969" height="649" alt="stm32-mcu-based-board" src="https://github.com/user-attachments/assets/732467c9-7fcd-4113-b076-28b4cdfddc89" />

- STM32 Cube Programmer   
	The Arduino IDE uses the STM32CubeProgrammer to write firmware to the STM32.   
	Please note that older versions of STM32CubeProgrammer do not support newer models such as STM32G0.   
	I used version 2.20.   
	![Image](https://github.com/user-attachments/assets/d6b365b8-6955-4e2a-9937-7d5607e65da4)

- Adafruit GFX Library   
	https://github.com/adafruit/Adafruit-GFX-Library   
	I used version 1.13.0.   
	<img width="971" height="648" alt="adafruit-gfx-library" src="https://github.com/user-attachments/assets/c76c26c6-841d-48ec-80bb-44bd2656b655" />

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
If you are powering the device via the ST-LINK port, you must provide a separate 5V supply.   

----

# Detect TFT driver   
The TFT driver is detected automatically.   
__Note:Keep the wire length as short as possible.__   
If the wires are not connected correctly, device information cannot be obtained properly.   
```
readReg16(0)=0x0
readReg32(A1)=0x0
readReg40(BF)=0x0
readReg32(D4)=0x0
readReg40(EF)=0x0
readReg32(FE)=0x0
readReg32(04)=0x0
readReg32(D3)=0x0
readReg16(0)=0x0
Device ID: 0x0
```

If the wires are connected correctly, the device information can be obtained accurately.
```
readReg16(0)=0x0
readReg32(A1)=0x0
readReg40(BF)=0x0
readReg32(D4)=0x0
readReg40(EF)=0x202
readReg32(FE)=0x0
readReg32(04)=0x0
readReg32(D3)=0x9341
Device ID: 0x9341
```

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

- STM32G030 + ILI9341 2.4 inch TFT
	![Image](https://github.com/user-attachments/assets/dcf391b2-2f39-4663-87d9-908f361f101e)

- STM32G431 + ILI9341 2.4 inch TFT
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

- Valiant is Generic F103. CPU Frequency is 64MHz.   
	|Options|CNTL_INTERFACE 0|CNTL_INTERFACE 1|
	|:-:|:-:|:-:|
	|Screen fill            |745307 |414816 |
	|Text                   |42718  |29976  |
	|Lines                  |614509 |424154 |
	|Horiz/Vert Lines       |62204  |35052  |
	|Rectangles (outline)   |40784  |23376  |
	|Rectangles (filled)    |1547196|861198 |
	|Circles (filled)       |226631 |143438 |
	|Circles (outline)      |271700 |188449 |
	|Triangles (outline)    |136203 |93405  |
	|Triangles (filled)     |540888 |313942 |
	|Rounded rects (outline)|109921 |72912  |
	|Rounded rects (filled) |1553975|870245 |

- Valiant is F103 PillBoard. CPU Frequency is 72MHz.   
	|Options|CNTL_INTERFACE 0|CNTL_INTERFACE 1|
	|:-:|:-:|:-:|
	|Screen fill            |662393 |368670 |
	|Text                   |37970  |26639  |
	|Lines                  |546149 |376973 |
	|Horiz/Vert Lines       |55284  |31152  |
	|Rectangles (outline)   |36248  |20776  |
	|Rectangles (filled)    |1375087|765390 |
	|Circles (filled)       |201420 |127483 |
	|Circles (outline)      |241472 |167486 |
	|Triangles (outline)    |121051 |83015  |
	|Triangles (filled)     |480712 |279025 |
	|Rounded rects (outline)|97694  |62802  |
	|Rounded rects (filled) |1381105|773431 |

- Valiant is BlackPill F401CC. CPU Frequency is 84MHz.   
	|Options|CNTL_INTERFACE 0|CNTL_INTERFACE 1|
	|:-:|:-:|:-:|
	|Screen fill            |247241 |192333 |
	|Text                   |26177  |20430  |
	|Lines                  |240153 |177725 |
	|Horiz/Vert Lines       |20854  |16212  |
	|Rectangles (outline)   |13871  |10792  |
	|Rectangles (filled)    |513445 |399455 |
	|Circles (filled)       |84325  |65780  |
	|Circles (outline)      |105621 |78305  |
	|Triangles (outline)    |52836  |39184  |
	|Triangles (filled)     |186336 |145204 |
	|Rounded rects (outline)|41465  |31279  |
	|Rounded rects (filled) |518461 |403446 |

- Valiant is BlackPill F411CE. CPU Frequency is 100MHz.   
	|Options|CNTL_INTERFACE 0|CNTL_INTERFACE 1|
	|:-:|:-:|:-:|
	|Screen fill            |216318 |168281 |
	|Text                   |22914  |17914  |
	|Lines                  |209843 |155334 |
	|Horiz/Vert Lines       |18245  |14185  |
	|Rectangles (outline)   |12137  |9445   |
	|Rectangles (filled)    |449223 |349489 |
	|Circles (filled)       |73813  |57629  |
	|Circles (outline)      |92305  |68411  |
	|Triangles (outline)    |46180  |34295  |
	|Triangles (filled)     |163041 |127048 |
	|Rounded rects (outline)|36258  |27380  |
	|Rounded rects (filled) |453632 |353008 |

# Benchmark using ILI9341(240x320)   
The unit is microseconds.   
I used the LL_GPIO_WriteOutputPort function to turn the control port on and off.   

<table>
    <tr>
        <td>Valiant</td>
        <td>ATmega328</td>
        <td>F072</td>
        <td>G030</td>
        <td>F103(Generic)</td>
        <td>F103(PillBoard)</td>
        <td>F303</td>
        <td>L452</td>
        <td>F401</td>
        <td>F411</td>
        <td>F407</td>
        <td>G431</td>
        <td>F446</td>
        <td>H562</td>
        <td>H750</td>
    </tr>
    <tr>
        <td>CPU Freq</td>
        <td>20MHz</td>
        <td>48MHz</td>
        <td>64MHz</td>
        <td>64MHz</td>
        <td>72MHz</td>
        <td>72MHz</td>
        <td>80MHz</td>
        <td>84MHz</td>
        <td>100MHz</td>
        <td>168MHz</td>
        <td>170MHz</td>
        <td>180MHz</td>
        <td>250MHz</td>
        <td>480MHz</td>
    </tr>
    <tr>
        <td>Core</td>
        <td>AVR RISC</td>
        <td>M0</td>
        <td>M0+</td>
        <td>M3</td>
        <td>M3</td>
        <td>M4</td>
        <td>M4</td>
        <td>M4</td>
        <td>M4</td>
        <td>M4</td>
        <td>M4</td>
        <td>M4</td>
        <td>M33</td>
        <td>M7</td>
    </tr>
    <tr>
        <td>Screen fill</td>
        <td>1379560</td>
        <td>713964</td>
        <td>421112</td>
        <td>745307</td>
        <td>662393</td>
        <td>358057</td>
        <td>259637</td>
        <td>247241</td>
        <td>216318</td>
        <td>141878</td>
        <td>158932</td>
        <td>132427</td>
        <td>101466</td>
        <td>222468</td>
    </tr>
    <tr>
        <td>Text</td>
        <td>344024</td>
        <td>73319</td>
        <td>48437</td>
        <td>42718</td>
        <td>37970</td>
        <td>37647</td>
        <td>28825</td>
        <td>26177</td>
        <td>22914</td>
        <td>15097</td>
        <td>17240</td>
        <td>14272</td>
        <td>9015</td>
        <td>14673</td>
    </tr>
    <tr>
        <td>Lines</td>
        <td>3390180</td>
        <td>675985</td>
        <td>437615</td>
        <td>614509</td>
        <td>546149</td>
        <td>336332</td>
        <td>250545</td>
        <td>240153</td>
        <td>209843</td>
        <td>137693</td>
        <td>152302</td>
        <td>130958</td>
        <td>87493</td>
        <td>147627</td>
    </tr>
    <tr>
        <td>Horiz/Vert Lines</td>
        <td>144664</td>
        <td>60070</td>
        <td>35648</td>
        <td>62204</td>
        <td>55284</td>
        <td>30165</td>
        <td>21950</td>
        <td>20854</td>
        <td>18245</td>
        <td>11958</td>
        <td>13410</td>
        <td>11173</td>
        <td>8502</td>
        <td>18371</td>
    </tr>
    <tr>
        <td>Rectangles (outline)</td>
        <td>104260</td>
        <td>39824</td>
        <td>23838</td>
        <td>40784</td>
        <td>36246</td>
        <td>20040</td>
        <td>14875</td>
        <td>13871</td>
        <td>12137</td>
        <td>7953</td>
        <td>9041</td>
        <td>7437</td>
        <td>5598</td>
        <td>11867</td>
    </tr>
    <tr>
        <td>Rectangles (filled)</td>
        <td>3267476</td>
        <td>1482576</td>
        <td>874695</td>
        <td>1547196</td>
        <td>1375087</td>
        <td>743518</td>
        <td>539271</td>
        <td>513445</td>
        <td>449223</td>
        <td>294609</td>
        <td>330060</td>
        <td>274991</td>
        <td>210665</td>
        <td>461764</td>
    </tr>
    <tr>
        <td>Circles (filled)</td>
        <td>1211484</td>
        <td>237519</td>
        <td>149117</td>
        <td>226631</td>
        <td>201420</td>
        <td>120380</td>
        <td>97797</td>
        <td>84325</td>
        <td>73813</td>
        <td>48080</td>
        <td>58613</td>
        <td>45358</td>
        <td>31899</td>
        <td>59721</td>
    </tr>
    <tr>
        <td>Circles (outline)</td>
        <td>1475108</td>
        <td>297537</td>
        <td>193435</td>
        <td>271700</td>
        <td>241472</td>
        <td>148705</td>
        <td>110695</td>
        <td>105621</td>
        <td>92305</td>
        <td>60769</td>
        <td>67262</td>
        <td>57622</td>
        <td>38709</td>
        <td>64918</td>
    </tr>
    <tr>
        <td>Triangles (outline)</td>
        <td>1075596</td>
        <td>149009</td>
        <td>96140</td>
        <td>136203</td>
        <td>121051</td>
        <td>74211</td>
        <td>55313</td>
        <td>52836</td>
        <td>46180</td>
        <td>30354</td>
        <td>33566</td>
        <td>28766</td>
        <td>19352</td>
        <td>32905</td>
    </tr>
    <tr>
        <td>Triangles (filled)</td>
        <td>1721636</td>
        <td>542331</td>
        <td>328165</td>
        <td>540888</td>
        <td>480712</td>
        <td>268777</td>
        <td>202875</td>
        <td>186336</td>
        <td>163041</td>
        <td>106788</td>
        <td>122744</td>
        <td>99944</td>
        <td>74429</td>
        <td>155460</td>
    </tr>
    <tr>
        <td>Rounded rects (outline)</td>
        <td>506428</td>
        <td>117285</td>
        <td>74930</td>
        <td>109921</td>
        <td>97694</td>
        <td>58746</td>
        <td>43702</td>
        <td>41465</td>
        <td>36258</td>
        <td>23791</td>
        <td>26548</td>
        <td>22529</td>
        <td>15519</td>
        <td>27647</td>
    </tr>
    <tr>
        <td>Rounded rects (filled)</td>
        <td>3795228</td>
        <td>1495318</td>
        <td>884908</td>
        <td>1553975</td>
        <td>1381105</td>
        <td>750346</td>
        <td>548296</td>
        <td>518461</td>
        <td>453632</td>
        <td>297450</td>
        <td>334986</td>
        <td>277742</td>
        <td>211891</td>
        <td>461366</td>
    </tr>
</table>

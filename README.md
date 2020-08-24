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
|LCD_RD|--|PB0|
|LCD_WR|--|PB1|
|LCD_RS|--|PB5|
|LCD_CS|--|PB6|
|LCD_RST|--|PB7|
|LCD_D0|--|PA0|
|LCD_D1|--|PA1|
|LCD_D2|--|PA2(*1)|
|LCD_D3|--|PA3|
|LCD_D4|--|PA4|
|LCD_D5|--|PA5|
|LCD_D6|--|PA6|
|LCD_D7|--|PA7|
|5V|--|5V(*2)|
|3.3V|--|3.3V(*2)|
|GND|--|GND|

(\*1)
Serial.print of NUCLEO and DISC1 gose to PA2   
If you use NUCLEO or DISC1, you need to change it.   

(\*2)
When a regulator(It's often AMS1117) is mounted on the back, it's operated 5V.   
When a regulator is NOT mounted on the back, it's operated 3.3V.   

__Note__:You can change to any pin. To change the pin, change Arduino-STM32-8bitTFT.h.   

__Note__:Keep the wire length as short as possible.   

----

# Tested TFT    
ILI9325 2.4inch 240x320   
ILI9341 2.4inch 240x320   
ILI9342 2.4inch 240x320   
SPFD5408 2.4inch 240x320   
R61505 2.4inch 240x320   
ST7783 2.4inch 240x320   
LGDP4532 2.4inch 240x320   
ILI9481 3.5inch 320x480   
R61509V 3.6inch 240x400   
RM68140 3.95inch 320x480   

![TFT-SHIELD-2](https://user-images.githubusercontent.com/6020549/77811736-c0082a80-70df-11ea-861e-d2117e2718a0.JPG)

__NOTE__   
If you want to use a TFT that is not on the list, please use issues to let us know where you purchased it.   
However, expensive TFTs will not be supported.   

----

# Boards available    
This library uses LL GPIO Generic Driver.   
Probably all boards that can use the LL GPIO Generic Driver are available.   
Here is support status of low-layer drivers.   
https://www.st.com/content/st_com/en/search.html#q=Descriptions%20hal%20and%20ll-t=resources-page=1

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

- NUCLEO F446RE + ILI9341 2.4 inch TFT

![8bitTFT](https://user-images.githubusercontent.com/6020549/77814188-2ac26180-70f2-11ea-8080-9e3cac22ce5a.JPG)

----

# Benchmark using ILI9341(240x320)   
|Benchmark|STM32F103|STM32F303|STM32F401|STM32F407|STM32F446|ATmega328|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|Screen fill            |2241101|1854703|1208997|647337 |604184 |1379560|
|Text                   |138955 |106085 |69792  |38303  |35748  |344024 |
|Lines                  |1337689|999535 |660532 |361830 |337721 |3390180|
|Horiz/Vert Lines       |185661 |152992 |99924  |53548  |49978  |144664 |
|Rectangles (outline)   |120109 |98346  |64325  |34627  |32311  |104260 |
|Rectangles (filled)    |4756300|3935313|2583183|1386162|1293716|3267476|
|Circles (filled)       |610890 |471781 |310337 |167938 |156716 |1211484|
|Circles (outline)      |588951 |439863 |290416 |159225 |148621 |1475108|
|Triangles (outline)    |302008 |225153 |148665 |81285  |75894  |1075596|
|Triangles (filled)     |1550456|1262459|821918 |440290 |410928 |1721636|
|Rounded rects (outline)|262224 |201583 |132647 |72231  |67431  |506428 |
|Rounded rects (filled) |4711541|3899510|2555561|1372596|1281003|3795228|




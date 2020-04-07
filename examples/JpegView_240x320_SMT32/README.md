# JPEG Viewer    

Viewer of a JPEG file in the SD card.   

# Additional Software requirement    

- Arduino FAT16/FAT32 Library   
https://github.com/greiman/SdFat   

- JPEG decoder library   
https://github.com/Bodmer/JPEGDecoder   

# Wirering for TFT built-in SD-CARD Reader   

|TFT||STM32F103|
|:-:|:-:|:-:|
|SD_SS|--|PB12|
|SD_SCK|--|PB13|
|SD_DO|--|PB14|
|SD_DI|--|PB15|

__NOTE__   
The pins used in the SPI differ from board to board.   
You need to check the following files for the SPI pins on your board.   
```
Default SPI
C:\Users\user\Documents\ArduinoData\packages\STM32\hardware\stm32\{Core_Version}\variants\{Board_Name}\variant.h

Alternative SPI
C:\Users\user\Documents\ArduinoData\packages\STM32\hardware\stm32\{Core_Version}\variants\{Board_Name}\PeripheralPins.c
```

# How to use    

Copy JPEGS file to your SD-CARD.   
__The biggest length of the JPEG file name is 32 character.__   
Wire TFT built-in SD-CARD Reader to STM32.   
Write this sketch.   

STM32F103 + ILI9341 2.4 inch TFT

![JPEG-View-2 4](https://user-images.githubusercontent.com/6020549/77842950-43ef0f00-71d3-11ea-8b09-4ac20095e6b3.JPG)


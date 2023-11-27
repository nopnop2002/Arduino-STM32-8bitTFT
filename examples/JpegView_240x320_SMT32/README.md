# JPEG Viewer    

Viewer of a JPEG file in the SD card.   

# Additional Software requirement    

- Arduino FAT16/FAT32 Library V2.0.0   
https://github.com/greiman/SdFat   

- JPEG decoder library V1.8.1   
https://github.com/Bodmer/JPEGDecoder   

# Wirering for TFT built-in SD-CARD Reader   
STM32 has multiple SPI buses.   
The number of buses depends on the model.   
This project uses SPI_2 as the SPI object.   
The GPIO used for SPI_2 varies by board.   
GPIO using SPI_2 should check the following files:   
```
Default SPI
C:\Users\user\Documents\ArduinoData\packages\STM32\hardware\stm32\{Core_Version}\variants\{Board_Name}\variant.h

Alternative SPI
C:\Users\user\Documents\ArduinoData\packages\STM32\hardware\stm32\{Core_Version}\variants\{Board_Name}\PeripheralPins.c
```

|TFT||STM32F103|
|:-:|:-:|:-:|
|SD_SS|--|PB12|
|SD_SCK|--|PB13|
|SD_DO|--|PB14|
|SD_DI|--|PB15|

__NOTE__   
Looks like ```transfer(txBuf, rxBuf, count)``` has been removed from SPI in Arduino_Core_STM32 Ver 2.7.0.   
For now use the standard Arduino API by editing SdFatConfig.h and change this.   
```#define SPI_DRIVER_SELECT 1```

# How to use    

Copy JPEGS file to your SD-CARD.   
__The biggest length of the JPEG file name is 32 character.__   
Wire TFT built-in SD-CARD Reader to STM32.   
Write this sketch.   

STM32F103 + ILI9341 2.4 inch TFT

![JPEG-View-2 4](https://user-images.githubusercontent.com/6020549/77842950-43ef0f00-71d3-11ea-8b09-4ac20095e6b3.JPG)


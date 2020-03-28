/*
 * 8bit TFT Library for Arduino_Core_STM32
 *
 * based on MCUFRIEND_kbv.cpp by David Prentice
 * https://github.com/prenticedavid/MCUFRIEND_kbv
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _Arduino-STM32-8bitTFTH_
#define _Arduino-STM32-8bitTFTH_

#include "Arduino.h"
#include "Print.h"
#include <Adafruit_GFX.h>


/*
To use a different resolution TFT, change this or use setResolution().
*/
#define TFTWIDTH  240
#define TFTHEIGHT 320

// Color definitions
#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGRAY   0xC618      /* 192, 192, 192 */
#define DARKGRAY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define PINK        0xF81F
#define GRAY        0x5AEB

/*
Define pins and Output Data Registers
*/

#if 1
#define TFT_DATA       GPIOA
#define TFT_D0         LL_GPIO_PIN_0
#define TFT_D1         LL_GPIO_PIN_1
#define TFT_D2         LL_GPIO_PIN_2
#define TFT_D3         LL_GPIO_PIN_3
#define TFT_D4         LL_GPIO_PIN_4
#define TFT_D5         LL_GPIO_PIN_5
#define TFT_D6         LL_GPIO_PIN_6
#define TFT_D7         LL_GPIO_PIN_7
//Port data |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |
//Pin stm32 |PA7|PA6|PA5|PA4|PA3|PA2|PA1|PA0|
#endif

#if 0
#define TFT_DATA       GPIOA
#define TFT_D0         LL_GPIO_PIN_8
#define TFT_D1         LL_GPIO_PIN_9
#define TFT_D2         LL_GPIO_PIN_10
#define TFT_D3         LL_GPIO_PIN_11
#define TFT_D4         LL_GPIO_PIN_12
#define TFT_D5         LL_GPIO_PIN_13
#define TFT_D6         LL_GPIO_PIN_14
#define TFT_D7         LL_GPIO_PIN_15
//Port data |D7  |D6  |D5  |D4  |D3  |D2  |D1 |D0 |
//Pin stm32 |PA15|PA14|PA13|PA12|PA11|PA10|PA9|PA8|
#endif


#if 0
#define TFT_DATA       GPIOB
#define TFT_D0         LL_GPIO_PIN_0
#define TFT_D1         LL_GPIO_PIN_1
#define TFT_D2         LL_GPIO_PIN_2
#define TFT_D3         LL_GPIO_PIN_3
#define TFT_D4         LL_GPIO_PIN_4
#define TFT_D5         LL_GPIO_PIN_5
#define TFT_D6         LL_GPIO_PIN_6
#define TFT_D7         LL_GPIO_PIN_7
//Port data |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |
//Pin stm32 |PB7|PB6|PB5|PB4|PB3|PB2|PB1|PB0|
#endif

#if 0
#define TFT_DATA       GPIOB
#define TFT_D0         LL_GPIO_PIN_8
#define TFT_D1         LL_GPIO_PIN_9
#define TFT_D2         LL_GPIO_PIN_10
#define TFT_D3         LL_GPIO_PIN_11
#define TFT_D4         LL_GPIO_PIN_12
#define TFT_D5         LL_GPIO_PIN_13
#define TFT_D6         LL_GPIO_PIN_14
#define TFT_D7         LL_GPIO_PIN_15
//Port data |D7  |D6  |D5  |D4  |D3  |D2  |D1 |D0 |
//Pin stm32 |PB15|PB14|PB13|PB12|PB11|PB10|PB9|PB8|
#endif

#if 0
#define TFT_DATA       GPIOC
#define TFT_D0         LL_GPIO_PIN_0
#define TFT_D1         LL_GPIO_PIN_1
#define TFT_D2         LL_GPIO_PIN_2
#define TFT_D3         LL_GPIO_PIN_3
#define TFT_D4         LL_GPIO_PIN_4
#define TFT_D5         LL_GPIO_PIN_5
#define TFT_D6         LL_GPIO_PIN_6
#define TFT_D7         LL_GPIO_PIN_7
//Port data |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |
//Pin stm32 |PC7|PC6|PC5|PC4|PC3|PC2|PC1|PC0|
#endif

#if 0
#define TFT_DATA       GPIOC
#define TFT_D0         LL_GPIO_PIN_8
#define TFT_D1         LL_GPIO_PIN_9
#define TFT_D2         LL_GPIO_PIN_10
#define TFT_D3         LL_GPIO_PIN_11
#define TFT_D4         LL_GPIO_PIN_12
#define TFT_D5         LL_GPIO_PIN_13
#define TFT_D6         LL_GPIO_PIN_14
#define TFT_D7         LL_GPIO_PIN_15
//Port data |D7  |D6  |D5  |D4  |D3  |D2  |D1 |D0 |
//Pin stm32 |PC15|PC14|PC13|PC12|PC11|PC10|PC9|PC8|
#endif

#if 0
#define TFT_DATA       GPIOD
#define TFT_D0         LL_GPIO_PIN_0
#define TFT_D1         LL_GPIO_PIN_1
#define TFT_D2         LL_GPIO_PIN_2
#define TFT_D3         LL_GPIO_PIN_3
#define TFT_D4         LL_GPIO_PIN_4
#define TFT_D5         LL_GPIO_PIN_5
#define TFT_D6         LL_GPIO_PIN_6
#define TFT_D7         LL_GPIO_PIN_7
//Port data |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |
//Pin stm32 |PD7|PD6|PD5|PD4|PD3|PD2|PD1|PD0|
#endif

#if 0
#define TFT_DATA       GPIOD
#define TFT_D0         LL_GPIO_PIN_8
#define TFT_D1         LL_GPIO_PIN_9
#define TFT_D2         LL_GPIO_PIN_10
#define TFT_D3         LL_GPIO_PIN_11
#define TFT_D4         LL_GPIO_PIN_12
#define TFT_D5         LL_GPIO_PIN_13
#define TFT_D6         LL_GPIO_PIN_14
#define TFT_D7         LL_GPIO_PIN_15
//Port data |D7  |D6  |D5  |D4  |D3  |D2  |D1 |D0 |
//Pin stm32 |PD15|PD14|PD13|PD12|PD11|PD10|PD9|PD8|
#endif

#if 0
#define TFT_DATA       GPIOE
#define TFT_D0         LL_GPIO_PIN_0
#define TFT_D1         LL_GPIO_PIN_1
#define TFT_D2         LL_GPIO_PIN_2
#define TFT_D3         LL_GPIO_PIN_3
#define TFT_D4         LL_GPIO_PIN_4
#define TFT_D5         LL_GPIO_PIN_5
#define TFT_D6         LL_GPIO_PIN_6
#define TFT_D7         LL_GPIO_PIN_7
//Port data |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 |
//Pin stm32 |PE7|PE6|PE5|PE4|PE3|PE2|PE1|PE0|
#endif

#if 0
#define TFT_DATA       GPIOE
#define TFT_D0         LL_GPIO_PIN_8
#define TFT_D1         LL_GPIO_PIN_9
#define TFT_D2         LL_GPIO_PIN_10
#define TFT_D3         LL_GPIO_PIN_11
#define TFT_D4         LL_GPIO_PIN_12
#define TFT_D5         LL_GPIO_PIN_13
#define TFT_D6         LL_GPIO_PIN_14
#define TFT_D7         LL_GPIO_PIN_15
//Port data |D7  |D6  |D5  |D4  |D3  |D2  |D1 |D0 |
//Pin stm32 |PE15|PE14|PE13|PE12|PE11|PE10|PE9|PE8|
#endif


#define TFT_CNTRL      GPIOB
#define LL_LOW(LL_GPIO_PIN)  LL_GPIO_WriteOutputPort(TFT_CNTRL, (LL_GPIO_ReadOutputPort(TFT_CNTRL) & ~(LL_GPIO_PIN)))
#define LL_HIGH(LL_GPIO_PIN) LL_GPIO_WriteOutputPort(TFT_CNTRL, (LL_GPIO_ReadOutputPort(TFT_CNTRL) | LL_GPIO_PIN))


// Note:
// PA15 PB3 PB4 is assigned to JTAG debug port by default on some boards.
// Therefore, it may not be available by default.
#define TFT_RD         LL_GPIO_PIN_0 // Px0
#define TFT_WR         LL_GPIO_PIN_1 // Px1
#define TFT_RS         LL_GPIO_PIN_5 // Px5
#define TFT_CS         LL_GPIO_PIN_6 // Px6
#define TFT_RST        LL_GPIO_PIN_7 // Px7

//#define DELAY          delayMicroseconds(10);
#define DELAY          (void)0  // NOP

#define RD_ACTIVE      LL_LOW(TFT_RD)
#define RD_IDLE        LL_HIGH(TFT_RD)
#define WR_ACTIVE      LL_LOW(TFT_WR)
#define WR_IDLE        LL_HIGH(TFT_WR)
#define CD_COMMAND     LL_LOW(TFT_RS)
#define CD_DATA        LL_HIGH(TFT_RS)
#define CS_ACTIVE      LL_LOW(TFT_CS)
#define CS_IDLE        LL_HIGH(TFT_CS)
#define RST_ACTIVE     LL_LOW(TFT_RST)
#define RST_IDLE       LL_HIGH(TFT_RST)

#define RD_STROBE      {RD_ACTIVE; RD_IDLE;} // Not use
#define WR_STROBE      {WR_ACTIVE; WR_IDLE;} // Not use



class STM32_TFT_8bit : public Adafruit_GFX {

 public:

  STM32_TFT_8bit(void);
  void     enablePortClock(GPIO_TypeDef *gpio);
  void     setResolution(int16_t width, int16_t height);
  void     setOffset(int16_t offset);
  void     begin(uint16_t ID);
  void     setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
  void     fillScreen(uint16_t color);
  void     drawLine(int16_t x0, int16_t y0,int16_t x1, int16_t y1, uint16_t color);
  void     drawPixel(int16_t x, int16_t y, uint16_t color);
  void     pushColors8(uint8_t * block, int16_t n, bool first);
  void     pushColors(uint16_t * block, int16_t n, bool first);
  void     drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void     drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void     fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
  int16_t  readGRAM(int16_t x, int16_t y, uint16_t * block, int16_t w, int16_t h);
  uint16_t readPixel(int16_t x, int16_t y) { uint16_t color; readGRAM(x, y, &color, 1, 1); return color; }
  void     setRotation(uint8_t r);
  void     vertScroll(int16_t top, int16_t scrollines, int16_t offset);
  void     invertDisplay(boolean i);
  uint16_t readID(void);


 private:
  void     setWriteDataBus(void);
  void     setReadDataBus(void);
  void     write8(uint8_t);
  void     writeCmdByte(uint8_t c);
  void     WriteCmd(uint16_t c);
  void     writeDataByte(uint8_t d);
  void     writeDataWord(uint16_t d);
  void     WriteCmdData(uint16_t cmd, uint16_t dat);
  void     WriteCmdParamN(uint8_t cmd, int8_t N, uint8_t * block);
  void     WriteCmdParam4(uint8_t cmd, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);
  void     init_table(const void *table, int16_t size);
  void     init_table16(const void *table, int16_t size);
  void     writeCmdWord(uint16_t c);
  uint8_t  read8(void);
  uint8_t  read8bits(void);
  uint16_t read16bits(void);
  uint16_t readReg16(uint16_t reg);
  uint16_t readReg16Index(uint16_t reg, int8_t index);
  uint32_t readReg32(uint16_t reg);
  uint32_t readReg40(uint16_t reg);
  uint16_t _lcd_ID, _lcd_capable, _lcd_rev, _lcd_madctl, _lcd_drivOut, _MC, _MP, _MW, _SC, _EC, _SP, _EP;
  int16_t  _lcd_width = 0, _lcd_height = 0, _lcd_offset=0;
  uint32_t _pins[8];
};

#endif //endif of the header file

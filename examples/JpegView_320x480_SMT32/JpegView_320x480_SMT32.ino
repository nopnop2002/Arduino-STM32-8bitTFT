/*
 * 8bit TFT Library for  Arduino_Core_STM32
 *
 * based on MCUFRIEND_kbv.cpp by David Prentice
 * https://github.com/prenticedavid/MCUFRIEND_kbv
 *
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


#include <Adafruit_GFX.h>
#include "Arduino-STM32-8bitTFT.h"
#include <SdFat.h> // https://github.com/greiman/SdFat
#include <sdios.h> // https://github.com/greiman/SdFat
#include <JPEGDecoder.h> // https://github.com/Bodmer/JPEGDecoder

STM32_TFT_8bit tft;

// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
// 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 1

// Define SPI_2 object.
// STM32F103's SPI_2 object uses the following GPIO.
#define SD_CS   PB12
#define SD_SCLK PB13
#define SD_MISO PB14
#define SD_MOSI PB15
static SPIClass SPI_2 (SD_MOSI, SD_MISO, SD_SCLK, SD_CS);

// Define SdSpiConfig using SPI_2 object.
#define SetSDSpeed 48
#define SD_CONFIG SdSpiConfig (SD_CS, DEDICATED_SPI, SD_SCK_MHZ (SetSDSpeed), &SPI_2)
//------------------------------------------------------------------------------

#if SD_FAT_TYPE == 0
SdFat sd;
File file;
File root;
#elif SD_FAT_TYPE == 1
SdFat32 sd;
File32 file;
File32 root;
#elif SD_FAT_TYPE == 2
SdExFat sd;
ExFile file;
ExFile root;
#elif SD_FAT_TYPE == 3
SdFs sd;
FsFile file;
FsFile root;
#endif  // SD_FAT_TYPE

//------------------------------------------------------------------------------
// Store error strings in flash to save RAM.
#define error(s) sd.errorHalt(&Serial, F(s))
//------------------------------------------------------------------------------

#define OPT_REDUCTION 1
#define OPT_CENTER 2

#define maxFileCount 100
int jpegFileCount;
uint16_t jpegFileIndex[maxFileCount];

int getFileNameByIndex(int index, char * fname, size_t fnameSize)
{
  if (!file.open(&root, index, O_READ)) {
    error("open file failed");
  }
  //Serial.println("open ok ");
  file.getName(fname, fnameSize);
  //Serial.println("fname=" + String(fname));
  file.close();
  return strlen(fname);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("Arduino-STM32-8bitTFT");

  uint32_t ID = tft.readID();
  tft.setResolution(320, 480); // Set your resolution
  Serial.print("Device ID: 0x"); Serial.println(ID, HEX);
  tft.begin(ID);

  uint32_t width = tft.width();
  Serial.print("Width: "); Serial.println(width);
  uint32_t height = tft.height();
  Serial.print("Height: "); Serial.println(height);
  if (width < height) tft.setRotation(3);

  // Initialize the SD card.
  if (!sd.begin(SD_CONFIG)) {
    sd.initErrorHalt(&Serial);
  }

  jpegFileCount = 0;
  if (!root.open("/")) {
    error("open root");
  }
  while (file.openNext(&root, O_RDONLY)) {
    // Skip directories and hidden files.
    if (!file.isSubDir() && !file.isHidden()) {
      // get file name
      char fname[32];
      file.getName(fname, sizeof(fname));
      Serial.print("fname=");
      Serial.println(fname);
      //jpegFileCount++;

      // Is jpeg file
      if (strstr(fname, ".jpg") != 0) {
        // Save dirIndex of file in directory.
        if (jpegFileCount < maxFileCount) {
          jpegFileIndex[jpegFileCount++] = file.dirIndex();
        }
      }
    }
    file.close();
  }
  Serial.println("jpegFileCount=" + String(jpegFileCount));
  
  for (int ipos=0;ipos<jpegFileCount;ipos++) {
    char fname[32];
    getFileNameByIndex(jpegFileIndex[ipos], fname, sizeof(fname));   
  }
}


void loop(void) {
  static int ipos = 0;

  // Get JPEG file name
  char fname[32];
  int len = getFileNameByIndex(jpegFileIndex[ipos], fname, sizeof(fname));

  // Draw JPEG image with reduction
  tft.fillScreen(random(0x10000));
  drawFSJpeg(fname, 0, 0, OPT_REDUCTION + OPT_CENTER);
 
  ipos++;
  if (ipos == jpegFileCount) ipos = 0;
 
  delay(5000);
}

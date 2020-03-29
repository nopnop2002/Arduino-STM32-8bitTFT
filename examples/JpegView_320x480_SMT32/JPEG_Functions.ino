/*====================================================================================
  This sketch contains support functions to render the Jpeg images.

  Created by Bodmer 5th Feb 2017
  Updated by nopnop2002 19/4/2018
  ==================================================================================*/

// Return the minimum of two values a and b
#define minimum(a,b)     (((a) < (b)) ? (a) : (b))
#define maximum(a,b)     (((a) > (b)) ? (a) : (b))

//====================================================================================
//   This function opens the array and primes the decoder
//====================================================================================
void drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos) {

  boolean decoded = JpegDec.decodeArray(arrayname, array_size);

  if (decoded) {
    // print information about the image to the serial port
    jpegInfo();

    // render the image onto the screen at given coordinates
    jpegRender(xpos, ypos, 0);
  }
  else {
    Serial.println("Jpeg file format not supported!");
  }
}

//====================================================================================
//   This function opens the Filing System Jpeg image file and primes the decoder
//
//   options : OPT_REDUCTION
//             If it's large than screen, it would reduce so that it may fit into a screen.
//             OPT_CENTER
//             If it's smaller than screen, it would show to the center of the screen.
//====================================================================================
void drawFSJpeg(const char *filename, int xpos, int ypos, int options) {

  Serial.println("=====================================");
  Serial.print("Drawing file: "); Serial.println(filename);
  Serial.println("=====================================");

  // Open the file (the Jpeg decoder library will close it)
  File jpgFile = SD.open( filename, FILE_READ);  // file handle reference for SD library
 
  if ( !jpgFile ) {
    Serial.print("ERROR: File \""); Serial.print(filename); Serial.println ("\" not found!");
    return;
  }

  // To initialise the decoder and provide the file, we can use one of the following methods:
  boolean decoded = JpegDec.decodeSdFile(jpgFile);   // we can pass the SD file handle to the decoder,
  //boolean decoded = JpegDec.decodeFsFile(filename);  // or we can pass the filename
                                                       // The filename can be a String or character array
  if (decoded) {
    // print information about the image to the serial port
    jpegInfo();

    // render the image onto the screen at given coordinates
    jpegRender(xpos, ypos, options);
  }
  else {
    Serial.println("Jpeg file format not supported!");
  }
}

//====================================================================================
//   Decode and paint onto the TFT screen
//====================================================================================
void jpegRender(int xpos, int ypos, int options) {

//if (options & OPT_REDUCTION) Serial.println("OPT_REDUCTION"); 
//if (options & OPT_CENTER) Serial.println("OPT_CENTER"); 
  // retrieve infomration about the image
  uint16_t  *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;
//Serial.println("mcu_w=" + String(mcu_w));
//Serial.println("mcu_h=" + String(mcu_h));
//Serial.println("max_x=" + String(max_x));
//Serial.println("max_y=" + String(max_y));

  uint16_t szImg2 = mcu_w * mcu_h;
  uint16_t *pImg2;
  pImg2 = (uint16_t *) malloc(szImg2*2);

  uint32_t tft_width = tft.width();
//Serial.print("tft_width: "); Serial.println(tft_width);
  uint32_t tft_height = tft.height();
//Serial.print("tft_height: "); Serial.println(tft_height);

  int reduction_x = 1;
  int reduction_y = 1;
  if (max_x > tft_width) {
    reduction_x = (max_x / tft_width);
    if (max_x % tft_width) reduction_x++;
  }
  if (max_y > tft_height) {
    reduction_y = (max_y / tft_height);
    if (max_y % tft_height) reduction_y++;
  }
//Serial.println("reduction_x=" + String(reduction_x));
//Serial.println("reduction_y=" + String(reduction_y));
  int reduction = maximum(reduction_x, reduction_y);
//Serial.println("reduction=" + String(reduction));
  
  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
  uint32_t min_h = minimum(mcu_h, max_y % mcu_h);
//Serial.println("min_w=" + String(min_w));
//Serial.println("min_h=" + String(min_h));


  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;

  // record the current time so we can measure how long it takes to draw an image
  uint32_t drawTime = millis();

  uint16_t max_xx = max_x;
  uint16_t max_yy = max_y;
  if (reduction > 1 && (options & OPT_REDUCTION) ) {
    max_xx = max_x / reduction; // new image size of X
    max_yy = max_y / reduction; // new image size of Y
  }
//Serial.println("max_xx=" + String(max_xx));
//Serial.println("max_yy=" + String(max_yy));

  // calculation center position
  int delta_x = 0;
  int delta_y = 0;
  if ( (max_xx < tft_width) && (options & OPT_CENTER) ) {
    delta_x = (tft_width - max_xx) / 2;
  }
  if ( (max_yy < tft_height) && (options & OPT_CENTER) ) {
    delta_y = (tft_height - max_yy) / 2;
  }
//Serial.println("delta_x=" + String(delta_x));
//Serial.println("delta_y=" + String(delta_y));

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

  // read each MCU block until there are no more
  while ( JpegDec.read()) {

    // save a pointer to the image block
    pImg = JpegDec.pImage;

    // calculate where the image block should be drawn on the screen
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right and bottom edges
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    memcpy(pImg2, JpegDec.pImage, szImg2*2);
    int mcu_xx = mcu_x + delta_x;
    int mcu_yy = mcu_y + delta_y;
    uint32_t win_ww = win_w;
    uint32_t win_hh = win_h;
  
    if (reduction > 1 && (options & OPT_REDUCTION) ){
      int pos1 = 0;
      int pos2 = 0;
      for(int x=0; x<win_w; x+=reduction) {
        for(int y=0; y<win_h; y+=reduction) {
          pos2 = (x * win_w) + y;
//Serial.println("pos1=" + String(pos1) + " x =" + String(x) + " y=" + String(y) + " pos2=" + String(pos2));
          pImg2[pos1++] = pImg2[pos2];
        }
      }
      mcu_xx = JpegDec.MCUx * (mcu_w/reduction) + xpos + delta_x;
      mcu_yy = JpegDec.MCUy * (mcu_h/reduction) + ypos + delta_y;
      win_ww = win_w / reduction;
      if (win_w % reduction) win_ww++;
      win_hh = win_h / reduction;
      if (win_h % reduction) win_hh++;
    }

 


#if 0    
    // calculate how many pixels must be drawn
    uint16_t mcu_pixels = win_w * win_h;
Serial.println("win_x=" + String(win_w) + " win_y=" + String(win_h));

    // draw image MCU block only if it will fit on the screen
    if ( ( mcu_x + win_w) <= tft.width() && ( mcu_y + win_h) <= tft.height())
  {
      // Now set a MCU bounding window on the TFT to push pixels into (x, y, x + width - 1, y + height - 1)
      tft.setAddrWindow(mcu_x, mcu_y, mcu_x + win_w - 1, mcu_y + win_h - 1);

      // Write all MCU pixels to the TFT window
      //while (mcu_pixels--) tft.pushColor(*pImg++); // Send MCU buffer to TFT 16 bits at a time
//      tft.pushColors(pImg, mcu_pixels, 1);
      tft.pushColors(pImg2, mcu_pixels, 1);
    }
#endif


    // calculate how many pixels must be drawn
    uint16_t mcu_pixels = win_ww * win_hh;
//Serial.println("win_ww=" + String(win_ww) + " win_hh=" + String(win_hh));

    // draw image MCU block only if it will fit on the screen
    if ( (mcu_xx + win_ww) <= tft_width && ( mcu_yy + win_hh) <= tft_height)
  {
      // Now set a MCU bounding window on the TFT to push pixels into (x, y, x + width - 1, y + height - 1)
      tft.setAddrWindow(mcu_xx, mcu_yy, mcu_xx + win_ww - 1, mcu_yy + win_hh - 1);

      // Write all MCU pixels to the TFT window
      //while (mcu_pixels--) tft.pushColor(*pImg++); // Send MCU buffer to TFT 16 bits at a time
      tft.pushColors(pImg2, mcu_pixels, 1);
    }

    // Stop drawing blocks if the bottom of the screen has been reached,
    // the abort function will close the file
    else if ( ( mcu_y + win_h) >= tft.height()) JpegDec.abort();

  }

  free(pImg2);
  // calculate how long it took to draw the image
  drawTime = millis() - drawTime;

  // print the results to the serial port
  Serial.print  ("Total render time was    : "); Serial.print(drawTime); Serial.println(" ms");
  if (reduction > 1 && (options & OPT_REDUCTION) ) {
    int reductionRate = (float)(1.0 / reduction) * 100;
    Serial.print  ("Rate of reduction was    : "); Serial.print(reductionRate); Serial.println(" %");
  }
  Serial.println("=====================================");

}
//====================================================================================
//   Send time taken to Serial port
//====================================================================================
void jpegInfo() {
  Serial.println(F("==============="));
  Serial.println(F("JPEG image info"));
  Serial.println(F("==============="));
  Serial.print(F(  "Width      :")); Serial.println(JpegDec.width);
  Serial.print(F(  "Height     :")); Serial.println(JpegDec.height);
  Serial.print(F(  "Components :")); Serial.println(JpegDec.comps);
  Serial.print(F(  "MCU / row  :")); Serial.println(JpegDec.MCUSPerRow);
  Serial.print(F(  "MCU / col  :")); Serial.println(JpegDec.MCUSPerCol);
  Serial.print(F(  "Scan type  :")); Serial.println(JpegDec.scanType);
  Serial.print(F(  "MCU width  :")); Serial.println(JpegDec.MCUWidth);
  Serial.print(F(  "MCU height :")); Serial.println(JpegDec.MCUHeight);
  Serial.println(F("==============="));
}

//====================================================================================
//   Open a Jpeg file on an SD card and dump it to the Serial port as a C array
//====================================================================================
void createArray(const char *filename) {

  File jpgFile;  // File handle reference For SD library
  
  if ( !( jpgFile = SD.open( filename, FILE_READ))) {
    Serial.println(F("JPEG file not found"));
    return;
  }

  uint8_t data;
  byte line_len = 0;
  Serial.println("// Generated by a JPEGDecoder library example sketch:");
  Serial.println("// https://github.com/Bodmer/JPEGDecoder");
  Serial.println("");
  Serial.println("#if defined(__AVR__)");
  Serial.println("  #include <avr/pgmspace.h>");
  Serial.println("#endif");
  Serial.println("");
  Serial.print("const uint8_t ");
  while (*filename != '.') Serial.print(*filename++);
  Serial.println("[] PROGMEM = {"); // PROGMEM added for AVR processors

  while ( jpgFile.available()) {

    data = jpgFile.read();
    Serial.print("0x"); if (abs(data) < 16) Serial.print("0");
    Serial.print(data, HEX); Serial.print(",");// Add value and comma
    line_len++;
    if ( line_len >= 32) {
      line_len = 0;
      Serial.println();
    }

  }

  Serial.println("};\r\n");
  jpgFile.close();
}

// Function to print all timestamps.
void printTimestamps(SdFile& f) {
  dir_t d;
  if (!f.dirEntry(&d)) {
    return;
  }

  //Serial.print("Creation: ");
  //f.printFatDate(d.creationDate);
  //Serial.print(" ");
  //f.printFatTime(d.creationTime);

  //Serial.print("Modify: ");
  f.printFatDate(d.lastWriteDate);
  Serial.print(" ");
  f.printFatTime(d.lastWriteTime);

  //Serial.print("Access: ");
  //f.printFatDate(d.lastAccessDate);
  Serial.print(" ");
}

// Show JPEG file list on console
int showJpegFileList (uint16_t * fileIndexs, int MaxIndex) {
  SdFile file;
  SdFile dirFile;
  SdFile file2;

  // open root directory.
  if (!dirFile.open("/", O_READ)) {
    SD.errorHalt("open root failed");
  }

  Serial.println("--------------------------------------------");
  uint16_t n = 0;
  while (n < MaxIndex && file.openNext(&dirFile, O_READ)) {

    // Skip directories and hidden files.
    if (!file.isSubDir() && !file.isHidden()) {

      // open file.
      if (!file2.open(&dirFile, file.dirIndex(), O_READ)) {
        SD.errorHalt(F("open"));
      }

      // get file size  
      char buf[60];
      uint32_t fsz = file2.fileSize();

      // get file name
      char fname[20];
      file2.getName(fname,20);
      //Serial.print("fname=");
      //Serial.println(fname);

      // Is JPEG file
      if (strstr(fname, ".jpg") != 0) {
        printTimestamps(file2);
        sprintf(buf,"%10d %s",fsz,fname);
        Serial.println(buf);
        // Save dirIndex of file in directory.
        fileIndexs[n++] = file.dirIndex();
      }
      file2.close();
    }
    file.close();
  }
  Serial.println("--------------------------------------------");
  return n;
}


int getFileName(int index, char * fname, size_t fnameSize)
{
  // Get JPEG file name
  //Serial.println("index=" + String(index));
  SdFile file;
  SdFile dirFile;
  if (!dirFile.open("/", O_READ)) {
    SD.errorHalt("open root failed");
  }
  if (!file.open(&dirFile, index, O_READ)) {
    SD.errorHalt(F("open file failed"));
  }
  //Serial.print("open ok ");
  file.getName(fname, fnameSize);
  //Serial.println("fname=" + String(fname));
  file.close();
  dirFile.close();
  return strlen(fname);
}

//====================================================================================


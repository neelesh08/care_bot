
//----------------------------------------------- max_heart rate --------------------------------------

void max_setup()
{
 
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
 
}



//------------------------------------------------rtc setup-------------------------------------

void rtc_setup(){



#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
   
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }
}


//----------------------------------------adlx345------------------

void adlx_setup(){



    adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);

}



// ------------------------------------------ sd card setup ---------------------------------------

void sd_setup() {
  Serial.begin(115200);
 
  
  digitalWrite(21, HIGH); // Touch controller chip select (if used)
  digitalWrite(15, HIGH); // TFT screen chip select
  digitalWrite( 5, HIGH); // SD card chips select, must use GPIO 5 (ESP32 SS)
 
  tft.begin();
 
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
 
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
 
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
 
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
 
  Serial.println("initialisation done.");
  // all files are in landscape, you would need to change the code if you wanted portrait
  tft.setRotation(1);  // landscape

  
}


void drawSdJpeg(const char *filename, int xpos, int ypos) {
 
  
  File jpegFile = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
 
  if ( !jpegFile ) {
    Serial.print("ERROR: File \""); Serial.print(filename); Serial.println ("\" not found!");
    return;
  }
 
  Serial.println("===========================");
  Serial.print("Drawing file: "); Serial.println(filename);
  Serial.println("===========================");
 
  // Use one of the following methods to initialise the decoder:
  boolean decoded = JpegDec.decodeSdFile(jpegFile);  // Pass the SD file handle to the decoder,
  //boolean decoded = JpegDec.decodeSdFile(filename);  // or pass the filename (String or character array)
 
  if (decoded) {
    // print information about the image to the serial port
    jpegInfo();
    // render the image onto the screen at given coordinates
    jpegRender(xpos, ypos);
  }
  else {
    Serial.println("Jpeg file format not supported!");
  }
}
 

void jpegRender(int xpos, int ypos) {
 
  //jpegInfo(); // Print information from the JPEG file (could comment this line out)
 
  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;
 
  bool swapBytes = tft.getSwapBytes();
  tft.setSwapBytes(true);
  
  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
//  uint32_t min_w = min(mcu_w, max_x % mcu_w);
//  uint32_t min_h = min(mcu_h, max_y % mcu_h);
 
  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;
 
  // record the current time so we can measure how long it takes to draw an image
  uint32_t drawTime = millis();
 
  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;
 
  // Fetch data from the file, decode and display
  while (JpegDec.read()) {    // While there is more data in the file
    pImg = JpegDec.pImage ;   // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)
 
    // Calculate coordinates of top left corner of current MCU
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;
 
    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    //else win_w = min_w;
 
    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    //else win_h = min_h;
 
    // copy pixels into a contiguous block
    if (win_w != mcu_w)
    {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++)
      {
        p += mcu_w;
        for (int w = 0; w < win_w; w++)
        {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }
 
    // calculate how many pixels must be drawn
    uint32_t mcu_pixels = win_w * win_h;
 
    // draw image MCU block only if it will fit on the screen
    if (( mcu_x + win_w ) <= tft.width() && ( mcu_y + win_h ) <= tft.height())
      tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
    else if ( (mcu_y + win_h) >= tft.height())
      JpegDec.abort(); // Image has run off bottom of screen so abort decoding
  }
 
  tft.setSwapBytes(swapBytes);
 
  showTime(millis() - drawTime); // These lines are for sketch testing only
}
 

void jpegInfo() {
 
  // Print information extracted from the JPEG file
  Serial.println("JPEG image info");
  Serial.println("===============");
  Serial.print("Width      :");
  Serial.println(JpegDec.width);
  Serial.print("Height     :");
  Serial.println(JpegDec.height);
  Serial.print("Components :");
  Serial.println(JpegDec.comps);
  Serial.print("MCU / row  :");
  Serial.println(JpegDec.MCUSPerRow);
  Serial.print("MCU / col  :");
  Serial.println(JpegDec.MCUSPerCol);
  Serial.print("Scan type  :");
  Serial.println(JpegDec.scanType);
  Serial.print("MCU width  :");
  Serial.println(JpegDec.MCUWidth);
  Serial.print("MCU height :");
  Serial.println(JpegDec.MCUHeight);
  Serial.println("===============");
  Serial.println("");
}
 

 
void showTime(uint32_t msTime) {

  Serial.print(F(" JPEG drawn in "));
  Serial.print(msTime);
  Serial.println(F(" ms "));
}








//
//while(true){
//        GetPoint();
//        checkBack = isBackPressed();
//        if(checkBack == true){
//          CurrentStatus = 1;
//          drawSdJpeg(screen[CurrentStatus] , 0 , 0);
//          return;
//        }
//        
//        
//        if(p.x > 37 && p.x < 283 && p.y > 193 && p.y< 225){  // on press on calculate 
//              int startTime = millis();
//              tft.setCursor(40,40);
//              tft.print(startTime);
//              bool runHeart = true;
//              while(runHeart){
//
//                    bool checkBack = isBackPressed();
//                    if(checkBack == true){
//                      CurrentStatus = 1;
//                      drawSdJpeg(screen[CurrentStatus] , 0 , 0);
//                      return;
//                    }
//                    
//                    int presentTime = millis();
//                    tft.setCursor(80,40);
//                    tft.print(presentTime);
//                    getBpm();    
//
//                    tft.setCursor(138,49);
//                    tft.print(beatAvg);
//
//
//                    refreshScreen(40,40,10);
//                    refreshScreen(80, 40 ,10);
//                    refreshScreen(138,49,0);
//            
//            }
//          
//        }
//    }

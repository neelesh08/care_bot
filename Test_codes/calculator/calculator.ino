

#include<SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include <Fonts/FreeSans9pt7b.h> 
#include <JPEGDecoder.h> 
#include <SPI.h>
#include <SD.h>
#include <TFT.h> 

#include "TouchEvent.h"

//used pins
#define TFT_CS   5      //diplay chip select
#define TFT_DC   2     //display d/c
#define TFT_MOSI 23     //diplay MOSI
#define TFT_CLK  18     //display clock
#define TFT_RST  4     //display reset
#define TFT_MISO 19     //display MISO

#define TOUCH_CS 21    //touch screen chip select
#define TOUCH_IRQ 22     //touch screen interrupt


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS , TFT_DC ,TFT_RST); // created tft object
XPT2046_Touchscreen touch(TOUCH_CS , TOUCH_IRQ); // created object for touch

TouchEvent tevent(touch); // tevent controller
TS_Point last;

String result = "";
String last1 = " ";


void condition(int x1 , int x2 , int y1 , int y2 , String x , TS_Point p){
  if(p.x > x1 && p.x < x2 && p.y >y1 && p.y < y2){
    tft.print(x);
    last1 = "1";
    result += "1";
  }
}





void onClicked(TS_Point p){
 
  tft.setCursor(20,30);
  tft.setTextColor(ILI9341_BLACK);
  tft.print(last1);
 
  tft.setTextSize(1);
  tft.setCursor(20,30);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  
  if(p.x > 11 && p.x <46 && p.y > 69 && p.y < 105){
      tft.print("1");
      last1 = "1";
      result += "1";
      
      
  }

  else if(p.x > 11 && p.x <46 && p.y > 124 && p.y <159 ){
      tft.print("4");
      last1 = "4";
      result += "4";
      
  }

  else if(p.x > 11 && p.x <46 && p.y > 179 && p.y <214){
      tft.println("7");
      last1 = "7";
      result += "7";
  }

  else if(p.x > 61 && p.x <96 && p.y > 69 && p.y <105 ){
      tft.println("2");
      last1 = "2";
      result += "2";
  }

  else if(p.x > 61 && p.x <96&& p.y > 124 && p.y <159 ){
      tft.println("5");
      last1 = "5";
      result += "5";
  }
  else if(p.x > 61 && p.x <96 && p.y > 179 && p.y <214 ){
      tft.println("8");
      last1 = "8";
      result += "8";
  }

  else if(p.x > 111 && p.x <146 && p.y > 69 && p.y <105 ){
      tft.println("3");
      last1 = "3";
      result += "3";
  }

  else if(p.x > 111 && p.x <146 && p.y > 124 && p.y <159 ){
      tft.println("6");
      last1 = "6";
      result += "6";
  }

  else if(p.x > 111 && p.x <146 && p.y > 179 && p.y <214 ){
      tft.println("9");
      last1 = "9";
      result += "9";
  }

  else if(p.x > 161 && p.x <196 && p.y > 69 && p.y <105 ){
    tft.println("0");
    last1 = "0";
    result += "0";
  }
  else if(p.x > 161 && p.x <196 && p.y > 124 && p.y <159 ){
      tft.println("+");
      last1 = "+";
      result += "+";
  }
  else if(p.x > 161 && p.x <196 && p.y > 179 && p.y <214 ){
      
      tft.println("-");
      last1 = "-";
      result += "-";
  }

  else if(p.x > 211 && p.x <246 && p.y > 69 && p.y <105 ){
      tft.println(".");
      last1 = ".";
      result += ".";
  }

  else if(p.x > 211 && p.x <246 && p.y > 124 && p.y <159 ){
      tft.println("/");
      last1 = "/";
      result += "/";
      
  }

  else if(p.x > 211 && p.x <246 && p.y > 179 && p.y <214 ){
      tft.println("*");
      last1 = "*";
      result += "*";
  }

  else if(p.x > 267 && p.x <302 && p.y > 69 && p.y <105 ){
      tft.println("CE");
      last1 = "CE";
  }

  else if(p.x > 267 && p.x <302 && p.y > 124 && p.y <159 ){
      tft.println("CLR");
      last1 = "CLR";
  }

  else if(p.x > 267 && p.x <302 && p.y > 179 && p.y <214 ){
      tft.println(result);
      last1 = "=";
      
  }

  

 

////  if(p.x > 11 && p.x <46 && p.y > 69 && p.y < 105){
//    result += "1";
//     tft.fillRect(11,14,285,35,ILI9341_WHITE);
//    tft.setCursor(15,20);
//    tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);
//    tft.print("CLICKED 1");
//    Serial.println(p.x);
//    Serial.print(" ");
//    Serial.print(p.y);
//    tft.println(p.x);
//    tft.println(p.y);
//  }
  
}




void drawIcon(){

  int icon_width = 35 , icon_height = 35;

  tft.drawRect(11,14,285,35,ILI9341_WHITE);
  tft.setFont(&FreeSans9pt7b);

  //  row 1
  tft.setCursor(23,88);
  tft.print("1");

  tft.setCursor(73,88);
  tft.print("2");

  tft.setCursor(123,88);
  tft.print("3");

  tft.setCursor(172,88);
  tft.print("0");

  


  tft.setCursor(267,88);
  tft.print("CE");

  // ROW 2

  tft.setCursor(23,144);
  tft.print("4");

  tft.setCursor(73,144);
  tft.print("5");

  tft.setCursor(123,144);
  tft.print("6");

  tft.setCursor(172,144);
  tft.print("7");

  tft.setCursor(227,144);
  tft.print("/");

  tft.setCursor(267,144);
  tft.print("CLR");

  // ROW3 

  tft.setCursor(23,199);
  tft.print("7");

  tft.setCursor(73,199);
  tft.print("8");

  tft.setCursor(123,199);
  tft.print("9");

  tft.setCursor(227,199);
  tft.print("x");

  tft.setCursor(267,199);
  tft.print("=");

  tft.setTextSize(2);
  tft.setCursor(172,199);
  tft.print("-");

  

  

  tft.setCursor(227,88);
  tft.print(".");


    tft.setTextSize(1);
  

  tft.drawRect(11,69,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(11,124,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(11,179,icon_width,icon_height,ILI9341_WHITE);
  
  tft.drawRect(61,69,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(61,124,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(61,179,icon_width,icon_height,ILI9341_WHITE);

  tft.drawRect(111,69,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(111,124,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(111,179,icon_width,icon_height,ILI9341_WHITE);

  tft.drawRect(161,69,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(161,124,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(161,179,icon_width,icon_height,ILI9341_WHITE);

  tft.drawRect(211,69,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(211,124,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(211,179,icon_width,icon_height,ILI9341_WHITE);

  tft.drawRect(267,69,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(267,124,icon_width,icon_height,ILI9341_WHITE);
  tft.drawRect(267,179,icon_width,icon_height,ILI9341_WHITE);



  
}


void setup() {

  Serial.begin(115200);
  tft.begin();
  touch.begin();
  tft.setRotation(1);
  tevent.setResolution(tft.width(),tft.height());
  Serial.println("WELCOME TO CALCULATOR");
  Serial.println("Display resolution");
  
  Serial.println(tft.width());
  Serial.println(tft.height());
  tevent.registerOnTouchClick(onClicked);
  tft.fillScreen(ILI9341_BLACK);
  drawIcon();

}

void loop() {
  
  tevent.pollTouchScreen();
}



void drawSdJpeg(const char *filename, int xpos, int ypos) {

  // Open the named file (the Jpeg decoder library will close it)
  File jpegFile = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
 
  if ( !jpegFile ) {
    Serial.print("ERROR: File \""); Serial.print(filename); Serial.println ("\" not found!");
    return;
  }

  Serial.println("===========================");
  Serial.print("Drawing file: "); Serial.println(filename);
  Serial.println("===========================");

  // Use one of the following methods to initialise the decoder:
  bool decoded = JpegDec.decodeSdFile(jpegFile);  // Pass the SD file handle to the decoder,
  //bool decoded = JpegDec.decodeSdFile(filename);  // or pass the filename (String or character array)

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

//####################################################################################################
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//####################################################################################################
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
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
  uint32_t min_w = jpg_min(mcu_w, max_x % mcu_w);
  uint32_t min_h = jpg_min(mcu_h, max_y % mcu_h);

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
    else win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

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

//####################################################################################################
// Print image information to the serial port (optional)
//####################################################################################################
// JpegDec.decodeFile(...) or JpegDec.decodeArray(...) must be called before this info is available!
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

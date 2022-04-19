

#include<SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include <Fonts/FreeSans9pt7b.h> 

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
  // put your main code here, to run repeatedly:
  tevent.pollTouchScreen();
}

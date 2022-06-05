

#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
 
// JPEG decoder library
#include <JPEGDecoder.h>

// Toucj controller
#include <XPT2046_Touchscreen.h>
#include "TouchEvent.h"

#define TOUCH_CS 21    //touch screen chip select
#define TOUCH_IRQ 22     //touch screen interrupt

// Creating object of class XPT2046_Touchscreen
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);

const char* icon[] = {"/icon0_40.jpg" , "/icon0_50.jpg" , "/icon0_60.jpg",
                      "/icon1_40.jpg" , "/icon1_50.jpg" , "/icon1_60.jpg",
                      "/icon2_40.jpg" , "/icon2_50.jpg" , "/icon2_60.jpg",
                      "/icon3_40.jpg" , "/icon3_50.jpg" , "/icon3_60.jpg",
                      "/icon4_40.jpg" , "/icon4_50.jpg" , "/icon4_60.jpg",
                      "/icon5_40.jpg" , "/icon5_50.jpg" , "/icon5_60.jpg"       
                  } ;

const char* screen[] = { "/screen_1.jpg" , "/screen_2.jpg" }; 

//init TouchEvent with pointer to the touch screen driver
TouchEvent tevent(touch);
TS_Point p;
int pos = 0;

void setup(){
  touch.begin();

  sd_setup();
  
//  tevent.registerOnTouchClick(changeIcon);
  tevent.registerOnTouchClick(changeScreen);
//  tevent.registerOnTouchSwipe(onSwipe);
  drawSdJpeg(screen[0] , 0 , 0 );
  
}

void iconUndrawer(){
  drawSdJpeg(icon[0] , 253 , 0);
  drawSdJpeg(icon[1] , 191 , 35);
  drawSdJpeg(icon[2] , 135 , 95);
  drawSdJpeg(icon[1], 191 , 160);
  drawSdJpeg(icon[0] , 256, 200);
}



void iconDrawer(int p1,int p2 , int p3 ,int p4 , int p5){
  drawSdJpeg(icon[p1] , 253 , 0);
  drawSdJpeg(icon[p2] , 191 , 35);
  drawSdJpeg(icon[p3] , 135 , 95);
  drawSdJpeg(icon[p4] , 191 , 160);
  drawSdJpeg(icon[p5] , 256, 200);
}

void testCount(TS_Point p){
  pos++;
  tft.setCursor(40,40);
  tft.print(pos);
}

void onSwipe(uint8_t dir) {
   if(pos > 5){
    pos = 5;
  }
  if(pos <= 0){
    pos = 0;
  }
  switch(dir) {
    case 0:  //right to left switch to next screen
        pos++;
       
      
      break;
    case 1:  //left to right switch to previous screen
        pos--;
        
     
      break;
  }
  switch(pos){
    case 1:
          iconDrawer(3,7,11,13,15);
          break;
    case 2:
          iconDrawer(6,10,14,16,3);
          break;
    case 3:
          iconDrawer(9,13,17,4,6);
          break;
    case 4:
          iconDrawer(12,16,5,7,9);
          break;
    case 5:
          iconDrawer(15,4,8,10,12);
          break;
    default:
          break;
  }
}

void changeScreen(TS_Point p){

//  if(p.x > 200 && p.x< 250 && p.y > 180 && p.y < 230){
//     
//  }


  tft.setCursor(100,100);
  tft.print("            ");
  tft.setCursor(100,100);
  tft.print("x:");
  tft.print(p.x);
  tft.print(" "); 
  tft.print("y:");
  tft.print(p.y);

  
//  if(p.x > 30 && p.y > 65 && p.x < 80 && p.y < 115){
//    drawSdJpeg(screen[1] , 0 ,0 );
//  }
//
//  if(p.x >30 && p.y > 220 && p.x < 80 && p.y < 270){
//    drawSdJpeg(screen[0] , 0 , 0);
//  }

    if(p.x > 30 && p.y > 65 && p.x < 80 && p.y < 115){
    drawSdJpeg(screen[1] , 0 ,0 );
  }

  if(p.x >30 && p.y > 220 && p.x < 80 && p.y < 270){
    drawSdJpeg(screen[0] , 0 , 0);
  }





  
}



void changeIcon(TS_Point p){
  
  if(p.x > 0 && p.x < 40 && p.y > 23 && p.y < 63 ){
      pos = pos-1;
  }
  else if(p.x > 60 && p.x < 100 && p.y > 23 && p.y < 63){
      pos = pos + 1; 
  }
//  tft.setCursor(60,60);
//  tft.print("          ");
//  tft.setCursor(60,60);
//  tft.print("x:");
//  tft.print(p.x);
//  tft.print(" "); 
//  tft.print("y:");
//  tft.print(p.y);
  tft.setCursor(40,40);
  tft.print("   ");
  tft.setCursor(40,40);
  if(pos > 5){
    pos = 5;
  }
  if(pos <= 0){
    pos = 0;
  }
  tft.print(pos);
  switch(pos){
    
    case 1:
          iconDrawer(3,7,11,13,15);
          break;
    case 2:
          iconDrawer(6,10,14,16,3);
          break;
    case 3:
          iconDrawer(9,13,17,4,6);
          break;
    case 4:
          iconDrawer(12,16,5,7,9);
          break;
    case 5:
          iconDrawer(15,4,8,10,12);
          break;
    default:
          
          break;
  }
}

void loop() {

 
  tevent.pollTouchScreen();
       
}
 

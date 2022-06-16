


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
#include "dict.h"

const char* screen[] = { "/dictionary.jpg"}; 

TouchEvent tevent(touch);
TS_Point p;

void setup(){
  touch.begin();

  sd_setup();
  

  tevent.registerOnTouchClick(dictionaryScreen);

  drawSdJpeg(screen[0] , 0 , 0 );
  
}


void dictionaryScreen(TS_Point p){
 
}

void loop(){

    myFunc();
   
  
}





void myFunc(){

  if( Serial.available() > 0){
    String choice, ch;
    String WordToFind = Serial.readString();
    dictionary obj;
    
    for(;;){

        if(Serial.available() > 0){
        Serial.println("Enter the choice");
        Serial.println("1. Add char 2. display");
        delay(1000);
        choice = Serial.readString();
      
        int choice1 = choice.toInt();
        switch(choice1){
          
          case 1: 
                Serial.println("Enter the char");
                if(Serial.available() >0 ){
                  delay(100);
                  ch = Serial.readString();
                   obj.addChar(ch);
                }
               

                break;
           case 2:
                Serial.println("Display");
                obj.displayWord();
                break;
           default :
                Serial.print(choice1);
                Serial.println("Invalid choice");          
        }   
    }
    }
  }

  
}

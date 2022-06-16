

#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(); // tft display object

#include <JPEGDecoder.h>
#include <XPT2046_Touchscreen.h>
#include "TouchEvent.h"

// including max sensor library
#include "MAX30105.h"
#include "heartRate.h"
MAX30105 particleSensor; // max30105 object 

// including rtc library
//#include "RTClib.h"
//RTC_DS1307 rtc;
//
//bool Showtime = false;
//String presentTime = "";

#define TOUCH_CS 21      //touch screen chip select
#define TOUCH_IRQ 22     //touch screen interrupt


const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

// Creating object of class XPT2046_Touchscreen
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);


const char* screen[] = { "/new_ui/main_screen.jpg" ,
                         "/new_ui/main_screen_2.jpg", "/new_ui/steps.jpg" , "/new_ui/heart_rate.jpg" ,"/new_ui/spo2.jpg" , "/new_ui/temp", 
                         "/new_ui/photo_viewer.jpg", "/new_ui/Alarm.jpg" , "/new_ui/soil_moisture.jpg" , "/new_ui/calculator.jpg", 
                         "/new_ui/stocks.jpg" , "/new_ui/dictionary.jpg" , "/new_ui/settings.jpg" , "/new_ui/weather.jpg", 
                         
                         }; 

int CurrentStatus = 0;

//init TouchEvent with pointer to the touch screen driver
TouchEvent tevent(touch);
TS_Point p;

TS_Point p_old;

int pos = 0;


// --------------------- setup ------------------------
void setup(){
  touch.begin();
  sd_setup();
  
//  xTaskCreatePinnedToCore( coreOneTask , "fucntion" , 100000 , NULL , 0,NULL , 0);
//  delay(100);
  drawSdJpeg(screen[0] , 0 , 0 ); 
  delay(100);
  
}








    


void mainScreen(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
  while(true){
      if(touch.touched() && !touch.bufferEmpty()){
            GetPoint();
          
          // <--------------------- health -------------------------->  
            if(p.x > 41 && p.x < 90 && p.y > 20 && p.y < 69){
                CurrentStatus = 2;
                steps();
       
            }
            else if(p.x > 102 && p.x <151 && p.y >20 && p.y < 69){
              CurrentStatus = 3;
              heartRate();
            }

            else if(p.x > 163 && p.x < 212 && p.y > 20 && p.y < 69){
              CurrentStatus =4;
              spo2();
            } 

            else if(p.x > 224 && p.x < 273 && p.y > 20 && p.y < 69){
              CurrentStatus = 5;
              temp();
          }

          // <---------------------- basic category       --------------------->

          else if(p.x > 41 && p.x < 90 && p.y > 77 && p.y < 126){
              CurrentStatus =6 ;
              gallery();
              
          }

          else if(p.x > 102 && p.x <151 && p.y >77 && p.y < 126){
              CurrentStatus  = 7;
              alarm_rtc();
          }


          else if(p.x > 163 && p.x < 212 && p.y > 77 && p.y < 126){
              CurrentStatus = 8;
              soil_moisture();
          }

          else if(p.x > 224 && p.x < 273 && p.y > 77 && p.y < 126){
              CurrentStatus = 9;
              calculator();
          }

          //-------------------- stocks ---------------// 

          else if(p.x > 41 && p.x < 90 && p.y > 134 && p.y < 183){
              CurrentStatus =10 ;
              stocks();
              
          }

          else if(p.x > 102 && p.x <151 && p.y >134 && p.y < 183){
              CurrentStatus  = 11;
              dictionary();
          }


          else if(p.x > 163 && p.x < 212 && p.y > 134 && p.y < 183){
              CurrentStatus = 12;
              settings();
            
          }

          else if(p.x > 224 && p.x < 273 && p.y > 134 && p.y < 183){
              CurrentStatus = 13;
              weather();
          }
            
          
          // up arrow , home  , down arrow navigation
          else if(p.x > 41 && p.x < 119 && p.y > 202 && p.y < 230){
              CurrentStatus = 1;
//              drawSdJpeg(screen[CurrentStatus] , 0 , 0);
              
          }

          else if(p.x > 119 && p.x < 197 && p.y > 202 && p.y < 230){
            CurrentStatus = 0;
            drawSdJpeg(screen[CurrentStatus], 0 , 0); 
            return;
          }

          else if(p.x > 197 && p.x < 275 && p.y > 202 && p.y <230){
//            CurrentStatus = 14;
//            drawSdJpeg(screen[CurrentStatus] , 0 , 0);
//            mainScreen1();
            
          }
          
    }
  }
}

void mainScreen1(){



  while(true){
      if(touch.touched() && !touch.bufferEmpty()){
            GetPoint();
          
          // <--------------------- health -------------------------->  
            if(p.x > 41 && p.x < 90 && p.y > 20 && p.y < 69){
                CurrentStatus = 2;
                steps();
       
            }
            else if(p.x > 102 && p.x <151 && p.y >20 && p.y < 69){
              CurrentStatus = 3;
              heartRate();
            }

            else if(p.x > 163 && p.x < 212 && p.y > 20 && p.y < 69){
              CurrentStatus =4;
              spo2();
            } 

            else if(p.x > 224 && p.x < 273 && p.y > 20 && p.y < 69){
              CurrentStatus = 5;
              temp();
          }

          // <---------------------- basic category       --------------------->

          else if(p.x > 41 && p.x < 90 && p.y > 77 && p.y < 126){
              CurrentStatus =6 ;
              gallery();
              
          }

          else if(p.x > 102 && p.x <151 && p.y >77 && p.y < 126){
              CurrentStatus  = 7;
              alarm_rtc();
          }


          else if(p.x > 163 && p.x < 212 && p.y > 77 && p.y < 126){
              CurrentStatus = 8;
              soil_moisture();
          }

          else if(p.x > 224 && p.x < 273 && p.y > 77 && p.y < 126){
              CurrentStatus = 9;
              calculator();
          }

         
            
          
          // up arrow , home  , down arrow navigation
          else if(p.x > 41 && p.x < 119 && p.y > 202 && p.y < 230){
              CurrentStatus = 1;
              drawSdJpeg(screen[CurrentStatus] , 0 , 0);
              mainScreen();              
          }

          else if(p.x > 119 && p.x < 197 && p.y > 202 && p.y < 230){
            CurrentStatus = 0;
            drawSdJpeg(screen[CurrentStatus], 0 , 0); 
            return;
          }

          else if(p.x > 197 && p.x < 275 && p.y > 202 && p.y <230){
            CurrentStatus = 14;
            
            
          }
          
    }
  }
  
}


//void printTime(int x , int y){
//    DateTime now = rtc.now();
//   char buf[] = "hh:mm";
//   tft.setCursor(x, y);
//   tft.setTextSize(3);
//   tft.println(now.toString(buf));
//   delay(100);
//}




void loop() {
    
//    printTime(100,40);


    if(touch.touched() && !touch.bufferEmpty()){
      
      GetPoint();
        Serial.print("P.x :");
        Serial.print(p.x);
        Serial.print("P.y :");
        Serial.print(p.y);
        Serial.println(" ");
        
      if(p.x > 180 && p.x < 220 && p.y > 182 && p.y < 222){
          CurrentStatus = 1;
          Serial.print("P.x :");
          Serial.print(p.x);
          Serial.print("P.y :");
          Serial.print(p.y);
          Serial.println(" ");
        
          mainScreen();
          
      }
    }

       
}


void GetPoint(){
   p = touch.getPoint();
   p.x = map(p.x , 256 ,3860, 0 ,320);
   p.y = map(p.y , 300 , 3760 , 0 ,240);
   
}


bool isBackPressed(){
  GetPoint();
  if(p.x >0 && p.x < 30 && p.y >0 && p.y < 30)
    return true;
  
  return false;
}

bool isStartPressed(){
  GetPoint();
  if(p.x > 37 && p.x < 283 && p.y > 193 && p.y < 225 ){
    return 1;
  }
    return 0;  
}


void refreshScreen(int cor_x , int cor_y , int len){
  tft.setCursor(cor_x , cor_y);
  String x = " ";
  for(int i=0 ; i<len ; i++){
    x += " ";
  }
  tft.print(x);
  
}








void changeScreen(TS_Point p){

  int x = 0;
  
  while(true){
    
    p = touch.getPoint();
//     p.x = map(p.x, TS_LEFT, TS_RT, 0, 320);
//     p.y = map(p.y, TS_TOP, TS_BOT, 0, 240);
    Serial.print(" x: ");
    Serial.print(p.x);
    Serial.print(" y: ");
    Serial.print(p.y);
    Serial.println("");
    
    if(p.x > 145 && p.x < 180 && p.y > 200 && p.y > 230){
      mainScreen();
    }
   }
 }

void touchTest(){


  if(touch.touched()){

      if(!touch.bufferEmpty()){

       
//        p = touch.getPoint();
//        refreshScreen(0,0,18);
//        refreshScreen(0,20,18);

//        tft.setCursor(0,0);
//        tft.print("p.x :");
//        tft.print(p.x);
//        tft.print("p.y :");
//        tft.print(p.y);
        
//        tft.println(" ");
        
//        
//        p.x = map(p.x , 256 ,3860, 0 ,320);
//        p.y = map(p.y , 300 , 3760 , 0 ,240);
//        
//        tft.setCursor(0,20);
//
//        tft.print("P.x :");
//        tft.print(p.x);
//        tft.print("P.y :");
//        tft.print(p.y);
//        tft.println(" ");

        
        Serial.print("P.x :");
        Serial.print(p.x);
        Serial.print("P.y :");
        Serial.print(p.y);
        Serial.println(" ");
        

      }
   }
}

void testFontSize(){

    tft.setCursor(0,0);
    tft.setTextSize(1);
    tft.print("Neelesh");

    tft.setCursor(0,20);
    tft.setTextSize(2);
    tft.print("Neelesh");

    tft.setCursor(0,40);
    tft.setTextSize(3);
    tft.print("Neelesh");

    tft.setCursor(0,80);
    tft.setTextSize(4);
    tft.print("Neelesh");

    tft.setCursor(0,160);
    tft.setTextSize(5);
    tft.print("Neelesh");
}

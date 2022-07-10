
//#include "dictionary.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <ThingESP.h>
ThingESP32 thing("user109", "ESP8266", "888555222");
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(); // tft display object



#include<WiFi.h>
#include<HTTPClient.h>
#include<ArduinoJson.h>

#include <JPEGDecoder.h>
#include <XPT2046_Touchscreen.h>
#include "TouchEvent.h"

// including max sensor library
#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"
MAX30105 particleSensor; // max30105 object 
//
#include <Wire.h>
#include <ADXL345.h>


ADXL345 adxl; 

// start time
unsigned long startTime = 0;
unsigned long presentTime;

const char* ssid = "ASUS_X00TD";
const char* password = "healsou1";
// including rtc library
#include "RTClib.h"
RTC_DS1307 rtc;


#define TOUCH_CS 13      //touch screen chip select
#define TOUCH_IRQ 26     //touch screen interrupt


#define color 0x282828
// boolean values for the working 
bool ShowSteps = true;   
bool ShowTimings = true;

// twilio 

// time format

// spo2 
#define MAX_BRIGHTNESS 255

//// variables for spo2 
uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data
int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid

byte pulseLED = 11; //Must be on PWM pin
byte readLED = 13; //Blinks with each data read

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

String heartrate;
String spo2Modified;
float temperature;

// Creating object of class XPT2046_Touchscreen
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);


const char* screen[] = { "/new_ui/main_screen.jpg" ,
                         "/new_ui/main_screen_2.jpg", "/new_ui/steps.jpg" , "/new_ui/heart_rate.jpg" ,"/new_ui/spo2.jpg" , "/new_ui/temp.jpg", 
                         "/new_ui/photo_viewer.jpg", "/new_ui/Alarm.jpg" , "/new_ui/soil_moisture.jpg" , "/new_ui/calculator.jpg", 
                         "/new_ui/stocks.jpg" , "/new_ui/dictionary.jpg" , "/new_ui/settings.jpg" , "/new_ui/weather.jpg", 
                         "/new_ui/main_screen_4.jpg" , 
                         "/new_ui/temp.jpg" , "/new_ui/fill.jpg" , "/new_ui/music.jpg" , "/new_ui/camera_shutter.jpg" , 
                         "/new_ui/games/jpg" , "/new_ui/media.jpg" , "/new_ui/energy_saver.jpg" , "/new_ui/energy_saver.jpg" , 
                         "/new_ui/deep_sleep.jpg" ,
                         "/new_ui/wifi_connecting.jpg"
                      
                     }; 


int step_s =0 ;
float distance = 0;
int calories = 0;
float prevAcl = 0 , newAcl = 0;

int CurrentStatus = 0;

//init TouchEvent with pointer to the touch screen driver
TouchEvent tevent(touch);
TS_Point p;

TS_Point p_old;

int pos = 0;

DateTime now;




// --------------------- setup ------------------------
void setup(){
  touch.begin();
  sd_setup();

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(100 , 100);
  tft.print("Searching wifi");
  
  twilioStepUp();
  xTaskCreatePinnedToCore( twilio , "function" , 4092 , NULL , 0,NULL ,0);
   //xTaskCreatePinnedToCore( twilio , "function1", 4092 , NULL , 0 ,NULL , 1);
//  delay(100);
  drawSdJpeg(screen[0] , 0 , 0 ); 
//  rtc_setup();
    adlx_setup();
  delay(100); //vTaskdelay(1000);
  
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
              heartRateMeasure();
            }

            else if(p.x > 163 && p.x < 212 && p.y > 20 && p.y < 69){
              CurrentStatus =4;
//              spo2Measure();
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
              //dictionary();
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
            CurrentStatus = 14;
            drawSdJpeg(screen[CurrentStatus] , 0 , 0);
            mainScreen1();    
        }
    }
  }
}

void mainScreen1(){



  while(true){
      if(touch.touched() && !touch.bufferEmpty()){
            GetPoint();
          
          

         
            
          
          // up arrow , home  , down arrow navigation
           if(p.x > 41 && p.x < 119 && p.y > 202 && p.y < 230){
              CurrentStatus = 1;
              drawSdJpeg(screen[CurrentStatus] , 0 , 0);
              mainScreen();              
          }

          else if(p.x > 119 && p.x < 197 && p.y > 202 && p.y < 230){
            CurrentStatus = 0;
            drawSdJpeg(screen[CurrentStatus], 0 , 0); 
            initialScreen();
          }

          else if(p.x > 197 && p.x < 275 && p.y > 202 && p.y <230){
            CurrentStatus = 14;
            
            
            
          }
          
    }
  }
  
}



void loop(){   //esp32 two cpu0 and cpu1   loop() uses cpu1
  initialScreen();
}



void initialScreen() {

    while(1){
 
//          tft.setCursor(100 , 100);
//          char buf[] = "hh:mm";
//          tft.print(now.toString(buf));
          if(touch.touched() && !touch.bufferEmpty()){
                GetPoint();  
                if(p.x > 140 && p.x < 180 && p.y > 167 && p.y < 207){
                CurrentStatus = 1;
                mainScreen();   
            }
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

void  refreshScreen1(int x , int y , int w , int h){
  tft.fillRect(x, y , w, h, color);
}

void refreshScreen(int cor_x , int cor_y ,  int len ){
  
    String temp = "";
    for(int i=0; i<len ; i++){
      temp += temp + " ";
    }
  
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


//        Serial.print("P.x :");
//        Serial.print(p.x);
//        Serial.print("P.y :");
//        Serial.print(p.y);
//        Serial.println(" ");

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

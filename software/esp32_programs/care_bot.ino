#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
#include <ThingESP.h>
#include <WiFi.h>
ThingESP32 thing("user109", "ESP8266", "888555222");
int LED = LED_BUILTIN;
int i;
unsigned long previousMillis = 0;
const long INTERVAL = 6000;
int x[2];
String heartbeat;

void setup(){

  //set up max30010
  max_setup();


     
// thingespsetup
    pinMode(LED, OUTPUT);
    thing.SetWiFi("KAVYASHREE", "8150966088");
    thing.initDevice();
  


  //setup sd and tft 
  tft.init();
  tft.setRotation(1);
 tft.fillScreen(TFT_BLACK);

  
}


String HandleResponse(String query)
{
    if  (query == "led")      
    {
     
        return "heartbeat";
    }
    else{
        return "Your query was invalid..";
}
}
void loop(){
  
  max_loop();

  tft.setCursor(0, 0, 2);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.println("BPM");
  tft.setTextFont(4);
  tft.setTextColor(TFT_BLUE,TFT_BLACK);

  if (x[0] >= 99){
     heartbeat = String(x[0]);
     tft.println(heartbeat);
  }
  else{
  String heartbeat = "0" + String(x[0]);
  tft.println(heartbeat);
  
  }

  
  tft.setTextSize(1);
  tft.setTextFont(2);
  

  if(x[1] == 1){
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    tft.println("  detected      ");
    
  }
  else{
    tft.setTextColor(TFT_RED,TFT_BLACK); 
    tft.println("NOT detected");
  
  }
  delay(100);
  thing.Handle();
  delay(100);

}

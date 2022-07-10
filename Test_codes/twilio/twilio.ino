#include <ThingESP.h>
ThingESP32 thing("user109", "ESP8266", "888555222");


int LED = LED_BUILTIN;

unsigned long previousMillis = 0;
const long INTERVAL = 6000;  

void setup()
{
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  thing.SetWiFi("ASUS_X00TD", "healsou1");

  thing.initDevice();

}


String HandleResponse(String query)
{

  if (query == "led on") {
    digitalWrite(LED, 0);
    return "Done: LED Turned ON";
  }

  else if (query == "led off") {
    digitalWrite(LED, 1);
    return "Done: LED Turned OFF";
  }

  else if (query == "led status")
    return digitalRead(LED) ? "LED is OFF" : "LED is ON";


  else return "Your query was invalid..";

}


void loop()
{

  

  thing.Handle();

}

#include <FirebaseESP32.h>
#include  <WiFi.h>
#include "DHT.h"

#define FIREBASE_HOST "https://stealth-3c873-default-rtdb.firebaseio.com/"
#define WIFI_SSID "ASUS_X00TD" // Change the name of your WIFI
#define WIFI_PASSWORD "healsou1" // Change the password of your WIFI
#define FIREBASE_Authorization_key "6VVoOF9VCrBlsPr1mBY7jlw8NTD02ClCiNFtZ2B2"

#define DHTPIN 5
#define SOILPIN A0

#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;
FirebaseJson json;

// variables for storing data
float hum ;
  float temp;
  float soil;

void setup() {
 Serial.begin(115200);
  pinMode(SOILPIN, INPUT);
  dht.begin();
  twilioStepUp();
//   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
//   Serial.print("Connecting...");
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    Serial.print(".");
//    delay(300);
//  }
//  Serial.println();
//  Serial.print("IP Address: ");
//  Serial.println(WiFi.localIP());
//  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  xTaskCreatePinnedToCore( twilio , "function" , 4092 , NULL , 0,NULL ,0);
  
}

void loop() {
 
   hum = dht.readHumidity();
   temp = dht.readTemperature();  
   soil = analogRead(SOILPIN);
   soil = 100 - map(soil , 0 , 4095 , 0 ,100);
   if (isnan(hum) || isnan(temp)  ){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C");
  Serial.print(" Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.println();
  Serial.println("Soil Moisture:" + String(soil));

  Firebase.setFloat(firebaseData, "/Home/Temperature", temp);
  Firebase.setFloat(firebaseData, "/Home/Humidity", hum);
  Firebase.setFloat(firebaseData, "/Home/SoilMoisture", soil);
   delay(200);
}

// ------------------------------------------- Stocks ----------------------------------------

void stocks(){

    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
}



// ------------------------------------------- settings ----------------------------------------------------

void settings(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
}

// wifi status check 

void wifiStatus(){
  delay(100);
//  CurrentStatus = 20;
//  drawSdJpeg(screen[CurrentStatus] , 0 , 0);

  
  WiFi.begin(ssid, password);
  tft.setCursor(32 , 104);
  tft.setTextSize(3);
  tft.print("Wifi connecting");
   
  while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
        if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
        }
       
  }
  
  



  tft.setCursor(32 , 104);
  tft.print("wifi connected");

  
  CurrentStatus = 13 ; 
  drawSdJpeg(screen[CurrentStatus] , 0 , 0);
  return ;

}


// scrap weather data
void scrapWeatherData(String payload){
  char jsonweatherfile[1000];
  payload.toCharArray(jsonweatherfile , 1000);
  StaticJsonDocument<1000> docs;
  deserializeJson(docs , jsonweatherfile);
  String temp = docs["main"]["temp"];
  String temp_max = docs["main"]["temp_max"];
  String temp_min = docs["main"]["temp_min"];
  String humidity = docs["main"]["humidity"];
  String pressure = docs["main"]["pressure"];
  int  visibility = docs["visibility"];

  tft.setTextSize(2);
  tft.setCursor(156,63);
  tft.print(temp);

  tft.setCursor(217 , 123);
  tft.print(temp_max);

  tft.setCursor(217 , 145);
  tft.print(temp_min);

  tft.setCursor(217 , 169);
  tft.print(humidity);

  tft.setCursor(217 , 191);
  tft.print(pressure);

  tft.setCursor(217 , 218);
  tft.print(visibility);

  
  Serial.print("tmep :");
  Serial.print(temp);
  Serial.print("temp_max :");
  Serial.print(temp_max);
  Serial.print("temp_min :");
  Serial.print(temp_min);
  Serial.print("humidity :");
  Serial.print(humidity);
  Serial.print("pressure :");
  Serial.print(pressure);
  Serial.print("visibiltiy :");
  Serial.print(visibility);
  
}

// -------------------------------------------weather -----------------------------------------------

void weather(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
  delay(1000);
  wifiStatus();

  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin("https://api.openweathermap.org/data/2.5/weather?q=bengaluru&appid=73b8dbdabd44cd4c27a2c264beb435f0");
    int httpcode = http.GET();
    if(httpcode > 0 ){
      if(httpcode == HTTP_CODE_OK){
        String payload = http.getString();
        Serial.println(payload);
        scrapWeatherData(payload);
      }
      
    }
    else{
      // error message
    }
    http.end();
  }
  
    while(true){
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;



        
      }
    }
  
}

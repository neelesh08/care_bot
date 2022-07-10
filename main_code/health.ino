// ------------------------------------------- Steps function ----------------------------------------

void steps(){

    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
    ShowSteps = false;
    while(true){
      
      if(isBackPressed()){
        ShowSteps = true;
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
        pedometer_loop();

        refreshScreen(138 ,50,2);
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        
        refreshScreen(194 ,130,2);
        tft.setTextColor(TFT_WHITE,TFT_BLACK);

        refreshScreen(92 ,130,2);
        tft.setTextColor(TFT_WHITE,TFT_BLACK);
        
        tft.setCursor(138,50);
        tft.setTextSize(2);
        tft.print(step_s);

        tft.setCursor(194 ,130);
        tft.setTextSize(2);
        tft.print(distance);

        tft.setCursor(92,130);
        tft.setTextSize(2);
        tft.print(calories);
        
      
    }
}

// ------------------------------------------- heart Rate function ------------------------------------


void heartRate(){
    bool runHeart = true;
    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
    max_setup();
    String heartRate = String(beatAvg);
    startTime = millis();
    presentTime = millis();
    while(true){
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
      
    if(p.x > 37 && p.x < 281 && p.y >193 && p.y <225 ){
        
        while(runHeart){
        bpm();
          presentTime = millis();
      if(presentTime - startTime > 45000){
        runHeart = false;
      }
      tft.setTextColor(TFT_WHITE , TFT_BLACK);
      tft.setTextSize(3);
      tft.setCursor(200,100);
      tft.print(String((presentTime-startTime)/1000));
      
    }
    

    
    }
}
    
    CurrentStatus = 1;
    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
    return ;
}


// ------------------------------------------- spo2 ----------------------------------------------------

void spo2(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
  max_setup();
  bool runSpo2  = true;
  startTime = millis();
    while(true){
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }

//      if(p.x > 37 && p.x < 281 && p.y >193 && p.y <225 ){
//        
//        while(runSpo2){
//        bpm();
//          presentTime = millis();
//      if(presentTime - startTime > 45000){
//        runSpo2 = false;
//      }
//      tft.setTextColor(TFT_WHITE , TFT_BLACK);
//      tft.setTextSize(3);
//      tft.setCursor(200,100);
//      tft.print(String((presentTime-startTime)/1000));
//      
//    }
//    
//
//    
//    }


      
    }
  
}

// -------------------------------------------temperature -----------------------------------------------

void temp(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
}



// ------------------------------------------ heart rate ---------------------------------------------



void getHeartRate(){
    
    unsigned long startTime = millis();
    unsigned long presentTime = 0;
    while(presentTime - startTime > 45000){
      tft.print(presentTime);
      presentTime = millis();
      if(isBackPressed()){
        
         CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
          return;
      }

      bpm();
      
    }

  
}


void  bpm(){

  
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

//  Serial.print("IR=");
//  Serial.print(irValue);
//  Serial.print(", BPM=");
//  Serial.print(beatsPerMinute);
//  Serial.print(", Avg BPM=");
  
  tft.setTextColor(TFT_WHITE , TFT_BLACK);
  tft.setCursor(100,100);
  
  Serial.print(beatAvg);
  tft.print(beatAvg);
  if (irValue < 50000){
    
    refreshScreen(97,178,18);
    tft.setTextColor(TFT_WHITE , TFT_BLACK);
    tft.setCursor(97,178);
    tft.print("no finger?");
    Serial.print(" No finger?");
  }
  Serial.println();
}

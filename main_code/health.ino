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


void heartRateMeasure(){
    bool runHeart = true;
    
    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
    max_setup();
    ShowSteps = false;
    String heartRate = String(beatAvg);
   
    presentTime = millis();
    while(true){
      
      if(isBackPressed()){
//        ShowSteps = true;
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        particleSensor.shutDown();
        return;
      }
      
    if(p.x > 37 && p.x < 281 && p.y >193 && p.y <225 ){
        beatAvg = 0;
        startTime = millis();
        while(runHeart){
        bpm();
        if(isBackPressed()){

        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        particleSensor.shutDown();
        return;
      }
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

void spo2Measure(){
 
  
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

  max_setup();
  
  bool runSpo2  = true;
 
    while(true){
      if(isBackPressed()){
        particleSensor.shutDown();
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }


      if(p.x > 37 && p.x < 281 && p.y >193 && p.y <225 ){
        spo2 = 0;
        
        while(runSpo2){  
        getSpo2();
        
        if(isBackPressed()){
        
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        particleSensor.shutDown();
        return;
      }
      
     
      tft.setTextColor(TFT_WHITE , TFT_BLACK);
      tft.setTextSize(3);
      tft.setCursor(200,100);
      tft.print(String((presentTime-startTime)/1000));
      
         } 
      } 
    }
  
}

// ----------------------------------------------spo2----------------------------


void getSpo2(){


    bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps

  //read the first 100 samples, and determine the signal range
  for (byte i = 0 ; i < bufferLength ; i++)
  {
    while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample(); //We're finished with this sample so move to next sample

    Serial.print(F("red="));
    Serial.print(redBuffer[i], DEC);
    Serial.print(F(", ir="));
    Serial.println(irBuffer[i], DEC);
  }

  //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
  while (1)
  {

    if(isBackPressed()){
        
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        particleSensor.shutDown();
        return;
      }
    //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
    for (byte i = 25; i < 100; i++)
    {
      redBuffer[i - 25] = redBuffer[i];
      irBuffer[i - 25] = irBuffer[i];
    }

    //take 25 sets of samples before calculating the heart rate.
    for (byte i = 75; i < 100; i++)
    {

      if(isBackPressed()){
        
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        particleSensor.shutDown();
        return;
      }   
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data

      digitalWrite(readLED, !digitalRead(readLED)); //Blink onboard LED with every data read

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample

     if(spo2 <= 9){
       spo2Modified = "0" + String(spo2Modified); 
     }
     else 
     spo2Modified = String(spo2);

     // tft.setCursor(28,94);
      
      if(spo2 == -999) {
        tft.setTextColor(TFT_WHITE , TFT_BLACK);
        tft.setTextSize(1);
        tft.setTextColor(TFT_RED,color);
        tft.setCursor(80,115);
        String error = "data not found";
        tft.println(error);
      }
      else{
      tft.setCursor(80,115);
      tft.setTextColor(TFT_GREEN , color);
      tft.setTextSize(1);
      tft.println("data found     ");
      tft.setCursor(107,105);
      tft.setTextColor(TFT_WHITE,color);
      tft.print(spo2Modified);
      }

      Serial.print(F(", SPO2="));
      Serial.print(spo2, DEC);



     
     
    }
  
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  }
    

  
}



// -------------------------------------------temperature -----------------------------------------------

void temp(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
  max_temp();
    while(true){

      temperature = particleSensor.readTemperature();

      refreshScreen(100 , 100 , 20);
      tft.setCursor(100,100);
      tft.print(String(temperature));
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        particleSensor.shutDown();
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
  if(irValue <= 0){
    irValue = 100;
  }

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
  
  tft.setTextColor(TFT_WHITE , color);
  tft.setCursor(100,100);
  heartrate = String(beatAvg);
    if(beatAvg <= 99){
      heartrate = "0" + String(beatAvg);
    }
  Serial.print(heartrate);
  tft.print(beatAvg);
  if (irValue < 50000){
    
//    refreshScreen1(97,178,18, 18); 
    tft.setTextColor(TFT_WHITE , color);
    tft.setCursor(97,178);
    tft.print("no finger?");
    Serial.print(" No finger?");
  }

  else{
//    refreshScreen1(97,178,18 , 18);
    tft.setTextColor(TFT_WHITE , color);
    tft.setCursor(97,178);
    tft.print("finger detected");
    Serial.print("finger detected");
  }
  Serial.println();
}

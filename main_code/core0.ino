  

 
void twilio(void *parameter){
//  rtc_setup();

  while(1){


        
//       if(ShowSteps)
//       pedometer_loop();

//       if(ShowTimings)
//       printTime();
        //delay(5000);
        vTaskDelay(1000/portTICK_PERIOD_MS);
       thing.Handle();
       //delay(5000);
        vTaskDelay(1000/portTICK_PERIOD_MS);

       
       }
  }


String HandleResponse(String query)
{

  if (query == "send heartrate") {
    String hr = String(beatAvg);
    return hr;
  }

  else if(query == "send spo2") {
    String sp = String(spo2);
    return sp;
  }

  

  else if(query == "send health report"){
    String t = "heart rate" + String(beatAvg) + "\n" + "Spo2 value:" + String(spo2) + "\n";
    return t;
  }

  

//  else if (query == "dude") {
//   
//    return "hemanth boss here";
//  }

//  else if (query == "who is hemanth's girlfriend")
//    return "Her name starts with letter K and ends with a";


  else return "invalid request";

}

void twilioStepUp(){
  thing.SetWiFi("narzo", "UZUMAKI51");
//  thing.SetWiFi("ASUS_X00TD", "healsou1");
  thing.initDevice();
  
}

void printTime(){
   
    now = rtc.now();
    char buf[] = "hh:mm";
    tft.setCursor(0,0);
    tft.setTextColor(TFT_WHITE , TFT_BLACK);
    tft.setTextSize(1);
    //Serial.println(now.toString(buf));
    for(int i = 0; i <5 ;i++ ){ tft.println(String(buf[i]));}
    
    vTaskDelay(3000/portTICK_PERIOD_MS);
    //delay(100);
}

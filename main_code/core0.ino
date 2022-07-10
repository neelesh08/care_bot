

 
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

  if (query == "hi") {

    return "hi macha";
  }

  else if (query == "dude") {
   
    return "hemanth boss here";
  }

  else if (query == "who is hemanth's girlfriend")
    return "Her name starts with letter K and ends with a";


  else return "Hemanth is boss, idc";

}

void twilioStepUp(){
  
  thing.SetWiFi("ASUS_X00TD", "healsou1");
  thing.initDevice();
  
}

void printTime(){
    now = rtc.now();
    char buf[] = "hh:mm";
//   tft.setCursor(x, y);
//   tft.setTextSize(3);
    Serial.println(now.toString(buf));
//   tft.println(now.toString(buf));
   delay(100);
}

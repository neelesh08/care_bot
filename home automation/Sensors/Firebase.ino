#include <ThingESP.h>
ThingESP32 thing("user109", "ESP8266", "888555222");

void twilioStepUp(){
  thing.SetWiFi(WIFI_SSID, WIFI_PASSWORD);
  thing.initDevice();
}

void twilio(void *parameter){


  while(1){
        vTaskDelay(1000/portTICK_PERIOD_MS);
        thing.Handle();
        vTaskDelay(1000/portTICK_PERIOD_MS);
       }
  }

String HandleResponse(String query)
{

  if (query == "send humidity") {
    if(hum == 0)
      return "Data Not found";
    String hr = String(hum ,3 );
    return hr;
  }

  else if(query == "send temp") 
  { if(temp == 0)
        return "Data Not found";
    String sp = String(temp, 3);
    return sp;
  }

  else if(query == "send soil moisture"){
    if(soil == 0)
      return "Data Not found";
    String s = String(soil , 3);
    return s;
  }

  else if(query == "send home report"){

    String report = "";
    report += "Humidity: ";
    report += (hum == 0)? "Data Not found" : String(hum , 3);
    report += "\n";
    report += "Temperature: ";
    report += (temp == 0)? "Data Not found" : String(temp , 3);
    report += "\n";
    report += "Soil moisture: ";
    report += (soil == 0)? "Data Not found" : String(soil , 3);
    
    return report; 
  }


  else return "invalid request";

}

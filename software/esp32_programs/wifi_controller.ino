/*#include <WiFi.h>
#include <ThingESP.h>

ThingESP3

void setup()
{
    Serial.begin(115200);

    pinMode(LED, OUTPUT);

    thing.SetWiFi("wifi_ssid", "wifi_password");

    thing.initDevice();
}

String HandleResponse(String query)
{

    if (query == "led on")
    {
        digitalWrite(LED, 1);
        return "Done: LED Turned ON";
    }

    else if (query == "led off")
    {
        digitalWrite(LED, 0);
        return "Done: LED Turned OFF";
    }

    else if (query == "led status")
        return digitalRead(LED) ? "LED is ON" : "LED is OFF";

    else
        return "Your query was invalid..";
}

void loop()
{

    // if (millis() - previousMillis >= INTERVAL)
    // {
    //     previousMillis = millis();
    //     String msg = digitalRead(LED) ? "LED is ON" : "LED is OFF";
    //     thing.sendMsg("PHONE_NUMBER", msg);
    // }

    thing.Handle();
}*/


void dictionary(){

    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
    Dictionary dict_word;
    String wordx;
    while(true){

        if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }


      if(p.x > 41 && p.x < 279 && p.y > 56 && p.y < 89){
          wordx = wordCollector();
          tft.setCursor(41,56 );
          tft.print(wordx);
          if(WiFi.status() == WL_CONNECTED){
            HTTPClient http;
            http.begin("https://api.dictionaryapi.dev/api/v2/entries/en/" + wordx);

            int httpcode = http.GET();
             if(httpcode > 0 && httpcode == HTTP_CODE_OK){

              String payload = http.getString();
              scrapDictionaryData(payload);

              
             }
             else{
                tft.println("Error found");
             }
             http.end();
          }
  
          }
          
          
      
      
    }
  
}


String wordCollector(){
    CurrentStatus = 25;
    drawSdJpeg(screen[CurrentStatus] , 0 , 0);
    String SearchWord = "";
    while(true){


      if(p.x > 33 && p.x < 56 && p.y >108 && p.y <24){
         SearchWord += "q";
      }

      else if(p.x > 59 && p.x < 82 && p.y >108 && p.y <24){
         SearchWord += "w";
      }

      else if(p.x > 85  && p.x < 108 && p.y >108 && p.y <24){
         SearchWord += "e";
      }

      else if(p.x > 111  && p.x < 134 && p.y >108 && p.y <24){
         SearchWord += "r";
      }

      else if(p.x > 137  && p.x < 160 && p.y >108 && p.y <24){
         SearchWord += "t";
      }

      else if(p.x > 163  && p.x < 186 && p.y >108 && p.y <24){
         SearchWord += "y";
      }

      else if(p.x > 189  && p.x < 212 && p.y >108 && p.y <24){
         SearchWord += "u";
      }

      else if(p.x > 215  && p.x < 238 && p.y >108 && p.y <24){
         SearchWord += "i";
      }

      else if(p.x > 241  && p.x < 264 && p.y >108 && p.y <24){
         SearchWord += "o";
      }

      else if(p.x > 267  && p.x < 290 && p.y >108 && p.y <24){
         SearchWord += "p";
      }

    //---------------------------- zone 2 --------------------------------
      else if(p.x > 44  && p.x < 67 && p.y >137&& p.y < 161){
         SearchWord += "a";
      }

      else if(p.x > 70  && p.x < 93 && p.y >137 &&  p.y < 161){
         SearchWord += "s";
      }

      else if(p.x > 96  && p.x < 119 && p.y >137&& p.y < 161){
         SearchWord += "d";
      }

      else if(p.x > 122  && p.x < 145 && p.y >137 &&  p.y < 161){
         SearchWord += "f";
      }

      else if(p.x > 148  && p.x < 171 && p.y >137&& p.y < 161){
         SearchWord += "g";
      }

      else if(p.x > 174  && p.x < 197 && p.y >137 &&  p.y < 161){
         SearchWord += "h";
      }

      else if(p.x > 201  && p.x < 224 && p.y >137&& p.y < 161){
         SearchWord += "j";
      }

      else if(p.x > 228  && p.x < 251 && p.y >137 &&  p.y < 161){
         SearchWord += "k";
      }

      else if(p.x > 255  && p.x < 278 && p.y >137&& p.y < 161){
         SearchWord += "l";
      }

// ----------------------- zone 3 --------------------------------
      else if(p.x > 73  && p.x < 96 && p.y >167&& p.y < 190){
         SearchWord += "z";
      }

      else if(p.x > 98  && p.x < 121 && p.y >167 &&  p.y < 190){
         SearchWord += "x";
      }

      else if(p.x > 123  && p.x < 146 && p.y >167 && p.y < 190){
         SearchWord += "c";
      }

      else if(p.x > 149  && p.x < 172 && p.y >167 &&  p.y < 190){
         SearchWord += "v";
      }

       else if(p.x > 175  && p.x < 198 && p.y >167 && p.y < 190){
         SearchWord += "b";
      }

      else if(p.x > 201  && p.x < 224 && p.y >167 &&  p.y < 190){
         SearchWord += "n";
      }

       else if(p.x > 227  && p.x < 250 && p.y >167 && p.y < 190){
         SearchWord += "m";
      }

      else if(p.x > 253  && p.x < 276 && p.y >167 &&  p.y < 190){
         // delete last inserted word
         
      }


      else if(p.x > 253 && p.x < 279 && p.y > 195 && 219){
            // Serial.println(SearchWord);
            return SearchWord;
    }

}

}


void scrapDictionaryData(String payload){
  
  char jsonfile[1000];
  payload.toCharArray(jsonfile , 1000); 
  StaticJsonDocument<1000> doc;
  deserializeJson(doc, jsonfile); 

  String buffer1 = doc[0]["meanings"][0]["definitions"][0]["definition"];

  tft.setCursor(41 ,120);
  tft.print(buffer1);
  Serial.println(buffer1);

}

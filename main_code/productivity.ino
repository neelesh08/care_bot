// ------------------------------------------- gallery ----------------------------------------

void gallery(){

    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(touch.touched()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
}

// ------------------------------------------- alarm rtc ------------------------------------


void alarm_rtc(){

    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(touch.touched()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
  
}


// ------------------------------------------- soil moisture----------------------------------------------------

void soil_moisture(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(touch.touched()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
  
}

// -------------------------------------------calculator -----------------------------------------------

void calculator(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(touch.touched()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
  
}

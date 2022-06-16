// ------------------------------------------- Stocks ----------------------------------------

void stocks(){

    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(touch.touched()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
}

// ------------------------------------------- dictionar ------------------------------------


void dictionary(){

    drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(touch.touched()){
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
      if(touch.touched()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
  
}

// -------------------------------------------weather -----------------------------------------------

void weather(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );

    while(true){
      if(touch.touched()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        return;
      }
    }
  
}

// -------------------------------------------calculator -----------------------------------------------

String expression = "";
int len = 0;

void calculator(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
  
   while(true){
      if(isBackPressed()){
        CurrentStatus = 1;
        drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
        expression = "";
        return;
      }

      expressionSolver();

       
      
    
      
    }     
 }


 void expressionSolver(){

       if(touch.touched() && !touch.bufferEmpty()){
      if(p.x > 26  && p.x < 155  && p.y > 206 && p.y < 233){
          expression += "0";  len++;
      }

      else if(p.x > 163  && p.x < 223  && p.y > 206 && p.y < 233){
        expression += "."; len++;
      }

      else if(p.x > 239 && p.x < 299 && p.y > 208 && p.y < 233){

//        const char *Expressn = expression.c_str();
        char buf[30];
        expression += "*";
        expression.toCharArray(buf , expression.length());
        Express* eptr = new Express(buf);
        eptr->parse();
        int res = eptr->solve();
        refreshScreen(30,41, 25);
        tft.setCursor(30,41);
        expression = String(res);
        tft.print(expression);
//        expression = "";
      }


      else if(p.x > 27 && p.x <87 && p.y > 173 && p.y < 200){
        expression += "1"; len++;
      }

      else if(p.x > 95 && p.x < 155 && p.y > 173 && p.y <200){
        expression += "2"; len++;
      }

      else if(p.x > 163 && p.x < 223 && p.y > 173 && p.y < 200){
        expression += "3"; len++;
      }

      else if(p.x > 235 && p.x < 295 && p.y > 173 && p.y <200){
        expression += "+"; len++;
      }


      else if(p.x > 27 && p.x <87 && p.y > 143 && p.y < 170){
        expression += "4"; len++;
      }

      else if(p.x > 95 && p.x < 155 && p.y > 143 && p.y <170){
        expression += "5"; len++;
      }

      else if(p.x > 163 && p.x < 223 && p.y > 143 && p.y < 170){
        expression += "6"; len++;
      }

      else if(p.x > 235 && p.x < 295 && p.y > 143 && p.y <170){
        expression += "-"; len++;
      }

      else if(p.x > 27 && p.x <87 && p.y > 111 && p.y < 138){
        expression += "7"; len++;
      }

      else if(p.x > 95 && p.x < 155 && p.y > 111 && p.y <138){
        expression += "8"; len++;
      }

      else if(p.x > 163 && p.x < 223 && p.y > 111 && p.y < 138){
        expression += "9"; len++;
      }

      else if(p.x > 235 && p.x < 295 && p.y > 111 && p.y <138){
        expression += "*"; len++;
      }


      else if(p.x > 27 && p.x < 87 && p.y > 78 && p.y < 104){
//        expression += "7"; 
          expression = "";
           // clear();
      }

      else if(p.x > 95 && p.x < 155 && p.y > 78 && p.y <104){
//        expression += "8";
//        modulo;
      }

      else if(p.x > 163 && p.x < 223 && p.y > 78 && p.y < 104){
//        expression += "9";
      }

      else if(p.x > 235 && p.x < 295 && p.y > 78 && p.y <104){
//        expression += "*";
          expression += "/";
      }

      refreshScreen(30,41, 25);
      tft.setCursor(30,41);
      tft.setTextSize(1);
      tft.print(expression);
      delay(500);
     
       }    
 }

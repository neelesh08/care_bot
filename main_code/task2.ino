//
//
//void changeScreen(TS_Point p){
//
//  int x = 0;
//  
//  while(true){
//    
//    p = touch.getPoint();
////     p.x = map(p.x, TS_LEFT, TS_RT, 0, 320);
////     p.y = map(p.y, TS_TOP, TS_BOT, 0, 240);
//    Serial.print(" x: ");
//    Serial.print(p.x);
//    Serial.print(" y: ");
//    Serial.print(p.y);
//    Serial.println("");
//    
//    if(p.x > 145 && p.x < 180 && p.y > 200 && p.y > 230){
//      mainScreen();
//    }
//   }
// }
//
//void touchTest(){
//
//
//  if(touch.touched()){
//
//      if(!touch.bufferEmpty()){
//
//       
////        p = touch.getPoint();
////        refreshScreen(0,0,18);
////        refreshScreen(0,20,18);
//
////        tft.setCursor(0,0);
////        tft.print("p.x :");
////        tft.print(p.x);
////        tft.print("p.y :");
////        tft.print(p.y);
//        
////        tft.println(" ");
//        
////        
////        p.x = map(p.x , 256 ,3860, 0 ,320);
////        p.y = map(p.y , 300 , 3760 , 0 ,240);
////        
////        tft.setCursor(0,20);
////
////        tft.print("P.x :");
////        tft.print(p.x);
////        tft.print("P.y :");
////        tft.print(p.y);
////        tft.println(" ");
//
//        
//        Serial.print("P.x :");
//        Serial.print(p.x);
//        Serial.print("P.y :");
//        Serial.print(p.y);
//        Serial.println(" ");
//        
//
//      }
//   }
//}
//
//
////        Serial.print("P.x :");
////        Serial.print(p.x);
////        Serial.print("P.y :");
////        Serial.print(p.y);
////        Serial.println(" ");
//
//void testFontSize(){
//
//    tft.setCursor(0,0);
//    tft.setTextSize(1);
//    tft.print("Neelesh");
//
//    tft.setCursor(0,20);
//    tft.setTextSize(2);
//    tft.print("Neelesh");
//
//    tft.setCursor(0,40);
//    tft.setTextSize(3);
//    tft.print("Neelesh");
//
//    tft.setCursor(0,80);
//    tft.setTextSize(4);
//    tft.print("Neelesh");
//
//    tft.setCursor(0,160);
//    tft.setTextSize(5);
//    tft.print("Neelesh");
//}

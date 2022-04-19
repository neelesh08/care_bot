
#include "tinyexpr.h"
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  double answer = te_interp("3*2+4*1+(4+9)*6", 0);
    Serial.println( answer);
    
}

void loop() {
  // put your main code here, to run repeatedly:
   
}

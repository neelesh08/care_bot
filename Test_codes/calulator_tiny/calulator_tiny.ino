#include "tinyexpr.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  char term[] = "12 + (2 * 5)";
  Serial.println(term);
  int error;
  double result = te_interp(term, &error);
  if (error){
    Serial.println("Problem with expression.");
  } else {
    Serial.printf(" = %.10g\n", result);
  }
  delay(1000);
}

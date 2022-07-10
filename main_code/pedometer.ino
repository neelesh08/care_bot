

void pedometer_loop(){
  int x,y,z;  
  adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z

  double xyz[3];
  double ax,ay,az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];

  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.println(az);
  prevAcl = newAcl;
  newAcl = sqrt(ax*ax+ay*ay+az*az);
  Serial.print("acceleration");

  float change = newAcl - prevAcl;
  

  if (change > .1) step_s++;

  distance = step_s*.000762;
  calories = step_s*0.04;

  Serial.print("steps");
  Serial.println(step_s);
  delay(500);
}

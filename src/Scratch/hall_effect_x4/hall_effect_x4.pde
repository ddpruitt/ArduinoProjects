/*
 *    FILE: MM01
 *  AUTHOR: Rob van den Tillaart
 *    DATE: 2010 03 19 
 *     URL: http://www.arduino.cc/playground/Code/HallEffect
 *
 * PURPOSE: use a A1301 as magnetometer   
 *
 * Pinlayout A1301
 * ==================
 *  1     GND
 *  2     signal    connected to Analog 0    
 *  3     Vdd +5V
 *
 */

int  time = 0;
int  oldtime = -1;
int  rawMM[] = {0,0,0,0};
long  bNull[] = { 516L, 517L, 523L, 523L }; // My midpoint, calibrate this
long B[4];

#define BFAC  1000L   // 2500 mv == 1000 Gauss in 505 steps

void setup() 
{
  // setup serial - diagnostics - port
  Serial.begin(9600);
}

void DoMeasurement()
{
  // measure magnetics
  for(int i=0;i<4;i++) {
    rawMM[i] = analogRead(i);   // Range : 0..1024
    B[i] = (rawMM[i] - bNull[i]) * BFAC / bNull[i];
  }

  
  
  Serial.print("MM:\t");
  for(int i = 0;i<4;i++) {
    Serial.print(rawMM[i]);
    Serial.print(",\t");
  }
    
  Serial.print("\t==B (Gauss):\t");
  for(int i = 0;i<4;i++) {
    Serial.print(B[i]);

    if (B[i] > 0) Serial.print(" SP");
    else Serial.print(" NP");

    if(i <3) Serial.print(",\t");   
  }
  Serial.println();
}

void loop() 
{
  /*
  time = millis()/500;
  if (time == oldtime) 
  {
    delay(100);
  }
  else
  {
    oldtime = time;
    DoMeasurement();
  }
  */
  delay(10);
  DoMeasurement();
}

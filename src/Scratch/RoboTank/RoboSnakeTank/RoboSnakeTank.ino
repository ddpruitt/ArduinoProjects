
#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // motor #2

int motor1Speed = 0;
int motor2Speed = 0;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor Setup");

  // turn on motor
  SetMotorSpeed(255,255);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {
  AheadSlow();
  delay(5000);
  AheadFull();
  delay(5000);
  PivotLeft();
  PivotRight();
  PivotLeft();
  delay(500);
}

int GetSpeedChangeIncrement(int startSpeed, int stopSpeed) {
  if(startSpeed == stopSpeed)
    return 0;
   else if (startSpeed > stopSpeed)
     return -1;
    else
      return 1;
}

void SetMotorSpeed(int m1, int m2) {
  
  if(m1==0) m1 = 1;
  if(m2==0) m2 = 1;
  
  int m1Step = GetSpeedChangeIncrement(motor1Speed, m1);
  int m2Step = GetSpeedChangeIncrement(motor2Speed, m2);
  
  do {

    motor1Speed += m1Step;
    motor1.setSpeed(motor1Speed); 
    
    motor2Speed += m2Step;
    motor2.setSpeed(motor2Speed); 

    delay(10);
  } while (motor1Speed != m1 && motor2Speed != m2);

}

void AheadFull() {
  Serial.println("All motors ahead - fast");  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  SetMotorSpeed(255,255);
}

void AheadSlow() {
  Serial.println("All motors ahead - fast");  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  SetMotorSpeed(100,100);
}

void AllStop() {
  SetMotorSpeed(0,0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void AsternSlow() {
  Serial.println("All motors backward - fast");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  SetMotorSpeed(100,100);
}

void AsternFast() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  SetMotorSpeed(255,255);
}


void PivotLeft() {
  Serial.println("Pivot left");
  AllStop();
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  SetMotorSpeed(100,100);
  delay(250);
  AllStop();
}

void PivotRight() {
  Serial.println("Pivot right");
  AllStop();
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  SetMotorSpeed(100,100);
  delay(250);
  AllStop();
}


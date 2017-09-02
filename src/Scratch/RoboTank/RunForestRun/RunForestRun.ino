
#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // motor #2

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor1.setSpeed(255); 
  motor2.setSpeed(255); 
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {
 go();
 delay(10000);
 halt();
 delay(500);
 left();
 delay(500);
 left();
 delay(1000);
}
void go() {
  Serial.println("All motors ahead - fast");  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor1.setSpeed(255); 
  motor2.setSpeed(255);
}

void backup() {
  Serial.println("All motors backward - fast");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor1.setSpeed(255); 
  motor2.setSpeed(255);
}

void left() {
  Serial.println("Pivot left");
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor1.setSpeed(200); 
  motor2.setSpeed(255);  
}

void right() {
  Serial.println("Pivot right");
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor1.setSpeed(255); 
  motor2.setSpeed(255);  
}

void halt() {
  uint8_t i;
  for (i=255; i!=0; i--) {
    motor1.setSpeed(i); 
    motor2.setSpeed(i); 
    delay(10);
    }
   Serial.println("All motors stop");
   motor1.run(RELEASE);
   motor2.run(RELEASE);
}

void avoidLeft() {
  halt();
  backup();
  delay(1500);
  left();
  delay(900);
}

void avoidRight() {
  halt();
  backup();
  delay(1500);
  right();
  delay(900);
}


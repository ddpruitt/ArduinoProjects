
#include <AFMotor.h>

//AF_DCMotor rightMotor(2, MOTOR12_64KHZ); // motor #1, 64KHz pwm
//AF_DCMotor leftMotor (1, MOTOR12_64KHZ); // motor #2, 64KHz pwm

AF_DCMotor rightMotor(2, MOTOR12_8KHZ); // motor #1, 8KHz pwm
AF_DCMotor leftMotor (1, MOTOR12_8KHZ); // motor #2, 8KHz pwm

//buffer size for NMEA compliant GPS string
#define DATABUFFERSIZE      80
char dataBuffer[DATABUFFERSIZE+1]; //Add 1 for NULL terminator
byte dataBufferIndex = 0;

char startChar = '$'; // or '!', or whatever your start character is
char endChar = '\r';
boolean storeString = false; //This will be our flag to put the data in our buffer

char delimiters[] = "$: ;";
char gamePadCommand[2][DATABUFFERSIZE+1];

char* commands[7] = { "BTN", "LJSY", "LJSX", "RJSY", "RJSX", "LTRG", "LTRG" };
void (*commandFunction[7])() = { handleButton, handleJoystick, handleJoystick, handleJoystick, handleJoystick, handleTrigger, handleTrigger};

uint8_t leftMotorCurrSpeed, leftMotorPrevSpeed;
uint8_t rightMotorCurrSpeed, rightMotorPrevSpeed;

void setup() {
  Serial.begin(9600);
  Serial.flush();
  
//  Serial1.begin(9600);
//  Serial1.flush();

  // turn on motor
  rightMotor.setSpeed(255); 
  leftMotor.setSpeed(255); 
  rightMotor.run(RELEASE);
  leftMotor.run(RELEASE);
  
  leftMotorCurrSpeed = leftMotorPrevSpeed = 0;
  rightMotorCurrSpeed = rightMotorPrevSpeed = 0;
  
  //Serial.println("Setup Complete");  
  
}

void loop() {
   if(getSerialString()){
    //Serial.println(dataBuffer);
    parseNmea(dataBuffer, delimiters);
     
    for( int i=0;i<7;i++) {
         //Serial.print(gamePadCommand[0]),Serial.print(" : "),Serial.println(commands[i]);
       if(strcmp(gamePadCommand[0], commands[i])==0) {
         commandFunction[i]();
         break;
       }
     }
   }
  delay(10); 
} 


void handleButton() {
  if(strcmp(gamePadCommand[1],"S1")==0)  return;
  if(strcmp(gamePadCommand[1],"S2")==0)  return;
  if(strcmp(gamePadCommand[1],"Y")==0)  return;
  if(strcmp(gamePadCommand[1],"X")==0) { allStop();  return; }
  if(strcmp(gamePadCommand[1],"B")==0)  return;
  if(strcmp(gamePadCommand[1],"A")==0)  return;
  if(strcmp(gamePadCommand[1],"WHITE")==0)  return;
  if(strcmp(gamePadCommand[1],"BLACK")==0)  return;
  if(strcmp(gamePadCommand[1],"UP")==0) { goForward();  return; }
  if(strcmp(gamePadCommand[1],"LEFT")==0) { pivotLeft();  return; }
  if(strcmp(gamePadCommand[1],"DOWN")==0) { goBack();  return; }
  if(strcmp(gamePadCommand[1],"RIGHT")==0) { pivotRight();  return; }
  if(strcmp(gamePadCommand[1],"BACK")==0)  return;
  if(strcmp(gamePadCommand[1],"START")==0)  return;
}

void handleJoystick() {
  
  if ( (strcmp(gamePadCommand[0],"RJSX")==0) || (strcmp(gamePadCommand[0],"LJSX")==0)) return;
  
  int jsValue;
  jsValue = atoi(gamePadCommand[1]);
  
  uint8_t directionToGo;
  directionToGo = jsValue > 0 ? FORWARD : BACKWARD;
  jsValue = map(abs(jsValue), 0, 500, 0, 255);
  
  if ( (strcmp(gamePadCommand[0],"RJSY")==0)) {
    rightMotor.run(directionToGo);
    rightMotor.setSpeed(jsValue);
  }

  if ( (strcmp(gamePadCommand[0],"LJSY")==0)) {
    leftMotor.run(directionToGo);
    leftMotor.setSpeed(jsValue);
  }
  
  //Serial.print(gamePadCommand[0]), Serial.print(" : "), Serial.println(jsValue);
}

void handleTrigger(){
  return;
}

void goForward() {
  //Serial.println("All motors ahead - fast");  
  rightMotor.run(FORWARD);
  leftMotor.run(FORWARD);
  rightMotor.setSpeed(255); 
  leftMotor.setSpeed(255);
}

void goBack() {
  //Serial.println("All motors backward - fast");
  rightMotor.run(BACKWARD);
  leftMotor.run(BACKWARD);
  rightMotor.setSpeed(255); 
  leftMotor.setSpeed(255);
}

void pivotLeft() {
  //Serial.println("Pivot left");
  rightMotor.run(FORWARD);
  leftMotor.run(BACKWARD);
  rightMotor.setSpeed(200); 
  leftMotor.setSpeed(255);  
}

void pivotRight() {
  //Serial.println("Pivot right");
  rightMotor.run(BACKWARD);
  leftMotor.run(FORWARD);
  rightMotor.setSpeed(255); 
  leftMotor.setSpeed(255);  
}

void allStop() {
    rightMotor.setSpeed(0); 
    leftMotor.setSpeed(0); 
   //Serial.println("All motors stop");
   rightMotor.run(RELEASE);
   leftMotor.run(RELEASE);
}

boolean getSerialString(){
    static byte dataBufferIndex = 0;
    while(Serial.available()>0){
        char incomingbyte = Serial.read();
        if(incomingbyte==startChar){
            dataBufferIndex = 0;  //Initialize our dataBufferIndex variable
            storeString = true;
        }
        if(storeString){
            //Let's check our index here, and abort if we're outside our buffer size
            //We use our define here so our buffer size can be easily modified
            if(dataBufferIndex==DATABUFFERSIZE){
                //Oops, our index is pointing to an array element outside our buffer.
                dataBufferIndex = 0;
                storeString = false;
                break;
            }
            
            if(incomingbyte==endChar){
                dataBuffer[dataBufferIndex] = 0; //null terminate the C string
                storeString = false;
                //Our data string is complete.  return true
                return true;
            } else {
                dataBuffer[dataBufferIndex++] = incomingbyte;
                dataBuffer[dataBufferIndex] = 0; //null terminate the C string
            }
        } else {
          dataBuffer[0] = 0;
          storeString = false;
          dataBufferIndex = 0;
        }
    }
   
    //We've read in all the available Serial data, and don't have a valid string yet, so return false
    return false;
}

void parseNmea(char *nmea, char *delimiters) {
  *gamePadCommand[0] = '\0';
  *gamePadCommand[1] = '\0';
  
  char *curPosition;
  curPosition = strtok(nmea,delimiters);
  if(curPosition==NULL) return;
  
  strcpy(gamePadCommand[0], curPosition);

  curPosition = strtok(NULL,delimiters);
  if(curPosition==NULL) return;
  
  strcpy(gamePadCommand[1], curPosition);
  
}

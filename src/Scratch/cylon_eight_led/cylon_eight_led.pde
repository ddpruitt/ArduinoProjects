
 
int ledPins[] = {2,3,4,5,6,7,8,9}; 
 
void setup()
{
  
  for(int i = 0; i < 8; i++){
      pinMode(ledPins[i],OUTPUT);
  }
}
 
 
void loop()
{
//   for(int i=0;i<10;i++)                          
     oneAfterAnotherLoop(); 

}
 
void oneAfterAnotherLoop(){
  int delayTime = 100; //the time (in milliseconds) to pause between LEDs
 
  for(int i = 0; i <= 7; i++){
    digitalWrite(ledPins[i], HIGH);  //Turns on LED #i each time this runs i
    delay(delayTime);                //gets one added to it so this will repeat 
    digitalWrite(ledPins[i], LOW);  //Turns on LED #i each time this runs i
  }                                  //8 times the first time i will = 0 the final
                                     //time i will equal 7;
 
  for(int i = 7; i >= 0; i--){  //same as above but rather than starting at 0 and counting up
    digitalWrite(ledPins[i], HIGH);  //Turns on LED #i each time this runs i
    delay(delayTime);                //gets one added to it so this will repeat 
    digitalWrite(ledPins[i], LOW);  //Turns on LED #i each time this runs i
  }                                  //8 times the first time i will = 7 the final
                                     //time it will equal 0
                                     
                                     
}



void inAndOut(){
  int delayTime = 100; //the time (in milliseconds) to pause between LEDs
                       //make smaller for quicker switching and larger for slower
  
  //runs the LEDs out from the middle
  for(int i = 0; i <= 3; i++){
    int offLED = i - 1;  //Calculate which LED was turned on last time through
    if(i == 0) {         //for i = 1 to 7 this is i minus 1 (i.e. if i = 2 we will
      offLED = 3;        //turn on LED 2 and off LED 1)
    }                    //however if i = 0 we don't want to turn of led -1 (doesn't exist)
                         //instead we turn off LED 7, (looping around)
    int onLED1 = 3 - i;       //this is the first LED to go on ie. LED #3 when i = 0 and LED 
                             //#0 when i = 3 
    int onLED2 = 4 + i;       //this is the first LED to go on ie. LED #4 when i = 0 and LED 
                             //#7 when i = 3 
    int offLED1 = 3 - offLED; //turns off the LED we turned on last time
    int offLED2 = 4 + offLED; //turns off the LED we turned on last time
    
    digitalWrite(ledPins[onLED1], HIGH);
    digitalWrite(ledPins[onLED2], HIGH);    
    digitalWrite(ledPins[offLED1], LOW);    
    digitalWrite(ledPins[offLED2], LOW);        
    delay(delayTime);
  }
 
  //runs the LEDs into the middle
  for(int i = 3; i >= 0; i--){
    int offLED = i + 1;  //Calculate which LED was turned on last time through
    if(i == 3) {         //for i = 1 to 7 this is i minus 1 (i.e. if i = 2 we will
      offLED = 0;        //turn on LED 2 and off LED 1)
    }                    //however if i = 0 we don't want to turn of led -1 (doesn't exist)
                         //instead we turn off LED 7, (looping around)
    int onLED1 = 3 - i;       //this is the first LED to go on ie. LED #3 when i = 0 and LED 
                             //#0 when i = 3 
    int onLED2 = 4 + i;       //this is the first LED to go on ie. LED #4 when i = 0 and LED 
                             //#7 when i = 3 
    int offLED1 = 3 - offLED; //turns off the LED we turned on last time
    int offLED2 = 4 + offLED; //turns off the LED we turned on last time
    
    digitalWrite(ledPins[onLED1], HIGH);
    digitalWrite(ledPins[onLED2], HIGH);    
    digitalWrite(ledPins[offLED1], LOW);    
    digitalWrite(ledPins[offLED2], LOW);        
    delay(delayTime);
  }
}


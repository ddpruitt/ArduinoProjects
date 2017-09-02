
//buffer size for NMEA compliant GPS string
//For Razor, set value to 17 instead
#define DATABUFFERSIZE      80
char dataBuffer[DATABUFFERSIZE+1]; //Add 1 for NULL terminator
byte dataBufferIndex = 0;

char startChar = '$'; // or '!', or whatever your start character is
char endChar = '\r';
boolean storeString = false; //This will be our flag to put the data in our buffer

char delimiters[] = "$: ;";
char gamePadCommand[2][DATABUFFERSIZE+1];

void setup() {
  Serial.begin(9600);
  Serial.flush();
  
  Serial1.begin(9600);
  Serial1.flush();  

  Serial.println("Setup Complete");
}

void loop() {

  if(getSerialString()){
    parseNmea(dataBuffer, delimiters);
    if(strcmp(gamePadCommand[0],"BTN")==0) Serial.println(gamePadCommand[1]);
    //else Serial.println(gamePadCommand[0]);
  } 
}

boolean getSerialString(){
    static byte dataBufferIndex = 0;
    while(Serial1.available()>0){
        char incomingbyte = Serial1.read();
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
                break;
            }
            
            if(incomingbyte==endChar){
                dataBuffer[dataBufferIndex] = 0; //null terminate the C string
                //Our data string is complete.  return true
                return true;
            } else {
                dataBuffer[dataBufferIndex++] = incomingbyte;
                dataBuffer[dataBufferIndex] = 0; //null terminate the C string
            }
        } else {
        }
    }
   
    //We've read in all the available Serial data, and don't have a valid string yet, so return false
    return false;
}

void printNmeaType(char *nmea, const char *delimiters) {
    char *curPosition;
    curPosition = strtok(nmea, delimiters);

    while(curPosition!=NULL){
        printf(curPosition);
        printf("\n");
        curPosition = strtok(NULL, delimiters);
    }
    printf("\n-----\n");
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

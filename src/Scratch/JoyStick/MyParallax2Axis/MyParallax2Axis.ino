
int _upDown = 0;
int _leftRight = 0;

int _upDownPort = 0;
int _leftRightPort = 1;

void setup() 
{
  // setup serial - diagnostics - port
  Serial.begin(9600);
}

void loop()
{
  
  _upDown = analogRead(_upDownPort);
  _leftRight = analogRead(_leftRightPort);
  
  Serial.print(_upDown);
  Serial.print('\t');
  Serial.print(_leftRight);
  Serial.println();
  delay(100);
  
  
  
  
}

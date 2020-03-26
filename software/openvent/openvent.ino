

int STP = 10; // LED auf Digitalpin 10 verbunden
int DIR = 9; // LED auf Digitalpin 9 verbunden


void setup() {
  // put your setup code here, to run once:

  pinMode(STP, OUTPUT); // Setzt den Pin als output.
  pinMode(DIR, OUTPUT); // Setzt den Pin als output.
  
  Serial.begin(9600);
//Set STEP frequency:
  setAnalogWriteFrequency(STP,256); //7 Atmungen pro min
  //setAnalogWriteFrequency(STP,346); //10 Atmungen pro min
  //setAnalogWriteFrequency(STP,450); //13 Atmungen pro min
  analogWrite(STP, 50);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(DIR, HIGH); 
  delay(4167); //3084(20), 2372(25)
  digitalWrite(DIR, LOW);
  delay(4167); //3084(20), 2372(25)

  
}

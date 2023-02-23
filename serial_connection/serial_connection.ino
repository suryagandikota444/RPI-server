// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
}
void loop() {

  while (!Serial.available());
  int x = Serial.readString().toInt();

  if (x==1) {
    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int y = 0; y < 400; y++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(5000); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(5000); 
    }
    delay(1000); // One second delay
  } else if (x==2) {
    digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int y = 0; y < 2400; y++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(350); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(350); 
    }
    delay(1000); // One second delay
  }
}

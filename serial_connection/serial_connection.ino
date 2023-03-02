// Defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 

char currentLocation = 'A';
int currentIndex = 0;
int numOfPulses = 0;

void setup() 
{
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
}
void loop() 
{
  while (Serial.available())
  {
    String input = Serial.readString();                 //getting the input - "A1" or "A2" or "C7" or "B3"
    char targetLocation = input.charAt(0);              // Parsing the input for the letter - 'A' or 'B' or 'C'
    int targetIndex = String(input.charAt(1)).toInt();  // Parsing the input for the number - 0, 1, 2, 3, 4, 5, 6, 7
    //Serial.print(currentLocation == 'A');
    //Serial.print(targetIndex);
    //Serial.println(numOfPulses);
    if((currentLocation == 'A' || currentLocation == 'B') && (targetLocation == 'A' || targetLocation == 'B'))
    {
      numOfPulses = (targetIndex - currentIndex) * 50;
      Serial.print(numOfPulses);
      Serial.println("CurrentLoc = A or B and TargetLocation = A or B");
      
    }
    else if((currentLocation == 'A' || currentLocation == 'B') && (targetLocation == 'C'))
    {
      int positionC = targetIndex / 2;
      numOfPulses = (positionC - currentIndex) * 50;
      Serial.println(numOfPulses);
      Serial.println("CurrentLoc = A or B and TargetLocation = C");
      
    }
    else if((currentLocation == 'C') && (targetLocation == 'A' || targetLocation == 'B'))
    {
      int positionC = currentIndex / 2;
      numOfPulses = (positionC - targetIndex) * 50;
      
      Serial.println(numOfPulses + 200);
      Serial.println("CurrentLoc = C and TargetLocation = A or B");
      
    }
    else if(currentLocation == 'C' && targetLocation == 'C')
    {
      int positionC = targetIndex / 2;
      currentIndex = currentIndex / 2; 
      numOfPulses = (positionC - currentIndex) * 50;
      Serial.println(numOfPulses);
      Serial.println("CurrentLoc = C and TargetLocation = C");
      
    }
    else
    {
      //do something -> extra space as of rn
    }

    
    //Serial.print("second num");
    //Serial.print(numOfPulses);
    //Signal the motor now
    if(numOfPulses < 0)
    {
      numOfPulses = (-1) * numOfPulses;
    }
    digitalWrite(dirPin,HIGH);
    for(int y = 0; y < (numOfPulses); y++) 
    {
       digitalWrite(stepPin,HIGH); 
       delayMicroseconds(3000); 
       digitalWrite(stepPin,LOW); 
       delayMicroseconds(3000); 
    }
    numOfPulses = 0;
    delay(1000); //One second delay
    currentLocation = targetLocation; //Current position is now the old target position
    currentIndex = targetIndex;


  }
}

// defines pins numbers
//const int stepPin = 3; 
//const int dirPin = 4; 
//
//void setup() {
//  // Sets the two pins as Outputs
//  pinMode(stepPin,OUTPUT); 
//  pinMode(dirPin,OUTPUT);
//  Serial.begin(115200);
//  Serial.setTimeout(1);
//}
//void loop() {
//
//  while (!Serial.available());
//  int x = Serial.readString().toInt();
//
//  if (x==1) {
//    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
//    // Makes 200 pulses for making one full cycle rotation
//    for(int y = 0; y < 400; y++) {
//      digitalWrite(stepPin,HIGH); 
//      delayMicroseconds(3000); 
//      digitalWrite(stepPin,LOW); 
//      delayMicroseconds(3000); 
//    }
//    delay(1000); // One second delay
//  } else if (x==2) {
//    digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
//    // Makes 200 pulses for making one full cycle rotation
//    for(int y = 0; y < 600; y++) {
//      digitalWrite(stepPin,HIGH); 
//      delayMicroseconds(3000); 
//      digitalWrite(stepPin,LOW); 
//      delayMicroseconds(3000); 
//    }
//    delay(1000); // One second delay
//  }
//}

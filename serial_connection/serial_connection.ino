// Defines pins numbers
const int stepPin = 3;
const int dirPin = 4;

char currentLocation = 'A';
int currentIndex = 0;
int numOfPulses = 0;

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
}
void loop() {
  while (Serial.available()) {
    String input = Serial.readString();                                            //getting the input - "A1" or "A2"
    or "C7" or "B3" char targetLocation = input.charAt(0);                         // Parsing the input for the
    letter - 'A' or 'B' or 'C' int targetIndex = String(input.charAt(1)).toInt();  // Parsing theinput for the number - 0, 1, 2, 3, 4, 5, 6, 7
//Serial.print(currentLocation == 'A');
//Serial.print(targetIndex);
//Serial.println(numOfPulses);
if((currentLocation == 'A' || currentLocation == 'B') && (targetLocation == 'A' || targetLocation == 'B'))
{
  int temp = (targetIndex - currentIndex) * 50;
  if (temp < 0) {
    numOfPulses = temp + 200;
  } else {
    numOfPulses = temp;
  }
  //Serial.println("Before: CurrentLoc = A or B");
  //Serial.println(numOfPulses);
  //Serial.println("Num of Pulses: " + numOfPulses);
  //Serial.println("Now: CurrentLoc = A or B");

  Serial.println("(Before) Location: " + String(currentLocation) + "" + String(currentIndex));
  Serial.println("(After) Location: " + input);
  Serial.println("Steps taken: " + String(numOfPulses));
  Serial.println();
}
else if ((currentLocation == 'A' || currentLocation == 'B') && (targetLocation == 'C')) {
  int positionC = targetIndex / 2;
  int temp = (positionC - currentIndex) * 50;
  if (temp < 0) {
    numOfPulses = temp + 200;
  } else {
    numOfPulses = temp;
  }
  // Serial.println("Before: CurrentLoc = A or B");
  // Serial.println(numOfPulses);
  // //Serial.println("Num of Pulses: " + numOfPulses);
  // Serial.println("Now: CurrentLoc = C");
  // Serial.println();
  Serial.println("(Before) Location: " + String(currentLocation) + "" + String(currentIndex));
  Serial.println("(After) Location: " + input);
  Serial.println("Steps taken: " + String(numOfPulses));
  Serial.println();
}
else if ((currentLocation == 'C') && (targetLocation == 'A' || targetLocation == 'B')) {
  int positionC = currentIndex / 2;
  int temp = (targetIndex - positionC) * 50;
  if (temp < 0) {
    numOfPulses = temp + 200;
  } else {
    numOfPulses = temp;
  }
  // Serial.println("Before: CurrentLoc = C");
  // Serial.println(numOfPulses);
  // //Serial.println("Num of Pulses: " + numOfPulses);
  // Serial.println("Now: CurrentLoc = A or B");
  // Serial.println();
  Serial.println("(Before) Location: " + String(currentLocation) + "" + String(currentIndex));
  Serial.println("(After) Location: " + input);
  Serial.println("Steps taken: " + String(numOfPulses));
  Serial.println();
}
else if (currentLocation == 'C' && targetLocation == 'C') {
  int positionC = targetIndex / 2;
  currentIndex = currentIndex / 2;
  int temp = (positionC - currentIndex) * 50;

  if (temp < 0) {
    numOfPulses = temp + 200;
  } else {
    numOfPulses = temp;
  }
  // Serial.println("Before: CurrentLoc = C");
  // Serial.println(numOfPulses);
  // //Serial.println("Num of Pulses: " + numOfPulses);
  // Serial.println("Now: CurrentLoc = C");
  // Serial.println();
  Serial.println("(Before) Location: " + String(currentLocation) + "" + String(currentIndex));
  Serial.println("(After) Location: " + input);
  Serial.println("Steps taken: " + String(numOfPulses));
  Serial.println();
}

//Serial.print("second num");
//Serial.print(numOfPulses);
//Signal the motor now
digitalWrite(dirPin, HIGH);
for (int y = 0; y < (numOfPulses); y++) {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(3000);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(3000);
}
numOfPulses = 0;
delay(1000);                       //One second delay
currentLocation = targetLocation;  //Current position is now the old target position
  currentIndex = targetIndex;
  }
}

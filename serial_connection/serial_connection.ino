// Defines pins numbers
#include "FastLED.h"
#include <pixeltypes.h>

//Defining the LED pins
#define LED_pin 10
#define NUM_LEDs 21

const int stepPin = 3;
const int dirPin = 4;

char currentLocation = 'A';
int currentIndex = 0;
int numOfPulses = 0;

CRGB LedStrip[NUM_LEDs];



void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);
  FastLED.addLeds<WS2812B, LED_pin, GRB>(LedStrip,NUM_LEDs);
}
void loop() {
  while (Serial.available()) {
    String input = Serial.readString();                                            //getting the input - "A1" or "A2" or "C7" or "B3" 
    char targetLocation = input.charAt(0);                         // Parsing the input for theletter - 'A' or 'B' or 'C' 
    int targetIndex = String(input.charAt(1)).toInt();  // Parsing theinput for the number - 0, 1, 2, 3, 4, 5, 6, 7
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

   if(targetLocation == 'A') {
        //First Set of LEDS light up
        for(int LEDIt = 0; LEDIt<20; LEDIt++){
          if(LEDIt<7)
          {
            LedStrip[LEDIt]=CRGB::DarkOrchid;
          }

          else
          {
            LedStrip[LEDIt]=CRGB::Black;
          }
          
        }
        FastLED.show();    
        delay(10);  
      }
      if(targetLocation == 'B') {
        //First Set of LEDS light up
        for(int LEDIt = 0; LEDIt<21; LEDIt++){
          if(LEDIt>7 || LEDIt<14)
          {
            LedStrip[LEDIt]=CRGB::DarkOrchid;
          }

          else
          {
            LedStrip[LEDIt]=CRGB::Black;
          }
        }
        FastLED.show();     
        delay(10); 
      }   
      
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

   if(targetLocation == 'C') {
        //First Set of LEDS light up
        
          for(int LEDIt = 0; LEDIt<21; LEDIt++){
          if(LEDIt>14)
          {
            LedStrip[LEDIt]=CRGB::DarkOrchid;
          }

          else
          {
            LedStrip[LEDIt]=CRGB::Black;
          }
        }
        }
        FastLED.show();     
        delay(10); 
        

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

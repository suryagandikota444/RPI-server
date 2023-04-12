#include "FastLED.h"
#include <pixeltypes.h>

//Defining Pins
const int hallPin = 2;
const int stepPin = 3;
const int dirPin = 4;

//Start Location = A0
char currentLocation = 'A';
int currentIndex = 0;

//Moves the motor -> 0 Pulses initially
int numOfPulses = 0;
int tempPulses = 0;
int ledStart = 0;
int ledEnd = 0;

//Defining Pre-processor Directives
#define LED_pin1 12
#define LED_pin2 9
#define NUM_LEDs 21
#define BRIGHTNESS 130
#define HUE 185 //Value between 1 and 360 [RED =0,Green =120, Blue =240]
#define SAT 255 //KEEP at 255
#define VAL 255 //KEEP at 255

//Two LED Strips
CRGB LedStrip1[NUM_LEDs];
CRGB LedStrip2[NUM_LEDs];

void setup() 
{
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  
  //HALL EFFECT SENSOR CODE (Homing)
  pinMode(A2, INPUT);
  while (analogRead(A2) > 100)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);
  } 
  
  //Establishing Connection with the Arduino
  Serial.begin(115200);
  Serial.setTimeout(1);

  //FastLED Library
  FastLED.addLeds<WS2812B, LED_pin1, GRB>(LedStrip1,NUM_LEDs);
  FastLED.addLeds<WS2812B, LED_pin2, GRB>(LedStrip2,NUM_LEDs);
  FastLED.setBrightness(BRIGHTNESS);

  //Defining the LED Color
  CHSV LEDColor = CHSV(HUE, SAT, VAL);
  for(int x=0; x<7; x++)
  {
    LedStrip1[x]=LEDColor;
    LedStrip2[x]=LEDColor;
  }
  FastLED.show();    
  delay(10);  
}
void loop() 
{
  //Defining LED Color
  CHSV LEDColor = CHSV(HUE, SAT, VAL);
  
  while (Serial.available()) 
  {
    //Getting the input: "A1" or "A2", or "C6" respectively
    String input = Serial.readString();

    //Parsing the input
    //targetLocation = 'A' or 'B' or 'C'
    //targetIndex = 0 or 1 or 2 or 3 etc                                     
    char targetLocation = input.charAt(0);                        
    int targetIndex = String(input.charAt(1)).toInt(); 

    

    if((currentLocation == 'A' || currentLocation == 'B'))
    {
        switch(targetLocation)
        {
            case 'A':
                tempPulses = (targetIndex - currentIndex) * 50;
                ledStart = 0;
                ledEnd = 7;
                break;
            case 'B':
                tempPulses = (targetIndex - currentIndex) * 50;
                ledStart = 7;
                ledEnd = 14
                break;
            case 'C':
                tempPulses = ((targetIndex / 2) - currentIndex) * 50;
                ledStart = 14;
                ledEnd = 21
                break;
        }
    }
    else
    {
        switch(targetLocation)
        {
            case 'A':
                tempPulses = (targetIndex - (currentIndex / 2)) * 50;
                ledStart = 0;
                ledEnd = 7;
                break;
            case 'B':
                tempPulses = (targetIndex - (currentIndex / 2)) * 50;
                ledStart = 7;
                ledEnd = 14;
                break;
            case 'C':
                tempPulses = ((targetIndex / 2) - (currentIndex / 2)) * 50;
                ledStart = 14;
                ledEnd = 21
                break;
        }
    }

    //Adjusting for negative numbers and 3:1 Gear Ratio
    if(tempPulses < 0)
    {
        numOfPulses = (tempPulses + 200) * 3;
    }
    else
    {
        numOfPulses = tempPulses * 3;
    }
    
    //Signal the motor now
    digitalWrite(dirPin, HIGH);
    for (int y = 0; y < (numOfPulses); y++) 
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(3000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(3000);
    }

    //Displaying the LEDs
    //First 2 For Loops -> Turn Off LEDs (Not in Use)
    //Last For Loop -> Turn On LEDs (In Use)
    for(int LEDIt = 0; LEDIt < ledStart; LEDIt++)
    {
        LedStrip1[LEDIt] = CRGB::Black;;
        LedStrip2[LEDIt] = CRGB::Black;;
    }
    for(int LEDIt = ledEnd; LEDIt < 21; LEDIt++)
    {
        LedStrip1[LEDIt] = CRGB::Black;;
        LedStrip2[LEDIt] = CRGB::Black;;
    }
    for(int LEDIt = ledStart; LEDIt < ledEnd; LEDIt++)
    {
        LedStrip1[LEDIt] = LEDColor;
        LedStrip2[LEDIt] = LEDColor;
    }
    FastLED.show();    
    delay(10);

    //Reinitializing the Variables 
    numOfPulses = 0;
    tempPulses = 0;

    //One second delay
    delay(1000);                       

    //New Current Location is Now the Old Target Location
    currentLocation = targetLocation;  
    currentIndex = targetIndex;
  }
}

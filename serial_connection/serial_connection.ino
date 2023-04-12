// Defines pins numbers
#include "FastLED.h"
#include <pixeltypes.h>

//Defining the LED pins


// HALL EFFECT SENSOR CODE - TESTING
const int hallPin = 2;

const int stepPin = 3;
const int dirPin = 4;

char currentLocation = 'A';
int currentIndex = 0;
int numOfPulses = 0;



//Defining LED Items

#define LED_pin1 12
#define LED_pin2 9
#define NUM_LEDs 21
#define BRIGHTNESS 130
#define HUE 185 //Value between 1 and 360 [RED =0,Green =120, Blue =240]
#define SAT 255 //KEEP at 255
#define VAL 255 //KEEP at 255

CRGB LedStrip1[NUM_LEDs];
CRGB LedStrip2[NUM_LEDs];

void setup() 
{
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  
  //HALL EFFECT SENSOR CODE - TESTING
  pinMode(A2, INPUT);
  
  while (analogRead(A2) > 100)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);
  } 
  
  Serial.begin(115200);
  Serial.setTimeout(1);
  FastLED.addLeds<WS2812B, LED_pin1, GRB>(LedStrip1,NUM_LEDs);
  FastLED.addLeds<WS2812B, LED_pin2, GRB>(LedStrip2,NUM_LEDs);
  FastLED.setBrightness(BRIGHTNESS);

  //Defining LED Color
  CHSV LEDColor = CHSV(HUE, SAT, VAL);
  for(int x=0; x<7; x++)
  {
    LedStrip1[x]=LEDColor;
    LedStrip2[x]=LEDColor;
  }
  FastLED.show();    
  delay(10);  

  //HALL EFFECT TESTER
  /*while (true)
   {
      int x = analogRead(A2);
        Serial.print("Analog Sensor Reading: ");
      Serial.println(x);        
      
      delay(100);
   }*/

  Serial.println(1);


}
void loop() 
{
  //Defining LED Color

  
  CHSV LEDColor = CHSV(HUE, SAT, VAL);

//  Serial.println(1);
  
  while (Serial.available()) 
  {
    
    String input = Serial.readString();                                            //getting the input - "A1" or "A2" or "C7" or "B3" 
    char targetLocation = input.charAt(0);                         // Parsing the input for theletter - 'A' or 'B' or 'C' 
    int targetIndex = String(input.charAt(1)).toInt();  // Parsing theinput for the number - 0, 1, 2, 3, 4, 5, 6, 7
    Serial.println(input);
    if((currentLocation == 'A' || currentLocation == 'B') && (targetLocation == 'A' || targetLocation == 'B'))
    {
      int temp = (targetIndex - currentIndex) * 50;
      if (temp < 0) 
      {
        int temp2 = temp + 200;
        numOfPulses = temp2 * 3;
      } else 
      {
        numOfPulses = temp * 3;
      }


      if(targetLocation == 'A') 
      {
        //First Set of LEDS light up
        for(int LEDIt = 0; LEDIt<21; LEDIt++)
        {
          if(LEDIt<7)
          {
            LedStrip1[LEDIt] = LEDColor;
            LedStrip2[LEDIt] = LEDColor;
          }
          else
          {
            LedStrip1[LEDIt]= CRGB::Black;
            LedStrip2[LEDIt]= CRGB::Black;
          }   
        }
        FastLED.show();    
        delay(10);  
      }
      else if(targetLocation == 'B') 
      {
        //First Set of LEDS light up
        for(int LEDIt = 0; LEDIt<21; LEDIt++)
        {
          if(LEDIt>=7 && LEDIt<14)
          {
            LedStrip1[LEDIt] = LEDColor;
            LedStrip2[LEDIt] = LEDColor;
          }
          else
          {
            LedStrip1[LEDIt]=CRGB::Black;
            LedStrip2[LEDIt]=CRGB::Black;
          }
        }
        FastLED.show();    
        delay(10);  
      }

      // Serial.println("(Before) Location: " + String(currentLocation) + "" + String(currentIndex));
      // Serial.println("(After) Location: " + input);
      // Serial.println("Steps taken: " + String(numOfPulses));
      // Serial.println();
    }
    else if ((currentLocation == 'A' || currentLocation == 'B') && (targetLocation == 'C')) 
    {
      int positionC = targetIndex / 2;
      int temp = (positionC - currentIndex) * 50;
      if (temp < 0) 
      {
        int temp2 = temp + 200;
        numOfPulses = temp2 * 3;
      } 
      else 
      {
        numOfPulses = temp * 3;
      }

      if(targetLocation == 'C') 
      {
        //First Set of LEDS light up    
        for(int LEDIt = 0; LEDIt<21; LEDIt++)
        {
          if(LEDIt>=14)
          {
            LedStrip1[LEDIt] = LEDColor;
            LedStrip2[LEDIt] = LEDColor;
          }
          else
          {
            LedStrip1[LEDIt]=CRGB::Black;
            LedStrip2[LEDIt]=CRGB::Black;
          }
        }
      
        FastLED.show();     
        delay(10);
      }
      // Serial.println("(Before) Location: " + String(currentLocation) + "" + String(currentIndex));
      // Serial.println("(After) Location: " + input);
      // Serial.println("Steps taken: " + String(numOfPulses));
      // Serial.println();
    }
    else if ((currentLocation == 'C') && (targetLocation == 'A' || targetLocation == 'B')) 
    {
      int positionC = currentIndex / 2;
      int temp = (targetIndex - positionC) * 50;
      if (temp < 0) 
      {
        int temp2 = temp + 200;
        numOfPulses = temp2 * 3;
      } 
      else 
      {
        numOfPulses = temp * 3;
      }

      if(targetLocation == 'A') 
      {
        //First Set of LEDS light up
        for(int LEDIt = 0; LEDIt<21; LEDIt++)
        {
          if(LEDIt<=7)
          {
            LedStrip1[LEDIt] = LEDColor;
            LedStrip2[LEDIt] = LEDColor;
          }
          else
          {
            LedStrip1[LEDIt]=CRGB::Black;
            LedStrip2[LEDIt]=CRGB::Black;
          }   
        }
        FastLED.show();    
        delay(10);  
      }
      else if(targetLocation == 'B') 
      {
        //First Set of LEDS light up
        for(int LEDIt = 0; LEDIt<21; LEDIt++)
        {
          if(LEDIt>=7 && LEDIt<14)
          {
            LedStrip1[LEDIt] = LEDColor;
            LedStrip2[LEDIt] = LEDColor;
          }
          else
          {
            LedStrip1[LEDIt]=CRGB::Black;
            LedStrip2[LEDIt]=CRGB::Black;
          }
        }
        FastLED.show();    
        delay(10);  
      }
          
      // Serial.println("(Before) Location: " + String(currentLocation) + "" + String(currentIndex));
      // Serial.println("(After) Location: " + input);
      // Serial.println("Steps taken: " + String(numOfPulses));
      // Serial.println();
    }
    else if (currentLocation == 'C' && targetLocation == 'C') 
    {
      int positionC = targetIndex / 2;
      currentIndex = currentIndex / 2;
      int temp = (positionC - currentIndex) * 50;

      if (temp < 0) 
      {
        int temp2 = temp + 200;
        numOfPulses = temp2 * 3;
      } else 
      {
        numOfPulses = temp * 3;
      }
      if(targetLocation == 'C') 
      {
        //First Set of LEDS light up    
        for(int LEDIt = 0; LEDIt<21; LEDIt++)
        {
          if(LEDIt>=14)
          {
            LedStrip1[LEDIt]= LEDColor;
            LedStrip2[LEDIt]= LEDColor;
          }
          else
          {
            LedStrip1[LEDIt]=CRGB::Black;
            LedStrip2[LEDIt]=CRGB::Black;
          }
        }
        FastLED.show();     
        delay(10);
      }
      // Serial.println("(Before) Location: " + String(currentLocation) + "" + String(currentIndex));
      // Serial.println("(After) Location: " + input);
      // Serial.println("Steps taken: " + String(numOfPulses));
      // Serial.println();

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
    numOfPulses = 0;
    delay(1000);                       //One second delay
    currentLocation = targetLocation;  //Current position is now the old target position
    currentIndex = targetIndex;

    Serial.println(1);
  }
}

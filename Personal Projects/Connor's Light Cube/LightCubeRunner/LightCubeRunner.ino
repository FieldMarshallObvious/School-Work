/*
  Simple program to cycle through different
  sets of colors on the LED ring when any 
  of the four buttons are pressed
*/

#include <Adafruit_NeoPixel.h>

# define NUMPIXELS 16

// All button pins
# define BUTTONPINSET1 7
# define BUTTONPINSET2 8

// All LED pins
# define RGBRINPIN 2
# define WHITESQUAREPIN 3

Adafruit_NeoPixel pixels(NUMPIXELS, RGBRINPIN, NEO_GRB + NEO_KHZ800);


// Handle debouncing
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1;
int buttonState;

bool colorsInitialized = false;

int colorSet1[4][3] = { {30, 203, 225}, {150, 30, 225}, {225, 52, 30}, {106, 225, 30}};
int curPixelColorIndex[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1, -1, -1, -1, -1, -1, -1};
int counter = 0;

void setup() {
  Serial.begin(9600);
  // setup button pins
  pinMode(BUTTONPINSET1, INPUT);
  pinMode(BUTTONPINSET2, INPUT);

  // setup led pins
  pinMode(RGBRINPIN, OUTPUT);
  pinMode(WHITESQUAREPIN, OUTPUT);

  // initialize adafruit neopixels
  pixels.begin();
}

void loop() {
  int reading = digitalRead(BUTTONPINSET1);
  //int buttonState2 = digitalRead(BUTTONPINSET2);

  // If the siwtch changed due to noise
  // log the debounce time
  if( reading != lastButtonState )
  {
    lastDebounceTime = millis();
  }

  if( (millis() - lastDebounceTime) > debounceDelay )
  {
    if( reading != buttonState )
    {
      buttonState = reading;      
      if( buttonState == 0 )
      {
        Serial.println("Button pressed!");
        colorsInitialized = false;
        resetCurColorArray();
      }
      else 
        Serial.println("Button is not pressed!");  
    }
  }  
  
  pixels.clear();
  pixels.setBrightness(10);

  // Do not reinitialize the 
  // colors if they are not initialized
  if (!colorsInitialized)
    initializeColors(colorSet1);
  else
    cycleColors(colorSet1, curPixelColorIndex, counter); 
  
  if ( counter < 4 )
  {
    counter++;
  }
  else 
  {
    counter = 0;
  }
  
  lastButtonState = reading;

}

// Reset all items in the color array

void resetCurColorArray() {
  for( int i = 0; i < 16; i++ )
  {
    curPixelColorIndex[i] = -1;    
  }
}

void initializeColors(int colorSet[][3]) {
  for( int i = 0; i < 16; i++ )
  {
    // If the current index is not initialized
    // initialize it
    if( curPixelColorIndex[i] == -1 )
    {
      // Set each of the pixel blocks
      // to their corresponding starting color
      if ( i < 4 )
      {
        curPixelColorIndex[i] = 0;      
      }
      else if ( i < 8 )
      {
        curPixelColorIndex[i] = 1;    
        digitalWrite(WHITESQUAREPIN, HIGH);
  
      }
      else if ( i < 12 )
      {
        curPixelColorIndex[i] = 2;      
      }
      else if ( i < 16 )
      {
        curPixelColorIndex[i] = 3;      
      }
    }

    /*Serial.print("Pixel array is ");
    Serial.print(curPixelColorIndex[i], DEC);
    Serial.print(" @ ");
    Serial.println(i, DEC);*/
    
    // Set the current pixel 
    pixels.setPixelColor(i, pixels.Color(colorSet[curPixelColorIndex[i]][0], colorSet[curPixelColorIndex[i]][1], colorSet[curPixelColorIndex[i]][2]));
  }
  pixels.show();

  Serial.println("Showing pixels!");

  delay(250);

  colorsInitialized = true;
}

// Change each of the four leds to their next
// neighboor
void cycleColors(int colorSet[][3], int curPixelColorIndex[], int counter) 
{
  changeItem(counter, curPixelColorIndex);
  changeItem(counter + 4, curPixelColorIndex);
  changeItem(counter + 8, curPixelColorIndex);
  changeItem(counter + 12, curPixelColorIndex);

  for( int i = 0; i < 16; i++ )
  {
    pixels.setPixelColor(i, pixels.Color(colorSet[curPixelColorIndex[i]][0], colorSet[curPixelColorIndex[i]][1], colorSet[curPixelColorIndex[i]][2]));
  }
  pixels.show();
  delay(250);
} 

// Swap the desired item with it's neighboor
void changeItem(int counter,  int * curPixelColorIndex) {
  // If there is another value after this one
  // set this value to the next value
  if( counter < 15 )
  {
    curPixelColorIndex[counter] = curPixelColorIndex[counter + 1];    
  }
  // Otherwise set it to the first 
  // item in the array
  else 
  {
    curPixelColorIndex[counter] = curPixelColorIndex[0];
  }
}



/*
  Simple program to cycle through different
  sets of colors on the LED ring when any 
  of the four buttons are pressed
*/

#include <Adafruit_NeoPixel.h>

# define NUMPIXELS 16

# define PIXELBRIGHTNESS 255

# define COLORSETS 2

// All button pins
# define BUTTONPINSET1 7
# define BUTTONPINSET2 8

// All LED pins
# define RGBRINPIN 2
# define WHITESQUAREPIN 3

// Counter for sleep
# define SLEEPINCREMENT 5

// All delay time values
# define STANDARDTIME 50
# define DEBUGTIME 100

// Program flags
# define DISABLE_BUTTONS false
# define DEBUG false 

Adafruit_NeoPixel pixels(NUMPIXELS, RGBRINPIN, NEO_GRB + NEO_KHZ800);


// Handle debouncing
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonState;
int buttonPressedCounter = 0; // Keep track of where the user is in the cycle

bool colorsInitialized = true;
bool colorActive = false;
bool dimmingRing = false;
bool processedInput = false;

// Manage the ring light colors
int colorSet[4][3] = { {30, 203, 225}, {150, 30, 225}, {225, 52, 30}, {106, 225, 30}};
int colorSet1[4][3] = { {30, 203, 225}, {150, 30, 225}, {225, 52, 30}, {106, 225, 30}};
int colorSet2[4][3] = { {30, 225, 72}, {225, 169, 30}, {225, 30, 184}, {30, 86, 225}};
int curPixelColorIndex[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1, -1, -1, -1, -1, -1, -1};
int counter = 0;
int sleepCounter = 10;
int colorSetCounter = 0;
int finalBrightnessValue = 0;

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
  pixels.clear();

  int reading = digitalRead(BUTTONPINSET1);
  //int buttonState2 = digitalRead(BUTTONPINSET2);


  // If the siwtch changed due to noise
  // log the debounce time
  if( reading != lastButtonState )
  {
    lastDebounceTime = millis();
    processedInput = false;
  }

  if( (millis() - lastDebounceTime) > debounceDelay )
  {
    if( reading != buttonState & processedInput )
    {
      buttonState = reading;      
      if( buttonState == 0 && !DISABLE_BUTTONS )
      {
        Serial.println("Button pressed!");
        // Change the cycle to next value
        if (buttonPressedCounter < 3)
          buttonPressedCounter++;
        else
          buttonPressedCounter = 0;
      }
      else 
        Serial.println("Button is not pressed!");  

      // Determine how to switch the device
      // based on what state we are currently in
      switch (buttonPressedCounter) {
        case 0:
          colorsInitialized = false;
          colorActive = true;
          resetCurColorArray();
          changeSquareState(true);
          break;
        case 1:
          dimmingRing = true;
          finalBrightnessValue = 85;
          sleepCounter = SLEEPINCREMENT ;
          break;
        case 2:
          finalBrightnessValue = 175;
          dimmingRing = true;
          sleepCounter = SLEEPINCREMENT + 5;
          break;
        case 3:
          dimmingRing = true;
          finalBrightnessValue = 255;
          sleepCounter = SLEEPINCREMENT + 5;
          changeSquareState(false);

      }
    }
  }  

  // Do not reinitialize the 
  // colors if they are not initialized
  if (!colorsInitialized)
    initializeColors(colorSet);

  else if ( colorActive )
    cycleColors(colorSet, curPixelColorIndex, counter, PIXELBRIGHTNESS - sleepCounter ); 
  
  if ( dimmingRing )
  {
    sleepCounter += SLEEPINCREMENT;

    Serial.print("sleep counter ");
    Serial.println(sleepCounter);
    Serial.print("final brightness value ");
    Serial.println(finalBrightnessValue);
    Serial.print("Cur pixel value ");
    Serial.println(( PIXELBRIGHTNESS - sleepCounter ));

    
    // Once the sleep counter has reached it's desired
    // desintation, reset the flags  
    if ( sleepCounter >= finalBrightnessValue )
    {
      dimmingRing = false;

      // If the ring is supposed to be disabled, 
      // set the pixels to zero
      if( finalBrightnessValue = 255 )
      {
        colorActive = false;
        pixels.setBrightness(0);
        pixels.show();
        sleepCounter = 0;
      }

    }

  }
  
  if ( counter < 4 )
  {
    counter++;
  }
  else 
  {
    counter = 0;
  }
  
  lastButtonState = reading;

  delay(DEBUG ? DEBUGTIME : STANDARDTIME);
    
  processedInput = true;
}

// Reset all items in the color array
void resetCurColorArray() {
  for( int i = 0; i < 16; i++ )
  {
    curPixelColorIndex[i] = -1;    
  }
}

// Change the parent color set to the new color set
void changeColorSet( int newColorSet[4][3])
{
  // Change current color set to the new color set values
  colorSet[0][0] = newColorSet[0][0];
  colorSet[0][1] = newColorSet[0][1];
  colorSet[0][2] = newColorSet[0][2];

  colorSet[1][0] = newColorSet[1][2];
  colorSet[1][1] = newColorSet[1][2];
  colorSet[1][2] = newColorSet[1][2];

  colorSet[1][0] = newColorSet[2][2];
  colorSet[1][1] = newColorSet[2][2];
  colorSet[1][2] = newColorSet[2][2];

}

// Change the square state to on if
// true, otherwise turn to false
void changeSquareState(bool state) {
  if (state)
    digitalWrite(WHITESQUAREPIN, HIGH);
  else 
    digitalWrite(WHITESQUAREPIN, LOW);
}

// Inititalize all colors in the color array to their
// starting values
void initializeColors(int colorSet[][3]) {
  pixels.setBrightness(PIXELBRIGHTNESS);
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

    // Only print these items if debug is true 
    if (DEBUG) {
      Serial.print("Pixel array is ");
      Serial.print(curPixelColorIndex[i], DEC);
      Serial.print(" @ ");
      Serial.println(i, DEC);
    }
    
    // Set the current pixel 
    pixels.setPixelColor(i, pixels.Color(colorSet[curPixelColorIndex[i]][0], colorSet[curPixelColorIndex[i]][1], colorSet[curPixelColorIndex[i]][2]));
  }
  pixels.show();

  Serial.println("Showing pixels!");


  colorsInitialized = true;
}

// Change each of the four leds to their next
// neighboor
void cycleColors(int colorSet[][3], int curPixelColorIndex[], int counter, int brightness) 
{
  changeItem(counter, curPixelColorIndex);
  changeItem(counter + 4, curPixelColorIndex);
  changeItem(counter + 8, curPixelColorIndex);
  changeItem(counter + 12, curPixelColorIndex);

  /*Serial.print("Pixel brightness");
  Serial.println(brightness);*/

  for( int i = 0; i < 16; i++ )
  {
    setPixelColor(i, colorSet[curPixelColorIndex[i]][0], colorSet[curPixelColorIndex[i]][1], colorSet[curPixelColorIndex[i]][2], brightness);
  }
  pixels.show();
} 

// Set the pixel color based on brightness
void setPixelColor( uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint16_t brightness) {
	pixels.setPixelColor(n, ((brightness*r)/255) , ((brightness*g)/255), ((brightness*b)/255));
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



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
# define INITIALSLEEPCHANGE 0
# define WAKEINCREMENT -5 

// Change the rate at which colors chante
# define COLORRATE 1
# define MAXSTEPS 255
# define epsilon 0.05

// All delay time values
# define STANDARDTIME 100
# define DEBUGTIME 100

// Debug flags 
# define DISABLE_BUTTONS false
# define DEBUG false 
# define VERBOSEOUTPUT false 
# define SWITCHOUTPUT true
# define WAKINGOUT false
# define SLEEPINGOUT false
# define INITOUT false

Adafruit_NeoPixel pixels(NUMPIXELS, RGBRINPIN, NEO_GRB + NEO_KHZ800);

void initializeColors(int colorSet[][3], int colorSetCounter, int brightness = 0);


// Handle debouncing
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonState;
int buttonPressedCounter = -1; // Keep track of where the user is in the cycle

bool colorsInitialized = true;
bool colorActive = false;
bool dimmingRing = false;
bool wakingRing = false;
bool processedInput = true;
bool swappingColor = false;
bool reachedDest = false;
bool switchColorDirection = false;

// Manage the ring light colors
int colorSet[4][3] = { {75, 100, 225}, {100, 125, 225}, {125, 150, 30}, {150, 175, 255}};
int curPixelColorIndex[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1, -1, -1, -1, -1, -1, -1};
int counter = 0;
int sleepCounter = 255;
int colorChangeCounter = 0;
int colorSetCounter = 1;
int finalBrightnessValue = 0;
float newR = 30;
float newG = 203;
float newB = 255;

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
  //pixels.clear();

  int reading = digitalRead(BUTTONPINSET1);
  //int buttonState2 = digitalRead(BUTTONPINSET2);


  if( processedInput )
  {

    buttonState = reading;      
    if( buttonState == 1 && !DISABLE_BUTTONS )
    {
      processedInput = false;

      Serial.println("Button pressed!");
      // Change the cycle to next value
      if (buttonPressedCounter < 5)
      {
        buttonPressedCounter++;
      }
      else
      {
        buttonPressedCounter = 0;
      }

      // Determine how to switch the device
      // based on what state we are currently in
      switch (buttonPressedCounter) {
        case 0:
          colorsInitialized = false;
          wakingRing = true;
          colorActive = true;
          sleepCounter = 255;
          resetCurColorArray();
          changeSquareState(true);
          if( SWITCHOUTPUT || VERBOSEOUTPUT ) 
          { 
            Serial.println("Using button 0");
            Serial.print("sleep counter ");
            Serial.println(sleepCounter);
          }
          break;
        case 1:
          colorsInitialized = true;
          wakingRing = false;
          dimmingRing = true;
          finalBrightnessValue = 175;
          sleepCounter = 0;
          if( SWITCHOUTPUT || VERBOSEOUTPUT )
          { 
            Serial.println("Using button 1");
            Serial.print("sleep counter ");
            Serial.println(sleepCounter);
          }
          break;
        case 2:
          finalBrightnessValue = 85;
          dimmingRing = true;
          wakingRing = false;
          sleepCounter += SLEEPINCREMENT + INITIALSLEEPCHANGE;
          if( SWITCHOUTPUT || VERBOSEOUTPUT )
          { 
            Serial.println("Using button 2");
            Serial.print("sleep counter ");
            Serial.println(sleepCounter);
          }
          break;
        case 3:
          dimmingRing = true;
          wakingRing = false;
          finalBrightnessValue = 0;
          sleepCounter += SLEEPINCREMENT + INITIALSLEEPCHANGE;
          if( SWITCHOUTPUT || VERBOSEOUTPUT )
          {
            Serial.println("Using button 3");
            Serial.print("sleep counter ");
            Serial.println(sleepCounter);
          }
          break;
        case 4: 
          changeSquareState(false);
          swappingColor = false;
          processedInput = true;
          break;
        default:
          Serial.println("Using invalid input");
          processedInput = true;
          delay(2*STANDARDTIME);          

      }
    }
    else 
      Serial.println("Button is not pressed!");  
  }

  // Do not reinitialize the 
  // colors if they are not initialized
  if (!colorsInitialized)
  {
    initializeColors(colorSet, counter, ( PIXELBRIGHTNESS - sleepCounter ));
    //cycleColors(colorSet, curPixelColorIndex, counter, PIXELBRIGHTNESS - sleepCounter ); 

  }

  else if ( colorActive )
  {
    cycleColors(colorSet, curPixelColorIndex, counter, colorSetCounter, PIXELBRIGHTNESS - sleepCounter ); 
    if ( swappingColor && (!dimmingRing || !wakingRing) && colorActive && false )
    {
      if( colorSetCounter > 0 )
        moveBetweenTwoColors(colorSet[!switchColorDirection ? (colorSetCounter == 2 ? 0 : colorSetCounter - 1) : (colorSetCounter)][0], 
                            colorSet[!switchColorDirection ? (colorSetCounter == 2 ? 0 : colorSetCounter - 1) : (colorSetCounter)][1], 
                            colorSet[!switchColorDirection ? (colorSetCounter == 2 ? 0 : colorSetCounter - 1) : (colorSetCounter)][2],
                            colorSet[!switchColorDirection ? (colorSetCounter) : (colorSetCounter == 2 ? 0 : colorSetCounter + 1)][0], 
                            colorSet[!switchColorDirection ? (colorSetCounter) : (colorSetCounter == 2 ? 0 : colorSetCounter + 1)][1], 
                            colorSet[!switchColorDirection ? (colorSetCounter) : (colorSetCounter == 2 ? 0 : colorSetCounter + 1)][2], counter,  PIXELBRIGHTNESS - sleepCounter);
      else 
        moveBetweenTwoColors(colorSet[!switchColorDirection ? 2 : (colorSetCounter)][0], 
                             colorSet[!switchColorDirection ? 2 : (colorSetCounter)][1], colorSet[!switchColorDirection ? 2 : (colorSetCounter)][2],
                             colorSet[!switchColorDirection ? (colorSetCounter) : (1)][0], colorSet[!switchColorDirection ? (colorSetCounter) : (1)][1], 
                             colorSet[!switchColorDirection ? (colorSetCounter) : (1)][2], counter,  PIXELBRIGHTNESS - sleepCounter);
      
    }
  }

  // Change the brigthness of the 
  // neopixel when the flag is active
  if ( dimmingRing )
  {
    sleepCounter += SLEEPINCREMENT;
    if ( VERBOSEOUTPUT || SLEEPINGOUT )
    {
      Serial.println("----------------");
      Serial.print("sleep counter ");
      Serial.println(sleepCounter);
      Serial.print("final brightness value ");
      Serial.println(finalBrightnessValue);
      Serial.print("button pressed ");
      Serial.println(buttonPressedCounter);
      Serial.print("Cur pixel value ");
      Serial.println(( PIXELBRIGHTNESS - sleepCounter ));
      Serial.println("----------------");
    }

    
    // Once the sleep counter has reached it's desired
    // desintation, reset the flags  
    if ( ( PIXELBRIGHTNESS - sleepCounter ) == finalBrightnessValue )
    {
      if ( VERBOSEOUTPUT || SLEEPINGOUT ) Serial.println("Completed sleep action");

      dimmingRing = false;
      processedInput = true;

      // If the ring is supposed to be disabled, 
      // set the pixels to zero
      if( finalBrightnessValue == 0 )
      {
        colorActive = false;
        pixels.setBrightness(0);
        pixels.show();
        //sleepCounter = 0;
      }

    }

  }
  else if ( wakingRing )
  {
    sleepCounter += WAKEINCREMENT;

    if ( VERBOSEOUTPUT || WAKINGOUT )
    {
      Serial.println("**********");
      Serial.println("Waking ring");
      Serial.print("sleep counter ");
      Serial.println(sleepCounter);
      Serial.print("Cur pixel value ");
      Serial.println(( PIXELBRIGHTNESS - sleepCounter ));
      Serial.print("button pressed ");
      Serial.println(buttonPressedCounter);
      Serial.println("**********");
    }


    // Once the sleep counter has been reset stop waking
    if( ( PIXELBRIGHTNESS - sleepCounter ) == 255 )
    {
      if ( VERBOSEOUTPUT || WAKINGOUT ) Serial.println("Completed wake action");

      wakingRing = false;
      pixels.show();
      processedInput = true;      
    }
  }
  
  if ( counter < 4 && colorActive )
  {
    counter++;
  }
  else if( colorActive )
  {
    counter = 0;  
    Serial.print("Old color "); 
    Serial.println(colorSetCounter);
    colorChangeCounter++;



    if( reachedDest )
    {
      if( !switchColorDirection)
      {
        colorSetCounter++;
        if ( colorSetCounter < 3 )
        {
          switchColorDirection = true;
        }
      }
      
      if ( switchColorDirection )
      {
        colorSetCounter--;
        if ( colorSetCounter >= 4 )
        {
          switchColorDirection = false;
        }
      }

      colorChangeCounter = 0;
      newR = colorSet[colorSetCounter == 2 ? 0 : colorSetCounter - 1][0]; 
      newG = colorSet[colorSetCounter == 2 ? 0 : colorSetCounter - 1][1];
      newB = colorSet[colorSetCounter == 2 ? 0 : colorSetCounter - 1][2];
      reachedDest = false;
    }

    /*Serial.print("final r ");
    Serial.print(colorSet[colorSetCounter][0]);
    Serial.print(" final g ");
    Serial.print(colorSet[colorSetCounter][1]);
    Serial.print(" final b ");
    Serial.println(colorSet[colorSetCounter][2]);*/

    if(!dimmingRing && !wakingRing )
      processedInput = true;
    //Serial.print("New color "); 
    //Serial.println(colorSetCounter);
    swappingColor = true;
    /*if(colorActive && (!dimmingRing || !wakingRing))
      swappingColor = true;
    else
      swappingColor = false;*/
  }
  
  lastButtonState = reading;

  delay(DEBUG ? DEBUGTIME : STANDARDTIME);
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
void initializeColors(int colorSet[][3], int colorSetCounter, int brightness ) {
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
    setPixelColor(i, colorSet[curPixelColorIndex[i]][0], colorSet[i][1], colorSet[i][2], brightness);
  }
  pixels.show();

  Serial.println("Showing pixels!");


  colorsInitialized = true;
}

// Change each of the four leds to their next
// neighboor
void cycleColors(int colorSet[][3], int curPixelColorIndex[], int counter, int colorSetCounter, int brightness) 
{

  // Light the next 4 pixels
  changeItem(counter, curPixelColorIndex);
  changeItem(counter + 4, curPixelColorIndex);
  changeItem(counter + 8, curPixelColorIndex);
  changeItem(counter + 12, curPixelColorIndex);

  /*Serial.print("Pixel brightness");
  Serial.println(brightness);*/

  for( int i = 0; i < 4; i++ )
  {
    int curIndex = counter + (i * 4);
    setPixelColor(curIndex, colorSet[curPixelColorIndex[colorSetCounter]][0], colorSet[colorSetCounter][1], colorSet[colorSetCounter][2], brightness);
  }
  pixels.show();
} 

// Set the pixel color based on brightness
void setPixelColor( uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint16_t brightness) {
	pixels.setPixelColor(n, pixels.Color( (r * brightness)/255, (g * brightness)/255, (b * brightness)/255));
}

// Draw a line between the two different colors
void moveBetweenTwoColors( int r1, int g1, int b1,
                           int r2, int g2, int b2, int counter, int brightness ) {
  float incrementR = float(r1) < float(r2) ? COLORRATE : -COLORRATE;
  float incrementG = float(g1) < float(g2) ? COLORRATE : -COLORRATE;
  float incrementB = float(b1) < float(b2) ? COLORRATE : -COLORRATE;

  // Increment all the values in the direction of the new color
  newR += newR != float(r2) ? incrementR:0;
  newG += newG != float(g2) ? incrementG:0;
  newB += newB != float(b2) ? incrementB:0;


  Serial.print("new R ");
  Serial.print(newR);
  Serial.print(", new G ");
  Serial.print(newG);
  Serial.print(", newB ");
  Serial.println(newB);
  Serial.print("final r ");
  Serial.print(r2);
  Serial.print(" final g ");
  Serial.print(g2);
  Serial.print(" final b ");
  Serial.println(b2);
  /*Serial.print("Increment newR ");
  Serial.print(incrementR);
  Serial.print(" Increment newG ");
  Serial.print(incrementG);
  Serial.print(" Increment newB ");
  Serial.println(incrementB);*/
  
  setPixelColor(counter, newR, newG, newB, brightness);
  setPixelColor(counter + 4, newR, newG, newB, brightness);
  setPixelColor(counter + 8, newR, newG, newB, brightness);
  setPixelColor(counter + 12, newR, newG, newB, brightness);
  pixels.show();

  if ( newR == float(r2) && newG == float(g2) && newB == float(b2) )
  {
    Serial.println("Reached dest colors");  
    Serial.print("new R ");
    Serial.print(newR);
    Serial.print(", new G ");
    Serial.print(newG);
    Serial.print(", newB ");
    Serial.println(newB);
    Serial.print("final r ");
    Serial.print(colorSet[colorSetCounter][0]);
    Serial.print(" final g ");
    Serial.print(colorSet[colorSetCounter][1]);
    Serial.print(" final b ");
    Serial.println(colorSet[colorSetCounter][2]);
    Serial.println(b2);
    reachedDest = true;
    //delay(10000);
    return;
  }

  // Once we have reached the specified color
  // break out of the loop and 
  //delay(20);
  
  /*Serial.println("**********************");
  Serial.print("r1 ");
  Serial.print(r1);
  Serial.print(", g1 ");
  Serial.print(g1);
  Serial.print(", b1 ");
  Serial.println(b1);
  Serial.print("r2 ");
  Serial.print(r2);
  Serial.print(", g2 ");
  Serial.print(g2);
  Serial.print(", b2 ");
  Serial.println(b2);*/
}

// Swap the desired item with it's neighboor
void changeItem(int counter,  int * curPixelColorIndex) {
  // If there is another value after this one
  // set this value to the next value
  if( counter < 15 )
  {
    // Set previous node to this node
    curPixelColorIndex[counter] = curPixelColorIndex[counter + 1];    
  }
  // Otherwise set it to the first 
  // item in the array
  else 
  {
    curPixelColorIndex[counter] = curPixelColorIndex[0];
  }
}



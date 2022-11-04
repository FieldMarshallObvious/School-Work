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

// Keep track of if the button has been
// pressed0
bool curButtonState = false;

int colorSet1[4][3] = { {30, 203, 225}, {150, 30, 225}, {225, 52, 30}, {106, 225, 30}};

void setup() {
  // setup button pins
  pinMode(BUTTONPINSET1, INPUT);
  pinMode(BUTTONPINSET1, INPUT);

  // setup led pins
  pinMode(RGBRINPIN, OUTPUT);
  pinMode(WHITESQUAREPIN, OUTPUT);

  // initialize adafruit neopixels
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear();
  pixels.setBrightness(10);

  cycleColors(colorSet1);
}

void cycleColors(int colorSet[][3]) {
  int counter = 0;
  int offsetIteration = 4;
  int starterIndex = 0;
  bool firstPass = false;
  int curPixelColorIndex[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1, -1, -1, -1, -1, -1, -1};

  while(true)
  {
    // If the current index is not initialized
    // initialize it
    if( curPixelColorIndex[counter] == -1 )
    {
      // Set each of the pixel blocks
      // to their corresponding starting color
      if ( counter < 4 )
      {
        curPixelColorIndex[counter] = 0;      
      }
      else if ( counter < 8 )
      {
        curPixelColorIndex[counter] = 1;    
        digitalWrite(WHITESQUAREPIN, HIGH);
  
      }
      else if ( counter < 12 )
      {
        curPixelColorIndex[counter] = 2;      
      }
      else if ( counter < 16 )
      {
        curPixelColorIndex[counter] = 3;      
      }

    }
    else 
    {
      swapItems(counter, curPixelColorIndex);
    }    

    // Set the current pixel 
    pixels.setPixelColor(counter, pixels.Color(colorSet[curPixelColorIndex[counter]][0], colorSet[curPixelColorIndex[counter]][1], colorSet[curPixelColorIndex[counter]][2]));


    if( !firstPass ) { counter++; }
    else { counter += offsetIteration; }

    // If this is the first pass
    // and we have iterated through all the pixels
    // display the pixels
    if( counter > 15)
    {
      pixels.show();

      delay(500);
    }    

    // If the counter has reached the end,
    // reset it
    if ( counter > 15 )
    {
      starterIndex++;
      if ( starterIndex >= 15 )
      {
        counter = starterIndex;
      }
      else 
      {
        counter = 0;
      }
    }

  }
}

void swapItems(int counter,  int * curPixelColorIndex) {
    // If this is the first item
    // swap it with the end of array
    if ( counter <= 4 )
    {
      curPixelColorIndex[0] = curPixelColorIndex[15 - counter];
    }
    // Otherwise swap it with the item 4 spaces back
    else 
    {
      curPixelColorIndex[counter] = curPixelColorIndex[counter - 4];
    }
}



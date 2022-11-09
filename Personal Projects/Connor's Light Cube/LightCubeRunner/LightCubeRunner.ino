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
// pressed
bool curButtonState = false;

bool colorsInitialized = false;

int colorSet1[4][3] = { {30, 203, 225}, {150, 30, 225}, {225, 52, 30}, {106, 225, 30}};
  int curPixelColorIndex[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1, -1, -1, -1, -1, -1, -1};

void setup() {
  Serial.begin(115200);

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

  // Do not reinitialize the 
  // colors if they are not initialized
  if (!colorsInitialized)
    initializeColors(colorSet1);
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

    Serial.print("Pixel array is ");
    Serial.print(curPixelColorIndex[i], DEC);
    Serial.print(" @ ");
    Serial.println(i, DEC);

    // Set the current pixel 
    pixels.setPixelColor(i, pixels.Color(colorSet[curPixelColorIndex[i]][0], colorSet[curPixelColorIndex[i]][1], colorSet[curPixelColorIndex[i]][2]));
  }
  pixels.show();

  Serial.println("Showing pixels!");

  delay(500);

  colorsInitialized = true;
}

// Iterate each of the four leds
void cycleColors(int colorSet[][3], int curPixelColorIndex[], int counter) 
{
  changeItem(counter, curPixelColorIndex);
  pixels.setPixelColor(counter, pixels.Color(colorSet[curPixelColorIndex[counter]][0], colorSet[curPixelColorIndex[counter]][1], colorSet[curPixelColorIndex[counter]][2]));
  pixels.show();

}



void changeItem(int counter,  int * curPixelColorIndex) {
    // Decrease this items value if it is greater than 0
    if( curPixelColorIndex[counter] > 0 )
    {
      curPixelColorIndex[counter] -= 1;
    }
    else
    {
      curPixelColorIndex[counter] = 3;
    }
}



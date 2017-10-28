// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// // released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            A6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      20

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
void bruce(int);
int val = 1;
void setup() {
    Serial.begin(9600);
    pixels.begin(); // This initializes the NeoPixel library.
    pixels.setBrightness(50);
    Serial.begin(9600);
    pinMode(A2,OUTPUT);
}

void loop() {
    digitalWrite(A2,HIGH);
    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
    // fix 2, 13
        val = Serial.parseInt();
        pixels.setPixelColor(val,pixels.Color(100,0,0));
        pixels.show();
        delay(10);

}

// Function to shift the piece of text in bruce across the 23 leds
// a long bar is R+G, a dot is R followed by a blue
// LOGIC SHOULD BE FIXED TO ALLOW FOR ACTUAL LONG DOTS
void bruce(int loops) {
    unsigned int bruce = 1576367959;
    unsigned int shiftedBruce = bruce;
    unsigned int current = 0;
    int previous =0;
    for(int i =0; i < NUMPIXELS;i++)
    {
        current=shiftedBruce&(1<<i);
        if(current)
        {
            current = current / current;
        }
        pixels.setPixelColor(i,pixels.Color(255*current,0,0));
        Serial.print(i);
        Serial.print(" ");
        Serial.println(current);
    }
    pixels.show();
    delay(250);
}
/*
        for(int n = 0;n<30;n++)
        {

            rCur = bruce & 1;
            gCur = bruce & 2;
            bCur = ~(rCur & gCur);
            for(int i=0;i<NUMPIXELS-1;i++){
                pixels.setPixelColor(i, pixels.Color(rCur*255,gCur*255,bCur*255));
                shiftedBruce = shiftedBruce << 2;
                pixels.setPixelColor(i+1, pixels.Color(rCur*255,gCur*255,bCur*255));
                pixels.show();
                delay(500);
            }
        }
        shiftedBruce = bruce;
    }
*/


//BEAT DETECTION
//Reads in frequency bands and displays the lights as appropriate 

void beats() {
    int bass = 0;
    int mids = 0;
    int highs= 0;
    bass = analogRead(4);
    mids = analogRead(8);
    highs= analogRead(9);

    bass = map(bass, 0,4095,0,255);
    mids = map(mids, 0,4095,0,255);
    highs =map(highs,0,4095,0,255);

    for(int i =0;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(highs,mids,bass));
    }
    //Toggle for reset of reading
    digitalWrite(15,LOW);
    digitalWrite(17,LOW);
    digitalWrite(18,LOW);
    delay(1);
    digitalWrite(15,HIGH);
    digitalWrite(17,HIGH);
    digitalWrite(18,HIGH);
    delay(250);
}

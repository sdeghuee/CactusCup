#include <Adafruit_NeoPixel.h>

#define PIN A6
#define SWI 6
#define NUMPIXELS 23
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t,uint8_t);
void rainbow(uint8_t);
void rainbowCycle(uint8_t);
void theaterChase(uint32_t,uint8_t);
void theaterChaseRainbow(uint8_t);
uint32_t Wheel(byte);
void bruce(int);
void dash(int);
void dot(int);
void allone(int,int, int);
int phase = 0;


void setup() {
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    pinMode(SWI,INPUT);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strip.setBrightness(20);
    Serial.begin(9600);
}

void loop() {
    // Some example procedures showing how to display to the pixels:
//    bruce(500);
//    colorWipe(strip.Color(255, 0, 0), 50); // Red
//    colorWipe(strip.Color(0, 255, 0), 50); // Green
//    colorWipe(strip.Color(0, 0, 255), 50); // Blue
//    colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
    // Send a theater pixel chase in...
//    theaterChase(strip.Color(127, 127, 127), 50); // White
//    theaterChase(strip.Color(127, 0, 0), 50); // Red
//    theaterChase(strip.Color(0, 0, 127), 50); // Blue
//    rainbow(20);
    phase = !digitalRead(SWI);
    if(phase == 0)
    {
        allone(0,0,0);
    }
    else if(phase == 1)
    {
        rainbowCycle(20);
    }
//    theaterChaseRainbow(50);
    
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}

void rainbow(uint8_t wait) {
    uint16_t i, j;

    for(j=0; j<256; j++) {
        for(i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel((i+j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
    uint16_t i, j;

    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
                strip.setPixelColor(i+q, c);    //turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
                strip.setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
    for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
                strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
                strip.setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void bruce(int time)
{
    dash(time);
    dot(time);
    dot(time);
    dot(time);

    dot(time);
    dash(time);
    dot(time);

    dot(time);
    dot(time);
    dash(time);

    dash(time);
    dot(time);
    dash(time);
    dot(time);

    dot(time);
}

void dash(int time)
{
    Serial.println("dash");
    allone(0,255,0);
    delay(2*time);
    allone(0,0,0);
    delay(time);
}

void dot(int time)
{
    Serial.println("dot");
    allone(0,255,0);
    delay(time);
    allone(0,0,0);
    delay(time);
}

void allone(int g,int r, int b)
{
    for(uint16_t i=0; i<strip.numPixels(); i++)
    {
        strip.setPixelColor(i, strip.Color(g, r, b));
        strip.show();
    }
}

// This #include statement was automatically added by the Spark IDE.
#include "LiquidCrystal_I2C.h"

// This #include statement was automatically added by the Spark IDE.
#include "neopixel/neopixel.h"

#include "application.h"
//#include "spark_disable_wlan.h" // For faster local debugging only
#include "neopixel/neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D3
#define PIXEL_COUNT 24
#define PIXEL_TYPE WS2812B

#define LCD_PIN D3
#define MAX_LENGTH 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
LiquidCrystal_I2C   *lcd;

String header = "Tweeting Rainbow:";
String tweet = "Butterfly in the sky, I can go twice as high, take a look, it's in a book, a reading rainbow, I can go anywhere!";
String pendingTweet = "";
uint16_t tweet_offset = 0;

void setup() 
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  lcd = new LiquidCrystal_I2C(0x3F, 20, 4);
  lcd->init();
  lcd->backlight();
  lcd->clear();
  updateDisplay();
  
  Spark.function("setTweet", setTweet);
}

void loop() 
{
  //rainbow(20);
  halvesBackAndForth(40, 4000);
}

void clear(uint16_t pixel)
{
    strip.setPixelColor(pixel, 0);
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

void halvesBackAndForth(uint8_t wait, uint16_t lcdWait) {
  uint16_t i, j;

  uint16_t waiting = 0;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      if (i % 2 == 0) {
        strip.setPixelColor(i, Wheel((i+j) & 255));
        strip.setPixelColor(strip.numPixels() - i - 1, Wheel((255 -i-j) & 255));
      } else {
        strip.setPixelColor(i, Wheel((255 -i-j) & 255));
        strip.setPixelColor(strip.numPixels() - i - 1, Wheel((i+j) & 255));
      }
      strip.show();
      delay(wait);
      waiting += wait;
      if (waiting > lcdWait) {
          waiting = waiting - lcdWait;
          swapLengthyTweet();
      }
      clear(i);
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void swapLengthyTweet() {
    if (tweet.length() > MAX_LENGTH) {
        tweet_offset = tweet_offset + 60;
        if (tweet_offset >= tweet.length()) {
            tweet_offset = 0;
        }
        updateDisplay();
    }
}

int setTweet(String t) {
    int segment = t.substring(0,1).toInt();
    int total = t.substring(2,3).toInt();
    String sub = t.substring(4);
    
    if (segment == 1) {
        // First segment
        pendingTweet = sub;
    } else {
        // Appendage
        pendingTweet += sub;
    }
    
    if (segment == total) {
        // Final
        tweet = pendingTweet;
        tweet_offset = 0;
        updateDisplay();
    }
    
    return 1;
}

void updateDisplay() {
    setDisplay(header, tweet.substring(tweet_offset, tweet_offset + 20), 
                       tweet.substring(tweet_offset + 20, tweet_offset + 40), 
                       tweet.substring(tweet_offset + 40, tweet_offset + 60));
}

void setDisplay(String a, String b, String c, String d) {
    if (a.length() > 20 || b.length() > 20 || c.length() > 20 || d.length() > 20) {
        return;
    }
    
    lcd->setCursor(0, 0);
    lcd->print("                    ");
    lcd->setCursor(0, 0);
    lcd->print(a);

    lcd->setCursor(0, 1);
    lcd->print("                    ");
    lcd->setCursor(0, 1);
    lcd->print(b);

    lcd->setCursor(0, 2);
    lcd->print("                    ");
    lcd->setCursor(0, 2);
    lcd->print(c);

    lcd->setCursor(0, 3);
    lcd->print("                    ");
    lcd->setCursor(0, 3);
    lcd->print(d);
}
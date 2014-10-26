Tweeting Rainbow
==================

Step 1: Strap an LCD screen to your personal being

Step 2: Live-stream tweets to your chest

![Tweeting Rainbow](http://i.imgur.com/keVWP97.jpg)

## Hardware

You need:

* [Spark Core](http://spark.io) - $40
* [20x4 LCD](http://www.amazon.com/gp/product/B0080DYTZQ/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1) - $10-12
* 2x 4.7k Resistors (optional, but recommended)
* Jumper Wires

Wiring: 

* Spark D0 to LCD SDA
* Spark D1 to LCD SCL
* GRND to GRND
* VIN to VCC
* VIN to positive (red) line on breadboard
* two resistors from positive to D0 and D1

The .ino file provides additional handling of a 24-Neopixel LED ring on pin D3 that requires additional wiring. If you do not have LEDs, you can safely remove all associated neopixel code.

Diagram to come.

## Running

1. Make sure the LCD address in tweeting-rainbow.ino is correct. It is usually 0x27 or 0x34, but check with the manufacturer.

2. Flash the firmware onto your Spark Core.

3. Insert your access tokens and IDs as needed in the server script.

4. Turn on your core and run the server script on your computer, or host it on Heroku with a [scheduler](https://devcenter.heroku.com/articles/clock-processes-python).


## Example Tweets

\#wtf
> twitter is DEAD and it's only 11pm wtf i didn't raise ya'll to be WEAK like this i'm so disappointed in you children

\#fml
> RT @schoolfession: "Woke up hungover af after a party, found someone's cum in my socks...... #fml" - Colonial HS

\#halloween
> OH MY GOD HALLOWEEN MEANS RERUNS OF HALLOWEENTOWN ON DISNEY CHANNEL WHAT A TIME TO BE ALIVE

\#spooky
> my "spooky halloween" name is juicy dong demon

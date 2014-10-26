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

Diagram to come.

## Running

1. Flash the firmware onto your Spark Core.

2. Insert your access tokens and IDs as needed in the server script.

3. Turn on your core and run the server script on your computer, or host it on Heroku wuth a [scheduler](https://devcenter.heroku.com/articles/clock-processes-python).
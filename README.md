 WORD CLOCK - NeoMatrix 8x8 ESP32&NTP Edition
================
by [kghr labo](https://xxxxxx)
Original by [Andy Doro](https://andydoro.com/) & [Dano Wall](https://github.com/danowall)


A word clock which uses NeoPixel RGB LEDs for a color shifting effect.


Hardware:
-------
 
 - [ESP32 Dev kit](xxxxxxxx) (should work with any ESP32-compatibles) 
 - [NeoPixel 64 LEDs (WS2812B)](xxxxxx)
 - laser cut faceplate & enclosure
 
Software:
-------
 
This code requires the following libraries:
 
 - [FastLED](https://github.com/FastLED/FastLED)


Wiring:
-------

 - Solder NeoPixel 5V to ESP32 Dev kit VCC(5V), GND to GND, DIN to GOIO pin 16.
 

grid pattern:
-------

 ```
 A T W E N T Y D
 Q U A R T E R Y
 F I V E H A L F
 D P A S T O W I
 F I V E I G H T
 S I X T H R E E
 T W E L E V E N
 F O U R N I N E
 ```
 
 Tape LED layout:
 -------
 
 ```
   |== ESP32 Dev kit
   |
 0 X--X--X--X--X--X--X--X 7
                        |
15 X--X--X--X--X--X--X--X 8
   |
16 X--X--X--X--X--X--X--X 23
                        |
31 X--X--X--X--X--X--X--X 24
   |
32 X--X--X--X--X--X--X--X 39
                        |
47 X--X--X--X--X--X--X--X 40
   |
48 X--X--X--X--X--X--X--X 55
                        |
63 X--X--X--X--X--X--X--X 56
 ```

Acknowledgements:
  - Thanks [Andy Doro](https://andydoro.com/) & [Dano Wall](https://github.com/danowall) 
 


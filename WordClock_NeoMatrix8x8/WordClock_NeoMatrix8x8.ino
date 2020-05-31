/*
   WORD CLOCK - 8x8 NeoPixel Desktop Edition for ESP32
   by kghr labo
   (original for Trinket Pro by Andy Doro)

   A word clock using NeoPixel RGB LEDs for a color shift effect.

   Hardware:
      
   - ESP32 Dev kit
   - NeoPixel 64 LEDs (WS2812B)


   Software:

   This code requires the following libraries:
   
   - FastLED https://github.com/FastLED/FastLED


   Wiring:
   - Solder NeoPixel 5V to ESP32 Dev kit VCC(5V), GND to GND, DIN to GOIO pin 16.
   

   grid pattern

    A T W E N T Y D
    Q U A R T E R Y
    F I V E H A L F
    D P A S T O W I
    F I V E I G H T
    S I X T H R E E
    T W E L E V E N
    F O U R N I N E


*/

// include the library code:
#include <WiFi.h>
#include <FastLED.h>

// define how to write each of the words

// 64-bit "mask" for each pixel in the matrix- is it on or off?
uint64_t mask;

// define masks for each word. we add them with "bitwise or" to generate a mask for the entire "phrase".
#define MFIVE    mask |= 0xF00000000000        // these are in hexadecimal
#define MTEN     mask |= 0x5800000000000000
#define AQUARTER mask |= 0x80FE000000000000
#define TWENTY   mask |= 0x7E00000000000000
#define HALF     mask |= 0xF0000000000
#define PAST     mask |= 0x7800000000
#define TO       mask |= 0xC00000000
#define ONE      mask |= 0x43
#define TWO      mask |= 0xC040
#define THREE    mask |= 0x1F0000
#define FOUR     mask |= 0xF0
#define FIVE     mask |= 0xF0000000
#define SIX      mask |= 0xE00000
#define SEVEN    mask |= 0x800F00
#define EIGHT    mask |= 0x1F000000
#define NINE     mask |= 0xF
#define TEN      mask |= 0x1010100
#define ELEVEN   mask |= 0x3F00
#define TWELVE   mask |= 0xF600
#define ANDYDORO mask |= 0x8901008400040040

#define WIFI     mask = 0x3C0000000
#define WIFIER   mask = 0x3C0002010
#define NTPER    mask = 0xC00004000002010

// define pins
#define NEOPIN       16  // connect to DIN on NeoPixel
#define NUM_LEDS     64  // 8x8
#define LED_TYPE     WS2812B
#define COLOR_ORDER  GRB

CRGB leds[NUM_LEDS];

// wifi setting
const char* ssid     = "set your wifi ssid";
const char* password = "set your wifi password";

// brightness based on time of day- could try warmer colors at night?
#define DAYBRIGHTNESS 40
#define NIGHTBRIGHTNESS 20

// cutoff times for day / night brightness. feel free to modify.
#define MORNINGCUTOFF 7  // when does daybrightness begin?   7am
#define NIGHTCUTOFF   22 // when does nightbrightness begin? 10pm

// define delays
#define FLASHDELAY 250  // delay for startup "flashWords" sequence
#define SHIFTDELAY 100   // controls color shifting speed

struct tm theTime; // Holds current clock time

int j;   // an integer for the color shifting effect

// ntp setting
const char* ntpServer = "time.google.com";
const long  gmtOffset_sec = 3600*9; // JST +9
const int   daylightOffset_sec = 3600*0; // no Daylight Saving


void setup() {
  // put your setup code here, to run once:

  //Serial for debugging
  //Serial.begin(9600);

  // initialize NeoPixel 
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, NEOPIN>(leds, NUM_LEDS);
  FastLED.setBrightness(DAYBRIGHTNESS);
  FastLED.clear(); // Initialize all pixels to 'off'
  FastLED.show();

  // wifi connect
  int retry = 0;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500); // 500ms
    retry ++;
    mask = 0;
    if (retry%2) WIFI;
    applyMask();
    
    if (retry > 20) {
      WIFIER;  // wifi connect timeout (500ms x 20 = 10 sec)
      applyMask();
      delay(30000); // hold 30 sec
      ESP.restart(); // restart ESP32
    }
  }
  Serial.println();
  Serial.printf("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // Config NTP 
  configTime( gmtOffset_sec, 0, ntpServer);
   
  // When you are in/out DST, please reboot this WORD CLOCK to apply daylightOffset_sec.
  if (daylightOffset_sec != 0) {
    if (checkDst() == true) { // check whether we're in DST right now. If we are, subtract an hour.
      configTime( gmtOffset_sec, daylightOffset_sec, ntpServer);
    }
  }
  getTheTime();
  Serial.println(&theTime, "%A, %B %d %Y %H:%M:%S");
   
  // startup sequence... do colorwipe?
  // delay(500);
  // rainbowCycle(20);
  delay(500);
  flashWords(); // briefly flash each word in sequence
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  getTheTime();
  adjustBrightness();
  displayTime();

}

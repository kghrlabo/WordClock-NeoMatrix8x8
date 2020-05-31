
// change brightness based on the time of day.

void adjustBrightness() {
  //change brightness if it's night time
  if (theTime.hour() < MORNINGCUTOFF || theTime.hour() > NIGHTCUTOFF) {
    FastLED.setBrightness(NIGHTBRIGHTNESS);
  } else {
    FastLED.setBrightness(DAYBRIGHTNESS);
  }
}

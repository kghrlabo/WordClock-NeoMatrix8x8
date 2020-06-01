
// change brightness based on the time of day.

void adjustBrightness() {
  //change brightness if it's night time
  if (theTime.tm_hour < MORNINGCUTOFF || theTime.tm_hour > NIGHTCUTOFF) {
    FastLED.setBrightness(NIGHTBRIGHTNESS);
  } else {
    FastLED.setBrightness(DAYBRIGHTNESS);
  }
}

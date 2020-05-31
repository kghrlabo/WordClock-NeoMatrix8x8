//

void getTheTime() {
  if(!getLocalTime(&theTime)){
    Serial.println("Failed to obtain time");
    NTPER;  // wifi connect timeout
    applyMask();
    delay(30000);
    ESP.restart();
  }
  return;
}

boolean checkDst() {

  //Get the day of the week. 0 = Sunday, 6 = Saturday
  int previousSunday = theTime.tm_mday - theTime.tm_wday;

  boolean dst = false; //Assume we're not in DST
  if (theTime.tm_mon > 3 && theTime.tm_mon < 11) dst = true; //DST is happening!

  //In March, we are DST if our previous Sunday was on or after the 8th.
  if (theTime.tm_mon == 3)
  {
    if (previousSunday >= 8) dst = true;
  }
  //In November we must be before the first Sunday to be dst.
  //That means the previous Sunday must be before the 1st.
  if (theTime.tm_mon == 11)
  {
    if (previousSunday <= 0) dst = true;
  }

  return dst;

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Decalcifier Program with countdown timer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CountDown Timer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void countdowntimer() {
  tDown.run();
  tDown.start();
}

void tDownComplete() {}

void clocklcd() {
  lcd.setCursor(6, 1);
  lcd.print(tDown.getCurrentTime());                                                            // Do not use F() here the clock will not change
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Decalcifier Program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cleaning() {

  coffeeTemp_c = coffeeSensor.calc_Celsius(&temperature);
  pinMode (coffeeStartbut, OUTPUT);                                    // sets coffee start button to an output as the relay that controlls cleaning programs is connected to the same line so it can cause program errors
  cleaningProg = 1;                                                    // disable all button functions that are not in use in this program

  enum screens { cleanstart, waterwithdecal, pausedcountdown, waterwithdecalsecond, waitforcleanwater, flushwithwater, cleaningcomplete };
  byte currentScreen = -1;

  if ( currentScreen != cleanstart && cleaningstatus == 0 ) {

    currentScreen = cleanstart;
    Serial.println (F(" Fill water tank add decailer then press button to start"));
    lcd.setCursor(0, 0);
    lcd.print(F("Fill water tank,    "));
    lcd.setCursor(0, 1);
    lcd.print(F("Add Decalcifier then"));
    lcd.setCursor(0, 2);
    lcd.print(F("Click to start      "));
    lcd.setCursor(0, 3);
    lcd.print(F("Boiler C="));
    lcd.print(coffeeTemp_c);
    lcd.print(F("      "));
    while  (middle)
    {
      middle = false;
      if (currentTime - previousTime >= 100)
        cleaningstatus ++;               // Increment Count by 1
      previousTime = currentTime;
    }
  }

  if ( currentScreen != waterwithdecal && cleaningstatus == 1 ) {

    currentScreen = waterwithdecal;
    Serial.println (F("Cleaning Started"));
    lcd.setCursor(0, 0);
    lcd.print(F("Cleaning Started    "));
    lcd.setCursor(0, 1);
    lcd.print(F("Decalcifier Solution"));
    lcd.setCursor(0, 2);
    lcd.print(F("Boiler C="));
    lcd.print(coffeeTemp_c);
    lcd.print(F("     "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= 30000 && cleaningstatus == 1) {
      previousTime = currentTime;
      cleaningstatus ++;
    }
  }

  if ( currentScreen != pausedcountdown && cleaningstatus == 2 ) {

    currentScreen = pausedcountdown;
    Serial.println (F("Pause"));
    lcd.setCursor(0, 0);             
    lcd.print(F("** Empty Driptray **"));
    lcd.setCursor(0, 1);
    lcd.print(F("      "));
    countdowntimer();
    clocklcd();
    lcd.setCursor(14, 1);
    lcd.print(F("      "));
    lcd.setCursor(0, 2);
    lcd.print(F("Boiler C="));
    lcd.print(coffeeTemp_c);
    lcd.print(F("      "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, LOW);
  }
  if (currentTime - previousTime >= 300000 && cleaningstatus == 2) {
    previousTime = currentTime;
    cleaningstatus ++;
  }

  if ( currentScreen != waterwithdecalsecond && cleaningstatus == 3 ) {

    currentScreen = waterwithdecalsecond;
    Serial.println (F("Flush cleaner"));
    lcd.setCursor(0, 0);
    lcd.print(F("Cleaning Started    "));
    lcd.setCursor(0, 1);
    lcd.print(F("Decalcifier solution"));
    lcd.setCursor(0, 2);
    lcd.print(F("second flush        "));
    lcd.setCursor(0, 3);
    lcd.print(F("Boiler C="));
    lcd.print(coffeeTemp_c);
    lcd.print(F("      "));
    digitalWrite(pumpRelay, HIGH);
  }
  if (currentTime - previousTime >= 20000 && cleaningstatus == 3) {
    previousTime = currentTime;
    cleaningstatus ++;
  }


  if ( currentScreen != waitforcleanwater && cleaningstatus == 4 ) {

    currentScreen = waitforcleanwater;
    Serial.println (F("Empty tank and add fresh water"));
    lcd.setCursor(0, 0);
    lcd.print(F("Empty Tank/Driptray "));
    lcd.setCursor(0, 1);
    lcd.print(F("Add Fresh water     "));
    lcd.setCursor(0, 2);
    lcd.print(F("Click to begin      "));
    lcd.setCursor(0, 3);
    lcd.print(F("Last cycle!         "));
    digitalWrite(pumpRelay, HIGH);
    while  (middle)
    {
      middle = false;
      if (currentTime - previousTime >= 100)
        cleaningstatus ++;               // Increment Count by 1
      previousTime = currentTime;
    }
  }

  if ( currentScreen != flushwithwater && cleaningstatus == 5 ) {

    currentScreen = flushwithwater;
    Serial.println (F("Fresh water flush"));
    lcd.setCursor(0, 0);
    lcd.print(F("Fresh water Flush   "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("Boiler C="));
    lcd.print(coffeeTemp_c);
    lcd.print(F("      "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
  }
  if (currentTime - previousTime >= 60000 && cleaningstatus == 5) {
    previousTime = currentTime;
    cleaningstatus ++;
  }

  if ( currentScreen != cleaningcomplete && cleaningstatus == 6 ) {

    currentScreen = cleaningcomplete;
    Serial.println(F("Cleaning Complete press button to exit to main program"));
    lcd.setCursor(0, 0);
    lcd.print(F("Cleaning Complete   "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("Boiler C="));
    lcd.print(coffeeTemp_c);
    lcd.print(F("      "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait to exit "));
    digitalWrite(pumpRelay, LOW);
  }
  if (currentTime - previousTime >= 5000 && cleaningstatus == 6) {
    previousTime = currentTime;
    cleaningstatus ++;
  }
  if (cleaningstatus == 7) {
    Serial.println(F("Reset to main program"));
    delay(2000); //call reset
  }
}

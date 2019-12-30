void backflush() {
                                                                                                   // The F() macro tells the compiler to leave this particular array in PROGMEM.
                                                                                                   // Then when it is time to access it, one byte of the data is copied to RAM at a time.                                                                                      
   cleaningProg =1;
   pinMode (coffeeStartbut, OUTPUT);                                                               // Sets coffee start button as output as relay is connected to start button power line                                                       
   int BFrun;                                                                                                 
   BFrun = BFpause *1000;                                                                          // BFrun will now equal BFpause times 1000    
   
                                                                                                        
                                                                                                   
  if (bfTag == 0) {
    Serial.println (F("Fill portafilter with detergent and DoubleClick"));
    lcd.setCursor(0, 0);
    lcd.print(F("  Fill Portafiller  "));
    lcd.setCursor(0, 1);
    lcd.print(F("   With Detergent   "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Start   "));
    while    (middle) 
    { 
       middle = false; 
      if (currentTime - previousTime >= 200 && bfTag == 0)
        bfTag ++;
      previousTime = currentTime;

    }
  }

  if (bfTag == 1)
  {
    Serial.println (F("Back Flush Start"));
    lcd.setCursor(0, 0);
    lcd.print(F("Back Flush Start    "));
    lcd.setCursor(0, 1);
    lcd.print(F("1 of 11             "));
    lcd.setCursor(0, 2);
    lcd.print(F("Detergent Cycle     "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= 4000 && bfTag == 1) {
      bfTag ++;
      previousTime = currentTime;
    }
  }
  if (bfTag == 2 || bfTag == 4 || bfTag == 6 || bfTag == 8 || bfTag == 12 || bfTag == 14 || bfTag == 16 || bfTag == 18)
  {
    Serial.println (F("Back Flush pause"));
    lcd.setCursor(0, 0);
    lcd.print(F("Back Flush Pause!   "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, LOW);
    if (currentTime - previousTime >= BFrun) {
      bfTag ++;
      previousTime = currentTime;
    }
  }
  if (bfTag == 3)
  {
    Serial.println (F("Back Flush 2nd"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("2 of 11             "));
    lcd.setCursor(0, 2);
    lcd.print(F("Detergent Cycle     "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= BFrun && bfTag == 3) {
      bfTag ++;
      previousTime = currentTime;
    }
  }
 
  if (bfTag  == 5)
  {
    Serial.println (F("Back Flush 3rd"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("3 of 11             "));
    lcd.setCursor(0, 2);
    lcd.print(F("Detergent Cycle     "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= BFrun && bfTag == 5) {
      bfTag ++;
      previousTime = currentTime;
    }
  }

  if (bfTag  == 7)
  {
    Serial.println (F("Back Flush 4th"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("4 of 11             "));
    lcd.setCursor(0, 2);
    lcd.print(F("Detergent Cycle     "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= BFrun && bfTag == 7) {
      bfTag ++;
      previousTime = currentTime;
    }
  }

  if (bfTag  == 9)
  {
    Serial.println (F("Back Flush 5th"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("5 of 11             "));
    lcd.setCursor(0, 2);
    lcd.print(F("Detergent Cycle     "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= BFrun && bfTag == 9) {
      bfTag ++;
      previousTime = currentTime;
    }
  }
  if (bfTag  == 10)
  {
    Serial.println (F("Back Flush pause"));
    digitalWrite(pumpRelay, LOW);
    lcd.print(F("Empty Portafilter of"));
    lcd.setCursor(0, 1);
    lcd.print(F("     Detergent!     "));
    lcd.setCursor(0, 2);
    lcd.print(F(" Click to Continue  "));
    lcd.setCursor(0, 3);
    lcd.print(F("  With Flush Cycle  "));
    Serial.println(F("Empty Group Head of cleaner then press test to continue"));
    while (middle)
    {
      middle = false;
      if (currentTime - previousTime >= 200 && bfTag == 10)
        bfTag ++;
      previousTime = currentTime;
    }
  }
  if (bfTag == 11)
  {
    Serial.println (F("Back Flush water flush"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("6 of 11             "));
    lcd.setCursor(0, 2);
    lcd.print(F("Flush Cycle         "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= 4000 && bfTag == 11) {
      bfTag ++;
      previousTime = currentTime;
    }
  }
 
  if (bfTag  == 13)
  {
    Serial.println (F("Back Flush water flush 2nd"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("7 of 11             "));
    lcd.setCursor(0, 2);
    lcd.print(F("Flush Cycle         "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= BFrun && bfTag == 13) {
      bfTag ++;
      previousTime = currentTime;
    }
  }
 
  if (bfTag == 15)
  {
    Serial.println (F("Back Flush water flush 3rd"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("8 of 11             "));
    lcd.setCursor(0, 2);
    lcd.print(F("Flush Cycle         "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= BFrun && bfTag == 15) {
      bfTag ++;
      previousTime = currentTime;
    }
  }

  if (bfTag == 17)
  {

    Serial.println (F("Back Flush water flush 4th"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("9 of 11            "));
    lcd.setCursor(0, 2);
    lcd.print(F("Flush Cycle         "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= BFrun && bfTag == 17) {
      bfTag ++;
      previousTime = currentTime;
    }
  }
  
  if (bfTag == 19)
  {
    Serial.println (F("Back Flush water flush 5th"));
    lcd.print(F("Back Flush RUN!     "));
    lcd.setCursor(0, 1);
    lcd.print(F("10 of 11            "));
    lcd.setCursor(0, 2);
    lcd.print(F("Flush Cycle         "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, HIGH);
    if (currentTime - previousTime >= BFrun && bfTag == 19) {
      bfTag ++;
      previousTime = currentTime;
    }
  }
  if (bfTag == 20)
  {
    Serial.println (F("Back Flush pause"));
    lcd.print(F("Back Flush Finished "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("Please Wait!        "));
    digitalWrite(pumpRelay, LOW);
    bfTag ++;
    Serial.println(F("Back Flush Complete press button to exit to main program"));
  }
  if (currentTime - previousTime >= 8000 && bfTag == 21) {
    Serial.println(F("Reset to main program"));
    delay(2000); //call reset
  }
  else if (bfTag > 22)
  {
    bfTag = 0;
  }
}

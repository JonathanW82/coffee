


void coffeescreen() {

  updatecoffeeSensor();
  lcd.setCursor(0, 0);
  lcd.print(F("Boiler "));
  lcd.print(F("    C= "));
  coffeeTemp_c = coffeeSensor.calc_Celsius(&temperature);
  lcd.print(coffeeTemp_c);
  lcd.setCursor(19, 0);
  lcd.print(F(" "));
  lcd.setCursor(0, 1);
  lcd.print(F("Target     C= "));
  lcd.print(coffeeBoilerTarget);
  
  if (coffeeBoilerTarget > 100) {
    lcd.setCursor(18, 1);
    lcd.print(F("00"));
    lcd.setCursor(20, 1);
    lcd.print(F(" "));
  }
  else if (coffeeBoilerTarget < 100){
    lcd.setCursor(17, 1);
    lcd.print(F("00"));
    lcd.setCursor(19, 1);
    lcd.print(F("  "));
  }
  setTime(0);                                                                                     // sets seconds to zero to restart espresso timer

  if (coffeeTemp_c < coffeeBoilerTarget) {
    lcd.setCursor(0, 2);
    lcd.print(F("  Machine HEATING   "));
    lcd.setCursor(0, 3);
    lcd.print(F("    Please Wait!    "));
  }
  else {
    lcd.setCursor(0, 3);
    lcd.print (F("Machine READY !!    "));
    lcd.setCursor(0, 2);
    lcd.print (F("                    "));

  }
}

void espressomakescreen() {

  updatecoffeeSensor();
  lcd.setCursor(0, 0);
  lcd.print(F("Making Espresso     "));
  lcd.setCursor(0, 1);
  lcd.print(F("TIME ="));
  lcd.setCursor(6, 1);
  lcd.print(F("  "));
  lcd.setCursor(8, 1);
  if (seconds < 10) lcd.print (F("0"));
  lcd.print(seconds);
  lcd.setCursor(10, 1);
  lcd.print(F("          "));
  lcd.setCursor(0, 2);
  lcd.print(F("Boiler "));
  lcd.print(F("     C="));
  coffeeTemp_c = coffeeSensor.calc_Celsius(&temperature);
  lcd.print(coffeeTemp_c);
  lcd.setCursor(0, 3);
  lcd.print(F("Checkout that Crema!"));

  if(coffeeTemp_c <100){
  lcd.setCursor(19, 2);
  lcd.print(F(" "));
  }
}

void steamscreen() {

  updatecoffeeSensor();
  lcd.setCursor(0, 0);
  lcd.print(F("Steaming in Progress"));
  lcd.setCursor(0, 1);
  lcd.print(F("C= "));
  coffeeTemp_c = coffeeSensor.calc_Celsius(&temperature);
  lcd.print(coffeeTemp_c);
  lcd.setCursor(10, 1);
  lcd.print(F(" T= "));
  lcd.print(steamBoilerTarget);

   if (steamBoilerTarget < 100){
    lcd.setCursor(16, 1);
    lcd.print(F("    "));
  }
  else if(steamBoilerTarget >100){
    lcd.setCursor(17, 1);
    lcd.print(F("   "));
  }
  
   if (coffeeTemp_c < steamBoilerTarget) {
    lcd.setCursor(0, 2);
    lcd.print(F("  Machine HEATING   "));
    lcd.setCursor(0, 3);
    lcd.print(F("    Please Wait!    "));
  }
  else {
    lcd.setCursor(0, 3);
    lcd.print (F("Machine READY !!    "));
    lcd.setCursor(0, 2);
    lcd.print (F("                    "));

  }
}

void hotWater() {

  lcd.setCursor(0, 0);
  lcd.print(F("DISPENSE HOT WATER  "));
  lcd.setCursor(0, 1);
  lcd.print(F("FROM STEAM WAND TURN"));
  lcd.setCursor(0, 2);
  lcd.print(F("STEAM KNOB          "));
  lcd.setCursor(0, 3);
  lcd.print(F("OR CHECK BUTTONS!!  "));
}

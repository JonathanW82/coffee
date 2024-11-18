
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Steam Boiler Settings ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void updateSteamheater () {
  if (menuEntered == 1) {digitalWrite(Boiler, LOW); }
  else {
    steamtempVal = coffeeSensor.calc_Celsius(&temperature);

    if (steamtempVal <= steamBoilerTarget && steamSwing == 0) {
      digitalWrite(Boiler, HIGH);
    }
    else {
      digitalWrite(Boiler, LOW);
      Serial.print(F("Steam Boiler OFF"));
      steamSwing = 1;
    }
    if (steamtempVal < steamBoilerTarget - 5 && steamSwing == 1)
    {
      steamSwing = 0;
    }
  }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Coffee Boiler Settings ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

float heatcycles; // the number of millis out of 1000 for the current heat amount (percent * 10)

boolean heaterState = 0;

unsigned long heatCurrentTime, heatLastTime;


void updatecoffeeHeater() {
  boolean h;
  heatCurrentTime = millis();
  if (heatCurrentTime - heatLastTime >= 1000 or heatLastTime > heatCurrentTime) { //second statement prevents overflow errors
    // begin cycle
    _turnHeatElementOnOff(1);  //
    heatLastTime = heatCurrentTime;
  }
  if (heatCurrentTime - heatLastTime >= heatcycles) {
    _turnHeatElementOnOff(0);
  }
}

void setHeatPowerPercentage(float power) {
  if (power <= 0.0) {
    power = 0.0;
  }
  if (power >= 1000.0) {
    power = 1000.0;
  }
  heatcycles = power;
}

float getHeatCycles() {
  return heatcycles;
}

void _turnHeatElementOnOff(boolean on) {

  digitalWrite(Boiler, on);     //turn pin high
  heaterState = on;
}

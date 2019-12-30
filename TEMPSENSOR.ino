

void updatecoffeeSensor() {
  // data from temperature sensor converted to degrees celcious

  coffeeSensor.getTemperature(&temperature);
  Temperatur_C = coffeeSensor.calc_Celsius(&temperature);

}

float latestReading = 0.0;

void updateTempSensor() {
    coffeeSensor.getTemperature(&temperature);                                              // standard way of getting the temperature.
    
   
}

float getFreshTemp() { 
      latestReading =  Temperatur_C = coffeeSensor.calc_Celsius(&temperature);
     
  return latestReading;

}

float getLastTemp() {
  return latestReading;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PID EEPROM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void get_data_from_eeprom(){
  EEPROM.get(4, coffee_boiler_target);                             // EEprom to get inital Coffee temp Traget from position 26
  EEPROM.get(8, steam_boiler_target);                              // EEprom to get initial Steam temp Target from position 20
  EEPROM.get(12, bf_pause_duration);
  EEPROM.get(16, boiler_PID.P);
  EEPROM.get(20, boiler_PID.I);
  EEPROM.get(24, boiler_PID.D);
}

void put_data_to_eeprom(){
  EEPROM.put(4, coffee_boiler_target);                             // EEprom to get inital Coffee temp Traget from position 26
  EEPROM.put(8, steam_boiler_target);                              // EEprom to get initial Steam temp Target from position 20
  EEPROM.put(12, bf_pause_duration);
  EEPROM.put(16, boiler_PID.P);
  EEPROM.put(20, boiler_PID.I);
  EEPROM.put(24, boiler_PID.D);
}


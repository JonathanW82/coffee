//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PID EEPROM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void get_data_from_eeprom(){
  EEPROM.get(4, initial_set_up);
  EEPROM.get(8, coffee_boiler_target);                             // EEprom to get inital Coffee temp Traget from position 26
  EEPROM.get(12, steam_boiler_target);                              // EEprom to get initial Steam temp Target from position 20
  EEPROM.get(16, bf_pause_duration);
  EEPROM.get(20, boiler_PID.P);
  EEPROM.get(24, boiler_PID.I);
  EEPROM.get(28, boiler_PID.D);
  EEPROM.get(32, pre_infusion_target_pressure);
  EEPROM.get(36, pre_infusion_run_time);
  EEPROM.get(40, pre_infusion_pause_time);
  EEPROM.get(44, espresso_pull_time);
}

void put_data_to_eeprom(){
  EEPROM.put(4, initial_set_up);
  EEPROM.put(8, coffee_boiler_target);                             // EEprom to get inital Coffee temp Traget from position 26
  EEPROM.put(12, steam_boiler_target);                              // EEprom to get initial Steam temp Target from position 20
  EEPROM.put(16, bf_pause_duration);
  EEPROM.put(20, boiler_PID.P);
  EEPROM.put(24, boiler_PID.I);
  EEPROM.put(28, boiler_PID.D);
  EEPROM.put(32, pre_infusion_target_pressure);
  EEPROM.put(36, pre_infusion_run_time);
  EEPROM.put(40, pre_infusion_pause_time);
  EEPROM.put(44, espresso_pull_time);
}

void check_initial_set_up(){
  if(!initial_set_up){
    Serial.println("Initial setup start");
    initial_set_up = true;
    coffee_boiler_target = 95;
    steam_boiler_target = 130;
    bf_pause_duration = 5000;
    boiler_PID.P = 1;
    boiler_PID.I = 1;
    boiler_PID.D = 1;
    pre_infusion_target_pressure = 3.00;
    pre_infusion_run_time = 2;
    pre_infusion_pause_time = 4;
    espresso_pull_time = 28;
    put_data_to_eeprom();
    get_data_from_eeprom();
  }else{
    Serial.println("Initial setup done");
  }
}

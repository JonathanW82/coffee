
void set_temp_targets(){

  if(steam_active){
    boiler_target = steam_boiler_target;
  }else{
    boiler_target = coffee_boiler_target;
  }
}

void update_pid(){

  static float pid_update_timer = 0;

  if (millis() - pid_update_timer < 200) { 
    return;
  }
  pid_update_timer = millis();
  boiler_PID.Compute();
}

void control_boiler(){

  static float last_switch_time = 0;
  const unsigned long cycle_time = 5000;  // Total cycle time in milliseconds

  boiler_PID.min_out = 0;
  boiler_PID.max_out = cycle_time;

  if (millis() - last_switch_time >= cycle_time) {
    last_switch_time = millis();
  }
  

  if ((millis() - last_switch_time) < pid_output) {
    digitalWrite(boiler_ssr, HIGH);  // Turn on SSR
  } else {
    digitalWrite(boiler_ssr, LOW);   // Turn off SSR
  }
}
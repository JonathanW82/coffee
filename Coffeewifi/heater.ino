
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


void control_boiler() {
  static unsigned long last_switch_time = 0;

  // Calculate on-time and off-time based on PID output
  heat_on_time = (pid_output * cycle_time) / 100;
  heat_off_time = cycle_time - heat_on_time;

  // Check where we are in the cycle
  unsigned long elapsed_time = millis() - last_switch_time;

  if (elapsed_time < heat_on_time) {
    digitalWrite(boiler_ssr, HIGH);  // Turn on SSR
  } else if (elapsed_time < cycle_time) {
    digitalWrite(boiler_ssr, LOW);   // Turn off SSR
  } else {
    // Reset cycle
    last_switch_time = millis();
  }
}
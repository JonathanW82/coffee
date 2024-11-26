
void set_temp_targets(){

  if(steam_active){
    boiler_target = steam_boiler_target;
  }else{
    boiler_target = coffee_boiler_target;
  }
}

void update_pid(){

  static float pid_update_timer = 0;

  if (millis() - pid_update_timer < cycle_time) { 
    return;
  }
  pid_update_timer = millis();
  boiler_PID.Compute();
}

void control_boiler() {

  // unsigned long elapsed_time = millis() - last_switch_time;
  // static bool set_state = false;

  heat_on_time = (pid_output * cycle_time) / 100;
  heat_off_time = cycle_time - heat_on_time;

  if (millis() - time_loop_start  > cycle_time) {
    time_loop_start = millis();
  }

  if (millis() - time_loop_start < heat_on_time){                           
      digitalWrite(boiler_ssr, HIGH);  // Turn on SSR
      boiler_pin_status = true;
    }
    else {
      digitalWrite(boiler_ssr, LOW);;
      boiler_pin_status = false;
    }

}
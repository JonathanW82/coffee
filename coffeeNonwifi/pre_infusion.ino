void run_coffee_with_pre_infusion() {
  /* 
    state machine to start coffee pump and valve and when the pressure gets to 3bar a 2 second timer starts
    then it pauses for anoteh 2 seonds then it runs at full 9 bar for a further 28 seconds or an alloted user
    pre set time. the machine then stops and goes back to idle.

  */
    if(steam_active){
      return;
    }

    static unsigned long timer = 0;

    switch(pre_infusion_state){

      case idle_pif:
        if(!auto_active){
            return;
        }
        pre_infusion_state = start_pif;
      break;

      case start_pif:
        auto_pressure_running = true;
        digitalWrite(pump_relay, HIGH);
        current_lcd_display_state = pre_infuse_disp;

        if(pressure_stable){
          pre_infusion_state = infuse_pif;
        }
      break;

      case infuse_pif:
        if(millis() - timer < pre_infusion_run_time * 1000){
          return;
        }
        timer = millis();
        auto_pressure_running = false;
        pressure_stable = false;
        pump_dimmer.set_dimmer_percent(0);
        pre_infusion_state = pause_pif;
      break;

      case pause_pif:
        if(millis() - timer < pre_infusion_pause_time * 1000){
          return;
        }
        timer = millis();
        pre_infusion_state = pull_espresso_pif;
      break;

      case pull_espresso_pif:
        pump_dimmer.set_dimmer_percent(100);
        current_lcd_display_state = run_espresso_disp;
        if(millis() - timer < espresso_pull_time * 1000){
          return;
        }
        timer = millis();
        pre_infusion_state = end_pif;
      break;

      case end_pif:
        auto_pressure_running = false;
        digitalWrite(pump_relay, LOW);
        pump_dimmer.set_dimmer_percent(0);
        current_lcd_display_state = auto_coffee_finish_disp;
        auto_active = false;
        pressure_stable = false;
        if(millis() - timer < 4000){
          return;
        }
        timer = millis();
        pre_infusion_state = idle_pif;
      break;
   
    }
}

void auto_pressure(){

  if(auto_pressure_running){

    static int pwm_percentage = 0;
    const int tolerance = 0.10;       // Hysteresis tolerance
    static unsigned long timer = 0;

    if (pwm_percentage < 0) pwm_percentage = 0;
    if (pwm_percentage > 100) pwm_percentage = 100;

    if (get_water_pressure() < (pre_infusion_target_pressure - tolerance)) {
        // If pressure is below the lower threshold, increase PWM to start the pump
        if(millis() - timer < 1000){
          return;
        }
        timer = millis();
        pump_dimmer.set_dimmer_percent(pwm_percentage += 10); // Start or increase the pump

    } else if (get_water_pressure() > (pre_infusion_target_pressure + tolerance)) {
        // If pressure is above the upper threshold, decrease PWM to slow down the pump
        pump_dimmer.set_dimmer_percent(pwm_percentage -= 0.10); // Reduce the pump output
    } else {
        // Pressure is within the desired range (with hysteresis), maintain the current PWM
        pump_dimmer.set_dimmer_percent(pwm_percentage);
        pressure_stable = true;
    }
  }
}
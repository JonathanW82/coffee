//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Decalcifier Program with countdown timer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CountDown Timer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void boiler_decalcifier(){

  if(!run_boiler_decalcifier){
    return;
  }

  cleaning_program_running = true;
  pinMode (coffee_start_button, OUTPUT);                                    // sets coffee start button to an output as the relay that controlls cleaning programs is connected to the same line so it can cause program errors

  static float decal_state_timer = 0;

  switch(current_boiler_decalcifier_state){

    case idle_dc:
      while(middle){
          middle = false;
          if (millis() - decal_state_timer < 200){
            return;
          }
        decal_state_timer = millis();
        current_boiler_decalcifier_state = flush_dc;
        current_lcd_display_state = flush_dc_disp;
      }
    break;

    case flush_dc:
      digitalWrite(pumpRelay, HIGH);
     
      if(millis() - decal_state_timer < 30000) {
        return;
      }
       decal_state_timer = millis();

       cleaning_cycle++;

       if(cleaning_cycle == 2){
        current_boiler_decalcifier_state = empty_dc;
        current_lcd_display_state = empty_dc_disp;
       }
       if(cleaning_cycle == 3){
        current_boiler_decalcifier_state = end_dc;
        current_lcd_display_state = end_dc_disp;
       }
       if(cleaning_cycle == 4){
        current_boiler_decalcifier_state = flush_dc;
        current_lcd_display_state = flush_dc_disp;
       }
       if(cleaning_cycle > 4){
        current_boiler_decalcifier_state = end_dc;
        current_lcd_display_state = end_dc_disp;
       }
       else{
        current_boiler_decalcifier_state = pause_dc;
        current_lcd_display_state = pause_dc_disp;
       }
    break;

    case pause_dc:
      digitalWrite(pumpRelay, LOW);
    
      if (millis() - decal_state_timer < 300000) {
        return;
      }
      decal_state_timer = millis();
      reset_count_down();
      count_down_reset = true;
      current_boiler_decalcifier_state = flush_dc;
      current_lcd_display_state = flush_dc_disp;
    break;

    case empty_dc:
      digitalWrite(pumpRelay, LOW);

      while(middle)
      {
        middle = false;
        if (millis() - decal_state_timer < 200){
          return;
        }
        decal_state_timer = millis();
        current_boiler_decalcifier_state = flush_dc;
        current_lcd_display_state = flush_dc_disp;
      }
    break;

    case end_dc:
      digitalWrite(pumpRelay, LOW);

      if (millis() - decal_state_timer < 5000) {
        return;
      }
      decal_state_timer = millis();
      cleaning_cycle = 0;
      run_boiler_decalcifier = false;
      current_boiler_decalcifier_state = idle_dc;
      current_lcd_display_state = coffee_idle;
      pinMode (coffee_start_button, INPUT_PULLUP); 
      cleaning_program_running = false;
    break;
  }
}
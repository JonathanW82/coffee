
void group_head_back_flush(){

  if(!run_back_flush){
    return;
  }

  cleaning_program_running = true;
  pinMode (coffee_start_button, OUTPUT);                   // Sets coffee start button as output as relay is connected to start button power line                                                       
  int pause_period = bf_pause_duration * 1000;                   // BFrun will now equal BFpause times 100
  static float prev_flush_time = 0;

  switch(current_back_flush_state){

    case idle_bf:   
      while(middle) 
      { 
        if (millis()- prev_flush_time < 200){
          return;
        }
        prev_flush_time = millis();
        middle = false;
        current_back_flush_state = start_detergent_bf;
        current_lcd_display_state = start_detergent_bf_disp;
        back_flush_cycle_counter++;
      }
    break;

    case start_detergent_bf:
        digitalWrite(pumpRelay, HIGH);
        if (millis() - prev_flush_time < 4000) {
          return;
        }
        prev_flush_time = millis();
        current_back_flush_state = pause_bf;
        current_lcd_display_state = pause_bf_disp;
    break;

    case pause_bf:
        digitalWrite(pumpRelay, LOW);
   
        if(millis() - prev_flush_time < pause_period){
          return;
        }
        prev_flush_time = millis();
        back_flush_cycle_counter ++;

        if(back_flush_cycle_counter <= 4){
          current_back_flush_state = start_detergent_bf;
          current_lcd_display_state = start_detergent_bf_disp;
        }

        if(back_flush_cycle_counter == 5){
          current_back_flush_state = empty_filter_bf;
          current_lcd_display_state = empty_filter_bf_disp;
        }

        if(back_flush_cycle_counter > 5){
          current_back_flush_state = water_flush_bf;
          current_lcd_display_state = water_flush_bf_disp;
        }
        
    break;

    case empty_filter_bf:
      digitalWrite(pumpRelay, LOW);
      
      while (middle)
      {
        middle = false;
        if (millis() - prev_flush_time < 200){
          return;
        }
        prev_flush_time = millis();
        current_back_flush_state = water_flush_bf;
        current_lcd_display_state = water_flush_bf_disp;
      }
    break;

    case water_flush_bf:
        digitalWrite(pumpRelay, HIGH);

        if (millis() - prev_flush_time < 4000) {
          return;
        }
        prev_flush_time = millis();

        if(back_flush_cycle_counter == 11){
          current_back_flush_state = end_bf;
          current_lcd_display_state = end_bf_disp;
        }else{
          current_back_flush_state = pause_bf;
          current_lcd_display_state = pause_bf_disp;
        }
    break;

    case end_bf:
        digitalWrite(pumpRelay, LOW);
     
        if (millis() - prev_flush_time < 8000) {
            return;
        }
        Serial.println(F("Reset to main program"));
        run_back_flush = false;
        back_flush_cycle_counter = 0;
        current_back_flush_state = idle_bf;
        current_lcd_display_state = coffee_idle;
        pinMode (coffee_start_button, INPUT_PULLUP);  
        cleaning_program_running = false;
    break;
  }
}
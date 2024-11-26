
void main_lcd_display_status(){

  switch(current_lcd_display_state){

    case idle:
    break;

    case coffee_idle_disp:
      lcd.setCursor(0, 0);
      lcd.print(F("Boiler "));
      lcd.print(F("    C= "));
      lcd.print(boiler_temp_c);
      lcd.setCursor(19, 0);
      lcd.print(F(" "));
      lcd.setCursor(0, 1);
      lcd.print(F("Target     C= "));
      lcd.print(coffee_boiler_target);
      
      if (coffee_boiler_target > 100) {
        lcd.setCursor(18, 1);
        lcd.print(F("00"));
        lcd.setCursor(20, 1);
        lcd.print(F(" "));
      }
      else if (coffee_boiler_target < 100){
        lcd.setCursor(17, 1);
        lcd.print(F("00"));
        lcd.setCursor(19, 1);
        lcd.print(F("  "));
      }
      if (boiler_temp_c < coffee_boiler_target) {
        lcd.setCursor(0, 2);
        lcd.print(F("Machine HEATING     "));
        lcd.setCursor(0, 3);
        lcd.print(F("                    "));
      }
      else {
        lcd.setCursor(0, 2);
        lcd.print (F("Machine READY !!   "));
        lcd.setCursor(0, 3);
        lcd.print(F("Press for auto-start"));
      }
    break;

    //##################################### make screen for auto mode #####################################

    case run_espresso_disp:
        lcd.setCursor(0, 0);
        lcd.print(F("Making Espresso     "));
        lcd.setCursor(0, 1);
        lcd.print(F("TIME ="));
        lcd.setCursor(6, 1);
        lcd.print(F("  "));
        lcd.setCursor(8, 1);
        count_up_timer();

      if (seconds < 10) lcd.print (F("0"));

        lcd.print(seconds);
        lcd.setCursor(10, 1);
        lcd.print(F("          "));
        lcd.setCursor(0, 2);
        lcd.print(F("Boiler "));
        lcd.print(F("     C="));

      if(boiler_temp_c < 100){
          lcd.setCursor(19, 2);
          lcd.print(F(" "));
      }

        lcd.print(boiler_temp_c);
        lcd.setCursor(0, 3);
    break;

    case pre_infuse_disp:
        lcd.setCursor(0, 0);
        lcd.print(F("Starting PreInfusion"));
        lcd.setCursor(0, 1);
        lcd.print(F("                    "));
        lcd.setCursor(0, 2);
        lcd.print(F("Please wait!        "));
        lcd.setCursor(0, 3);
        lcd.print(F("                    "));
    break;

    case auto_coffee_finish_disp:
        lcd.setCursor(0, 0);
        lcd.print(F("Extraction finished "));
        lcd.setCursor(0, 1);
        lcd.print(F("                    "));
        lcd.setCursor(0, 2);
        lcd.print(F("Please wait!        "));
        lcd.setCursor(0, 3);
        lcd.print(F("                    "));
    break;

    case run_steam_disp:
      lcd.setCursor(0, 0);
      lcd.print(F("Steaming in Progress"));
      lcd.setCursor(0, 1);
      lcd.print(F("C= "));;
      lcd.print(boiler_temp_c);
      lcd.setCursor(10, 1);
      lcd.print(F(" T= "));
      lcd.print(steam_boiler_target);

      if (steam_boiler_target < 100){
        lcd.setCursor(16, 1);
        lcd.print(F("    "));
      }
      else if(steam_boiler_target >100){
        lcd.setCursor(17, 1);
        lcd.print(F("   "));
      }
      
      if (boiler_temp_c < steam_boiler_target) {
        lcd.setCursor(0, 2);
        lcd.print(F("Machine HEATING     "));
        lcd.setCursor(0, 3);
        lcd.print(F("Please Wait!        "));
      }
      else {
        lcd.setCursor(0, 3);
        lcd.print (F("Machine READY !!    "));
        lcd.setCursor(0, 2);
        lcd.print (F("                    "));
      }
    break;

    case run_hot_water_disp:
      lcd.setCursor(0, 0);
      lcd.print(F("DISPENSE HOT WATER  "));
      lcd.setCursor(0, 1);
      lcd.print(F("FROM STEAM WAND TURN"));
      lcd.setCursor(0, 2);
      lcd.print(F("STEAM KNOB          "));
      lcd.setCursor(0, 3);
      lcd.print(F("OR CHECK BUTTONS!!  "));
    break;

    // cleaning programs

    case idle_dc_disp:
      lcd.setCursor(0, 0);
      lcd.print(F("Fill water tank,    "));
      lcd.setCursor(0, 1);
      lcd.print(F("Add Decalcifier then"));
      lcd.setCursor(0, 2);
      lcd.print(F("Click to start      "));
      lcd.setCursor(0, 3);
      lcd.print(F("Boiler C="));
      lcd.print(boiler_temp_c);
      lcd.print(F("      "));
    break;

    case flush_dc_disp:
      Serial.println (F("Cleaning Started"));
      lcd.setCursor(0, 0);
      lcd.print(F("Cleaning Started    "));
      lcd.setCursor(0, 1);
      lcd.print(F("Decalcifier Solution"));
      lcd.setCursor(0, 2);
      lcd.print(F("Boiler C="));
      lcd.print(boiler_temp_c);
      lcd.print(F("     "));
      lcd.setCursor(0, 3);
      lcd.print(F("Please Wait!        "));
    break;

    case pause_dc_disp:
      lcd.setCursor(0, 0);             
      lcd.print(F("** Empty Driptray **"));
      lcd.setCursor(0, 1);
      lcd.print(F("      "));
      lcd.setCursor(6, 1);
      count_down_timer(4, 59); // set timer 5 mins
      lcd.print(minutes);
      lcd.print(":");
      if (seconds < 10) {
        Serial.print("0");
      }
      lcd.print(seconds);
      lcd.setCursor(14, 1);
      lcd.print(F("      "));
      lcd.setCursor(0, 2);
      lcd.print(F("Boiler C="));
      lcd.print(boiler_temp_c);
      lcd.print(F("      "));
      lcd.setCursor(0, 3);
      lcd.print(F("Please Wait!        "));
    break;

    case empty_dc_disp:
      lcd.setCursor(0, 0);
      lcd.print(F("Empty Tank/Driptray "));
      lcd.setCursor(0, 1);
      lcd.print(F("Add Fresh water     "));
      lcd.setCursor(0, 2);
      lcd.print(F("Click to begin      "));
      lcd.setCursor(0, 3);
      lcd.print(F("Last cycle!         "));
    break;

    case end_dc_disp:
      lcd.setCursor(0, 0);
      lcd.print(F("Cleaning Complete   "));
      lcd.setCursor(0, 1);
      lcd.print(F("                    "));
      lcd.setCursor(0, 2);
      lcd.print(F("Boiler C="));
      lcd.print(boiler_temp_c);
      lcd.print(F("      "));
      lcd.setCursor(0, 3);
      lcd.print(F("Please Wait to exit "));
    break;

    // back flush program

    case idle_bf_disp:
      lcd.setCursor(0, 0);
      lcd.print(F("  Fill Portafiller  "));
      lcd.setCursor(0, 1);
      lcd.print(F("   With Detergent   "));
      lcd.setCursor(0, 2);
      lcd.print(F("                    "));
      lcd.setCursor(0, 3);
      lcd.print(F("   Click To Start   "));
    break;

    case start_detergent_bf_disp:
        lcd.setCursor(0, 0);
        lcd.print(F("Back Flush    "));
        lcd.setCursor(0, 1);
        lcd.print(back_flush_cycle_counter);
        lcd.setCursor(2, 1);
        lcd.print(F(" of 11             "));
        lcd.setCursor(0, 2);
        lcd.print(F("Detergent Cycle     "));
        lcd.setCursor(0, 3);
        lcd.print(F("Please Wait!        "));
    break;

    case pause_bf_disp:
        lcd.setCursor(0, 0);
        lcd.print(F("Back Flush Pause!   "));
        lcd.setCursor(0, 1);
        lcd.print(F("                    "));
        lcd.setCursor(0, 2);
        lcd.print(F("                    "));
        lcd.setCursor(0, 3);
        lcd.print(F("Please Wait!        "));
    break;

    case empty_filter_bf_disp:
        lcd.print(F("Empty Portafilter of"));
        lcd.setCursor(0, 1);
        lcd.print(F("     Detergent!     "));
        lcd.setCursor(0, 2);
        lcd.print(F(" Click to Continue  "));
        lcd.setCursor(0, 3);
        lcd.print(F("  With Flush Cycle  "));
    break;

    case water_flush_bf_disp:
        lcd.setCursor(0, 0);
        lcd.print(F("Back Flush    "));
        lcd.setCursor(0, 1);
        lcd.print(back_flush_cycle_counter);
        lcd.setCursor(2, 1);
        lcd.print(F(" of 11             "));
        lcd.setCursor(0, 2);
        lcd.print(F("Flush Cycle         "));
        lcd.setCursor(0, 3);
        lcd.print(F("Please Wait!        "));
    break;

    case end_bf_disp:
        lcd.print(F("Back Flush Finished "));
        lcd.setCursor(0, 1);
        lcd.print(F("                    "));
        lcd.setCursor(0, 2);
        lcd.print(F("                    "));
        lcd.setCursor(0, 3);
        lcd.print(F("Please Wait!        "));
    break;
  }
}
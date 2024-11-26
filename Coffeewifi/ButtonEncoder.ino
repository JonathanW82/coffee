void read_encoder_button() {

  static bool clicked = false;        
  static unsigned long press_time = 0;
  bool current_state = !digitalRead(encoder_switch_pin); 

  if (current_state && !clicked) {
    clicked = true;              
    press_time = millis();        
  }

  if (!current_state && clicked) {
    unsigned long duration = millis() - press_time;

    if (duration >= 3000) {
      clicked = false;  // long click and hold
      delay(2000);      // kick the dog and reset program
    } 
    else if (duration < 1500) {
      middle = true;   // single click
      clicked = false;
    }
  }

    // Prevent other actions if a cleaning program is running
    if (cleaning_program_running) return;

    // Handle middle button actions
    if (middle) {
        middle = false;

        if (page == 1 && menu_item == 1) {
            menu_entered = true;
            steam_active = false;
            current_lcd_display_state = idle;
            menu_item = 2;
            return;
        }

        // Define menu actions using a helper function
        handle_menu_navigation(3);
        handle_menu_navigation(4);
        handle_menu_navigation(5);
        handle_menu_navigation(6);
        handle_menu_navigation(7);
        handle_menu_navigation(8);
        handle_menu_navigation(9);
        handle_menu_navigation(10);
        handle_menu_navigation(11);

        // Special case for menu_item 11
        if (page == 1 && menu_item == 12 && menu_entered) {
            menu_entered = false;
        }
    }
}

// Helper function to handle repetitive menu navigation logic
void handle_menu_navigation(int target_menu_item) {
    if (menu_item == target_menu_item && menu_entered) {
        if (page == 1) {
            page++;
            enter = true;
        } else if (page == 2 && enter) {
            page--;
            enter = false;
        }
    }
}
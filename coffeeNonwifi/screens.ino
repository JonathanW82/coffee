/*
  How to make a new menu item, first go to screens() page then make a menu_item with the nxt coresponding number in the list and call it page 1. if the menu needs to have a sub menu make
  this under page 2. it the new menu item needs to be saved to EEPROM make a new position in memory in the setup with spaces of 8 bytes EG EEPROM.get(0,newitem) EEPROM.get(8,newitem) so
  on so forth, this will allow the program to retrive the data from memory incase of power loss.
  Second go to rotation menu and add the next menu_item using the next coresponding number do this twice for up and down and the last_menu_item, it will become clear when you see it.
  also it will need to have an EEPROM.put to save the integer to memory.
  if the newmenuitem has a sub catagory, page2 then it will also need to be added to the enter pressed, to enter and exit that part of the menu making them global.
*/


void menu_screens()
{
  if (menu_item == 2 && page == 1 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F(" *Cleaning & Setup* "));
    lcd.setCursor(0, 1);
    lcd.print(F("  To Navigate Turn  "));
    lcd.setCursor(0, 2);
    lcd.print(F("Button Left Or Right"));
    lcd.setCursor(0, 3);
    lcd.print(F("Then Click to Enter "));
  }

  if ( menu_item == 3 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set Coffee Target   "));
    lcd.setCursor(0, 1);
    lcd.print(F("Temperature!        "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 3 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("Coffee Target Temp  "));
    lcd.setCursor(0, 1);
    lcd.print(F("C="));
    lcd.setCursor(2, 1);
    lcd.print(coffee_boiler_target);
    lcd.setCursor(7, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));

  }

  if ( menu_item == 4 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set Steam Target    "));
    lcd.setCursor(0, 1);
    lcd.print(F("Temperature!        "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));

  }

  if ( menu_item == 4 && page == 2 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Steam Target Temp   "));
    lcd.setCursor(0, 1);
    lcd.print(F("C="));
    lcd.setCursor(2, 1);
    lcd.print(steam_boiler_target);
    lcd.setCursor(5, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
    if (steam_boiler_target < 100) {
      lcd.setCursor(4, 1);
      lcd.print(F(" "));
    }
  }

  if (menu_item == 5 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("  Back Flush Clean  "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 5 && page == 2 && menu_entered)
  {
    current_back_flush_state = idle_bf;
    current_lcd_display_state = idle_bf_disp;
    run_back_flush = true;
  }

  if (menu_item == 6 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("   Boiler Descale   "));
    lcd.setCursor(0, 1);
    lcd.print(F("Machine Must Be Hot!"));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 6 && page == 2 && menu_entered)
  {
    current_boiler_decalcifier_state = idle_dc;
    current_lcd_display_state = idle_dc_disp;
    run_boiler_decalcifier = true;
  }

  if ( menu_item == 7 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set Back Flush      "));
    lcd.setCursor(0, 1);
    lcd.print(F("Pause/Start Duration"));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 7 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("Pause/Start Duration"));
    lcd.setCursor(0, 1);
    lcd.print(F("Seconds="));
    lcd.setCursor(8, 1);
    lcd.print(bf_pause_duration);
    lcd.setCursor(9, 1);
    lcd.print(F("           "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("1 to 9 seconds Max! "));
  }

  if ( menu_item == 8 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set PID P           "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 8 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("Set PID P           "));
    lcd.setCursor(0, 1);
    lcd.print(F("PID_P  ="));
    lcd.setCursor(8, 1);
    lcd.print(boiler_PID.P);
    lcd.setCursor(9, 1);
    lcd.print(F("           "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
  }

  if ( menu_item == 9 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set PID I           "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 9 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("Set PID I           "));
    lcd.setCursor(0, 1);
    lcd.print(F("PID_I  ="));
    lcd.setCursor(8, 1);
    lcd.print(boiler_PID.I);
    lcd.setCursor(9, 1);
    lcd.print(F("           "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
  }

    if ( menu_item == 10 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set PID D           "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 10 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("Set PID D           "));
    lcd.setCursor(0, 1);
    lcd.print(F("PID_D  ="));
    lcd.setCursor(8, 1);
    lcd.print(boiler_PID.D);
    lcd.setCursor(9, 1);
    lcd.print(F("           "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
  }
  if ( menu_item == 11 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set Pre-infusion    "));
    lcd.setCursor(0, 1);
    lcd.print(F("Pressure            "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 11 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("PreInfusion Pressure"));
    lcd.setCursor(0, 1);
    lcd.print(F("Pressure  = "));
    lcd.setCursor(13, 1);
    lcd.print(pre_infusion_target_pressure);
    lcd.setCursor(18, 1);
    lcd.print(F("       "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
  }

  if ( menu_item == 12 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Set Pre-infusion    "));
    lcd.setCursor(0, 1);
    lcd.print(F("Run time            "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 12 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("PreInfusion         "));
    lcd.setCursor(0, 1);
    lcd.print(F("Run time  = "));
    lcd.setCursor(13, 1);
    lcd.print(pre_infusion_run_time);
    lcd.setCursor(15, 1);
    lcd.print(F("      "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
  }

  if ( menu_item == 13 && page == 1 && menu_entered){
    lcd.setCursor(0, 0);
    lcd.print(F("Set Pre-infusion    "));
    lcd.setCursor(0, 1);
    lcd.print(F("Run time            "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 13 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("PreInfusion         "));
    lcd.setCursor(0, 1);
    lcd.print(F("Pause time = "));
    lcd.setCursor(14, 1);
    lcd.print(pre_infusion_pause_time);
    lcd.setCursor(17, 1);
    lcd.print(F("   "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
  }

  if ( menu_item == 14 && page == 1 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("Set Pre-infusion    "));
    lcd.setCursor(0, 1);
    lcd.print(F("Espresso Pull Time  "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 14 && page == 2 && menu_entered) {
    lcd.setCursor(0, 0);
    lcd.print(F("PreInfusion         "));
    lcd.setCursor(0, 1);
    lcd.print(F("Pull Time = "));
    lcd.setCursor(13, 1);
    lcd.print(espresso_pull_time);
    lcd.setCursor(16, 1);
    lcd.print(F("    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
  }

  if (menu_item == 15 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("  Software Version  "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Enter   "));
  }

  if (menu_item == 15 && page == 2 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("* Software Version *"));
    lcd.setCursor(0, 1);
    lcd.print(F(" CoffeeMenus V-2024 "));
    lcd.setCursor(0, 2);
    lcd.print(F(" 17th November 2024 "));
    lcd.setCursor(0, 3);
    lcd.print(F("   by Jon Wheway    "));
  }

  if (menu_item == 16 && page == 1 && menu_entered)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("    Exit Setup      "));
    lcd.setCursor(0, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("   Click To Exit!   "));
  }
}

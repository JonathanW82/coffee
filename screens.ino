/*
  How to make a new menu item, first go to screens() page then make a menuitem with the nxt coresponding number in the list and call it page 1. if the menu needs to have a sub menu make
  this under page 2. it the new menu item needs to be saved to EEPROM make a new position in memory in the setup with spaces of 8 bytes EG EEPROM.get(0,newitem) EEPROM.get(8,newitem) so
  on so forth, this will allow the program to retrive the data from memory incase of power loss.
  Second go to rotation menu and add the next menuitem using the next coresponding number do this twice for up and down and the lastmenuitem, it will become clear when you see it.
  also it will need to have an EEPROM.put to save the integer to memory.
  if the newmenuitem has a sub catagory, page2 then it will also need to be added to the enter pressed, to enter and exit that part of the menu making them global.
*/


void screens()
{
  if (menuitem == 2 && page == 1 && menuEntered == 1 ) {
    lcd.setCursor(0, 0);
    lcd.print(F(" *Cleaning & Setup* "));
    lcd.setCursor(0, 1);
    lcd.print(F("  To Navigate Turn  "));
    lcd.setCursor(0, 2);
    lcd.print(F("Button Left Or Right"));
    lcd.setCursor(0, 3);
    lcd.print(F("Then Click to Enter "));
  }
  if ( menuitem == 3 && page == 1 && menuEntered == 1)
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

  if (menuitem == 3 && page == 2 && menuEntered == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("Coffee Target Temp  "));
    lcd.setCursor(0, 1);
    lcd.print(F("C="));
    lcd.setCursor(2, 1);
    lcd.print(coffeeBoilerTarget);
    lcd.setCursor(7, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));

  }

  if ( menuitem == 4 && page == 1 && menuEntered == 1)
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

  if ( menuitem == 4 && page == 2 && menuEntered == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("Steam Target Temp   "));
    lcd.setCursor(0, 1);
    lcd.print(F("C="));
    lcd.setCursor(2, 1);
    lcd.print(steamBoilerTarget);
    lcd.setCursor(5, 1);
    lcd.print(F("                    "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
    if (steamBoilerTarget < 100) {
      lcd.setCursor(4, 1);
      lcd.print(F(" "));
    }

  }
  if (menuitem == 5 && page == 1 && menuEntered == 1)
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
  if (menuitem == 5 && page == 2 && menuEntered == 1)
  {
    backflush();
  }
  if (menuitem == 6 && page == 1 && menuEntered == 1)
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
  if (menuitem == 6 && page == 2 && menuEntered == 1)
  {
    cleaning();
  }
  if ( menuitem == 7 && page == 1 && menuEntered == 1)
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

  if (menuitem == 7 && page == 2 && menuEntered == 1) {
    lcd.setCursor(0, 0);
    lcd.print(F("Pause/Start Duration"));
    lcd.setCursor(0, 1);
    lcd.print(F("Seconds="));
    lcd.setCursor(8, 1);
    lcd.print(BFpause);
    lcd.setCursor(9, 1);
    lcd.print(F("           "));
    lcd.setCursor(0, 2);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(F("1 to 9 seconds Max! "));

  }
  if (menuitem == 8 && page == 1 && menuEntered == 1)
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
  if (menuitem == 8 && page == 2 && menuEntered == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("* Software Version *"));
    lcd.setCursor(0, 1);
    lcd.print(F(" CoffeeMenus VER 7  "));
    lcd.setCursor(0, 2);
    lcd.print(F(" 18th November 2019 "));
    lcd.setCursor(0, 3);
    lcd.print(F("   by Jon Wheway    "));
  }
  if (menuitem == 9 && page == 1 && menuEntered == 1)
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

void readEncoderButton() {

  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
      case ClickEncoder::Clicked:
        middle = true;
        break;
      case ClickEncoder::Held:
        ButReset = true;
        break;

    }
  }
  if (cleaningProg == 0) {                                   // if a cleaning program is running stop all other encoder click actions failure to do so will stall the program and kick the dog

    if (middle) //Middle Button is Pressed
    {
      middle = false;
      if (page == 1 && menuitem == 1)
      {
        middle = false;
        menuEntered ++;                                       // menuEntered allows the program to only have one button to enter exit things
        lcd.clear();                                          // so when program is running it can exit to setup via menueEntered also have menuitem++ to forward the next menuitem
        menuitem = 2;
        value = 0;
      }
      if (page == 1 && menuitem == 3 && menuEntered == 1)
      {
        middle = false;
        page ++;
        enter++;

      }
      else if (page == 2 && menuitem == 3 && enter == 1 && menuEntered == 1)
      {
        middle = false;
        page --;
        enter --;

      }

      if (page == 1 && menuitem == 4 && menuEntered == 1)
      {
        middle = false;
        page ++;
        enter++;
      }
      else if  (page == 2 && menuitem == 4 && enter == 1 && menuEntered == 1)
      {
        middle = false;
        page --;
        enter --;
      }
      if (page == 1 && menuitem == 5 && menuEntered == 1)
      {
        middle = false;
        page ++;
        enter++;
      }
      else if (page == 2 && menuitem == 5 && enter == 1 && menuEntered == 1)
      {
        middle = false;
        menuEntered = 0;
      }
      if (page == 1 && menuitem == 6 && menuEntered == 1)
      {
        middle = false;
        page ++;
        enter++;
      }
      else if (page == 2 && menuitem == 6 && enter == 1 && menuEntered == 1)
      {
        middle = false;
        menuEntered = 0;
      }
      if (page == 1 && menuitem == 7 && menuEntered == 1)
      {
        middle = false;
        page ++;
        enter++;
      }
      else if  (page == 2 && menuitem == 7 && enter == 1 && menuEntered == 1)
      {
        middle = false;
        page --;
        enter --;
      }
      if (page == 1 && menuitem == 8 && menuEntered == 1)
      {
        middle = false;
        page ++;
        enter++;
      }
      else if  (page == 2 && menuitem == 8 && enter == 1 && menuEntered == 1)
      {
        middle = false;
        page --;
        enter --;
      }
      if (page == 1 && menuitem == 9 && menuEntered == 1)
      {
        middle = false;
        delay(2000);
      }
    }
  }
}

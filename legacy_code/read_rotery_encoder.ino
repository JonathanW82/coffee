void readRotaryEncoder()
{
  value += encoder->getValue();

  if (value / 4 > last) {
    last = value / 4;
    down = true;
    if (currentTime - previousTime >= 50) {
      currentTime = previousTime;
    }
  } else   if (value / 4 < last) {
    last = value / 4;
    up = true;
    if (currentTime - previousTime >= 50) {
      currentTime = previousTime;
    }
  }
}

void timerIsr() {
  encoder->service();
}  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ROTATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void EncoderRotation() {

  if (up && page == 1 ) {
    up = false;

    if (menuitem == 1)
    {
      menuitem--;
    }
    if (menuitem == 2)
    {
      menuitem--;
    }
    if (menuitem == 3)
    {
      menuitem--;
    }
    if (menuitem == 4)
    {
      menuitem--;
    }
    if (menuitem == 5)
    {
      menuitem--;
    }
    if (menuitem == 6)
    {
      menuitem--;
    }
    if (menuitem == 7)
    {
      menuitem--;
    }
    if (menuitem == 8)
    {
      menuitem--;
    }
    if (menuitem == 9)
    {
      menuitem--;
    }
    lastMenuItem = menuitem;
    menuitem--;

    if (menuitem == 0)
    {
      menuitem = 1;
    }
  }
  else if (up && menuitem == 3 && enter == 1 && page == 2 ) {
    up = false;
    coffeeBoilerTarget--;
    EEPROM.put(26, coffeeBoilerTarget);
    if (coffeeBoilerTarget < 0) {
      coffeeBoilerTarget = 0;
    }
  }
  else if (up && menuitem == 4 && enter == 1 && page == 2 ) {
    up = false;
    steamBoilerTarget--;
    EEPROM.put(20, steamBoilerTarget);
    if (steamBoilerTarget < 0) {
      steamBoilerTarget = 0;
    }
  }
  else if (up && menuitem == 7 && enter == 1 && page == 2 ) {
    up = false;
    BFpause --;
    EEPROM.put(30, BFpause);
    if (BFpause < 0) {
      BFpause = 0;
    }
  }
  if (down && page == 1) //We have turned the Rotary Encoder Clockwise
  {

    down = false;

    if (down && menuitem == 3 && lastMenuItem == 2) {
      menuitem++;

    }
    else if (down && menuitem == 4 && lastMenuItem == 3) {
      menuitem++;

    }
    else if (down && menuitem == 5 &&  lastMenuItem == 4) {
      menuitem++;

    }
    else if (down && menuitem == 6 && lastMenuItem == 5) {
      menuitem++;

    }
    else if (down && menuitem == 7 && lastMenuItem == 6) {
      menuitem++;
    }
    else if (down && menuitem == 8 && lastMenuItem == 7) {
      menuitem++;
    }
    else if (down && menuitem == 9 && lastMenuItem == 8) {
      menuitem++;
    }
    lastMenuItem = menuitem;
    menuitem++;

    if (menuitem == 10)
    {
      menuitem--;
    }
  }
  else if (down && menuitem == 3 && enter == 1 && page == 2 ) {
    down = false;
    coffeeBoilerTarget++;
    EEPROM.put(26, coffeeBoilerTarget);
    if (coffeeBoilerTarget > 125) {
      coffeeBoilerTarget = 125;
    }
  }

  else if (down && menuitem == 4 && enter == 1 && page == 2 ) {
    down = false;
    steamBoilerTarget ++;
    EEPROM.put(20, steamBoilerTarget);
    if (steamBoilerTarget > 140) {
      steamBoilerTarget = 140;
    }
  }
  else if (down && menuitem == 7 && enter == 1 && page == 2 ) {
    down = false;
    BFpause ++;
    EEPROM.put(30, BFpause);
    if (BFpause > 9) {
      BFpause = 9;
    }
  }
}

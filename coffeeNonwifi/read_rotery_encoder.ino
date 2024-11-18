void readRotaryEncoder() {
    static float pre_time = 0;
    value += encoder->getValue();
    int current = value / 4;

    if (current > last || current < last) {
        last = current;
        if (millis() - pre_time >= 50) {
            pre_time = millis();
            (current > last) ? down = true : up = true;
        }
    }
}

void timerIsr() {
    encoder->service();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ROTATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void EncoderRotation() {
    if (up) handleEncoderUp();
    if (down) handleEncoderDown();
}

// Handle Rotary Encoder turning up
void handleEncoderUp() {
    up = false;

    if (page == 1) {
        menuitem--;
        if (menuitem < 1) menuitem = 1; // Prevent underflow
        lastMenuItem = menuitem;
    } else if (page == 2 && enter == 1) {
        switch (menuitem) {
            case 3:
                coffee_boiler_target = adjustValue(coffee_boiler_target, -1, 0, 125);
                break;
            case 4:
                steam_boiler_target = adjustValue(steam_boiler_target, -1, 0, 145);
                break;
            case 7:
                bf_pause_duration = adjustValue(bf_pause_duration, -1, 0, 9);
                break;
            case 8:
                boiler_PID.P = adjustValue(boiler_PID.P, -1, -30, 30);
                break;
            case 9:
                boiler_PID.I = adjustValue(boiler_PID.I, -1, -30, 30);
                break;
            case 10:
                boiler_PID.D = adjustValue(boiler_PID.D, -1, -30, 30);
                break;
        }
        put_data_to_eeprom();
    }
}

// Handle Rotary Encoder turning down
void handleEncoderDown() {
    down = false;

    if (page == 1) {
        menuitem++;
        if (menuitem > 11) menuitem = 11; // Prevent overflow
        lastMenuItem = menuitem;
    } else if (page == 2 && enter == 1) {
        switch (menuitem) {
            case 3:
                coffee_boiler_target = adjustValue(coffee_boiler_target, 1, 0, 125);
                break;
            case 4:
                steam_boiler_target = adjustValue(steam_boiler_target, 1, 0, 145);
                break;
            case 7:
                bf_pause_duration = adjustValue(bf_pause_duration, 1, 0, 9);
                break;
            case 8:
                boiler_PID.P = adjustValue(boiler_PID.P, 1, -30, 30);
                break;
            case 9:
                boiler_PID.I = adjustValue(boiler_PID.I, 1, -30, 30);
                break;
            case 10:
                boiler_PID.D = adjustValue(boiler_PID.D, 1, -30, 30);
                break;
        }
        put_data_to_eeprom();
    }
}

// Utility function to adjust a value within bounds
int adjustValue(int currentValue, int delta, int minValue, int maxValue) {
    currentValue += delta;
    if (currentValue < minValue) currentValue = minValue;
    if (currentValue > maxValue) currentValue = maxValue;
    return currentValue;
}

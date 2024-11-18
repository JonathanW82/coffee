
void read_encoder_movement(){
    static int pos = 0;
    encoder.tick();
    static int new_direction = 0;

    int newPos = encoder.getPosition();
    if (pos != newPos) {
        new_direction = static_cast<int>(encoder.getDirection());
        pos = newPos;
        (new_direction == 1) ? up = true : down = true;
    } 
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
        menu_item--;
        if (menu_item < 1) menu_item = 1; // Prevent underflow
        last_menu_item = menu_item;
    } else if (page == 2 && enter) {
        switch (menu_item) {
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
        menu_item++;
        if (menu_item > 11) menu_item = 11; // Prevent overflow
        last_menu_item = menu_item;
    } else if (page == 2 && enter) {
        switch (menu_item) {
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

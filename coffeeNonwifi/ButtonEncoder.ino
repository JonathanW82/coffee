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

    // Prevent other actions if a cleaning program is running
    if (cleaning_program_running) return;

    // Handle middle button actions
    if (middle) {
        middle = false;

        if (page == 1 && menuitem == 1) {
            menuEntered = true;
            steam_active = false;
            current_lcd_display_state = idle;
            lcd.clear();
            menuitem = 2;
            value = 0;
            return;
        }

        // Define menu actions using a helper function
        handleMenuNavigation(3);
        handleMenuNavigation(4);
        handleMenuNavigation(5);
        handleMenuNavigation(6);
        handleMenuNavigation(7);
        handleMenuNavigation(8);

        // Special case for menuitem 9
        if (page == 1 && menuitem == 11 && menuEntered) {
            menuEntered = false;
        }
    }
}

// Helper function to handle repetitive menu navigation logic
void handleMenuNavigation(int targetMenuItem) {
    if (menuitem == targetMenuItem && menuEntered) {
        if (page == 1) {
            page++;
            enter++;
        } else if (page == 2 && enter == 1) {
            page--;
            enter--;
        }
    }
}

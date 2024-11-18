
void control_commands(char* topic, char* payload, int payload_length) {

    if (str_startwith(topic, "coffee/sub/coffee_boiler_target")) {
        coffee_boiler_target = payloadCovertedToFloat(payload, payload_length);
    }

    if (str_startwith(topic, "coffee/sub/steam_boiler_target")) {
        steam_boiler_target = payloadCovertedToFloat(payload, payload_length);
    }

    if (str_startwith(topic, "coffee/sub/bf_pause_duration")) {
        bf_pause_duration = payloadCovertedToInt(payload, payload_length);
    }

    if (str_startwith(topic, "coffee/sub/PID_P")) {
        boiler_PID.P = payloadCovertedToFloat(payload, payload_length);
    }

    if (str_startwith(topic, "coffee/sub/PID_I")) {
        boiler_PID.I = payloadCovertedToFloat(payload, payload_length);
    }

    if (str_startwith(topic, "coffee/sub/PID_D")) {
        boiler_PID.D = payloadCovertedToFloat(payload, payload_length);
    }

    if (str_startwith(topic, "coffee/sub/reset")) {
        delay(2000);
        return;
    }

    put_data_to_eeprom();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ String comparason ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool str_startwith(char* string, char* start) {
  return string == strstr(string, start);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Covert string to float ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float payloadCovertedToFloat(char* payload, int payload_length) {
  payload[payload_length] = '\0';
  String s = String((char*)payload);                // Convert the incomming string to an float
  float string_to_float = s.toFloat();
  return string_to_float;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Covert string to int ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float payloadCovertedToInt(char* payload, int payload_length) {
  payload[payload_length] = '\0';
  String s = String((char*)payload);                // Convert the incomming string to an int
  int string_to_int = s.toInt();
  return string_to_int;
}
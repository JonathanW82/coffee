class GetSet {
  public:
    GetSet(String topic) {
      internal_topic = topic;
    }
    void set_float(float x, bool j) {
      is_retain(j);
      if (x != float_val || initial_message_send) {
        float_val = x;
        mqtt_client.publish(internal_topic, String(float_val), is_retained, 1);
        initial_message_send = false;
        Serial.println(internal_topic + " " + float_val);
      }
    }
    void set_int(int x, bool j) {
      is_retain(j);
      if (x != int_val || initial_message_send) {
        int_val = x;
        mqtt_client.publish(internal_topic, String(int_val), is_retained, 1);
        initial_message_send = false;
        Serial.println(internal_topic + " " + int_val);
      }
    }
    void set_string(String x, bool j) {
      is_retain(j);
      if (x != string_val || initial_message_send) {
        string_val = x;
        mqtt_client.publish(internal_topic, String(string_val), is_retained, 1);
        initial_message_send = false;
        Serial.println(internal_topic + " " + string_val);
      }
    }
    void set_bool(bool x, bool j) {
      is_retain(j);
      if (x !=  bool_val || initial_message_send) {
        bool_val = x;
        mqtt_client.publish(internal_topic, String(bool_val), is_retained, 1);
        initial_message_send = false;
        Serial.println(internal_topic + " " + bool_val);
      }
    }
    void is_retain(bool j) {
      if (j) is_retained = true;
      else is_retained = false;
    }
    int get() {
      return get_val;
    }
  private:
    int get_val;
    float float_val;
    int int_val;
    String internal_topic;
    String string_val;
    bool bool_val;
    bool is_retained;
    bool initial_message_send = true;
};

// values
GetSet temperature_PID_P(String(main_path) + "temp/boiler_P");
GetSet temperature_PID_I(String(main_path) + "temp/boiler_I");
GetSet temperature_PID_D(String(main_path) + "temp/boiler_D");
GetSet temperature_P_response(String(main_path) + "temp/boiler_P_response");
GetSet temperature_I_response(String(main_path) + "temp/boiler_I_response");
GetSet temperature_D_response(String(main_path) + "temp/boiler_D_response");
GetSet temperature(String(main_path) + "temp/temp");
GetSet temperature_target(String(main_path) + "temp/boiler_target");
GetSet temperature_error(String(main_path) + "temp/temp_error");
GetSet temperature_output(String(main_path) + "temp/pid_output");
GetSet temperature_heat_on(String(main_path) + "temp/heat_time_On");
GetSet temperature_heat_off(String(main_path) + "temp/heat_time_Off");
// states
GetSet temperature_steam_on(String(main_path) + "state/steam_active");
GetSet temperature_heat_pin_state(String(main_path) + "state/heating_output");
GetSet temperature_cleaning_prog(String(main_path) + "state/cleaning_program_active");
GetSet temperature_coffee_button(String(main_path) + "state/coffee_button_state");
GetSet temperature_steam_button(String(main_path) + "state/steam_button_state");
GetSet temperature_water_pump(String(main_path) + "state/water_pump");

void Mqtt_publish() {

    if(no_mqtt_connection){
        return;
    }

    float temp_error_val = boiler_target - boiler_temp_c;

    temperature_PID_P.set_float(boiler_PID.P, true);
    temperature_PID_I.set_float(boiler_PID.I, true);
    temperature_PID_D.set_float(boiler_PID.D, true);
    temperature_P_response.set_float(boiler_PID.P_response, false);
    temperature_I_response.set_float(boiler_PID.I_response, false);
    temperature_D_response.set_float(boiler_PID.D_response, false);
    temperature.set_float(boiler_temp_c, false);
    temperature_target.set_float(boiler_target, true);
    temperature_error.set_float(temp_error_val, false);
    temperature_output.set_float(pid_output, false);
    temperature_heat_on.set_int(heat_on_time, false);
    temperature_heat_off.set_int(heat_off_time, false);
    temperature_heat_pin_state.set_bool(check_pin_state(boiler_ssr), false);
    temperature_steam_on.set_bool(steam_active, false);
    temperature_cleaning_prog.set_bool(cleaning_program_running, false);
    temperature_coffee_button.set_bool(coffee_start_button_state ,false);
    temperature_steam_button.set_bool(steam_button_state ,false);
    temperature_water_pump.set_bool(check_pin_state(pump_relay), false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~ Output pin state ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool check_pin_state(int pin) {
  bool state;
  return state = digitalRead(pin);      // Checks the status of the output pins
}

void publish_hardware_state(){
    // hardware values
    mqtt_client.publish(String(main_path) + "hardware/coffee-start-button-pin", String(coffee_start_button), true, 1);
    mqtt_client.publish(String(main_path) + "hardware/steam-button-pin", String(steam_button), true, 1);
    mqtt_client.publish(String(main_path) + "hardware/encoder-pin-1", String(encoder_pin1), true, 1);
    mqtt_client.publish(String(main_path) + "hardware/encoder-pin-2", String(encoder_pin2), true, 1);
    mqtt_client.publish(String(main_path) + "hardware/encoder-switch-pin", String(encoder_switch_pin), true, 1);
    mqtt_client.publish(String(main_path) + "hardware/boiler-relay-pin", String(boiler_ssr), true, 1);
    mqtt_client.publish(String(main_path) + "hardware/pump-relay-pin", String(pump_relay), true, 1);
}
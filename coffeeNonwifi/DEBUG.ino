void debug() {

  static unsigned long debug_timer = 0;

  if (millis() - debug_timer < 2000) {
    return;
  }
  debug_timer = millis();

  Serial.print("PID-OUTPUT = ");
  Serial.println(pid_output);
  Serial.print("heat_on_time = ");
  Serial.println(heat_on_time);
  Serial.print("heat_off_time = ");
  Serial.println(heat_off_time);
  Serial.print("temp_c = ");
  Serial.println(boiler_temp_c);
  Serial.print("boiler-target = ");
  Serial.println(boiler_target);
  Serial.print("boiler-heater = ");
  Serial.println(boiler_pin_status);
  Serial.print("PID_P = ");
  Serial.println(boiler_PID.P);
  Serial.print("PID_P__response = ");
  Serial.println(boiler_PID.P_response);
  Serial.print("PID_I = ");
  Serial.println(boiler_PID.I);
  Serial.print("PID_I_response = ");
  Serial.println(boiler_PID.I_response);
  Serial.print("PID_D = ");
  Serial.println(boiler_PID.D);
  Serial.print("PID_D_response = ");
  Serial.println(boiler_PID.D_response);
}

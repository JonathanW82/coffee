void setUpMqtt() {
  mqtt_client.begin(MQTT_HOST, 1883, www_client);
  mqtt_client.onMessageAdvanced(mqtt_message);
}

char path[200];
char* construct_path(char* endpoint) {
  // macaddress/sensor_1;
  char subpath[200];
  strcpy(subpath, MACADDRESS);
  strcat(subpath, "/");
  strcat(subpath, SUBSCRIBE_PATH);
  strcat(subpath, endpoint);
  strcpy(path, subpath);
  return path;
}

void maintain_mqtt_connection() {

  if(no_mqtt_connection){
    return;
  }
  
  static unsigned long last_connection_attempt = 0;
  static int mqtt_connection_attempt = 0;
  if (mqtt_client.connected()) {
    return;
  }
  // only attempt to connect once a second
  if (millis() - last_connection_attempt < 1000) {
    return;
  }
  last_connection_attempt = millis();
  Serial.print(F("Connecting to MQTT host \""));
  Serial.print(MQTT_HOST);
  Serial.print(F("\" ... "));
  if (!mqtt_client.connect(DEVICE_NAME)) {
    Serial.println(F(" connection failed."));
    mqtt_connection_attempt++;
    if(mqtt_connection_attempt >= 2) no_mqtt_connection = true;
    return;
  }
  Serial.println(F("success!"));
  
  mqtt_client.subscribe(construct_path("coffee_boiler_target"));
  mqtt_client.subscribe(construct_path("steam_boiler_target"));
  mqtt_client.subscribe(construct_path("bf_pause_duration"));
  mqtt_client.subscribe(construct_path("PID_P"));
  mqtt_client.subscribe(construct_path("PID_I"));
  mqtt_client.subscribe(construct_path("PID_D"));
  mqtt_client.subscribe(construct_path("reset"));

  snprintf(main_path, sizeof(main_path), "%s%s/", PUBLISH_PATH, MACADDRESS);
  publish_hardware_state();
}

void mqtt_message(MQTTClient* client, char topic[], char payload[], int payload_length) {
  Serial.print("message recieved: ");
  Serial.print(topic);
  Serial.print(" = ");
  Serial.println(payload);
  control_commands(topic, payload, payload_length);
}
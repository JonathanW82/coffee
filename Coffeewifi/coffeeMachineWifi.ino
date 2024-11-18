#include <LiquidCrystal_I2C.h>
#include <SparkFun_External_EEPROM.h>
#include <Adafruit_SleepyDog.h>
#include <OneWire.h>
#include <Wire.h>
#include <max6675.h>
#include <PID.h>
#include <MQTT.h>
#include <MQTTClient.h>
#include <WiFiNINA.h>
#include <RotaryEncoder.h>
#include "credentials.h"

#define WIFI_NAME WIFI_SSID
#define WIFI_PASSWORD WIFI_PASSWORD
#define MQTT_HOST "192.168.1.225"
#define SUBSCRIBE_PATH "coffee/sub/"
#define DEVICE_NAME "coffee-machine"
#define PUBLISH_PATH "coffee/"
char MACADDRESS[18];  // 00:00:00:00:00:00
int status = WL_IDLE_STATUS;
MQTTClient mqtt_client;
WiFiClient www_client;
bool no_wifi_connection = false;
bool no_mqtt_connection = false;

ExternalEEPROM EEPROM;     

const byte button_ON = 0;
const byte button_OFF = 1;

byte menu_item = 1;
byte page = 1;
byte last_menu_item = 1;
bool menu_entered = false;
bool enter = false;                            

float coffee_boiler_target = 0;
float steam_boiler_target = 0;
bool steam_active = false;

int minutes = 0;
int seconds = 0;

// cound down timers
int delta_min_cd = 0; 
int delta_sec_cd = 0;
bool initialized_count_down = false;

int current_min_cu = 0;
int current_sec_cu = 0;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ screen status and timer declarations for cleaning~~~~~~~~~~~~
bool cleaning_program_running = false;

int cleaning_cycle = 0;
bool run_boiler_decalcifier = false;
enum boiler_decalcifier_state {idle_dc, pause_dc, decalcifying_dc, flush_dc, empty_dc, end_dc};
boiler_decalcifier_state current_boiler_decalcifier_state; 

int  bf_pause_duration = 0;
int back_flush_cycle_counter = 0; 
bool run_back_flush = false;
enum back_flush_state{idle_bf, pause_bf, start_detergent_bf, empty_filter_bf, water_flush_bf, end_bf};
back_flush_state current_back_flush_state;

enum lcd_display_state{idle, idle_dc_disp, pause_dc_disp, decalcifying_dc_disp, flush_dc_disp, empty_dc_disp, end_dc_disp,
idle_bf_disp, pause_bf_disp, start_detergent_bf_disp, empty_filter_bf_disp, water_flush_bf_disp, end_bf_disp,
coffee_idle, run_espresso, run_steam, run_hot_water};
lcd_display_state current_lcd_display_state;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main Machine buttons pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const byte coffee_start_button = 5;           
const byte steam_button = 9;                 
byte coffee_start_button_state = 0;
byte steam_button_state = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Encoder Pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define encoder_pin1 A2
#define encoder_pin2 A3
#define encoder_switch_pin 8

RotaryEncoder encoder(encoder_pin1, encoder_pin2, RotaryEncoder::LatchMode::TWO03);

bool up = false;
bool down = false;
bool middle = false;
bool call_reset = false;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Realy ouput Pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const byte pump_relay = 2;
const byte boiler_ssr = 6;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Temp sensor  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const byte thermoDO = 3;
const byte thermoCS = 7;
const byte thermoCLK = 10;

MAX6675 boiler_thermocouple(thermoCLK, thermoCS, thermoDO);

float boiler_temp_c = 0;

void get_boiler_temp(){
  static float boiler_temp_read_timer = 0;

  if(millis() - boiler_temp_read_timer < 1000){
    return;
  }
  boiler_temp_read_timer = millis();
  boiler_temp_c = boiler_thermocouple.readCelsius();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PID ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float pid_output = 0;
float boiler_target = 0;

PID boiler_PID(&boiler_temp_c, &pid_output, &boiler_target, 1, 1, 1); // Decalre the PID classes

unsigned long heat_on_time = 0;
unsigned long heat_off_time = 0;
long cycle_time = 5000;                          // Total cycle time in milliseconds

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LiquidCrystal_I2C lcd(0x3F,20,4);                // set the LCD address to 0x3F or 0x27 depending what display using for a 16 chars 2 line display

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char main_path[200];

void setup() {

  Serial.begin(9600);                            // Initialise Serial
  lcd.begin(20, 4);                              // initialize the lcd for 16 chars 2 lines
  lcd.backlight();                               // Turns backlight LCD on
  Wire.begin();                                  // Enable wire

  pinMode(pump_relay, OUTPUT);                   // sets the relay pins to outputs digitally written to Low
  digitalWrite (pump_relay, LOW);
  pinMode(boiler_ssr, OUTPUT);
  digitalWrite (boiler_ssr, LOW);

  enable_eeprom();                               // enable external eeprom chip                      
  get_data_from_eeprom();

  pinMode (coffee_start_button, INPUT_PULLUP);   // Sets button pins to inputs with arduino internal pullup resistors activated
  pinMode (steam_button, INPUT_PULLUP);

  pinMode(encoder_switch_pin, INPUT_PULLUP);     // set encoder button state

  boiler_PID.init();                             // Initialise Pid for temp and hum
  boiler_PID.min_out = 0;
  boiler_PID.max_out = 100;

  wifi();

  int watchdogTimeout = Watchdog.enable(1000);   // enable watchdog and wait 1 seconds before reset
}


//############################################################### LOOP ######################################################################

void loop() {

  Watchdog.reset();              // Reset Watchdog and reset precesor if crashed or inactive                                            
  maintain_mqtt_connection();    // ensure the mqtt is connected
  check_pannel_button_status();  // check if the panel buttons have changed state
  check_machine_status();        // check what the machine state is currently and display the correct screen and set the target temps 
  set_temp_targets();            // check temp tragets in case the target temp has chaned due to machine being in steam or coffee mode
  get_boiler_temp();             // get current boiler temperature
  update_pid();                  // update the pid calculations
  control_boiler();              // update the boiler solid state relay
  read_encoder_button();         // read the encoder and check for changes
  read_encoder_movement();
  menu_screens();                // set the menu screens
  boiler_decalcifier();          // start cleaning programs if enabled
  group_head_back_flush();
  mqtt_client.loop();
}


bool check_pannel_button_status(){
  coffee_start_button_state = digitalRead(coffee_start_button); // get the main panel button states 
  steam_button_state = digitalRead(steam_button);
  return true;
}

bool check_machine_status(){

  if (!menu_entered) {
    
    if (coffee_start_button_state == button_OFF && steam_button_state == button_OFF) {
       current_lcd_display_state = coffee_idle;
       steam_active = false;
       reset_count_up_timer();
    }

    if (coffee_start_button_state == button_ON && steam_button_state == button_OFF) {
       current_lcd_display_state = run_espresso;
       steam_active = false;
    }

    if (steam_button_state == button_ON && coffee_start_button_state == button_OFF ) {
       current_lcd_display_state = run_steam;
       steam_active = true;
    }

    if (coffee_start_button_state == button_ON && steam_button_state == button_ON ) {
       current_lcd_display_state = run_hot_water;
       steam_active = true;
    }
  }
  return true;
}
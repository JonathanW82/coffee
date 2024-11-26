#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <Wire.h>
#include <max6675.h>
#include <PID.h>
#include <RotaryEncoder.h>
#include "credentials.h"
#include <avr/wdt.h> 
#include <EEPROM.h>
#include <water_pressure.h>
#include <pwm_ac_dimmer.h>

bool initial_set_up = false;  

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
bool auto_active = false;

int minutes = 0;
int seconds = 0;

// cound down timers
int delta_min_cd = 0; 
int delta_sec_cd = 0;
bool initialized_count_down = false;

int current_min_cu = 0;
int current_sec_cu = 0;

float prev_temp_error_val = -1;
float prev_boiler_PID_P = -1;
float prev_boiler_PID_I = -1;
float prev_boiler_PID_D = -1;
float prev_boiler_PID_P_response = -1;
float prev_boiler_PID_I_response = -1;
float prev_boiler_PID_D_response = -1;
float prev_boiler_temp_c = -1;
float prev_boiler_target = -1;
float prev_pid_output = -1;
float prev_heat_on_time = -1;
float prev_heat_off_time = -1;
bool prev_heater_pin_state;
bool prev_steam_active;
bool prev_cleaning_program_running;
bool prev_coffee_start_button_state;
bool prev_steam_button_state;
bool prev_water_pump;

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
coffee_idle_disp, run_espresso_disp, run_steam_disp, run_hot_water_disp, pre_infuse_disp, auto_coffee_finish_disp};
lcd_display_state current_lcd_display_state;

enum pre_infusion_state_machine{idle_pif, start_pif, infuse_pif, pause_pif, pull_espresso_pif, end_pif};
pre_infusion_state_machine pre_infusion_state;

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Water pressure Pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pressure_sensor_Cls water_pressure;
byte water_pressure_pin = A0;
bool auto_pressure_running = false;
bool pressure_stable = false;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Water pump dimmer Pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pwm_ac_dimmer_Cls pump_dimmer;
byte pump_dimmer_pin = 11;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Realy ouput Pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const byte pump_relay = 2;
const byte boiler_ssr = 6;

bool boiler_pin_status = false;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Temp sensor  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const byte thermoDO = 3;
const byte thermoCS = 7;
const byte thermoCLK = 10;

MAX6675 boiler_thermocouple(thermoCLK, thermoCS, thermoDO);

float boiler_temp_c = 0;

void get_boiler_temp(){
  static unsigned long boiler_temp_read_timer = 0;

  if(millis() - boiler_temp_read_timer < 1000){
    return;
  }
  boiler_temp_read_timer = millis();
 // boiler_temp_c = boiler_thermocouple.readCelsius();
  boiler_temp_c = 85;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PID ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float pid_output = 0;
float boiler_target = 0;

PID boiler_PID(&boiler_temp_c, &pid_output, &boiler_target, 1, 1, 1); // Decalre the PID classes

float heat_on_time = 0;
float heat_off_time = 0;
float cycle_time = 10000;                          // Total cycle time in milliseconds

unsigned long time_loop_start = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Pre Infustion  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

float pre_infusion_target_pressure = 0;
int pre_infusion_run_time = 0;
int pre_infusion_pause_time = 0;
int espresso_pull_time = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LiquidCrystal_I2C lcd(0x3F,20,4);                // set the LCD address to 0x3F or 0x27 depending what display using for a 16 chars 2 line display

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
void setup() {

  Serial.begin(9600);                            // Initialise Serial
  lcd.begin(20, 4);                              // initialize the lcd for 16 chars 2 lines
  lcd.backlight();                               // Turns backlight LCD on
  Wire.begin();                                  // Enable wire

  pinMode(pump_relay, OUTPUT);                   // sets the relay pins to outputs digitally written to Low
  digitalWrite (pump_relay, LOW);
  pinMode(boiler_ssr, OUTPUT);
  digitalWrite (boiler_ssr, LOW);

  //enable_eeprom();                               // enable external eeprom chip                      
  get_data_from_eeprom();
  check_initial_set_up();

  pinMode (coffee_start_button, INPUT_PULLUP);   // Sets button pins to inputs with arduino internal pullup resistors activated
  pinMode (steam_button, INPUT_PULLUP);

  pinMode(encoder_switch_pin, INPUT_PULLUP);     // set encoder button state

  water_pressure.pressure_pin = water_pressure_pin;
  water_pressure.voltage_offset = 0.454;
  water_pressure.init();

  pump_dimmer.pwm_pin = pump_dimmer_pin;
  pump_dimmer.init();
  pump_dimmer.set_dimmer_percent(0);

  pre_infusion_state = idle_pif;
  current_boiler_decalcifier_state = idle_dc;
  current_back_flush_state = idle_bf;

  boiler_PID.init();                             // Initialise Pid for temp and hum
  boiler_PID.min_out = 0;
  boiler_PID.max_out = 100;

  //wdt_enable(WDTO_1S);  
  //int watchdogTimeout = Watchdog.enable(1000);   // enable watchdog and wait 1 seconds before reset
}


void check_pannel_button_status(){
  if(cleaning_program_running){
    return;
  }

  if(auto_active){
    return;
  }

  coffee_start_button_state = digitalRead(coffee_start_button); // get the main panel button states 
  steam_button_state = digitalRead(steam_button);
}

void check_machine_status(){

    if (menu_entered) {
      return;
    }

    if(auto_active){
      return;
    }
    
    if (coffee_start_button_state == button_OFF && steam_button_state == button_OFF) {
       current_lcd_display_state = coffee_idle_disp;
       steam_active = false;
       reset_count_up_timer();
    }

    if (coffee_start_button_state == button_ON && steam_button_state == button_OFF) {
       current_lcd_display_state = run_espresso_disp;
       steam_active = false;
    }

    if (steam_button_state == button_ON && coffee_start_button_state == button_OFF ) {
       current_lcd_display_state = run_steam_disp;
       steam_active = true;
    }

    if (coffee_start_button_state == button_ON && steam_button_state == button_ON ) {
       current_lcd_display_state = run_hot_water_disp;
       steam_active = true;
    }
}

float get_water_pressure(){
  water_pressure.read_pressure_sensor();
  return water_pressure.pressure_value_bar;
}


//############################################################### LOOP ######################################################################

void loop() {
    //wdt_reset(); 
  //Watchdog.reset();              // Reset Watchdog and reset precesor if crashed or inactive                                            
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
  run_coffee_with_pre_infusion();
  auto_pressure();
  //debug();

}
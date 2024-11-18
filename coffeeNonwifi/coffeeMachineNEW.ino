#include <TimerOne.h>
#include <ClickEncoder.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <avr/wdt.h>                                          // Watchdog Lib
#include <OneWire.h>
#include <Wire.h>
#include <max6675.h>
#include <PID.h>
// #include <TimeLib.h>
// #include <Time.h>

const byte button_ON = 0;
const byte button_OFF = 1;

byte menuitem = 1;
byte page = 1;
byte lastMenuItem = 1;
bool menuEntered = false;
byte enter = 0;                                                // stops functions that are not cleaning
bool cleaning_program_running = false;
int  bf_pause_duration = 0;                                              // Back flush pause/run duration
float coffee_boiler_target = 0;
float steam_boiler_target = 0;
bool steam_active = false;

bool up = false;
bool down = false;
bool middle = false;
bool ButReset = false;

ClickEncoder *encoder;
int16_t last, value;

int minute = 0;
int seconds = 0;

int delta_min_cd = 0; 
int delta_sec_cd = 0;
bool initialized_count_down = false;

int current_min_cu = 0;
int current_sec_cu = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ screen status and timer declarations for cleaning~~~~~~~~~~~~

int cleaning_cycle = 0;
bool run_boiler_decalcifier = false;
enum boiler_decalcifier_state {idle_dc, pause_dc, decalcifying_dc, flush_dc, empty_dc, end_dc};
boiler_decalcifier_state current_boiler_decalcifier_state; 

int back_flush_cycle_counter = 0; 
bool run_back_flush = false;
enum back_flush_state{idle_bf, pause_bf, start_detergent_bf, empty_filter_bf, water_flush_bf, end_bf};
back_flush_state current_back_flush_state;

enum lcd_display_state{idle, idle_dc_disp, pause_dc_disp, decalcifying_dc_disp, flush_dc_disp, empty_dc_disp, end_dc_disp,
idle_bf_disp, pause_bf_disp, start_detergent_bf_disp, empty_filter_bf_disp, water_flush_bf_disp, end_bf_disp,
coffee_idle, run_espresso, run_steam, run_hot_water};
lcd_display_state current_lcd_display_state;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main Machine buttons pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const byte coffee_start_button = 5;                                    // using byte instead of int. int uses 2 bytes of memory
const byte steam_button = 9;                                          // byte only uses 1 byte of memory
byte coffee_start_button_state = 0;
byte steam_button_state = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Realy ouput Pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const byte pumpRelay = 2;
const byte boiler_ssr = 6;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Temp sensor  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const byte thermoDO = 3;
const byte thermoCS = 7;
const byte thermoCLK = 10;

MAX6675 boiler_thermocouple(thermoCLK, thermoCS, thermoDO);

float boiler_temp_c = 0;

float get_boiler_temp(){
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);      // Set the LCD I2C address
// set the LCD address to 0x3F or 0x27 depending what display using for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup() {

  Serial.begin(9600);                                             // Initialise Serial
  lcd.begin(20, 4);                                               // initialize the lcd for 16 chars 2 lines
  lcd.backlight();                                                // Turns backlight LCD on
  
  pinMode(pumpRelay, OUTPUT);                                     // sets the relay pins to outputs digitally written to Low
  digitalWrite (pumpRelay, LOW);
  pinMode(boiler_ssr, OUTPUT);
  digitalWrite (boiler_ssr, LOW);

  get_data_from_eeprom();

  pinMode (coffee_start_button, INPUT_PULLUP);                         // Sets button pins to inputs with arduino internal pullup resistors activated
  pinMode (steam_button, INPUT_PULLUP);

  encoder = new ClickEncoder(A1, A0, A2);                         // set analog channel 0,1,2 for use with the rotery encoder
  encoder->setAccelerationEnabled(false);                         // disable encode acelleration

  Timer1.initialize(1000);                                        // timer iterupt for the rotery encoder
  Timer1.attachInterrupt(timerIsr);

  boiler_PID.init();                           // Initialise Pid for temp and hum

  last = encoder->getValue();

  wdt_enable(WDTO_1S);                                            // enable watchdog and wait 1 seconds before reset

}


//############################################################### LOOP ######################################################################

void loop() {

  wdt_reset();                                                       // Reset Watchdog and reset precesor if crashed or inactive
  coffee_start_button_state = digitalRead(coffee_start_button);
  steam_button_state = digitalRead(steam_button);
  Reset();
  readRotaryEncoder();
  menu_screens();
  timerIsr();
  get_boiler_temp();
  boiler_decalcifier();
  group_head_back_flush();
  set_temp_targets();
  update_pid();
  control_boiler();
 
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ General Machine Status ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  if (!menuEntered) {
    
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
}

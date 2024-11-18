#include <TimerOne.h>
#include <ClickEncoder.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <avr/wdt.h>                                          // Watchdog Lib
#include <TSIC.h>
#include <OneWire.h>
#include <Wire.h>
#include <TimeLib.h>
#include <Time.h>
#include "Countimer.h"

#define ESPRESSO_TEMP_ADDRESS 12

int eeAddress = 0;                                            // Adress to start saving to EEprom

byte menuitem = 1;
byte page = 1;
byte lastMenuItem = 1;
byte menuEntered = 0;
byte enter = 0;                                                // stops functions that are not cleaning
byte cleaningProg = 0;
int  BFpause = 0;                                              // Back flush pause/run duration
byte bfTag = 0;
byte ScreenTransition = 0;
float coffeeBoilerTarget = 0;
int  steamBoilerTarget = 0;
byte steamActive = 0;
byte steamSwing = 0;

boolean up = false;
boolean down = false;
boolean middle = false;
boolean ButReset = false;

ClickEncoder *encoder;
int16_t last, value;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ screen status and timer declarations for cleaning~~~~~~~~~~~~
byte cleaningstatus = 0;                                          // used to count how many times the cleaning program has implimented
Countimer tDown;
time_t seconds = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Millis statment declarations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned long currentTime;
unsigned long previousTime = 0;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main Machine buttons pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const byte coffeeStartbut = 5;                                    // using byte instead of int. int uses 2 bytes of memory
const byte steamBut = 9;                                          // byte only uses 1 byte of memory
byte coffeestartbutState = 0;
byte steambutState = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Realy ouput Pins ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const byte pumpRelay = 2;
const byte Boiler  = 6;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  Temp sensor  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TSIC coffeeSensor(7);                                                // only Signalpin, VCCpin unused by default

// Temperature reading saved as a float
uint16_t temperature = 0;
float Temperatur_C = 0;


// connected to dispence switch
float coffeeTemp_c = 0;
byte coffeetempState = 0;
float coffeetempVal = 0;

// connected to steam switch
float steamTemp_c = 0;
byte steamtempState = 0;
float steamtempVal = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PID ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define PGAIN_ADR 0
#define IGAIN_ADR 4
#define DGAIN_ADR 8

#define PID_UPDATE_INTERVAL 200 // milliseconds

float targetTemp; //current temperature goal
float heatPower; // 0 - 1000  milliseconds on per second

unsigned long lastPIDTime;  // most recent PID update time in ms

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Lcd Display ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);      // Set the LCD I2C address
// set the LCD address to 0x3F or 0x27 depending what display using for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup() {

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ countdown Timer setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  tDown.setCounter(0, 5, 0, tDown.COUNT_DOWN, tDownComplete);     // countdown timer setup for 5 minutes, used in the cleaning program
  tDown.setInterval(clocklcd, 1000);                              // counting down at 1 second intival millis reference

  Serial.begin(9600);                                             // Initialise Serial
  lcd.begin(20, 4);                                               // initialize the lcd for 16 chars 2 lines
  lcd.backlight();                                                // Turns backlight LCD on
  pinMode(pumpRelay, OUTPUT);                                     // sets the relay pins to outputs digitally written to Low
  digitalWrite (pumpRelay, LOW);
  pinMode(Boiler, OUTPUT);
  digitalWrite (Boiler, LOW);

  EEPROM.get(26, coffeeBoilerTarget);                             // EEprom to get inital Coffee temp Traget from position 26
  EEPROM.get(20, steamBoilerTarget);                              // EEprom to get initial Steam temp Target from position 20
  EEPROM.get(30, BFpause);


  pinMode (coffeeStartbut, INPUT_PULLUP);                         // Sets button pins to inputs with arduino internal pullup resistors activated
  pinMode (steamBut, INPUT_PULLUP);

  setupPID(PGAIN_ADR, IGAIN_ADR, DGAIN_ADR );                     // Send addresses to the PID module
  setupSerialInterface();
  targetTemp = readFloat(ESPRESSO_TEMP_ADDRESS);
  lastPIDTime = millis();

  coffeeSensor.getTemperature(&temperature);                      // Get initial Boiler temp data

  encoder = new ClickEncoder(A1, A0, A2);                         // set analog channel 0,1,2 for use with the rotery encoder
  encoder->setAccelerationEnabled(false);                         // disable encode acelleration

  Timer1.initialize(1000);                                        // timer iterupt for the rotery encoder
  Timer1.attachInterrupt(timerIsr);

  last = encoder->getValue();

  wdt_enable(WDTO_1S);                                            // enable watchdog and wait 1 seconds before reset

}

void setTargetTemp(float t) {                                    
  targetTemp = t;
  coffeeBoilerTarget = t;
  writeFloat(t, ESPRESSO_TEMP_ADDRESS);
  EEPROM.put(26, coffeeBoilerTarget);
}

float getTargetTemp() {

  //return targetTemp;
  return coffeeBoilerTarget;
}

//############################################################### LOOP ######################################################################

void loop() {

  wdt_reset();                                                       // Reset Watchdog and reset precesor if crashed or inactive
  Reset();
  readRotaryEncoder();
  screens();
  timerIsr();
  currentTime = millis();
  seconds = now();                                                   // initialises the seconds counter for esspresso screen
  coffeestartbutState = digitalRead(coffeeStartbut);
  steambutState = digitalRead(steamBut);
  updateSerialInterface();
  updateTempSensor();
  Debug();

  if (ScreenTransition == 0) {                                        // stops the menu being entered while coffee making is in progress
    readEncoderButton();
  }

  if (menuEntered == 0) {}                                            // if the main screen is active (menuEntered == 0) then turn off reading the rotery encoder
  else {
    EncoderRotation();
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Heater Element Global Control ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  if (steamActive == 0)
  {
    if (millis() < lastPIDTime) {
      lastPIDTime = 0;
    }
    if ((millis() - lastPIDTime) > PID_UPDATE_INTERVAL) {
      lastPIDTime +=  PID_UPDATE_INTERVAL;
      heatPower = updatePID(targetTemp, getFreshTemp());
      setHeatPowerPercentage(heatPower);
    }
    updatecoffeeHeater();
  }
  else
  {
    updateSteamheater();
    }
  
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ General Machine Status ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  if (menuEntered == 0) {

    if (coffeestartbutState == HIGH && steambutState == HIGH) {
      coffeescreen();
      ScreenTransition = 0;
      steamActive = 0;

    }
    if (coffeestartbutState == LOW && steambutState == HIGH) {
      espressomakescreen();
      ScreenTransition = 1;
      steamActive = 0;

    }
    if (steambutState == LOW && coffeestartbutState == HIGH ) {
      steamscreen();
      steamActive = 1;
    }

    if (coffeestartbutState == LOW && steambutState == LOW ) {
      hotWater();
      steamActive = 1;
    }
  }
}

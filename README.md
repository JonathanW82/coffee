
<h1 align="center">
   <img src="https://github.com/jonathanw82/Coffee/blob/master/images/repoimage.jpg" alt="Coffee"/>
 </h1>
 

# Gaggia Classic Espresso Machine Upgrade.
These files make up a complete program to run on an Arduino with a rotary encoder and a solid-state relay,
The menu system enables you to change target temperatures and access cleaning programs, while the PID controls the heater 
whether to heat coffee or produce steam. The program is based on the barebones PID for espresso [here](https://playground.arduino.cc/Main/BarebonesPIDForEspresso/) and inspiration for the menu system was loosely taken from the Arduino Rotary Encoder Menu [here](http://educ8s.tv/arduino-rotary-encoder-menu/)


#### The users goals of this system are:
* An easy to navigate menu.
* Low power consumption.
* More features.
* Create great Coffee Fast.


#### I think this system gives this to the user because:
* The rotery encoder is easy to use with one button click.
* The display gives realtime data such as water temperature.
* The system has built-in semiautomatic cleaning programs such as backflush and descale.

 
 ## Features:
* Rotery encoder for navigation.
* Lcd display for real time data.
* built-in relays for semiautomation.
* Easy to user cleaning programs.
  
  
### Nice to have
* Glycerine filled pressure gauge for stable pressure readings.
* Higher maximum temperature, water temp sensor.(Current model only 150c.
* Flow meter to dispence exact abounds of water.
 
 
## Parts:
* 1x Gaggia Classic pre 2009 with 3 way valve.
* 1x Arduino Nano flashed with Uno firmware [here](https://uk.rs-online.com/web/p/processor-microcontroller-development-kits/1927586?cm_mmc=UK-PLA-DS3A-_-google-_-CSS_UK_EN_Semiconductors_Whoop-_-Processor+%26+Microcontroller+Development+Kits_Whoop-_-1927586&matchtype=&aud-827186183886:pla-365806887317&gclid=CjwKCAjw4MP5BRBtEiwASfwAL1V2_ZPV5CFIHVJwqMWt440qj7niZnY0ZLb_qy5z4QArddATyjpiUBoCdTcQAvD_BwE&gclsrc=aw.ds)
* 2x Arduino 240V 220V AC Mains Sensor Opto Isolator Optocoupler 5V 3.3V 1 Channel NN015 [here](https://webshop2you.com/nl/product/arduino-240v-220v-ac-mains-sensor-opto-isolator-optocoupler-5v-3-3v-1-channel-nn015/)
* 1x TSIC 306 temperature sensor [here](https://uk.rs-online.com/web/p/temperature-sensors-humidity-sensors/1218022?cm_mmc=UK-PLA-DS3A-_-google-_-CSS_UK_EN_Semiconductors_Whoop-_-Temperature+Sensors+%26+Humidity+Sensors_Whoop-_-1218022&matchtype=&pla-304991652191&gclid=CjwKCAjw4MP5BRBtEiwASfwAL1Mm6vmGNY1QsjenYBxqMryW4MPXaiZl-vVgC9BdH6MISGYiW1tLMRoCfooQAvD_BwE&gclsrc=aw.ds)
* 1x KY-040 Rotery Encoder [here](https://www.cricklewoodelectronics.com/Rotary-encoder-module-for-Arduino-KY-040.html?gclid=EAIaIQobChMIybWK-_Pl6QIVS7DtCh2XhAvKEAQYAyABEgKdBPD_BwE) 
* 1x Lcd 2004i2c Display [here](https://www.q26.co.uk/lcd-i2c-display-1602-or-2004-blue-on-white-ideal-for-arduino-or-raspberry-pi)
* 1x 5v 30amp Relay [here](https://robotdyn.com/relay-module-1-relay-5v-30a.html)
* 1x Crydom 25 A rms Solid State Relay, Zero Cross, Surface Mount [here](https://uk.rs-online.com/web/p/solid-state-relays/0346918/)
* 1x 240vac to 5vdc 3amp psu [here](https://uk.farnell.com/mean-well/rs-15-5/power-supply-ac-dc-5v-3a/dp/2816008?gclid=CjwKCAjw4MP5BRBtEiwASfwALzykFUpy0D1NfGwB9AtFk6ge9z51hKcsFSTC2TFxDH8aA4QST4EspxoCu5AQAvD_BwE&gross_price=true&mckv=sYdHUosbD_dc|pcrid|432101776060|plid||kword||match||slid||product|2816008|pgrid|104413864510|ptaid|pla-903929785098|&CMP=KNC-GUK-SHOPPING-CIRCUIT-PROTECTION-NEWSTRUCTURE-Test113-MarinBidding)
* 1x Upgraded Brass brew plate [here](https://www.theespressoshop.co.uk/en/Gaggia-Brass-Shower-Plate-Holder-%C3%B8-57x14mm---WGA16G1002/m-1976.aspx)
* 1x Chasis mount Pressure Guage 0-16bar [here](https://www.mrbean2cup.co.uk/vibiemme-manometer-0-16-bar)
* 1x Pre 2015 Steam Wand conversion [here](https://www.theespressoshop.co.uk/en/GB/Gaggia-Classic-pre-2015-Steam-Tube-Conversion-Kit---10049046/m-1971.aspx?PartnerID=22&utm_source=google&utm_medium=shopping&utm_campaign=UnitedKingdom&gclid=CjwKCAjw4MP5BRBtEiwASfwAL_4M7cJEe2LzkQFlZVfYTnMWm9F29JhH0SmJHmF0dWXiy117YAxrkxoCV5QQAvD_BwE)


### Setup program flow:
On pressing the rotary encoder centre button
* Cleaning and setup.
* Coffee Temp target on click, will give a menu allowing selection of 0-125c via rotating the rotary encoder and on click will save the selection.
* Steam Temp target on click, will give a menu allowing selection of 0-140c via rotating the rotary encoder and on click will save the selection.
* Backflush Clean on click, will start a cleaning program.
* Boiler descale on click will start the descaling program.
* Set Backflush Pause/Start duration on click, will give a menu allowing selection of 0-9 seconds.
* Software Version on click, will display the software version.
* Exit Setup.
* If the centre button on the encoder is held down it will cause the arduino to rest by kicking the watch dog, this can be done regardless of being in setup mode.


## General Operation
When the machine first turned on, the current boiler temperature is displayed with the target boiler temperature displayed below that, below again is a notification that states if the machine is up to temperature or not. The heater PID runs independently even if the user is in the setup menu, the PID will continue to control the heater if the user changes the target temperature on the exit of the menu the Arduino is reset allowing the new target temperature to be saved in the EEPROM for the PID to utilise.

When the make coffee switch is turned on the display changes to "making espresso", with time elapsed time displayed below and the current boiler temperature.

When the stream button is switched on the display changes to "steaming in progress", with the stream boiler temperature displayed and blow the stream target temperature, followed by machine status warning of ready or heating.

If both steam and coffee buttons are pressed, the display will change to dispensing hot water. Hot water will then be routed out the steam wand. 


## Cleaning programs
* The Backflush program, 
To use the machine must be up to temperature and a blank dish placed in the portafilter, when activated the screen displays "please fill the portafilter with detergent and press start", the machine will run the pump to the preset time then stop, backflush pause is displayed, after the allotted time the pump will run again then stop this will happen 10 times, after 10 times, "empty portafilter of detergent click to continue with flush" will be displayed, the pump will run and stop another 10 times. After the display will say "backflush finished" then reset the machine back to the standard coffee boiler temperature screen.

* The Decalcifire program,
To use the machine must be up to temperature, warm water with descaler must be placed into the water tank, when activated the screen will display, "Fill water tank add descaler then press button to start", the display will change to "cleaning started", the pump will run for 30 seconds then stop. The screen will display "please empty drip tray"  while a countdown timer counts down from 5 minutes, after the allotted time the pump will run for a further 30 seconds while the screen says "Decalcifier solution second flush", the machine will once again pause and the screen will display, "Empty tank/Drip tray and add fresh water, click to begin the last cycle". "Freshwater Flush will be displayed and the pump will run for 1 minute followed by the screen display "Cleaning complete please wait to exit", a delay of 2 seconds is called and the watchdog will reset the machine to the standard coffee boiler temperature screen.

#

## Modifications
Apart from the PID, I also changed the brew plate to a brass version to help with temperature dispersal and stabilisation, the shower plate was also upgraded and the group head seal was also changed for the neoprene version which will outlast the rubber version by quite some time. The steam wand was changed for the Rancilio Silvas version as the original Pannarello Steam Tube is just pure rubbish. 


<div align="center">
<img src="https://github.com/jonathanw82/Coffee/blob/master/images/grouphead.jpg" alt="group" width="45%"/>
<img src="https://github.com/jonathanw82/Coffee/blob/master/images/wand.jpg" alt="wand" width="45%"/></div>

I also Installed a chasis mount Pressure Guage that gives quite an accurate display, unfortunately, due to the facet pump the needle jumps about but it is still a good ballpark display and I know I'm getting a good 9 bar brew pressure.

<div align="center">
<img src="https://github.com/jonathanw82/Coffee/blob/master/images/hole.jpg" alt="hole" width="45%"/><img
src="https://github.com/jonathanw82/Coffee/blob/master/images/guage.jpg" alt="guage" width="45%"/></div>

#

### Decals
The decals have changed somewhat during creation, at first we had buttons than moved over to utilise the rotary encoder


<div align="center">
<img src="https://github.com/jonathanw82/Coffee/blob/master/images/coffee decal.jpg" alt="decal1" width="45%"/>
<img src="https://github.com/jonathanw82/Coffee/blob/master/images/coffee decal ver2.jpg" alt="decal2" width="45%"/>
<img src="https://github.com/jonathanw82/Coffee/blob/master/images/control.jpg" alt="control" width="45%"/></div>

#


### When all is said and done this machine pulls a decent cup of coffee
Thanks to the Gaggia Classic having a commercial 85mm portafilter an 18-gram (double) basket my favourite coffee recipes work well.

<div align="center">
<img src="https://github.com/jonathanw82/Coffee/blob/master/images/shot.jpg" alt="shot" width="45%"/>
<img src="https://github.com/jonathanw82/Coffee/blob/master/images/milk.jpg" alt="milk" width="45%"/></div>

#

### My persoanl favorite recipres

My favourite caffeinated coffee has to be Wogan Coffee, Riposo [here](https://wogancoffee.com/product/riposo/) I just love the chocolaty notes this coffee gives as an espresso and a fantastic price.

My favourite Decaffeinated coffee has to be Extract Coffee, SUGARCANE DECAF ESPRESSO [here](https://extractcoffee.co.uk/shop/coffee/hero/sugarcane-decaf-espresso-1kg/) It's just a good satisfying cup!

Both of these coffees lend themselves well to the same  2-1 brew ratio,
* Nice hot machine/group head.
* Water temperature 96-97c.
* 9 bar of brew pressure.
* 18 grams of fine ground on-demand coffee.
* 36 grams in the cup from a 26-30 second brew time.


### Credits:
I would like to thank my friend Cersnic Tebor for his help with this project.

The ideas for the menu system came from here 
http://educ8s.tv/arduino-rotary-encoder-menu/

The Pid to run the heater
https://playground.arduino.cc/Main/BarebonesPIDForEspresso/


##### Media:


All other images are my own.

[Back_to_top](#Gaggia)

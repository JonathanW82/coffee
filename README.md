
<h1 align="center">
   <img src="https://github.com/jonathanw82/Coffee/blob/master/images/repoimage.jpg" alt="Coffee"/>
 </h1>
 

# Gaggia Classic Espresso Machine Upgrade.
These files make up a complete program to run on an Arduino with a rotary encoder and a solid-state relay,
The menu system enables you to change target temperatures and access cleaning programs, while the PID controls the heater 
whether to heat coffee or produce steam!

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
* On pressing and holding the rotary encoder centre button the machine will reset.



### Nice to Have
* Glycerine filled pressure gauge for stable pressure readings.
* Higher maximum temperature, water temp sensor.(Current model only 150c)


### Credits:
I would like to thank my friend Cersnic Tebor for his help with this project.

The ideas for the menu system came from here 
http://educ8s.tv/arduino-rotary-encoder-menu/

The Pid to run the heater
https://playground.arduino.cc/Main/BarebonesPIDForEspresso/


##### Media:


All other images are my own.

[Back_to_top](#Gaggia)

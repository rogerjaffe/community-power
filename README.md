# community-power

This is for Shadi Lidioce's POE class at Kearny HS

The system has three components represented by the three folders display, master, region

**display**: Processing program that displays the current hour in the simulation.  The program is run on the same computer that has the master controller.  It reads the serial port to receive signals from the master Arduino controller.

**master**: Arduino program that simulates the master clock.  Two signals are generated in the program:

* **SEND_HOUR**: Pulse is generated each time the simulation reaches 00:00 (midnight). This is on Arduino pin 13

* **SEND_SYNC**: Pulse is generated each time the simulation switches to the next hour.  This is on Arduino pin 12

* **GROUND**: Make sure that the Arduino ground (any pin labeled GND) is connected to the ground of each of the regional Arduinos

The signals are connected to the regional Arduinos

**region**: Arduino program that turns on and off LEDs that represent the different electrical grid areas of the region of the city.  This Arduino receives two signals from the master controller Arduino:

* **INT_HOUR**: Pulse signaling 00:00 (midnight). This is on Arduino pin 3

* **INT_SYNC**: Pulse signaling a change to the next hour.  This is on Arduino pin 2

The Arduino code by default supports up to 25 LEDs that can represent electrical grid areas of the region.  Connections and configuration are as follows:

**Lines 15-16**: Setting the TEST variable to true (line 15) lets the region controller test itself without having to be hooked up to a master controller.  SIMULATE_HOUR_SWITCH_DELAY is set to the delay in milliseconds between successive hour switches.  Setting the TEST variable to false will disable this test so the region controller will respond to the master controller.

**Lines 39-40**: Configures the five LED anode and cathode pins.  The LED anode is the longer of the two leads.  The cathode is the shorter lead.  If the leads have been cut to the same size, look at the LED from the top and the cathode is the side with the flat edge.

**Lines 46-51**: Configures the actual LED connections.  For example

* {0, 0} means that both anode and cathode are connected to ANODE[0] (pin 4) and CATHODE[0] (pin 9).  

* {2, 1} means that the LED anode is connected to ANODE[2] (pin 6) and the cathode is connected to CATHODE[1] (pin 10).

The system by default is configured for 4 LEDs, but can support up to 16 LEDs by adding more pairs in this section.  

**Lines 62-87**: These lines set the ON/OFF configuration for each of the hours of the day starting with hour 0 (midnight) and going through hour 23 (11:00pm).  The first value is for LED1, second value for LED2, etc.

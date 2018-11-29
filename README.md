# community-power

This is for Shadie's POE class at Kearny HS

The system has three components represented by the three folders display, master, region

**display**: Processing program that displays the current hour in the simulation.  The program reads the serial port to receive signals from the master Arduino controller.

**master**: Arduino program that simulates the master clock.  Two signals are generated in the program:

* **SEND_HOUR**: Pulse is generated each time the simulation reaches 00:00 (midnight). This is on Arduino pin 13

* **SEND_SYNC**: Pulse is generated each time the simulation switches to the next hour.  This is on Arduino pin 12

The signals are connected to the regional Arduinos

**region**: Arduino program that turns on and off LEDs that represent the different electrical grid areas of the region of the city.  This Arduino receives two signals from the master controller Arduino:

* **INT_HOUR**: Pulse signaling 00:00 (midnight). This is on Arduino pin 3

* **INT_SYNC**: Pulse signaling a change to the next hour.  This is on Arduino pin 2

The Arduino code by default supports up to 16 LEDs that can represent four electrical grid areas of the region.  Connections and configuration are as follows:

**Lines 25-26**: Configures the four LED anode and cathode pins.  The LED anode is the longer of the two leads.  The cathode is the shorter lead.  If the leads have been cut to the same size, look at the LED from the top and the cathode is the side with the flat edge.

**Lines 32-37**: Configures the actual LED connections.  For example

* {0, 0} means that both anode and cathode are connected to ANODE[0] (pin 4) and CATHODE[0] (pin 9).  

* {2, 1} means that the LED anode is connected to ANODE[2] (pin 6) and the cathode is connected to CATHODE[1] (pin 10).

The system by default is configured for 4 LEDs, but can support up to 16 LEDs by adding more pairs in this section.  

**Lines 48-73**: These lines set the ON/OFF configuration for each of the hours of the day starting with hour 0 (midnight) and going through hour 23 (11:00pm).  The first value is for LED1, second value for LED2, etc.

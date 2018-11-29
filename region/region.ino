// System constants
const int INT_SYNC = 2;   // Connect this pin to the SEND_SYNC pin on the master
const int INT_HOUR = 3;   // Connect this pin to the SEND_HOUR pin on the master

const int MAX_HOUR = 24;
const int STANDBY = -1;
const int MIDNIGHT = 0;
const int BLINK_DELAY = 5;          // in ms
const int LED_TEST_DELAY = 2000;    // 2 second delay for LED test

const int ON = true;
const int OFF = false;

// State variables
int currentHour = STANDBY;
int prevHour = STANDBY;

// Led data structure
struct Led {
  int anode;
  int cathode;
};

// Anode and cathode pin definitions
const int ANODES[] = {4, 5, 6, 7, 8};
const int CATHODES[] = {9, 10, 11, 12, 13};

// Define anode and cathode numbers used for each LED
// For example, LED[1] is connected to ANODES[2] and CATHODES[1]
// LED[1] means the LED at index 1 in the array; since array
// indexes always start at 0, LED[1] is the 2nd LED in the array
const Led leds[] = {
  {0, 0},
  {2, 1},
  {2, 2},
  {3, 0}
};

const int NUM_LEDS = sizeof(leds) / sizeof(leds[0]);

// Define on and off rules for each LED
// Each row represents an hour starting at hour 0 (midnight)
// Each column represents the LED number
// For example, in hour 2, LEDs 0 through 3 are OFF, OFF, ON, and OFF
// Simply add more ON/OFF labels separated by commas to add more 
// LEDs to the rules.  Each line MUST have the same number of 
// entries equal to the number of LEDs you are using.
const boolean onRules[][NUM_LEDS] = {
  {ON, OFF, OFF, OFF},
  {OFF, ON, OFF, OFF},
  {OFF, OFF, ON, OFF},
  {OFF, OFF, OFF, ON},
  {ON, ON, OFF, OFF},
  {OFF, ON, ON, OFF},
  {OFF, OFF, ON, ON},
  {ON, OFF, OFF, ON},
  {ON, ON, ON, OFF},
  {OFF, ON, ON, ON},
  {ON, OFF, ON, ON},
  {ON, ON, OFF, ON},
  {ON, OFF, OFF, OFF},
  {ON, OFF, ON, OFF},
  {OFF, ON, OFF, ON},
  {OFF, OFF, ON, ON},
  {ON, ON, OFF, OFF},
  {OFF, ON, OFF, OFF},
  {OFF, OFF, OFF, OFF},
  {OFF, OFF, OFF, OFF},
  {OFF, OFF, OFF, OFF},
  {OFF, OFF, OFF, OFF},
  {OFF, OFF, OFF, OFF},
  {OFF, OFF, OFF, OFF}
};

void setup() {
  // Open serial port
  Serial.begin(9600);
  
  // Set interrupt pin modes and attach the interrupt 
  // service routines.  Interrupts are triggered in response
  // to signals from the Master Controller
  pinMode(INT_SYNC, INPUT_PULLUP);
  pinMode(INT_HOUR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_SYNC), setSync, RISING);
  attachInterrupt(digitalPinToInterrupt(INT_HOUR), bumpHour, RISING);

  // Set the pin modes for the anode and cathode pins
  for (int i=0; i<sizeof(ANODES)/sizeof(int); i++) {
    pinMode(ANODES[i], OUTPUT);
    pinMode(CATHODES[i], OUTPUT);
  }
  
  // Turn on all the LEDs to test that they all work
  ledTest();
  Serial.println("Region clock started");
}

// Called in response to a SYNC signal from the Master
// Controller.  Sets the current hour to STANDBY and
// stops the simulation until the HOUR signal is received
// from the Master Controller
void setSync() {
  currentHour = MIDNIGHT;  
  Serial.println("SYNC SYSTEM");
}

// Called in response to an HOUR signal from the Master
// Controller.  Adds 1 to the current hour, or, if currentHour
// equals 23, sets the current hour back to 0
void bumpHour() {
  currentHour = (currentHour+1) % MAX_HOUR;
  Serial.println("BUMP HOUR");
}

void loop() {
  // If there's been a change in currentHour, print a
  // console message
  if (prevHour != currentHour) {
    if (currentHour == STANDBY) {
      Serial.println("STANDBY");
    } else {
      Serial.print("Current hour: ");
      Serial.println(currentHour);
    }
    prevHour = currentHour;
  }
  
  // Set the LEDs according to the state table above
  setRegionalLEDs();  
}

/**
 * The currentHour variable is an integer between 0 and 24 and  
 * represents the hour of a 24-hour clock or military time.
 * 
 * 0 = midnight
 * 1-11 = 1 am through 11 am
 * 12 = 12 noon
 * 13-23 = 1 pm through 11 pm
 */
void setRegionalLEDs() {
  if (currentHour != STANDBY) {
    for (int i=0; i<NUM_LEDS; i++) {
      boolean status = onRules[currentHour][i]; 
      if (status) {
        blinkLed(i);
      }
    }
  }
}

// Blinks the led at ledIdx very quickly!!
void blinkLed(int ledIdx) {
  // Get the anode and cathode indexes for the led at ledIdx
  int anode = leds[ledIdx].anode;
  int cathode = leds[ledIdx].cathode;
  // Get the pins for the anode and cathode
  int anodePin = ANODES[anode];
  int cathodePin = CATHODES[cathode];
  // Turn the LED on
  digitalWrite(anodePin, HIGH);
  digitalWrite(cathodePin, LOW);
  // Wait a short amount of time...
  delay(BLINK_DELAY);
  // ... and turn the LED off
  digitalWrite(anodePin, LOW);
  digitalWrite(cathodePin, HIGH);
}

// Turn on all of the LEDS in the system to make sure they
// work properly
void ledTest() {
  Serial.println("Begin LED test");
  for (int i=0; i<sizeof(ANODES)/sizeof(int); i++) {
    digitalWrite(ANODES[i], HIGH);
    digitalWrite(CATHODES[i], LOW);
  }  
  delay(LED_TEST_DELAY);      // Wait 2 seconds
  for (int i=0; i<sizeof(ANODES)/sizeof(int); i++) {
    digitalWrite(ANODES[i], LOW);
    digitalWrite(CATHODES[i], HIGH);
  }  
  Serial.println("LED test complete");
}


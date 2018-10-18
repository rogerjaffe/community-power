int MAX_HOUR = 24;
int STANDBY = -1;
int INT_SYNC = 2;
int INT_HOUR = 3;
int SYNC_BTN = 7;
int HOUR_BTN = 8;

int currentHour = STANDBY;
int prevHour = 0;

boolean hourBtnPressed = false;
boolean syncBtnPressed = false;

void setup() {
  pinMode(SYNC_BTN, INPUT);
  pinMode(HOUR_BTN, INPUT);
  pinMode(INT_SYNC, INPUT_PULLUP);
  pinMode(INT_HOUR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_SYNC), setSync, RISING);
  attachInterrupt(digitalPinToInterrupt(INT_HOUR), bumpHour, RISING);
  Serial.begin(9600);
  Serial.println("Region clock started");
}

boolean checkButtons(int btn, boolean &pressed) {
  int btnStatus = digitalRead(btn);
  if (btnStatus == HIGH) {
    if (!pressed) {
      pressed = true;
      return true;
    } else {
      return false;
    }
  } else {
    pressed = false;
    return false;
  }
}

void setSync() {
  currentHour = STANDBY;  
  Serial.println("SYNC SYSTEM");
}

void bumpHour() {
  currentHour = (currentHour+1) % MAX_HOUR;
  Serial.println("BUMP HOUR");
}

void loop() {
  if (checkButtons(SYNC_BTN, syncBtnPressed)) {
    setSync();
  }
  if (checkButtons(HOUR_BTN, hourBtnPressed)) {
    bumpHour();
  }
  if (prevHour != currentHour) {
    if (currentHour == STANDBY) {
      Serial.println("STANDBY");
    } else {
      Serial.print("Current hour: ");
      Serial.println(currentHour);
    }
    prevHour = currentHour;
  }
  setRegionalLEDs();  
}

/**
 * This is the function that you will need to modify to simulate
 * your region's power consumption.
 * 
 * The currentHour variable is an integer between 0 and 24 and  
 * represents the hour of a 24-hour clock or military time.
 * 
 * 0 = midnight
 * 1-11 = 1 am through 11 am
 * 12 = 12 noon
 * 13-23 = 1 pm through 11 pm
 * 
 * Follow the code below and READ THE COMMENTS to learn how to
 * program the LEDs for your region!
 */
setRegionalLEDs() {
  
}



int MAX_HOUR = 24;      // Hours should go 0 - 23
int DELAY = 2;          // Delay between "hours" in seconds
int LEAD_TIME = 2;      // Seconds lead time before starting at hour 0
int STANDBY = -1;       // Boot up
int PULSE_WIDTH = 100;  // Signal pulse width for other Arduinos

long prevClock = STANDBY;     // Previous clock time
long seconds = 0;

int currentHour = STANDBY;

int SEND_SYNC = 12;
int SEND_HOUR = 13;

void setup()
{
  pinMode(SEND_SYNC, OUTPUT);
  pinMode(SEND_HOUR, OUTPUT);
  Serial.begin(9600);
  Serial.println(getTimeText(currentHour));
}

void loop()
{
  seconds = millis();
  if (currentHour == STANDBY) {
    if (seconds-prevClock >= LEAD_TIME*1000) {
      currentHour = 0;          
      prevClock = seconds;
      sendPulse(SEND_SYNC);
      Serial.println(getTimeText(currentHour));
    }
  } else {
    if (seconds-prevClock >= DELAY*1000) {
      currentHour = (currentHour+1) % MAX_HOUR;
      prevClock = seconds;
      sendPulse(SEND_HOUR);
      Serial.println(getTimeText(currentHour));
    }
  }
}

void sendPulse(int pin) {
  digitalWrite(pin, HIGH);
  delay(PULSE_WIDTH);
  digitalWrite(pin, LOW);
}

String getTimeText(int currentHour) {
  if (currentHour == STANDBY) {
    return "STANDBY";
  } else if (currentHour == 0) {
    return "12:00 AM";
  } else if (currentHour < 12) {
    return String(currentHour)+":00 AM";
  } else if (currentHour == 12) {
    return "12:00 PM";
  } else {
    return String(currentHour-12)+":00 PM";
  }
}


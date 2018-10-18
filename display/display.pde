import processing.serial.*;

// ********  IMPORTANT NOTE **********
// If you get an error that says "Error opening serial port" then
// look at the list in the console at the bottom of this window
// and find the same port that the Arduino is connected to
// Get the index number next to the port and change the number
// assigned to "com_port" below to that index.  Then re-run
// the program
int com_port  = 3;   // Index number in Serial.list

Serial port;                    // Create object from Serial class
PFont f;                        // Font for the display
final int WIDTH = 800;          // Display size
final int HEIGHT = 600;

void settings() {
  size(WIDTH, HEIGHT);          // Set display size
}

void setup() {
  println("Serial port list (start with index=0)");
  for (int i=0; i<Serial.list().length; i++) {
    print("Index ");
    print(i);
    print(": ");
    println(Serial.list()[i]);
  }
  port = new Serial(this, Serial.list()[com_port], 9600);    // Com port specified here

  // Display settings
  smooth();
  f = createFont("Arial", 12, true);
  textFont(f, 128);
  fill(0);
  drawText("STANDBY");  
}

// Read value from serial stream
String getValue() {
  String value = "";
  while (port.available () > 0) {
    value = port.readStringUntil('\n');
  }
  return value;
}

// Draw text passed in to str
void drawText(String str) {
  background(255, 255, 255);
  textAlign(CENTER);
  text(str, WIDTH/2, HEIGHT/2);  
}

// Draw loop
void draw() {
  // Get any incoming data from the serial port
  String str = getValue();
  println(str);
  if (str.length() > 0) {
    drawText(str);
  }
}
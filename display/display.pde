import processing.serial.*;

Serial port;                    // Create object from Serial class
PFont f;
int com_port  = 3;   // Index number in Serial.list
final int WIDTH = 800;
final int HEIGHT = 600;

void settings() {
  size(WIDTH, HEIGHT);
}

void setup() {
  println("Serial port list (start with index=0)");
  for (int i=0; i<Serial.list().length; i++) {
    println(Serial.list()[i]);
  }
  //print(Serial.list());
  port = new Serial(this, Serial.list()[com_port], 9600);    // Com port specified here
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

void drawText(String str) {
  background(255, 255, 255);
  textAlign(CENTER);
  text(str, WIDTH/2, HEIGHT/2);  
}

void draw() {
  String str = getValue();
  println(str);
  if (str.length() > 0) {
    drawText(str);
  }
  //text("abc", 10, 50);
  //if (mousePressed) {
  //  fill(0);
  //} else {
  //  fill(255);
  //}
  //ellipse(mouseX, mouseY, 80, 80);
}
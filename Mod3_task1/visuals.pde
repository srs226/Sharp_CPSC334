//import library
import oscP5.*;
//initialize variables
String value1 = "0";
float value2 = 0;
OscP5 oscP5;

void setup() {
  size(400,400);
  frameRate(25);
  oscP5 = new OscP5(this,12000);
}
//change background color based on value of light sensor
void draw() {
  value2 = Integer.parseInt(value1);
  value2 = map(value2, 0, 2000, 0, 510);
  if(value2 <= 255){
    background(0, 0, value2);
  }
  else{
    background(value2 - 255, value2 - 255, 255);
  }
}

//recieve message
void oscEvent(OscMessage theOscMessage) {
  value1 = theOscMessage.get(0).stringValue();
  println(value1);
}

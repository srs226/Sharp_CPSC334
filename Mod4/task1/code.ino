#include <Stepper.h>
#include <ESP32Servo.h>

const int stepsPerRev = 2048;

Servo myservo;
Stepper myStepper(stepsPerRev, 19,18,5,17);
int angle = 0;
void setup() {
  // set speed of stepper
  myStepper.setSpeed(10);
  //pin the servo is at
  myservo.attach(26);
  //set servo angle to 0
  if (myservo.read() != angle){
    myservo.write(angle);
    angle+=10;
  }
  Serial.begin(9600);
}

void loop() {
  //rotate stepper
  myStepper.step(stepsPerRev);
  //increment servo angle
  if (angle != 180){
    angle+=10;
  }
  else {
    angle = 0;
  }
  delay(500);
  //move servo
  myservo.write(angle);
}


//libraries
#include <WiFi.h>
#include <WiFiUdp.h>

#include "pitches.h"

#define SPEAKER      25   // The output pin for the piezo buzzer
#define NUM_OF_KEYS   9   // Number of keys that are on the keyboard
#define SMOOTH       25   // determine how many readings are stored for smoothing

// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
int notes[]={0,0,0,0,0,0,0,0,0}; // initial array
int notes0[]={NOTE_G2,NOTE_A2,NOTE_B2,NOTE_C3,NOTE_D3,NOTE_E3,NOTE_FS3,NOTE_G3,NOTE_A3}; // G-Major scale
int notes1[]={NOTE_GS3,NOTE_AS3,NOTE_B3,NOTE_CS4,NOTE_DS4,NOTE_E4,NOTE_FS4,NOTE_GS4,NOTE_AS4}; // Ab-Minor scale
int notes2[]={NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_DS5,NOTE_FS4}; // C-Major scale
int notes3[]={NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5, NOTE_GS4}; // A-Minor scale
int notes4[]={NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_AS4,NOTE_C5,NOTE_DS5, NOTE_CS5}; // C Blues scale

//initialize for WiFi and udp
const char* ssid = "yale wireless";
const char* password = "";

const char* addy = "172.29.24.126";
const uint16_t port = 8000;

WiFiUDP udp;

// the latest reading from touchpins
int reading;
//esp touch pins
int touchpin[] = {2, 4, 15, 12, 13, 14, 27, 33, 32};

//pins for leds 
int red = 19;
int blue = 16;
int green = 18;

int red2 = 23;
int blue2 = 22;
int green2 = 21;

//variables for light color and intensity
int effect = 0, intense = 0;


void setup() {
  Serial.begin(115200);
  //setup connection and confirm
  //Serial.println(WiFi.macAddress());
  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){      
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  //send message to pi so pi has correct port to send data on
  String msg = "hi";
  udp.beginPacket(addy,port);
  udp.print(msg);  // USES .print INSTEAD OF .write
  udp.endPacket();
  // Set the leds and speaker as an output:
  pinMode(SPEAKER, OUTPUT); 
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue2, OUTPUT);
}

void loop() {
  //detect if pi is sending data
  if(udp.parsePacket()){
    //clear data
    udp.flush();
    effect++;
    intense = 0;
  }
  effect = effect % 5;
  //set correct light and colors
  lights(effect);

  //play music
  music();
}

void lights(int effect) {
  //turn on perimeter lights
  int state = effect;
  switch(state)
  {
    case 0:
    //white light
      if(intense == 0){
        color(255,255,255);
        //new scale
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes0[i];
        }
      }
      else{
        //change intensity of light for each key press
        color((10 * intense) % 255, (10 * intense) % 255, (10 * intense) % 255);
      }
    break;

    case 1:
      //blue light
      if(intense == 0){
        color(0, 0, 100);
        //new scale
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes1[i];
        }
      }
      else{
        color(0, 0, (10 * intense) % 255);
      }
    break;
    
    case 2:
      //green light
      if(intense == 0){
        color(0, 100, 0);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes2[i];
        }
      }
      else{
        color(0, (10 * intense) % 255, 0);
      }
    break;

    case 3:
      //red light
      if(intense == 0){
        color(0, 100, 100);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes3[i];
        }
      }
      else{
        color(0, (10 * intense) % 255, (10 * intense) % 255);
      }
    break;

    case 4:
      //yellow light
      if(intense == 0){
        color(100, 100, 0);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes3[i];
        }
      }
      else{
        color(0, 100, (10 * intense) % 255);
      }
    break;
  }
}

void music() {
  // Loop through each key:
  for (int i = 0; i < NUM_OF_KEYS; ++i) {
    // If the capacitance reading is greater than the threshold, play a note:
    reading = touchRead(touchpin[i]);
    // check if triggered
    if(reading < SMOOTH){ 
    // executes if the sensor is triggered
      intense++;
      // Plays the note corresponding to the key pressed while key is pressed
      tone(SPEAKER, notes[i]);
      while(reading < SMOOTH){
      reading = touchRead(touchpin[i]);
      }
      
    }
    else{
      tone(SPEAKER, 0);
    }
  }

}

//write to leds
void color(int red_val, int green_val, int blue_val)
 {
  analogWrite(red, red_val);
  analogWrite(green, green_val);
  analogWrite(blue, blue_val);

  analogWrite(red2, red_val);
  analogWrite(green2, green_val);
  analogWrite(blue2, blue_val);
}



/* this is code from my first esp, the red portion of the leds burned out with the first esp so I had to make some changes
//libraries
#include <WiFi.h>
#include <WiFiUdp.h>

#include "pitches.h"

#define SPEAKER      25   // The output pin for the piezo buzzer
#define NUM_OF_KEYS   9   // Number of keys that are on the keyboard
#define SMOOTH       25   // determine how many readings are stored for smoothing

// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
int notes[]={0,0,0,0,0,0,0,0,0}; // initial array
int notes0[]={NOTE_G2,NOTE_A2,NOTE_B2,NOTE_C3,NOTE_D3,NOTE_E3,NOTE_FS3,NOTE_G3,NOTE_A3}; // G-Major scale
int notes1[]={NOTE_GS3,NOTE_AS3,NOTE_B3,NOTE_CS4,NOTE_DS4,NOTE_E4,NOTE_FS4,NOTE_GS4,NOTE_AS4}; // Ab-Minor scale
int notes2[]={NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_DS5,NOTE_FS4}; // C-Major scale
int notes3[]={NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5, NOTE_GS4}; // A-Minor scale
int notes4[]={NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_AS4,NOTE_C5,NOTE_DS5, NOTE_CS5}; // C Blues scale

//initialize for WiFi and udp
const char* ssid = "yale wireless";
const char* password = "";

const char* addy = "172.29.128.95";
const uint16_t port = 8092;

WiFiUDP udp;

// the latest reading from touchpins
int reading;
//esp touch pins
int touchpin[] = {2, 4, 15, 12, 13, 14, 27, 33, 32};

//pins for leds 
int red = 18;
int blue = 16;
int green = 19;

//variables for light color and intensity
int effect = 0, intense = 0;


void setup() {
  Serial.begin(115200);
  //setup connection and confirm
  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){      
    Serial.print(".");
    delay(100);
  }
  Serial.println("");
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  //send message to pi so pi has correct port to send data on
  String msg = "hi";
  udp.beginPacket(addy,port);
  udp.print(msg);  // USES .print INSTEAD OF .write
  udp.endPacket();
  // Set the leds and speaker as an output:
  pinMode(SPEAKER, OUTPUT); 
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  //detect if pi is sending data
  if(udp.parsePacket()){
    //clear data
    udp.flush();
    effect++;
    intense = 0;
  }
  effect = effect % 5;
  //set correct light and colors
  lights(effect);

  //play music
  music();
}

void lights(int effect) {
  //turn on perimeter lights
  int state = effect;
  switch(state)
  {
    case 0:
    //white light
      if(intense == 0){
        color(255,255,255);
        //new scale
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes0[i];
        }
      }
      else{
        //change intensity of light for each key press
        color((10 * intense) % 255, (10 * intense) % 255, (10 * intense) % 255);
      }
    break;

    case 1:
      //blue light
      if(intense == 0){
        color(0, 0, 100);
        //new scale
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes1[i];
        }
      }
      else{
        color(0, 0, (10 * intense) % 255);
      }
    break;
    
    case 2:
      //green light
      if(intense == 0){
        color(0, 100, 0);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes2[i];
        }
      }
      else{
        color(0, (10 * intense) % 255, 0);
      }
    break;

    case 3:
      //red light
      if(intense == 0){
        color(100, 0, 0);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes3[i];
        }
      }
      else{
        color((10 * intense) % 255, 0, 0);
      }
    break;

    case 4:
      //yellow light
      if(intense == 0){
        color(100, 100, 0);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes3[i];
        }
      }
      else{
        color((10 * intense) % 255, (10 * intense) % 255, 0);
      }
    break;
  }
}

void music() {
  // Loop through each key:
  for (int i = 0; i < NUM_OF_KEYS; ++i) {
    // If the capacitance reading is greater than the threshold, play a note:
    reading = touchRead(touchpin[i]);
    // check if triggered
    if(reading < SMOOTH){ 
    // executes if the sensor is triggered
      intense++;
      // Plays the note corresponding to the key pressed while key is pressed
      tone(SPEAKER, notes[i]);
      while(reading < SMOOTH){
      reading = touchRead(touchpin[i]);
      }
      
    }
    else{
      tone(SPEAKER, 0);
    }
  }

}

//write to leds
void color(int red_val, int green_val, int blue_val)
 {
  analogWrite(red, red_val);
  analogWrite(green, green_val);
  analogWrite(blue, blue_val);
}
*/

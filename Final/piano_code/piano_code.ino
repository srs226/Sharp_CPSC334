//libraries

#include <Tone32.hpp>
#include "pitches.h"


const int SPEAKER = 25;   
const int SPEAKER2 = 26;   // The output pins for the speaker
#define NUM_OF_KEYS  9   // Number of keys that are on the keyboard
#define SMOOTH       40   // determine how many readings are stored for smoothing
#define BUTTON       35
#define POT          34
// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
int notes[]={0,0,0,0,0,0,0,0,0}; // initial array
int notes0[]={NOTE_G2,NOTE_A2,NOTE_B2,NOTE_C3,NOTE_D3,NOTE_E3,NOTE_FS3,NOTE_G3,NOTE_A3}; // G-Major scale
int notes1[]={NOTE_GS3,NOTE_AS3,NOTE_B3,NOTE_CS4,NOTE_DS4,NOTE_E4,NOTE_FS4,NOTE_GS4,NOTE_AS4}; // Ab-Minor scale
int notes2[]={NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5}; // C-Major scale
int notes3[]={NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5, NOTE_B5}; // A-Minor scale
int notes4[]={NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_AS4,NOTE_C5,NOTE_DS5, NOTE_F5}; // C Blues scale

int notes5[]={NOTE_C6,NOTE_D6,NOTE_E6,NOTE_F6,NOTE_G6,NOTE_A6,NOTE_B6,NOTE_C7,NOTE_D7}; // C Maj
int notes6[]={NOTE_GS1,NOTE_AS1,NOTE_B1,NOTE_CS2,NOTE_DS2,NOTE_E2,NOTE_FS2,NOTE_GS2,NOTE_AS2}; // Ab scale

//for two tones
const int TONE_PWM_CHANNEL = 5;
const int TONE_PWM_CHANNEL2 = 0;
Tone32 tone1(SPEAKER, TONE_PWM_CHANNEL);
Tone32 tone2(SPEAKER2, TONE_PWM_CHANNEL2);


// the latest reading from touchpins
int reading;
//esp touch pins
int touchpin[] = {33, 14, 15, 32, 13, 2, 27, 12, 4};

//pins for leds 
int red = 16;
int blue = 18;
int green = 19;

int red2 = 22;
int blue2 = 23;
int green2 = 21;

//variables for light color and intensity
int effect = 0, intense = 0, effect2 = -1, change = 0;


void setup() {
  Serial.begin(115200);
 
  // Set the outputs n inputs:
  pinMode(BUTTON, INPUT);
  pinMode(POT, INPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue2, OUTPUT);
}

void loop() {
  //switch notes
  if(digitalRead(BUTTON)){
    effect++;
    change = 0;
    delay(200);
    if(effect != effect2)
    {
      lights(effect);
      effect2 = effect;
    }
  }
  effect = effect % 7;
  //change led brightness
  int softPotADC = analogRead(POT);
  if(softPotADC > 0){
    intense = map(softPotADC, 0, 4095, 0, 51);
    change++;
    lights(effect);
    delay(100);
  }
  //set correct light and colors
  if(effect != effect2)
  {
    lights(effect);
    effect2 = effect;
  }

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
      if(change == 0){
        color(255,255,255);
        //new scale
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes0[i];
        }
      }
      else{
        //change intensity of light for each key press
        color(intense * 5, intense * 4, intense * 4);
      }
    break;

    case 1:
      //blue light
      if(change == 0){
        color(0, 0, 100);
        //new scale
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes1[i];
        }
      }
      else{
        color(0, 0, (5 * intense));
      }
    break;
    
    case 2:
      //green light
      if(change == 0){
        color(0, 100, 0);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes2[i];
        }
      }
      else{
        color(0, (5 * intense), 0);
      }
    break;

    case 3:
      //aqua light
      if(change == 0){
        color(0, 100, 100);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes3[i];
        }
      }
      else{
        color(0, (5 * intense), (5 * intense));
      }
    break;

    case 4:
      //yellow light
      if(change == 0){
        color(100, 100, 0);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes4[i];
        }
      }
      else{
        color((5 * intense), (4 * intense), 0);
      }
    break;

    case 5:
      //red light
      if(change == 0){
        color(100, 0, 0);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes5[i];
        }
      }
      else{
        color((5 * intense), 0, 0);
      }
    break;

    case 6:
      //purple light
      if(change == 0){
        color(100, 0, 100);
        for(int i = 0; i < NUM_OF_KEYS; i++)
        {
          notes[i] = notes6[i];
        }
      }
      else{
        color((5 * intense), 0, (5 * intense));
      }
    break;
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

bool s1_on = false;
bool s2_on = false;
int touch1, touch2;

// If the capacitance reading is greater than the threshold, play a note:
void music(){
  for (int i = 0; i < NUM_OF_KEYS; ++i) {
    reading = touchRead(touchpin[i]);
    // check if speaker 1 is off and the nail's note isn't already being played
    if(reading < SMOOTH &! s1_on && touchpin[i] != touch2){ 
    // executes if the sensor is triggered
      intense++;
      // Plays the note corresponding to the key pressed while key is pressed
      touch1 = touchpin[i];
      tone1.playTone(notes[i]);
      s1_on = true;
      
    }
    //no note coming out of speaker 1
    else if(reading > SMOOTH && touch1 == touchpin[i] && s1_on){
      tone1.stopPlaying();
      s1_on = false;
    }
    // check if speaker 2 is off and the nail's note isn't already being played
    else if(reading < SMOOTH &! s2_on && touchpin[i] != touch1){ 
    // executes if the sensor is triggered
      intense++;
      // Plays the note corresponding to the key pressed while key is pressed
      touch2 = touchpin[i];
      tone2.playTone(notes[i]);
      s2_on = true;
      
    }
    //no note coming out of speaker 2
    else if(reading > SMOOTH && touch2 == touchpin[i] && s2_on){
      tone2.stopPlaying();
      s2_on = false;
    }
  }
}

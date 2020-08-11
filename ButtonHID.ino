/* 
 Simple media keyboard project
 (c) Stuart Teasdale 2020
 
*/ 
#include<Encoder.h>
#include<HID-Project.h>
#include "ButtonHID.h"


Encoder volume_control(2,3);

void setup() {
  //start serial connection
  //Serial.begin(9600);
  //configure pins as an input and enable the internal pull-up resistor
  for (int button=0; button<button_count; button++) {
    pinMode(button_pin[button], button_pin_mode[button]);
  }
  
  Consumer.begin();
}

int rotary_change() {
  int vol = volume_control.read();
  volume_control.write(0);
  if (vol > 0) { return 1;}
  else if (vol < 0) { return -1;}
  else return 0;
}


void loop() {
  
  for (int i=0; i < button_count; i++){
    button[i].pressed = !digitalRead(button[i].pin);
    if (button[i].pressed){
      if (!button[i].press_sent){
        Consumer.write(button[i].key);
        button[i].press_sent=true;
        }
      }
    else {
      button[i].press_sent=false;
    }
  //Serial.print(all_button_state[i]);Serial.print(" | ");
  }
  
  
  int volume_change = rotary_change();
  if (volume_change >0){
    Consumer.write(MEDIA_VOL_UP);
    //Serial.print("UP");
  } 
  else if (volume_change < 0){
    Consumer.write(MEDIA_VOL_DOWN);
    //Serial.print("DOWN");
  }
  //Serial.println(""); 
  
  delay(100);

}

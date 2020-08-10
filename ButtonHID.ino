/* 
 Simple media keyboard project
 (c) Stuart Teasdale 2020
 
*/ 
#include<Encoder.h>
#include<HID-Project.h>

int core_button_pin[] = {5,6,7,8,9};
int extra_button = 4;
const int core_button_count = 5;
int vol;
int RXLED = 17;
#define TRUE 1
#define FALSE 0

// 5 buttons and the encoder push
const ConsumerKeycode KEYCONF[6] = {MEDIA_PREVIOUS,MEDIA_STOP,MEDIA_PLAY_PAUSE,MEDIA_NEXT,CONSUMER_EXPLORER,MEDIA_VOL_MUTE};

Encoder volume_control(2,3);

void setup() {
  //start serial connection
  //Serial.begin(9600);
  //configure pins as an input and enable the internal pull-up resistor
  for (int button=0; button<core_button_count; button++) {
    pinMode(core_button_pin[button], INPUT_PULLUP);
  }
  pinMode(extra_button,INPUT);
  Consumer.begin();
}

int rotary_change() {
  int vol = volume_control.read();
  volume_control.write(0);
  if (vol > 0) { return 1;}
  else if (vol < 0) { return -1;}
  else return 0;
}

void buttons_read(int buttons[]){
  for (int button=0;button < core_button_count;button++){
    buttons[button] = !digitalRead(core_button_pin[button]);
  }
  buttons[core_button_count]=!digitalRead(extra_button);
}


void loop() {
  static int all_button_state[core_button_count+1];
  static int button_press_already_sent[core_button_count+1];
  
  //read the pushbutton values
  buttons_read(all_button_state);
    
    //Debounce button check

  for (int i=0;i<core_button_count + 1 ;i++){
    if (all_button_state[i]){
      if (!button_press_already_sent[i]){
        Consumer.write(KEYCONF[i]);
        button_press_already_sent[i]=TRUE;
        }
      }
    else {
      button_press_already_sent[i]=FALSE;
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


int button_pin[] = {5,6,7,8,9,4};
int button_pin_mode[] = {INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT};

const int button_count = 6;
int vol;
int RXLED = 17;

struct Button {
  int pin;
  int pin_mode;
  ConsumerKeycode key;
  bool pressed;
  bool press_sent;
};
// 5 buttons and the encoder push
const ConsumerKeycode KEYCONF[6] = {MEDIA_PREVIOUS,MEDIA_STOP,MEDIA_PLAY_PAUSE,MEDIA_NEXT,CONSUMER_EXPLORER,MEDIA_VOL_MUTE};
Button button[6] ={
  {5, INPUT_PULLUP, MEDIA_PREVIOUS, false, false},
  {6, INPUT_PULLUP, MEDIA_STOP, false, false},
  {7, INPUT_PULLUP, MEDIA_PLAY_PAUSE, false, false},
  {8, INPUT_PULLUP, MEDIA_NEXT, false, false},
  {9, INPUT_PULLUP, CONSUMER_EXPLORER, false, false},
  {4, INPUT, MEDIA_VOL_MUTE, false, false}
};

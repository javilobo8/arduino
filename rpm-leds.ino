const int latchPin = 8;
const int clockPin = 13;
const int dataPin  = 11;

const int n_leds = 8;

int numOfRegisters = 1;
byte* registerState;

byte byteRead;
int led_value = 0;
int value = 0;

void setup() {
  //Initialize array
  registerState = new byte[numOfRegisters];
  for (size_t i = 0; i < numOfRegisters; i++) {
    registerState[i] = 0;
  }

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while(true) {
    if (Serial.available()) {
      value = Serial.parseInt();
      if (value != 0) {
        led_value = value;
      }
    }
    display();
  }
}

void display() {
  for (int k = 0; k < n_leds; k++){
    regWrite(k, k <= led_value - 1 ? HIGH : LOW);
  }
}

void regWrite(int pin, bool state){
  digitalWrite(latchPin, LOW);
  byte* states = &registerState[0];
  bitWrite(*states, pin, state);
  shiftOut(dataPin, clockPin, MSBFIRST, *states);
  digitalWrite(latchPin, HIGH);
}

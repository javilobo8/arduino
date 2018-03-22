const int latchPin = 8;
const int clockPin = 13;
const int dataPin  = 11;

byte leds[8] = {};
byte led_data = 0x00;
int value = 0;

int power(int value, int exponent) {
  return 0.5 + pow(value, exponent);
}

void setup() {
  // Fill leds byte array
  for (size_t i = 1; i <= 8; i++) {
    leds[i - 1] = power(2, i) - 1;
  }

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while(true) {
    led_data = 0x00;
    if (Serial.available()) {
      // [-1, 1, 2, 3, 4, 5, 6, 7, 8]
      value = Serial.parseInt();
      if (value != 0) {
        led_data = leds[value - 1];
      }
    }
    display();
  }
}

void display() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, led_data);
  digitalWrite(latchPin, HIGH);
}

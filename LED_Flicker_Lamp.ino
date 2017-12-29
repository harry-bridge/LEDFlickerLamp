// PWM LED Fade for battery powered lamp
// Created for A Beautiful Game
// Created by Harry Bridge

const byte buttonPin = 10;
//
unsigned int buttonState[] = {0, 0, 13000, 1};
// LEDPin, currentIntens
int led1[] = {11, 0};


// define directions for LED fade
#define UP 0
#define DOWN 1

// constants for min and max PWM
const int minPWM = 0;
const int maxPWM = 250;

// State Variable for Fade Direction
byte fadeDirection = UP;

// Global Fade Value
// fadeValue, fadeIncrement, fadeInterval
int fadeConsts[] = {0, 10, 20};

// millis() timing Variable, just for fading
unsigned long previousFadeMillis = 0;

void setup() {
  pinMode(led1[0], OUTPUT);
  pinMode(buttonPin, INPUT);
  // put pwmLED into known state (off)
  analogWrite(led1[0], minPWM);

//  Serial.begin(9600);
}

// Fade up/down function
void doTheFade(int led[], byte fadeDirection) {
  // Fade up
  if (fadeDirection == UP) {
    while (led[1] < maxPWM) {
      if (millis() - previousFadeMillis >= fadeConsts[2]) {

        led[1] = led[1] + fadeConsts[1];

        analogWrite(led[0], led[1]);
        previousFadeMillis = millis();
      };

    };
  // Fade down
  } else {
    while (led[1] > minPWM) {
      if (millis() - previousFadeMillis >= fadeConsts[2]) {

        led[1] = led[1] - fadeConsts[1];

        analogWrite(led[0], led[1]);
        previousFadeMillis = millis();
      };
    };
  };
}

void loop() {
  // Read button state
  buttonState[0] = digitalRead(buttonPin);
  if (buttonState[0] == HIGH) {
    buttonState[1] ++;
  };

  // Toggle LED
  if (buttonState[1] > 0 and buttonState[1] < (buttonState[2]) and buttonState[0] == LOW) {
    if (buttonState[3] == 1) {
      buttonState[3] = 2;
    } else {
      buttonState[3] = 1;
    }

  // Fade LED
  } else if (buttonState[1] == buttonState[2] and buttonState[0] == HIGH) {
    if (buttonState[3] == 1) {
      buttonState[3] = 4;
    } else {
      buttonState[3] = 3;
    }
  };

  // Do things based on button state
  switch (buttonState[3]) {
    case 1:
      led1[1] = minPWM;
      analogWrite(led1[0], minPWM);
      break;
    case 2:
      led1[1] = maxPWM;
      analogWrite(led1[0], maxPWM);
      break;
    case 3:
      doTheFade(led1, DOWN);
      buttonState[3] = 1;
      break;
    case 4:
      doTheFade(led1, UP);
      buttonState[3] = 2;
      break;
  };

  // Reset button state
  if (buttonState[0] == LOW) {
    buttonState[1] = 0;
  }

//  Serial.print(buttonState[3]);
//  Serial.print(" - ");
//  Serial.print(buttonState[1]);
//  Serial.print(" - ");
//  Serial.println(led1[1]);

}

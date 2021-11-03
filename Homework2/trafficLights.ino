const int carRedPin = 3; 
const int carYellowPin = 4;
const int carGreenPin = 5;

const int pedRedPin = 11;
const int pedGreenPin = 12;

const int buzzerPin = 8;
int buzzerTone = 300;

const int buttonPin = 2;

bool buttonState = LOW;

bool reading = HIGH;
bool lastReading = HIGH;

unsigned int lastDebounceTime = 0;
unsigned int debounceDelay = 50;

bool carRed = LOW;
bool carYellow = LOW;
bool carGreen = HIGH;

bool pedRed = HIGH;
bool pedGreen = LOW;

bool startAction = false;
bool inAction = false;
bool yellowOn = false;
bool countDown = false;

unsigned int redTime = 0;
unsigned int yellowTime = 0;
unsigned int pressedTime = 0;
unsigned int tickerTime = 0;

int expiringGreenTime = 10000;
int finalRedTime = 15000;
int finalYellowTime = 3000;
int finalGreenTime = 10000;


int slowBlinkingDelayStart = 1000;
int slowBlinkingDelayFinish = 1200;
int fastBlinkingDelayStart = 400;
int fastBlinkingDelayFinish = 700;

void setup() {
  /* declaring all the leds as output */
  pinMode(carRedPin, OUTPUT);
  pinMode(carYellowPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  pinMode(pedRedPin, OUTPUT);
  pinMode(pedGreenPin, OUTPUT);
  /* declaring the button pin as input-pullup */
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  /* initiating digitally the values for each led of the traffic lights */
  digitalWrite(carRedPin,carRed);
  digitalWrite(carYellowPin,carYellow);
  digitalWrite(carGreenPin,carGreen);
  digitalWrite(pedRedPin,pedRed);
  digitalWrite(pedGreenPin,pedGreen);
  /*reading if the button was pressed*/
  reading = digitalRead(buttonPin);
  /* debounce trick for reading the button values more accurately */
  if(reading != lastReading){
    lastDebounceTime = millis();
  }
  /**
   * if the button was pressed in the detected interval 
   * and the traffic light change is not in progress,
   * then we start the actions
  **/
  if(millis() - lastDebounceTime > debounceDelay && !startAction){ 
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState == LOW){
        startAction = true;
        inAction = true;      
      }
    }
  }
  /* the action has been triggered, we are starting the timer and switch to state 2 - yellow */
  if(inAction){
    pressedTime = millis();
    yellowOn = true;
    inAction = false;
   }
  /* after 10 seconds we can move on from green of the cars to the yellow light */
  if(millis() - pressedTime > finalGreenTime && yellowOn){
    carGreen = !carGreen;
    carYellow = !carYellow;
    yellowTime = millis();
    yellowOn = false;
  }
  /**
   * yellow only lasts 3 seconds so we are switching it off and moving on  
   * to the next state which is green for the pedestrians and red for cars
   * we are also starting the ticking sounds
  **/ 
  if(millis() - yellowTime > finalYellowTime && carYellow){
    carYellow = !carYellow;
    carRed = !carRed;
    pedRed = !pedRed;
    pedGreen = !pedGreen;
    redTime = millis();
    tickerTime = millis();
  }
  /* this portion is for slow ticking sound */
  if(millis() - tickerTime> slowBlinkingDelayStart && pedGreen){
    tone(buzzerPin, buzzerTone, 100);
  }
  if(millis() - tickerTime > slowBlinkingDelayFinish && pedGreen){
    noTone(buzzerPin);
    tickerTime = millis();
  }
  /* countDown is the boolean value that becomes true in the last seconds of green for the pedestrians */
  if(millis() - redTime > expiringGreenTime && pedGreen){
    countDown = true;
  }
  /* this portion is for fast ticking sound and flickering of the green light for the pedestrians */
  if(millis() - tickerTime> fastBlinkingDelayStart && countDown){
    tone(buzzerPin, buzzerTone, 100);
    pedGreen = !pedGreen;
  }
  if(millis() - tickerTime > fastBlinkingDelayFinish && countDown){
    noTone(buzzerPin);
    tickerTime = millis();
  }
  /* after the green time has expired we are switching the lights to the initial state */
  if(millis() - redTime > finalRedTime && pedGreen){
    carGreen = !carGreen;
    pedRed = !pedRed;
    carRed = !carRed;
    pedGreen = LOW;
    countDown = !countDown;
    tickerTime = 0;
    startAction = false;
  }
  lastReading = reading;
}

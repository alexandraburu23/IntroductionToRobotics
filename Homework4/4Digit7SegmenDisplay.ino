const int dataPin = 12; //DS
const int latchPin = 11; // STCP
const int clockPin = 10; //SHCP

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int displayCount = 4;

int displayDigits[displayCount] = {
  segD1,segD2,segD3,segD4
};

int digitArray[16] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

const int swPin = 2;
const int xPin = A0;
const int yPin = A1;

bool swState = LOW;
bool lastSwState = LOW;
int digitNumber[displayCount] = {0, 0, 0, 0};

int xValue = 0;
int yValue = 0;

bool joyMovedX = false;
bool joyMovedY = false;

int minThreshold =400;
int maxThreshold = 600;

bool dpState = false;
bool selected = false;
int displayNo = 0;
unsigned int pointTime = 0;

void setup (){
  /* pins for shift register */
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  /* declaring pins for the 4 displays*/
  for(int i = 0; i < displayCount; i++){
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  /* declaring pins for the joystick */
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop(){
  /* reading Ox and Oy values for the joystick movement */
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  /* browsing through displays with the joystick movements */
  /* we can browse if we have not selected yet a display to increment */
  /* if the value is less than the min threshold value, we are browsing left */
  if(xValue < minThreshold && !joyMovedX && !selected){
    if(displayNo < 3){
      displayNo++;
    }
    else{
      displayNo = 0;
    }
    joyMovedX = true;
  }
  /* opposite case, if the value is bigger that max threshold value, we are browsing right */
  if(xValue > maxThreshold && !joyMovedX && !selected){
    if(displayNo > 0){
      displayNo--;
    }
    else{
      displayNo = 3;
    }
    joyMovedX = true;
  }
  /* a x-value between threshold values means a stand-by position, nothing is moving */
  if(xValue >= minThreshold && xValue <= maxThreshold && !selected){
    joyMovedX = false;
  }
  /* reading button state */
  swState = digitalRead(swPin);
  /* if we press the button, we select a display to modify */
  if( swState != lastSwState && swState == LOW){
    selected = !selected;
    Serial.println("pushed");
   }
   /* in case we selected a display, then, by moving the joystick on the Oy axis we change the digit shown */
   /* we apply the same logic as in the Ox movement */
  if(selected){
    if(yValue > maxThreshold && !joyMovedY){
      if(digitNumber[displayNo] > 0){
        digitNumber[displayNo]--;
      }
      else{
        digitNumber[displayNo] = 9;
      }
      joyMovedY = true;
    }
    if(yValue < minThreshold && !joyMovedY){
      if(digitNumber[displayNo] < 9){
        digitNumber[displayNo]++;
      }
      else{
        digitNumber[displayNo] = 0;
      }
      joyMovedY = true;
    }
    if(yValue >= minThreshold && yValue <= maxThreshold ){
      joyMovedY = false;
    }
  }

  /* for debugging purposes */
  Serial.print(displayNo);
  Serial.print(" ");
  Serial.println(digitNumber[displayNo]);
  /* calling the function for displaying the values */
  writeNumber(displayNo,selected);
  /* changing the last state of the button */
  lastSwState = swState;
}

/* function for displaying the digits */
void writeNumber(int displayNo, int selected){
  /* we are using an array to save the digits for each display */
  for(int i = 0; i < displayCount; i++){
    int noToWrite = 0;
    /* we are treating the current display separately*/
    if(i == displayNo){
      /* if the display is selected the point has to light up */
      /* to make the point light up we can increment the bit-value with 1, corresponding with the dp-led */
      if(selected){
        noToWrite = digitArray[digitNumber[i]]+1;
      }
      /* if the display is not selected, the point has to blink */
      else{
        noToWrite = digitArray[digitNumber[i]];
        /* on */
        if(millis() - pointTime > 500){
          noToWrite = digitArray[digitNumber[i]]+1;
        }
        /* off */
        if(millis() - pointTime > 1000){
          noToWrite = digitArray[digitNumber[i]];
          pointTime = millis();
        }    
      }
    }
    /* the other displays are lit according to the value in the array */
    else{
      noToWrite = digitArray[digitNumber[i]];
    }
    /* displaying the values with the shift register */
    showDigit(i);
    writeReg(noToWrite);
    /* waiting for the electrical charge to run out */
    delay(6); 
  }
}

/* function for preparing the displays */
void showDigit(int displayNumber){
  for(int i = 0; i < displayCount; i++){
    digitalWrite(displayDigits[i],HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

/* function for writing the registers */
void writeReg(int digit){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin,HIGH);
}

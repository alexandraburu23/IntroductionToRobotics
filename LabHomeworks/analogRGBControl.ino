const int potGreenPin = A0; 
const int potBluePin = A1;
const int potRedPin = A2;

const int redPin = 11; 
const int greenPin = 9; 
const int bluePin = 10;

int potRedValue=0;
int potGreenValue=0;
int potBlueValue=0;

int ledRedValue=0;
int ledGreenValue=0;
int ledBlueValue=0;


void setup() {
  // put your setup code here, to run once:
    pinMode(potRedPin, INPUT); 
    pinMode(potGreenPin, INPUT); 
    pinMode(potBluePin, INPUT);
    
    pinMode(redPin, OUTPUT); 
    pinMode(greenPin, OUTPUT); 
    pinMode(bluePin, OUTPUT);

}

void loop() {
  potRedValue = analogRead(potRedPin);
    potGreenValue = analogRead(potGreenPin);
    potBlueValue = analogRead(potBluePin);

    ledRedValue = map(potRedValue, 0,1023,0,255);
    ledGreenValue = map(potGreenValue, 0,1023,0,255);
    ledBlueValue = map(potBlueValue, 0,1023,0,255);

//    ledRedValue = potRedValue/4;
//    ledGreenValue = potGreenValue/4;
//    ledBlueValue = potBlueValue/4;
    
    setColor(ledRedValue, ledGreenValue, ledBlueValue);
    Serial.print("Red: ");
    Serial.print(ledRedValue);
    Serial.print(" Green: ");
    Serial.print(ledGreenValue);
    Serial.print(" Blue: ");
    Serial.print(ledBlueValue);
    Serial.print("\n");
    delay(30);
}

void setColor(int red,int green, int blue)
{
      analogWrite(redPin, red);
      analogWrite(greenPin, green); 
      analogWrite(bluePin, blue); 
}

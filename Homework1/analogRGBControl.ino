const int potRedPin = A0; 
const int potBluePin = A1;
const int potGreenPin = A2;

const int redPin = 11;
const int bluePin = 10; 
const int greenPin = 9; 

int potRedValue = 0;
int potGreenValue = 0;
int potBlueValue = 0;

float ledRedValue = 0;
float ledGreenValue = 0;
float ledBlueValue = 0;

int maxAnalogValue = 255;
int maxPotValue = 1023;

void setup() {
    /* declaring the pins for potentiometers as input */
    pinMode(potRedPin, INPUT); 
    pinMode(potGreenPin, INPUT); 
    pinMode(potBluePin, INPUT);
    /* declaring the pins for RGB led as output */
    pinMode(redPin, OUTPUT); 
    pinMode(greenPin, OUTPUT); 
    pinMode(bluePin, OUTPUT);
    /* initialize serial communication at 9600 bits per second */
    Serial.begin(9600);
}

void loop() {
    /* reading potentiometer values for each color of the RGB led */
    potRedValue = analogRead(potRedPin);
    potGreenValue = analogRead(potGreenPin);
    potBlueValue = analogRead(potBluePin);
    /* converting the 0..1023 scale to 0..255 in order to correspond with the max-min values of the led intensity */
    ledRedValue = map(potRedValue, 0, maxPotValue, 0, maxAnalogValue);
    ledGreenValue = map(potGreenValue, 0, maxPotValue, 0, maxAnalogValue);
    ledBlueValue = map(potBlueValue, 0, maxPotValue, 0, maxAnalogValue);
    /* setting the values of the RGB led */
    setColor(ledRedValue, ledGreenValue, ledBlueValue);
    /* printing every value in serial*/
    Serial.print("Red: ");
    Serial.print(ledRedValue);
    Serial.print(" Green: ");
    Serial.print(ledGreenValue);
    Serial.print(" Blue: ");
    Serial.print(ledBlueValue);
    Serial.print("\n");
    delay(1);
}

void setColor(int red, int green, int blue)
{
    /* setting the intensity for each color */
    analogWrite(redPin, red);
    analogWrite(greenPin, green); 
    analogWrite(bluePin, blue); 
}

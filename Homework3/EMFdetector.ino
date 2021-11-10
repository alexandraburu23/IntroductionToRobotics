#define SAMPLE 300

const int detPin = A1; 
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int segSize = 8;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

const int noOfStates = 8;
bool digitMatrix[noOfStates][segSize - 1] = {
// a  b  c  d  e  f  g
  {0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0}, 
  {1, 1, 0, 0, 0, 0, 0}, 
  {1, 1, 1, 0, 0, 0, 0}, 
  {1, 1, 1, 1, 0, 0, 0}, 
  {1, 1, 1, 1, 1, 0, 0}, 
  {1, 1, 1, 1, 1, 1, 0}, 
  {1, 1, 1, 1, 1, 1, 1}
};

const int buzzerPin = 11;

int buzzerSoundStep = 250;
int buzzerSound = 0;

int valueArray[sample];   
unsigned long averageValue;      
int emfValue = 0;

/* diplay level depending on the value detected*/
void displayLevel(int level){
  for(int i=0; i<segSize-1;i++){
    digitalWrite(segments[i],digitMatrix[level][i]);
  }
  buzzerSound = level * buzzerSoundStep;
  analogWrite(buzzerPin, buzzerSound);
}

void setup() {
  pinMode(detPin, INPUT);
  for(int i=0; i<segSize; i++){
    pinMode(segments[i],OUTPUT);
  }
  Serial.begin(9600);
}
void loop() {
  /*reading a number of samples to approximate the EM level and reduce noise*/
  for(int i = 0; i < SAMPLE; i++){              
     valueArray[i] = analogRead(detPin);       
     averageValue += valueArray[i];                     
  }                                                               
  emfValue = averageValue / sample;   
  /*constraining the value to fit in the [0,100] interval*/                
  emfValue = constrain(emfValue, 0, 100);  
  /*transforming emfValue to a level that can be displayed with the light abd sound*/                                  
  if(emfValue < 15){
    displayLevel(0);          
  }
  else if(emfValue < 30){
    displayLevel(1);
  }
  else if(emfValue < 45){
    displayLevel(2);
  }
  else if(emfValue < 60){
    displayLevel(3);
  }
  else if(emfValue < 75){
    displayLevel(4);
  }
  else if(emfValue < 90){
    displayLevel(5);
  }
  else{
    displayLevel(6);
  }
  Serial.println(emfValue);                                                        
  averageValue = 0;                                

}

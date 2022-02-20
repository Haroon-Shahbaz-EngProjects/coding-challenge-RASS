//Code for colour sensor to read values and control servos based on which value it sees
//Author : Haroon Shahbaz 
#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6 //assigning servo pins

Servo topServo;
Servo bottomServo; //create variables for servo

int frequency = 0;
int colour=0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  topServo.attach(7);
  bottomServo.attach(8);

  Serial.begin(9600);
}

void loop() {

  topServo.write(115); //close off top to prevent outside light from affecting data of gobstopper colour
  delay(500);
  
  for(int i = 115; i > 65; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(500);
  
  colour = readColor(); //call function to scan for colour
  delay(10);  

  switch (colour) { //rotate bottom servo to correct orientation to drop off gobstopper into correct location
    case 1:
    bottomServo.write(50);
    break;
    case 2:
    bottomServo.write(100); //cases for each colour
    break;
    case 3:
    bottomServo.write(150);
    break;
    case 0:
    break;
  }
  delay(300);
  
  colour=0;
}

// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency of Red value
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  delay(50);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency of green value
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  delay(50);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency of blue value
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  delay(50);

  if(R<45 & R>32 & G<65 & G>55){
    colour = 1; // Red
  }
  if(R<53 & R>40 & G<53 & G>40){
    colour = 2; // Green
  }
  if(R<38 & R>24 & G<44 & G>30){
    colour = 3; // Yellow
  }
  return colour;  
}

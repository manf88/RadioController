#include "RCSwitch.h"

#define triggerPin 8
#define echoPin 7
#define triggerDistance 15
#define timeout 5000

#define bits 24
#define signalOn 21589
#define signalOff 21588
    
RCSwitch mySwitch = RCSwitch();

bool isActive = false;

void setup() {
  //setup pins for the ultrasonic sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);
}

void loop() {
  //example code from http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/
  long duration, distance;

  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.print(distance);
  Serial.println(" cm");

  if(distance < triggerDistance){
    //toggle the current state
    isActive = !isActive;
     
    if(isActive){
      mySwitch.send(signalOn, bits);
    }
    else{
      mySwitch.send(signalOff, bits);
    }
    
    //add a delay here to prevent the switch from "flipping"
    delay(timeout);
  }
}

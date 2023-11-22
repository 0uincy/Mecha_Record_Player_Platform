// Moves stepper motor linear actuatior with sinusoidal motion profile

#include <math.h>

void move(int dir, int length, int profile[]);
void profile(int arr[], int length, int acc);

const int button1 = 36;   //input button 1
const int button2 = 39;   //input button 2

const int dirPin1 = 12;   //stepper motor driver 1 direction pin
const int stepPin1 = 14;  //stepper motor driver 1 step pin
const int enPin1 = 13;    //stepper motor driver 1 enable pin
const int dirPin2 = 33;   //stepper motor driver 2 direction pin
const int stepPin2 = 32;  //stepper motor driver 2 step pin
const int enPin2 = 25;    //stepper motor driver 2 enable pin

int input1 = 0;
int input2 = 0;
int direction = 0;

//160 steps/mm
const int travel = 24000; //steps for total travel
const int acceleration = 32000; 

int stepDelay[travel];

void setup(){ 
  // Initialize pins
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin1, OUTPUT);
  pinMode(enPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(enPin2, OUTPUT);

  profile(stepDelay, travel, acceleration);

  digitalWrite(enPin1, LOW);
  digitalWrite(enPin2, LOW);
}
 
void loop()
{  
  input1 = digitalRead(button1);
  input2 = digitalRead(button2);

  // Reads current position state, moves motors, then updates state
  if (input1 == HIGH){
    if (direction == LOW){
      digitalWrite(dirPin1, LOW);
      digitalWrite(dirPin2, LOW);
      move(direction, travel, stepDelay);
      direction = 1;
    }
    else if (direction == HIGH){
      digitalWrite(dirPin1, HIGH);
      digitalWrite(dirPin2, HIGH);
      move(direction, travel, stepDelay);
      direction = 0;
    }
  }

  delayMicroseconds(10000);
}

//Creates step delay timing motion profile
void profile(int arr[], int length, int acc){
  for (int i = 0; i < length/4; i++){
    arr[i] = 2*acc*i*i/length;
  }
  for (int i = length/4; i < length/2; i++){
    arr[i] = 2*acc*i-2*acc*i*i/length;
  }
  for (int i = length/2; i < length*3/4; i++){
    arr[i] = acc*-4*(i-length/2)/length;
  }
  for (int i = length*3/4; i < length; i++){
    arr[i] = acc*-(1-4*(i-length*3/4)/length);
  }
}

//Function that activates motors and moves according to motion profile
void move(int dir, int steps, int profile[]){
  digitalWrite(enPin1, LOW);
  digitalWrite(enPin2, LOW);
  for (int i = 0; i < steps; i++){
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(stepDelay[i]);
    digitalWrite(stepPin1, LOW);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(stepDelay[i]);
  }
  if (dir == LOW){
    digitalWrite(enPin1, HIGH);
    digitalWrite(enPin2, HIGH);
  }
}
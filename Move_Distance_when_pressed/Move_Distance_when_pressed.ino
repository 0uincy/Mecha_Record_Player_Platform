//Move two stepper motors with acceleration parameters between two fixed
//positions with a button press.

#include <AccelStepper.h>

const int goPin = 13;  //activation button pinout
const int ms1 = 23;
const int ms2 = 22;
const int spread = 21;

//Define motors & their respective direction and step pins
AccelStepper stepper1( AccelStepper::DRIVER, 33 , 25 );    //step, dir
AccelStepper stepper2( AccelStepper::DRIVER, 27 , 14 );

float acceleration = 35;    //in mm/s^2
float maxSpeed = 250;       //in mm/s
int travelDistance = 150;   //in mm
int conversion = 16*10;     //steps/rotation * mm/rotation

float acc;
float speed;
long int travel;
int state;
int go;
int stop;

void setup()
{ 
  //Convert distance & acceleration to steps
  acc = acceleration*conversion;
  speed = maxSpeed*conversion;
  travel = travelDistance*conversion;

  go = 0;     //value of 1 to initiate motor movement
  state = 0;  //0 = bottom, 1 = top

  //Initialize pins & invert enable pin
  pinMode(goPin,INPUT);
  pinMode(ms1, OUTPUT);
  digitalWrite(ms1, HIGH);
  pinMode(ms2, OUTPUT);
  digitalWrite(ms2, HIGH);
  pinMode(spread, OUTPUT);
  digitalWrite(spread, LOW);
  stepper1.setEnablePin(32);
  stepper2.setEnablePin(26); 
  stepper1.setPinsInverted(true, false, true);   //direction, step, enable
  stepper2.setPinsInverted(false, false, true);

  //Define motor parameters
  stepper1.setMaxSpeed(speed);
  stepper2.setMaxSpeed(speed);
  stepper1.setAcceleration(acc);
  stepper2.setAcceleration(acc);

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
}
 
void loop() //Movement control
{  
  go = digitalRead(goPin); //read control pin

  if (go == HIGH){
    //Go up
    if (state == 0){ 
      stepper1.enableOutputs();
      stepper2.enableOutputs();
      
      stepper1.moveTo(travel);
      stepper2.moveTo(travel);

      while (stepper1.distanceToGo() != 0){
        stepper1.run();
        stepper2.run();
      }

      state = 1;
    }

    //Go down and disable motors
    else if (state == 1){
      stepper1.enableOutputs();
      stepper2.enableOutputs();
      
      stepper1.moveTo(0);
      stepper2.moveTo(0);

      while (stepper1.distanceToGo() != 0){
        stepper1.run();
        stepper2.run();
      }

      stepper1.disableOutputs();
      stepper2.disableOutputs();

      state = 0;
    }
  }

  delay(10);
}
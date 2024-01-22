//Move two stepper motors with acceleration parameters between two fixed
//positions with a button press.

#include <AccelStepper.h>

const int goPin = 36;  //activation button pinout

//Define motors & their respective direction and step pins
AccelStepper stepper1( AccelStepper::DRIVER, 14 , 12 );
AccelStepper stepper2( AccelStepper::DRIVER, 32 , 33 );

float acceleration = 0.035; //in m/s^2
float maxSpeed = 250;       //in mm/s
int travelDistance = 150;   //in mm
int conversion = 160;       //in steps/mm

float acc;
float speed;
long int travel;
int state;
int go;
int stop;

void setup()
{ 
  //Convert distance & acceleration to steps
  acc = acceleration*1000*conversion;
  speed = maxSpeed*conversion;
  travel = travelDistance*conversion;

  go = 0;    //value of 1 to initiate motor movement
  state = 0; //0 for down position, 1/HIGH for up position

  //Initialize pins & invert enable pin
  pinMode(goPin,INPUT);
  stepper1.setEnablePin(13);
  stepper2.setEnablePin(25); 
  stepper1.setPinsInverted(false, false, true); //direction, step, enable
  stepper2.setPinsInverted(false, false, true);

  //Define motor parameters
  stepper1.setMaxSpeed(speed);
  stepper2.setMaxSpeed(speed);
  stepper1.setAcceleration(acc);
  stepper2.setAcceleration(acc);
  stepper1.setCurrentPosition(travel);
  stepper2.setCurrentPosition(travel);
}
 
void loop() //Movement control
{  
  go = digitalRead(goPin); //read control pin

  if (go == HIGH){
    //Go down and disable motors
    if (state == 0){
      stepper1.enableOutputs();
      stepper2.enableOutputs();

      stepper1.moveTo(travel);
      stepper2.moveTo(travel);
      while (stepper1.distanceToGo()!= 0){
        stepper1.run();
        stepper2.run();
      }

      stepper1.disableOutputs();
      stepper2.disableOutputs();

      state = 1;
    }

    //Go up
    else if (state == 1){ 
      stepper1.enableOutputs();
      stepper2.enableOutputs();
      
      stepper1.moveTo(0);
      stepper2.moveTo(0);
      while (stepper1.distanceToGo()!= 0){
        stepper1.run();
        stepper2.run();
      }

      state = 0;
    }
  }

  delay(1);
}
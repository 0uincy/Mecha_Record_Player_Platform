// Manual Control of 2 Stepper Motors at a Fixed Speed
// ESP32s WROOM Dev Module, TMC2208 Drivers

#include <AccelStepper.h>

// Define control pins & respective variables
const int Cpin = 36;  // clockwise
const int CCpin = 39; // counter clockwise
int Cwise = 0;
int CCwise = 0;

// Define default speed
const int speed = 3200;

// Define motors & their respective direction and step pins
AccelStepper stepper1( AccelStepper::DRIVER, 14 , 12 );
AccelStepper stepper2( AccelStepper::DRIVER, 32 , 33 );

void setup()
{ 
  // Initialize pins & invert enable pin
  pinMode(Cpin,INPUT);
  pinMode(CCpin,INPUT);
  stepper1.setEnablePin( 13 );
  stepper2.setEnablePin( 25 ); 
  stepper1.setPinsInverted( false, false, true );
  stepper2.setPinsInverted( false, false, true );

  // Define motor parameters
  stepper1.setMaxSpeed( 6400 );
  stepper2.setMaxSpeed( 6400 );
  stepper1.setSpeed(speed);
  stepper2.setSpeed(speed);

  // Enable motors
  stepper1.enableOutputs();
  stepper2.enableOutputs();
}
 
void loop() // Movement control
{  
  // Read control pins
  Cwise = digitalRead(Cpin);
  CCwise = digitalRead(CCpin);

  // Clockwise motion if Cpin high
  if (Cwise == HIGH){ 
    while (Cwise == HIGH){
      stepper1.setSpeed(speed);
      stepper2.setSpeed(speed);
      stepper1.runSpeed();
      stepper2.runSpeed();
      Cwise = digitalRead(Cpin);
    }
  }

  // Counter clockwise motion if  CCpin high
  else if (CCwise == HIGH){ 
    while (CCwise == HIGH){
    stepper1.setSpeed(-1*speed);
    stepper2.setSpeed(-1*speed);
    stepper1.runSpeed();
    stepper2.runSpeed();
    CCwise = digitalRead(CCpin);
    }
  }

  // No motion if Cpin and CCpin are low
  else{
    stepper1.setSpeed(0);
    stepper2.setSpeed(0);
    stepper1.runSpeed();
    stepper2.runSpeed();
  }
}
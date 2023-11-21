// Manual Control of 2 Stepper Motors at a Fixed Speed
// ESP32s WROOM Dev Module, TMC2208 Drivers

#include <AccelStepper.h>
#include <MultiStepper.h>

// Define control pins & respective variables
const int Cpin = 36;  // clockwise
const int CCpin = 39; // counter clockwise
int Cwise = 0;
int CCwise = 0;

// Define default speed
const int speed = 32000;

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
  stepper1.setMaxSpeed( 32000 );
  stepper2.setMaxSpeed( 32000 );
  stepper1.setAcceleration( 64000 );
  stepper2.setAcceleration( 64000 );
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
    stepper1.runToNewPosition( 24000 );
    stepper1.disableOutputs();
    stepper2.runToNewPosition( 24000 );
    stepper2.disableOutputs();
  }

  // Counter clockwise motion if  CCpin high
  else if (CCwise == HIGH){ 
    stepper1.enableOutputs();
    stepper1.runToNewPosition( 0 );
    stepper2.enableOutputs();
    stepper2.runToNewPosition( 0 );
  }

  // No motion if Cpin and CCpin are low
  else{
  }
}
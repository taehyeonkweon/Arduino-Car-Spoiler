#include <Stepper.h>
#include <Servo.h>

#define STEPS_PER_REVOLUTION 200  // The number of steps per revolution
#define ANGLE_PER_STEP 1.8        // 360 degrees / 200 steps per revolution = 1.8 degrees per step
#define DESIRED_ANGLE 70          // Desired angle to turn in degrees

// initialize the stepper library on pins 8, 9, 10, 11:
Stepper myStepper(STEPS_PER_REVOLUTION, 8, 9, 10, 11);
int button =  6; 
bool buttonState = false;
bool lastButtonState = false;
bool direction = true;  // true for positive direction, false for negative direction


void setup() {
  // set the speed at 10 rpm:
  myStepper.setSpeed(10);
  pinMode(button, INPUT_PULLUP);  

}
void loop() {
  buttonState = digitalRead(button);

  if (buttonState != lastButtonState) {  // Check if the button state has changed
    if (buttonState == LOW) {            // Check if the button is pressed
      if (direction) {
        moveStepperByAngle(-DESIRED_ANGLE); // Move by desired degrees in negative direction
      } else {
        moveStepperByAngle(DESIRED_ANGLE);  // Move by desired degrees in positive direction
      }
      direction = !direction;  // Toggle direction for the next button press
    }
    lastButtonState = buttonState;
  }
}

void moveStepperByAngle(float angle) {
  int steps = angle / ANGLE_PER_STEP;
  if (steps > 0) {
    for (int i = 0; i < steps; i++) {
      myStepper.step(1);
      delayMicroseconds(300);  // add a short delay between steps
    }
  } else {
    for (int i = 0; i > steps; i--) {
      myStepper.step(-1);
      delayMicroseconds(300);  // add a short delay between steps
    }
  }
}
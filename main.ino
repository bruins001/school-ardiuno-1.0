#include <AFMotor.h>

AF_DCMotor leftFrontMotor(1);
AF_DCMotor leftBackMotor(2);
AF_DCMotor rightFrontMotor(3);
AF_DCMotor rightBackMotor(4);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  int motorSpeed = 200;

  leftFrontMotor.setSpeed(motorSpeed);
  leftFrontMotor.run(FORWARD);
  leftBackMotor.setSpeed(motorSpeed);
  leftBackMotor.run(FORWARD);
  rightFrontMotor.setSpeed(motorSpeed);
  rightFrontMotor.run(FORWARD);
  rightBackMotor.setSpeed(motorSpeed);
  rightBackMotor.run(FORWARD);
}

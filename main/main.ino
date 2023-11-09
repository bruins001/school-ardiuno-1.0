#include <AFMotor.h>

AF_DCMotor leftFrontMotor(1);
AF_DCMotor leftBackMotor(2);
AF_DCMotor rightFrontMotor(3);
AF_DCMotor rightBackMotor(4);

int get_distance_sonic();

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int motorSpeedForward = 200;
  int motorSpeedBrake = 0;

  int distance = get_distance_sonic();
  Serial.println(distance);
  if (distance <= 20) {
    leftFrontMotor.setSpeed(motorSpeedBrake);
    leftFrontMotor.run(RELEASE);
    leftBackMotor.setSpeed(motorSpeedBrake);
    leftBackMotor.run(RELEASE);
    rightFrontMotor.setSpeed(motorSpeedBrake);
    rightFrontMotor.run(RELEASE);
    rightBackMotor.setSpeed(motorSpeedBrake);
    rightBackMotor.run(RELEASE);
  } else {
    leftFrontMotor.setSpeed(motorSpeedForward);
    leftFrontMotor.run(FORWARD);
    leftBackMotor.setSpeed(motorSpeedForward);
    leftBackMotor.run(FORWARD);
    rightFrontMotor.setSpeed(motorSpeedForward);
    rightFrontMotor.run(FORWARD);
    rightBackMotor.setSpeed(motorSpeedForward);
    rightBackMotor.run(FORWARD);
  }
}

int get_distance_sonic(){
  long duration;
  int distance;

  // reset sonic 
  digitalWrite(A1, LOW);
  delayMicroseconds(2);

  // send sonic sound
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);

  // get duration from Sonic sensor
  duration = pulseIn(A0, HIGH);

  // calc distance
  distance = ((duration*0.034)/2);


  return distance;
}

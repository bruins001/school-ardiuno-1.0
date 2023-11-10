#include <AFMotor.h>
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

AF_DCMotor leftFrontMotor(1);
AF_DCMotor leftBackMotor(2);
AF_DCMotor rightFrontMotor(3);
AF_DCMotor rightBackMotor(4);

HUSKYLENS huskylens;
SoftwareSerial mySerial(9, 10); // RX, TX
int stopLichtRoodId = 1;

int get_distance_sonic();

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  Serial.begin(115200);
  mySerial.begin(9600);
  while (!huskylens.begin(mySerial))
  {
      Serial.println(F("Begin failed!"));
      Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
      Serial.println(F("2.Please recheck the connection."));
      delay(100);
  }
}

void loop() {
  int motorSpeedForward = 200;
  int motorSpeedBrake = 0;

  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else
  {
      while (huskylens.available())
      {
          HUSKYLENSResult result = huskylens.read();
          if (result.ID == stopLichtRoodId) {
            // Stopt voertuig
            leftFrontMotor.setSpeed(motorSpeedBrake);
            leftFrontMotor.run(RELEASE);
            leftBackMotor.setSpeed(motorSpeedBrake);
            leftBackMotor.run(RELEASE);
            rightFrontMotor.setSpeed(motorSpeedBrake);
            rightFrontMotor.run(RELEASE);
            rightBackMotor.setSpeed(motorSpeedBrake);
            rightBackMotor.run(RELEASE);
            return;
          }
      }    
  }

  int distance = get_distance_sonic();
  if (distance <= 20) {
    // Stopt voertuig
    leftFrontMotor.setSpeed(motorSpeedBrake);
    leftFrontMotor.run(RELEASE);
    leftBackMotor.setSpeed(motorSpeedBrake);
    leftBackMotor.run(RELEASE);
    rightFrontMotor.setSpeed(motorSpeedBrake);
    rightFrontMotor.run(RELEASE);
    rightBackMotor.setSpeed(motorSpeedBrake);
    rightBackMotor.run(RELEASE); 
  } else {
    // Auto laten rijden
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

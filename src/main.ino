// ====================================================================
// DISCLAIMER:
// This code is provided as-is for educational and experimental 
// purposes only. The author makes no representations or warranties of 
// any kind concerning the safety, suitability, or accuracy of this 
// code. Use at your own risk. The author assumes no liability for any 
// damages, system failures, security breaches, or network issues 
// resulting from the use or implementation of this script.
// ====================================================================

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
float Ax;
float Ay;
float Az;
float roll;
float pitch;

int latchPin = 5;
int clockPin = 18;
int dataPin = 23;

byte led;

// If You want Calibrated results, you must rotate
// your board to all possible orientations, and 
// record your velues of xMax, xMin, yMax, yMin
// zMax, zMin. Put in your values and then
// uncomment the code below. Don't use my values, you have
// to measure your own for it to work.

// float xMax= 1.05;
// float xMin= -0.95;
// float yMax= .99;
// float yMin= -1.00;
// float zMax= 1.15 ;
// float zMin= -0.89;

// float xOffset = (xMax+xMin)/2;
// float yOffset = (yMax+yMin)/2;
// float zOffset = (zMax+zMin)/2;

// float xScale = 2/(xMax -xMin);
// float yScale = 2/(yMax - yMin);
// float zScale = 2/(zMax -zMin);

Adafruit_MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mpu.begin();
  Serial.println("MPU6050 Started!");
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  pinMode(latchPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Ax=a.acceleration.x/9.81;
  Ay=a.acceleration.y/9.81;
  Az=a.acceleration.z/9.81;

//Uncomment these lines of code to do the callibration
//This will only work if you have measured your max
//and min values, and put them in at the top of the code

  // Ax = xScale*(Ax-xOffset);
  // Ay = yScale*(Ay-yOffset);
  // Az = zScale*(Az-zOffset);

  pitch = -(atan2(Ay,Az) * (180/3.14));
  roll = atan2(Ax,Az) * (180/3.14);


  Serial.print("roll: ");
  Serial.print(roll);
  Serial.print(',');
  Serial.print("pitch: ");
  Serial.println(pitch);

  delay(50);


  if (pitch > 45.0) {
    led = 0x01;        // Q0
  }
  else if (pitch > 30.0) {
    led = 0x02;        // Q1
  }
  else if (pitch > 5.0) {
    led = 0x04;        // Q2
  }
  else if (pitch >= -5.0) {
    led = 0x08;        // Q3
  }
  else if (pitch >= -30.0) {
    led = 0x10;        // Q4
  }
  else if (pitch >= -45.0) {
    led = 0x20;        // Q5
  }
  else {
    led = 0x40;        // Q6
  }

  // Q7 is automatically OFF because bit 7 = 0

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, led);
  digitalWrite(latchPin, HIGH);

}

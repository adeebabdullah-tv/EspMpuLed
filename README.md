# ESP32 MPU6050 Angle Indicator

An open-source embedded electronics project that uses an MPU6050
accelerometer/gyroscope, ESP32, and 74HC595 shift register to measure
orientation and display the angle using LEDs.

## 🔧 Components

- ESP32
- MPU6050
- 74HC595N shift register
- LEDs
- Current-limiting resistors
- Breadboard
- Jumper wires

## ⚙️ How It Works

MPU6050
   ↓
ESP32
   ↓
Calculate angle
   ↓
Map angle to LED pattern
   ↓
74HC595
   ↓
LED indicators

The MPU6050 provides acceleration data to the ESP32. The ESP32 uses
the sensor readings to calculate the orientation angle.

The calculated angle is then converted into an LED pattern and sent
to the 74HC595 using three control lines:

- Data
- Clock
- Latch

The 74HC595 then controls the LEDs.

## 🧭 MPU6050 Calibration

Before using the angle measurements, the MPU6050 was calibrated to
reduce the offset in the sensor readings.

Calibration is important because even when the sensor is stationary,
the raw accelerometer readings may not be exactly what we expect.

## 💡 LED Angle Indicator

Different angle ranges correspond to different LEDs.

For example:

```text
Angle
  ↓
[ Angle range ]
      ↓
[ LED pattern ]
      ↓
[ 74HC595 ]
      ↓
[ LEDs ]

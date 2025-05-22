#include <Wire.h>
#include <DFRobot_DF2301Q.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
DFRobot_DF2301Q_I2C asr;

#define servo_MIN 150       // Minimum pulse length for servo (0 degrees)
#define servo_MAX 450       // Maximum pulse length for servo (180 degrees)
#define us_MIN 600
#define us_MAX 2400
#define servo_FREQ 50       // Servos run at ~50 Hz
#define servo_COUNT 10      // Total number of servos

uint8_t servonum = 0;     // Servo counter

void setup() {
  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(50);

  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection.");
    delay(3000);
  }

  Serial.println("Begin ok!");
}

 int convert_degree (int degree) {
    return map(degree, 0, 180, servo_MIN, servo_MAX);     // Converts angle to readable pulse length
  }                                                       // Takes angle 0-180 and sends out pulselen between min and max

void loop() {

  uint8_t CMDID = asr.getCMDID();

  if (CMDID > 0) {
    Serial.println(CMDID);

      switch(CMDID) {
        case 5:
          // Wing Servos
          Serial.println("Opening Wing Servos");
          for (uint16_t pulselen = 154; pulselen < 399; pulselen += 3) {
            pwm.setPWM(0, 0, pulselen);
            pwm.setPWM(1, 0, (553-pulselen));
            delay(10);
          }

          Serial.println("Mask opened");
          break;

        case 6:
          // Wing Servos
          Serial.println("Closing Wing Servos");
          for(uint16_t pulselen = 399; pulselen > 154 ; pulselen -= 3) {
            pwm.setPWM(0, 0, pulselen);
            pwm.setPWM(1, 0, (580-pulselen));
            delay(10);
          }

          Serial.println("Mask closed");
          break;
      }
    }
  }
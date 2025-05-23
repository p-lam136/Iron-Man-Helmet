#include <Wire.h>
#include <DFRobot_DF2301Q.h>
#include <Adafruit_PWMServoDriver.h>

#define servo_MIN 150       // Minimum pulse length for servo (0 degrees)
#define servo_MAX 450       // Maximum pulse length for servo (180 degrees)
#define servo_FREQ 50       // Servos run at ~50 Hz
#define servo_COUNT 10      // Total number of servos

uint8_t servonum = 0;     // Servo counter

DFRobot_DF2301Q_I2C asr;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("Starting Wire...");
  Wire.begin();
  Serial.println("Wire started");

  Serial.println("PWM Starting");
  pwm.begin();
  Serial.println("PWM Started");
  pwm.setPWMFreq(50);
  delay(50);

  Serial.println("About to call asr.begin()");
  bool started = asr.begin();
  Serial.print("asr.begin() returned: ");
  Serial.println(started);

  if (!started) {
    Serial.println("Communication with device failed");
  } else {
    Serial.println("Begin ok!");
  }
}

  int convert_degree (int degree) {
    return map(degree, 0, 180, servo_MIN, servo_MAX);     // Converts angle to readable pulse length
  }


void loop() {
  uint8_t CMDID = asr.getCMDID();

  if (CMDID > 0) {
    Serial.println(CMDID);
  }

  switch(CMDID) {
      case 5:
        // BROW Side
          Serial.println("Opening Brow Sides");
          for (uint16_t pulselen = 30; pulselen <= 90; pulselen++) {
            pwm.setPWM(2, 0, convert_degree(pulselen));
            pwm.setPWM(3, 0, convert_degree(30 + 90 - pulselen));
          }
          Serial.println("Brow Side Opened");

        // Wing Servos
        Serial.println("Opening Wing Servos");
        for (uint16_t pulselen = 154; pulselen < 399; pulselen += 3) {
          pwm.setPWM(0, 0, pulselen);
          pwm.setPWM(1, 0, (553-pulselen));
          delay(10);
        }

        Serial.println("Mask opened");
        delay(1);
        break;

      case 6:

        // Wing Servos
        Serial.println("Closing Wing Servos");
        for(uint16_t pulselen = 399; pulselen > 154 ; pulselen -= 3) {
          pwm.setPWM(0, 0, pulselen);
          pwm.setPWM(1, 0, (580-pulselen));
          delay(10);
        }

        // BROW Sides
          Serial.println("Closing Brow Sides");
          for (uint16_t pulselen = 90; pulselen >= 30; pulselen--) {
            pwm.setPWM(2, 0, convert_degree(pulselen));
            pwm.setPWM(3, 0, convert_degree(30 + 90 - pulselen));
          }
          Serial.println("Brow Sides Closed");

        break;
    }
}
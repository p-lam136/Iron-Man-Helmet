#include <Wire.h>
#include <DFRobot_DF2301Q.h>
#include <Adafruit_PWMServoDriver.h>

#define servo_MIN 150       // Minimum pulse length for servo (0 degrees)
#define servo_MAX 450       // Maximum pulse length for servo (180 degrees)
#define servo_FREQ 50       // Servos run at ~50 Hz

uint8_t servonum = 0;     // Servo counter

DFRobot_DF2301Q_I2C asr;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(115200);
  delay(500);

  Wire.begin();

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
        // CHEEKS
        Serial.println("Cheeks Opening");
        for (uint16_t pulselen = 90; pulselen >= 20; pulselen--) {
          pwm.setPWM(12, 0, convert_degree(pulselen));
          pwm.setPWM(13, 0, convert_degree(90 + 20 - pulselen));
        }
        Serial.println("Cheeks Opened");

        // NOSE Sides
        Serial.println("Opening Nose Sides");
        for (uint16_t pulselen = 86; pulselen >= 10; pulselen--) {
          pwm.setPWM(8, 0, convert_degree(86 + 10 - pulselen));
          pwm.setPWM(9, 0, convert_degree(pulselen));
        }
        Serial.println("Nose Sides Opened");

        //BROW Center
        Serial.println("Opening Brow Center");
        for (uint16_t pulselen = 120; pulselen >= 40; pulselen--) {
          pwm.setPWM(4, 0, convert_degree(pulselen));
        }
        Serial.println("Brow Center Opened");

        // BROW Side
        Serial.println("Opening Brow Sides");
        for (uint16_t pulselen = 30; pulselen <= 90; pulselen++) {
          pwm.setPWM(2, 0, convert_degree(pulselen));
          pwm.setPWM(3, 0, convert_degree(30 + 90 - pulselen));
        }
        Serial.println("Brow Side Opened");

        // NOSE Center
        Serial.println("Opening Nose Center");
        for (uint16_t pulselen = 110; pulselen >= 1; pulselen--) {
          pwm.setPWM(5, 0, convert_degree(pulselen));
        }
        Serial.println("Nose center opened");

        // EYES
        analogWrite(6, 0);
        Serial.println("LED OFF");

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

        //NOSE Center
        Serial.println("Closing Nose Center");
        for (uint16_t pulselen = 1; pulselen <= 110; pulselen++) {
          pwm.setPWM(5, 0, convert_degree(pulselen));
        }
        Serial.println("Nose Center Closed");

        // BROW Sides
        Serial.println("Closing Brow Sides");
        for (uint16_t pulselen = 90; pulselen >= 30; pulselen--) {
          pwm.setPWM(2, 0, convert_degree(pulselen));
          pwm.setPWM(3, 0, convert_degree(30 + 90 - pulselen));
        }
        Serial.println("Brow Sides Closed");

        // Brow Center
        Serial.println("Closing Brow Center");
        for (uint16_t pulselen = 40; pulselen <= 120; pulselen++) {
          pwm.setPWM(4, 0, convert_degree(pulselen));
        }
        Serial.println("Brow Center Closed");

        // NOSE Sides
        Serial.println("Closing Nose Sides");
        for (uint16_t pulselen = 10; pulselen <= 86; pulselen++) {
          pwm.setPWM(8, 0, convert_degree(86 + 10 - pulselen));
          pwm.setPWM(9, 0, convert_degree(pulselen));
        }
        Serial.println("Nose Sides Closed");

        // CHEEKS
        Serial.println("Cheeks Closing");
        for (uint16_t pulselen = 20; pulselen <= 90; pulselen++) {
          pwm.setPWM(12, 0, convert_degree(pulselen));
          pwm.setPWM(13, 0, convert_degree(90 + 20 - pulselen));
        }
        Serial.println("Cheeks Closed");

        // EYES
        analogWrite(6, 200);
        Serial.println("LED ON");

        Serial.println("Mask Closed");
        break;

    
  }
}
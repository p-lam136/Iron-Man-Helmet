#include <Wire.h>
#include <DFRobot_DF2301Q.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
DFRobot_DF2301Q_I2C asr;

#define servo_MIN 150       // Minimum pulse length for servo (0 degrees)
#define servo_MAX 450       // Maximum pulse length for servo (180 degrees)
#define servo_FREQ 50       // Servos run at ~50 Hz
#define servo_COUNT 10      // Total number of servos

uint8_t servonum = 0;     // Servo counter

void setup() {
  Serial.begin(115200);

  pwm.begin();
  pwm.setPWMfreq(50);
  delay(50);

  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection.");
    delay(3000);
  }

  serial.println("Begin ok!");
 
}

 int convert_degree (int degree) {
    return map(degree, 0, 180, servo_MIN, servo_MAX);     // Converts angle to readable pulse length
  }

void loop() {

  uint8_t CMDID = asr.getCMDID();

  if CMDID > 0;
  Serial.println(CMDID);

  switch(CMDID) {
    case 5:
      // SIDE NOSE
      serial.println("Opening nose sides")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      // CENTER NOSE
      serial.println("Opening center nose")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      // CHEEKS
      serial.println("Opening cheeks")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      // SIDE EYEBROW
      serial.println("Opening side eyebrows")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      // CENTER EYEBROW
      serial.println("Opening center eyebrow")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      Serial.println("Mask opened")
      break;

    case 6:
      // SIDE NOSE
      serial.println("Closing nose sides")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      // CENTER NOSE
      serial.println("Closing center nose")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      // CHEEKS
      serial.println("Closing cheeks")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      // SIDE EYEBROW
      serial.println("Closing side eyebrows")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      // CENTER EYEBROW
      serial.println("Closing center eyebrow")
      for(uint16_t pulselen = ; pulselen >= ; pulselen ))
      pwm.setpwm()
      pwm.setpwm()

      Serial.println("Mask closed")
      break;


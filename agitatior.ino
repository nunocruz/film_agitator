#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "rgb_lcd.h"


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);
int steps = 200;

//LCD
rgb_lcd lcd;
boolean refreshLCD = true;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  while (!Serial);
  Serial.println("Stepper test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  myMotor->setSpeed(255);  // 10 rpm

  lcd.begin(16, 2); 
}

void loop() {
  if (refreshLCD) {
    lcd.setCursor(0, 0);
    lcd.print("DOUBLE coil step");
    lcd.setCursor(0, 1);
    lcd.print(steps);
    refreshLCD = false;
  }

  if (steps > 0) {
    myMotor->step(steps, FORWARD, DOUBLE);
  }
}

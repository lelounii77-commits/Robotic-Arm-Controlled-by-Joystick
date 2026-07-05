/*
  Arduino-Based Robotic Arm Controlled by Joystick
  --------------------------------------------------
  Reads analog values from a joystick module (VRx, VRy) and maps
  them to servo angles (0-180 degrees) to control a simple robotic arm.

  Components:
    - Arduino UNO
    - Joystick module (VRx -> A0, VRy -> A1, SW -> D2 [optional])
    - 2-4 Servo motors (Base -> D9, Shoulder/Grip -> D10, ...)

  Wiring:
    Joystick VCC  -> 5V
    Joystick GND  -> GND
    Joystick VRx  -> A0
    Joystick VRy  -> A1
    Joystick SW   -> D2 (optional, used for grip open/close toggle)

    Servo 1 (Base)  signal -> D9
    Servo 2 (Grip)  signal -> D10
    Servos VCC -> 5V (external power supply recommended)
    Servos GND -> GND (common ground with Arduino)
*/

#include <Servo.h>

// ---------- Pin Configuration ----------
const int JOY_VRX_PIN = A0;   // Joystick X-axis
const int JOY_VRY_PIN = A1;   // Joystick Y-axis
const int JOY_SW_PIN  = 2;    // Joystick push-button (optional)

const int SERVO_BASE_PIN = 9;   // Base rotation servo
const int SERVO_GRIP_PIN = 10;  // Grip / claw servo

// ---------- Servo Objects ----------
Servo servoBase;
Servo servoGrip;

// ---------- Servo State ----------
int baseAngle = 90;   // Start at center position
int gripAngle = 90;   // Start at center position

// ---------- Tuning Parameters ----------
const int DEADZONE      = 40;   // Ignore small joystick drift around center
const int STEP_SIZE     = 2;    // Degrees to move per loop when joystick is pushed
const int LOOP_DELAY_MS = 20;   // Controls movement speed / smoothness

bool gripToggled = false;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(JOY_SW_PIN, INPUT_PULLUP);

  servoBase.attach(SERVO_BASE_PIN);
  servoGrip.attach(SERVO_GRIP_PIN);

  servoBase.write(baseAngle);
  servoGrip.write(gripAngle);

  Serial.println("Robotic Arm Ready. Use joystick to move.");
}

void loop() {
  int xValue = analogRead(JOY_VRX_PIN);   // 0 - 1023
  int yValue = analogRead(JOY_VRY_PIN);   // 0 - 1023
  int buttonState = digitalRead(JOY_SW_PIN);

  // ---------- X-Axis controls Base rotation ----------
  int xCenterOffset = xValue - 512;
  if (abs(xCenterOffset) > DEADZONE) {
    if (xCenterOffset > 0) {
      baseAngle = constrain(baseAngle + STEP_SIZE, 0, 180);
    } else {
      baseAngle = constrain(baseAngle - STEP_SIZE, 0, 180);
    }
    servoBase.write(baseAngle);
  }

  // ---------- Y-Axis controls Grip/Arm joint ----------
  int yCenterOffset = yValue - 512;
  if (abs(yCenterOffset) > DEADZONE) {
    if (yCenterOffset > 0) {
      gripAngle = constrain(gripAngle + STEP_SIZE, 0, 180);
    } else {
      gripAngle = constrain(gripAngle - STEP_SIZE, 0, 180);
    }
    servoGrip.write(gripAngle);
  }

  // ---------- Button press: print status (optional toggle logic) ----------
  if (buttonState == LOW && lastButtonState == HIGH) {
    gripToggled = !gripToggled;
    Serial.println("Button pressed - toggle state changed.");
  }
  lastButtonState = buttonState;

  // ---------- Debugging output ----------
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Base Angle: ");
  Serial.print(baseAngle);
  Serial.print(" | Grip Angle: ");
  Serial.println(gripAngle);

  delay(LOOP_DELAY_MS);
}

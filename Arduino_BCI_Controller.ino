// Arduino code for a 2-wheel robot car using an L298N motor driver.
// This is the final version designed to listen for single-character commands
// from an external source like Node-RED.

// --- Pin Definitions ---

// Left Motor
const int ENA = 9; // Speed control (PWM) for Left Motor
const int IN1 = 8; // Direction control 1 for Left Motor
const int IN2 = 7; // Direction control 2 for Left Motor

// Right Motor
const int ENB = 6; // Speed control (PWM) for Right Motor
const int IN3 = 5; // Direction control 1 for Right Motor
const int IN4 = 4; // Direction control 2 for Right Motor

// Set a default speed for the motors (0-255)
// 200 is a good starting point, not too fast.
int motorSpeed = 200;

void setup() {
  // Set all the motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize Serial communication at 9600 baud rate
  Serial.begin(9600);

  // Start with the car stopped
  stopCar();
}

void loop() {
  // Check if there is data from the serial port
  if (Serial.available() > 0) {
    char command = Serial.read();

    // Act based on the command received
    switch (command) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopCar();
        break;
    }
  }
}

// --- Movement Functions ---

void moveForward() {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motorSpeed);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed);
}

void moveBackward() {
  // Left motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motorSpeed);

  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, motorSpeed);
}

void turnLeft() {
  // Left motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motorSpeed);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed);
}

void turnRight() {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motorSpeed);

  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, motorSpeed);
}

void stopCar() {
  // Stop left motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  // Stop right motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

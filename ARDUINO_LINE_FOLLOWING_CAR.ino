// Define motor control pins
#define in1 9
#define in2 8
#define in3 7
#define in4 6

// Define motor enable pins for speed control
#define enA 10
#define enB 5

// Define IR sensor pins
#define LeftIR A0
#define RightIR A1

// Define LED pin
#define ledPin 13
#define ledPin2 12

int motorSpeed = 200; // Set the initial motor speed (adjust as needed)
int sensorThreshold = 500; // Set the threshold value for IR sensors (adjust as needed)

void setup() {
  // Initialize motor control pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize motor enable pins for speed control
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Initialize IR sensor pins as inputs
  pinMode(LeftIR, INPUT);
  pinMode(RightIR, INPUT);

  // Initialize LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Set up serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Read IR sensor values
  int LEFT_SENSOR = analogRead(LeftIR);
  int RIGHT_SENSOR = analogRead(RightIR);

  // Line-following logic
  if (LEFT_SENSOR < sensorThreshold && RIGHT_SENSOR < sensorThreshold) {
    // Both sensors on the black line - move forward
    driveForward();
    digitalWrite(ledPin1, LOW); // Turn off LED1
    digitalWrite(ledPin2, LOW); // Turn off LED2

  } else if (LEFT_SENSOR >= sensorThreshold && RIGHT_SENSOR < sensorThreshold) {
    // Right sensor off the line - turn right
    turnRight();
    digitalWrite(ledPin1, HIGH); // Turn on LED1
    digitalWrite(ledPin2, LOW); // Turn off LED2

  } else if (LEFT_SENSOR < sensorThreshold && RIGHT_SENSOR >= sensorThreshold) {
    // Left sensor off the line - turn left
    turnLeft();
    digitalWrite(ledPin1, LOW); // Turn off LED1
    digitalWrite(ledPin2, HIGH); // Turn on LED2
  } else {
    // Both sensors off the line or on an intersection - stop
    stopRobot();
    digitalWrite(ledPin1, LOW); // Turn off LED1
    digitalWrite(ledPin2, LOW); // Turn off LED2
  }

  // Print sensor values for debugging (optional)
  Serial.print("LEFT_SENSOR: ");
  Serial.print(LEFT_SENSOR);
  Serial.print(" RIGHT_SENSOR: ");
  Serial.println(RIGHT_SENSOR);

  delay(100); // Delay for stability, adjust as needed
}

void driveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void stopRobot() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

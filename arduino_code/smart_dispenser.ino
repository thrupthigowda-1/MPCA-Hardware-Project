#include <Servo.h>

// Pin Definitions
#define IR_SENSOR 2
#define TRIG 4
#define ECHO 5
#define SERVO_PIN 9
#define WATER A0

Servo myServo;
int count = 0;

void setup() {
  pinMode(IR_SENSOR, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(150);

  Serial.begin(9600);
}

void loop() {
  int ir = digitalRead(IR_SENSOR);

  // Ultrasonic distance measurement
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  // Water sensor reading
  int level = analogRead(WATER);

  Serial.print("IR: ");
  Serial.print(ir);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Level: ");
  Serial.print(level);
  Serial.print(" | Count: ");
  Serial.println(count);

  if (ir == LOW && distance > 2 && distance < 12) {
    if (level < 300) {
      Serial.println("Low Liquid!");
    }

    myServo.write(60);
    delay(1200);

    myServo.write(150);
    delay(500);

    count++;
  }

  delay(500);
}